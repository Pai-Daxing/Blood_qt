#include<string.h>
#include "Protocol.h"

//extern void OUTPUT_TEXT(char *);

typedef enum _RX_STATE{
    _sWaitBegin,
    _sWaitType,
    _sWaitLoop,
    _sWaitLength,
    _sWaitData,
    _sWaitCheck,
    _sWaitEnd
    } RX_STATE;

u8 CharToAsciiHigh(u8 c)
	{
	u8 r = (0xF0 & c) >> 4;
	if (r<10)
		return '0' + r;
	else
		return 'A' + r - 10;
	}

u8 CharToAsciiLow(u8 c)
	{
	u8 r = (0x0F & c);
	if (r<10)
		return '0' + r;
	else
		return 'A' + r - 10;
	}

u8 AsciiToChar(u8 ch)
	{
	if (((ch<'0') || (ch>'9')) &&
		((ch<'A') || (ch>'F')))
		{
		return 255;
		}
	if ((ch>='0')&&(ch<='9'))
		{
		return ch - '0';
		}
	else
		{
		return ch - 'A' + 10;
		}
	}

s32 SendSecuredFrameAck(u8 loop, u8 ack)
    {
    u8 tx_buf[2 + 2 * sizeof(TDataLinkFrame)];

    int i = 0;
    u8 crc;

    tx_buf[i++]=0x02;
    tx_buf[i++]=CharToAsciiHigh(FRAME_TYPE_SECURED_ACK);
    tx_buf[i++]=CharToAsciiLow(FRAME_TYPE_SECURED_ACK);
    crc = FRAME_TYPE_SECURED_ACK;

    tx_buf[i++]=CharToAsciiHigh(loop);
    tx_buf[i++]=CharToAsciiLow(loop);
    crc += loop;

    tx_buf[i++]=CharToAsciiHigh(1);
    tx_buf[i++]=CharToAsciiLow(1);
    crc += 1;

    tx_buf[i++]=CharToAsciiHigh(ack);
    tx_buf[i++]=CharToAsciiLow(ack);
    crc += ack;

    crc = ~crc;
    tx_buf[i++]=CharToAsciiHigh(crc);
    tx_buf[i++]=CharToAsciiLow(crc);
    tx_buf[i++]=0x03;

    HostProtocol.hal.ptr_tx_hal(HostProtocol.hal.dev_handle, tx_buf, i);

    return 0;
    }
CMD_CB_INFO  cmdCbInfo[0xFF];
s32 HostProtocol_RxDataLink( TProtocol* ptr_protocol )
    {
    static RX_STATE smRxState = _sWaitBegin;
    static u8  usDataCnt;
	static u8  usChkSum;
	static u8  usRxWord;
	static u32 bHiByte     = TRUE;
    static TDataLinkFrame  buf;
	
	u16         iCmdCnt = 0;
	u8          ch;
    s32 cnt=0;
    s32 i=0;
    u8 chbuf[1024];
	
	cnt = ptr_protocol->hal.ptr_rx_hal(ptr_protocol->hal.dev_handle, chbuf, 1024);
	
    while(i < cnt)
		{
		ch = chbuf[i];
		i++;
		
		if (_sWaitBegin == smRxState) 
			{ 
			/* If sync mode then wait for flag byte first */
			if ( 0x02 == ch ) 
				{ 
                smRxState = _sWaitType;
				}
			continue;
			}
		if (_sWaitEnd == smRxState) 
			{
            if ( 0x03 == ch ) 
                {
                switch(buf.type)
                    {
                    case FRAME_TYPE_SECURED_ACK:
                        RingFifoIn(ptr_protocol->ptr_secured_frame_ack_fifo, (u8*)&buf);
                        break;
                    case FRAME_TYPE_SECURED:
                        /* Correct command received */
                        {
                        u8 id = *(buf.payload);
                        cmdAckType ack = cmdAck_OK;
                        CMD_CB_INFO info = cmdCbInfo[id];
                        if ((info.id == id) && info.pf)
                            {
                            ack = info.pf(buf.payload, sizeof(buf.payload));
                            }
                        SendSecuredFrameAck(buf.loop, ack);
                        }
                        break;
                    case FRAME_TYPE_NONE_SECURED:
                        if ( RingFifoIn(ptr_protocol->ptr_received_frame_fifo , (u8*)&buf) )
                            {
                            iCmdCnt++;
                            }
                        else
                            {
                            //OUTPUT_TEXT("buffer full");
                            }
                        break;
                    default:
                        break;
                    }
                smRxState = _sWaitBegin;
                }
            continue;
			}
		
		if (bHiByte) 
			{ 
			ch = AsciiToChar(ch);
			if (ch > 0x0F)
				{
                if (FRAME_TYPE_SECURED == buf.type &&
                    (_sWaitLength == smRxState ||
                     _sWaitData == smRxState ||
                     _sWaitCheck == smRxState))
                    {
                    SendSecuredFrameAck(buf.loop, cmdAck_UnexpectedEnd);
                    }
                smRxState = _sWaitBegin;
				continue;
				}
			usRxWord = ch << 4;
			bHiByte = FALSE;
			}
		else
			{
			ch = AsciiToChar(ch);
			if (ch > 0x0F)
				{
                if (FRAME_TYPE_SECURED == buf.type &&
                    (_sWaitLength == smRxState ||
                     _sWaitData == smRxState ||
                     _sWaitCheck == smRxState))
                    {
                    SendSecuredFrameAck(buf.loop, cmdAck_UnexpectedEnd);
                    }
                smRxState = _sWaitBegin;
				continue;
				}
			usRxWord += ch;
			bHiByte = TRUE;
			
            switch (smRxState)
                {
                case _sWaitType:
                if (usRxWord != FRAME_TYPE_SECURED &&
                    usRxWord != FRAME_TYPE_SECURED_ACK &&
                    usRxWord != FRAME_TYPE_NONE_SECURED)
                    {
                    //OUTPUT_TEXT("invalid frame type");
                    smRxState = _sWaitBegin;
                    }
                else
                    {
                    buf.type = usRxWord;
                    usChkSum = usRxWord;
                    smRxState = _sWaitLoop;
                    }
                break;

                case _sWaitLoop:
                    buf.loop = usRxWord;
                    usChkSum += usRxWord;
                    smRxState = _sWaitLength;
                break;

                case _sWaitLength:
                if (usRxWord > DATA_LINK_FRAME_LEN)
                    {
                    if (FRAME_TYPE_SECURED == buf.type)
                        {
                        SendSecuredFrameAck(buf.loop, cmdAck_InvalidLen);
                        }
                    //OUTPUT_TEXT("invalid param length");
                    smRxState = _sWaitBegin;
                    }
                else
                    {
                    buf.len = usRxWord;
                    usChkSum += usRxWord;
                    usDataCnt = 0;
                    if(buf.len != 0)
                        smRxState = _sWaitData;
                    else
                        smRxState = _sWaitCheck;
                    }

                break;

                case _sWaitData:
                    buf.payload[usDataCnt++] = usRxWord;
                    usChkSum += usRxWord;
                    if (usDataCnt == buf.len)
                        {
                        smRxState = _sWaitCheck;
                        }

                    break;

				case _sWaitCheck:
                    buf.crc = usRxWord;
                    usChkSum += usRxWord;
					if (usChkSum != 0xFF) 
                        {
//						OUTPUT_TEXT("invalid checksum");
                        if (FRAME_TYPE_SECURED == buf.type)
                            {
                            SendSecuredFrameAck(buf.loop, cmdAck_IncorrectCRC);
                            }
						smRxState = _sWaitBegin;
						}
                    else
                        {
                        smRxState = _sWaitEnd;
						}
                    break;
                default:
                    break;
				}  /* switch(RxState) */
			}  /* Word received */
		}
    return iCmdCnt;
    } /* RxInt */




/* HostProtocol RxCmd */
#define HOST_PROTOCOL_RX_FIFO_LEN  (32) /* number of commands that can be buffered between 20ms execute intervals */
#define HOST_PROTOCOL_RX_BUF_SZ   (sizeof(TDataLinkFrame) * HOST_PROTOCOL_RX_FIFO_LEN)
u8 _HostProtocolRxFrameBuffer[HOST_PROTOCOL_RX_BUF_SZ];
TRingFifo HostProtocolRxFrameFifo = 
    {_HostProtocolRxFrameBuffer, sizeof(TDataLinkFrame), HOST_PROTOCOL_RX_FIFO_LEN, 0, 0};

#define HOST_PROTOCOL_SECURED_ACK_FIFO_LEN  (32) /* number of commands that can be buffered between 20ms execute intervals */
#define HOST_PROTOCOL_SECURED_ACK_BUF_SZ   (sizeof(TDataLinkFrame) * HOST_PROTOCOL_SECURED_ACK_FIFO_LEN)
u8 _HostProtocolRxSecuredAckFifoBuffer[HOST_PROTOCOL_SECURED_ACK_BUF_SZ];
TRingFifo HostProtocolRxSecuredAckFifo =
    {_HostProtocolRxSecuredAckFifoBuffer, sizeof(TDataLinkFrame), HOST_PROTOCOL_SECURED_ACK_FIFO_LEN, 0, 0};


/* HostProtocol Major Object */
TProtocol HostProtocol = {
    {0},
    &HostProtocolRxFrameFifo,
    &HostProtocolRxSecuredAckFifo,
    };


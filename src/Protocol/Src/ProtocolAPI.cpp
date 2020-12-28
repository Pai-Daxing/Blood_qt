#include"../ProtocolAPI.h"
#include<string.h>

#ifdef Q_WS_WIN32
#include <windows.h>
#endif
#ifdef Q_WS_QWS
#include <unistd.h>
#endif
#ifdef Q_WS_X11
#include <unistd.h>
#endif

extern u8 CharToAsciiHigh(u8 c);
extern u8 CharToAsciiLow(u8 c);
extern TProtocol HostProtocol;

void Protocol_Register(s32 dev_handle, pfProtocolHal ptr_rx_hal, pfProtocolHal ptr_tx_hal)
    {
    HostProtocol.hal.dev_handle = dev_handle;
    HostProtocol.hal.ptr_rx_hal = ptr_rx_hal;
    HostProtocol.hal.ptr_tx_hal = ptr_tx_hal;
    }

void Protocol_RxAction()
    {
    HostProtocol_RxDataLink(&HostProtocol);
    }

u8 Protocol_GetFrame(u8 * buf, u8 len)
    {
    TDataLinkFrame * ptr_frame;
    if (RingFifoGetFull(HostProtocol.ptr_received_frame_fifo, (u8**)&ptr_frame))
        {
        u8 actual_len = ptr_frame->len < len ? ptr_frame->len : len;
        memcpy(buf, ptr_frame->payload, actual_len);
        RingFifoCommitOut(HostProtocol.ptr_received_frame_fifo);
        return actual_len;
        }
    return 0;
    }

s32 Protocol_Send(const u8 * buf, u8 len)
    {
    u8 tx_buf[2 + 2 * sizeof(TDataLinkFrame)];

    int i,j;
    u8 crc;
    i=0;

    tx_buf[i++]=0x02;
    tx_buf[i++]=CharToAsciiHigh(FRAME_TYPE_NONE_SECURED);
    tx_buf[i++]=CharToAsciiLow(FRAME_TYPE_NONE_SECURED);
    crc = FRAME_TYPE_NONE_SECURED;

    tx_buf[i++]=CharToAsciiHigh(0);
    tx_buf[i++]=CharToAsciiLow(0);
    crc += 0;

    tx_buf[i++]=CharToAsciiHigh(len);
    tx_buf[i++]=CharToAsciiLow(len);
    crc += len;
    for(j=0;j<len;j++)
        {
        tx_buf[i++]=CharToAsciiHigh(buf[j]);
        tx_buf[i++]=CharToAsciiLow(buf[j]);
        crc += buf[j];
        }
    crc = ~crc;
    tx_buf[i++]=CharToAsciiHigh(crc);
    tx_buf[i++]=CharToAsciiLow(crc);
    tx_buf[i++]=0x03;

    HostProtocol.hal.ptr_tx_hal(HostProtocol.hal.dev_handle, tx_buf, i);

    return 0;
    }

s32 Protocol_Send_Secure(const u8 * buf, u8 len, s32 timeout)
    {
    static u8 loop = 0;
    u8 tx_buf[2 + 2 * sizeof(TDataLinkFrame)];

    int i = 0, j;
    u8 crc;
    loop++;

    tx_buf[i++]=0x02;
    tx_buf[i++]=CharToAsciiHigh(FRAME_TYPE_SECURED);
    tx_buf[i++]=CharToAsciiLow(FRAME_TYPE_SECURED);
    crc = FRAME_TYPE_SECURED;

    tx_buf[i++]=CharToAsciiHigh(loop);
    tx_buf[i++]=CharToAsciiLow(loop);
    crc += loop;

    tx_buf[i++]=CharToAsciiHigh(len);
    tx_buf[i++]=CharToAsciiLow(len);
    crc += len;
    for(j=0;j<len;j++)
        {
        tx_buf[i++]=CharToAsciiHigh(buf[j]);
        tx_buf[i++]=CharToAsciiLow(buf[j]);
        crc += buf[j];
        }
    crc = ~crc;
    tx_buf[i++]=CharToAsciiHigh(crc);
    tx_buf[i++]=CharToAsciiLow(crc);
    tx_buf[i++]=0x03;

    HostProtocol.hal.ptr_tx_hal(HostProtocol.hal.dev_handle, tx_buf, i);

    while(timeout > 0)
        {
        TDataLinkFrame* ack;
        if (RingFifoGetFull(HostProtocol.ptr_secured_frame_ack_fifo, (u8**)&ack))
            {
            if ((*ack).loop == loop)
                {
                RingFifoCommitOut(HostProtocol.ptr_secured_frame_ack_fifo);
                return (*ack).payload[0];
                }
            RingFifoCommitOut(HostProtocol.ptr_secured_frame_ack_fifo);
            }
#ifdef Q_WS_WIN32
        Sleep(50);
#endif
#ifdef Q_WS_QWS
        usleep(50000);
#endif
#ifdef Q_WS_X11
        usleep(50000);
#endif
        timeout -= 50;
        }

    return cmdAck_TimeOut;
    }

void Protocol_RegistCmdProc(u8 cmdId, pfCmdCallback ptr_func)
{
    cmdCbInfo[cmdId].id = cmdId;
    cmdCbInfo[cmdId].pf = ptr_func;
}

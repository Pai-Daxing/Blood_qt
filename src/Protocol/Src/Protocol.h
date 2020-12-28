#ifndef __SYS_HOST_PROTOCOL_H_
#define __SYS_HOST_PROTOCOL_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "RingFifo.h"

typedef s32 (*pfProtocolHal)(s32 dev_handle, u8 * buf, u32 size);

typedef struct _TProtocolHAL
    {
    s32 dev_handle;
    pfProtocolHal ptr_rx_hal; /* hw abstraction layer, platform dependent */
    pfProtocolHal ptr_tx_hal; /* hw abstraction layer, platform dependent */
    }TProtocolHAL;

typedef struct _TProtocol
    {
    TProtocolHAL hal;

    TRingFifo * ptr_received_frame_fifo;
    TRingFifo * ptr_secured_frame_ack_fifo;
    }TProtocol;

#define DATA_LINK_FRAME_LEN     (128)

#define FRAME_TYPE_SECURED         (1)
#define FRAME_TYPE_SECURED_ACK     (2)
#define FRAME_TYPE_NONE_SECURED    (3)

typedef struct
    {
    u8 type;
    u8 loop;
    u8 len;
    u8 payload[DATA_LINK_FRAME_LEN];
    u8 crc;
    }TDataLinkFrame;

extern TProtocol HostProtocol;

s32 HostProtocol_TxDataLink(TProtocol* ptr_protocol);
s32 HostProtocol_RxDataLink(TProtocol* ptr_protocol);
s32 HostProtocol_TxLogic(TProtocol* ptr_protocol);
s32 HostProtocol_RxLogic(TProtocol* ptr_protocol);

typedef enum
    {
    cmdAck_OK = 0,
    cmdAck_InvalidLen,
    cmdAck_IncorrectCRC,
    cmdAck_UnexpectedEnd,
    cmdAck_ReceiveBufferFull,
    cmdAck_TimeOut,
    cmdAck_Reject,
    }cmdAckType;

typedef cmdAckType (*pfCmdCallback)(u8* buf, s32 len);

typedef struct _cmd_cb_info
    {
    u8              id;
    pfCmdCallback   pf;
    } CMD_CB_INFO;


extern CMD_CB_INFO  cmdCbInfo[0xFF];

#ifdef __cplusplus
}
#endif

#endif /* __SYS_HOST_PROTOCOL_H_ */

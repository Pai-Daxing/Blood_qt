#ifndef _INCLUDE_sys_API_H_
#define _INCLUDE_sys_API_H_


#include "Src/Protocol.h"
#include "alarms.h"
#include "commands.h"
#include "status.h"

#ifdef __cplusplus
#include "qglobal.h"
extern "C"{
#endif

void Protocol_Register(s32 dev_handle, pfProtocolHal ptr_rx_hal, pfProtocolHal ptr_tx_hal);
void Protocol_RxAction();
void Protocol_RegistCmdProc(u8 cmdId, pfCmdCallback ptr_func);//注册命令响应函数(命令响应函数将被同步调用)
s32 Protocol_Send(const u8 * buf, u8 len);//发送不需要应答的数据

u8  Protocol_GetFrame(u8 * buf, u8 len);//获取不需要应答的数据(异步)
s32 Protocol_Send_Secure(const u8 * buf, u8 len, s32 timeout);//发送需要应答的数据

#ifdef __cplusplus
}
#endif

#endif

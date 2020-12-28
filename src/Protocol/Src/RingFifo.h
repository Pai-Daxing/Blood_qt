/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MISC_RINGFIFO_H
#define __MISC_RINGFIFO_H
#ifdef __cplusplus
extern "C"{
#endif
/* Includes ------------------------------------------------------------------*/
#include "../types.h"
/* Exported types ------------------------------------------------------------*/
typedef struct _TRingFifo
{
  u8* buf_addr;
  u16 unit_size; /* how many bytes is one fifo node */
  u16 fifo_len;
  u16 out_index;
  u16 in_index;  
}TRingFifo;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
s32 RingFifoOut(TRingFifo* pfifo, u8* pout);
s32 RingFifoIn(TRingFifo* pfifo, u8* pin);
s32 RingFifoGetFree(TRingFifo* pfifo, u8** punit);
s32 RingFifoGetFull(TRingFifo* pfifo, u8** punit);
s32 RingFifoCommitIn(TRingFifo* pfifo);
s32 RingFifoCommitOut(TRingFifo* pfifo);
s32 RingFifoConstruct(TRingFifo* pfifo, u8* pbuf, u16 unit_size, u16 fifo_len);
#ifdef __cplusplus
}
#endif
#endif /* __MISC_RINGFIFO_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/

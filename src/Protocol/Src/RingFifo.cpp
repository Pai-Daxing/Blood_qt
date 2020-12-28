/* Includes ------------------------------------------------------------------*/
#include "RingFifo.h"

/** @addtogroup STM32F10x_StdPeriph_Examples
* @{
*/

/** @addtogroup USART_Interrupt
* @{
*/ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/
/**
* @brief  This function handles PPP interrupt request.
* @param  None
* @retval None
*/
s32 RingFifoOut(TRingFifo* pfifo, u8* pout)
    {
    u16 i;
    u8* ptr_unit;
    if(pfifo->out_index != pfifo->in_index)
        {
        ptr_unit = pfifo->buf_addr + pfifo->unit_size * pfifo->out_index;
        for(i=0; i<pfifo->unit_size; i++)
            *(pout+i) = *(ptr_unit+i);
        pfifo->out_index = (pfifo->out_index + pfifo->fifo_len + 1)%pfifo->fifo_len;
        return 1;
        }
    return 0;
    }
    /**
    * @brief  This function handles PPP interrupt request.
    * @param  None
    * @retval None
*/
s32 RingFifoIn(TRingFifo* pfifo, u8* pin)
    {
    u16 i;
    u8* ptr_unit;
    if( pfifo->out_index != (pfifo->in_index + pfifo->fifo_len +1 )%pfifo->fifo_len )
        {
        ptr_unit = pfifo->buf_addr + pfifo->unit_size * pfifo->in_index;
        for(i=0; i<pfifo->unit_size; i++)
            *(ptr_unit+i) = *(pin+i);
        pfifo->in_index = (pfifo->in_index + pfifo->fifo_len + 1)%pfifo->fifo_len;
        return 1;
        }
    return 0;
    }
    /**
    * @brief  This function handles PPP interrupt request.
    * @param  None
    * @retval None
*/
s32 RingFifoConstruct(TRingFifo* pfifo, u8* pbuf, u16 unit_size, u16 fifo_len)
    {
    pfifo->buf_addr = pbuf;
    pfifo->unit_size = unit_size;
    pfifo->fifo_len = fifo_len;
    pfifo->in_index = pfifo->out_index = 0;
    return 1;
    }
    /**
    * @brief  This function handles PPP interrupt request.
    * @param  None
    * @retval None
*/
s32 RingFifoGetFree(TRingFifo* pfifo, u8** punit)
    {
    if( pfifo->out_index != (pfifo->in_index + pfifo->fifo_len +1 )%pfifo->fifo_len )
        {
        *punit = pfifo->buf_addr + pfifo->unit_size * pfifo->in_index;
        return 1;
        }
    return 0;
    }

s32 RingFifoGetFull(TRingFifo* pfifo, u8** punit)
    {
    if(pfifo->out_index != pfifo->in_index)
        {
        *punit = pfifo->buf_addr + pfifo->unit_size * pfifo->out_index;
        return 1;
        }
    return 0;
    }

s32 RingFifoCommitIn(TRingFifo* pfifo)
    {
    if( pfifo->out_index != (pfifo->in_index + pfifo->fifo_len +1 )%pfifo->fifo_len )
        {
        pfifo->in_index = (pfifo->in_index + pfifo->fifo_len + 1)%pfifo->fifo_len;
        return 1;
        }
    return 0;  
    }

s32 RingFifoCommitOut(TRingFifo* pfifo)
    {
    if(pfifo->out_index != pfifo->in_index)
        {
        pfifo->out_index = (pfifo->out_index + pfifo->fifo_len + 1)%pfifo->fifo_len;
        return 1;
        }
    return 0;  
    }
    /**
    * @brief  This function handles PPP interrupt request.
    * @param  None
    * @retval None
*/
/*void PPP_IRQHandler(void)
{
}*/

/**
* @}
*/ 

/**
* @}
*/ 

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/

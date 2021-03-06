/******************************************************************************
* Copyright (C) 2017, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd ("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC
* components. This software is licensed by HDSC to be adapted only
* for use in systems utilizing HDSC components. HDSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. HDSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/
/*****************************************************************************/
/** \file uart.h
 **
 ** Headerfile for UART functions
 **  
 **
 ** History:
 **   - 2017-05-10   Cathy     First Version
 **
 *****************************************************************************/

#ifndef __UART_H__
#define __UART_H__
/*****************************************************************************
 * Include files
 *****************************************************************************/
#include "ddl.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup UartGroup Universal Asynchronous Receiver/Transmitter (UART)
 **
 ******************************************************************************/
//@{

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief uart????????????????????????/???????????????????????????
 ******************************************************************************/
typedef enum en_uart_mmdorck
{
    UartData = 0u, ///<??????????????????????????????TB8??????   
    UartAddr = 1u, ///<??????????????????????????????TB8??????   
}en_uart_mmdorck_t;
/**
 ******************************************************************************
 ** \brief uart????????????
 ******************************************************************************/
typedef enum en_uart_check
{
    UartEven = 0u, ///<?????????
    UartOdd  = 1u, ///<?????????
}en_uart_check_t;
/**
 ******************************************************************************
 ** \brief uart?????????????????????
 ******************************************************************************/
typedef enum en_uart_multimode
{
    UartNormal = 0u, ///<??????????????????
    UartMulti  = 1u, ///<?????????????????????
}en_uart_multimode_t;
/**
 ******************************************************************************
 ** \brief uart???????????????????????????????????????????????????
 ******************************************************************************/

typedef struct stc_uart_multimode
{
    uint8_t             u8SlaveAddr;  ///<????????????
    uint8_t             u8SaddEn;     ///<??????????????????
}stc_uart_multimode_t;

/**
 ******************************************************************************
 ** \brief uart ????????????????????????
 ******************************************************************************/

typedef enum en_uart_mode
{
    UartMode0 = 0u, ///<??????0    
    UartMode1 = 1u, ///<??????1
    UartMode2 = 2u, ///<??????2
    UartMode3 = 3u, ///<??????3
} en_uart_mode_t;
/**
 ******************************************************************************
 ** \brief uart ????????????????????????
 ******************************************************************************/
typedef enum en_uart_func
{
    UartRenFunc    = 4u,    ///<0-TX; ///<1-???mode0????????????RX&TX ,mode0????????????RX; 
}en_uart_func_t;
/**
 ******************************************************************************
 ** \brief uart????????????????????????
 ******************************************************************************/
typedef enum en_uart_irq_sel
{
    UartRxIrq  = 0u,    ///<??????????????????
    UartTxIrq  = 1u,    ///<??????????????????  
}en_uart_irq_sel_t;

/**
 ******************************************************************************
 ** \brief uart ???????????????
 ******************************************************************************/
typedef enum en_uart_status
{
    UartRC    = 0u,  ///<????????????????????????
    UartTC    = 1u,  ///<????????????????????????
    UartFE    = 2u,  ///<???????????????
   
}en_uart_status_t;
/**
 ******************************************************************************
 ** \brief uart ??????????????????
 ******************************************************************************/
typedef struct stc_uart_instance_data
{   
    uint32_t               u32Idx;               ///< ?????????
    M0P_UART_TypeDef       *pstcInstance;        ///< ?????????????????????
} stc_uart_instance_data_t;
/**
 ******************************************************************************
 ** \brief uart ?????????????????????
 ******************************************************************************/
typedef struct stc_uart_baud_cfg
{
    en_uart_mode_t enMode;   ///<??????????????????
    boolean_t      bDbaud;   ///<?????????????????????
    uint32_t       u32Pclk;  ///< PCLK
    uint32_t       u32Baud;  ///<?????????
}stc_uart_baud_cfg_t;

/**
 ******************************************************************************
 ** \uart ????????????
 ******************************************************************************/
typedef struct stc_uart_cfg
{
    en_uart_mode_t       enRunMode;     ///<??????????????????
} stc_uart_cfg_t;

//UART?????????
en_result_t Uart_Init(M0P_UART_TypeDef* UARTx, stc_uart_cfg_t* pstcCfg);

///<????????????????????????
en_result_t Uart_EnableIrq(M0P_UART_TypeDef* UARTx, en_uart_irq_sel_t enIrqSel);
en_result_t Uart_DisableIrq(M0P_UART_TypeDef* UARTx, en_uart_irq_sel_t enIrqSel);

// ???????????????
en_result_t Uart_Init(M0P_UART_TypeDef* UARTx, stc_uart_cfg_t* pstcCfg);

// ???????????????
uint16_t Uart_SetBaudRate(M0P_UART_TypeDef* UARTx,stc_uart_baud_cfg_t* pstcBaud);

///<UART??????????????????????????????
en_result_t Uart_SetMultiMode(M0P_UART_TypeDef* UARTx, stc_uart_multimode_t* pstcMultiCfg);
                             
///< ??????????????????????????????
en_result_t Uart_EnableFunc(M0P_UART_TypeDef* UARTx, en_uart_func_t enFunc);
en_result_t Uart_DisableFunc(M0P_UART_TypeDef* UARTx, en_uart_func_t enFunc);

///< ???????????????????????????
uint8_t Uart_GetIsr(M0P_UART_TypeDef* UARTx);
boolean_t Uart_GetStatus(M0P_UART_TypeDef* UARTx,en_uart_status_t enStatus);
en_result_t Uart_ClrIsr(M0P_UART_TypeDef* UARTx);
en_result_t Uart_ClrStatus(M0P_UART_TypeDef* UARTx,en_uart_status_t enStatus);

//??????????????????
///< ????????????????????????
en_result_t Uart_SendDataPoll(M0P_UART_TypeDef* UARTx, uint8_t u8Data);
///< ????????????????????????
en_result_t Uart_SendDataIt(M0P_UART_TypeDef* UARTx, uint8_t u8Data);
uint8_t Uart_ReceiveData(M0P_UART_TypeDef* UARTx);
///< ??????????????????
en_result_t Uart_CheckEvenOrOdd(M0P_UART_TypeDef* UARTx, en_uart_check_t enCheck, uint8_t u8Recv);
///< ??????Rb8???
boolean_t Uart_GetRb8(M0P_UART_TypeDef* UARTx);
//< ??????TB8
en_result_t Uart_SetTb8(M0P_UART_TypeDef* UARTx, en_uart_check_t enCheck, uint8_t u8Data);


//@} // UartGroup

#ifdef __cplusplus
#endif

#endif /* __UART_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/




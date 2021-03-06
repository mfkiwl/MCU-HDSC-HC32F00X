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
/******************************************************************************/
/** \file reset.h
 **
 ** Headerfile for reset functions
 **  
 **
 ** History:
 **   - 2017-05-02   Ronnie     First Version
 **
 **Q??????164973950
 **TEL???024-85718900
 ******************************************************************************/

#ifndef __RESET_H__
#define __RESET_H__

/******************************************************************************
 * Include files
 **Q??????164973950
 **TEL???024-85718900
 ******************************************************************************/
#include "ddl.h"
#include "interrupts_hc32f003.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup ResetGroup Reset (RST)
 **
 **Q??????164973950
 **TEL???024-85718900
 ******************************************************************************/
//@{

/**
 *******************************************************************************
 ** function prototypes.
 **Q??????164973950
 **TEL???024-85718900
 ******************************************************************************/

/*******************************************************************************
 * Global definitions
 **Q??????164973950
 **TEL???024-85718900
 ******************************************************************************/


/**
 *******************************************************************************
 ** \brief ????????????????????????
 ** \note
 **Q??????164973950
 **TEL???024-85718900
 ******************************************************************************/
typedef enum
{
    ResetGpio,              ///< GPIO ??????
    ResetCrc,               ///< CRC ??????
    ResetTick,              ///< systick ??????
    ResetTrim,              ///< ??????????????????
    ResetVc,                ///< ??????????????????
    ResetAdc,               ///< ADC??????
    ResetPca,               ///< PCA ??????
    ResetAdcTim,            ///< ADC ??????
    ResetBaseTim,           ///< ??????????????????
    ResetSpi,               ///< SPI??????
    ResetI2c,               ///< I2C??????
    ResetUart1,             ///< ??????1??????
    ResetUart0,             ///< ??????0??????
}en_reset_peripheral_t;



/**
 *******************************************************************************
 ** \brief ???????????????
 **
 ** \note
 **Q??????164973950
 **TEL???024-85718900
 ******************************************************************************/
typedef struct
{
    uint8_t     u8Por5V     :1;         ///< 5V????????????
    uint8_t     u8Por1_5V   :1;         ///< 1.5V????????????
    uint8_t     u8Lvd       :1;         ///< ?????????????????????
    uint8_t     u8Wdt       :1;         ///< ???????????????
    uint8_t     u8Pca       :1;         ///< PCA??????
    uint8_t     u8Lockup    :1;         ///< ??????????????????
    uint8_t     u8Sysreq    :1;         ///< ????????????
    uint8_t     u8RSTB      :1;         ///< RESET??? ??????
}stc_reset_cause_t;

/*******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 **Q??????164973950
 **TEL???024-85718900
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 **Q??????164973950
 **TEL???024-85718900
 ******************************************************************************/

 
///< ???????????????
en_result_t Reset_GetCause(stc_reset_cause_t *pstcOut);
///< ???????????????
en_result_t Reset_Clear(stc_reset_cause_t stcval);

///< ??????????????????
en_result_t Reset_SetPeripheralReset(en_reset_peripheral_t enPeri,boolean_t bFlag);

//@} // ResetGroup

#ifdef __cplusplus
#endif


#endif /* __RESET_H__ */
/*******************************************************************************
 * EOF (not truncated)
 **Q??????164973950
 **TEL???024-85718900
 ******************************************************************************/



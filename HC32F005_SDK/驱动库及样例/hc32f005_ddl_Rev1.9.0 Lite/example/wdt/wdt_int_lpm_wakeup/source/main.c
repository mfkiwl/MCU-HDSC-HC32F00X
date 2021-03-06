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
/** \file main.c
 **
 ** A detailed description is available at
 ** @link Sample Group Some description @endlink
 **
 **   - 2017-05-17  1.0  CJ First version for Device Driver Library of Module.
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/

#include "wdt.h"
#include "lpm.h"
#include "gpio.h"

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/******************************************************************************
 * Local variable definitions ('static')                                      *
 ******************************************************************************/

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

uint8_t u32CountWdt;
uint8_t u8Flag=0xFF;

static void App_GpioInit(void);
static void App_WdtInit(void);

/**
 ******************************************************************************
 ** \brief  Main function of project
 **
 ** \return uint32_t return value, if needed
 **
 ** This sample
 **
 ******************************************************************************/
int32_t main(void)
{
    ///< ===============================================
    ///< ============ ?????????????????????????????????=============
    ///< ===============================================
    ///< ?????????????????????????????????????????????????????????????????????????????????????????????????????????
    ///< ???????????????????????????????????????????????????
    ///< ??????????????????????????????????????????????????????????????????????????????????????????
    delay1ms(2000);

    ///< GPIO ?????????
    App_GpioInit();
    while(TRUE == Gpio_GetInputIO(STK_USER_PORT, STK_USER_PIN));

    ///< WDT ?????????
    App_WdtInit();

    ///< ?????? WDT
    Wdt_Start();

    ///< ???????????????????????????????????????????????????????????????
    Lpm_GotoDeepSleep(TRUE);

    while (1)
    {
        ;
    }
}


///< WDT ??????????????????
void Wdt_IRQHandler(void)
{
    if(Wdt_GetIrqStatus())
    {
        Wdt_IrqClr();       ///<?????? wdt ????????????

        u8Flag = ~u8Flag;
        if(u8Flag)
        {
            Gpio_WriteOutputIO(STK_LED_PORT, STK_LED_PIN, TRUE);
        }
        else
        {
            Gpio_WriteOutputIO(STK_LED_PORT, STK_LED_PIN, FALSE);
        }

        u32CountWdt++;
    }

}

static void App_WdtInit(void)
{
    ///< ??????WDT????????????
    Sysctrl_SetPeripheralGate(SysctrlPeripheralWdt,TRUE);
    ///< WDT ?????????
    Wdt_Init(WdtIntEn, WdtT820ms);
    ///< ??????NVIC??????
    EnableNvic(WDT_IRQn, IrqLevel3, TRUE);
}



static void _LowPowerModeGpioSet(void)
{
    ///< ??????GPIO????????????
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio,TRUE);

    //swd as gpio
    Sysctrl_SetFunc(SysctrlSWDUseIOEn, TRUE);

    ///< ?????????????????????
    M0P_GPIO->P0ADS = 0;
    M0P_GPIO->P1ADS = 0;
    M0P_GPIO->P2ADS = 0;
    M0P_GPIO->P3ADS = 0;

    ///< ???????????????????????????LED????????????
    M0P_GPIO->P0DIR = 0XFFF7;
    M0P_GPIO->P1DIR = 0XFFFF;
    M0P_GPIO->P2DIR = 0XFFFF;
    M0P_GPIO->P3DIR = 0XFFFF;

    ///< ??????????????????KEY???????????????
    M0P_GPIO->P0PD = 0xFFF7;
    M0P_GPIO->P1PD = 0xFFFF;
    M0P_GPIO->P2PD = 0xFFFF;
    M0P_GPIO->P3PD = 0xFFF7;

}

static void App_GpioInit(void)
{
    stc_gpio_cfg_t stcGpioCfg;

    DDL_ZERO_STRUCT(stcGpioCfg);

    ///< ??????GPIO????????????
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio,TRUE);

    _LowPowerModeGpioSet();

    ///< LED ?????????
    stcGpioCfg.enDir = GpioDirOut;
    Gpio_WriteOutputIO(STK_LED_PORT,STK_LED_PIN,TRUE);
    Gpio_Init(STK_LED_PORT,STK_LED_PIN,&stcGpioCfg);

    ///< ??????????????????->??????
    stcGpioCfg.enDir = GpioDirIn;
    ///< ????????????????????????->???????????????
    stcGpioCfg.enDrv = GpioDrvL;
    ///< ?????????????????????->??????
    stcGpioCfg.enPu = GpioPuEnable;
    stcGpioCfg.enPd = GpioPdDisable;
    ///< ????????????????????????->??????????????????
    stcGpioCfg.enOD = GpioOdDisable;

    ///< GPIO IO USER KEY?????????
    Gpio_Init(STK_USER_PORT, STK_USER_PIN, &stcGpioCfg);

}

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/



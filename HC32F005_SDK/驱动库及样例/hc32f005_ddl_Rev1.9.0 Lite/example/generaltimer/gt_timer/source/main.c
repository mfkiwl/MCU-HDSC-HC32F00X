/******************************************************************************
* Copyright (C) 2016, Huada Semiconductor Co.,Ltd All rights reserved.
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
 **   - 2016-02-16  1.0  XYZ First version for Device Driver Library of Module.
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"
#include "bt.h"
#include "lpm.h"
#include "gpio.h"

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static volatile uint32_t u32BtTestFlag = 0;
static volatile uint32_t u32Cnt = 0;

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/


/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
static void App_GpioInit(void);
static en_result_t App_BtTimerTest(void);



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
    volatile uint8_t u8TestFlag = 0;

    App_GpioInit();

    if(Ok != App_BtTimerTest())
    {
        u8TestFlag |= 0x02;
    }

    while (1);
}


/*******************************************************************************
 * BT1中断服务函数
 ******************************************************************************/
void Tim1_IRQHandler(void)
{
    if (TRUE == Bt_GetIntFlag(TIM1))
    {
        Bt_ClearIntFlag(TIM1);
        u32BtTestFlag = 0x02;
    }
}

/*******************************************************************************
 * BT定时功能测试 （重载模式）
 ******************************************************************************/
static en_result_t App_BtTimerTest(void)
{
    stc_bt_cfg_t   stcCfg;
    en_result_t       enResult = Error;
    uint16_t          u16ArrData = 0x8000;
    uint16_t          u16InitCntData = 0xC000;

    //打开BT外设时钟
    Sysctrl_SetPeripheralGate(SysctrlPeripheralBt, TRUE);

    stcCfg.enGateP = BtPositive;
    stcCfg.enGate  = BtGateEnable;
    stcCfg.enPRS   = BtPCLKDiv16;
    stcCfg.enTog   = BtTogDisable;
    stcCfg.enCT    = BtTimer;
    stcCfg.enMD    = BtMode2;
    //Bt初始化
    if (Ok != Bt_Init(TIM1, &stcCfg))
    {
        enResult = Error;
    }

    //TIM1中断使能
    Bt_ClearIntFlag(TIM1);
    Bt_EnableIrq(TIM1);
    EnableNvic(TIM1_IRQn, IrqLevel3, TRUE);

    //设置重载值和计数值，启动计数
    Bt_ARRSet(TIM1, u16ArrData);
    Bt_Cnt16Set(TIM1, u16InitCntData);
    Bt_Run(TIM1);

    //此处进入中断……
    while(1)
    {
        //判断是否第二次进入中断
        if (0x02 == u32BtTestFlag)
        {
            u32BtTestFlag = u32BtTestFlag & (~0x02);
            if (1 == u32Cnt)
            {
                Bt_Stop(TIM1);
                enResult = Ok;
                break;
            }
            u32Cnt++;
        }
    }

    return enResult;
}

static void App_GpioInit(void)
{
    stc_gpio_cfg_t         stcTIM1Port;

    DDL_ZERO_STRUCT(stcTIM1Port);

    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE); //端口外设时钟使能

    stcTIM1Port.enDir  = GpioDirOut;
    //P25设置为TIM1_GATE
    Gpio_Init(GpioPort2, GpioPin5, &stcTIM1Port);
    Gpio_SetAfMode(GpioPort2,GpioPin5,GpioAf7);

}

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/



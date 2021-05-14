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
//Q群：164973950
//TEL：024-85718900
/******************************************************************************/
//Q群：164973950
//TEL：024-85718900
/** \file main.c
 **
 ** A detailed description is available at
 ** @link Sample Group Some description @endlink
 **
 **   - 2017-05-28 LiuHL    First Version
 **
 ******************************************************************************/
//Q群：164973950
//TEL：024-85718900

/******************************************************************************
 * Include files
 ******************************************************************************/
//Q群：164973950
//TEL：024-85718900
#include "lvd.h"
#include "gpio.h"

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
//Q群：164973950
//TEL：024-85718900
#define TEST_PORT       (2)
#define TEST_PIN        (6)

/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
//Q群：164973950
//TEL：024-85718900

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
//Q群：164973950
//TEL：024-85718900

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
//Q群：164973950
//TEL：024-85718900

/******************************************************************************
 * Local variable definitions ('static')                                      *
 ******************************************************************************/
//Q群：164973950
//TEL：024-85718900
static uint32_t gu32Cnt = 0;

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
//Q群：164973950
//TEL：024-85718900

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
//Q群：164973950
//TEL：024-85718900

void LvdIrqCallback(void)
{
    boolean_t bPortVal;

    gu32Cnt++;

    Lvd_DisableIrq();

    // 翻转测试口输出电平
    bPortVal = Gpio_GetIO(TEST_PORT, TEST_PIN);
    Gpio_SetIO(TEST_PORT, TEST_PIN, bPortVal^1u);
}


/**
 ******************************************************************************
 ** \brief  Main function of project
 **
 ** \return uint32_t return value, if needed
 **
 ** This sample
 **
 ******************************************************************************/
//Q群：164973950
//TEL：024-85718900
int main(void)
{
    stc_lvd_config_t stcLvdCfg;

    DDL_ZERO_STRUCT(stcLvdCfg);//变量清0

    if (Ok != Clk_SetPeripheralGate(ClkPeripheralGpio, TRUE))//开GPIO时钟
    {
        return 1;
    }
    if (Ok != Clk_SetPeripheralGate(ClkPeripheralVcLvd, TRUE))//开LVD时钟
    {
        return 1;
    }
    // Gpio_SetFunc_LVDOUT_P25();
    // Gpio_SetFunc_LVDOUT_P15();
    //配置测试IO口
    Gpio_InitIO(TEST_PORT, TEST_PIN, GpioDirOut);
    Gpio_SetIO(TEST_PORT, TEST_PIN, FALSE);

    //配置LVD输入口为模拟端口
    Gpio_SetAnalog(2, 5, TRUE);
    //Gpio_SetAnalog(2, 3, TRUE);
    // Gpio_SetAnalog(0, 3, TRUE);

    stcLvdCfg.bLvdReset = FALSE;//配置中断或者RESET功能
    stcLvdCfg.enInput = LvdInputP25;//配置LVD输入口
    stcLvdCfg.enThreshold = LvdTH2p6V;//配置LVD基准电压
    stcLvdCfg.bFilter = TRUE;
    stcLvdCfg.enFilterTime = LvdFilter29ms;
    stcLvdCfg.enIrqType = LvdIrqRise;
    stcLvdCfg.pfnIrqCbk = LvdIrqCallback;

    Lvd_Init(&stcLvdCfg);
    Lvd_EnableIrq(stcLvdCfg.enIrqType);
    delay1ms(1);
    Lvd_Enable();//LVD使能

    while (1)
    {
        if (gu32Cnt > 0)
        {
            gu32Cnt = 0;
            Lvd_EnableIrq(stcLvdCfg.enIrqType);//LVD中断使能
        }
    }
}

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
//Q群：164973950
//TEL：024-85718900



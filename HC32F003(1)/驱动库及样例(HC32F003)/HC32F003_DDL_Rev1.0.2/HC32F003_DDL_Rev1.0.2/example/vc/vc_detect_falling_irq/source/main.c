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
#include "vc.h"
#include "adc.h"
#include "gpio.h"

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
//Q群：164973950
//TEL：024-85718900
#define TEST_PORT           (2)
#define TEST_PIN            (6)

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
static en_vc_channel_t genChannel;

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

 void VcIrqCallback(void)
{
    boolean_t bPortVal;

    Vc_DisableIrq(genChannel);

    bPortVal = Gpio_GetIO(TEST_PORT, TEST_PIN);
    Gpio_SetIO(TEST_PORT, TEST_PIN, bPortVal^1u);
    gu32Cnt++;
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
    stc_vc_general_config_t stcVcGeneralCfg;
    stc_vc_channel_config_t stcVcChannelCfg;

    //变量清0
    DDL_ZERO_STRUCT(stcVcGeneralCfg);
    DDL_ZERO_STRUCT(stcVcChannelCfg);

    if (Ok != Clk_SetPeripheralGate(ClkPeripheralGpio, TRUE))//开启GPIO时钟
    {
        return 1;
    }
    if (Ok != Clk_SetPeripheralGate(ClkPeripheralVcLvd, TRUE))//开启VC时钟
    {
        return 1;
    }

    //配置测试IO口
    Gpio_InitIO(TEST_PORT, TEST_PIN, GpioDirOut);
    Gpio_SetIO(TEST_PORT, TEST_PIN, FALSE);

    Clk_SetPeripheralGate(ClkPeripheralAdcBgr, TRUE);//配置ADC时钟
    
    M0P_BGR->CR_f.BGR_EN = 0x1u;//必须使能
    M0P_BGR->CR_f.TS_EN = 0x1u;
    delay100us(1);

    //Gpio_SetFunc_VC0_OUT_P03();
    // Gpio_SetFunc_VC0_OUT_P31();   // SWCLK
    //Gpio_SetFunc_VC1_OUT_P24();
    Gpio_SetFunc_VC1_OUT_P32();//配置VC输出口


    //配置IO为模拟IO口
    Gpio_SetAnalog(3, 4, TRUE);
    Gpio_SetAnalog(3, 5, TRUE);
    Gpio_SetAnalog(3, 6, TRUE);
    //Gpio_SetAnalog(0, 1, TRUE);
    Gpio_SetAnalog(2, 3, TRUE);
    Gpio_SetAnalog(2, 5, TRUE);
    //Gpio_SetAnalog(3, 2, TRUE);
    Gpio_SetAnalog(3, 3, TRUE);

    // Adc_SetVref(RefVolSelInBgr2p5);
    
    
    // genChannel = VcChannel0;
    genChannel = VcChannel1;//配置VC输入通道

    stcVcGeneralCfg.bDivEn = FALSE;//6位DAC不使能
    // stcVcGeneralCfg.enDivVref = VcDivVrefAdc;
    stcVcGeneralCfg.enDivVref = VcDivVrefAvcc;//分压的参考电压为VCC
    stcVcGeneralCfg.u8DivVal = 0x3F;//分压值为1

    stcVcChannelCfg.enVcChannel = genChannel;//VC通道设置
    stcVcChannelCfg.enVcCmpDly = VcDelayoff;//迟滞配置
    stcVcChannelCfg.enVcBiasCurrent = VcBias300na;
    stcVcChannelCfg.enVcFilterTime = VcFilter28800us;
    stcVcChannelCfg.enVcInPin_P = VcInPCh0;
    stcVcChannelCfg.enVcInPin_N = AiBg1p2;
//    stcVcChannelCfg.enVcInPin_N = VcInNCh4;
    stcVcChannelCfg.enVcOutConfig = VcOutDisable;
    stcVcChannelCfg.enVcIrqSel = VcIrqFall;
    stcVcChannelCfg.pfnAnalogCmpCb = VcIrqCallback;

    Vc_GeneralInit(&stcVcGeneralCfg);

    Vc_ChannelInit(genChannel, &stcVcChannelCfg);
    
    Vc_EnableFilter(genChannel);

    if (Ok != Vc_ConfigIrq(stcVcChannelCfg.enVcChannel, stcVcChannelCfg.enVcIrqSel))
    {
        return 1;
    }

    if (Ok != Vc_EnableIrq(stcVcChannelCfg.enVcChannel))
    {
        return 1;
    }

    if (Ok != Vc_EnableChannel(stcVcChannelCfg.enVcChannel))
    {
        return 1;
    }

    while (1)
    {
        if (gu32Cnt > 0)
        {
            gu32Cnt = 0;
            Vc_EnableIrq(stcVcChannelCfg.enVcChannel);
        }
    }
}

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
//Q群：164973950
//TEL：024-85718900



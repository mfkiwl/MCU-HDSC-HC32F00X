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
 **   - 2019-04-19   Husj    First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "adt.h"
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
uint16_t u16ADTIM5CntValue;
uint16_t u16Capture;

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
void Tim5_IRQHandler(void)
{
    //????????????A / ????????????A
    if(TRUE == Adt_GetIrqFlag(M0P_ADTIM5, AdtCMAIrq))
    {
        u16ADTIM5CntValue = Adt_GetCount(M0P_ADTIM5);
        Adt_GetCaptureValue(M0P_ADTIM5, AdtCHxA, &u16Capture);
        Adt_ClearIrqFlag(M0P_ADTIM5, AdtCMAIrq);
    }
    
    //????????????B / ????????????B
    if(TRUE == Adt_GetIrqFlag(M0P_ADTIM5, AdtCMBIrq))
    {
        u16ADTIM5CntValue = Adt_GetCount(M0P_ADTIM5);
        Adt_GetCaptureValue(M0P_ADTIM5, AdtCHxB, &u16Capture);
        Adt_ClearIrqFlag(M0P_ADTIM5, AdtCMBIrq);
    }
    
    //????????????C
    if(TRUE == Adt_GetIrqFlag(M0P_ADTIM5, AdtCMCIrq))
    {
        u16ADTIM5CntValue = Adt_GetCount(M0P_ADTIM5);
        Adt_ClearIrqFlag(M0P_ADTIM5, AdtCMCIrq);
    }
    
    //????????????D
    if(TRUE == Adt_GetIrqFlag(M0P_ADTIM5, AdtCMDIrq))
    {
        u16ADTIM5CntValue = Adt_GetCount(M0P_ADTIM5);
        Adt_ClearIrqFlag(M0P_ADTIM5, AdtCMDIrq);
    }
    
    //????????????
    if(TRUE == Adt_GetIrqFlag(M0P_ADTIM5, AdtOVFIrq))
    {
        u16ADTIM5CntValue = Adt_GetCount(M0P_ADTIM5);
        Adt_ClearIrqFlag(M0P_ADTIM5, AdtOVFIrq);
    }
    
    //????????????
    if(TRUE == Adt_GetIrqFlag(M0P_ADTIM5, AdtUDFIrq))
    {
        u16ADTIM5CntValue = Adt_GetCount(M0P_ADTIM5);
        Adt_ClearIrqFlag(M0P_ADTIM5, AdtUDFIrq);
    }
    
    //????????????????????????
    if(TRUE == Adt_GetIrqFlag(M0P_ADTIM5, AdtDTEIrq))
    {
        Adt_StopCount(M0P_ADTIM5);
        Adt_ClearIrqFlag(M0P_ADTIM5, AdtDTEIrq);
    }
}

///< AdvTimer5 ??????????????????
void App_AdvTimerCmpIrq(void)
{
    uint16_t u16Period;
    en_adt_compare_t enAdtCompare;
    uint16_t u16Compare;
    
    stc_adt_basecnt_cfg_t     stcAdtBaseCntCfg;
    stc_adt_CHxX_port_cfg_t   stcAdtTIMACfg;
    stc_adt_CHxX_port_cfg_t   stcAdtTIMBCfg;
    stc_adt_port_trig_cfg_t   stcAdtPortTrig;
    stc_gpio_cfg_t            stcTIM5Port;
    
    DDL_ZERO_STRUCT(stcAdtBaseCntCfg);
    DDL_ZERO_STRUCT(stcAdtTIMACfg);
    DDL_ZERO_STRUCT(stcAdtTIMBCfg);
    DDL_ZERO_STRUCT(stcAdtPortTrig);
    DDL_ZERO_STRUCT(stcTIM5Port);
    
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);         //????????????????????????
    
    stcTIM5Port.enDir  = GpioDirOut;
    //P25?????????TIM5_CHA
    Gpio_Init(GpioPort2, GpioPin5, &stcTIM5Port);
    Gpio_SetAfMode(GpioPort2,GpioPin5,GpioAf3);
    
    //P26?????????TIM5_CHB
    Gpio_Init(GpioPort2, GpioPin6, &stcTIM5Port);
    Gpio_SetAfMode(GpioPort2,GpioPin6,GpioAf3);
    
    Sysctrl_SetPeripheralGate(SysctrlPeripheralAdvTim, TRUE);//ADT??????????????????
  
    stcAdtBaseCntCfg.enCntMode = AdtTriangleModeA;
    stcAdtBaseCntCfg.enCntDir = AdtCntUp;
    stcAdtBaseCntCfg.enCntClkDiv = AdtClkPClk0;
    Adt_Init(M0P_ADTIM5, &stcAdtBaseCntCfg);                      //ADT????????????????????????????????????
    
    
    stcAdtTIMACfg.enCap = AdtCHxCompareOutput;
    stcAdtTIMACfg.bOutEn = FALSE;
    stcAdtTIMBCfg.enCap = AdtCHxCompareOutput;
    stcAdtTIMBCfg.bOutEn = FALSE;
    Adt_CHxXPortCfg(M0P_ADTIM5, AdtCHxA, &stcAdtTIMACfg);        //TIM5_CHA????????????
    Adt_CHxXPortCfg(M0P_ADTIM5, AdtCHxB, &stcAdtTIMBCfg);        //TIM5_CHA????????????

    
    u16Period = 0xA000;
    Adt_SetPeriod(M0P_ADTIM5, u16Period);                           //????????????

    enAdtCompare = AdtCompareA;
    u16Compare = 0x1000;
    Adt_SetCompareValue(M0P_ADTIM5, enAdtCompare, u16Compare);      //??????????????????????????????A??????

    enAdtCompare = AdtCompareB;
    u16Compare = 0x3000;
    Adt_SetCompareValue(M0P_ADTIM5, enAdtCompare, u16Compare);       //??????????????????????????????B??????
    
    enAdtCompare = AdtCompareC;
    u16Compare = 0x5000;
    Adt_SetCompareValue(M0P_ADTIM5, enAdtCompare, u16Compare);       //??????????????????????????????C??????
    
    enAdtCompare = AdtCompareD;
    u16Compare = 0x7000;
    Adt_SetCompareValue(M0P_ADTIM5, enAdtCompare, u16Compare);       //??????????????????????????????D??????
    
    Adt_ClearAllIrqFlag(M0P_ADTIM5);
    Adt_CfgIrq(M0P_ADTIM5, AdtCMAIrq, TRUE);
    Adt_CfgIrq(M0P_ADTIM5, AdtCMBIrq, TRUE);
    Adt_CfgIrq(M0P_ADTIM5, AdtCMCIrq, TRUE);
    Adt_CfgIrq(M0P_ADTIM5, AdtCMDIrq, TRUE);  //??????????????????
    EnableNvic(ADTIM5_IRQn, IrqLevel3, TRUE);
    
    Adt_StartCount(M0P_ADTIM5);
    
    delay1ms(1000);
    
    Adt_StopCount(M0P_ADTIM5);
    Adt_ClearCount(M0P_ADTIM5);
    
    Adt_ClearAllIrqFlag(M0P_ADTIM5);
    Adt_CfgIrq(M0P_ADTIM5, AdtCMAIrq, FALSE);
    Adt_CfgIrq(M0P_ADTIM5, AdtCMBIrq, FALSE);
    Adt_CfgIrq(M0P_ADTIM5, AdtCMCIrq, FALSE);
    Adt_CfgIrq(M0P_ADTIM5, AdtCMDIrq, FALSE); //??????????????????
    EnableNvic(ADTIM5_IRQn, IrqLevel3, FALSE);

}

///< AdvTimer5 ??????????????????
void App_AdvTimerCapIrq(void)
{
    stc_adt_basecnt_cfg_t     stcAdtBaseCntCfg;
    stc_adt_port_trig_cfg_t   stcAdtPortTrig;
    stc_gpio_cfg_t            stcTIM5Port;
    stc_gpio_cfg_t            stcTRIBPort;
    stc_gpio_cfg_t            stcOutPort;
    
    DDL_ZERO_STRUCT(stcAdtBaseCntCfg);
    DDL_ZERO_STRUCT(stcAdtPortTrig);
    DDL_ZERO_STRUCT(stcTIM5Port);
    DDL_ZERO_STRUCT(stcTRIBPort);
    DDL_ZERO_STRUCT(stcOutPort);
    
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);         //????????????????????????
    
    stcTIM5Port.enDir  = GpioDirOut;
    //P25?????????TIM5_CHA
    Gpio_Init(GpioPort2, GpioPin5, &stcTIM5Port);
    Gpio_SetAfMode(GpioPort2,GpioPin5,GpioAf3);
    
    //P26?????????TIM5_CHB
    Gpio_Init(GpioPort2, GpioPin6, &stcTIM5Port);
    Gpio_SetAfMode(GpioPort2,GpioPin6,GpioAf3);
    
    Sysctrl_SetPeripheralGate(SysctrlPeripheralAdvTim, TRUE);//ADT??????????????????

    
    stcAdtBaseCntCfg.enCntMode = AdtTriangleModeA;
    stcAdtBaseCntCfg.enCntDir = AdtCntUp;
    stcAdtBaseCntCfg.enCntClkDiv = AdtClkPClk0;
    Adt_Init(M0P_ADTIM5, &stcAdtBaseCntCfg);                      //ADT????????????????????????????????????
    
    
    // P03 -> P34 Rise -> Time TrigB Rise -> HW Capture A
    // P03 -> P34 Fall -> Time TrigB Fall -> HW Capture B
        
    //PB11?????????ADT TRIB ??????
    stcTRIBPort.enDir  = GpioDirIn;
    Gpio_Init(GpioPort3, GpioPin4, &stcTRIBPort);

    
    //PB14????????????????????????
    stcOutPort.enDir  = GpioDirOut;
    Gpio_Init(GpioPort0, GpioPin3, &stcOutPort);

    Gpio_WriteOutputIO(GpioPort0, GpioPin3, FALSE);                //P03?????????
    
    stcAdtPortTrig.enTrigSrc = AdtTrigxSelP34;                     //P34??????TRIB??????
    stcAdtPortTrig.bFltEn = TRUE;                                   //??????????????????
    stcAdtPortTrig.enFltClk = AdtFltClkPclk0Div16;                  //????????????
    Adt_PortTrigCfg(AdtTrigB, &stcAdtPortTrig);                     //??????????????????
    
    Adt_CfgHwCaptureA(M0P_ADTIM5, AdtHwTrigTimTriBRise);             //????????????A????????????TRIB?????????????????????
    Adt_CfgHwCaptureB(M0P_ADTIM5, AdtHwTrigTimTriBFall);             //????????????B????????????TRIB?????????????????????
    
    Adt_ClearAllIrqFlag(M0P_ADTIM5);
    Adt_CfgIrq(M0P_ADTIM5, AdtCMAIrq, TRUE);
    Adt_CfgIrq(M0P_ADTIM5, AdtCMBIrq, TRUE);  //??????????????????
    EnableNvic(ADTIM5_IRQn, IrqLevel3, TRUE);
    
    Adt_StartCount(M0P_ADTIM5);
    
    delay1ms(1000);
    Gpio_WriteOutputIO(GpioPort0, GpioPin3, TRUE);     //P03?????????
    delay1ms(1000);
    Gpio_WriteOutputIO(GpioPort0, GpioPin3, FALSE);     //P03?????????
    delay1ms(1000);
    
    Adt_ClearHwCaptureA(M0P_ADTIM5);
    Adt_ClearHwCaptureB(M0P_ADTIM5);
    Adt_StopCount(M0P_ADTIM5);
    Adt_ClearCount(M0P_ADTIM5);

    Adt_ClearAllIrqFlag(M0P_ADTIM5);
    Adt_CfgIrq(M0P_ADTIM5, AdtCMAIrq, FALSE);
    Adt_CfgIrq(M0P_ADTIM5, AdtCMBIrq, FALSE);//??????????????????
    EnableNvic(ADTIM5_IRQn, IrqLevel3, FALSE);
}


///< AdvTimer5 ????????????????????????
void App_AdvTimerOvfUdfIrq(void)
{
    uint16_t u16Period;
    
    stc_adt_basecnt_cfg_t     stcAdtBaseCntCfg;
    stc_adt_port_trig_cfg_t   stcAdtPortTrig;
    stc_gpio_cfg_t            stcTIM5Port;
    
    DDL_ZERO_STRUCT(stcAdtBaseCntCfg);
    DDL_ZERO_STRUCT(stcAdtPortTrig);
    DDL_ZERO_STRUCT(stcTIM5Port);
    
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);         //????????????????????????
    
    stcTIM5Port.enDir  = GpioDirOut;
    //P25?????????TIM5_CHA
    Gpio_Init(GpioPort2, GpioPin5, &stcTIM5Port);
    Gpio_SetAfMode(GpioPort2,GpioPin5,GpioAf3);
    
    //P26?????????TIM5_CHB
    Gpio_Init(GpioPort2, GpioPin6, &stcTIM5Port);
    Gpio_SetAfMode(GpioPort2,GpioPin6,GpioAf3);
    
    Sysctrl_SetPeripheralGate(SysctrlPeripheralAdvTim, TRUE);//ADT??????????????????

    
    stcAdtBaseCntCfg.enCntMode = AdtTriangleModeA;
    stcAdtBaseCntCfg.enCntDir = AdtCntUp;
    stcAdtBaseCntCfg.enCntClkDiv = AdtClkPClk0;
    Adt_Init(M0P_ADTIM5, &stcAdtBaseCntCfg);                      //ADT????????????????????????????????????

    
    u16Period = 0xA000;
    Adt_SetPeriod(M0P_ADTIM5, u16Period);                           //????????????

    Adt_ClearAllIrqFlag(M0P_ADTIM5);
    Adt_CfgIrq(M0P_ADTIM5, AdtOVFIrq, TRUE);//??????????????????
    Adt_CfgIrq(M0P_ADTIM5, AdtUDFIrq, TRUE);//??????????????????
    EnableNvic(ADTIM5_IRQn, IrqLevel3, TRUE);
    
    Adt_StartCount(M0P_ADTIM5);
    
    delay1ms(2000);

    Adt_StopCount(M0P_ADTIM5);
    Adt_ClearCount(M0P_ADTIM5);
    
    Adt_ClearAllIrqFlag(M0P_ADTIM5);
    Adt_CfgIrq(M0P_ADTIM5, AdtOVFIrq, FALSE);//??????????????????
    Adt_CfgIrq(M0P_ADTIM5, AdtUDFIrq, FALSE);//??????????????????
    EnableNvic(ADTIM5_IRQn, IrqLevel3, FALSE);

}


///< AdvTimer5 ??????????????????????????????
void App_AdvTimerDeadTimeErrIrq(void)
{
    uint16_t u16Period;
    en_adt_compare_t enAdtCompare;
    uint16_t u16Compare;
    
    stc_adt_basecnt_cfg_t     stcAdtBaseCntCfg;
    stc_adt_CHxX_port_cfg_t   stcAdtTIMACfg;
    stc_adt_CHxX_port_cfg_t   stcAdtTIMBCfg;
    stc_adt_port_trig_cfg_t   stcAdtPortTrig;
    stc_gpio_cfg_t            stcTIM5Port;
    
    DDL_ZERO_STRUCT(stcAdtBaseCntCfg);
    DDL_ZERO_STRUCT(stcAdtTIMACfg);
    DDL_ZERO_STRUCT(stcAdtTIMBCfg);
    DDL_ZERO_STRUCT(stcAdtPortTrig);
    DDL_ZERO_STRUCT(stcTIM5Port);
    
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);         //????????????????????????
    
    stcTIM5Port.enDir  = GpioDirOut;
    //P25?????????TIM5_CHA
    Gpio_Init(GpioPort2, GpioPin5, &stcTIM5Port);
    Gpio_SetAfMode(GpioPort2,GpioPin5,GpioAf3);
    
    //P25?????????TIM5_CHB
    Gpio_Init(GpioPort2, GpioPin6, &stcTIM5Port);
    Gpio_SetAfMode(GpioPort2,GpioPin6,GpioAf3);
    
    Sysctrl_SetPeripheralGate(SysctrlPeripheralAdvTim, TRUE);//ADT??????????????????

    
    stcAdtBaseCntCfg.enCntMode = AdtTriangleModeA;
    stcAdtBaseCntCfg.enCntDir = AdtCntUp;
    stcAdtBaseCntCfg.enCntClkDiv = AdtClkPClk0;
    Adt_Init(M0P_ADTIM5, &stcAdtBaseCntCfg);                      //ADT????????????????????????????????????
    
    u16Period = 0xA000;
    Adt_SetPeriod(M0P_ADTIM5, u16Period);                           //????????????

    enAdtCompare = AdtCompareA;
    u16Compare = 0x5000;
    Adt_SetCompareValue(M0P_ADTIM5, enAdtCompare, u16Compare);      //??????????????????????????????A??????
    
    enAdtCompare = AdtCompareC;
    u16Compare = 0x5000;
    Adt_SetCompareValue(M0P_ADTIM5, enAdtCompare, u16Compare);       //??????????????????????????????C??????
    
    
    stcAdtTIMBCfg.enCap = AdtCHxCompareOutput;
    stcAdtTIMBCfg.bOutEn = TRUE;
    stcAdtTIMBCfg.enPerc = AdtCHxPeriodKeep;
    stcAdtTIMBCfg.enCmpc = AdtCHxCompareInv;
    stcAdtTIMBCfg.enStaStp = AdtCHxStateSelSS;
    stcAdtTIMBCfg.enStaOut = AdtCHxPortOutHigh;
    Adt_CHxXPortCfg(M0P_ADTIM5, AdtCHxB, &stcAdtTIMBCfg);  //CHxB????????????
    
    Adt_SetDTUA(M0P_ADTIM5, 0x6666);
    Adt_SetDTDA(M0P_ADTIM5, 0x6666);
    Adt_CfgDT(M0P_ADTIM5, TRUE, TRUE);                     //??????????????????
    
    Adt_ClearAllIrqFlag(M0P_ADTIM5);
    Adt_CfgIrq(M0P_ADTIM5, AdtDTEIrq, TRUE);               //??????????????????
    EnableNvic(ADTIM5_IRQn, IrqLevel3, TRUE);
    
    Adt_StartCount(M0P_ADTIM5);
    
    delay1ms(1000);
    
    Adt_ClearAllIrqFlag(M0P_ADTIM5);
    Adt_CfgIrq(M0P_ADTIM5, AdtDTEIrq, FALSE);              //??????????????????
    EnableNvic(ADTIM5_IRQn, IrqLevel3, FALSE);
    Adt_CfgDT(M0P_ADTIM5, FALSE, FALSE);
    
    Adt_StopCount(M0P_ADTIM5);
    Adt_ClearCount(M0P_ADTIM5);
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
int32_t main(void)
{

    /******************************??????????????????********************************/
    App_AdvTimerCmpIrq();
    
    /*******************************??????????????????*******************************/
    //App_AdvTimerCapIrq();
    
    /***************************?????????????????????**********************************/
    //App_AdvTimerOvfUdfIrq();
    
    /****************************??????????????????????????????****************************/
    //App_AdvTimerDeadTimeErrIrq();

    

    while(1);
}

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/



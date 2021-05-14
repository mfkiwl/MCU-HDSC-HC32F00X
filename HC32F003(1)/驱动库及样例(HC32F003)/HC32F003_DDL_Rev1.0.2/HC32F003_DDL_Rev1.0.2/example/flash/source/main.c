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
 **   - 2016-02-16  1.0  XYZ First version for Device Driver Library of Module.
 **
 ******************************************************************************/
//Q群：164973950
//TEL：024-85718900

/******************************************************************************
 * Include files
 ******************************************************************************/
//Q群：164973950
//TEL：024-85718900
#include "ddl.h"
#include "flash.h"

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
//Q群：164973950
//TEL：024-85718900
//#define RUN_IN_RAM 1    //need to config *.icf

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

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
//Q群：164973950
//TEL：024-85718900
static volatile uint32_t u32FlashTestFlag   = 0;
/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
//Q群：164973950
//TEL：024-85718900


/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
//Q群：164973950
//TEL：024-85718900

/*******************************************************************************
 * FLASH 中断服务函数
 ******************************************************************************/
//Q群：164973950
//TEL：024-85718900
 void FlashInt(void)
 {
    if (TRUE == Flash_GetIntFlag(flash_int0))
    {
        Flash_ClearIntFlag(flash_int0);
        u32FlashTestFlag |= 0x01;
        Flash_DisableIrq(flash_int0);
    }
    if (TRUE == Flash_GetIntFlag(flash_int1))
    {
        Flash_ClearIntFlag(flash_int1);
        u32FlashTestFlag |= 0x02;
        Flash_DisableIrq(flash_int1);
    }
      
 }
   
   
/*******************************************************************************
 * FLASH 编程测试
 ******************************************************************************/
//Q群：164973950
//TEL：024-85718900
en_result_t FlashWriteTest(void)
{
    en_result_t       enResult = Error;
    uint32_t          u32Addr  = 0x3ff0;
    uint8_t           u8Data   = 0x5a;
    uint16_t          u16Data  = 0x5a5a;
    uint32_t          u32Data  = 0x5a5a5a5a;

    Flash_Init(FlashInt, 0);
    
    Flash_SectorErase(u32Addr);
    
    enResult = Flash_WriteByte(u32Addr, u8Data);
    if (Ok == enResult)
    {
        if(*((volatile uint8_t*)u32Addr) == u8Data)
        {
            enResult = Ok;
        }
        else
        {
            return enResult;
        }
    }
    else
    {
        enResult = Error;
        return enResult;
    }  

    u32Addr += 2;
    enResult = Flash_WriteHalfWord(u32Addr, u16Data);
    if (Ok == enResult)
    {
        if(*((volatile uint16_t*)u32Addr) == u16Data)
        {
            enResult = Ok;
        }
        else
        {
            return enResult;
        }
    }
    else
    {
        return enResult;
    }

    u32Addr += 2;
    enResult = Flash_WriteWord(u32Addr, u32Data);
    if (Ok == enResult)
    {
        if(*((volatile uint32_t*)u32Addr) == u32Data)
        {
            enResult = Ok;
        }
        else
        {
            return enResult;
        }
    }
    else
    {
        return enResult;
    }  
    
    return enResult;
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

int32_t main(void)
{
    volatile uint8_t u8TestFlag = 0;
    
    if(Ok != FlashWriteTest())
    {
        u8TestFlag |= 0x01;
    }   
    
    while (1);
}

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
//Q群：164973950
//TEL：024-85718900



//************************************************************
//  Copyright (c) 合肥市新定义电子有限公司
//	文件名称: 		rd8_option.h
//	作者:					新定义应用团队
//	模块功能: 		Customer Option寄存器配置头文件
//  最后更正日期: 2022年5月20日
// 	版本: 				V1.000
//  说明:该文件仅适用于RD8系列芯片
//*************************************************************

#ifndef _rd8_OPTION_H_
#define _rd8_OPTION_H_

#include "rd8.h"

//系统时钟分频枚举
typedef enum
{
  SYSCLK_PRESSEL_FOSC_D1 = (uint8_t)0x00, //预分频 Fsys = Fosc/1
  SYSCLK_PRESSEL_FOSC_D2 = (uint8_t)0x10, //预分频 Fsys = Fosc/2
  SYSCLK_PRESSEL_FOSC_D4 = (uint8_t)0x20, //预分频 Fsys = Fosc/4
  SYSCLK_PRESSEL_FOSC_D8 = (uint8_t)0x30  //预分频 Fsys = Fosc/8
} SYSCLK_PresSel_TypeDef;

//低电压复位挡位选择
typedef enum
{
  LVR_INVALID = (uint8_t)0x04, //LVR无效
  LVR_1_9V = (uint8_t)0x00,    //LVR 1.9V复位
  LVR_2_9V = (uint8_t)0x01,    //LVR 2.9V复位
  LVR_3_7V = (uint8_t)0x02,    //LVR 3.7V复位
  LVR_4_3V = (uint8_t)0x03     //LVR 4.3V复位
} LVR_Config_TypeDef;

//IAP操作复位枚举
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
typedef enum
{
  IAP_OPERATERANGE__LAST_0K_CODEREGION = (uint8_t)0x00, //不允许进行IAP操作
  IAP_OPERATERANGE__LAST_1K_CODEREGION = (uint8_t)0x04, //允许ROM最后1k进行IAP操作
  IAP_OPERATERANGE__LAST_2K_CODEREGION = (uint8_t)0x08, //允许ROM最后2k进行IAP操作
  IAP_OPERATERANGE__ALL_CODEREGION = (uint8_t)0x0c      //允许ROM所有区域进行IAP操作
} IAP_OperateRange_TypeDef;
#endif
#if defined(RD8G403)
typedef enum
{
  IAP_OPERATERANGE_ONLY_EEPROM 		    = (uint8_t)0x00,	//只允许EEPROM进行IAP操作
  IAP_OPERATERANGE__LAST_0_5K_CODEREGION  = (uint8_t)0x04,	//允许ROM最后0.5k和EEPROM进行IAP操作
  IAP_OPERATERANGE__LAST_1K_CODEREGION    = (uint8_t)0x08,	//允许ROM最后1k和EEPROM进行IAP操作
  IAP_OPERATERANGE__ALL_CODEREGION 	    = (uint8_t)0x0c		//允许ROM和EEPROM所有区域进行IAP操作
} IAP_OperateRange_TypeDef;
#endif

#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x)
/* ADC参考电压挡位枚举 */
typedef enum
{
  ADC_VREF_VDD = 0x00,    //VDD做参考ADC电压
  ADC_VREF_2_048V = 0x40,	//内部2.048V做ADC参考电压
  ADC_VREF_1_024V = 0x80, //内部1.024V做ADC参考电压
  ADC_VREF_2_4V = 0xC0  	//内部2.4V做ADC参考电压
} ADC_Vref_TypeDef;
#endif 
#if defined(RD8G403)
typedef enum
{
  ADC_VREF_VDD  = 0x00,					//选择VDD做ADC参考电压
  ADC_VREF_2_4V = 0x80,   			//选择内部2.4V做ADC参考电压
} ADC_Vref_TypeDef;
#endif

#if defined(RD8G05x) || defined(RD8T05x)
/* ADC参考电压挡位枚举 */
typedef enum
{
  ADC_VREF_VDD  = 0x00,					//选择VDD做ADC参考电压
  ADC_VREF_1_024V = 0x40,   		//选择内部1.024V做ADC参考电压
  ADC_VREF_2_4V = 0x80,   			//选择内部2.4V做ADC参考电压
  ADC_VREF_2_048V = 0xC0,				//选择内部2.048V做ADC参考电压
} ADC_Vref_TypeDef;
#endif

void OPTION_WDT_Cmd(FunctionalState NewState);
void OPTION_XTIPLL_Cmd(FunctionalState NewState);
void OPTION_SYSCLK_Init(SYSCLK_PresSel_TypeDef SYSCLK_PresSel);
void OPTION_LVR_Init(LVR_Config_TypeDef LVR_Config);
void OPTION_ADC_VrefConfig(ADC_Vref_TypeDef ADC_Vref);
void OPTION_IAP_SetOperateRange(IAP_OperateRange_TypeDef IAP_OperateRange);
void OPTION_JTG_Cmd(FunctionalState NewState);

#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
#else
void OPTION_RST_PIN_Cmd(FunctionalState NewState);
#endif

#endif
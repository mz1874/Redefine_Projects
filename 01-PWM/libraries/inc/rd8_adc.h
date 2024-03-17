//************************************************************
//  Copyright (c) 合肥市新定义电子有限公司
//	文件名称: 		rd8_adc.h
//	作者:					新定义应用团队
//	模块功能: 		BTM固件库函数C文件
//  最后更正日期: 2022年5月17日
// 	版本: 				V1.000
//  说明: 
//*************************************************************

#ifndef _rd8_ADC_H_
#define _rd8_ADC_H_

#include "rd8.h"
//说明:ADC参考电源枚举定义在option.h，使用ADC请注意将该文件导入
#include "rd8_option.h"

#if defined (RD8G403)
/* ADC采样时钟分频枚举 */
typedef enum
{
  ADC_PRESSEL_FHRC_D32 = (uint8_t)0x00, //预分频 fADC = fHRC/32
  ADC_PRESSEL_FHRC_D24 = (uint8_t)0x01, //预分频 fADC = fHRC/24
  ADC_PRESSEL_FHRC_D16 = (uint8_t)0x02, //预分频 fADC = fHRC/16
  ADC_PRESSEL_FHRC_D12 = (uint8_t)0x03, //预分频 fADC = fHRC/12
  ADC_PRESSEL_FHRC_D8 = (uint8_t)0x04,  //预分频 fADC = fHRC/8
  ADC_PRESSEL_FHRC_D6 = (uint8_t)0x05,  //预分频 fADC = fHRC/6
  ADC_PRESSEL_FHRC_D4 = (uint8_t)0x06,  //预分频 fADC = fHRC/4
  ADC_PRESSEL_FHRC_D3 = (uint8_t)0x07   //预分频 fADC = fHRC/3
} ADC_PresSel_TypeDef;

//ADC采样周期选择枚举
typedef enum
{
  ADC_Cycle_6Cycle = (uint8_t)0x00, //ADC采样时间为6个ADC采样时钟周期
  ADC_Cycle_36Cycle = (uint8_t)0x08 //ADC采样时间为36个ADC采样时钟周期
} ADC_Cycle_TypeDef;
#else
/* ADC采样时钟分频枚举 */
typedef enum
{
  ADC_PRESSEL_3CLOCK = (uint8_t)0x10,  //采样时间为3个系统时钟
  ADC_PRESSEL_6CLOCK = (uint8_t)0x14,  //采样时间为6个系统时钟
  ADC_PRESSEL_16CLOCK = (uint8_t)0x18, //采样时间为16个系统时钟
  ADC_PRESSEL_32CLOCK = (uint8_t)0x1c  //采样时间为32个系统时钟
} ADC_PresSel_TypeDef;

//ADC采样周期选择枚举
typedef enum
{
  ADC_Cycle_Null = 0x00 //该功能无效
} ADC_Cycle_TypeDef;
#endif

#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x)
//ADC采样通道选择
typedef enum
{
  ADC_CHANNEL_0 = (uint8_t)0x00,     //选择AIN0做AD输入口
  ADC_CHANNEL_1 = (uint8_t)0x01,     //选择AIN1做AD输入口
  ADC_CHANNEL_2 = (uint8_t)0x02,     //选择AIN2做AD输入口
  ADC_CHANNEL_3 = (uint8_t)0x03,     //选择AIN3做AD输入口
  ADC_CHANNEL_4 = (uint8_t)0x04,     //选择AIN4做AD输入口
  ADC_CHANNEL_5 = (uint8_t)0x05,     //选择AIN5做AD输入口
  ADC_CHANNEL_6 = (uint8_t)0x06,     //选择AIN6做AD输入口
  ADC_CHANNEL_7 = (uint8_t)0x07,     //选择AIN7做AD输入口
  ADC_CHANNEL_8 = (uint8_t)0x08,     //选择AIN8做AD输入口
  ADC_CHANNEL_9 = (uint8_t)0x09,     //选择AIN9做AD输入口
  ADC_CHANNEL_10 = (uint8_t)0x0A,    //选择AIN10做AD输入口
  ADC_CHANNEL_11 = (uint8_t)0x0B,    //选择AIN11做AD输入口
  ADC_CHANNEL_12 = (uint8_t)0x0C,    //选择AIN12做AD输入口
  ADC_CHANNEL_13 = (uint8_t)0x0D,    //选择AIN13做AD输入口
  ADC_CHANNEL_14 = (uint8_t)0x0E,    //选择AIN14做AD输入口
  ADC_CHANNEL_15 = (uint8_t)0x0F,    //选择AIN15做AD输入口
  ADC_CHANNEL_VDD_D4 = (uint8_t)0x1f //选择内部1/4VDD做AD输入口
} ADC_Channel_TypeDef;

//ADC采样通道使能枚举
typedef enum
{
  ADC_EAIN_0 = (uint16_t)0x0001,  //选择AIN0
  ADC_EAIN_1 = (uint16_t)0x0002,  //选择AIN1
  ADC_EAIN_2 = (uint16_t)0x0004,  //选择AIN2
  ADC_EAIN_3 = (uint16_t)0x0008,  //选择AIN3
  ADC_EAIN_4 = (uint16_t)0x0010,  //选择AIN4
  ADC_EAIN_5 = (uint16_t)0x0020,  //选择AIN5
  ADC_EAIN_6 = (uint16_t)0x0040,  //选择AIN6
  ADC_EAIN_7 = (uint16_t)0x0080,  //选择AIN7
  ADC_EAIN_8 = (uint16_t)0x0100,  //选择AIN8
  ADC_EAIN_9 = (uint16_t)0x0200,  //选择AIN9
  ADC_EAIN_10 = (uint16_t)0x0400, //选择AIN10
  ADC_EAIN_11 = (uint16_t)0x0800, //选择AIN11
  ADC_EAIN_12 = (uint16_t)0x1000, //选择AIN12
  ADC_EAIN_13 = (uint16_t)0x2000, //选择AIN13
  ADC_EAIN_14 = (uint16_t)0x4000, //选择AIN14
  ADC_EAIN_15 = (uint16_t)0x8000  //选择AIN15
} ADC_EAIN_TypeDef;
#endif
#if defined(RD8G05x) || defined(RD8T05x)
typedef enum
{
  ADC_CHANNEL_0 = (uint8_t)0x00,     //选择AIN0做AD输入口
  ADC_CHANNEL_1 = (uint8_t)0x01,     //选择AIN1做AD输入口
  ADC_CHANNEL_2 = (uint8_t)0x02,     //选择AIN2做AD输入口
  ADC_CHANNEL_3 = (uint8_t)0x03,     //选择AIN3做AD输入口
  ADC_CHANNEL_4 = (uint8_t)0x04,     //选择AIN4做AD输入口
  ADC_CHANNEL_5 = (uint8_t)0x05,     //选择AIN5做AD输入口
  ADC_CHANNEL_6 = (uint8_t)0x06,     //选择AIN6做AD输入口
  ADC_CHANNEL_7 = (uint8_t)0x07,     //选择AIN7做AD输入口
  ADC_CHANNEL_8 = (uint8_t)0x08,     //选择AIN8做AD输入口
  ADC_CHANNEL_9 = (uint8_t)0x09,     //选择AIN9做AD输入口
  ADC_CHANNEL_VDD_D4 = (uint8_t)0x1f //选择内部1/4VDD做AD输入口
} ADC_Channel_TypeDef;

typedef enum
{
  ADC_EAIN_0 = (uint16_t)0x0001, //选择AIN0
  ADC_EAIN_1 = (uint16_t)0x0002, //选择AIN1
  ADC_EAIN_2 = (uint16_t)0x0004, //选择AIN2
  ADC_EAIN_3 = (uint16_t)0x0008, //选择AIN3
  ADC_EAIN_4 = (uint16_t)0x0010, //选择AIN4
  ADC_EAIN_5 = (uint16_t)0x0020, //选择AIN5
  ADC_EAIN_6 = (uint16_t)0x0040, //选择AIN6
  ADC_EAIN_7 = (uint16_t)0x0080, //选择AIN7
  ADC_EAIN_8 = (uint16_t)0x0100, //选择AIN8
  ADC_EAIN_9 = (uint16_t)0x0200, //选择AIN9
} ADC_EAIN_TypeDef;
#endif

#if defined(RD8G403)
typedef enum
{
  ADC_CHANNEL_0 = (uint8_t)0x00,     //选择AIN0做AD输入口
  ADC_CHANNEL_1 = (uint8_t)0x01,     //选择AIN1做AD输入口
  ADC_CHANNEL_2 = (uint8_t)0x02,     //选择AIN2做AD输入口
  ADC_CHANNEL_3 = (uint8_t)0x03,     //选择AIN3做AD输入口
  ADC_CHANNEL_4 = (uint8_t)0x04,     //选择AIN4做AD输入口
  ADC_CHANNEL_5 = (uint8_t)0x05,     //选择AIN5做AD输入口
  ADC_CHANNEL_6 = (uint8_t)0x06,     //选择AIN6做AD输入口
  ADC_CHANNEL_VDD_D4 = (uint8_t)0x1f //选择内部1/4VDD做AD输入口
} ADC_Channel_TypeDef;

typedef enum
{
  ADC_EAIN_0 = (uint16_t)0x0001, //选择AIN0
  ADC_EAIN_1 = (uint16_t)0x0002, //选择AIN1
  ADC_EAIN_2 = (uint16_t)0x0004, //选择AIN2
  ADC_EAIN_3 = (uint16_t)0x0008, //选择AIN3
  ADC_EAIN_4 = (uint16_t)0x0010, //选择AIN4
  ADC_EAIN_5 = (uint16_t)0x0020, //选择AIN5
  ADC_EAIN_6 = (uint16_t)0x0040  //选择AIN6
} ADC_EAIN_TypeDef;
#endif

//ADC转换平均值采样次数
typedef enum
{
  ADC_SamplesNum_FourTimes = 0x04,			//采样次数为4次
	ADC_SamplesNum_SixTimes = 0x06,				//采样次数为6次
	ADC_SamplesNum_EightTimes = 0x08,			//采样次数为8次
	ADC_SamplesNum_TenTimes = 0x0A,				//采样次数为10次
} ADC_SamplesNum_TypeDef;

/*******************************宏函数*******************************/
/*****************************************************
*函数名称:void ADC_StartConversion(void)
*函数功能:开始一次AD转换
*入口参数:void
*出口参数:void
*****************************************************/
#define ADC_StartConversion() SET_BIT(ADCCON,0X40)

/*****************************************************
*函数名称:void ADC_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*函数功能:ADC中断初始化
*入口参数:
FunctionalState:NewState:中断使能/关闭选择
PriorityStatus:Priority:中断优先级选择
*出口参数:void
*****************************************************/
#define ADC_ITConfig(NewState,Priority)										\
					do{  																						\
							EADC = (bit)NewState;												\
							IPADC = (bit)Priority;											\
					}while(0)

/*****************************************************
*函数名称:FlagStatus ADC_GetFlagStatus(void)
*函数功能:获得ADC中断标志状态
*入口参数:void
*出口参数:
FlagStatus:ADC中断标志状态
*****************************************************/
#define ADC_GetFlagStatus() ((READ_BIT(ADCCON,0x20)) ? (SET):(RESET))

/*****************************************************
*函数名称:void ADC_ClearFlag(void)
*函数功能:清除ADC中断标志状态
*入口参数:void
*出口参数:void
*****************************************************/
#define ADC_ClearFlag() CLEAR_BIT(ADCCON,0x20)

void ADC_DeInit(void);
void ADC_Init(ADC_PresSel_TypeDef ADC_PrescalerSelection, ADC_Cycle_TypeDef ADC_Cycle);
void ADC_ChannelConfig(ADC_Channel_TypeDef ADC_Channel, FunctionalState NewState);
void ADC_EAINConfig(uint16_t ADC_EAIN_Select, FunctionalState NewState);
void ADC_Cmd(FunctionalState NewState);
uint16_t ADC_GetConversionValue(void);
void ADC_VrefConfig(ADC_Vref_TypeDef ADC_Vref);
uint16_t ADC_GetConversionAverageValue(ADC_SamplesNum_TypeDef ADC_SamplesNum);
#endif

/******************* (C) COPYRIGHT 2021 SinOne Microelectronics *****END OF FILE****/
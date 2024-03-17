//************************************************************
//  Copyright (c) 合肥市新定义电子有限公司
//	文件名称: 		rd8_pwm.h
//	作者:					新定义应用团队
//	模块功能: 		PWM固件库函数头文件
//  最后更正日期:	2022年7月6日
// 	版本: 				V1.001
//  说明:该文件仅适用于RD8系列芯片
//*************************************************************

#ifndef _rd8_PWM_H_
#define _rd8_PWM_H_

#include "rd8.h"
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x)
//PWM预分频选择
typedef enum
{
  PWM0_PRESSEL_FHRC_D1 = (uint8_t)0x00, //PWM0预分频为Fhrc/1
  PWM0_PRESSEL_FHRC_D2 = (uint8_t)0x10, //PWM0预分频为Fhrc/2
  PWM0_PRESSEL_FHRC_D4 = (uint8_t)0x20, //PWM0预分频为Fhrc/4
  PWM0_PRESSEL_FHRC_D8 = (uint8_t)0x30, //PWM0预分频为Fhrc/8
  PWM2_PRESSEL_FHRC_D1 = (uint8_t)0x02, //PWM2预分频为Fhrc/1
  PWM3_PRESSEL_FHRC_D1 = (uint8_t)0x03, //PWM3预分频为Fhrc/1
  PWM4_PRESSEL_FHRC_D1 = (uint8_t)0x04, //PWM4预分频为Fhrc/1
} PWM_PresSel_TypeDef;

//PWM输出通道选择
typedef enum
{
  PWM00 = (uint8_t)0x00, //PWM输出通道选择: PWM00
  PWM01 = (uint8_t)0x01, //PWM输出通道选择: PWM01
  PWM02 = (uint8_t)0x02, //PWM输出通道选择: PWM02
  PWM03 = (uint8_t)0x03, //PWM输出通道选择: PWM03
  PWM04 = (uint8_t)0x04, //PWM输出通道选择: PWM04
  PWM05 = (uint8_t)0x05, //PWM输出通道选择: PWM05
  PWM06 = (uint8_t)0x06, //PWM输出通道选择: PWM06
  PWM07 = (uint8_t)0x07, //PWM输出通道选择: PWM07
  PWM20 = (uint8_t)0x20, //PWM输出通道选择: PWM20
  PWM21 = (uint8_t)0x21, //PWM输出通道选择: PWM21
  PWM30 = (uint8_t)0x32, //PWM输出通道选择: PWM30
  PWM31 = (uint8_t)0x33, //PWM输出通道选择: PWM31
  PWM40 = (uint8_t)0x44, //PWM输出通道选择: PWM40
  PWM41 = (uint8_t)0x45, //PWM输出通道选择: PWM41
} PWM_OutputPin_TypeDef;

//PWM互补模式通道选择
typedef enum
{
  PWM00PWM01 = (uint8_t)0x00, //PWM互补模式通道选择:PWM00、PWM01
  PWM02PWM03 = (uint8_t)0x02, //PWM互补模式通道选择:PWM02、PWM03
  PWM04PWM05 = (uint8_t)0x04, //PWM互补模式通道选择:PWM04、PWM05
  PWM06PWM07 = (uint8_t)0x06  //PWM互补模式通道选择:PWM06、PWM07
} PWM_ComplementaryOutputPin_TypeDef;

//PWM源选择
typedef enum
{
  PWM0_Type = (uint8_t)0x00, //操作PWM0
  PWM2_Type = (uint8_t)0x02, //操作PWM2
  PWM3_Type = (uint8_t)0x03, //操作PWM3
  PWM4_Type = (uint8_t)0x04, //操作PWM4
} PWM_Type_TypeDef;

#endif

#if defined(RD8G05x) || defined(RD8T05x)
//PWM预分频选择
typedef enum
{
  PWM_PRESSEL_FHRC_D1 = (uint8_t)0x00, //PWM0预分频为Fhrc/1
  PWM_PRESSEL_FHRC_D2 = (uint8_t)0x10, //PWM0预分频为Fhrc/2
  PWM_PRESSEL_FHRC_D4 = (uint8_t)0x20, //PWM0预分频为Fhrc/4
  PWM_PRESSEL_FHRC_D8 = (uint8_t)0x30, //PWM0预分频为Fhrc/8
} PWM_PresSel_TypeDef;

//PWM输出通道选择
typedef enum
{
  PWM0 = (uint8_t)0x00, //PWM输出通道选择: PWM00
  PWM1 = (uint8_t)0x01, //PWM输出通道选择: PWM01
  PWM2 = (uint8_t)0x02, //PWM输出通道选择: PWM02
  PWM3 = (uint8_t)0x03, //PWM输出通道选择: PWM03
  PWM4 = (uint8_t)0x04, //PWM输出通道选择: PWM04
  PWM5 = (uint8_t)0x05, //PWM输出通道选择: PWM05
  PWM6 = (uint8_t)0x06, //PWM输出通道选择: PWM06
  PWM7 = (uint8_t)0x07, //PWM输出通道选择: PWM07
} PWM_OutputPin_TypeDef;

//PWM互补模式通道选择
typedef enum
{
  PWM0PWM1 = (uint8_t)0x00, //PWM互补模式通道选择:PWM00、PWM01
  PWM2PWM3 = (uint8_t)0x02, //PWM互补模式通道选择:PWM02、PWM03
  PWM4PWM5 = (uint8_t)0x04, //PWM互补模式通道选择:PWM04、PWM05
  PWM6PWM7 = (uint8_t)0x06  //PWM互补模式通道选择:PWM06、PWM07
} PWM_ComplementaryOutputPin_TypeDef;

//PWM源选择
typedef enum
{
  PWM0_Type = (uint8_t)0x00, //操作PWM0
} PWM_Type_TypeDef;

#endif

//PWM故障检测模式
typedef enum
{
  PWM0_Latch_Mode = ((uint8_t)0x00),    //PWM故障检测模式:锁存模式
  PWM0_Immediate_Mode = ((uint8_t)0x20) //PWM故障检测模式:立即模式
} PWM_FaultDetectionMode_TypeDef;

//PWM故障检测电平选择
typedef enum
{
  PWM0_FaultDetectionVoltage_Low = ((uint8_t)0x00), //PWM故障检测低电平选择
  PWM0_FaultDetectionVoltage_high = ((uint8_t)0x10) //PWM故障检测高电平选择
} PWM_FaultDetectionVoltageSelect_TypeDef;

//PWM故障检测输入信号滤波时间
typedef enum
{
  PWM0_WaveFilteringTime_0us = ((uint8_t)0x00), //PWM故障检测输入信号滤波时间0us
  PWM0_WaveFilteringTime_1us = ((uint8_t)0x01), //PWM故障检测输入信号滤波时间1us
  PWM0_WaveFilteringTime_4us = ((uint8_t)0x02), //PWM故障检测输入信号滤波时间4us
  PWM0_WaveFilteringTime_16us = ((uint8_t)0x03) //PWM故障检测输入信号滤波时间16us
} PWM_FaultDetectionWaveFilteringTime_TypeDef;

#endif

#if defined (RD8G403)
typedef enum
{
  PWM_PRESSEL_FOSC_D1  = (uint8_t)0x00,		//PWM预分频为Fosc/1
  PWM_PRESSEL_FOSC_D2  = (uint8_t)0x01,		//PWM预分频为Fosc/2
  PWM_PRESSEL_FOSC_D8  = (uint8_t)0x02,		//PWM预分频为Fosc/8
  PWM_PRESSEL_FOSC_D32 = (uint8_t)0x03		//PWM预分频为Fosc/32
} PWM_PresSel_TypeDef;

typedef enum
{
  PWM2_OutputPin_P26       = ((uint8_t)0x00),		//PWM2输出口选择P26
  PWM2_OutputPin_P14       = ((uint8_t)0x04)		//PWM2输出口选择P14
} PWM2_OutputPin_TypeDef;

typedef enum
{
  PWM5_OutputPin_P12       = ((uint8_t)0x00),		//PWM5输出口选择P12
  PWM5_OutputPin_P21       = ((uint8_t)0x08)		//PWM5输出口选择P21
} PWM5_OutputPin_TypeDef;

typedef enum
{
  PWM0 = (uint8_t)0x01,						//PWM输出通道选择:PWM0
  PWM1 = (uint8_t)0x02,						//PWM输出通道选择:PWM1
  PWM2 = (uint8_t)0x04,						//PWM输出通道选择:PWM2
  PWM3 = (uint8_t)0x08,						//PWM输出通道选择:PWM3
  PWM4 = (uint8_t)0x10,						//PWM输出通道选择:PWM4
  PWM5 = (uint8_t)0x20,						//PWM输出通道选择:PWM5
  PWM6 = (uint8_t)0x40,						//PWM输出通道选择:PWM6
} PWM_OutputPin_TypeDef;

typedef enum
{
  PWM0PWM3 = (uint8_t)0x00,					//PWM互补模式通道选择:PWM0、PWM3
  PWM1PWM4 = (uint8_t)0x01,					//PWM互补模式通道选择:PWM1、PWM4
  PWM2PWM5 = (uint8_t)0x02					//PWM互补模式通道选择:PWM2、PWM5
} PWM_ComplementaryOutputPin_TypeDef;

//PWM源选择
typedef enum
{
  PWM0_Type = (uint8_t)0x00, //操作PWM0
} PWM_Type_TypeDef;
#endif

//PWM对齐模式
typedef enum
{
  PWM0_Edge_Aligned_Mode = (uint8_t)0x00,     //PWM边沿对齐模式
  PWM0_Center_Alignment_Mode = (uint8_t)0x01, //PWM中间对齐模式
} PWM_Aligned_Mode_TypeDef;

//PWM引脚复用选择
typedef enum
{
  PWM_OUTPUTSTATE_DISABLE = ((uint8_t)0x00), //该PIN脚作为GPIO
  PWM_OUTPUTSTATE_ENABLE = ((uint8_t)0x01)   //该PIN脚作为PWM
} PWM_OutputState_TypeDef;

//PWM输出正反向选择
typedef enum
{
  PWM_POLARITY_NON_INVERT = ((uint8_t)0x00), //PWM输出不反向
  PWM_POLARITY_INVERT = ((uint8_t)0x01)      //PWM输出反向
} PWM_Polarity_TypeDef;

//PWM占空比改变方向
typedef enum
{
  PWM_DutyChange_Up = (uint8_t)0x01, 		//PWM占空比增加
  PWM_DutyChange_Dowm = (uint8_t)0x00, 	//PWM占空比减少
} PWM_DutyChange_TypeDef;

/* PWM0基础操作函数：操作对象默认为PWM0 */
void PWM_DeInit(void);
// 配置死区时间
void PWM_DeadTimeConfig(uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime);
// 使能PWM
void PWM_Cmd(FunctionalState NewState);

// 配置PWM中断
void PWM_ITConfig(FunctionalState NewState,
                  PriorityStatus Priority);

// 获取中断位
FlagStatus PWM_GetFlagStatus(void);
//清楚中断位
void PWM_ClearFlag(void);

#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
FlagStatus PWM_GetFaultDetectionFlagStatus(void);
void PWM_ClearFaultDetectionFlag(void);
void PWM_FaultDetectionConfig(FunctionalState NewState);
void PWM_FaultDetectionModeConfig(PWM_FaultDetectionMode_TypeDef FaultDetectionMode,
                                  PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect,
                                  PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime);
#endif

/* 通用基础操作函数： 形参可以选择待操作PWM源*/
void PWM_Init(PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period);
// 设置PWM 计数器对其方式
void PWM_Aligned_Mode_Select(PWM_Aligned_Mode_TypeDef PWM_Aligned_Mode);
//输出使能
void PWM_OutputStateConfig(uint8_t PWM_OutputPin,
                           PWM_OutputState_TypeDef PWM_OutputState);
//极性配置
void PWM_PolarityConfig(uint8_t PWM_OutputPin,
                        PWM_Polarity_TypeDef PWM_Polarity);
//独立模式配置
void PWM_IndependentModeConfig(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle);
//互补模式配置
void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin,
                                 uint16_t PWM_DutyCycle);
//独立模式配置
void PWM_IndependentModeConfigEX(PWM_OutputPin_TypeDef PWM_ComplementaryOutputPin,
                                 uint16_t PWM_DutyCycle,
                                 PWM_OutputState_TypeDef PWM_OutputState);
//互补模式配置
void PWM_ComplementaryModeConfigEX(PWM_ComplementaryOutputPin_TypeDef PWM_OutputPin,
                                   uint16_t PWM_DutyCycle,
                                   PWM_OutputState_TypeDef PWM_OutputState);
//更改独立模式占空比
ErrorStatus PWM_IndependentMode_DutyChange(PWM_OutputPin_TypeDef PWM_OutputPin,
    PWM_DutyChange_TypeDef Change_Direction,
    uint16_t DutyIncremental);
//更改互补模式占空比
ErrorStatus PWM_ComplementaryMode_DutyChange(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin,
    PWM_DutyChange_TypeDef Change_Direction,
    uint16_t DutyIncremental);


/* 扩展版操作函数：在PWM0基础操作函数上增加选择待操作PWM源的形参 */
void PWM_DeInitEX(PWM_Type_TypeDef PWM_Type);
void PWM_DeadTimeConfigEX(PWM_Type_TypeDef PWM_Type, uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime);
void PWM_CmdEX(PWM_Type_TypeDef PWM_Type,
               FunctionalState NewState);
void PWM_ITConfigEX(PWM_Type_TypeDef PWM_Type, FunctionalState NewState, PriorityStatus Priority);
FlagStatus PWM_GetFlagStatusEX(PWM_Type_TypeDef PWM_Type);
void PWM_ClearFlagEX(PWM_Type_TypeDef PWM_Type);
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
FlagStatus PWM_GetFaultDetectionFlagStatusEX(PWM_Type_TypeDef PWM_Type);
void PWM_ClearFaultDetectionFlagEX(PWM_Type_TypeDef PWM_Type);
void PWM_FaultDetectionConfigEX(PWM_Type_TypeDef PWM_Type, FunctionalState NewState);
void PWM_FaultDetectionModeConfigEX(PWM_Type_TypeDef PWM_Type,
                                    PWM_FaultDetectionMode_TypeDef FaultDetectionMode,
                                    PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect,
                                    PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime);
#endif



/* PWM引脚重复用选择 */
#if defined (RD8G403)
void PWM_PWM2Selection(PWM2_OutputPin_TypeDef PWM2_OutputPin);
void PWM_PWM5Selection(PWM5_OutputPin_TypeDef PWM5_OutputPin);
#endif

#endif

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/
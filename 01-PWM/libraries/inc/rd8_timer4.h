//************************************************************
//  Copyright (c) 合肥市新定义电子有限公司
//	文件名称: 		rd8_timerx.h
//	作者		:
//	模块功能: 		TIMER4固件库函数头文件
//  最后更正日期: 2022/01/24
// 	版本: 				V1.10002
//  说明:该文件仅适用于RD8系列芯片
//*************************************************************

#ifndef _rd8_TIMER4_H_
#define _rd8_TIMER4_H_

#include "rd8.H"

#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
typedef enum
{
  TIM4_PRESSEL_FSYS_D12 = ((uint8_t)0x00), //TIMER4计数源来自系统时钟12分频
  TIM4_PRESSEL_FSYS_D1 = ((uint8_t)0x01)   //TIMER4计数源来自系统时钟
} TIM4_PresSel_TypeDef;

#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
typedef enum
{
  TIM4_MODE_TIMER = ((uint8_t)0x01),  //TIMER2做定时器
  TIM4_MODE_COUNTER = ((uint8_t)0x02) //TIMER2做计数器
} TIM4_CountMode_TypeDef;

typedef enum
{
  TIM4_COUNTDIRECTION_UP = ((uint8_t)0x00),     //向上计数模式
  TIM4_COUNTDIRECTION_DOWN_UP = ((uint8_t)0x10) //向上/向下计数模式
} TIM4_CountDirection_TypeDef;

typedef enum
{
  TIM4_FLAG_TF4 = (uint8_t)0x80, //中断标志位TF4
  TIM4_FLAG_EXF4 = (uint8_t)0x40 //中断标志位EXF4
} TIM4_Flag_TypeDef;

typedef enum
{
  TIM4_WORK_MODE0 = ((uint8_t)0x00), //TIMER4选择工作模式0
  TIM4_WORK_MODE1 = ((uint8_t)0x01), //TIMER4选择工作模式1
  TIM4_WORK_MODE3 = ((uint8_t)0x03), //TIMER4选择工作模式3
} TIM4_WorkMode_TypeDef;
#endif

void TIM4_DeInit();
void TIM4_PrescalerSelection(TIM4_PresSel_TypeDef TIM4_PrescalerSelection);
void TIM4_WorkMode1Config(uint16_t TIM4_SetCounter);
void TIM4_Cmd(FunctionalState NewState);
void TIM4_ITConfig(FunctionalState NewState, PriorityStatus Priority);
FlagStatus TIM4_GetFlagStatus(TIM4_Flag_TypeDef TIM4_Flag);
void TIM4_ClearFlag(TIM4_Flag_TypeDef TIM4_Flag);

void TIM4_TimeBaseInit(TIM4_CountMode_TypeDef TIM4_CountMode,
                       TIM4_CountDirection_TypeDef TIM4_CountDirection);
void TIM4_WorkMode0Config(uint16_t TIM4_SetCounter);
void TIM4_WorkMode3Config(uint16_t TIM4_SetCounter);
void TIM4_WorkModeConfig(TIM4_WorkMode_TypeDef TIM4_WorkMode, uint16_t TIM4_SetCounter);
void TIM4_SetEXEN4(FunctionalState NewState);

#endif

#endif
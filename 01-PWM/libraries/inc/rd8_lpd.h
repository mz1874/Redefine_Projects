//************************************************************
//  Copyright (c) 合肥市新定义电子有限公司
//	文件名称:			rd8_usci0.h
//	作者:
//	模块功能:			USCI0固件库函数C文件
//  最后更正日期:	2022年6月13日
// 	版本: 				V1.000
//  说明:该文件仅适用于RD8系列芯片
//*************************************************************

#ifndef _rd8_LPD_H_
#define _rd8_LPD_H_

#include "rd8.h"

typedef enum
{
  LPD_VTRIP_1_85V = (uint8_t)0x00, //LPD门限电压阈值为1.85V
  LPD_VTRIP_2_05V = (uint8_t)0x01, //LPD门限电压阈值为2.05V
  LPD_VTRIP_2_25V = (uint8_t)0x02, //LPD门限电压阈值为2.25V
  LPD_VTRIP_2_45V = (uint8_t)0x03, //LPD门限电压阈值为2.45V
  LPD_VTRIP_2_85V = (uint8_t)0x04, //LPD门限电压阈值为2.85V
  LPD_VTRIP_3_45V = (uint8_t)0x05, //LPD门限电压阈值为3.45V
  LPD_VTRIP_3_85V = (uint8_t)0x06, //LPD门限电压阈值为3.85V
  LPD_VTRIP_4_45V = (uint8_t)0x07, //LPD门限电压阈值为4.45V
} LPD_Vtrip_TypeDef;

typedef enum
{
  LPD_FLAG_LPDIF = (uint8_t)0x40, //LPD中断请求标志
  LPD_FLAG_LPDOF = (uint8_t)0x80, //LPD状态标志位
} LPD_Flag_TypeDef;

/*******************************宏函数*******************************/
/*****************************************************
*函数名称:FlagStatus LPD_GetFlagStatus(LPD_Flag_Typedef LPD_Flag)
*函数功能:获得LPD中断标志状态
*入口参数:
LPD_GetFlagStatus:LPD_Flag:中断标志位选择
*出口参数:
FlagStatus:LPD中断标志位置起状态
*****************************************************/
#define LPD_GetFlagStatus(LPD_Flag) ((READ_BIT(SCON,LPD_Flag)) ? (SET):(RESET))

/*****************************************************
*函数名称:void LPD_ClearFlag(LPD_Flag_Typedef LPD_Flag)
*函数功能:清除LPD中断标志状态
*入口参数:
LPD_Flag_Typedef;LPD_Flag:中断标志位选择
*出口参数:void
*****************************************************/
#define LPD_ClearFlag() CLEAR_BIT(SCON,LPD_Flag)

void LPD_DeInit(void);
void LPD_VtripConfig(LPD_Vtrip_TypeDef LPD_Vtrip);
void LPD_ITConfig(FunctionalState NewState, PriorityStatus Priority);
void LPD_Cmd(FunctionalState NewState);

#endif
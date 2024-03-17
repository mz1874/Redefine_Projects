//************************************************************
//  Copyright (c) 合肥市新定义电子有限公司
//	文件名称:			rd8_usci0.c
//	作者:
//	模块功能:			USCI0固件库函数C文件
//  最后更正日期:	2022年6月13日
// 	版本: 				V1.000
//  说明:该文件仅适用于RD8系列芯片
//*************************************************************

#include "rd8_lpd.h"

#if defined(RD8G05x) || defined(RD8T05x)

/**************************************************
*函数名称:void USCI1_DeInit(void)
*函数功能:USCI1相关寄存器复位至缺省值
*入口参数:void
*出口参数:void
**************************************************/
void LPD_DeInit(void)
{
	/* 配置相关寄存器复位 */
	LPDCFG = 0x00;
	/* 中断相关寄存器复位 */
	IE2 &= 0x7F;
	IP2 &= 0x7F;
}

/**************************************************
*函数名称:void LPD_VtripConfig(LPD_Vtrip_TypeDef LPD_Vtrip)
*函数功能:设置LPD门限电压阈值
*入口参数:
LPD_Vtrip_TypeDef:LPD_Vtrip:LPD门限电压阈值
*出口参数:void
**************************************************/
void LPD_VtripConfig(LPD_Vtrip_TypeDef LPD_Vtrip)
{
	LPDCFG &= 0xF1;	//复位门限电压阈值寄存器
	LPDCFG = LPD_Vtrip << 1;	//设置门限电压阈值寄存器
}

/**************************************************
*函数名称:void LPD_Cmd(FunctionalState NewState)
*函数功能:使能LPD功能
*入口参数:
FunctionalState:NewState:功能使能/失能
*出口参数:void
**************************************************/
void LPD_Cmd(FunctionalState NewState)
{
	if(NewState == ENABLE)
	{
		LPDCFG &= 0xFE;
	}
	else
	{
		LPDCFG |= 0x01;
	}
}

/*****************************************************
*函数名称:void LPD_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*函数功能:LPD中断初始化
*入口参数:
FunctionalState:NewState:中断使能/关闭选择
PriorityStatus:Priority:中断优先级选择
*出口参数:void
*****************************************************/
void LPD_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
	/* 中断开关 */
  if (NewState != DISABLE)
  {
    IE2 |= 0x01;
  }
  else
  {
    IE2 &= 0xFE;
  }

	/* 中断优先级 */
  if (Priority != LOW)
  {
    IP2 |= 0x01;
  }
  else
  {
    IP2 &= 0xFE;
  }
}


#endif
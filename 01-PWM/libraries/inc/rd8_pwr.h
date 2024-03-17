//************************************************************
//  Copyright (c) 合肥市新定义电子有限公司
//	文件名称: 		rd8_pwr.h
//	作者		:
//	模块功能: 		PWR固件库函数头文件
//  最后更正日期: 2020/8/14
// 	版本: 				V1.0
//  说明:该文件仅适用于RD8系列芯片
//*************************************************************

#ifndef _rd8_PWR_H_
#define _rd8_PWR_H_

#include "rd8.h"
#include <intrins.h>

void PWR_DeInit(void);
void PWR_EnterSTOPMode(void);
void PWR_EnterIDLEMode(void);

#endif

/******************* (C) COPYRIGHT 2018 SinOne Microelectronics *****END OF FILE****/
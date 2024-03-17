//************************************************************
//  Copyright (c) 合肥市新定义电子有限公司
//	文件名称: 			rd8_chksum.h
//	作者:					新定义应用团队
//	模块功能: 			BTM固件库函数C文件
//  最后更正日期: 2022年6月10日
// 	版本: 				V1.000
//  说明:
//*************************************************************

#ifndef _RD8_CHKSUM_H_
#define	_RD8_CHKSUM_H_

#include "rd8.h"

void CHKSUM_DeInit(void);
void CHKSUM_StartOperation(void);
uint16_t CHKSUM_GetCheckValue(void);

#endif

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/
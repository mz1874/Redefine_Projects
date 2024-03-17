//************************************************************
//  Copyright (c) 合肥市新定义电子有限公司
//	文件名称: 		rd8_CRC.h
//	作者					新定义应用团队
//	模块功能: 		CRC固件库函数头文件
//  最后更正日期: 2022年5月20日
// 	版本: 				V1.000
//  说明:该文件仅适用于RD8系列芯片
//*************************************************************

#ifndef _rd8_CRC_H_
#define _rd8_CRC_H_

#include "rd8.h"

uint32_t CRC_All(void); //根据IAP Range选项，硬件CRC运算CODE内容，返回CRC结果
uint32_t CRC_Frame(uint8_t *buff,
                   uint8_t Length); //软件CRC，将buff指向的数组进行CRC运算，返回CRC结果

#endif

/******************* (C) COPYRIGHT 2022 RDS Microelectronics *****END OF FILE****/
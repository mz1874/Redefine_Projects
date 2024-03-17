//************************************************************
//  Copyright (c) 合肥市新定义电子有限公司
//	文件名称: 		rd8_mdu.h
//	作者:					新定义应用团队
//	模块功能: 		MDU固件库函数头文件
//  最后更正日期: 2022年5月20日
// 	版本: 				V1.000
//  说明:该文件仅适用于RD8系列芯片
//*************************************************************

#ifndef _rd8_MDU_H_
#define _rd8_MDU_H_

#include "rd8.h"

typedef struct
{
  uint8_t MDU_EXA3Reg; //EXA3寄存器
  uint8_t MDU_EXA2Reg; //EXA2寄存器
  uint8_t MDU_EXA1Reg; //EXA1寄存器
  uint8_t MDU_EXA0Reg; //EXA0寄存器
} MDU_EXAxReg_Typedef;

typedef union
{
  MDU_EXAxReg_Typedef MDU_EXAxReg;
  uint32_t MDU_Temp;
} MDU_Temp_Union;

void MDU_DeInit(void);
void MDU_MultiplicationConfig(uint16_t Multiplicand, uint16_t Multiplier);
void MDU_DivisionConfig(uint32_t Dividend, uint16_t Divisor);
void MDU_StartOperation(void);
uint32_t MDU_GetProduct(void);
uint32_t MDU_GetQuotient(void);
uint16_t MDU_GetRemainder(void);

#endif

/******************* (C) COPYRIGHT 2018 SinOne Microelectronics *****END OF FILE****/
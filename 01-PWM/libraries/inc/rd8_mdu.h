//************************************************************
//  Copyright (c) �Ϸ����¶���������޹�˾
//	�ļ�����: 		rd8_mdu.h
//	����:					�¶���Ӧ���Ŷ�
//	ģ�鹦��: 		MDU�̼��⺯��ͷ�ļ�
//  ����������: 2022��5��20��
// 	�汾: 				V1.000
//  ˵��:���ļ���������RD8ϵ��оƬ
//*************************************************************

#ifndef _rd8_MDU_H_
#define _rd8_MDU_H_

#include "rd8.h"

typedef struct
{
  uint8_t MDU_EXA3Reg; //EXA3�Ĵ���
  uint8_t MDU_EXA2Reg; //EXA2�Ĵ���
  uint8_t MDU_EXA1Reg; //EXA1�Ĵ���
  uint8_t MDU_EXA0Reg; //EXA0�Ĵ���
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
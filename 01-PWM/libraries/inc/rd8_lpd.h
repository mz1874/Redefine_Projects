//************************************************************
//  Copyright (c) �Ϸ����¶���������޹�˾
//	�ļ�����:			rd8_usci0.h
//	����:
//	ģ�鹦��:			USCI0�̼��⺯��C�ļ�
//  ����������:	2022��6��13��
// 	�汾: 				V1.000
//  ˵��:���ļ���������RD8ϵ��оƬ
//*************************************************************

#ifndef _rd8_LPD_H_
#define _rd8_LPD_H_

#include "rd8.h"

typedef enum
{
  LPD_VTRIP_1_85V = (uint8_t)0x00, //LPD���޵�ѹ��ֵΪ1.85V
  LPD_VTRIP_2_05V = (uint8_t)0x01, //LPD���޵�ѹ��ֵΪ2.05V
  LPD_VTRIP_2_25V = (uint8_t)0x02, //LPD���޵�ѹ��ֵΪ2.25V
  LPD_VTRIP_2_45V = (uint8_t)0x03, //LPD���޵�ѹ��ֵΪ2.45V
  LPD_VTRIP_2_85V = (uint8_t)0x04, //LPD���޵�ѹ��ֵΪ2.85V
  LPD_VTRIP_3_45V = (uint8_t)0x05, //LPD���޵�ѹ��ֵΪ3.45V
  LPD_VTRIP_3_85V = (uint8_t)0x06, //LPD���޵�ѹ��ֵΪ3.85V
  LPD_VTRIP_4_45V = (uint8_t)0x07, //LPD���޵�ѹ��ֵΪ4.45V
} LPD_Vtrip_TypeDef;

typedef enum
{
  LPD_FLAG_LPDIF = (uint8_t)0x40, //LPD�ж������־
  LPD_FLAG_LPDOF = (uint8_t)0x80, //LPD״̬��־λ
} LPD_Flag_TypeDef;

/*******************************�꺯��*******************************/
/*****************************************************
*��������:FlagStatus LPD_GetFlagStatus(LPD_Flag_Typedef LPD_Flag)
*��������:���LPD�жϱ�־״̬
*��ڲ���:
LPD_GetFlagStatus:LPD_Flag:�жϱ�־λѡ��
*���ڲ���:
FlagStatus:LPD�жϱ�־λ����״̬
*****************************************************/
#define LPD_GetFlagStatus(LPD_Flag) ((READ_BIT(SCON,LPD_Flag)) ? (SET):(RESET))

/*****************************************************
*��������:void LPD_ClearFlag(LPD_Flag_Typedef LPD_Flag)
*��������:���LPD�жϱ�־״̬
*��ڲ���:
LPD_Flag_Typedef;LPD_Flag:�жϱ�־λѡ��
*���ڲ���:void
*****************************************************/
#define LPD_ClearFlag() CLEAR_BIT(SCON,LPD_Flag)

void LPD_DeInit(void);
void LPD_VtripConfig(LPD_Vtrip_TypeDef LPD_Vtrip);
void LPD_ITConfig(FunctionalState NewState, PriorityStatus Priority);
void LPD_Cmd(FunctionalState NewState);

#endif
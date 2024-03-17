//************************************************************
//  Copyright (c) �Ϸ����¶���������޹�˾
//	�ļ�����:			rd8_INT.h
//	����:					�¶���Ӧ���Ŷ�
//	ģ�鹦��:			INT�̼��⺯��ͷ�ļ�
//  ����������:	2022��6��9��
// 	�汾:					V1.001
//  ˵��:���ļ���������RD8ϵ��оƬ
//*************************************************************

#ifndef _rd8_INT_H_
#define _rd8_INT_H_

#include "rd8.h"

//�ⲿ�жϴ�����ʽѡ��ö��
typedef enum
{
  INT_TRIGGER_RISE_ONLY = (uint8_t)0x01, //�ⲿ�жϴ�����ʽΪ������
  INT_TRIGGER_FALL_ONLY = (uint8_t)0x02, //�ⲿ�жϴ�����ʽΪ�½���
  INT_TRIGGER_RISE_FALL = (uint8_t)0x03, //�ⲿ�жϴ�����ʽΪ���������½���
  INT_TRIGGER_DISABLE = (uint8_t)0x04    //�ر��ⲿ�жϴ���
} INT_TriggerMode_Typedef;

//�ⲿ�ж�����ѡ��ö��
typedef enum
{
  INT0 = (uint8_t)0x00, //�ⲿ�ж�0
  INT1 = (uint8_t)0x01, //�ⲿ�ж�1
  INT2 = (uint8_t)0x02  //�ⲿ�ж�2
} INTx_Typedef;

#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x)
//�ⲿ�ж�0�����ѡ��ö��
typedef enum
{
  INT04 = (uint8_t)0x10, //��P04����Ϊ�ⲿ�жϽ�
  INT05 = (uint8_t)0x20, //��P05����Ϊ�ⲿ�жϽ�
  INT06 = (uint8_t)0x40, //��P06����Ϊ�ⲿ�жϽ�
  INT07 = (uint8_t)0x80  //��P07����Ϊ�ⲿ�жϽ�
} INT0x_Typedef;

//�ⲿ�ж�1�����ѡ��ö��
typedef enum
{
  INT10 = (uint8_t)0x01, //��P40����Ϊ�ⲿ�жϽ�
  INT11 = (uint8_t)0x02, //��P41����Ϊ�ⲿ�жϽ�
  INT12 = (uint8_t)0x04, //��P42����Ϊ�ⲿ�жϽ�
  INT13 = (uint8_t)0x08, //��P43����Ϊ�ⲿ�жϽ�
  INT14 = (uint8_t)0x10, //��P14����Ϊ�ⲿ�жϽ�
  INT15 = (uint8_t)0x20, //��P15����Ϊ�ⲿ�жϽ�
  INT16 = (uint8_t)0x40, //��P16����Ϊ�ⲿ�жϽ�
  INT17 = (uint8_t)0x80  //��P17����Ϊ�ⲿ�жϽ�
} INT1x_Typedef;

//�ⲿ�ж�2�����ѡ��ö��
typedef enum
{
  INT20 = (uint8_t)0x01, //��P20����Ϊ�ⲿ�жϽ�
  INT21 = (uint8_t)0x02, //��P21����Ϊ�ⲿ�жϽ�
  INT22 = (uint8_t)0x04, //��P22����Ϊ�ⲿ�жϽ�
  INT23 = (uint8_t)0x08  //��P23����Ϊ�ⲿ�жϽ�
} INT2x_Typedef;
#endif

#if defined(RD8G05x) || defined(RD8T05x)
//�ⲿ�ж�0�����ѡ��ö��
typedef enum
{
  INT01 = (uint8_t)0x02,			//��P11����ΪINT0��
  INT02 = (uint8_t)0x04,			//��P12����ΪINT0��
  INT03 = (uint8_t)0x08				//��P13����ΪINT0��
} INT0x_Typedef;

//�ⲿ�ж�1�����ѡ��ö��
typedef enum
{
  INT10 = (uint8_t)0x01, //��P14����ΪINT1��
  INT11 = (uint8_t)0x02, //��P15����ΪINT1��
  INT12 = (uint8_t)0x04, //��P16����ΪINT1��
  INT13 = (uint8_t)0x08  //��P17����ΪINT1��
} INT1x_Typedef;

//�ⲿ�ж�2�����ѡ��ö��
typedef enum
{
  INT20 = (uint8_t)0x01, //��P04����ΪINT2��
  INT21 = (uint8_t)0x02, //��P05����ΪINT2��
  INT22 = (uint8_t)0x04, //��P06����ΪINT2��
  INT23 = (uint8_t)0x08, //��P07����ΪINT2��
  INT24 = (uint8_t)0x10, //��P20����ΪINT2��
  INT25 = (uint8_t)0x20  //��P21����ΪINT2��
} INT2x_Typedef;
#endif

#if defined(RD8G403)
//�ⲿ�ж�0�����ѡ��ö��
typedef enum
{
  INT00 = (uint8_t)0x01,			//��P00����ΪINT0��
  INT01 = (uint8_t)0x02			//��P01����ΪINT0��
} INT0x_Typedef;

//�ⲿ�ж�1�����ѡ��ö��
typedef enum
{
  INT10 = (uint8_t)0x01,					//��P10����ΪINT1��
  INT11 = (uint8_t)0x02,					//��P11����ΪINT1��
  INT12 = (uint8_t)0x04,					//��P12����ΪINT1��
  INT13 = (uint8_t)0x08,					//��P13����ΪINT1��
  INT14 = (uint8_t)0x10,					//��P14����ΪINT1��
  INT15 = (uint8_t)0x20,					//��P15����ΪINT1��
  INT16 = (uint8_t)0x40					//��P16����ΪINT1��
} INT1x_Typedef;

//�ⲿ�ж�2�����ѡ��ö��
typedef enum
{
  INT21 = (uint8_t)0x02,					//��P21����ΪINT2��
  INT22 = (uint8_t)0x04,					//��P22����ΪINT2��
  INT23 = (uint8_t)0x08,					//��P23����ΪINT2��
  INT24 = (uint8_t)0x10,					//��P24����ΪINT2��
  INT25 = (uint8_t)0x20,					//��P25����ΪINT2��
  INT26 = (uint8_t)0x40,					//��P26����ΪINT2��
  INT27 = (uint8_t)0x80						//��P27����ΪINT2��
} INT2x_Typedef;
#endif


void INT_DeInit(INTx_Typedef INTx);
void INT0_SetTriggerMode(uint8_t INT0x, INT_TriggerMode_Typedef TriggerMode);
void INT1_SetTriggerMode(uint8_t INT1x, INT_TriggerMode_Typedef TriggerMode);
void INT2_SetTriggerMode(uint8_t INT2x, INT_TriggerMode_Typedef TriggerMode);
void INT0_ITConfig(FunctionalState NewState, PriorityStatus Priority);
void INT1_ITConfig(FunctionalState NewState, PriorityStatus Priority);
void INT2_ITConfig(FunctionalState NewState, PriorityStatus Priority);

#endif

/******************* (C) COPYRIGHT 2022 RDS Microelectronics *****END OF FILE****/
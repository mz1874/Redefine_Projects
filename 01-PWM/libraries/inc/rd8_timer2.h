//************************************************************
//  Copyright (c) �Ϸ����¶���������޹�˾
//	�ļ�����: 		rd8_timer2.h
//	����:					�¶���Ӧ���Ŷ�
//	ģ�鹦��: 		TIMER2�̼��⺯��ͷ�ļ�
//  ����������: 2022��5��13��
// 	�汾: 				V1.10001
//  ˵��:���ļ���������RD8ϵ��оƬ
//*************************************************************

#ifndef _rd8_TIMER2_H_
#define _rd8_TIMER2_H_

#include "rd8.H"

typedef enum
{
  TIM2_PRESSEL_FSYS_D12 = ((uint8_t)0x00), //TIMER2����Դ����ϵͳʱ��12��Ƶ
  TIM2_PRESSEL_FSYS_D1 = ((uint8_t)0x01)   //TIMER2����Դ����ϵͳʱ��
} TIM2_PresSel_TypeDef;

typedef enum
{
  TIM2_MODE_TIMER = ((uint8_t)0x01),  //TIMER2����ʱ��
  TIM2_MODE_COUNTER = ((uint8_t)0x02) //TIMER2��������
} TIM2_CountMode_TypeDef;

typedef enum
{
  TIM2_COUNTDIRECTION_UP = ((uint8_t)0x00),     //���ϼ���ģʽ
  TIM2_COUNTDIRECTION_DOWN_UP = ((uint8_t)0x10) //����/���¼���ģʽ
} TIM2_CountDirection_TypeDef;

typedef enum
{
  TIM2_FLAG_TF2 = (uint8_t)0x80, //�жϱ�־λTF2
  TIM2_FLAG_EXF2 = (uint8_t)0x40 //�жϱ�־λEXF2
} TIM2_Flag_TypeDef;

typedef enum
{
  TIM2_WORK_MODE0 = ((uint8_t)0x00), //TIMER2ѡ����ģʽ0
  TIM2_WORK_MODE1 = ((uint8_t)0x01), //TIMER2ѡ����ģʽ1
  TIM2_WORK_MODE3 = ((uint8_t)0x03), //TIMER2ѡ����ģʽ3
} TIM2_WorkMode_TypeDef;



void TIM2_DeInit();
void TIM2_PrescalerSelection(TIM2_PresSel_TypeDef TIM2_PrescalerSelection);
void TIM2_TimeBaseInit(TIM2_PresSel_TypeDef
                       TIM2_PrescalerSelection,
                       TIM2_CountMode_TypeDef TIM2_CountMode,
                       TIM2_CountDirection_TypeDef TIM2_CountDirection);
void TIM2_WorkMode0Config(uint16_t TIM2_SetCounter);
void TIM2_WorkMode1Config(uint16_t TIM2_SetCounter);
void TIM2_WorkMode3Config(uint16_t TIM2_SetCounter);
void TIM2_WorkModeConfig(TIM2_WorkMode_TypeDef TIM2_WorkMode, uint16_t TIM2_SetCounter);
void TIM2_SetEXEN2(FunctionalState NewState);
void TIM2_Cmd(FunctionalState NewState);
uint16_t TIM2_GetCapture(void);
void TIM2_ITConfig(FunctionalState NewState, PriorityStatus Priority);
FlagStatus TIM2_GetFlagStatus(TIM2_Flag_TypeDef TIM2_Flag);
void TIM2_ClearFlag(TIM2_Flag_TypeDef TIM2_Flag);

#endif

/******************* (C) COPYRIGHT 2022 SinOne Microelectronics *****END OF FILE****/
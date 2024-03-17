//************************************************************
//  Copyright (c) �Ϸ����¶���������޹�˾
//	�ļ�����: 		rd8_btm.c
//	����:					�¶���Ӧ���Ŷ�
//	ģ�鹦��: 		BTM�̼��⺯��C�ļ�
//  ����������: 2022��5��20��
// 	�汾: 				V1.000
//  ˵��:���ļ���������RD8ϵ��оƬ
//*************************************************************

#include "rd8_btm.h"

/**************************************************
*��������:void BTM_Init(BTM_Timebase_TypeDef BTM_Timebase)
*��������:BTM��ʼ�����ú���
*��ڲ���:
BTM_Timebase_TypeDef:BTM_Timebase:BTM���ʱ��ѡ��
*���ڲ���:void
**************************************************/
void BTM_Init(BTM_Timebase_TypeDef BTM_Timebase)
{
  BTMCON = (BTMCON & 0xF0) | BTM_Timebase;
}

/*****************************************************
*��������:void BTM_Cmd(FunctionalState NewState)
*��������:BTM���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void BTM_Cmd(FunctionalState NewState)
{
  if (NewState == DISABLE)
  {
    BTMCON &= 0x7f;
  }
  else
  {
    BTMCON |= 0x80;
  }
}

/*****************************************************
*��������:void BTM_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:BTM�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void BTM_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  //�ж�ʹ������
  if (NewState == DISABLE)
  {
    IE1 &= 0xfb;
  }
  else
  {
    IE1 |= 0x04;
  }

  //�ж����ȼ�����
  if (Priority == LOW)
  {
    IP1 &= 0xfb;
  }
  else
  {
    IP1 |= 0x04;
  }
}

/******************* (C) COPYRIGHT 2022 RDS Microelectronics *****END OF FILE****/
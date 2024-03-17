//************************************************************
//  Copyright (c) �Ϸ����¶���������޹�˾
//	�ļ�����: 		rd8_acmp.c
//	����:					�¶���Ӧ���Ŷ�
//	ģ�鹦��: 		ACMP�̼��⺯��C�ļ�
//  ����������: 2022��5��20��
// 	�汾: 				V1.000
//  ˵��:���ļ���������RD8ϵ��оƬ
//*************************************************************

#include "rd8_acmp.h"

#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x)
/**************************************************
*��������:void ACMP_DeInit(void)
*��������:MDU��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void ACMP_DeInit(void)
{
  CMPCON = 0X00;
  CMPCFG = 0X00;
}

/**************************************************
*��������:void ACMP_Init(ACMP_Vref_Typedef ACMP_Vref, ACMP_Channel_TypeDef ACMP_Channel)
*��������:ģ��Ƚ�����ʼ�����ú���
*��ڲ���:
ACMP_Vref_Typedef:ACMP_Vref:ACMP�ο���ѹѡ��
ACMP_Channel_TypeDef:ACMP_Channel:ACMP����ͨ��ѡ��
*���ڲ���:void
**************************************************/
void ACMP_Init(ACMP_Vref_Typedef ACMP_Vref, ACMP_Channel_TypeDef ACMP_Channel)
{
  CMPCON = CMPCON & 0XF0 | ACMP_Vref;
  CMPCFG = CMPCFG & 0XFC | ACMP_Channel;
}

/**************************************************
*��������:void ACMP_SetTriggerMode(ACMP_TriggerMode_Typedef ACMP_TriggerMode)
*��������:ACMP�жϴ�����ʽ���ú���
*��ڲ���:
ACMP_TriggerMode_Typedef:ACMP_TriggerMode:�жϴ�����ʽѡ��
*���ڲ���:void
**************************************************/
void ACMP_SetTriggerMode(ACMP_TriggerMode_Typedef ACMP_TriggerMode)
{
  CMPCFG = CMPCFG & 0X03 | ACMP_TriggerMode;
}

/*****************************************************
*��������:void ACMP_Cmd(FunctionalState NewState)
*��������:ACMP���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void ACMP_Cmd(FunctionalState NewState)
{
  if (NewState == DISABLE)
  {
    CMPCON &= 0X7F;
  }
  else
  {
    CMPCON |= 0x80;
  }
}

/*****************************************************
*��������:void ACMP_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:ACMP�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void ACMP_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  if (NewState == DISABLE)
  {
    IE1 &= 0XBF;
  }
  else
  {
    IE1 |= 0X20;
  }

  if (Priority == LOW)
  {
    IP1 &= 0XBF;
  }
  else
  {
    IP1 |= 0X20;
  }
}

/*****************************************************
*��������:FlagStatus ACMP_GetFlagStatus(ACMP_Flag_TypeDef ACMP_Flag)
*��������:���ACMP��־״̬
*��ڲ���:
ACMP_Flag_TypeDef:ACMP_Flag:��־λѡ��
*���ڲ���:
FlagStatus:ACMP��־״̬
*****************************************************/
FlagStatus ACMP_GetFlagStatus(ACMP_Flag_TypeDef ACMP_Flag)
{
  return (bool)(CMPCON & ACMP_Flag);
}

/*****************************************************
*��������:void ACMP_ClearFlag(void)
*��������:�����־״̬
*��ڲ���:void
*���ڲ���:void
*****************************************************/
void ACMP_ClearFlag(void)
{
  CMPCON &= (~ACMP_FLAG_CMPIF);
}

#endif

/******************* (C) COPYRIGHT 2022 RDS Microelectronics *****END OF FILE****/
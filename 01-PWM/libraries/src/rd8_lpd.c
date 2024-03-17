//************************************************************
//  Copyright (c) �Ϸ����¶���������޹�˾
//	�ļ�����:			rd8_usci0.c
//	����:
//	ģ�鹦��:			USCI0�̼��⺯��C�ļ�
//  ����������:	2022��6��13��
// 	�汾: 				V1.000
//  ˵��:���ļ���������RD8ϵ��оƬ
//*************************************************************

#include "rd8_lpd.h"

#if defined(RD8G05x) || defined(RD8T05x)

/**************************************************
*��������:void USCI1_DeInit(void)
*��������:USCI1��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void LPD_DeInit(void)
{
	/* ������ؼĴ�����λ */
	LPDCFG = 0x00;
	/* �ж���ؼĴ�����λ */
	IE2 &= 0x7F;
	IP2 &= 0x7F;
}

/**************************************************
*��������:void LPD_VtripConfig(LPD_Vtrip_TypeDef LPD_Vtrip)
*��������:����LPD���޵�ѹ��ֵ
*��ڲ���:
LPD_Vtrip_TypeDef:LPD_Vtrip:LPD���޵�ѹ��ֵ
*���ڲ���:void
**************************************************/
void LPD_VtripConfig(LPD_Vtrip_TypeDef LPD_Vtrip)
{
	LPDCFG &= 0xF1;	//��λ���޵�ѹ��ֵ�Ĵ���
	LPDCFG = LPD_Vtrip << 1;	//�������޵�ѹ��ֵ�Ĵ���
}

/**************************************************
*��������:void LPD_Cmd(FunctionalState NewState)
*��������:ʹ��LPD����
*��ڲ���:
FunctionalState:NewState:����ʹ��/ʧ��
*���ڲ���:void
**************************************************/
void LPD_Cmd(FunctionalState NewState)
{
	if(NewState == ENABLE)
	{
		LPDCFG &= 0xFE;
	}
	else
	{
		LPDCFG |= 0x01;
	}
}

/*****************************************************
*��������:void LPD_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:LPD�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void LPD_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
	/* �жϿ��� */
  if (NewState != DISABLE)
  {
    IE2 |= 0x01;
  }
  else
  {
    IE2 &= 0xFE;
  }

	/* �ж����ȼ� */
  if (Priority != LOW)
  {
    IP2 |= 0x01;
  }
  else
  {
    IP2 &= 0xFE;
  }
}


#endif
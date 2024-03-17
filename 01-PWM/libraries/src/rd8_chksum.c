//************************************************************
//  Copyright (c) �Ϸ����¶���������޹�˾
//	�ļ�����:			rd8_chksum.c
//	����:					�¶���Ӧ���Ŷ�
//	ģ�鹦��:			CHKSUN�̼��⺯��C�ļ�
//  ����������:	2022��7��6��
// 	�汾: 				V1.001
//  ˵��:
//*************************************************************

#include "rd8_chksum.h"

#if defined(RD8G403)
/**************************************************
*��������:void CHKSUM_DeInit(void)
*��������:CHKSUM��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void CHKSUM_DeInit(void)
{
  OPERCON &= 0XFE;
  CHKSUML = 0X00;
  CHKSUMH = 0X00;
}

/**************************************************
*��������:void CHKSUM_StartOperation(void)
*��������:����һ��check sum����
*��ڲ���:void
*���ڲ���:void
**************************************************/
void CHKSUM_StartOperation(void)
{
  OPERCON |= 0X01;

  while(OPERCON & 0x01);
}

/**************************************************
*��������:uint16_t CHKSUM_GetCheckValue(void)
*��������:��ȡһ��check sum����ֵ
*��ڲ���:void
*���ڲ���:
uint16_t:check sum����ֵ
**************************************************/
uint16_t CHKSUM_GetCheckValue(void)
{
  uint16_t checktemp;
  checktemp = (uint16_t)(CHKSUMH << 8) +
              (uint16_t)CHKSUML;
  return checktemp;
}
#endif
/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/
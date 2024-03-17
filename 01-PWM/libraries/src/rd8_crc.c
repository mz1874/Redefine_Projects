//************************************************************
//  Copyright (c) �Ϸ����¶���������޹�˾
//	�ļ�����:			rd8_CRC.c
//	����:					�¶���Ӧ���Ŷ�
//	ģ�鹦��:			CRC�̼��⺯��C�ļ�
//  ����������:	2022��6��8��
// 	�汾:					V1.001
//  ˵��:���ļ���������RD8ϵ��оƬ
//*************************************************************

#include "rd8_CRC.h"
#include "intrins.H"

#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
/**************************************************
*��������:unsigned long CRC_All()
*��������:�󱾹���HEX��CRC32У��ֵ���ü����������OPTION��IAR Range��ͬ���仯
*��ڲ���:void
*���ڲ���:
uint32_t:����CRC������
**************************************************/
uint32_t CRC_All()
{
  uint32_t CRC_Result;
  OPERCON |= 0x01;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  CRCINX = 0x00;

  {
    /* keil C51 ���ݴ洢Ϊ���ģʽ */
    *((uint8_t*)&CRC_Result + 3) = CRCREG;

    *((uint8_t*)&CRC_Result + 2) = CRCREG;

    *((uint8_t*)&CRC_Result + 1) = CRCREG;

    *((uint8_t*)&CRC_Result) = CRCREG;
  }

  return CRC_Result;
}

/**************************************************
*��������:uint32_t CRC_Frame(uint8_t* buff,uint8_t Length)
*��������:������֡��CRCУ��ֵ
*��ڲ���:
uint8_t*:buff:������Ҫ����CRC���������
uint8_t:Length:������Ҫ��������鳤��
*���ڲ���:
uint32_t:CRC������
**************************************************/
uint32_t CRC_Frame(uint8_t* buff, uint8_t Length)
{
  uint8_t i;
  uint32_t CRC_Result = 0;

  EA = 0;
  OPERCON |= 0x02;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();

  for(i = 0; i < Length; i++)
  {
    CRC_Result = *(buff + i);
    CRCREG = CRC_Result;
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
  }

  CRCINX = 0x00;
  {
    /* keil C51 ���ݴ洢Ϊ���ģʽ */
    *((uint8_t*)&CRC_Result + 3) = CRCREG;

    *((uint8_t*)&CRC_Result + 2) = CRCREG;

    *((uint8_t*)&CRC_Result + 1) = CRCREG;

    *((uint8_t*)&CRC_Result) = CRCREG;
  }
  EA = 1;

  return CRC_Result;
}

#endif

/******************* (C) COPYRIGHT 2022 RDS Microelectronics *****END OF FILE****/
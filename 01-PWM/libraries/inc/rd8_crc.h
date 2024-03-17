//************************************************************
//  Copyright (c) �Ϸ����¶���������޹�˾
//	�ļ�����: 		rd8_CRC.h
//	����					�¶���Ӧ���Ŷ�
//	ģ�鹦��: 		CRC�̼��⺯��ͷ�ļ�
//  ����������: 2022��5��20��
// 	�汾: 				V1.000
//  ˵��:���ļ���������RD8ϵ��оƬ
//*************************************************************

#ifndef _rd8_CRC_H_
#define _rd8_CRC_H_

#include "rd8.h"

uint32_t CRC_All(void); //����IAP Rangeѡ�Ӳ��CRC����CODE���ݣ�����CRC���
uint32_t CRC_Frame(uint8_t *buff,
                   uint8_t Length); //���CRC����buffָ����������CRC���㣬����CRC���

#endif

/******************* (C) COPYRIGHT 2022 RDS Microelectronics *****END OF FILE****/
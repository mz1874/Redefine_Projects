//************************************************************
//  Copyright (c) �Ϸ����¶���������޹�˾
//	�ļ�����: 		rd8_iap.h
//	����:					�¶���Ӧ���Ŷ�
//	ģ�鹦��: 		BTM�̼��⺯��H�ļ�
//  ����������: 2022��5��20��
// 	�汾: 				V1.000
//  ˵��:���ļ���������RD8ϵ��оƬ
//*************************************************************

#ifndef _rd8_IAP_H_
#define _rd8_IAP_H_

#include "rd8.h"
#include "intrins.h"

//IAP��������ѡ��ö��
typedef enum
{
  IAP_MEMTYPE_ROM			= (uint8_t)0x00,	//IAP��������ΪROM
  IAP_MEMTYPE_UID			= (uint8_t)0x01,	//IAP��������ΪUID��ֻ��
	IAP_MEMTYPE_EEPROM	= (uint8_t)0x02,	//IAP��������ΪEEPROM
	IAP_MEMTYPE_LDROM		= (uint8_t)0x03,	//ֻ��LDROM�������ʱ��Ч��ֻ��
} IAP_MemType_TypeDef;

#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
typedef enum
{
	IAP_HOLDTIME_Null = (uint8_t)0x00			//����Flash������ҪHold Time
}IAP_HoldTime_TypeDef;
#endif

#if defined (RD8G403)
typedef enum
{
  IAP_HOLDTIME_1500US   = (uint8_t)0x08, //�趨CPU Hold TimeΪ1.5MS
  IAP_HOLDTIME_3000US   = (uint8_t)0x04, //�趨CPU Hold TimeΪ3MS
  IAP_HOLDTIME_6000US	  = (uint8_t)0x00  //�趨CPU Hold TimeΪ6MS
}IAP_HoldTime_TypeDef;
#endif

///MCU��λ��������ѡ��ö��
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
typedef enum
{
  IAP_BTLDType_APPROM = (uint8_t)0x00, //MCU��λ���APROM��λ
  IAP_BTLDType_LDROM = (uint8_t)0x01,  //MCU��λ���LDROM��λ
} IAP_BTLDType_TypeDef;
#endif

void IAP_DeInit(void);
ErrorStatus IAP_ProgramByte(uint32_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType,
                     uint8_t WriteTimeLimit);
uint16_t IAP_ProgramByteArray(uint32_t Address, uint16_t ArraySize, uint8_t* ByteArray, IAP_MemType_TypeDef IAP_MemType,
                     uint8_t WriteTimeLimit);
uint8_t IAP_ReadByte(uint32_t Address, IAP_MemType_TypeDef IAP_MemType);
uint16_t IAP_ReadByteArray(uint32_t Address, uint16_t ArraySize, uint8_t* ByteArray, IAP_MemType_TypeDef IAP_MemType);
void IAP_SectorErase(IAP_MemType_TypeDef IAP_MemType, uint32_t IAP_SectorEraseAddress,
                     uint8_t WriteTimeLimit);

#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
void IAP_BootLoaderControl(IAP_BTLDType_TypeDef IAP_BTLDType);
#endif

#endif

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/
//************************************************************
//  Copyright (c) 合肥市新定义电子有限公司
//	文件名称: 		rd8_iap.h
//	作者:					新定义应用团队
//	模块功能: 		BTM固件库函数H文件
//  最后更正日期: 2022年5月20日
// 	版本: 				V1.000
//  说明:该文件仅适用于RD8系列芯片
//*************************************************************

#ifndef _rd8_IAP_H_
#define _rd8_IAP_H_

#include "rd8.h"
#include "intrins.h"

//IAP操作区域选择枚举
typedef enum
{
  IAP_MEMTYPE_ROM			= (uint8_t)0x00,	//IAP操作区域为ROM
  IAP_MEMTYPE_UID			= (uint8_t)0x01,	//IAP操作区域为UID，只读
	IAP_MEMTYPE_EEPROM	= (uint8_t)0x02,	//IAP操作区域为EEPROM
	IAP_MEMTYPE_LDROM		= (uint8_t)0x03,	//只在LDROM程序操作时生效，只读
} IAP_MemType_TypeDef;

#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
typedef enum
{
	IAP_HOLDTIME_Null = (uint8_t)0x00			//高速Flash，不需要Hold Time
}IAP_HoldTime_TypeDef;
#endif

#if defined (RD8G403)
typedef enum
{
  IAP_HOLDTIME_1500US   = (uint8_t)0x08, //设定CPU Hold Time为1.5MS
  IAP_HOLDTIME_3000US   = (uint8_t)0x04, //设定CPU Hold Time为3MS
  IAP_HOLDTIME_6000US	  = (uint8_t)0x00  //设定CPU Hold Time为6MS
}IAP_HoldTime_TypeDef;
#endif

///MCU复位启动区域选择枚举
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
typedef enum
{
  IAP_BTLDType_APPROM = (uint8_t)0x00, //MCU复位后从APROM复位
  IAP_BTLDType_LDROM = (uint8_t)0x01,  //MCU复位后从LDROM复位
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
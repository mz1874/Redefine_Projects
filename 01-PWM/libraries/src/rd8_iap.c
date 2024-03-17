//************************************************************
//  Copyright (c) 合肥市新定义电子有限公司
//	文件名称:			rd8_iap.c
//	作者:					新定义应用团队
//	模块功能:			IAP固件库函数H文件
//  最后更正日期:	2022年6月9日
// 	版本:					V1.000
//  说明:该文件仅适用于RD8系列芯片
//*************************************************************
#include "rd8_iap.h"

/**************************************************
*函数名称:void IAP_DeInit(void)
*函数功能:IAP相关寄存器复位至缺省值
*入口参数:void
*出口参数:void
**************************************************/
void IAP_DeInit(void)
{
  IAPKEY = 0X00;
  IAPADL = 0X00;
  IAPADH = 0X00;
  IAPADE = 0X00;
  IAPDAT = 0X00;
  IAPCTL = 0X00;
}

#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x)
#include "IAP_Option_EW.h"

/**************************************************
*函数名称:void IAP_SectorEraseOption(Address,Data,IAP_MemType)
*函数功能:IAP扇区擦除
*入口参数:uint32_t:Address:IAP操作地址
*         IAP_MemType_TypeDef:IAP_MemType:IAP操作对象
*出口参数:void
**************************************************/
#define IAP_SectorEraseOption(Address,IAP_MemType) \
if(IAP_MemType == IAP_MEMTYPE_ROM)\
{\
	IAP_CodeSectorEraseOption(Address);\
}\
else if(IAP_MemType == IAP_MEMTYPE_EEPROM)\
{\
	IAP_EEPROMSectorEraseOption(Address);\
}\

/**************************************************
*函数名称:void IAP_ProgramByteOption(Address,Data,IAP_MemType)
*函数功能:IAP单Byte写入
*入口参数:uint32_t:Address:IAP操作地址
*         uint8_t:Data:写入的数据
*         IAP_MemType_TypeDef:IAP_MemType:IAP操作对象
*出口参数:void
**************************************************/
#define IAP_ProgramByteOption(Address,Data,IAP_MemType) \
if(IAP_MemType == IAP_MEMTYPE_ROM)\
{\
	IAP_CodeProgramByteOption(Address,Data);\
}\
else if(IAP_MemType == IAP_MEMTYPE_EEPROM)\
{\
	IAP_EEPROMProgramByteOption(Address,Data);\
}\

#if defined(RD8G37x) || defined(RD8T37x)

/**************************************************
*函数名称:uint8_t IAP_ReadByte(uint16_t Address, IAP_MemType_TypeDef IAP_MemType)
*函数功能:IAP读一个字节
*入口参数:
uint32_t:Address:IAP操作地址
IAP_MemType_TypeDef:IAP_MemType:IAP操作对象
*出口参数:
uint8_t:读到的字节数据
**************************************************/
uint8_t IAP_ReadByte(uint32_t Address, IAP_MemType_TypeDef IAP_MemType)
{
  uint8_t tmpbyte;
  BitStatus tmpbit;
  uint8_t tmpROMBNK;
  uint8_t tmpIAPADE;

  tmpbit = (BitStatus)EA;			//保存中断标志位状态
  /* 保存当前IAP操作区域和Bank分区 */
  tmpIAPADE = IAPADE;
  tmpROMBNK = ROMBNK;

  /* 如果开启了总中断，需要关闭总中断，防止IAP操作出错 */
  if(tmpbit != RESET)
  {
    disableInterrupts();
  }

  /* 逻辑地址转MCU地址 */
  if(Address >= 0x10000)  //如果超过64K则需要操作Bank寄存器指向目标地址
  {
    if(Address < 0x18000)
    {
      ROMBNK = (ROMBNK & 0xCF) | 0x20;
      Address = (Address - 0x8000);
    }
    else if(Address < 0x20000)
    {

      ROMBNK = (ROMBNK & 0xCF) | 0x30;
      Address = (Address - 0x10000);
    }
  }
  else
  {
    ROMBNK = (ROMBNK & 0xCF) | 0x10;
  }

  IAPADE = IAP_MemType;				//选择需要操作的IAP区域
  tmpbyte = *((uint8_t code*)Address);			//读取地址中存储的数据

  /* 恢复原IAP操作区域和Bank分区 */
  ROMBNK = tmpROMBNK;
  IAPADE = tmpIAPADE;

  /* 恢复原中断总开关 */
  if(tmpbit != RESET)
  {
    enableInterrupts();
  }

  return tmpbyte;			//返回读出的数据
}

/**************************************************
*函数名称:uint16_t IAP_ReadByteArray(uint32_t Address, IAP_MemType_TypeDef IAP_MemType,uint16_t ArraySize,uint8_t *ByteArray)
*函数功能:IAP读取长度可设的字符数组
*入口参数:
uint32_t:Address:IAP操作地址
IAP_MemType_TypeDef:IAP_MemType:IAP操作对象
uint8_t:ArraySize:需要读取数组的长度
uint8_t *:ByteArray:存放读取数据的数组指针
*出口参数:
**************************************************/
uint16_t IAP_ReadByteArray(uint32_t Address, uint16_t ArraySize, uint8_t* ByteArray, IAP_MemType_TypeDef IAP_MemType)
{
  BitStatus tmpbit;
  uint8_t tmpROMBNK;
  uint8_t tmpIAPADE;
  uint16_t tmpCnt;

  tmpbit = (BitStatus)EA;			//保存中断标志位状态
  /* 保存当前IAP操作区域和Bank分区 */
  tmpIAPADE = IAPADE;
  tmpROMBNK = ROMBNK;

  /* 如果开启了总中断，需要关闭总中断，防止IAP操作出错 */
  if(tmpbit != RESET)
  {
    disableInterrupts();
  }

  for(tmpCnt = 0; tmpCnt < ArraySize; tmpCnt++)
  {
    uint32_t tmpAddress = Address + tmpCnt;

    //逻辑地址转MCU地址
    if(Address >= 0x10000)  //如果超过64K则需要操作Bank寄存器指向目标地址
    {
      if(Address < 0x18000)
      {
        ROMBNK = (ROMBNK & 0xCF) | 0x20;
        Address = (Address - 0x8000);
      }
      else if(Address < 0x20000)
      {

        ROMBNK = (ROMBNK & 0xCF) | 0x30;
        Address = (Address - 0x10000);
      }
    }
    else
    {
      ROMBNK = (ROMBNK & 0xCF) | 0x10;
    }

    IAPADE = IAP_MemType;				//选择需要操作的IAP区域
    ByteArray[tmpCnt] = *((uint8_t code*)tmpAddress);			//读取地址中存储的数据
  }

  /* 恢复原IAP操作区域和Bank分区 */
  ROMBNK = tmpROMBNK;
  IAPADE = tmpIAPADE;

  /* 恢复原中断总开关 */
  if(tmpbit != RESET)
  {
    enableInterrupts();
  }

  return tmpCnt;
}

/**************************************************
*函数名称:void IAP_ProgramByte(uint16_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType, uint8_t WriteTimeLimit)
*函数功能:IAP写入一个字节
*入口参数:
uint32_t:Address:IAP操作地址
uint8_t:Data:写入的数据
IAP_MemType_TypeDef:IAP_MemType:IAP操作对象（ROM）
uint8_t:WriteTimeLimitIAP操作时限（值需大于等于0x40）
*出口参数:
ErrorStatus:写入成功/失败
**************************************************/
ErrorStatus IAP_ProgramByte(uint32_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType,
                            uint8_t WriteTimeLimit)
{
  uint8_t tmpData ;
  WriteTimeLimit = 0x00;	//该入参在RDS系列型号中无效
  IAP_ProgramByteOption(Address, Data, IAP_MemType);
  tmpData = IAP_ReadByte(Address, IAP_MemType);
  if(tmpData != Data)
    return ERROR;
  else
    return SUCCESS;
}

/**************************************************
*函数名称:void IAP_ProgramByteArray(uint16_t Address,, uint16_t ArraySize, uint8_t* ByteArray, IAP_MemType_TypeDef IAP_MemType, uint8_t WriteTimeLimit)
*函数功能:IAP写入长度可设的字节数组
*入口参数:
uint32_t:Address:IAP操作地址
uint8_t:ArraySize:需要写入数组的长度
uint8_t*:ByteArray:写入数据的数组指针
IAP_MemType_TypeDef:IAP_MemType:IAP操作对象
uint8_t:WriteTimeLimitIAP操作时限（值需大于等于0x40）
*出口参数:
uint8_t:数组中数据写入成功的长度
**************************************************/
uint16_t IAP_ProgramByteArray(uint32_t Address, uint16_t ArraySize, uint8_t* ByteArray, IAP_MemType_TypeDef IAP_MemType,
                             uint8_t WriteTimeLimit)
{
  uint16_t tmpCnt ;
  uint8_t tmpData;
  uint32_t tmpAddress;
  WriteTimeLimit = 0x00;	//该入参在RD8x3x型号中无效

  for(tmpCnt = 0; tmpCnt < ArraySize;)
  {
    tmpAddress = Address + tmpCnt;
    IAP_ProgramByteOption(tmpAddress, ByteArray[tmpCnt], IAP_MemType);
    tmpData = IAP_ReadByte(tmpAddress, IAP_MemType);
    if(tmpData != ByteArray[tmpCnt++])
      break;
  }
  return tmpCnt;
}

/**************************************************
*函数名称:void IAP_SectorErase(IAP_MemType_TypeDef IAP_MemType, uint32_t IAP_SectorEraseAddress,
                     uint8_t WriteTimeLimit)
*函数功能:IAP扇区擦除
*入口参数:
IAP_MemType_TypeDef:IAP_MemType:IAP操作对象（ROM）
uint32_t:IAP_SectorEraseAddress:IAP扇区擦除目标地址
uint8_t:WriteTimeLimit:IAP操作时限(值需大于等于0x40)
*出口参数:void
**************************************************/
void IAP_SectorErase(IAP_MemType_TypeDef IAP_MemType, uint32_t IAP_SectorEraseAddress,
                     uint8_t WriteTimeLimit)
{
  WriteTimeLimit = 0x00;	//该型号入参无效
  IAP_SectorEraseOption(IAP_SectorEraseAddress, IAP_MemType);
}

#else

/**************************************************
*函数名称:uint8_t IAP_ReadByte(uint16_t Address, IAP_MemType_TypeDef IAP_MemType)
*函数功能:IAP读一个字节
*入口参数:
uint32_t:Address:IAP操作地址
IAP_MemType_TypeDef:IAP_MemType:IAP操作对象（ROM、UID）
*出口参数:
uint8_t:读到的字节数据
**************************************************/
uint8_t IAP_ReadByte(uint32_t Address, IAP_MemType_TypeDef IAP_MemType)
{
  uint8_t tmpbyte;
  BitStatus tmpbit;
  tmpbit = (BitStatus)EA;

  if(tmpbit != RESET)
  {
    disableInterrupts();
  }

  IAPADE = IAP_MemType;
  tmpbyte = *((uint8_t code*)Address);
  IAPADE = IAP_MEMTYPE_ROM;

  if(tmpbit != RESET)
  {
    enableInterrupts();
  }

  return tmpbyte;
}

/**************************************************
*函数名称:uint16_t IAP_ReadByteArray(uint32_t Address,uint16_t ArraySize,uint8_t *ByteArray, IAP_MemType_TypeDef IAP_MemType)
*函数功能:IAP读取长度可设的字符数组
*入口参数:
uint32_t:Address:IAP操作地址
IAP_MemType_TypeDef:IAP_MemType:IAP操作对象
uint8_t:ArraySize:需要读取数组的长度
uint8_t *:ByteArray:存放读取数据的数组指针
*出口参数:
uint8_t:读取到数组的长度
**************************************************/
uint16_t IAP_ReadByteArray(uint32_t Address, uint16_t ArraySize, uint8_t* ByteArray, IAP_MemType_TypeDef IAP_MemType)
{
  uint16_t tmpCnt;
  BitStatus tmpbit;
  tmpbit = (BitStatus)EA;


  if(tmpbit != RESET)
  {
    disableInterrupts();
  }

  IAPADE = IAP_MemType;

  for(tmpCnt = 0; tmpCnt < ArraySize; tmpCnt++)
  {
    ByteArray[tmpCnt] = *((uint8_t code*)(Address + tmpCnt));
  }

  IAPADE = IAP_MEMTYPE_ROM;
  if(tmpbit != RESET)
  {
    enableInterrupts();
  }

  return tmpCnt;
}

/**************************************************
*函数名称:ErrorStatus IAP_ProgramByte(uint16_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType, uint8_t WriteTimeLimit)
*函数功能:IAP写入一个字节
*入口参数:
uint32_t:Address:IAP操作地址
uint8_t:Data:写入的数据
IAP_MemType_TypeDef:IAP_MemType:IAP操作对象（ROM）
uint8_t:WriteTimeLimitIAP操作时限（值需大于等于0x40）
*出口参数:void
ErrorStatus:写入成功/失败
**************************************************/
ErrorStatus IAP_ProgramByte(uint32_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType,
                            uint8_t WriteTimeLimit)
{
  uint8_t tmpData;
  WriteTimeLimit = 0x00;	//该型号入参无效
  IAP_ProgramByteOption(Address, Data, IAP_MemType);
  tmpData = IAP_ReadByte(Address, IAP_MemType);
  if(tmpData != Data)
    return ERROR;
  else
    return SUCCESS;
}

/**************************************************
*函数名称:uint16_t IAP_ProgramByteArray(uint32_t Address, uint16_t ArraySize, uint8_t* ByteArray, IAP_MemType_TypeDef IAP_MemType,uint8_t WriteTimeLimit)
*函数功能:IAP写入长度可设的字节数组
*入口参数:
uint32_t:Address:IAP操作地址
uint8_t:ArraySize:需要写入数组的长度
uint8_t*:ByteArray:写入数据的数组指针
IAP_MemType_TypeDef:IAP_MemType:IAP操作对象
uint8_t:WriteTimeLimitIAP操作时限（值需大于等于0x40）
*出口参数:
uint8_t:数组中数据写入成功的长度
**************************************************/
uint16_t IAP_ProgramByteArray(uint32_t Address, uint16_t ArraySize, uint8_t* ByteArray, IAP_MemType_TypeDef IAP_MemType,
                             uint8_t WriteTimeLimit)
{
  uint16_t tmpCnt ;
  uint8_t tmpData;
  uint32_t tmpAddress;
  WriteTimeLimit = 0x00;	//该入参在RD8x3x型号中无效
  for(tmpCnt = 0; tmpCnt < ArraySize;tmpCnt++)
  {
    tmpAddress = Address + tmpCnt;
    IAP_ProgramByteOption(tmpAddress, ByteArray[tmpCnt], IAP_MemType);
    tmpData = IAP_ReadByte(tmpAddress, IAP_MemType);
    if(tmpData != ByteArray[tmpCnt])
      break;
  }
  return tmpCnt;
}

/**************************************************
*函数名称:void IAP_SectorErase(IAP_MemType_TypeDef IAP_MemType, uint32_t IAP_SectorEraseAddress,
                     uint8_t WriteTimeLimit)
*函数功能:IAP扇区擦除
*入口参数:
IAP_MemType_TypeDef:IAP_MemType:IAP操作对象（ROM）
uint32_t:IAP_SectorEraseAddress:IAP扇区擦除目标地址
uint8_t:WriteTimeLimit:IAP操作时限(值需大于等于0x40)
*出口参数:void
**************************************************/
void IAP_SectorErase(IAP_MemType_TypeDef IAP_MemType, uint32_t IAP_SectorEraseAddress,
                     uint8_t WriteTimeLimit)
{
  WriteTimeLimit = 0x00;	//该型号入参无效
  IAP_SectorEraseOption(IAP_SectorEraseAddress, IAP_MemType);
}
#endif


/**************************************************
*函数名称:void IAP_BootLoaderControl(IAP_BTLDType_TypeDef IAP_BTLDType)
*函数功能:MCU软件复位后的启动区域配置，可以选择为APROM/LDROM
*入口参数:
IAP_BTLDType_Ty	peDef:IAP_BTLDType:软复位后的启动区域
*出口参数:void
**************************************************/
void IAP_BootLoaderControl(IAP_BTLDType_TypeDef IAP_BTLDType)
{
  IAPCTL = (IAPCTL & 0xFB) | IAP_BTLDType;
}
#endif

#if defined(RD8G05x) || defined(RD8T05x)

/**************************************************
*函数名称:uint8_t IAP_ReadByte(uint16_t Address, IAP_MemType_TypeDef IAP_MemType)
*函数功能:IAP读一个字节
*入口参数:
uint32_t:Address:IAP操作地址
IAP_MemType_TypeDef:IAP_MemType:IAP操作对象（ROM、UID）
*出口参数:
uint8_t:读到的字节数据
**************************************************/
uint8_t IAP_ReadByte(uint32_t Address, IAP_MemType_TypeDef IAP_MemType)
{
  uint8_t tmpbyte;
  BitStatus tmpbit;
  tmpbit = (BitStatus)EA;

  if(tmpbit != RESET)
  {
    disableInterrupts();
  }

  IAPADE = IAP_MemType;
  tmpbyte = *((uint8_t code*)Address);
  IAPADE = IAP_MEMTYPE_ROM;

  if(tmpbit != RESET)
  {
    enableInterrupts();
  }

  return tmpbyte;
}

/**************************************************
*函数名称:uint16_t IAP_ReadByteArray(uint32_t Address,uint16_t ArraySize,uint8_t *ByteArray, IAP_MemType_TypeDef IAP_MemType)
*函数功能:IAP读取长度可设的字符数组
*入口参数:
uint32_t:Address:IAP操作地址
IAP_MemType_TypeDef:IAP_MemType:IAP操作对象
uint8_t:ArraySize:需要读取数组的长度
uint8_t *:ByteArray:存放读取数据的数组指针
*出口参数:
**************************************************/
uint16_t IAP_ReadByteArray(uint32_t Address, uint16_t ArraySize, uint8_t* ByteArray, IAP_MemType_TypeDef IAP_MemType)
{
  uint16_t tmpCnt;
  BitStatus tmpbit;
  tmpbit = (BitStatus)EA;


  if(tmpbit != RESET)
  {
    disableInterrupts();
  }

  IAPADE = IAP_MemType;

  for(tmpCnt = 0; tmpCnt < ArraySize; tmpCnt++)
  {
    ByteArray[tmpCnt] = *((uint8_t code*)Address);
  }

  IAPADE = IAP_MEMTYPE_ROM;
  if(tmpbit != RESET)
  {
    enableInterrupts();
  }

  return tmpCnt;
}

/**************************************************
*函数名称:void IAP_SectorErase(IAP_MemType_TypeDef IAP_MemType, uint16_t IAP_SectorEraseAddress)
*函数功能:IAP扇区擦除
*入口参数:
IAP_MemType_TypeDef:IAP_MemType:IAP操作对象（ROM）
uint32_t:IAP_SectorEraseAddress:IAP扇区擦除目标地址
uint8_t:WriteTimeLimit:IAP操作时限(值需大于等于0x40)
*出口参数:void
**************************************************/
void IAP_SectorErase(IAP_MemType_TypeDef IAP_MemType, uint32_t IAP_SectorEraseAddress,
                     uint8_t WriteTimeLimit)
{
  /* UID区域不允许扇区擦除操作 */
  if((IAP_MemType == IAP_MEMTYPE_UID))
    return;

  IAPADE = IAP_MemType;
  IAPADH = (uint8_t)(IAP_SectorEraseAddress >> 8); //擦除IAP目标地址高位值
  IAPADL = (uint8_t)IAP_SectorEraseAddress;        //擦除IAP目标地址低位值
  IAPKEY = WriteTimeLimit;
  IAPCTL = 0x20;
  IAPCTL |= 0x02;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  IAPADE = IAP_MEMTYPE_ROM;
}

/**************************************************
*函数名称:void IAP_ProgramByte(uint16_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType, uint8_t WriteTimeLimit)
*函数功能:IAP写入一个字节
*入口参数:
uint32_t:Address:IAP操作地址
uint8_t:Data:写入的数据
IAP_MemType_TypeDef:IAP_MemType:IAP操作对象
uint8_t:WriteTimeLimit:IAP操作时限(值需大于等于0x40)
*出口参数:
ErrorStatus:写入成功/失败
**************************************************/
ErrorStatus IAP_ProgramByte(uint32_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType,
                            uint8_t WriteTimeLimit)
{
  BitStatus tmpbit;
  uint8_t tmpData;
  /* UID区域不允许写操作 */
  if((IAP_MemType == IAP_MEMTYPE_UID))
    return ERROR;

  tmpbit = (BitStatus)EA;
  if(tmpbit != RESET)
  {
    disableInterrupts();
  }

  IAPADE = IAP_MemType;
  IAPDAT = Data;
  IAPADH = (uint8_t)(Address >> 8);
  IAPADL = (uint8_t)Address;
  IAPKEY = WriteTimeLimit;
  IAPCTL = 0x10;
  IAPCTL |= 0x02;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();

  tmpData = *((uint8_t code*)Address);			//回读写入的数据
  IAPADE = IAP_MEMTYPE_ROM;
  /* 恢复原中断总开关 */
  if(tmpbit != RESET)
  {
    enableInterrupts();
  }
  /* 判断实际写入数据和理论数据是否一致*/
  if(Data != tmpData)
    return ERROR;
  else
    return SUCCESS;
}

/**************************************************
*函数名称:void IAP_ProgramByteArray(uint16_t Address,, uint16_t ArraySize, uint8_t* ByteArray, IAP_MemType_TypeDef IAP_MemType, uint8_t WriteTimeLimit)
*函数功能:IAP写入长度可设的字节数组
*入口参数:
uint32_t:Address:IAP操作地址
uint8_t:ArraySize:需要写入数组的长度
uint8_t*:ByteArray:写入数据的数组指针
IAP_MemType_TypeDef:IAP_MemType:IAP操作对象
uint8_t:WriteTimeLimitIAP操作时限（值需大于等于0x40）
*出口参数:
uint8_t:数组中数据写入成功的长度
**************************************************/
uint16_t IAP_ProgramByteArray(uint32_t Address, uint16_t ArraySize, uint8_t* ByteArray, IAP_MemType_TypeDef IAP_MemType,
                             uint8_t WriteTimeLimit)
{
  BitStatus tmpbit;
  uint16_t tmpCnt;
  uint8_t tmpData;

  /* UID区域不允许写操作 */
  if((IAP_MemType == IAP_MEMTYPE_UID))
    return 0;

  tmpbit = (BitStatus)EA;
  if(tmpbit != RESET)
  {
    disableInterrupts();
  }
  IAPADE = IAP_MemType;
  IAPKEY = WriteTimeLimit;
  for(tmpCnt = 0; tmpCnt < ArraySize; tmpCnt++)
  {
		
    IAPDAT = ByteArray[tmpCnt];
    IAPADH = (uint8_t)((Address + tmpCnt) >> 8);
    IAPADL = (uint8_t)(Address + tmpCnt);

    IAPCTL = 0x10;
    IAPCTL |= 0x02;
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();

    if(ByteArray[tmpCnt] == *((uint8_t code*)Address))
      break;
  }
  IAPADE = IAP_MEMTYPE_ROM;
  /* 恢复原中断总开关 */
  if(tmpbit != RESET)
  {
    enableInterrupts();
  }
  /* 判断实际写入数据和理论数据是否一致*/
  if(tmpData != tmpData)
    return ERROR;
  else
    return SUCCESS;
}

/**************************************************
*函数名称:void IAP_BootLoaderControl(IAP_BTLDType_TypeDef IAP_BTLDType)
*函数功能:MCU软件复位后的启动区域配置，可以选择为APROM/LDROM
*入口参数:
IAP_BTLDType_Ty	peDef:IAP_BTLDType:软复位后的启动区域
*出口参数:void
**************************************************/
void IAP_BootLoaderControl(IAP_BTLDType_TypeDef IAP_BTLDType)
{
  IAPCTL = (IAPCTL & 0xFB) | IAP_BTLDType;
}
#endif

#if defined(RD8G403)
/**************************************************
*函数名称:void IAP_SetHoldTime(IAP_HoldTime_TypeDef IAP_HoldTime)
*函数功能:IAP操作CPU Hold Time配置函数
*入口参数:
IAP_HoldTime_TypeDef:IAP_HoldTimed:Hold TimeTime选择
*出口参数:void
**************************************************/
void IAP_SetHoldTime(IAP_HoldTime_TypeDef
                     IAP_HoldTime)
{
  IAPCTL = IAPCTL & 0XF3 | IAP_HoldTime;
}

/**************************************************
*函数名称:ErrorStatus IAP_ProgramByte(uint16_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType, uint8_t WriteTimeLimit)
*函数功能:IAP写入一个字节
*入口参数:
uint16_t:Address:IAP操作地址
uint8_t:Data:写入的数据
IAP_MemType_TypeDef:IAP_MemType:IAP操作对象（ROM、EEPROM）
备注：IAP_MEMTYPE_UID不允许写操作，对UID进行写操作无效
uint8_t:WriteTimeLimit:IAP操作时限	(非零值)
*出口参数:void
**************************************************/
ErrorStatus IAP_ProgramByte(uint32_t Address,
                            uint8_t Data, IAP_MemType_TypeDef IAP_MemType,
                            uint8_t WriteTimeLimit)
{
  BitStatus tmpbit;

  /* UID操作区域不允许写操作 */
  if(IAP_MemType == IAP_MEMTYPE_UID)
    return ERROR;

  tmpbit = (BitStatus)EA;
  if(tmpbit != RESET)
  {
    disableInterrupts();
  }

  IAPADE = IAP_MemType;
  IAPDAT = Data;
  IAPADH = (uint8_t)(Address >> 8);
  IAPADL = (uint8_t)Address;
  IAPKEY = WriteTimeLimit;
  IAPCTL |= 0x02;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  IAPADE = IAP_MEMTYPE_ROM;

  if(tmpbit != RESET)
  {
    enableInterrupts();
  }
  if(Data == IAP_ReadByte(Address, IAP_MemType))
    return SUCCESS;
  else
    return ERROR;
}

/**************************************************
*函数名称:uint8_t IAP_ReadByte(uint16_t Address, IAP_MemType_TypeDef IAP_MemType)
*函数功能:IAP读一个字节
*入口参数:
uint16_t:Address:IAP操作地址
IAP_MemType_TypeDef:FLASH_MemType:IAP操作对象（ROM、UID、EEPROM）
*出口参数:uint8_t			读到的字节数据
**************************************************/
uint8_t IAP_ReadByte(uint32_t Address,
                     IAP_MemType_TypeDef IAP_MemType)
{
  uint8_t tmpbyte;
  BitStatus tmpbit;
  tmpbit = (BitStatus)EA;

  if(tmpbit != RESET)
  {
    disableInterrupts();
  }

  IAPADE = IAP_MemType;
  tmpbyte = *((uint8_t code*)Address);
  IAPADE = IAP_MEMTYPE_ROM;

  if(tmpbit != RESET)
  {
    enableInterrupts();
  }

  return tmpbyte;
}

#endif

/******************* (C) COPYRIGHT 2022 SinOne Microelectronics *****END OF FILE****/
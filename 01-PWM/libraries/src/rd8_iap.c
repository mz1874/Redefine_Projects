//************************************************************
//  Copyright (c) �Ϸ����¶���������޹�˾
//	�ļ�����:			rd8_iap.c
//	����:					�¶���Ӧ���Ŷ�
//	ģ�鹦��:			IAP�̼��⺯��H�ļ�
//  ����������:	2022��6��9��
// 	�汾:					V1.000
//  ˵��:���ļ���������RD8ϵ��оƬ
//*************************************************************
#include "rd8_iap.h"

/**************************************************
*��������:void IAP_DeInit(void)
*��������:IAP��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
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
*��������:void IAP_SectorEraseOption(Address,Data,IAP_MemType)
*��������:IAP��������
*��ڲ���:uint32_t:Address:IAP������ַ
*         IAP_MemType_TypeDef:IAP_MemType:IAP��������
*���ڲ���:void
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
*��������:void IAP_ProgramByteOption(Address,Data,IAP_MemType)
*��������:IAP��Byteд��
*��ڲ���:uint32_t:Address:IAP������ַ
*         uint8_t:Data:д�������
*         IAP_MemType_TypeDef:IAP_MemType:IAP��������
*���ڲ���:void
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
*��������:uint8_t IAP_ReadByte(uint16_t Address, IAP_MemType_TypeDef IAP_MemType)
*��������:IAP��һ���ֽ�
*��ڲ���:
uint32_t:Address:IAP������ַ
IAP_MemType_TypeDef:IAP_MemType:IAP��������
*���ڲ���:
uint8_t:�������ֽ�����
**************************************************/
uint8_t IAP_ReadByte(uint32_t Address, IAP_MemType_TypeDef IAP_MemType)
{
  uint8_t tmpbyte;
  BitStatus tmpbit;
  uint8_t tmpROMBNK;
  uint8_t tmpIAPADE;

  tmpbit = (BitStatus)EA;			//�����жϱ�־λ״̬
  /* ���浱ǰIAP���������Bank���� */
  tmpIAPADE = IAPADE;
  tmpROMBNK = ROMBNK;

  /* ������������жϣ���Ҫ�ر����жϣ���ֹIAP�������� */
  if(tmpbit != RESET)
  {
    disableInterrupts();
  }

  /* �߼���ַתMCU��ַ */
  if(Address >= 0x10000)  //�������64K����Ҫ����Bank�Ĵ���ָ��Ŀ���ַ
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

  IAPADE = IAP_MemType;				//ѡ����Ҫ������IAP����
  tmpbyte = *((uint8_t code*)Address);			//��ȡ��ַ�д洢������

  /* �ָ�ԭIAP���������Bank���� */
  ROMBNK = tmpROMBNK;
  IAPADE = tmpIAPADE;

  /* �ָ�ԭ�ж��ܿ��� */
  if(tmpbit != RESET)
  {
    enableInterrupts();
  }

  return tmpbyte;			//���ض���������
}

/**************************************************
*��������:uint16_t IAP_ReadByteArray(uint32_t Address, IAP_MemType_TypeDef IAP_MemType,uint16_t ArraySize,uint8_t *ByteArray)
*��������:IAP��ȡ���ȿ�����ַ�����
*��ڲ���:
uint32_t:Address:IAP������ַ
IAP_MemType_TypeDef:IAP_MemType:IAP��������
uint8_t:ArraySize:��Ҫ��ȡ����ĳ���
uint8_t *:ByteArray:��Ŷ�ȡ���ݵ�����ָ��
*���ڲ���:
**************************************************/
uint16_t IAP_ReadByteArray(uint32_t Address, uint16_t ArraySize, uint8_t* ByteArray, IAP_MemType_TypeDef IAP_MemType)
{
  BitStatus tmpbit;
  uint8_t tmpROMBNK;
  uint8_t tmpIAPADE;
  uint16_t tmpCnt;

  tmpbit = (BitStatus)EA;			//�����жϱ�־λ״̬
  /* ���浱ǰIAP���������Bank���� */
  tmpIAPADE = IAPADE;
  tmpROMBNK = ROMBNK;

  /* ������������жϣ���Ҫ�ر����жϣ���ֹIAP�������� */
  if(tmpbit != RESET)
  {
    disableInterrupts();
  }

  for(tmpCnt = 0; tmpCnt < ArraySize; tmpCnt++)
  {
    uint32_t tmpAddress = Address + tmpCnt;

    //�߼���ַתMCU��ַ
    if(Address >= 0x10000)  //�������64K����Ҫ����Bank�Ĵ���ָ��Ŀ���ַ
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

    IAPADE = IAP_MemType;				//ѡ����Ҫ������IAP����
    ByteArray[tmpCnt] = *((uint8_t code*)tmpAddress);			//��ȡ��ַ�д洢������
  }

  /* �ָ�ԭIAP���������Bank���� */
  ROMBNK = tmpROMBNK;
  IAPADE = tmpIAPADE;

  /* �ָ�ԭ�ж��ܿ��� */
  if(tmpbit != RESET)
  {
    enableInterrupts();
  }

  return tmpCnt;
}

/**************************************************
*��������:void IAP_ProgramByte(uint16_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType, uint8_t WriteTimeLimit)
*��������:IAPд��һ���ֽ�
*��ڲ���:
uint32_t:Address:IAP������ַ
uint8_t:Data:д�������
IAP_MemType_TypeDef:IAP_MemType:IAP��������ROM��
uint8_t:WriteTimeLimitIAP����ʱ�ޣ�ֵ����ڵ���0x40��
*���ڲ���:
ErrorStatus:д��ɹ�/ʧ��
**************************************************/
ErrorStatus IAP_ProgramByte(uint32_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType,
                            uint8_t WriteTimeLimit)
{
  uint8_t tmpData ;
  WriteTimeLimit = 0x00;	//�������RDSϵ���ͺ�����Ч
  IAP_ProgramByteOption(Address, Data, IAP_MemType);
  tmpData = IAP_ReadByte(Address, IAP_MemType);
  if(tmpData != Data)
    return ERROR;
  else
    return SUCCESS;
}

/**************************************************
*��������:void IAP_ProgramByteArray(uint16_t Address,, uint16_t ArraySize, uint8_t* ByteArray, IAP_MemType_TypeDef IAP_MemType, uint8_t WriteTimeLimit)
*��������:IAPд�볤�ȿ�����ֽ�����
*��ڲ���:
uint32_t:Address:IAP������ַ
uint8_t:ArraySize:��Ҫд������ĳ���
uint8_t*:ByteArray:д�����ݵ�����ָ��
IAP_MemType_TypeDef:IAP_MemType:IAP��������
uint8_t:WriteTimeLimitIAP����ʱ�ޣ�ֵ����ڵ���0x40��
*���ڲ���:
uint8_t:����������д��ɹ��ĳ���
**************************************************/
uint16_t IAP_ProgramByteArray(uint32_t Address, uint16_t ArraySize, uint8_t* ByteArray, IAP_MemType_TypeDef IAP_MemType,
                             uint8_t WriteTimeLimit)
{
  uint16_t tmpCnt ;
  uint8_t tmpData;
  uint32_t tmpAddress;
  WriteTimeLimit = 0x00;	//�������RD8x3x�ͺ�����Ч

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
*��������:void IAP_SectorErase(IAP_MemType_TypeDef IAP_MemType, uint32_t IAP_SectorEraseAddress,
                     uint8_t WriteTimeLimit)
*��������:IAP��������
*��ڲ���:
IAP_MemType_TypeDef:IAP_MemType:IAP��������ROM��
uint32_t:IAP_SectorEraseAddress:IAP��������Ŀ���ַ
uint8_t:WriteTimeLimit:IAP����ʱ��(ֵ����ڵ���0x40)
*���ڲ���:void
**************************************************/
void IAP_SectorErase(IAP_MemType_TypeDef IAP_MemType, uint32_t IAP_SectorEraseAddress,
                     uint8_t WriteTimeLimit)
{
  WriteTimeLimit = 0x00;	//���ͺ������Ч
  IAP_SectorEraseOption(IAP_SectorEraseAddress, IAP_MemType);
}

#else

/**************************************************
*��������:uint8_t IAP_ReadByte(uint16_t Address, IAP_MemType_TypeDef IAP_MemType)
*��������:IAP��һ���ֽ�
*��ڲ���:
uint32_t:Address:IAP������ַ
IAP_MemType_TypeDef:IAP_MemType:IAP��������ROM��UID��
*���ڲ���:
uint8_t:�������ֽ�����
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
*��������:uint16_t IAP_ReadByteArray(uint32_t Address,uint16_t ArraySize,uint8_t *ByteArray, IAP_MemType_TypeDef IAP_MemType)
*��������:IAP��ȡ���ȿ�����ַ�����
*��ڲ���:
uint32_t:Address:IAP������ַ
IAP_MemType_TypeDef:IAP_MemType:IAP��������
uint8_t:ArraySize:��Ҫ��ȡ����ĳ���
uint8_t *:ByteArray:��Ŷ�ȡ���ݵ�����ָ��
*���ڲ���:
uint8_t:��ȡ������ĳ���
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
*��������:ErrorStatus IAP_ProgramByte(uint16_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType, uint8_t WriteTimeLimit)
*��������:IAPд��һ���ֽ�
*��ڲ���:
uint32_t:Address:IAP������ַ
uint8_t:Data:д�������
IAP_MemType_TypeDef:IAP_MemType:IAP��������ROM��
uint8_t:WriteTimeLimitIAP����ʱ�ޣ�ֵ����ڵ���0x40��
*���ڲ���:void
ErrorStatus:д��ɹ�/ʧ��
**************************************************/
ErrorStatus IAP_ProgramByte(uint32_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType,
                            uint8_t WriteTimeLimit)
{
  uint8_t tmpData;
  WriteTimeLimit = 0x00;	//���ͺ������Ч
  IAP_ProgramByteOption(Address, Data, IAP_MemType);
  tmpData = IAP_ReadByte(Address, IAP_MemType);
  if(tmpData != Data)
    return ERROR;
  else
    return SUCCESS;
}

/**************************************************
*��������:uint16_t IAP_ProgramByteArray(uint32_t Address, uint16_t ArraySize, uint8_t* ByteArray, IAP_MemType_TypeDef IAP_MemType,uint8_t WriteTimeLimit)
*��������:IAPд�볤�ȿ�����ֽ�����
*��ڲ���:
uint32_t:Address:IAP������ַ
uint8_t:ArraySize:��Ҫд������ĳ���
uint8_t*:ByteArray:д�����ݵ�����ָ��
IAP_MemType_TypeDef:IAP_MemType:IAP��������
uint8_t:WriteTimeLimitIAP����ʱ�ޣ�ֵ����ڵ���0x40��
*���ڲ���:
uint8_t:����������д��ɹ��ĳ���
**************************************************/
uint16_t IAP_ProgramByteArray(uint32_t Address, uint16_t ArraySize, uint8_t* ByteArray, IAP_MemType_TypeDef IAP_MemType,
                             uint8_t WriteTimeLimit)
{
  uint16_t tmpCnt ;
  uint8_t tmpData;
  uint32_t tmpAddress;
  WriteTimeLimit = 0x00;	//�������RD8x3x�ͺ�����Ч
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
*��������:void IAP_SectorErase(IAP_MemType_TypeDef IAP_MemType, uint32_t IAP_SectorEraseAddress,
                     uint8_t WriteTimeLimit)
*��������:IAP��������
*��ڲ���:
IAP_MemType_TypeDef:IAP_MemType:IAP��������ROM��
uint32_t:IAP_SectorEraseAddress:IAP��������Ŀ���ַ
uint8_t:WriteTimeLimit:IAP����ʱ��(ֵ����ڵ���0x40)
*���ڲ���:void
**************************************************/
void IAP_SectorErase(IAP_MemType_TypeDef IAP_MemType, uint32_t IAP_SectorEraseAddress,
                     uint8_t WriteTimeLimit)
{
  WriteTimeLimit = 0x00;	//���ͺ������Ч
  IAP_SectorEraseOption(IAP_SectorEraseAddress, IAP_MemType);
}
#endif


/**************************************************
*��������:void IAP_BootLoaderControl(IAP_BTLDType_TypeDef IAP_BTLDType)
*��������:MCU�����λ��������������ã�����ѡ��ΪAPROM/LDROM
*��ڲ���:
IAP_BTLDType_Ty	peDef:IAP_BTLDType:��λ�����������
*���ڲ���:void
**************************************************/
void IAP_BootLoaderControl(IAP_BTLDType_TypeDef IAP_BTLDType)
{
  IAPCTL = (IAPCTL & 0xFB) | IAP_BTLDType;
}
#endif

#if defined(RD8G05x) || defined(RD8T05x)

/**************************************************
*��������:uint8_t IAP_ReadByte(uint16_t Address, IAP_MemType_TypeDef IAP_MemType)
*��������:IAP��һ���ֽ�
*��ڲ���:
uint32_t:Address:IAP������ַ
IAP_MemType_TypeDef:IAP_MemType:IAP��������ROM��UID��
*���ڲ���:
uint8_t:�������ֽ�����
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
*��������:uint16_t IAP_ReadByteArray(uint32_t Address,uint16_t ArraySize,uint8_t *ByteArray, IAP_MemType_TypeDef IAP_MemType)
*��������:IAP��ȡ���ȿ�����ַ�����
*��ڲ���:
uint32_t:Address:IAP������ַ
IAP_MemType_TypeDef:IAP_MemType:IAP��������
uint8_t:ArraySize:��Ҫ��ȡ����ĳ���
uint8_t *:ByteArray:��Ŷ�ȡ���ݵ�����ָ��
*���ڲ���:
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
*��������:void IAP_SectorErase(IAP_MemType_TypeDef IAP_MemType, uint16_t IAP_SectorEraseAddress)
*��������:IAP��������
*��ڲ���:
IAP_MemType_TypeDef:IAP_MemType:IAP��������ROM��
uint32_t:IAP_SectorEraseAddress:IAP��������Ŀ���ַ
uint8_t:WriteTimeLimit:IAP����ʱ��(ֵ����ڵ���0x40)
*���ڲ���:void
**************************************************/
void IAP_SectorErase(IAP_MemType_TypeDef IAP_MemType, uint32_t IAP_SectorEraseAddress,
                     uint8_t WriteTimeLimit)
{
  /* UID�������������������� */
  if((IAP_MemType == IAP_MEMTYPE_UID))
    return;

  IAPADE = IAP_MemType;
  IAPADH = (uint8_t)(IAP_SectorEraseAddress >> 8); //����IAPĿ���ַ��λֵ
  IAPADL = (uint8_t)IAP_SectorEraseAddress;        //����IAPĿ���ַ��λֵ
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
*��������:void IAP_ProgramByte(uint16_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType, uint8_t WriteTimeLimit)
*��������:IAPд��һ���ֽ�
*��ڲ���:
uint32_t:Address:IAP������ַ
uint8_t:Data:д�������
IAP_MemType_TypeDef:IAP_MemType:IAP��������
uint8_t:WriteTimeLimit:IAP����ʱ��(ֵ����ڵ���0x40)
*���ڲ���:
ErrorStatus:д��ɹ�/ʧ��
**************************************************/
ErrorStatus IAP_ProgramByte(uint32_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType,
                            uint8_t WriteTimeLimit)
{
  BitStatus tmpbit;
  uint8_t tmpData;
  /* UID��������д���� */
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

  tmpData = *((uint8_t code*)Address);			//�ض�д�������
  IAPADE = IAP_MEMTYPE_ROM;
  /* �ָ�ԭ�ж��ܿ��� */
  if(tmpbit != RESET)
  {
    enableInterrupts();
  }
  /* �ж�ʵ��д�����ݺ����������Ƿ�һ��*/
  if(Data != tmpData)
    return ERROR;
  else
    return SUCCESS;
}

/**************************************************
*��������:void IAP_ProgramByteArray(uint16_t Address,, uint16_t ArraySize, uint8_t* ByteArray, IAP_MemType_TypeDef IAP_MemType, uint8_t WriteTimeLimit)
*��������:IAPд�볤�ȿ�����ֽ�����
*��ڲ���:
uint32_t:Address:IAP������ַ
uint8_t:ArraySize:��Ҫд������ĳ���
uint8_t*:ByteArray:д�����ݵ�����ָ��
IAP_MemType_TypeDef:IAP_MemType:IAP��������
uint8_t:WriteTimeLimitIAP����ʱ�ޣ�ֵ����ڵ���0x40��
*���ڲ���:
uint8_t:����������д��ɹ��ĳ���
**************************************************/
uint16_t IAP_ProgramByteArray(uint32_t Address, uint16_t ArraySize, uint8_t* ByteArray, IAP_MemType_TypeDef IAP_MemType,
                             uint8_t WriteTimeLimit)
{
  BitStatus tmpbit;
  uint16_t tmpCnt;
  uint8_t tmpData;

  /* UID��������д���� */
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
  /* �ָ�ԭ�ж��ܿ��� */
  if(tmpbit != RESET)
  {
    enableInterrupts();
  }
  /* �ж�ʵ��д�����ݺ����������Ƿ�һ��*/
  if(tmpData != tmpData)
    return ERROR;
  else
    return SUCCESS;
}

/**************************************************
*��������:void IAP_BootLoaderControl(IAP_BTLDType_TypeDef IAP_BTLDType)
*��������:MCU�����λ��������������ã�����ѡ��ΪAPROM/LDROM
*��ڲ���:
IAP_BTLDType_Ty	peDef:IAP_BTLDType:��λ�����������
*���ڲ���:void
**************************************************/
void IAP_BootLoaderControl(IAP_BTLDType_TypeDef IAP_BTLDType)
{
  IAPCTL = (IAPCTL & 0xFB) | IAP_BTLDType;
}
#endif

#if defined(RD8G403)
/**************************************************
*��������:void IAP_SetHoldTime(IAP_HoldTime_TypeDef IAP_HoldTime)
*��������:IAP����CPU Hold Time���ú���
*��ڲ���:
IAP_HoldTime_TypeDef:IAP_HoldTimed:Hold TimeTimeѡ��
*���ڲ���:void
**************************************************/
void IAP_SetHoldTime(IAP_HoldTime_TypeDef
                     IAP_HoldTime)
{
  IAPCTL = IAPCTL & 0XF3 | IAP_HoldTime;
}

/**************************************************
*��������:ErrorStatus IAP_ProgramByte(uint16_t Address, uint8_t Data, IAP_MemType_TypeDef IAP_MemType, uint8_t WriteTimeLimit)
*��������:IAPд��һ���ֽ�
*��ڲ���:
uint16_t:Address:IAP������ַ
uint8_t:Data:д�������
IAP_MemType_TypeDef:IAP_MemType:IAP��������ROM��EEPROM��
��ע��IAP_MEMTYPE_UID������д��������UID����д������Ч
uint8_t:WriteTimeLimit:IAP����ʱ��	(����ֵ)
*���ڲ���:void
**************************************************/
ErrorStatus IAP_ProgramByte(uint32_t Address,
                            uint8_t Data, IAP_MemType_TypeDef IAP_MemType,
                            uint8_t WriteTimeLimit)
{
  BitStatus tmpbit;

  /* UID������������д���� */
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
*��������:uint8_t IAP_ReadByte(uint16_t Address, IAP_MemType_TypeDef IAP_MemType)
*��������:IAP��һ���ֽ�
*��ڲ���:
uint16_t:Address:IAP������ַ
IAP_MemType_TypeDef:FLASH_MemType:IAP��������ROM��UID��EEPROM��
*���ڲ���:uint8_t			�������ֽ�����
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
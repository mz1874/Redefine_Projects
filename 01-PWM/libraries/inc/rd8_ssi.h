//************************************************************
//  Copyright (c) �Ϸ����¶���������޹�˾
//	�ļ�����:			rd8_ssi.h
//	����:					�¶���Ӧ���Ŷ�
//	ģ�鹦��:			BTM�̼��⺯��C�ļ�
//  ����������:	2022��6��10��
// 	�汾: 				V1.000
//  ˵��:
//*************************************************************

#ifndef _rd8_SSI_H_
#define	_rd8_SSI_H_

#include "rd8.h"

#if defined (RD8G403)
typedef enum
{
  SPI_FIRSTBIT_MSB = (uint8_t)0x00, 			   //MSB���ȷ���
  SPI_FIRSTBIT_LSB = (uint8_t)0x04  			   //LSB���ȷ���
} SPI_FirstBit_TypeDef;

typedef enum
{
  SPI_BAUDRATEPRESCALER_4   = (uint8_t)0x00, //SPIʱ������Ϊϵͳʱ�ӳ���4
  SPI_BAUDRATEPRESCALER_8   = (uint8_t)0x01, //SPIʱ������Ϊϵͳʱ�ӳ���8
  SPI_BAUDRATEPRESCALER_16  = (uint8_t)0x02, //SPIʱ������Ϊϵͳʱ�ӳ���16
  SPI_BAUDRATEPRESCALER_32  = (uint8_t)0x03, //SPIʱ������Ϊϵͳʱ�ӳ���32
  SPI_BAUDRATEPRESCALER_64  = (uint8_t)0x04, //SPIʱ������Ϊϵͳʱ�ӳ���64
  SPI_BAUDRATEPRESCALER_128 = (uint8_t)0x05, //SPIʱ������Ϊϵͳʱ�ӳ���128
  SPI_BAUDRATEPRESCALER_256 = (uint8_t)0x06, //SPIʱ������Ϊϵͳʱ�ӳ���256
  SPI_BAUDRATEPRESCALER_512 = (uint8_t)0x07  //SPIʱ������Ϊϵͳʱ�ӳ���512
} SPI_BaudRatePrescaler_TypeDef;

typedef enum
{
  SPI_MODE_MASTER = (uint8_t)0x20, //SPIΪ���豸
  SPI_MODE_SLAVE  = (uint8_t)0x00  //SPIΪ���豸
} SPI_Mode_TypeDef;

typedef enum
{
  SPI_CLOCKPOLARITY_LOW  = (uint8_t)0x00, //SCK�ڿ���״̬��Ϊ�͵�ƽ
  SPI_CLOCKPOLARITY_HIGH = (uint8_t)0x10  //SCK�ڿ���״̬��Ϊ�ߵ�ƽ
} SPI_ClockPolarity_TypeDef;

typedef enum
{
  SPI_CLOCKPHASE_1EDGE = (uint8_t)0x00, //SCK�ĵ�һ�زɼ�����
  SPI_CLOCKPHASE_2EDGE = (uint8_t)0x08  //SCK�ĵڶ��زɼ�����
} SPI_ClockPhase_TypeDef;

typedef enum
{
  //��Ϊ�ӻ�
  TWI_SlaveIdle = 0x00,
  TWI_SlaveReceivedaAddress = 0x01,
  TWI_SlaveReceivedaData = 0x02,
  TWI_SlaveSendData = 0x03,
  TWI_SlaveReceivedaUACK = 0x04,
  TWI_SlaveDisableACK = 0x05,
  TWI_SlaveAddressError = 0x06,

} SSI_TWIState_TypeDef;

typedef enum
{
  SPI_TXE_DISINT = (uint8_t)0x00, //TXEΪ1ʱ���������ж�
  SPI_TXE_ENINT  = (uint8_t)0x01  //TXEΪ1ʱ�������ж�
} SPI_TXE_INT_TypeDef;

typedef enum
{
  UART1_Mode_10B  = 0X00,//UART1����Ϊ10λģʽ
  UART1_Mode_11B  = 0X80 //UART1����Ϊ11λģʽ
} UART1_Mode_TypeDef;

typedef enum
{
  UART1_RX_ENABLE  = 0X10,//UART1�������
  UART1_RX_DISABLE = 0X00 //UART1��ֹ����
} UART1_RX_TypeDef;

typedef enum
{
  SPI_FLAG_SPIF    = (uint8_t)0x80, //SPI���ݴ��ͱ�־λSPIF
  SPI_FLAG_WCOL    = (uint8_t)0x50, //SPIд���ͻ��־λWCOL
  SPI_FLAG_TXE     = (uint8_t)0x08, //SPI���ͻ������ձ�־TXE
  TWI_FLAG_TWIF    = (uint8_t)0x40,	//TWI�жϱ�־λTWIF
  TWI_FLAG_GCA	   = (uint8_t)0x10,	//TWIͨ�õ�ַ��Ӧ��־λGCA
  UART1_FLAG_TI	   = (uint8_t)0x02,	//UART1�����жϱ�־λTI
  UART1_FLAG_RI	   = (uint8_t)0x01	//UART1�����жϱ�־λRI
} SSI_Flag_TypeDef;

typedef enum
{
  SSI_STATE_READY = 0x00,   //׼����־
  SSI_STATE_BUSY = 0x01,    //æµ��־
  SSI_STATE_ERROR = 0x02,   //�����־
  SSI_STATE_TIMEOUT = 0x03,  //��ʱ��־
  SSI_STATE_WAIT = 0x04,   //�ȴ���־
} SSI_StatusTypeDef;

typedef struct __SSI_HandleInfoDef
{
  union
  {
    uint8_t* Size_u8;              //8λ���ݷ��ͻ�����
    uint16_t* Size_u16;           //16λ���ݷ��ͻ�����
  } pTxBuffPtr;
  uint8_t TxXferSize;              //���ݷ�����
  uint8_t TxXferCount;            //���ݷ��ͼ�����
  union
  {
    uint8_t* Size_u8;              //8λ���ݷ��ͻ�����
    uint16_t* Size_u16;           //16λ���ݷ��ͻ�����
  } pRxBuffPtr;
  uint8_t RxXferSize;              //���ݽ�����
  uint8_t RxXferCount;              //���ݽ��ռ�������С
  SSI_StatusTypeDef TxState;      //����״̬
  SSI_StatusTypeDef RxState;      //����״̬
} SSI_HandleInfoDef;

#if defined (RD8G403)
typedef enum
{
  SSI_PinSelection_P10P27P26 = (uint8_t)0x00, 		   //SSI��������ΪP10��P27��P26
  SSI_PinSelection_P21P22P23 = (uint8_t)0x20, 		   //SSI��������ΪP21��P22��P23
  SSI_PinSelection_URATP27 = (uint8_t)0x00,  		   //SSIUART����ΪP27,��RX
  SSI_PinSelection_URATP22 = (uint8_t)0x20  		   //SSIUART����ΪP22,��RX
} SSI_PinSelection_TypeDef;
void SSI_PinSelection(SSI_PinSelection_TypeDef
                      PinSeletion);
#endif

void SSI_DeInit(void);
void SSI_SPI_Init(SPI_FirstBit_TypeDef FirstBit,
                  SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler,
                  SPI_Mode_TypeDef Mode,
                  SPI_ClockPolarity_TypeDef ClockPolarity,
                  SPI_ClockPhase_TypeDef ClockPhase,
                  SPI_TXE_INT_TypeDef SPI_TXE_INT);
void SSI_SPI_Cmd(FunctionalState NewState);
void SSI_SPI_SendData(uint8_t Data);
uint8_t SSI_SPI_ReceiveData(void);

StatusTypeDef SSI_SPI_Receive(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout);
StatusTypeDef SSI_SPI_Transmit(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout);
StatusTypeDef SSI_SPI_TransmitReceive(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pTxData, uint8_t* pRxData, uint8_t Size, uint32_t Timeout);

StatusTypeDef SSI_SPI_IRQHandler(SSI_HandleInfoDef* SSI_HANDLE);
StatusTypeDef SSI_SPI_Receive_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size);
StatusTypeDef SSI_SPI_Transmit_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size);
StatusTypeDef SSI_SPI_TransmitReceive_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pTxData, uint8_t* pRxData, uint8_t Size);

void SSI_TWI_Init(uint8_t TWI_Address);
void SSI_TWI_AcknowledgeConfig(FunctionalState NewState);
void SSI_TWI_GeneralCallCmd(FunctionalState NewState);
FlagStatus SSI_GetTWIStatus(SSI_TWIState_TypeDef SSI_TWIState);
FlagStatus SSI_GetFlagStatus(SSI_Flag_TypeDef SSI_FLAG);
void SSI_TWI_Cmd(FunctionalState NewState);
void SSI_TWI_SendData(uint8_t Data);
uint8_t SSI_TWI_ReceiveData(void);

StatusTypeDef SSI_TWI_Slave_Transmit(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout);
StatusTypeDef SSI_TWI_Slave_Transmit_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size);
StatusTypeDef SSI_TWI_Slave_Transmit_IRQHandler(SSI_HandleInfoDef* SSI_HANDLE);

StatusTypeDef SSI_TWI_Slave_Receive(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout);
StatusTypeDef SSI_TWI_Slave_Receive_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size);
StatusTypeDef SSI_TWI_Slave_Receive_IRQHandler(SSI_HandleInfoDef* SSI_HANDLE);

void SSI_UART1_Init(uint32_t UART1Fsys,
                    uint32_t BaudRate, UART1_Mode_TypeDef Mode,
                    UART1_RX_TypeDef RxMode);
void SSI_UART1_SendData8(uint8_t Data);
uint8_t SSI_UART1_ReceiveData8(void);
void SSI_UART1_SendData9(uint16_t Data);
uint16_t SSI_UART1_ReceiveData9(void);

StatusTypeDef SSI_UART1_Transmit(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout);
StatusTypeDef SSI_UART1_Transmit_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size);
StatusTypeDef SSI_UART1_Transmit_IRQHandler(SSI_HandleInfoDef* SSI_HANDLE);
StatusTypeDef SSI_UART1_Receive(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout);
StatusTypeDef SSI_UART1_Receive_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size);
StatusTypeDef SSI_UART1_Receive_IRQHandler(SSI_HandleInfoDef* SSI_HANDLE);

void SSI_ITConfig(FunctionalState NewState,
                  PriorityStatus Priority);
void SSI_ClearFlag(SSI_Flag_TypeDef SSI_FLAG);
#endif

#endif

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/
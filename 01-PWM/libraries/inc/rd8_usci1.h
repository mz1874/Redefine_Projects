//************************************************************
//  Copyright (c) �Ϸ����¶���������޹�˾
//	�ļ�����: 		rd8_usci1.h
//	����		:
//	ģ�鹦��: 		USCI1�̼��⺯��ͷ�ļ�
//  ����������: 2022��8��19��
// 	�汾: 				V1.1003
//  ˵��:���ļ���������RD8ϵ��оƬ
//*************************************************************

#ifndef _rd8_USCI1_H_
#define _rd8_USCI1_H_

#include "rd8.h"

#define USCI1_UART_BaudRate_FsysDIV12 0X00 //��ģʽ0���ã����ж˿���ϵͳʱ�ӵ�1/12������
#define USCI1_UART_BaudRate_FsysDIV4 0X01  //��ģʽ0���ã����ж˿���ϵͳʱ�ӵ�1/4������

typedef enum
{
  USCI1_Mode_SPI = (uint8_t)0x01, //SPI
  USCI1_Mode_TWI = (uint8_t)0x02, //TWI
  USCI1_Mode_UART = (uint8_t)0x03 //UART
} USCI1_CommunicationMode_TypeDef;

typedef enum
{
  USCI1_SPI_FIRSTBIT_MSB = (uint8_t)0x00, //MSB���ȷ���
  USCI1_SPI_FIRSTBIT_LSB = (uint8_t)0x04  //LSB���ȷ���
} USCI1_SPI_FirstBit_TypeDef;

typedef enum
{
  USCI1_SPI_BAUDRATEPRESCALER_1 = (uint8_t)0x00,  //SPIʱ������Ϊϵͳʱ�ӳ���1
  USCI1_SPI_BAUDRATEPRESCALER_2 = (uint8_t)0x01,  //SPIʱ������Ϊϵͳʱ�ӳ���2
  USCI1_SPI_BAUDRATEPRESCALER_4 = (uint8_t)0x02,  //SPIʱ������Ϊϵͳʱ�ӳ���4
  USCI1_SPI_BAUDRATEPRESCALER_8 = (uint8_t)0x03,  //SPIʱ������Ϊϵͳʱ�ӳ���8
  USCI1_SPI_BAUDRATEPRESCALER_16 = (uint8_t)0x04, //SPIʱ������Ϊϵͳʱ�ӳ���16
  USCI1_SPI_BAUDRATEPRESCALER_32 = (uint8_t)0x05, //SPIʱ������Ϊϵͳʱ�ӳ���32
  USCI1_SPI_BAUDRATEPRESCALER_64 = (uint8_t)0x06, //SPIʱ������Ϊϵͳʱ�ӳ���64
  USCI1_SPI_BAUDRATEPRESCALER_128 = (uint8_t)0x07 //SPIʱ������Ϊϵͳʱ�ӳ���128
} USCI1_SPI_BaudRatePrescaler_TypeDef;

typedef enum
{
  USCI1_SPI_MODE_MASTER = (uint8_t)0x20, //SPIΪ���豸
  USCI1_SPI_MODE_SLAVE = (uint8_t)0x00   //SPIΪ���豸
} USCI1_SPI_Mode_TypeDef;

typedef enum
{
  USCI1_SPI_CLOCKPOLARITY_LOW = (uint8_t)0x00, //SCK�ڿ���״̬��Ϊ�͵�ƽ
  USCI1_SPI_CLOCKPOLARITY_HIGH = (uint8_t)0x10 //SCK�ڿ���״̬��Ϊ�ߵ�ƽ
} USCI1_SPI_ClockPolarity_TypeDef;

typedef enum
{
  USCI1_SPI_CLOCKPHASE_1EDGE = (uint8_t)0x00, //SCK�ĵ�һ�زɼ�����
  USCI1_SPI_CLOCKPHASE_2EDGE = (uint8_t)0x08  //SCK�ĵڶ��زɼ�����
} USCI1_SPI_ClockPhase_TypeDef;

typedef enum
{
  USCI1_SPI_TXE_DISINT = (uint8_t)0x00, //TBIEΪ0ʱ�����������ж�
  USCI1_SPI_TXE_ENINT = (uint8_t)0x01   //TBIEΪ1ʱ���������ж�
} USCI1_SPI_TXE_INT_TypeDef;

typedef enum
{
  USCI1_SPI_DATA8 = (uint8_t)0x00, //SPI 8λ����ģʽ
  USCI1_SPI_DATA16 = (uint8_t)0x02 //SPI 16λ����ģʽ
} USCI1_TransmissionMode_TypeDef;

typedef enum
{
  USCI1_TWI_1024 = (uint8_t)0x00, //TWIͨ������ Fhrc/1024
  USCI1_TWI_512 = (uint8_t)0x01,  //TWIͨ������ Fhrc/512
  USCI1_TWI_256 = (uint8_t)0x02,  //TWIͨ������ Fhrc/256
  USCI1_TWI_128 = (uint8_t)0x03,  //TWIͨ������ Fhrc/128
  USCI1_TWI_64 = (uint8_t)0x04,   //TWIͨ������ Fhrc/64
  USCI1_TWI_32 = (uint8_t)0x05,   //TWIͨ������ Fhrc/32
  USCI1_TWI_16 = (uint8_t)0x06,   //TWIͨ������ Fhrc/16
} USCI1_TWI_MasterCommunicationRate_TypeDef;

typedef enum
{
    USCI1_TWI_SlaveIdle = 0x00,
    USCI1_TWI_SlaveReceivedaAddress = 0x01,
    USCI1_TWI_SlaveReceivedaData = 0x02,
    USCI1_TWI_SlaveSendData = 0x03,
    USCI1_TWI_SlaveReceivedaUACK = 0x04,
    USCI1_TWI_SlaveDisableACK = 0x05,
    USCI1_TWI_SlaveAddressError = 0x06,
    USCI1_TWI_MasterIdle = 0x00,
    USCI1_TWI_MasterSendAddress = 0x01,
    USCI1_TWI_MasterSendData = 0x02,
    USCI1_TWI_MasterReceivedaData = 0x03,
    USCI1_TWI_MasterReceivedaUACK = 0x04,
} USCI1_TWIState_TypeDef;

typedef enum
{
  USCI1_UART_Mode_8B = 0X00,  //UART����Ϊ8λģʽ
  USCI1_UART_Mode_10B = 0X40, //UART����Ϊ10λģʽ
  USCI1_UART_Mode_11B = 0X80  //UART����Ϊ11λģʽ
} USCI1_UART_Mode_TypeDef;

typedef enum
{
  USCI1_UART_RX_ENABLE = 0X10, //UART��������
  USCI1_UART_RX_DISABLE = 0X00 //UART��ֹ����
} USCI1_UART_RX_TypeDef;

typedef enum
{
  USCI1_SPI_FLAG_SPIF = (uint8_t)0x80, //SPI���ݴ��ͱ�־λSPIF
  USCI1_SPI_FLAG_WCOL = (uint8_t)0x50, //SPIд���ͻ��־λWCOL
  USCI1_SPI_FLAG_TXE = (uint8_t)0x08,  //SPI���ͻ������ձ�־TXE
  USCI1_TWI_FLAG_TWIF = (uint8_t)0x40, //TWI�жϱ�־λTWIF
  USCI1_TWI_FLAG_GCA = (uint8_t)0x10,  //TWIͨ�õ�ַ��Ӧ��־λGCA
  USCI1_TWI_FLAG_MSTR = (uint8_t)0x20, //TWI���ӱ�־λMSTR
  USCI1_TWI_FLAG_TXRXnE = (uint8_t)0x80,
  USCI1_UART_FLAG_RI = (uint8_t)0x01, //UART�����жϱ�־λRI
  USCI1_UART_FLAG_TI = (uint8_t)0x02, //UART�����жϱ�־λTI
} USCI1_Flag_TypeDef;

typedef enum
{
  USCI1_TWI_Write = 0x00, //д����
  USCI1_TWI_Read = 0x01,  //������
} USCI1_TWI_RWType;

typedef enum
{
  USCI1_STATE_READY = 0x00,   //׼����־
  USCI1_STATE_BUSY = 0x01,    //æµ��־
  USCI1_STATE_ERROR = 0x02,   //�����־
  USCI1_STATE_TIMEOUT = 0x03,  //��ʱ��־
  USCI1_STATE_WAIT = 0x04,   //�ȴ���־
} USCI1_StatusTypeDef;

typedef struct __USCI1_HandleInfoDef
{
    union
    {
        uint8_t* Size_u8;              //8λ���ݷ��ͻ�����
        uint16_t* Size_u16;           //16λ���ݷ��ͻ�����
    }pTxBuffPtr;
    uint8_t TxXferSize;              //���ݷ�����
    uint8_t TxXferCount;            //���ݷ��ͼ�����
    union
    {
        uint8_t* Size_u8;              //8λ���ݽ��ջ�����
        uint16_t* Size_u16;           //16λ���ݽ��ջ�����
    }pRxBuffPtr;
    uint8_t RxXferSize;              //���ݽ�����
    uint8_t RxXferCount;              //���ݽ��ռ�������С
    USCI1_StatusTypeDef TxState;      //����״̬
    USCI1_StatusTypeDef RxState;      //����״̬
} USCI1_HandleInfoDef;

void USCI1_DeInit(void);
void USCI1_SPI_Init(USCI1_SPI_FirstBit_TypeDef FirstBit,
                    USCI1_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler, USCI1_SPI_Mode_TypeDef Mode,
                    USCI1_SPI_ClockPolarity_TypeDef ClockPolarity, USCI1_SPI_ClockPhase_TypeDef ClockPhase,
                    USCI1_SPI_TXE_INT_TypeDef SPI_TXE_INT, USCI1_TransmissionMode_TypeDef TransmissionMode);
void USCI1_TransmissionMode(USCI1_TransmissionMode_TypeDef TransmissionMode);
void USCI1_SPI_Cmd(FunctionalState NewState);
void USCI1_SPI_SendData_8(uint8_t Data);
uint8_t USCI1_SPI_ReceiveData_8(void);
void USCI1_SPI_SendData_16(uint16_t Data);
uint16_t USCI1_SPI_ReceiveData_16(void);

USCI1_StatusTypeDef USCI1_SPI_Receive(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout);
USCI1_StatusTypeDef USCI1_SPI_Transmit(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout);
USCI1_StatusTypeDef USCI1_SPI_TransmitReceive(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pTxData, uint8_t* pRxData, uint8_t Size, uint32_t Timeout);

USCI1_StatusTypeDef USCI1_SPI_IRQHandler(USCI1_HandleInfoDef* USCI1_HANDLE);
USCI1_StatusTypeDef USCI1_SPI_Receive_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size);
USCI1_StatusTypeDef USCI1_SPI_Transmit_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size);
USCI1_StatusTypeDef USCI1_SPI_TransmitReceive_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pTxData, uint8_t* pRxData, uint8_t Size);


void USCI1_TWI_Slave_Init(uint8_t TWI_Address);
void USCI1_TWI_MasterCommunicationRate(USCI1_TWI_MasterCommunicationRate_TypeDef
                                           TWI_MasterCommunicationRate);
void USCI1_TWI_Start(void);
void USCI1_TWI_MasterModeStop(void);
void USCI1_TWI_SlaveClockExtension(FunctionalState NewState);
void USCI1_TWI_AcknowledgeConfig(FunctionalState NewState);
void USCI1_TWI_GeneralCallCmd(FunctionalState NewState);
FlagStatus USCI1_GetTWIStatus(USCI1_TWIState_TypeDef USCI1_TWIState);
void USCI1_TWI_Cmd(FunctionalState NewState);
void USCI1_TWI_SendData(uint8_t Data);
uint8_t USCI1_TWI_ReceiveData(void);

USCI1_StatusTypeDef USCI1_TWI_Master_Transmit(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t slaveAddr, uint8_t* pData, uint8_t Size, uint32_t Timeout);
USCI1_StatusTypeDef USCI1_TWI_Slave_Transmit(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout);

USCI1_StatusTypeDef USCI1_TWI_Master_Transmit_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t slaveAddr, uint8_t* pData, uint8_t Size);
USCI1_StatusTypeDef USCI1_TWI_Master_Transmit_IRQHandler(USCI1_HandleInfoDef* USCI1_HANDLE);

USCI1_StatusTypeDef USCI1_TWI_Slave_Transmit_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size);
USCI1_StatusTypeDef USCI1_TWI_Slave_Transmit_IRQHandler(USCI1_HandleInfoDef* USCI1_HANDLE);

USCI1_StatusTypeDef USCI1_TWI_Master_Receive(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t slaveAddr, uint8_t* pData, uint8_t Size, uint32_t Timeout);
USCI1_StatusTypeDef USCI1_TWI_Slave_Receive(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout);

USCI1_StatusTypeDef USCI1_TWI_Master_Receive_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t slaveAddr, uint8_t* pData, uint8_t Size);
USCI1_StatusTypeDef USCI1_TWI_Master_Receive_IRQHandler(USCI1_HandleInfoDef* USCI1_HANDLE);

USCI1_StatusTypeDef USCI1_TWI_Slave_Receive_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size);
USCI1_StatusTypeDef USCI1_TWI_Slave_Receive_IRQHandler(USCI1_HandleInfoDef* USCI1_HANDLE);

void USCI1_UART_Init(uint32_t UART1Fsys, uint32_t BaudRate, USCI1_UART_Mode_TypeDef Mode,
                     USCI1_UART_RX_TypeDef RxMode);
void USCI1_UART_SendData8(uint8_t Data);
uint8_t USCI1_UART_ReceiveData8(void);
void USCI1_UART_SendData9(uint16_t Data);
uint16_t USCI1_UART_ReceiveData9(void);

StatusTypeDef USCI1_UART_Transmit(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout);
StatusTypeDef USCI1_UART_Transmit_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size);
StatusTypeDef USCI1_UART_Transmit_IRQHandler(USCI1_HandleInfoDef* USCI1_HANDLE);
StatusTypeDef USCI1_UART_Receive(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout);
StatusTypeDef USCI1_UART_Receive_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size);
StatusTypeDef USCI1_UART_Receive_IRQHandler(USCI1_HandleInfoDef* USCI1_HANDLE);

void USCI1_ITConfig(FunctionalState NewState, PriorityStatus Priority);
FlagStatus USCI1_GetFlagStatus(USCI1_Flag_TypeDef USCI1_FLAG);
void USCI1_ClearFlag(USCI1_Flag_TypeDef USCI1_FLAG);
void USCI1_TWI_SendAddr(uint8_t Addr, USCI1_TWI_RWType RW);
#endif

/******************* (C) COPYRIGHT 2022 SinOne Microelectronics *****END OF FILE****/
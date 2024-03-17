//************************************************************
//  Copyright (c) 合肥市新定义电子有限公司
//	文件名称:			rd8_ssi.h
//	作者:					新定义应用团队
//	模块功能:			BTM固件库函数C文件
//  最后更正日期:	2022年6月10日
// 	版本: 				V1.000
//  说明:
//*************************************************************

#ifndef _rd8_SSI_H_
#define	_rd8_SSI_H_

#include "rd8.h"

#if defined (RD8G403)
typedef enum
{
  SPI_FIRSTBIT_MSB = (uint8_t)0x00, 			   //MSB优先发送
  SPI_FIRSTBIT_LSB = (uint8_t)0x04  			   //LSB优先发送
} SPI_FirstBit_TypeDef;

typedef enum
{
  SPI_BAUDRATEPRESCALER_4   = (uint8_t)0x00, //SPI时钟速率为系统时钟除以4
  SPI_BAUDRATEPRESCALER_8   = (uint8_t)0x01, //SPI时钟速率为系统时钟除以8
  SPI_BAUDRATEPRESCALER_16  = (uint8_t)0x02, //SPI时钟速率为系统时钟除以16
  SPI_BAUDRATEPRESCALER_32  = (uint8_t)0x03, //SPI时钟速率为系统时钟除以32
  SPI_BAUDRATEPRESCALER_64  = (uint8_t)0x04, //SPI时钟速率为系统时钟除以64
  SPI_BAUDRATEPRESCALER_128 = (uint8_t)0x05, //SPI时钟速率为系统时钟除以128
  SPI_BAUDRATEPRESCALER_256 = (uint8_t)0x06, //SPI时钟速率为系统时钟除以256
  SPI_BAUDRATEPRESCALER_512 = (uint8_t)0x07  //SPI时钟速率为系统时钟除以512
} SPI_BaudRatePrescaler_TypeDef;

typedef enum
{
  SPI_MODE_MASTER = (uint8_t)0x20, //SPI为主设备
  SPI_MODE_SLAVE  = (uint8_t)0x00  //SPI为从设备
} SPI_Mode_TypeDef;

typedef enum
{
  SPI_CLOCKPOLARITY_LOW  = (uint8_t)0x00, //SCK在空闲状态下为低电平
  SPI_CLOCKPOLARITY_HIGH = (uint8_t)0x10  //SCK在空闲状态下为高电平
} SPI_ClockPolarity_TypeDef;

typedef enum
{
  SPI_CLOCKPHASE_1EDGE = (uint8_t)0x00, //SCK的第一沿采集数据
  SPI_CLOCKPHASE_2EDGE = (uint8_t)0x08  //SCK的第二沿采集数据
} SPI_ClockPhase_TypeDef;

typedef enum
{
  //作为从机
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
  SPI_TXE_DISINT = (uint8_t)0x00, //TXE为1时不允许发送中断
  SPI_TXE_ENINT  = (uint8_t)0x01  //TXE为1时允许发送中断
} SPI_TXE_INT_TypeDef;

typedef enum
{
  UART1_Mode_10B  = 0X00,//UART1设置为10位模式
  UART1_Mode_11B  = 0X80 //UART1设置为11位模式
} UART1_Mode_TypeDef;

typedef enum
{
  UART1_RX_ENABLE  = 0X10,//UART1允许接收
  UART1_RX_DISABLE = 0X00 //UART1禁止接收
} UART1_RX_TypeDef;

typedef enum
{
  SPI_FLAG_SPIF    = (uint8_t)0x80, //SPI数据传送标志位SPIF
  SPI_FLAG_WCOL    = (uint8_t)0x50, //SPI写入冲突标志位WCOL
  SPI_FLAG_TXE     = (uint8_t)0x08, //SPI发送缓存器空标志TXE
  TWI_FLAG_TWIF    = (uint8_t)0x40,	//TWI中断标志位TWIF
  TWI_FLAG_GCA	   = (uint8_t)0x10,	//TWI通用地址响应标志位GCA
  UART1_FLAG_TI	   = (uint8_t)0x02,	//UART1发送中断标志位TI
  UART1_FLAG_RI	   = (uint8_t)0x01	//UART1接收中断标志位RI
} SSI_Flag_TypeDef;

typedef enum
{
  SSI_STATE_READY = 0x00,   //准备标志
  SSI_STATE_BUSY = 0x01,    //忙碌标志
  SSI_STATE_ERROR = 0x02,   //错误标志
  SSI_STATE_TIMEOUT = 0x03,  //超时标志
  SSI_STATE_WAIT = 0x04,   //等待标志
} SSI_StatusTypeDef;

typedef struct __SSI_HandleInfoDef
{
  union
  {
    uint8_t* Size_u8;              //8位数据发送缓存区
    uint16_t* Size_u16;           //16位数据发送缓存区
  } pTxBuffPtr;
  uint8_t TxXferSize;              //数据发送量
  uint8_t TxXferCount;            //数据发送计数器
  union
  {
    uint8_t* Size_u8;              //8位数据发送缓存区
    uint16_t* Size_u16;           //16位数据发送缓存区
  } pRxBuffPtr;
  uint8_t RxXferSize;              //数据接收量
  uint8_t RxXferCount;              //数据接收计数器大小
  SSI_StatusTypeDef TxState;      //发送状态
  SSI_StatusTypeDef RxState;      //接收状态
} SSI_HandleInfoDef;

#if defined (RD8G403)
typedef enum
{
  SSI_PinSelection_P10P27P26 = (uint8_t)0x00, 		   //SSI共用引脚为P10，P27，P26
  SSI_PinSelection_P21P22P23 = (uint8_t)0x20, 		   //SSI共用引脚为P21，P22，P23
  SSI_PinSelection_URATP27 = (uint8_t)0x00,  		   //SSIUART引脚为P27,无RX
  SSI_PinSelection_URATP22 = (uint8_t)0x20  		   //SSIUART引脚为P22,无RX
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
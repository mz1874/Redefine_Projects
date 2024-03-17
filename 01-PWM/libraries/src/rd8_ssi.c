//************************************************************
//  Copyright (c) 合肥市新定义电子有限公司
//	文件名称:			rd8_ssi.c
//	作者:					新定义应用团队
//	模块功能:			BTM固件库函数C文件
//  最后更正日期:	2022年6月10日
// 	版本: 				V1.000
//  说明:
//*************************************************************

#include "rd8_ssi.h"

#if defined (RD8G403)
/**************************************************
*函数名称:void SSI_DeInit(void)
*函数功能:SSI相关寄存器复位至缺省值
*入口参数:void
*出口参数:void
**************************************************/
void SSI_DeInit(void)
{
  OTCON &= 0X3F;
  SSCON0 = 0X00;
  SSCON1 = 0X00;
  SSCON2 = 0X00;
  SSDAT = 0X00;
  IE1 &= (~0X01);
  IP1 &= (~0X01);
}

#if defined (RD8G403)
/**************************************************
*函数名称:SSI_PinSelection(SSI_PinSelection_TypeDef PinSeletion)
*函数功能:SSI引脚选择
*入口参数:
SSI_PinSelection_TypeDef:PinSeletion:选择SSI引脚为P10P27P26或P21P22P23
*出口参数:void
**************************************************/
void SSI_PinSelection(SSI_PinSelection_TypeDef
                      PinSeletion)
{
  OTCON = OTCON & 0XDF | PinSeletion;
}
#endif

/**************************************************
*函数名称:void SSI_SPI_Init(SPI_FirstBit_TypeDef FirstBit, SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler,SPI_Mode_TypeDef Mode,
							 SPI_ClockPolarity_TypeDef ClockPolarity, SPI_ClockPhase_TypeDef ClockPhase,SPI_TXE_INT_TypeDef SPI_TXE_INT)
*函数功能:SPI初始化配置函数
*入口参数:
SPI_FirstBit_TypeDef:FirstBit:优先传送位选择（MSB/LSB）
SPI_BaudRatePrescaler_TypeDef:BaudRatePrescaler:SPI时钟频率选择
SPI_Mode_TypeDef:Mode:SPI工作模式选择
SPI_ClockPolarity_TypeDef:ClockPolarity:SPI时钟极性选择
SPI_ClockPhase_TypeDef:ClockPhase:SPI时钟相位选择
SPI_TXE_INT_TypeDef:SPI_TXE_INT:发送缓存器中断允许选择
*出口参数:void
**************************************************/
void SSI_SPI_Init(SPI_FirstBit_TypeDef FirstBit,
                  SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler,
                  SPI_Mode_TypeDef Mode,
                  SPI_ClockPolarity_TypeDef ClockPolarity,
                  SPI_ClockPhase_TypeDef ClockPhase,
                  SPI_TXE_INT_TypeDef SPI_TXE_INT)
{
  OTCON = (OTCON & 0X3F) | 0X40;
  SSCON1 = SSCON1 & (~0X05) | FirstBit |
           SPI_TXE_INT;
  SSCON0 = SSCON0 & 0X80 | BaudRatePrescaler | Mode
           | ClockPolarity | ClockPhase;
}

/*****************************************************
*函数名称:void SSI_SPI_Cmd(FunctionalState NewState)
*函数功能:SPI功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
*****************************************************/
void SSI_SPI_Cmd(FunctionalState NewState)
{
  if(NewState != DISABLE)
  {
    SSCON0 |= 0X80;
  }
  else
  {
    SSCON0 &= (~0X80);
  }
}

/*****************************************************
*函数名称:void SSI_SPI_SendData(uint8_t Data)
*函数功能:SPI发送数据
*入口参数:
uint8_t:Data:发送的数据
*出口参数:void
*****************************************************/
void SSI_SPI_SendData(uint8_t Data)
{
  SSDAT = Data;
}

/*****************************************************
*函数名称:uint8_t SSI_SPI_ReceiveData(void)
*函数功能:获得SSDAT中的值
*入口参数:void
*出口参数:
uint8_t:SPI接收到的8位数据
*****************************************************/
uint8_t SSI_SPI_ReceiveData(void)
{
  return SSDAT;
}

/**********************************************************************************************************
*函数名称:StatusTypeDef SSI_SPI_IRQHandler(SSI_HandleInfoDef* SSI_HANDLE)
*函数功能:SPI0 中断处理
*入口参数:
SSI_HandleInfoDef*:SSI_HANDLE:指向包含 SPI0 信息的 SSI_HandleInfoDef 结构体的指针。
*出口参数:
void
**********************************************************************************************************/
StatusTypeDef SSI_SPI_IRQHandler(SSI_HandleInfoDef* SSI_HANDLE)
{
  StatusTypeDef TempStatus = Status_ERROR;

  if(SSI_HANDLE->RxState == SSI_STATE_BUSY)
  {
    /* 当数据没有接收完成 */
    if(SSI_HANDLE->RxXferCount < SSI_HANDLE->RxXferSize)
    {

        *(SSI_HANDLE->pRxBuffPtr.Size_u8 + SSI_HANDLE->RxXferCount) = SSI_SPI_ReceiveData();			//读取16位数据

      TempStatus = Status_BUSY;
      SSI_HANDLE->RxXferCount++;			//接收到数据，计数值加1

      /* 数据接收完成，状态位进行修改 */
      if(SSI_HANDLE->RxXferCount == SSI_HANDLE->RxXferSize)
      {
        SSI_HANDLE->RxState = SSI_STATE_READY;
        TempStatus =  Status_OK;
      }
    }

    if(SSI_HANDLE->TxState == SSI_STATE_BUSY)
    {

      SSI_HANDLE->TxXferCount++;			//数据发送完成，计数值加1
      /* 当数据没有发送完成 */
      if(SSI_HANDLE->TxXferCount < SSI_HANDLE->TxXferSize)
      {

          SSI_SPI_SendData(*(SSI_HANDLE->pTxBuffPtr.Size_u8 + SSI_HANDLE->TxXferCount));			//发送16位数据
        
        TempStatus = Status_BUSY;
      }
      /* 数据发送完成，状态位进行修改  */
      else if(SSI_HANDLE->TxXferCount == SSI_HANDLE->TxXferSize)
      {
        SSI_HANDLE->TxState = SSI_STATE_READY;
        TempStatus = Status_OK;
      }
    }
    /* 当SPI处于主机时，SPI需要发送数据，才能同步接收到数据 */
    else if(SSI_HANDLE->RxXferSize)
    {
      SSI_SPI_SendData(0x00);
    }
  }
  return TempStatus;
}


/**********************************************************************************************************
*函数名称:StatusTypeDef SSI_SPI_Receive(SSI_HandleInfoDef* SSI_HANDLE, uint8_t *pData, uint8_t Size, uint32_t Timeout)
*函数功能:SPI在轮询模式下接收大量数据
*入口参数:
SSI_HandleInfoDef*:SSI_HANDLE:指向包含指定SPI模块的配置信息结构体的指针
uint8_t *:pData:接收数据的存放区
uint16_t:Size:待接收的数据量
uint32_t:Timeout:超时时间
*出口参数:
StatusTypeDef:SSI 状态
**********************************************************************************************************/
StatusTypeDef SSI_SPI_Receive(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
{
  uint32_t TimeoutCnt = 0;

  if(SSI_HANDLE->RxState == SSI_STATE_READY)
  {
    /* 待发送数据长度必须大于0，否则返回错误状态 */
    if(((IE1 & 0x01) != 0) || (Size == 0U))
    {
      return SSI_STATE_ERROR;
    }

    /* SPI作为主机时，接收数据必定跟随发送数据 */
    if((SSCON0 & SPI_MODE_MASTER) != 0)
    {
      return SSI_SPI_TransmitReceive(SSI_HANDLE, pData, pData, Size, Timeout);			//跳转到阻塞模式数据收发函数
    }

    SSI_HANDLE->RxState = SSI_STATE_BUSY;			//发送进程忙碌中
    SSI_ClearFlag(SPI_FLAG_SPIF);			 //接收前清除接收中断标志
    SSI_HANDLE->pRxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
    SSI_HANDLE->RxXferSize = Size;			//更新待发送的数据量
    SSI_HANDLE->RxXferCount = 0;			//发送计数器清零

    while(SSI_HANDLE->RxXferCount < SSI_HANDLE->RxXferSize)
    {
      /* 等待SPI中断标志位置起 */
      if(SSI_GetFlagStatus(SPI_FLAG_SPIF))
      {
          *(SSI_HANDLE->pRxBuffPtr.Size_u8 + SSI_HANDLE->RxXferCount) = SSI_SPI_ReceiveData();			//读取16位数据,并且地址自增
        SSI_ClearFlag(SPI_FLAG_SPIF);				//清除标志位
        SSI_HANDLE->RxXferCount++;	//接收数据量计数加1
        TimeoutCnt = 0;			//超时计数值清零
      }
      else
      {
        /* 超时计数器不断累加，直到超出设定的超时时间 */
        if((TimeoutCnt++) > Timeout)
        {
          if(Timeout == 0)
            return SSI_STATE_TIMEOUT;				//返回超时错误
        }
        WDTCON |= 0x10;          //喂狗函数，防止看门狗复位
      }
    }

    if(SSI_HANDLE->RxXferCount == SSI_HANDLE->RxXferSize)
    {
      SSI_HANDLE->RxState = SSI_STATE_READY;	//接收完成
      return Status_OK;
    }
    else
    {
      SSI_HANDLE->RxState = SSI_STATE_ERROR;//接收错误
      return Status_ERROR;
    }
  }
  else
  {
    return Status_BUSY;//返回忙碌状态
  }
}

/**********************************************************************************************************
*函数名称:StatusTypeDef SSI_SPI_Receive_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t *pData, uint8_t Size)
*函数功能:中断模式接收一定量数据
*入口参数:
SSI_HandleInfoDef*:SSI_HANDLE:指向包含指定SPI模块的配置信息结构体的指针
uint8_t *:pData:接收数据的存放
uint16_t:Size:待接收的数据量
*出口参数:
StatusTypeDef:SSI 状态
**********************************************************************************************************/
StatusTypeDef SSI_SPI_Receive_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size)
{
  /* 检查一个接收进程是否正在进行 */
  if(SSI_HANDLE->RxState == SSI_STATE_READY)
  {
    /* 待发送数据长度必须大于0，否则返回错误状态 */
    if(((IE1 & 0x01) == 0) || (Size == 0U))
    {
      return SSI_STATE_ERROR;
    }

    /* SPI作为主机时，接收数据必定跟随发送数据 */
    if((SSCON0 & SPI_MODE_MASTER) != 0)
    {
      return SSI_SPI_TransmitReceive_IT(SSI_HANDLE, pData, pData, Size);			//跳转到中断模式数据收发函数
    }

    SSI_HANDLE->RxState = SSI_STATE_BUSY;			//状态更新为接收忙碌中
    SSI_ClearFlag(SPI_FLAG_SPIF);			//清除中断标志位
    SSI_HANDLE->pRxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
    SSI_HANDLE->RxXferSize = Size;			//更新待发送的数据量
    SSI_HANDLE->RxXferCount = 0;			//发送计数器清零

    return Status_OK;
  }
  else
  {
    return Status_BUSY;//返回标志位
  }
}

/**********************************************************************************************************
*函数名称:StatusTypeDef SSI_SPI_Transmit(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
*函数功能:SPI在轮询模式下发送大量数据
*入口参数:
SSI_HandleInfoDef*:SSI_HANDLE:指向包含指定SPI模块的配置信息结构体的指针
uint8_t *pData:指向数据缓存的指针。
uint16_t Size:发送数据的大小
uint32_t Timeout:超时时间
*出口参数:
StatusTypeDef:SSI 状态
**********************************************************************************************************/
StatusTypeDef SSI_SPI_Transmit(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
{
  uint32_t TimeoutCnt = 0;
  /* 检查一个发送进程是否正在进行 */
  if(SSI_HANDLE->TxState == SSI_STATE_READY)
  {
    /* 待发送数据长度必须大于0，否则返回错误状态 */
    if(((IE1 & 0x01) != 0) || (Size == 0U))
    {
      return Status_ERROR;
    }

    SSI_HANDLE->TxState = SSI_STATE_BUSY;			//发送进程忙碌中
    SSI_ClearFlag(SPI_FLAG_SPIF);			 //发送前清除标志位
    SSI_HANDLE->pTxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
    SSI_HANDLE->TxXferSize = Size;			//更新待发送的数据量
    SSI_HANDLE->TxXferCount = 0;			//发送计数器清零

    while(SSI_HANDLE->TxXferCount < SSI_HANDLE->TxXferSize)//判断是否接收所有数据
    {

        SSI_SPI_SendData(*(SSI_HANDLE->pTxBuffPtr.Size_u8 + SSI_HANDLE->TxXferCount));			//发送8位数据并且数据地址增加
      while(!SSI_GetFlagStatus(SPI_FLAG_SPIF))			//等待发送完成
      {
        /* 超时计数器不断累加，直到超出设定的超时时间 */
        if(TimeoutCnt++ > Timeout)
        {
          SSI_HANDLE->TxState = SSI_STATE_TIMEOUT;//发送超时
          return Status_TIMEOUT;
        }
        WDTCON |= 0x10;			//喂狗，防止等待时间过长，导致WDT复位
      }

      SSI_ClearFlag(SPI_FLAG_SPIF);				//发送前先清除标志位
      TimeoutCnt = 0;			//超时计数器清零
      SSI_HANDLE->TxXferCount ++;	//发送数据量计数
    }
    if(SSI_HANDLE->TxXferCount == SSI_HANDLE->TxXferSize)
    {
      SSI_HANDLE->TxState = SSI_STATE_READY;	//发送完成
      return Status_OK;
    }
    else
    {
      SSI_HANDLE->TxState = SSI_STATE_ERROR;//发生发送错误
      return Status_ERROR;
    }
  }
  else
  {
    return Status_BUSY;//返回忙碌状态
  }
}

	
/**********************************************************************************************************
*函数名称:StatusTypeDef SSI_SPI_Transmit_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size)
*函数功能:中断模式发送一定量数据
*入口参数:
SSI_HandleInfoDef *SSI_HANDLE:指向包含 SPI0 信息的 SSI_HandleInfoDef 结构体的指针。
uint8_t *pData:指向数据缓存的指针。
uint16_t Size:发送数据的大小
*出口参数:
StatusTypeDef:SSI 状态
**********************************************************************************************************/
StatusTypeDef SSI_SPI_Transmit_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size)
{
  /* 检查一个发送进程是否正在进行 */
  if(SSI_HANDLE->TxState == SSI_STATE_READY)
  {
    /* 没有开启SSI中断或发送数据量大小为0，返回错误 */
    if(((IE1 & 0x01) == 0) || (Size == 0U))
    {
      return Status_ERROR;
    }

    SSI_HANDLE->TxState = SSI_STATE_BUSY;			//发送进程忙碌中
    SSI_ClearFlag(SPI_FLAG_SPIF);			//清除中断标志位
    SSI_HANDLE->pTxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
    SSI_HANDLE->TxXferSize = Size;			//更新待发送的数据量
    SSI_HANDLE->TxXferCount = 0;			//发送计数器置0

    /* 发送第1byte数据 */
      SSI_SPI_SendData(*(SSI_HANDLE->pTxBuffPtr.Size_u8));

    return Status_OK;
  }
  else
  {
    return  Status_BUSY;			//状态位修改为忙碌状态
  }
}
/**********************************************************************************************************
*函数名称:StatusTypeDef SSI_SPI_TransmitReceive(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pTxData, uint8_t* pRxData, uint8_t Size, uint32_t Timeout)
*函数功能:阻塞模式收发一定量数据
*入口参数:
SSI_HandleInfoDef*:SSI_HANDLE:指向包含 SPI0 信息的 SSI_HandleInfoDef 结构体的指针。
*出口参数:
StatusTypeDef:SSI 状态
**********************************************************************************************************/
StatusTypeDef SSI_SPI_TransmitReceive(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pTxData, uint8_t* pRxData, uint8_t Size, uint32_t Timeout)
{
  uint32_t TimeoutCnt = 0;
  /* 检查一个发送进程是否正在进行 */
  if((SSI_HANDLE->TxState == SSI_STATE_READY) && (SSI_HANDLE->RxState == SSI_STATE_READY))
  {

    /* 待发送和接收数据长度必须大于0，否则返回错误状态 */
    if(((IE1 & 0x01) != 0) || (Size == 0U))
    {
      return  Status_ERROR;
    }

    SSI_HANDLE->TxState = SSI_HANDLE->RxState = SSI_STATE_BUSY;			//发送进程忙碌中
    SSI_ClearFlag(SPI_FLAG_SPIF);			//清除中断标志位
    SSI_HANDLE->pTxBuffPtr.Size_u8 = pTxData;       //指向待发送数据的地址
    SSI_HANDLE->pRxBuffPtr.Size_u8 = pRxData;
    SSI_HANDLE->TxXferSize = SSI_HANDLE->RxXferSize = Size;			//更新待发送的数据量
    SSI_HANDLE->TxXferCount = SSI_HANDLE->RxXferCount = 0;			//发送计数器清零

    while(SSI_HANDLE->TxXferCount < SSI_HANDLE->TxXferSize);
    {


      SSI_SPI_SendData(*(SSI_HANDLE->pTxBuffPtr.Size_u8 + SSI_HANDLE->TxXferCount));			//发送16位数据并且地址增加
      while(!SSI_GetFlagStatus(SPI_FLAG_SPIF))			//等待发送完成
      {
        /* 等待时间是否发生了超时 */
        if(TimeoutCnt++ > Timeout)
        {
          return SSI_STATE_TIMEOUT;				//返回超时错误
        }
        WDTCON |= 0x10;			//喂狗，防止等待时间过长，导致WDT复位
      }
      SSI_ClearFlag(SPI_FLAG_SPIF);				//发送前先清除标志位
      *(SSI_HANDLE->pTxBuffPtr.Size_u8 + SSI_HANDLE->TxXferCount) = SSI_SPI_ReceiveData();

      TimeoutCnt = 0;			//超时计数值清零
      SSI_HANDLE->TxXferCount++;			//数据量计数值加1
      SSI_HANDLE->TxXferCount++;			//数据量计数值加1
    }
    if(SSI_HANDLE->TxXferCount == SSI_HANDLE->TxXferSize)
    {
      SSI_HANDLE->TxState = SSI_HANDLE->RxState = SSI_STATE_READY;	//发送完成
      return Status_OK;
    }
    else
    {
      SSI_HANDLE->TxState = SSI_STATE_ERROR;//发生发送错误
      return Status_ERROR;
    }
  }
  else
  {
    return Status_ERROR;
  }

}
/**********************************************************************************************************
*函数名称:StatusTypeDef SSI_SPI_TransmitReceive_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pTxData, uint8_t* pRxData, uint8_t Size)
*函数功能:SPI在中断模式下发送和接收大量数据时，先在main函数中调用此函数
*入口参数:
SSI_HandleInfoDef *SSI_HANDLE:指向包含指定SPI模块的配置信息结构体的指针
uint8_t *:pData:发送和接收数据的存放区
uint16_t:Size:待发送和接收的数据量
*出口参数:
StatusTypeDef:SSI 状态
**********************************************************************************************************/
StatusTypeDef SSI_SPI_TransmitReceive_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pTxData, uint8_t* pRxData, uint8_t Size)
{
  /* 待发送数据长度必须大于0，否则返回错误状态 */
  if((SSI_HANDLE->TxState == SSI_STATE_READY) && (SSI_HANDLE->RxState == SSI_STATE_READY))
  {

    /* 待发送和接收数据长度必须大于0，否则返回错误状态 */
    if(((IE1 & 0x01) == 0) || (Size == 0U))
    {
      return  Status_ERROR;
    }
    SSI_SPI_Cmd(DISABLE);
    SSI_HANDLE->TxState = SSI_HANDLE->RxState = SSI_STATE_BUSY;			//发送进程忙碌中
    SSI_ClearFlag(SPI_FLAG_SPIF);			//清除中断标志位
    SSI_HANDLE->pTxBuffPtr.Size_u8 = pTxData;
    SSI_HANDLE->pRxBuffPtr.Size_u8 = pRxData;			//指向待发送数据的地址
    SSI_HANDLE->TxXferSize = SSI_HANDLE->RxXferSize = Size;			//更新待发送的数据量
    SSI_HANDLE->TxXferCount = SSI_HANDLE->RxXferCount = 0;			//发送计数器清零
    SSI_SPI_Cmd(ENABLE);

    /* 发送第1byte数据 */
    /* SPI处于8位通信模式 */
    SSI_SPI_SendData(*(SSI_HANDLE->pTxBuffPtr.Size_u8));			//发送8位数据

    return  Status_OK;
  }
  else
  {
    return Status_ERROR;
  }
}


/**************************************************
*函数名称:void TWI_Init(uint8_t TWI_Address)
*函数功能:TWI初始化配置函数
*入口参数:
uint8_t:TWI_Address:TWI作为从机时7位从机地址配置
*出口参数:void
**************************************************/
void TWI_Init(uint8_t TWI_Address)
{
  OTCON = OTCON & 0X3F | 0X80;
  SSCON1 = TWI_Address << 1;
}

/**************************************************
*函数名称:void TWI_AcknowledgeConfig(FunctionalState NewState)
*函数功能:TWI接收应答使能函数
*入口参数:
FunctionalState:NewState:接收应答使能/失能选择
*出口参数:void
**************************************************/
void TWI_AcknowledgeConfig(FunctionalState
                               NewState)
{
  if(NewState != DISABLE)
  {
    SSCON0 |= 0X08;
  }
  else
  {
    SSCON0 &= 0XF7;
  }
}

/**************************************************
*函数名称:void TWI_GeneralCallCmd(FunctionalState NewState)
*函数功能:TWI通用地址响应使能函数
*入口参数:
FunctionalState:NewState:通用地址响应使能/失能选择
*出口参数:void
**************************************************/
void TWI_GeneralCallCmd(FunctionalState
                            NewState)
{
  if(NewState != DISABLE)
  {
    SSCON1 |= 0X01;
  }
  else
  {
    SSCON1 &= 0XFE;
  }
}

/**************************************************
*函数名称:FlagStatus SSI_GetTWIStatus(SSI_TWIState_TypeDef SSI_TWIState)
*函数功能:获取TWI状态机
*入口参数:
SSI_TWIState_TypeDef:SSI_TWIState:TWI状态机状态
*出口参数:void
**************************************************/
FlagStatus SSI_GetTWIStatus(SSI_TWIState_TypeDef SSI_TWIState)
{
  if((SSCON0 & 0x07) == SSI_TWIState)
    return SET;
  else
    return RESET;
}

/*****************************************************
*函数名称:void TWI_Cmd(FunctionalState NewState)
*函数功能:TWI功能开关函数
*入口参数:FunctionalState NewState	功能启动/关闭选择
*出口参数:void
*****************************************************/
void TWI_Cmd(FunctionalState NewState)
{
  if(NewState != DISABLE)
  {
    SSCON0 |= 0X80;
  }
  else
  {
    SSCON0 &= (~0X80);
  }
}

/*****************************************************
*函数名称:void TWI_SendData(uint8_t Data)
*函数功能:TWI发送数据
*入口参数:
uint8_t:Data:发送的数据
*出口参数:void
*****************************************************/
void TWI_SendData(uint8_t Data)
{
  SSDAT = Data;
}

/*****************************************************
*函数名称:uint8_t TWI_ReceiveData(void)
*函数功能:获得SSDAT中的值
*入口参数:void
*出口参数:
uint8_t:TWI接收到的8位数据
*****************************************************/
uint8_t TWI_ReceiveData(void)
{
  return SSDAT;
}

/*****************************************************
*函数名称：StatusTypeDef TWI_Wait_TWIF(SSI_HandleInfoDef* SSI_HANDLE,uint32_t Timeout)
*函数功能：等待TWIF置起
*入口参数：
SSI_HandleInfoDef*:SSI_HANDLE:指针指向SSI数据信息存放区
uint32_t:Timeout:超时时间设置
*出口参数：StatusTypeDef:函数执行状态
*****************************************************/
StatusTypeDef TWI_Wait_TWIF(SSI_HandleInfoDef* SSI_HANDLE, uint32_t Timeout)
{
  uint32_t TimeoutCnt = 0;
  while(!(SSI_GetFlagStatus(TWI_FLAG_TWIF)))			//等待启动信号发送完毕
  {
    TimeoutCnt++;
    if(TimeoutCnt > Timeout)
    {
      /* 超时更新状态 */
      if(SSI_HANDLE->TxState == SSI_STATE_BUSY)
        SSI_HANDLE->TxState = SSI_STATE_TIMEOUT;
      if(SSI_HANDLE->RxState == SSI_STATE_BUSY)
        SSI_HANDLE->RxState = SSI_STATE_TIMEOUT;
      return Status_TIMEOUT;
    }
  }
  SSI_ClearFlag(TWI_FLAG_TWIF);			//清除标志位
  return Status_OK;
}

/*****************************************************
*函数名称:StatusTypeDef TWI_Slave_Transmit(SSI_HandleInfoDef* SSI_HANDLE, uint32_t Timeout)
*函数功能:发送8位数据时，从机轮询模式下发送大量数据
* 注：默认开启时钟延长模式
*入口参数:
SSI_HandleInfoDef*:SSI_HANDLE:指针指向SSI数据信息存放区
uint8_t*:pData	指针指向存储区
uint32_t:Size:存储数据长度
uint32_t:Timeout:超时时间设置
*出口参数:
StatusTypeDef:函数执行状态
*****************************************************/
StatusTypeDef TWI_Slave_Transmit(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
{
  /* 检查一个发送进程是否正在进行 */
  if(SSI_HANDLE->TxState == SSI_STATE_READY)
  {
    /* 待发送数据长度必须大于0，否则返回错误状态 */
    if((IE1 & 0x01 != 0) || (Size == 0U))
    {
      return Status_ERROR;
    }
    else
    {
      SSI_HANDLE->TxState = SSI_STATE_BUSY;			//发送进程忙碌中
      SSI_ClearFlag(TWI_FLAG_TWIF);			 //发送前清除标志位
      SSI_HANDLE->pTxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
      SSI_HANDLE->TxXferSize = Size;			//更新待发送的数据量
      SSI_HANDLE->TxXferCount = 0;			//发送计数器清零

      
      TWI_AcknowledgeConfig(ENABLE);         //开启AA使能位
      if(TWI_Wait_TWIF(SSI_HANDLE, Timeout) == Status_TIMEOUT)            //等待地址匹配
      {
        TWI_AcknowledgeConfig(DISABLE);            //关闭AA使能
        return Status_TIMEOUT;
      }

      do
      {
        if(SSI_GetTWIStatus(TWI_SlaveSendData) == SET)           //检测状态机状态
        {

          SSCON2 = *(SSI_HANDLE->pTxBuffPtr.Size_u8 + SSI_HANDLE->TxXferCount);             //TWI发送数据

          if(TWI_Wait_TWIF(SSI_HANDLE, Timeout) == Status_TIMEOUT)             //等待启动信号发送完毕
          {
            TWI_AcknowledgeConfig(DISABLE);            //关闭AA使能
            return Status_TIMEOUT;
          }
          SSI_HANDLE->TxXferCount++;

          if(SSI_HANDLE->TxXferCount == SSI_HANDLE->TxXferSize - 1)

            TWI_AcknowledgeConfig(DISABLE);            //关闭AA使能

        }
        else if(SSI_GetTWIStatus(TWI_SlaveDisableACK) == SET)
        {

          SSI_HANDLE->TxXferCount++;
        }
        else
        {
          SSI_HANDLE->TxState = SSI_STATE_ERROR;
          return Status_ERROR;
        }
      }
      while(SSI_HANDLE->TxXferCount < SSI_HANDLE->TxXferSize);

      if(SSI_GetTWIStatus(TWI_SlaveDisableACK) == RESET)           //检测状态机状态
      {
        SSI_HANDLE->TxState = SSI_STATE_ERROR;
        return Status_ERROR;
      }

      if(SSI_HANDLE->TxXferCount == SSI_HANDLE->TxXferSize)
      {
        SSI_HANDLE->TxState = SSI_STATE_READY;	//发送完成
        return Status_OK;
      }
      else
      {
        SSI_HANDLE->TxState = SSI_STATE_ERROR;//发生发送错误
        return Status_ERROR;
      }
    }
  }
  else
  {
    return Status_BUSY;
  }
}

/*****************************************************
*函数名称:StatusTypeDef TWI_Slave_Transmit_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size)
*函数功能:从机使用中断模式下发送大量数据时，先在main函数中调用此函数
*入口参数:
SSI_HandleInfoDef*:SSI_HANDLE:指针指向SSI数据信息存放区
uint8_t*:pData 指针指向存储区
uint32_t:Size:存储数据长度
*出口参数:
StatusTypeDef:函数执行状态
*****************************************************/
StatusTypeDef TWI_Slave_Transmit_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size)
{
  /* 检查一个发送进程是否正在进行 */
  if(SSI_HANDLE->TxState == SSI_STATE_READY)
  {
    /* 待发送数据长度必须大于0，否则返回错误状态 */
    if(((IE1 & 0x01) == 0) || (Size == 0U))
    {
      return Status_ERROR;
    }
    else
    {
      
      TWI_AcknowledgeConfig(DISABLE);         //开启AA
      SSI_ClearFlag(TWI_FLAG_TWIF);			 //发送前清除标志位
      
      SSI_HANDLE->TxState = SSI_STATE_WAIT;			//发送进程忙碌中
      SSI_HANDLE->pTxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
      SSI_HANDLE->TxXferSize = Size;			//更新待发送的数据量
      SSI_HANDLE->TxXferCount = 0;			//发送计数器清零

      TWI_AcknowledgeConfig(ENABLE);         //开启AA

      return Status_OK;;
    }
  }
  else
  {
    return Status_ERROR;
  }
}

/*****************************************************
*函数名称:StatusTypeDef TWI_Slave_Transmit_IRQHandler(SSI_HandleInfoDef *SSI_HANDLE)
*函数功能:发送8位数据时，从机中断模式下发送大量数据
*入口参数:
SSI_HandleInfoDef*:SSI_HANDLE:指针指向SSI数据信息存放区
*出口参数:
StatusTypeDef:函数执行状态
*****************************************************/
StatusTypeDef TWI_Slave_Transmit_IRQHandler(SSI_HandleInfoDef* SSI_HANDLE)
{
  if(SSI_HANDLE->TxState == SSI_STATE_BUSY)
  {

    if(SSI_GetTWIStatus(TWI_SlaveSendData) == SET)
    {
      if(SSI_HANDLE->TxXferCount < SSI_HANDLE->TxXferSize)
      {
        SSI_HANDLE->TxXferCount++;			//第一次中断是接受到地址了
        SSCON2 = *(SSI_HANDLE->pTxBuffPtr.Size_u8 + SSI_HANDLE->TxXferCount);
        if(SSI_HANDLE->TxXferCount == SSI_HANDLE->TxXferSize - 1)
        {
          TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
        }
        return Status_BUSY;
      }
      else
      {
        TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
        SSI_HANDLE->TxState = SSI_STATE_ERROR;
        return Status_ERROR;
      }
    }
    /*
    1.但数据传输过程中，其他程序修改了AA控制位
    2.接收到主机回来的UACK */
    else if((SSI_GetTWIStatus(TWI_SlaveDisableACK) == SET) || (SSI_GetTWIStatus(TWI_SlaveReceivedaUACK) == SET))
    {
      TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
		 SSI_HANDLE->TxXferCount++;
      if(SSI_HANDLE->TxXferCount == SSI_HANDLE->TxXferSize)			//所有数据已发送
      {
        SSI_HANDLE->TxState = SSI_STATE_READY;
        return Status_OK;
      }
      else
      {
        SSI_HANDLE->TxState = SSI_STATE_ERROR;
        return Status_ERROR;
      }
    }
    else
    {
      TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
      /* 以下情况未发送过程出错
      1.数据发送后接受到UACK
      2.TWI不是工作在从机发送状态 */
      SSI_HANDLE->TxState = SSI_STATE_ERROR;
      return Status_ERROR;
    }
  }
  else if(SSI_HANDLE->TxState == SSI_STATE_WAIT)
  {
    if(SSI_GetTWIStatus(TWI_SlaveSendData) == SET)
    {
      SSCON2 = *(SSI_HANDLE->pTxBuffPtr.Size_u8 + SSI_HANDLE->TxXferCount);
      SSI_HANDLE->TxState = SSI_STATE_BUSY;
    }
    return Status_BUSY;
  }
  else
  {
    return Status_ERROR;//返回标志位
  }
}


/*****************************************************
*函数名称:StatusTypeDef TWI_Slave_Receive(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
*函数功能:接收8位数据时，从机轮询模式下接收大量数据
*入口参数:
SSI_HandleInfoDef*:SSI_HANDLE:指针指向SSI数据信息存放区
uint8_t*:pData 指针指向存储区
uint32_t:Size:存储数据长度
uint32_t:Timeout:超时时间设置
*出口参数:
StatusTypeDef:函数执行状态
*****************************************************/
StatusTypeDef TWI_Slave_Receive(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
{
  if(SSI_HANDLE->RxState == SSI_STATE_READY)
  {
    /* 待发送数据长度必须大于0，否则返回错误状态 */
    if((IE1 & 0x01 != 0) || (Size == 0U))
    {
      return Status_ERROR;
    }

    SSI_HANDLE->RxState = SSI_STATE_BUSY;			//发送进程忙碌中
    SSI_ClearFlag(TWI_FLAG_TWIF);			 //发送前清除标志位
    TWI_AcknowledgeConfig(ENABLE);         //开启AA使能位
    SSI_HANDLE->pRxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
    SSI_HANDLE->RxXferSize = Size;			//更新待发送的数据量
    SSI_HANDLE->RxXferCount = 0;			//发送计数器清零

    /* 接收地址工程 */
    if(TWI_Wait_TWIF(SSI_HANDLE, Timeout) == Status_TIMEOUT)            //等待信号发送完毕
    {
      /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
		 TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
      return Status_TIMEOUT;
    }

    if(SSI_GetTWIStatus(TWI_SlaveReceivedaData) == RESET)           //检测状态机状态
    {
      SSI_HANDLE->RxState = SSI_STATE_ERROR;
      /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
		 TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
      return Status_ERROR;
    }

    /* 接收数据过程 */
    do
    {
      if(TWI_Wait_TWIF(SSI_HANDLE, Timeout) == Status_TIMEOUT)            //等待启动信号发送完毕
      {
        return Status_TIMEOUT;
      }

      if(SSI_GetTWIStatus(TWI_SlaveReceivedaData) == SET)           //检测状态机状态
      {
        *(SSI_HANDLE->pRxBuffPtr.Size_u8 + SSI_HANDLE->RxXferCount) = SSCON2;             //TWI接收数据
        SSI_HANDLE->RxXferCount++;
        if(SSI_HANDLE->RxXferCount == SSI_HANDLE->RxXferSize - 1)
          TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位,回主机UAC
      }
      else if(SSI_GetTWIStatus(TWI_SlaveIdle) == SET)
      {
        if(SSI_HANDLE->RxXferCount == SSI_HANDLE->RxXferSize - 1)
        {
          *(SSI_HANDLE->pRxBuffPtr.Size_u8 + SSI_HANDLE->RxXferCount) = SSCON2;
          SSI_HANDLE->RxXferCount++;
        }
        else
        {
          SSI_HANDLE->RxState = SSI_STATE_ERROR;
          TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
          return Status_ERROR;
        }
      }
      else
      {
        SSI_HANDLE->RxState = SSI_STATE_ERROR;
        TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
        return Status_ERROR;
      }

    }
    while(SSI_HANDLE->RxXferCount < SSI_HANDLE->RxXferSize);

    if(SSI_HANDLE->RxXferCount == SSI_HANDLE->RxXferSize)
    {
      SSI_HANDLE->RxState = SSI_STATE_READY;	//发送完成
      return Status_OK;
    }
    else
    {
      SSI_HANDLE->RxState = SSI_STATE_ERROR;//发生发送错误
      return Status_ERROR;
    }
  }
  else
  {
    return Status_BUSY;
  }
}


/*****************************************************
*函数名称:void TWI_Slave_Receive_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size))
*函数功能:从机使用中断模式下接收大量数据时，先在main函数中调用此函数
*入口参数:
SSI_HandleInfoDef*:SSI_HANDLE:指针指向SSI数据信息存放区
uint8_t*:pData 指针指向存储区
uint32_t:Size:存储数据长度
*出口参数:
StatusTypeDef:函数执行状态
*****************************************************/
StatusTypeDef TWI_Slave_Receive_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size)
{
  if(SSI_HANDLE->RxState == SSI_STATE_READY)
  {
    /* 待发送数据长度必须大于0，否则返回错误状态 */
    if(((IE1 & 0x01) == 0) || (Size == 0U))
    {
      return Status_ERROR;
    }
    
    TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
    SSI_ClearFlag(TWI_FLAG_TWIF);			 //发送前清除标志位
    SSI_HANDLE->RxState = SSI_STATE_WAIT;			//发送进程忙碌中
    SSI_HANDLE->pRxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
    SSI_HANDLE->RxXferSize = Size;			//更新待发送的数据量
    SSI_HANDLE->RxXferCount = 0;			//发送计数器清零
    TWI_AcknowledgeConfig(ENABLE);         //开启AA使能位

    return Status_OK;
  }
  else
  {
    return Status_BUSY;
  }
}

/*****************************************************
*函数名称:StatusTypeDef TWI_Slave_Receive_IRQHandler(SSI_HandleInfoDef* SSI_HANDLE)
*函数功能:接收8位数据时，从机中断模式下接收大量数据
*入口参数:
SSI_HandleInfoDef:*SSI_HANDLE 指针指向SSI数据信息存放区
*出口参数:
StatusTypeDef:函数执行状态
*****************************************************/
StatusTypeDef TWI_Slave_Receive_IRQHandler(SSI_HandleInfoDef* SSI_HANDLE)
{
  if(SSI_HANDLE->RxState == SSI_STATE_BUSY)
  {
    if(SSI_GetTWIStatus(TWI_SlaveReceivedaData) == SET)           //检测状态机状态
    {
      if(SSI_HANDLE->RxXferCount < SSI_HANDLE->RxXferSize)
      {
        *(SSI_HANDLE->pRxBuffPtr.Size_u8 + SSI_HANDLE->RxXferCount) = SSCON2;             //TWI发送数据
        SSI_HANDLE->RxXferCount++;
        if(SSI_HANDLE->RxXferCount == SSI_HANDLE->RxXferSize - 1)
        {
          TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位,回主机UACK
        }
      }
      else
      {
        TWI_AcknowledgeConfig(DISABLE);
        return Status_ERROR;
      }
      return Status_BUSY;
    }
    else if(SSI_GetTWIStatus(TWI_SlaveIdle) == SET)
    {
      if(SSI_HANDLE->RxXferCount == SSI_HANDLE->RxXferSize - 1)
      {
        *(SSI_HANDLE->pRxBuffPtr.Size_u8 + SSI_HANDLE->RxXferCount) = SSCON2;
        SSI_HANDLE->RxXferCount++;
        TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位,回主机UACK
        SSI_HANDLE->RxState = SSI_STATE_READY;
        return Status_OK;
      }
      else
      {
        TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
        SSI_HANDLE->RxState = SSI_STATE_ERROR;
        return Status_ERROR;
      }
    }
    else
    {
      SSI_HANDLE->RxState = SSI_STATE_ERROR;
      TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
      return Status_ERROR;
    }
  }
  else if(SSI_HANDLE->RxState == SSI_STATE_WAIT)
  {
    SSI_HANDLE->RxState = SSI_STATE_BUSY;
    return Status_BUSY;
  }
  else
  {
    return Status_ERROR;
  }
}

/**************************************************
*函数名称:void SSI_UART1_Init(uint32_t UART1Fsys, uint32_t BaudRate, UART1_Mode_TypeDef Mode, UART1_RX_TypeDef RxMode)
*函数功能:UART1初始化配置函数
*入口参数:
uint32_t:UART1Fsys:系统时钟频率
uint32_t:BaudRate:波特率
UART1_Mode_TypeDef:Mode:UART1工作模式
UART1_RX_TypeDef:RxMode:接收允许选择
*出口参数:void
**************************************************/
void SSI_UART1_Init(uint32_t UART1Fsys,
                    uint32_t BaudRate, UART1_Mode_TypeDef Mode,
                    UART1_RX_TypeDef RxMode)
{

  OTCON |= 0xC0;
  SSCON0 = SSCON0 & 0X0F | Mode | RxMode;
  SSCON2 = UART1Fsys / BaudRate / 256;
  SSCON1 = UART1Fsys / BaudRate % 256;
}

/*****************************************************
*函数名称:void SSI_UART1_SendData8(uint8_t Data)
*函数功能:UART1发送8位数据
*入口参数:
uint8_t:Data:发送的数据
*出口参数:void
*****************************************************/
void SSI_UART1_SendData8(uint8_t Data)
{
  SSDAT = Data;
}

/*****************************************************
*函数名称:uint8_t SSI_UART1_ReceiveData8(void)
*函数功能:获得SSDAT中的值
*入口参数:void
*出口参数:
uint8_t:UART接收到的8位数据
*****************************************************/
uint8_t SSI_UART1_ReceiveData8(void)
{
  return SSDAT;
}

/*****************************************************
*函数名称:void SSI_UART1_SendData9(uint16_t Data)
*函数功能:UART1发送9位数据
*入口参数:
uint16_t:Data:发送的数据
*出口参数:void
*****************************************************/
void SSI_UART1_SendData9(uint16_t Data)
{
  uint8_t Data_9Bit;
  Data_9Bit = (Data >> 8);

  if(Data_9Bit)
  {
    SSCON0	|= 0x08;
  }
  else
  {
    SSCON0	&= 0xf7;
  }

  SSDAT = (uint8_t)Data;
}

/*****************************************************
*函数名称:uint16_t SSI_UART1_ReceiveData9(void)
*函数功能:获得SSDAT中的值及第九位的值
*入口参数:void
*出口参数:
uint16_t:接收到的数据
*****************************************************/
uint16_t SSI_UART1_ReceiveData9(void)
{
  uint16_t Data9;
  Data9 =  SSDAT + ((uint16_t)(SSCON0 & 0X04) << 6);
  SSCON0 &= 0XFB;
  return Data9;
}

/*****************************************************
*函数名称:StatusTypeDef  SSI_UART_Transmit(SSI_HandleInfoDef* SSI_HANDLE, uint8_t *pData, uint8_t Size, uint32_t Timeout)
*函数功能:UART在轮询模式下发送大量数据
*入口参数:
SSI_HandleInfoDef*:SSI_HANDLE:指针指向UART数据信息存放区
uint8_t *:pData:待发送数据
uint16_t:Size:待发送的数据量
uint32_t:Timeout:超时时间设置
*出口参数:
StatusTypeDef:函数执行状态
*****************************************************/
StatusTypeDef SSI_UART_Transmit(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
{
  uint32_t delaytime = 0;
  /* 检查一个发送进程是否正在进行 */
  if(SSI_HANDLE->TxState == SSI_STATE_READY)
  {
    /* 检查发送数据量是否为0 */
    if((IE1 & 0x01 != 0) || (Size == 0U))
    {
      return  Status_ERROR;
    }

    SSI_HANDLE->TxState = SSI_STATE_BUSY;			//发送进程忙碌中
    SSI_ClearFlag(UART1_FLAG_TI); //发送前清除发送中断标志，写1/写0清零
    SSI_HANDLE->pTxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
    SSI_HANDLE->TxXferSize = Size;			//更新待发送的数据量
    SSI_HANDLE->TxXferCount = 0;			//发送计数器清零

    while(SSI_HANDLE->TxXferCount < SSI_HANDLE->TxXferSize)//判断是否接收所有数据
    {
      if((SSCON0 & 0xC0) == UART1_Mode_11B)
      {
        /* 发送9位数据 */
        SSI_UART1_SendData9(*(SSI_HANDLE->pTxBuffPtr.Size_u16 + SSI_HANDLE->TxXferCount));
      }
      else
      {
        /* 发送8位数据 */
        SSI_UART1_SendData8(*(SSI_HANDLE->pTxBuffPtr.Size_u8 + SSI_HANDLE->TxXferCount));
      }

      /* 等待发送完成 */
      delaytime = 0;
      while(!(SSCON0 & 0x02))
      {
        if(delaytime++ > Timeout)
        {
          SSI_HANDLE->TxState = SSI_STATE_TIMEOUT;//发送超时
          return Status_TIMEOUT;
        }
      }

      SSI_ClearFlag(UART1_FLAG_TI); //发送中断标志清除，写1/写0清零
      SSI_HANDLE->TxXferCount ++;	//发送数据量计数
    }

    if(SSI_HANDLE->TxXferCount == SSI_HANDLE->TxXferSize)
    {
      SSI_HANDLE->TxState = SSI_STATE_READY;	//发送完成
      return Status_OK;
    }
    else
    {
      SSI_HANDLE->TxState = SSI_STATE_ERROR;//发生发送错误
      return Status_ERROR;
    }
  }
  else
  {
    return Status_BUSY;//返回标志位
  }
}


/*****************************************************
*函数名称:StatusTypeDef SSI_UART_Transmit_IT(SSI_HandleInfoDef *SSI_HANDLE, uint8_t *pData, uint8_t Size)
*函数功能:UART在中断模式下发送大量数据时，先在main函数中调用此函数
*入口参数:
SSI_HandleInfoDef*:SSI_HANDLE:指针指向UART数据信息存放区
uint8_t *:pData:待发送数据
uint16_t:Size:待发送的数据量
*出口参数:
StatusTypeDef:函数执行状态
*****************************************************/
StatusTypeDef SSI_UART_Transmit_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size)
{
  /* 检查一个发送进程是否正在进行 */
  if(SSI_HANDLE->TxState == SSI_STATE_READY)
  {
    /* 没有开启SSI中断或发送数据量大小为0，返回错误 */
    if(((IE1 & 0x01) == 0) || (Size == 0U))
    {
      return Status_ERROR;
    }

    SSI_HANDLE->TxState = SSI_STATE_BUSY;
    SSI_HANDLE->pTxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
    SSI_HANDLE->TxXferSize = Size;			//更新待发送的数据量
    SSI_HANDLE->TxXferCount = 0;			//发送计数器清零

    /* 发送第1帧数据 */
    if((SSCON0 & 0xC0) == UART1_Mode_11B)
    {
      /* 发送9位数据 */
      SSI_UART1_SendData9(*(SSI_HANDLE->pTxBuffPtr.Size_u16 + SSI_HANDLE->TxXferCount));
    }
    else
    {
      /* 发送8位数据 */
      SSI_UART1_SendData8(*(SSI_HANDLE->pTxBuffPtr.Size_u8 + SSI_HANDLE->TxXferCount));
    }
    return Status_OK;
  }
  else
  {
    return Status_BUSY;//返回标志位
  }
}

/*****************************************************
*函数名称:StatusTypeDef  SSI_UART_Transmit_IRQHandler(SSI_HandleInfoDef *SSI_HANDLE)
*函数功能:UART在中断模式下发送大量数据时，在中断服务函数中调用
*	注：该函数调用需要判断中断标志位是否置起
*入口参数:
SSI_HandleInfoDef:*SSI_HANDLE:指针指向UART数据信息存放区
*出口参数:
StatusTypeDef:函数执行状态
*****************************************************/
StatusTypeDef SSI_UART_Transmit_IRQHandler(SSI_HandleInfoDef* SSI_HANDLE)
{
  /* 处于发送线程 */
  if(SSI_HANDLE->TxState == SSI_STATE_BUSY)
  {
    SSI_HANDLE->TxXferCount++;
    /* 判断上一次发送是否是最后一次 */
    if(SSI_HANDLE->TxXferCount < SSI_HANDLE->TxXferSize)
    {
      /* 待发送数据量未为0，继续发送 */
      if((SSCON0 & 0xC0) == UART1_Mode_11B)
      {
        /* 发送9位数据 */
        SSI_UART1_SendData9(*(SSI_HANDLE->pTxBuffPtr.Size_u16 + SSI_HANDLE->TxXferCount));
      }
      else
      {
        /* 发送8位数据 */
        SSI_UART1_SendData8(*(SSI_HANDLE->pTxBuffPtr.Size_u8 + SSI_HANDLE->TxXferCount));
      }
      return Status_BUSY;
    }
    else if(SSI_HANDLE->TxXferCount == SSI_HANDLE->TxXferSize)
    {
      /* 发送完成 */
      SSI_HANDLE->TxState = SSI_STATE_READY;
      return Status_OK;
    }
    else
    {
      /* 发送数据量为0时还发送数据，返回错误 */
      SSI_HANDLE->TxState = SSI_STATE_ERROR;
      return Status_ERROR;
    }
  }
  else
  {
    return Status_BUSY;
  }
}

/*****************************************************
*函数名称:StatusTypeDef SSI_UART_Receive(SSI_HandleInfoDef* SSI_HANDLE, uint8_t *pData, uint8_t Size, uint32_t Timeout)
*函数功能:UART在轮询模式下接收大量数据
*入口参数:
SSI_SSI_HANDLEInfoDef*:SSI_HANDLE:指针指向SSI_UART数据信息存放区
uint8_t *:pData:接收数据的存放区
uint16_t:Size:待接收的数据量
uint32_t:Timeout:超时时间设置
*出口参数:
StatusTypeDef:函数执行状态
*****************************************************/
StatusTypeDef SSI_UART_Receive(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
{
  uint32_t delaytime = 0;
  /* 检查接收进程正在运行 */
  if(SSI_HANDLE->RxState == SSI_STATE_READY)
  {
    /* 检查接收数据量大小和是否开启接收使能 */
    if((IE1 & 0x01 != 0) || (Size == 0U) || ((SSCON0 & 0x10) != UART1_RX_ENABLE))
    {
      return  Status_ERROR;
    }

    SSI_HANDLE->RxState = SSI_STATE_BUSY;			//发送进程忙碌中
    SSI_ClearFlag(UART1_FLAG_RI);			 //接收前清除接收中断标志
    SSI_HANDLE->pRxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
    SSI_HANDLE->RxXferSize = Size;			//更新待发送的数据量
    SSI_HANDLE->RxXferCount = 0;			//发送计数器清零

    while(SSI_HANDLE->RxXferCount < SSI_HANDLE->RxXferSize) //判断是否接收所有数据
    {
      if(SSI_GetFlagStatus(UART1_FLAG_RI)) //判断接收标志位
      {
        SSI_ClearFlag(UART1_FLAG_RI);			//接收标志位清零

        /* 待接收数据量未为0，继续发送 */
        if((SSCON0 & 0xC0) == UART1_Mode_11B)
        {
          /* 接收9位数据 */
          *(SSI_HANDLE->pRxBuffPtr.Size_u16 + SSI_HANDLE->RxXferCount) = SSI_UART1_ReceiveData9();
        }
        else
        {
          /* 接收8位数据 */
          *(SSI_HANDLE->pRxBuffPtr.Size_u8 + SSI_HANDLE->RxXferCount) = SSI_UART1_ReceiveData8();
        }

        SSI_HANDLE->RxXferCount++;	//接收数据量计数
        delaytime = 0;//收到数据，超时计数清零
      }
      if(delaytime++ > Timeout)//计时溢出
      {
        SSI_HANDLE->RxState = SSI_STATE_TIMEOUT;//发送超时
        return Status_TIMEOUT;
      }
    }

    if(SSI_HANDLE->RxXferCount == SSI_HANDLE->RxXferSize)
    {
      SSI_HANDLE->RxState = SSI_STATE_READY;	//发送完成
      return Status_OK;
    }
    else
    {
      SSI_HANDLE->RxState = SSI_STATE_ERROR;//发生发送错误
      return Status_ERROR;
    }
  }
  else
  {
    return Status_BUSY;//返回标志位
  }
}

/*****************************************************
*函数名称:StatusTypeDef SSI_UART_Receive_IT(SSI_HandleInfoDef *SSI_HANDLE, uint8_t *pData, uint8_t Size)
*函数功能:UART在中断模式下接收大量数据时，先在main函数中调用此函数
*入口参数:
SSI_SSI_HANDLEInfoDef*:SSI_HANDLE:指针指向UART数据信息存放区
uint8_t *:pData:接收数据的存放区
uint16_t:Size:待接收的数据量
*出口参数:
StatusTypeDef:函数执行状态
*****************************************************/
StatusTypeDef SSI_UART_Receive_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size)
{
  /* 检查一个接收进程是否正在进行 */
  if(SSI_HANDLE->RxState == SSI_STATE_READY)
  {
    /* 检查是否开启SSI_UART中断或发送数据量大小为0或是否开启接收使能，返回错误 */
    if(((IE1 & 0x01) == 0) || (Size == 0U) || ((SSCON0 & 0x10) != UART1_RX_ENABLE))
    {
      return Status_ERROR;
    }

    SSI_HANDLE->RxState = SSI_STATE_BUSY;
    SSI_HANDLE->pRxBuffPtr.Size_u8 = pData;			//指向接收数据的存放地址
    SSI_HANDLE->RxXferSize = Size;			//更新待接收的数据量
    SSI_HANDLE->RxXferCount = 0;			//发送计数器清零

    return Status_OK;
  }
  else
  {
    return Status_BUSY;//返回标志位
  }
}

/*****************************************************
*函数名称:StatusTypeDef SSI_UART_Receive_IRQHandler(SSI_HandleInfoDef* SSI_HANDLE)
*函数功能:UART在中断模式下接收大量数据时，在中断服务函数中调用
*	注：该函数调用需要判断中断标志位是否置起
*入口参数:
SSI_HandleInfoDef*:SSI_HANDLE:指针指向SSI数据信息存放区
*出口参数:
StatusTypeDef:函数执行状态
*****************************************************/
StatusTypeDef SSI_UART1_Receive_IRQHandler(SSI_HandleInfoDef* SSI_HANDLE)
{
  /* 检查一个接收进程是否正在进行 */
  if(SSI_HANDLE->RxState == SSI_STATE_BUSY)
  {
    /* 处于接收线程，检查待接收数据量是否为0 */
    if(SSI_HANDLE->RxXferCount < SSI_HANDLE->RxXferSize)
    {
      /* 待接收数据量未为0，继续接收 */
      if((SSCON0 & 0xC0) == UART1_Mode_11B)
      {
        /* 接收9位数据 */
        *(SSI_HANDLE->pRxBuffPtr.Size_u16 + SSI_HANDLE->RxXferCount) = SSI_UART1_ReceiveData9();
      }
      else
      {
        /* 接收8位数据 */
        *(SSI_HANDLE->pRxBuffPtr.Size_u8 + SSI_HANDLE->RxXferCount) = SSI_UART1_ReceiveData8();
      }
      SSI_HANDLE->RxXferCount ++;
      /* 判断上一次发送是否是最后一次 */
      if(SSI_HANDLE->RxXferCount == SSI_HANDLE->RxXferSize)
      {
        /* 接收完成 */
        SSI_HANDLE->RxState = SSI_STATE_READY;
      }
      return Status_OK;
    }
    else
    {
      /* 接收数据量为0时还接收数据，返回错误 */
      SSI_HANDLE->RxState = SSI_STATE_ERROR;
      return Status_ERROR;
    }
  }
  else
  {
    return Status_BUSY;
  }
}


/*****************************************************
*函数名称:void SSI_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*函数功能:SSI中断初始化
*入口参数:
FunctionalState:NewState:中断使能/关闭选择
PriorityStatus:Priority:中断优先级选择
*出口参数:void
*****************************************************/
void SSI_ITConfig(FunctionalState NewState,
                  PriorityStatus Priority)
{
  if(NewState != DISABLE)
  {
    IE1 |= 0x01;
  }
  else
  {
    IE1 &= 0xFE;
  }

  /************************************************************/
  if(Priority != LOW)
  {
    IP1 |= 0x01;
  }
  else
  {
    IP1 &= 0xFE;
  }
}

/*****************************************************
*函数名称:FlagStatus SSI_GetFlagStatus(SSI_Flag_TypeDef SSI_FLAG)
*函数功能:获得SSI标志状态
*入口参数:
SSI_Flag_TypeDef:SSI_FLAG:所需获取的标志位
*出口参数:
FlagStatus:SSI标志位置起状态
*****************************************************/
FlagStatus SSI_GetFlagStatus(SSI_Flag_TypeDef
                             SSI_FLAG)
{
  FlagStatus bitstatus = RESET;

  if((SSI_FLAG == SPI_FLAG_SPIF) ||
      (SSI_FLAG == SPI_FLAG_WCOL) ||
      (SSI_FLAG == SPI_FLAG_TXE))
  {
    if((SSI_FLAG & SSCON1) != (uint8_t)RESET)
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }
  else
  {
    if((SSI_FLAG & SSCON0) != (uint8_t)RESET)
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }

  return bitstatus;
}

/*****************************************************
*函数名称:void SSI_ClearFlag(SSI_Flag_TypeDef SSI_FLAG)
*函数功能:清除SSI标志状态
*入口参数:
SSI_Flag_TypeDef:SSI_FLAG:所需清除的标志位
*出口参数:void
*****************************************************/
void SSI_ClearFlag(SSI_Flag_TypeDef SSI_FLAG)
{
  if((SSI_FLAG == SPI_FLAG_SPIF) ||
      (SSI_FLAG == SPI_FLAG_WCOL) ||
      (SSI_FLAG == SPI_FLAG_TXE))
  {
    SSCON1 &= (~SSI_FLAG);
  }
  else
  {
    SSCON0 &= (~SSI_FLAG);
  }
}
#endif

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/
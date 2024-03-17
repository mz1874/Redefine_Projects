//************************************************************
//  Copyright (c) �Ϸ����¶���������޹�˾
//	�ļ�����:			rd8_ssi.c
//	����:					�¶���Ӧ���Ŷ�
//	ģ�鹦��:			BTM�̼��⺯��C�ļ�
//  ����������:	2022��6��10��
// 	�汾: 				V1.000
//  ˵��:
//*************************************************************

#include "rd8_ssi.h"

#if defined (RD8G403)
/**************************************************
*��������:void SSI_DeInit(void)
*��������:SSI��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
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
*��������:SSI_PinSelection(SSI_PinSelection_TypeDef PinSeletion)
*��������:SSI����ѡ��
*��ڲ���:
SSI_PinSelection_TypeDef:PinSeletion:ѡ��SSI����ΪP10P27P26��P21P22P23
*���ڲ���:void
**************************************************/
void SSI_PinSelection(SSI_PinSelection_TypeDef
                      PinSeletion)
{
  OTCON = OTCON & 0XDF | PinSeletion;
}
#endif

/**************************************************
*��������:void SSI_SPI_Init(SPI_FirstBit_TypeDef FirstBit, SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler,SPI_Mode_TypeDef Mode,
							 SPI_ClockPolarity_TypeDef ClockPolarity, SPI_ClockPhase_TypeDef ClockPhase,SPI_TXE_INT_TypeDef SPI_TXE_INT)
*��������:SPI��ʼ�����ú���
*��ڲ���:
SPI_FirstBit_TypeDef:FirstBit:���ȴ���λѡ��MSB/LSB��
SPI_BaudRatePrescaler_TypeDef:BaudRatePrescaler:SPIʱ��Ƶ��ѡ��
SPI_Mode_TypeDef:Mode:SPI����ģʽѡ��
SPI_ClockPolarity_TypeDef:ClockPolarity:SPIʱ�Ӽ���ѡ��
SPI_ClockPhase_TypeDef:ClockPhase:SPIʱ����λѡ��
SPI_TXE_INT_TypeDef:SPI_TXE_INT:���ͻ������ж�����ѡ��
*���ڲ���:void
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
*��������:void SSI_SPI_Cmd(FunctionalState NewState)
*��������:SPI���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
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
*��������:void SSI_SPI_SendData(uint8_t Data)
*��������:SPI��������
*��ڲ���:
uint8_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void SSI_SPI_SendData(uint8_t Data)
{
  SSDAT = Data;
}

/*****************************************************
*��������:uint8_t SSI_SPI_ReceiveData(void)
*��������:���SSDAT�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:SPI���յ���8λ����
*****************************************************/
uint8_t SSI_SPI_ReceiveData(void)
{
  return SSDAT;
}

/**********************************************************************************************************
*��������:StatusTypeDef SSI_SPI_IRQHandler(SSI_HandleInfoDef* SSI_HANDLE)
*��������:SPI0 �жϴ���
*��ڲ���:
SSI_HandleInfoDef*:SSI_HANDLE:ָ����� SPI0 ��Ϣ�� SSI_HandleInfoDef �ṹ���ָ�롣
*���ڲ���:
void
**********************************************************************************************************/
StatusTypeDef SSI_SPI_IRQHandler(SSI_HandleInfoDef* SSI_HANDLE)
{
  StatusTypeDef TempStatus = Status_ERROR;

  if(SSI_HANDLE->RxState == SSI_STATE_BUSY)
  {
    /* ������û�н������ */
    if(SSI_HANDLE->RxXferCount < SSI_HANDLE->RxXferSize)
    {

        *(SSI_HANDLE->pRxBuffPtr.Size_u8 + SSI_HANDLE->RxXferCount) = SSI_SPI_ReceiveData();			//��ȡ16λ����

      TempStatus = Status_BUSY;
      SSI_HANDLE->RxXferCount++;			//���յ����ݣ�����ֵ��1

      /* ���ݽ�����ɣ�״̬λ�����޸� */
      if(SSI_HANDLE->RxXferCount == SSI_HANDLE->RxXferSize)
      {
        SSI_HANDLE->RxState = SSI_STATE_READY;
        TempStatus =  Status_OK;
      }
    }

    if(SSI_HANDLE->TxState == SSI_STATE_BUSY)
    {

      SSI_HANDLE->TxXferCount++;			//���ݷ�����ɣ�����ֵ��1
      /* ������û�з������ */
      if(SSI_HANDLE->TxXferCount < SSI_HANDLE->TxXferSize)
      {

          SSI_SPI_SendData(*(SSI_HANDLE->pTxBuffPtr.Size_u8 + SSI_HANDLE->TxXferCount));			//����16λ����
        
        TempStatus = Status_BUSY;
      }
      /* ���ݷ�����ɣ�״̬λ�����޸�  */
      else if(SSI_HANDLE->TxXferCount == SSI_HANDLE->TxXferSize)
      {
        SSI_HANDLE->TxState = SSI_STATE_READY;
        TempStatus = Status_OK;
      }
    }
    /* ��SPI��������ʱ��SPI��Ҫ�������ݣ�����ͬ�����յ����� */
    else if(SSI_HANDLE->RxXferSize)
    {
      SSI_SPI_SendData(0x00);
    }
  }
  return TempStatus;
}


/**********************************************************************************************************
*��������:StatusTypeDef SSI_SPI_Receive(SSI_HandleInfoDef* SSI_HANDLE, uint8_t *pData, uint8_t Size, uint32_t Timeout)
*��������:SPI����ѯģʽ�½��մ�������
*��ڲ���:
SSI_HandleInfoDef*:SSI_HANDLE:ָ�����ָ��SPIģ���������Ϣ�ṹ���ָ��
uint8_t *:pData:�������ݵĴ����
uint16_t:Size:�����յ�������
uint32_t:Timeout:��ʱʱ��
*���ڲ���:
StatusTypeDef:SSI ״̬
**********************************************************************************************************/
StatusTypeDef SSI_SPI_Receive(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
{
  uint32_t TimeoutCnt = 0;

  if(SSI_HANDLE->RxState == SSI_STATE_READY)
  {
    /* ���������ݳ��ȱ������0�����򷵻ش���״̬ */
    if(((IE1 & 0x01) != 0) || (Size == 0U))
    {
      return SSI_STATE_ERROR;
    }

    /* SPI��Ϊ����ʱ���������ݱض����淢������ */
    if((SSCON0 & SPI_MODE_MASTER) != 0)
    {
      return SSI_SPI_TransmitReceive(SSI_HANDLE, pData, pData, Size, Timeout);			//��ת������ģʽ�����շ�����
    }

    SSI_HANDLE->RxState = SSI_STATE_BUSY;			//���ͽ���æµ��
    SSI_ClearFlag(SPI_FLAG_SPIF);			 //����ǰ��������жϱ�־
    SSI_HANDLE->pRxBuffPtr.Size_u8 = pData;			//ָ����������ݵĵ�ַ
    SSI_HANDLE->RxXferSize = Size;			//���´����͵�������
    SSI_HANDLE->RxXferCount = 0;			//���ͼ���������

    while(SSI_HANDLE->RxXferCount < SSI_HANDLE->RxXferSize)
    {
      /* �ȴ�SPI�жϱ�־λ���� */
      if(SSI_GetFlagStatus(SPI_FLAG_SPIF))
      {
          *(SSI_HANDLE->pRxBuffPtr.Size_u8 + SSI_HANDLE->RxXferCount) = SSI_SPI_ReceiveData();			//��ȡ16λ����,���ҵ�ַ����
        SSI_ClearFlag(SPI_FLAG_SPIF);				//�����־λ
        SSI_HANDLE->RxXferCount++;	//����������������1
        TimeoutCnt = 0;			//��ʱ����ֵ����
      }
      else
      {
        /* ��ʱ�����������ۼӣ�ֱ�������趨�ĳ�ʱʱ�� */
        if((TimeoutCnt++) > Timeout)
        {
          if(Timeout == 0)
            return SSI_STATE_TIMEOUT;				//���س�ʱ����
        }
        WDTCON |= 0x10;          //ι����������ֹ���Ź���λ
      }
    }

    if(SSI_HANDLE->RxXferCount == SSI_HANDLE->RxXferSize)
    {
      SSI_HANDLE->RxState = SSI_STATE_READY;	//�������
      return Status_OK;
    }
    else
    {
      SSI_HANDLE->RxState = SSI_STATE_ERROR;//���մ���
      return Status_ERROR;
    }
  }
  else
  {
    return Status_BUSY;//����æµ״̬
  }
}

/**********************************************************************************************************
*��������:StatusTypeDef SSI_SPI_Receive_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t *pData, uint8_t Size)
*��������:�ж�ģʽ����һ��������
*��ڲ���:
SSI_HandleInfoDef*:SSI_HANDLE:ָ�����ָ��SPIģ���������Ϣ�ṹ���ָ��
uint8_t *:pData:�������ݵĴ��
uint16_t:Size:�����յ�������
*���ڲ���:
StatusTypeDef:SSI ״̬
**********************************************************************************************************/
StatusTypeDef SSI_SPI_Receive_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size)
{
  /* ���һ�����ս����Ƿ����ڽ��� */
  if(SSI_HANDLE->RxState == SSI_STATE_READY)
  {
    /* ���������ݳ��ȱ������0�����򷵻ش���״̬ */
    if(((IE1 & 0x01) == 0) || (Size == 0U))
    {
      return SSI_STATE_ERROR;
    }

    /* SPI��Ϊ����ʱ���������ݱض����淢������ */
    if((SSCON0 & SPI_MODE_MASTER) != 0)
    {
      return SSI_SPI_TransmitReceive_IT(SSI_HANDLE, pData, pData, Size);			//��ת���ж�ģʽ�����շ�����
    }

    SSI_HANDLE->RxState = SSI_STATE_BUSY;			//״̬����Ϊ����æµ��
    SSI_ClearFlag(SPI_FLAG_SPIF);			//����жϱ�־λ
    SSI_HANDLE->pRxBuffPtr.Size_u8 = pData;			//ָ����������ݵĵ�ַ
    SSI_HANDLE->RxXferSize = Size;			//���´����͵�������
    SSI_HANDLE->RxXferCount = 0;			//���ͼ���������

    return Status_OK;
  }
  else
  {
    return Status_BUSY;//���ر�־λ
  }
}

/**********************************************************************************************************
*��������:StatusTypeDef SSI_SPI_Transmit(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
*��������:SPI����ѯģʽ�·��ʹ�������
*��ڲ���:
SSI_HandleInfoDef*:SSI_HANDLE:ָ�����ָ��SPIģ���������Ϣ�ṹ���ָ��
uint8_t *pData:ָ�����ݻ����ָ�롣
uint16_t Size:�������ݵĴ�С
uint32_t Timeout:��ʱʱ��
*���ڲ���:
StatusTypeDef:SSI ״̬
**********************************************************************************************************/
StatusTypeDef SSI_SPI_Transmit(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
{
  uint32_t TimeoutCnt = 0;
  /* ���һ�����ͽ����Ƿ����ڽ��� */
  if(SSI_HANDLE->TxState == SSI_STATE_READY)
  {
    /* ���������ݳ��ȱ������0�����򷵻ش���״̬ */
    if(((IE1 & 0x01) != 0) || (Size == 0U))
    {
      return Status_ERROR;
    }

    SSI_HANDLE->TxState = SSI_STATE_BUSY;			//���ͽ���æµ��
    SSI_ClearFlag(SPI_FLAG_SPIF);			 //����ǰ�����־λ
    SSI_HANDLE->pTxBuffPtr.Size_u8 = pData;			//ָ����������ݵĵ�ַ
    SSI_HANDLE->TxXferSize = Size;			//���´����͵�������
    SSI_HANDLE->TxXferCount = 0;			//���ͼ���������

    while(SSI_HANDLE->TxXferCount < SSI_HANDLE->TxXferSize)//�ж��Ƿ������������
    {

        SSI_SPI_SendData(*(SSI_HANDLE->pTxBuffPtr.Size_u8 + SSI_HANDLE->TxXferCount));			//����8λ���ݲ������ݵ�ַ����
      while(!SSI_GetFlagStatus(SPI_FLAG_SPIF))			//�ȴ��������
      {
        /* ��ʱ�����������ۼӣ�ֱ�������趨�ĳ�ʱʱ�� */
        if(TimeoutCnt++ > Timeout)
        {
          SSI_HANDLE->TxState = SSI_STATE_TIMEOUT;//���ͳ�ʱ
          return Status_TIMEOUT;
        }
        WDTCON |= 0x10;			//ι������ֹ�ȴ�ʱ�����������WDT��λ
      }

      SSI_ClearFlag(SPI_FLAG_SPIF);				//����ǰ�������־λ
      TimeoutCnt = 0;			//��ʱ����������
      SSI_HANDLE->TxXferCount ++;	//��������������
    }
    if(SSI_HANDLE->TxXferCount == SSI_HANDLE->TxXferSize)
    {
      SSI_HANDLE->TxState = SSI_STATE_READY;	//�������
      return Status_OK;
    }
    else
    {
      SSI_HANDLE->TxState = SSI_STATE_ERROR;//�������ʹ���
      return Status_ERROR;
    }
  }
  else
  {
    return Status_BUSY;//����æµ״̬
  }
}

	
/**********************************************************************************************************
*��������:StatusTypeDef SSI_SPI_Transmit_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size)
*��������:�ж�ģʽ����һ��������
*��ڲ���:
SSI_HandleInfoDef *SSI_HANDLE:ָ����� SPI0 ��Ϣ�� SSI_HandleInfoDef �ṹ���ָ�롣
uint8_t *pData:ָ�����ݻ����ָ�롣
uint16_t Size:�������ݵĴ�С
*���ڲ���:
StatusTypeDef:SSI ״̬
**********************************************************************************************************/
StatusTypeDef SSI_SPI_Transmit_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size)
{
  /* ���һ�����ͽ����Ƿ����ڽ��� */
  if(SSI_HANDLE->TxState == SSI_STATE_READY)
  {
    /* û�п���SSI�жϻ�����������СΪ0�����ش��� */
    if(((IE1 & 0x01) == 0) || (Size == 0U))
    {
      return Status_ERROR;
    }

    SSI_HANDLE->TxState = SSI_STATE_BUSY;			//���ͽ���æµ��
    SSI_ClearFlag(SPI_FLAG_SPIF);			//����жϱ�־λ
    SSI_HANDLE->pTxBuffPtr.Size_u8 = pData;			//ָ����������ݵĵ�ַ
    SSI_HANDLE->TxXferSize = Size;			//���´����͵�������
    SSI_HANDLE->TxXferCount = 0;			//���ͼ�������0

    /* ���͵�1byte���� */
      SSI_SPI_SendData(*(SSI_HANDLE->pTxBuffPtr.Size_u8));

    return Status_OK;
  }
  else
  {
    return  Status_BUSY;			//״̬λ�޸�Ϊæµ״̬
  }
}
/**********************************************************************************************************
*��������:StatusTypeDef SSI_SPI_TransmitReceive(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pTxData, uint8_t* pRxData, uint8_t Size, uint32_t Timeout)
*��������:����ģʽ�շ�һ��������
*��ڲ���:
SSI_HandleInfoDef*:SSI_HANDLE:ָ����� SPI0 ��Ϣ�� SSI_HandleInfoDef �ṹ���ָ�롣
*���ڲ���:
StatusTypeDef:SSI ״̬
**********************************************************************************************************/
StatusTypeDef SSI_SPI_TransmitReceive(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pTxData, uint8_t* pRxData, uint8_t Size, uint32_t Timeout)
{
  uint32_t TimeoutCnt = 0;
  /* ���һ�����ͽ����Ƿ����ڽ��� */
  if((SSI_HANDLE->TxState == SSI_STATE_READY) && (SSI_HANDLE->RxState == SSI_STATE_READY))
  {

    /* �����ͺͽ������ݳ��ȱ������0�����򷵻ش���״̬ */
    if(((IE1 & 0x01) != 0) || (Size == 0U))
    {
      return  Status_ERROR;
    }

    SSI_HANDLE->TxState = SSI_HANDLE->RxState = SSI_STATE_BUSY;			//���ͽ���æµ��
    SSI_ClearFlag(SPI_FLAG_SPIF);			//����жϱ�־λ
    SSI_HANDLE->pTxBuffPtr.Size_u8 = pTxData;       //ָ����������ݵĵ�ַ
    SSI_HANDLE->pRxBuffPtr.Size_u8 = pRxData;
    SSI_HANDLE->TxXferSize = SSI_HANDLE->RxXferSize = Size;			//���´����͵�������
    SSI_HANDLE->TxXferCount = SSI_HANDLE->RxXferCount = 0;			//���ͼ���������

    while(SSI_HANDLE->TxXferCount < SSI_HANDLE->TxXferSize);
    {


      SSI_SPI_SendData(*(SSI_HANDLE->pTxBuffPtr.Size_u8 + SSI_HANDLE->TxXferCount));			//����16λ���ݲ��ҵ�ַ����
      while(!SSI_GetFlagStatus(SPI_FLAG_SPIF))			//�ȴ��������
      {
        /* �ȴ�ʱ���Ƿ����˳�ʱ */
        if(TimeoutCnt++ > Timeout)
        {
          return SSI_STATE_TIMEOUT;				//���س�ʱ����
        }
        WDTCON |= 0x10;			//ι������ֹ�ȴ�ʱ�����������WDT��λ
      }
      SSI_ClearFlag(SPI_FLAG_SPIF);				//����ǰ�������־λ
      *(SSI_HANDLE->pTxBuffPtr.Size_u8 + SSI_HANDLE->TxXferCount) = SSI_SPI_ReceiveData();

      TimeoutCnt = 0;			//��ʱ����ֵ����
      SSI_HANDLE->TxXferCount++;			//����������ֵ��1
      SSI_HANDLE->TxXferCount++;			//����������ֵ��1
    }
    if(SSI_HANDLE->TxXferCount == SSI_HANDLE->TxXferSize)
    {
      SSI_HANDLE->TxState = SSI_HANDLE->RxState = SSI_STATE_READY;	//�������
      return Status_OK;
    }
    else
    {
      SSI_HANDLE->TxState = SSI_STATE_ERROR;//�������ʹ���
      return Status_ERROR;
    }
  }
  else
  {
    return Status_ERROR;
  }

}
/**********************************************************************************************************
*��������:StatusTypeDef SSI_SPI_TransmitReceive_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pTxData, uint8_t* pRxData, uint8_t Size)
*��������:SPI���ж�ģʽ�·��ͺͽ��մ�������ʱ������main�����е��ô˺���
*��ڲ���:
SSI_HandleInfoDef *SSI_HANDLE:ָ�����ָ��SPIģ���������Ϣ�ṹ���ָ��
uint8_t *:pData:���ͺͽ������ݵĴ����
uint16_t:Size:�����ͺͽ��յ�������
*���ڲ���:
StatusTypeDef:SSI ״̬
**********************************************************************************************************/
StatusTypeDef SSI_SPI_TransmitReceive_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pTxData, uint8_t* pRxData, uint8_t Size)
{
  /* ���������ݳ��ȱ������0�����򷵻ش���״̬ */
  if((SSI_HANDLE->TxState == SSI_STATE_READY) && (SSI_HANDLE->RxState == SSI_STATE_READY))
  {

    /* �����ͺͽ������ݳ��ȱ������0�����򷵻ش���״̬ */
    if(((IE1 & 0x01) == 0) || (Size == 0U))
    {
      return  Status_ERROR;
    }
    SSI_SPI_Cmd(DISABLE);
    SSI_HANDLE->TxState = SSI_HANDLE->RxState = SSI_STATE_BUSY;			//���ͽ���æµ��
    SSI_ClearFlag(SPI_FLAG_SPIF);			//����жϱ�־λ
    SSI_HANDLE->pTxBuffPtr.Size_u8 = pTxData;
    SSI_HANDLE->pRxBuffPtr.Size_u8 = pRxData;			//ָ����������ݵĵ�ַ
    SSI_HANDLE->TxXferSize = SSI_HANDLE->RxXferSize = Size;			//���´����͵�������
    SSI_HANDLE->TxXferCount = SSI_HANDLE->RxXferCount = 0;			//���ͼ���������
    SSI_SPI_Cmd(ENABLE);

    /* ���͵�1byte���� */
    /* SPI����8λͨ��ģʽ */
    SSI_SPI_SendData(*(SSI_HANDLE->pTxBuffPtr.Size_u8));			//����8λ����

    return  Status_OK;
  }
  else
  {
    return Status_ERROR;
  }
}


/**************************************************
*��������:void TWI_Init(uint8_t TWI_Address)
*��������:TWI��ʼ�����ú���
*��ڲ���:
uint8_t:TWI_Address:TWI��Ϊ�ӻ�ʱ7λ�ӻ���ַ����
*���ڲ���:void
**************************************************/
void TWI_Init(uint8_t TWI_Address)
{
  OTCON = OTCON & 0X3F | 0X80;
  SSCON1 = TWI_Address << 1;
}

/**************************************************
*��������:void TWI_AcknowledgeConfig(FunctionalState NewState)
*��������:TWI����Ӧ��ʹ�ܺ���
*��ڲ���:
FunctionalState:NewState:����Ӧ��ʹ��/ʧ��ѡ��
*���ڲ���:void
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
*��������:void TWI_GeneralCallCmd(FunctionalState NewState)
*��������:TWIͨ�õ�ַ��Ӧʹ�ܺ���
*��ڲ���:
FunctionalState:NewState:ͨ�õ�ַ��Ӧʹ��/ʧ��ѡ��
*���ڲ���:void
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
*��������:FlagStatus SSI_GetTWIStatus(SSI_TWIState_TypeDef SSI_TWIState)
*��������:��ȡTWI״̬��
*��ڲ���:
SSI_TWIState_TypeDef:SSI_TWIState:TWI״̬��״̬
*���ڲ���:void
**************************************************/
FlagStatus SSI_GetTWIStatus(SSI_TWIState_TypeDef SSI_TWIState)
{
  if((SSCON0 & 0x07) == SSI_TWIState)
    return SET;
  else
    return RESET;
}

/*****************************************************
*��������:void TWI_Cmd(FunctionalState NewState)
*��������:TWI���ܿ��غ���
*��ڲ���:FunctionalState NewState	��������/�ر�ѡ��
*���ڲ���:void
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
*��������:void TWI_SendData(uint8_t Data)
*��������:TWI��������
*��ڲ���:
uint8_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void TWI_SendData(uint8_t Data)
{
  SSDAT = Data;
}

/*****************************************************
*��������:uint8_t TWI_ReceiveData(void)
*��������:���SSDAT�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:TWI���յ���8λ����
*****************************************************/
uint8_t TWI_ReceiveData(void)
{
  return SSDAT;
}

/*****************************************************
*�������ƣ�StatusTypeDef TWI_Wait_TWIF(SSI_HandleInfoDef* SSI_HANDLE,uint32_t Timeout)
*�������ܣ��ȴ�TWIF����
*��ڲ�����
SSI_HandleInfoDef*:SSI_HANDLE:ָ��ָ��SSI������Ϣ�����
uint32_t:Timeout:��ʱʱ������
*���ڲ�����StatusTypeDef:����ִ��״̬
*****************************************************/
StatusTypeDef TWI_Wait_TWIF(SSI_HandleInfoDef* SSI_HANDLE, uint32_t Timeout)
{
  uint32_t TimeoutCnt = 0;
  while(!(SSI_GetFlagStatus(TWI_FLAG_TWIF)))			//�ȴ������źŷ������
  {
    TimeoutCnt++;
    if(TimeoutCnt > Timeout)
    {
      /* ��ʱ����״̬ */
      if(SSI_HANDLE->TxState == SSI_STATE_BUSY)
        SSI_HANDLE->TxState = SSI_STATE_TIMEOUT;
      if(SSI_HANDLE->RxState == SSI_STATE_BUSY)
        SSI_HANDLE->RxState = SSI_STATE_TIMEOUT;
      return Status_TIMEOUT;
    }
  }
  SSI_ClearFlag(TWI_FLAG_TWIF);			//�����־λ
  return Status_OK;
}

/*****************************************************
*��������:StatusTypeDef TWI_Slave_Transmit(SSI_HandleInfoDef* SSI_HANDLE, uint32_t Timeout)
*��������:����8λ����ʱ���ӻ���ѯģʽ�·��ʹ�������
* ע��Ĭ�Ͽ���ʱ���ӳ�ģʽ
*��ڲ���:
SSI_HandleInfoDef*:SSI_HANDLE:ָ��ָ��SSI������Ϣ�����
uint8_t*:pData	ָ��ָ��洢��
uint32_t:Size:�洢���ݳ���
uint32_t:Timeout:��ʱʱ������
*���ڲ���:
StatusTypeDef:����ִ��״̬
*****************************************************/
StatusTypeDef TWI_Slave_Transmit(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
{
  /* ���һ�����ͽ����Ƿ����ڽ��� */
  if(SSI_HANDLE->TxState == SSI_STATE_READY)
  {
    /* ���������ݳ��ȱ������0�����򷵻ش���״̬ */
    if((IE1 & 0x01 != 0) || (Size == 0U))
    {
      return Status_ERROR;
    }
    else
    {
      SSI_HANDLE->TxState = SSI_STATE_BUSY;			//���ͽ���æµ��
      SSI_ClearFlag(TWI_FLAG_TWIF);			 //����ǰ�����־λ
      SSI_HANDLE->pTxBuffPtr.Size_u8 = pData;			//ָ����������ݵĵ�ַ
      SSI_HANDLE->TxXferSize = Size;			//���´����͵�������
      SSI_HANDLE->TxXferCount = 0;			//���ͼ���������

      
      TWI_AcknowledgeConfig(ENABLE);         //����AAʹ��λ
      if(TWI_Wait_TWIF(SSI_HANDLE, Timeout) == Status_TIMEOUT)            //�ȴ���ַƥ��
      {
        TWI_AcknowledgeConfig(DISABLE);            //�ر�AAʹ��
        return Status_TIMEOUT;
      }

      do
      {
        if(SSI_GetTWIStatus(TWI_SlaveSendData) == SET)           //���״̬��״̬
        {

          SSCON2 = *(SSI_HANDLE->pTxBuffPtr.Size_u8 + SSI_HANDLE->TxXferCount);             //TWI��������

          if(TWI_Wait_TWIF(SSI_HANDLE, Timeout) == Status_TIMEOUT)             //�ȴ������źŷ������
          {
            TWI_AcknowledgeConfig(DISABLE);            //�ر�AAʹ��
            return Status_TIMEOUT;
          }
          SSI_HANDLE->TxXferCount++;

          if(SSI_HANDLE->TxXferCount == SSI_HANDLE->TxXferSize - 1)

            TWI_AcknowledgeConfig(DISABLE);            //�ر�AAʹ��

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

      if(SSI_GetTWIStatus(TWI_SlaveDisableACK) == RESET)           //���״̬��״̬
      {
        SSI_HANDLE->TxState = SSI_STATE_ERROR;
        return Status_ERROR;
      }

      if(SSI_HANDLE->TxXferCount == SSI_HANDLE->TxXferSize)
      {
        SSI_HANDLE->TxState = SSI_STATE_READY;	//�������
        return Status_OK;
      }
      else
      {
        SSI_HANDLE->TxState = SSI_STATE_ERROR;//�������ʹ���
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
*��������:StatusTypeDef TWI_Slave_Transmit_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size)
*��������:�ӻ�ʹ���ж�ģʽ�·��ʹ�������ʱ������main�����е��ô˺���
*��ڲ���:
SSI_HandleInfoDef*:SSI_HANDLE:ָ��ָ��SSI������Ϣ�����
uint8_t*:pData ָ��ָ��洢��
uint32_t:Size:�洢���ݳ���
*���ڲ���:
StatusTypeDef:����ִ��״̬
*****************************************************/
StatusTypeDef TWI_Slave_Transmit_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size)
{
  /* ���һ�����ͽ����Ƿ����ڽ��� */
  if(SSI_HANDLE->TxState == SSI_STATE_READY)
  {
    /* ���������ݳ��ȱ������0�����򷵻ش���״̬ */
    if(((IE1 & 0x01) == 0) || (Size == 0U))
    {
      return Status_ERROR;
    }
    else
    {
      
      TWI_AcknowledgeConfig(DISABLE);         //����AA
      SSI_ClearFlag(TWI_FLAG_TWIF);			 //����ǰ�����־λ
      
      SSI_HANDLE->TxState = SSI_STATE_WAIT;			//���ͽ���æµ��
      SSI_HANDLE->pTxBuffPtr.Size_u8 = pData;			//ָ����������ݵĵ�ַ
      SSI_HANDLE->TxXferSize = Size;			//���´����͵�������
      SSI_HANDLE->TxXferCount = 0;			//���ͼ���������

      TWI_AcknowledgeConfig(ENABLE);         //����AA

      return Status_OK;;
    }
  }
  else
  {
    return Status_ERROR;
  }
}

/*****************************************************
*��������:StatusTypeDef TWI_Slave_Transmit_IRQHandler(SSI_HandleInfoDef *SSI_HANDLE)
*��������:����8λ����ʱ���ӻ��ж�ģʽ�·��ʹ�������
*��ڲ���:
SSI_HandleInfoDef*:SSI_HANDLE:ָ��ָ��SSI������Ϣ�����
*���ڲ���:
StatusTypeDef:����ִ��״̬
*****************************************************/
StatusTypeDef TWI_Slave_Transmit_IRQHandler(SSI_HandleInfoDef* SSI_HANDLE)
{
  if(SSI_HANDLE->TxState == SSI_STATE_BUSY)
  {

    if(SSI_GetTWIStatus(TWI_SlaveSendData) == SET)
    {
      if(SSI_HANDLE->TxXferCount < SSI_HANDLE->TxXferSize)
      {
        SSI_HANDLE->TxXferCount++;			//��һ���ж��ǽ��ܵ���ַ��
        SSCON2 = *(SSI_HANDLE->pTxBuffPtr.Size_u8 + SSI_HANDLE->TxXferCount);
        if(SSI_HANDLE->TxXferCount == SSI_HANDLE->TxXferSize - 1)
        {
          TWI_AcknowledgeConfig(DISABLE);         //�ر�AAʹ��λ
        }
        return Status_BUSY;
      }
      else
      {
        TWI_AcknowledgeConfig(DISABLE);         //�ر�AAʹ��λ
        SSI_HANDLE->TxState = SSI_STATE_ERROR;
        return Status_ERROR;
      }
    }
    /*
    1.�����ݴ�������У����������޸���AA����λ
    2.���յ�����������UACK */
    else if((SSI_GetTWIStatus(TWI_SlaveDisableACK) == SET) || (SSI_GetTWIStatus(TWI_SlaveReceivedaUACK) == SET))
    {
      TWI_AcknowledgeConfig(DISABLE);         //�ر�AAʹ��λ
		 SSI_HANDLE->TxXferCount++;
      if(SSI_HANDLE->TxXferCount == SSI_HANDLE->TxXferSize)			//���������ѷ���
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
      TWI_AcknowledgeConfig(DISABLE);         //�ر�AAʹ��λ
      /* �������δ���͹��̳���
      1.���ݷ��ͺ���ܵ�UACK
      2.TWI���ǹ����ڴӻ�����״̬ */
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
    return Status_ERROR;//���ر�־λ
  }
}


/*****************************************************
*��������:StatusTypeDef TWI_Slave_Receive(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
*��������:����8λ����ʱ���ӻ���ѯģʽ�½��մ�������
*��ڲ���:
SSI_HandleInfoDef*:SSI_HANDLE:ָ��ָ��SSI������Ϣ�����
uint8_t*:pData ָ��ָ��洢��
uint32_t:Size:�洢���ݳ���
uint32_t:Timeout:��ʱʱ������
*���ڲ���:
StatusTypeDef:����ִ��״̬
*****************************************************/
StatusTypeDef TWI_Slave_Receive(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
{
  if(SSI_HANDLE->RxState == SSI_STATE_READY)
  {
    /* ���������ݳ��ȱ������0�����򷵻ش���״̬ */
    if((IE1 & 0x01 != 0) || (Size == 0U))
    {
      return Status_ERROR;
    }

    SSI_HANDLE->RxState = SSI_STATE_BUSY;			//���ͽ���æµ��
    SSI_ClearFlag(TWI_FLAG_TWIF);			 //����ǰ�����־λ
    TWI_AcknowledgeConfig(ENABLE);         //����AAʹ��λ
    SSI_HANDLE->pRxBuffPtr.Size_u8 = pData;			//ָ����������ݵĵ�ַ
    SSI_HANDLE->RxXferSize = Size;			//���´����͵�������
    SSI_HANDLE->RxXferCount = 0;			//���ͼ���������

    /* ���յ�ַ���� */
    if(TWI_Wait_TWIF(SSI_HANDLE, Timeout) == Status_TIMEOUT)            //�ȴ��źŷ������
    {
      /* �����Ƿ�����ɣ�����Ҫ���ͽ����źţ���ֹ����ռ������ */
		 TWI_AcknowledgeConfig(DISABLE);         //�ر�AAʹ��λ
      return Status_TIMEOUT;
    }

    if(SSI_GetTWIStatus(TWI_SlaveReceivedaData) == RESET)           //���״̬��״̬
    {
      SSI_HANDLE->RxState = SSI_STATE_ERROR;
      /* �����Ƿ�����ɣ�����Ҫ���ͽ����źţ���ֹ����ռ������ */
		 TWI_AcknowledgeConfig(DISABLE);         //�ر�AAʹ��λ
      return Status_ERROR;
    }

    /* �������ݹ��� */
    do
    {
      if(TWI_Wait_TWIF(SSI_HANDLE, Timeout) == Status_TIMEOUT)            //�ȴ������źŷ������
      {
        return Status_TIMEOUT;
      }

      if(SSI_GetTWIStatus(TWI_SlaveReceivedaData) == SET)           //���״̬��״̬
      {
        *(SSI_HANDLE->pRxBuffPtr.Size_u8 + SSI_HANDLE->RxXferCount) = SSCON2;             //TWI��������
        SSI_HANDLE->RxXferCount++;
        if(SSI_HANDLE->RxXferCount == SSI_HANDLE->RxXferSize - 1)
          TWI_AcknowledgeConfig(DISABLE);         //�ر�AAʹ��λ,������UAC
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
          TWI_AcknowledgeConfig(DISABLE);         //�ر�AAʹ��λ
          return Status_ERROR;
        }
      }
      else
      {
        SSI_HANDLE->RxState = SSI_STATE_ERROR;
        TWI_AcknowledgeConfig(DISABLE);         //�ر�AAʹ��λ
        return Status_ERROR;
      }

    }
    while(SSI_HANDLE->RxXferCount < SSI_HANDLE->RxXferSize);

    if(SSI_HANDLE->RxXferCount == SSI_HANDLE->RxXferSize)
    {
      SSI_HANDLE->RxState = SSI_STATE_READY;	//�������
      return Status_OK;
    }
    else
    {
      SSI_HANDLE->RxState = SSI_STATE_ERROR;//�������ʹ���
      return Status_ERROR;
    }
  }
  else
  {
    return Status_BUSY;
  }
}


/*****************************************************
*��������:void TWI_Slave_Receive_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size))
*��������:�ӻ�ʹ���ж�ģʽ�½��մ�������ʱ������main�����е��ô˺���
*��ڲ���:
SSI_HandleInfoDef*:SSI_HANDLE:ָ��ָ��SSI������Ϣ�����
uint8_t*:pData ָ��ָ��洢��
uint32_t:Size:�洢���ݳ���
*���ڲ���:
StatusTypeDef:����ִ��״̬
*****************************************************/
StatusTypeDef TWI_Slave_Receive_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size)
{
  if(SSI_HANDLE->RxState == SSI_STATE_READY)
  {
    /* ���������ݳ��ȱ������0�����򷵻ش���״̬ */
    if(((IE1 & 0x01) == 0) || (Size == 0U))
    {
      return Status_ERROR;
    }
    
    TWI_AcknowledgeConfig(DISABLE);         //�ر�AAʹ��λ
    SSI_ClearFlag(TWI_FLAG_TWIF);			 //����ǰ�����־λ
    SSI_HANDLE->RxState = SSI_STATE_WAIT;			//���ͽ���æµ��
    SSI_HANDLE->pRxBuffPtr.Size_u8 = pData;			//ָ����������ݵĵ�ַ
    SSI_HANDLE->RxXferSize = Size;			//���´����͵�������
    SSI_HANDLE->RxXferCount = 0;			//���ͼ���������
    TWI_AcknowledgeConfig(ENABLE);         //����AAʹ��λ

    return Status_OK;
  }
  else
  {
    return Status_BUSY;
  }
}

/*****************************************************
*��������:StatusTypeDef TWI_Slave_Receive_IRQHandler(SSI_HandleInfoDef* SSI_HANDLE)
*��������:����8λ����ʱ���ӻ��ж�ģʽ�½��մ�������
*��ڲ���:
SSI_HandleInfoDef:*SSI_HANDLE ָ��ָ��SSI������Ϣ�����
*���ڲ���:
StatusTypeDef:����ִ��״̬
*****************************************************/
StatusTypeDef TWI_Slave_Receive_IRQHandler(SSI_HandleInfoDef* SSI_HANDLE)
{
  if(SSI_HANDLE->RxState == SSI_STATE_BUSY)
  {
    if(SSI_GetTWIStatus(TWI_SlaveReceivedaData) == SET)           //���״̬��״̬
    {
      if(SSI_HANDLE->RxXferCount < SSI_HANDLE->RxXferSize)
      {
        *(SSI_HANDLE->pRxBuffPtr.Size_u8 + SSI_HANDLE->RxXferCount) = SSCON2;             //TWI��������
        SSI_HANDLE->RxXferCount++;
        if(SSI_HANDLE->RxXferCount == SSI_HANDLE->RxXferSize - 1)
        {
          TWI_AcknowledgeConfig(DISABLE);         //�ر�AAʹ��λ,������UACK
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
        TWI_AcknowledgeConfig(DISABLE);         //�ر�AAʹ��λ,������UACK
        SSI_HANDLE->RxState = SSI_STATE_READY;
        return Status_OK;
      }
      else
      {
        TWI_AcknowledgeConfig(DISABLE);         //�ر�AAʹ��λ
        SSI_HANDLE->RxState = SSI_STATE_ERROR;
        return Status_ERROR;
      }
    }
    else
    {
      SSI_HANDLE->RxState = SSI_STATE_ERROR;
      TWI_AcknowledgeConfig(DISABLE);         //�ر�AAʹ��λ
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
*��������:void SSI_UART1_Init(uint32_t UART1Fsys, uint32_t BaudRate, UART1_Mode_TypeDef Mode, UART1_RX_TypeDef RxMode)
*��������:UART1��ʼ�����ú���
*��ڲ���:
uint32_t:UART1Fsys:ϵͳʱ��Ƶ��
uint32_t:BaudRate:������
UART1_Mode_TypeDef:Mode:UART1����ģʽ
UART1_RX_TypeDef:RxMode:��������ѡ��
*���ڲ���:void
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
*��������:void SSI_UART1_SendData8(uint8_t Data)
*��������:UART1����8λ����
*��ڲ���:
uint8_t:Data:���͵�����
*���ڲ���:void
*****************************************************/
void SSI_UART1_SendData8(uint8_t Data)
{
  SSDAT = Data;
}

/*****************************************************
*��������:uint8_t SSI_UART1_ReceiveData8(void)
*��������:���SSDAT�е�ֵ
*��ڲ���:void
*���ڲ���:
uint8_t:UART���յ���8λ����
*****************************************************/
uint8_t SSI_UART1_ReceiveData8(void)
{
  return SSDAT;
}

/*****************************************************
*��������:void SSI_UART1_SendData9(uint16_t Data)
*��������:UART1����9λ����
*��ڲ���:
uint16_t:Data:���͵�����
*���ڲ���:void
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
*��������:uint16_t SSI_UART1_ReceiveData9(void)
*��������:���SSDAT�е�ֵ���ھ�λ��ֵ
*��ڲ���:void
*���ڲ���:
uint16_t:���յ�������
*****************************************************/
uint16_t SSI_UART1_ReceiveData9(void)
{
  uint16_t Data9;
  Data9 =  SSDAT + ((uint16_t)(SSCON0 & 0X04) << 6);
  SSCON0 &= 0XFB;
  return Data9;
}

/*****************************************************
*��������:StatusTypeDef  SSI_UART_Transmit(SSI_HandleInfoDef* SSI_HANDLE, uint8_t *pData, uint8_t Size, uint32_t Timeout)
*��������:UART����ѯģʽ�·��ʹ�������
*��ڲ���:
SSI_HandleInfoDef*:SSI_HANDLE:ָ��ָ��UART������Ϣ�����
uint8_t *:pData:����������
uint16_t:Size:�����͵�������
uint32_t:Timeout:��ʱʱ������
*���ڲ���:
StatusTypeDef:����ִ��״̬
*****************************************************/
StatusTypeDef SSI_UART_Transmit(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
{
  uint32_t delaytime = 0;
  /* ���һ�����ͽ����Ƿ����ڽ��� */
  if(SSI_HANDLE->TxState == SSI_STATE_READY)
  {
    /* ��鷢���������Ƿ�Ϊ0 */
    if((IE1 & 0x01 != 0) || (Size == 0U))
    {
      return  Status_ERROR;
    }

    SSI_HANDLE->TxState = SSI_STATE_BUSY;			//���ͽ���æµ��
    SSI_ClearFlag(UART1_FLAG_TI); //����ǰ��������жϱ�־��д1/д0����
    SSI_HANDLE->pTxBuffPtr.Size_u8 = pData;			//ָ����������ݵĵ�ַ
    SSI_HANDLE->TxXferSize = Size;			//���´����͵�������
    SSI_HANDLE->TxXferCount = 0;			//���ͼ���������

    while(SSI_HANDLE->TxXferCount < SSI_HANDLE->TxXferSize)//�ж��Ƿ������������
    {
      if((SSCON0 & 0xC0) == UART1_Mode_11B)
      {
        /* ����9λ���� */
        SSI_UART1_SendData9(*(SSI_HANDLE->pTxBuffPtr.Size_u16 + SSI_HANDLE->TxXferCount));
      }
      else
      {
        /* ����8λ���� */
        SSI_UART1_SendData8(*(SSI_HANDLE->pTxBuffPtr.Size_u8 + SSI_HANDLE->TxXferCount));
      }

      /* �ȴ�������� */
      delaytime = 0;
      while(!(SSCON0 & 0x02))
      {
        if(delaytime++ > Timeout)
        {
          SSI_HANDLE->TxState = SSI_STATE_TIMEOUT;//���ͳ�ʱ
          return Status_TIMEOUT;
        }
      }

      SSI_ClearFlag(UART1_FLAG_TI); //�����жϱ�־�����д1/д0����
      SSI_HANDLE->TxXferCount ++;	//��������������
    }

    if(SSI_HANDLE->TxXferCount == SSI_HANDLE->TxXferSize)
    {
      SSI_HANDLE->TxState = SSI_STATE_READY;	//�������
      return Status_OK;
    }
    else
    {
      SSI_HANDLE->TxState = SSI_STATE_ERROR;//�������ʹ���
      return Status_ERROR;
    }
  }
  else
  {
    return Status_BUSY;//���ر�־λ
  }
}


/*****************************************************
*��������:StatusTypeDef SSI_UART_Transmit_IT(SSI_HandleInfoDef *SSI_HANDLE, uint8_t *pData, uint8_t Size)
*��������:UART���ж�ģʽ�·��ʹ�������ʱ������main�����е��ô˺���
*��ڲ���:
SSI_HandleInfoDef*:SSI_HANDLE:ָ��ָ��UART������Ϣ�����
uint8_t *:pData:����������
uint16_t:Size:�����͵�������
*���ڲ���:
StatusTypeDef:����ִ��״̬
*****************************************************/
StatusTypeDef SSI_UART_Transmit_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size)
{
  /* ���һ�����ͽ����Ƿ����ڽ��� */
  if(SSI_HANDLE->TxState == SSI_STATE_READY)
  {
    /* û�п���SSI�жϻ�����������СΪ0�����ش��� */
    if(((IE1 & 0x01) == 0) || (Size == 0U))
    {
      return Status_ERROR;
    }

    SSI_HANDLE->TxState = SSI_STATE_BUSY;
    SSI_HANDLE->pTxBuffPtr.Size_u8 = pData;			//ָ����������ݵĵ�ַ
    SSI_HANDLE->TxXferSize = Size;			//���´����͵�������
    SSI_HANDLE->TxXferCount = 0;			//���ͼ���������

    /* ���͵�1֡���� */
    if((SSCON0 & 0xC0) == UART1_Mode_11B)
    {
      /* ����9λ���� */
      SSI_UART1_SendData9(*(SSI_HANDLE->pTxBuffPtr.Size_u16 + SSI_HANDLE->TxXferCount));
    }
    else
    {
      /* ����8λ���� */
      SSI_UART1_SendData8(*(SSI_HANDLE->pTxBuffPtr.Size_u8 + SSI_HANDLE->TxXferCount));
    }
    return Status_OK;
  }
  else
  {
    return Status_BUSY;//���ر�־λ
  }
}

/*****************************************************
*��������:StatusTypeDef  SSI_UART_Transmit_IRQHandler(SSI_HandleInfoDef *SSI_HANDLE)
*��������:UART���ж�ģʽ�·��ʹ�������ʱ�����жϷ������е���
*	ע���ú���������Ҫ�ж��жϱ�־λ�Ƿ�����
*��ڲ���:
SSI_HandleInfoDef:*SSI_HANDLE:ָ��ָ��UART������Ϣ�����
*���ڲ���:
StatusTypeDef:����ִ��״̬
*****************************************************/
StatusTypeDef SSI_UART_Transmit_IRQHandler(SSI_HandleInfoDef* SSI_HANDLE)
{
  /* ���ڷ����߳� */
  if(SSI_HANDLE->TxState == SSI_STATE_BUSY)
  {
    SSI_HANDLE->TxXferCount++;
    /* �ж���һ�η����Ƿ������һ�� */
    if(SSI_HANDLE->TxXferCount < SSI_HANDLE->TxXferSize)
    {
      /* ������������δΪ0���������� */
      if((SSCON0 & 0xC0) == UART1_Mode_11B)
      {
        /* ����9λ���� */
        SSI_UART1_SendData9(*(SSI_HANDLE->pTxBuffPtr.Size_u16 + SSI_HANDLE->TxXferCount));
      }
      else
      {
        /* ����8λ���� */
        SSI_UART1_SendData8(*(SSI_HANDLE->pTxBuffPtr.Size_u8 + SSI_HANDLE->TxXferCount));
      }
      return Status_BUSY;
    }
    else if(SSI_HANDLE->TxXferCount == SSI_HANDLE->TxXferSize)
    {
      /* ������� */
      SSI_HANDLE->TxState = SSI_STATE_READY;
      return Status_OK;
    }
    else
    {
      /* ����������Ϊ0ʱ���������ݣ����ش��� */
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
*��������:StatusTypeDef SSI_UART_Receive(SSI_HandleInfoDef* SSI_HANDLE, uint8_t *pData, uint8_t Size, uint32_t Timeout)
*��������:UART����ѯģʽ�½��մ�������
*��ڲ���:
SSI_SSI_HANDLEInfoDef*:SSI_HANDLE:ָ��ָ��SSI_UART������Ϣ�����
uint8_t *:pData:�������ݵĴ����
uint16_t:Size:�����յ�������
uint32_t:Timeout:��ʱʱ������
*���ڲ���:
StatusTypeDef:����ִ��״̬
*****************************************************/
StatusTypeDef SSI_UART_Receive(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
{
  uint32_t delaytime = 0;
  /* �����ս����������� */
  if(SSI_HANDLE->RxState == SSI_STATE_READY)
  {
    /* ��������������С���Ƿ�������ʹ�� */
    if((IE1 & 0x01 != 0) || (Size == 0U) || ((SSCON0 & 0x10) != UART1_RX_ENABLE))
    {
      return  Status_ERROR;
    }

    SSI_HANDLE->RxState = SSI_STATE_BUSY;			//���ͽ���æµ��
    SSI_ClearFlag(UART1_FLAG_RI);			 //����ǰ��������жϱ�־
    SSI_HANDLE->pRxBuffPtr.Size_u8 = pData;			//ָ����������ݵĵ�ַ
    SSI_HANDLE->RxXferSize = Size;			//���´����͵�������
    SSI_HANDLE->RxXferCount = 0;			//���ͼ���������

    while(SSI_HANDLE->RxXferCount < SSI_HANDLE->RxXferSize) //�ж��Ƿ������������
    {
      if(SSI_GetFlagStatus(UART1_FLAG_RI)) //�жϽ��ձ�־λ
      {
        SSI_ClearFlag(UART1_FLAG_RI);			//���ձ�־λ����

        /* ������������δΪ0���������� */
        if((SSCON0 & 0xC0) == UART1_Mode_11B)
        {
          /* ����9λ���� */
          *(SSI_HANDLE->pRxBuffPtr.Size_u16 + SSI_HANDLE->RxXferCount) = SSI_UART1_ReceiveData9();
        }
        else
        {
          /* ����8λ���� */
          *(SSI_HANDLE->pRxBuffPtr.Size_u8 + SSI_HANDLE->RxXferCount) = SSI_UART1_ReceiveData8();
        }

        SSI_HANDLE->RxXferCount++;	//��������������
        delaytime = 0;//�յ����ݣ���ʱ��������
      }
      if(delaytime++ > Timeout)//��ʱ���
      {
        SSI_HANDLE->RxState = SSI_STATE_TIMEOUT;//���ͳ�ʱ
        return Status_TIMEOUT;
      }
    }

    if(SSI_HANDLE->RxXferCount == SSI_HANDLE->RxXferSize)
    {
      SSI_HANDLE->RxState = SSI_STATE_READY;	//�������
      return Status_OK;
    }
    else
    {
      SSI_HANDLE->RxState = SSI_STATE_ERROR;//�������ʹ���
      return Status_ERROR;
    }
  }
  else
  {
    return Status_BUSY;//���ر�־λ
  }
}

/*****************************************************
*��������:StatusTypeDef SSI_UART_Receive_IT(SSI_HandleInfoDef *SSI_HANDLE, uint8_t *pData, uint8_t Size)
*��������:UART���ж�ģʽ�½��մ�������ʱ������main�����е��ô˺���
*��ڲ���:
SSI_SSI_HANDLEInfoDef*:SSI_HANDLE:ָ��ָ��UART������Ϣ�����
uint8_t *:pData:�������ݵĴ����
uint16_t:Size:�����յ�������
*���ڲ���:
StatusTypeDef:����ִ��״̬
*****************************************************/
StatusTypeDef SSI_UART_Receive_IT(SSI_HandleInfoDef* SSI_HANDLE, uint8_t* pData, uint8_t Size)
{
  /* ���һ�����ս����Ƿ����ڽ��� */
  if(SSI_HANDLE->RxState == SSI_STATE_READY)
  {
    /* ����Ƿ���SSI_UART�жϻ�����������СΪ0���Ƿ�������ʹ�ܣ����ش��� */
    if(((IE1 & 0x01) == 0) || (Size == 0U) || ((SSCON0 & 0x10) != UART1_RX_ENABLE))
    {
      return Status_ERROR;
    }

    SSI_HANDLE->RxState = SSI_STATE_BUSY;
    SSI_HANDLE->pRxBuffPtr.Size_u8 = pData;			//ָ��������ݵĴ�ŵ�ַ
    SSI_HANDLE->RxXferSize = Size;			//���´����յ�������
    SSI_HANDLE->RxXferCount = 0;			//���ͼ���������

    return Status_OK;
  }
  else
  {
    return Status_BUSY;//���ر�־λ
  }
}

/*****************************************************
*��������:StatusTypeDef SSI_UART_Receive_IRQHandler(SSI_HandleInfoDef* SSI_HANDLE)
*��������:UART���ж�ģʽ�½��մ�������ʱ�����жϷ������е���
*	ע���ú���������Ҫ�ж��жϱ�־λ�Ƿ�����
*��ڲ���:
SSI_HandleInfoDef*:SSI_HANDLE:ָ��ָ��SSI������Ϣ�����
*���ڲ���:
StatusTypeDef:����ִ��״̬
*****************************************************/
StatusTypeDef SSI_UART1_Receive_IRQHandler(SSI_HandleInfoDef* SSI_HANDLE)
{
  /* ���һ�����ս����Ƿ����ڽ��� */
  if(SSI_HANDLE->RxState == SSI_STATE_BUSY)
  {
    /* ���ڽ����̣߳����������������Ƿ�Ϊ0 */
    if(SSI_HANDLE->RxXferCount < SSI_HANDLE->RxXferSize)
    {
      /* ������������δΪ0���������� */
      if((SSCON0 & 0xC0) == UART1_Mode_11B)
      {
        /* ����9λ���� */
        *(SSI_HANDLE->pRxBuffPtr.Size_u16 + SSI_HANDLE->RxXferCount) = SSI_UART1_ReceiveData9();
      }
      else
      {
        /* ����8λ���� */
        *(SSI_HANDLE->pRxBuffPtr.Size_u8 + SSI_HANDLE->RxXferCount) = SSI_UART1_ReceiveData8();
      }
      SSI_HANDLE->RxXferCount ++;
      /* �ж���һ�η����Ƿ������һ�� */
      if(SSI_HANDLE->RxXferCount == SSI_HANDLE->RxXferSize)
      {
        /* ������� */
        SSI_HANDLE->RxState = SSI_STATE_READY;
      }
      return Status_OK;
    }
    else
    {
      /* ����������Ϊ0ʱ���������ݣ����ش��� */
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
*��������:void SSI_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:SSI�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
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
*��������:FlagStatus SSI_GetFlagStatus(SSI_Flag_TypeDef SSI_FLAG)
*��������:���SSI��־״̬
*��ڲ���:
SSI_Flag_TypeDef:SSI_FLAG:�����ȡ�ı�־λ
*���ڲ���:
FlagStatus:SSI��־λ����״̬
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
*��������:void SSI_ClearFlag(SSI_Flag_TypeDef SSI_FLAG)
*��������:���SSI��־״̬
*��ڲ���:
SSI_Flag_TypeDef:SSI_FLAG:��������ı�־λ
*���ڲ���:void
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
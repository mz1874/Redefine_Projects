//************************************************************
//  Copyright (c) �Ϸ����¶���������޹�˾
//	�ļ�����: 		rd8_gpio.c
//	����:					�¶���Ӧ���Ŷ�
//	ģ�鹦��: 		GPIO�̼��⺯��C�ļ�
//  ����������: 2022��5��13��
// 	�汾: 				V1.10006
//  ˵��:���ļ���������RD8ϵ��оƬ
//*************************************************************

#include "rd8_gpio.h"

/**************************************************
*��������:void GPIO_DeInit(void)
*��������:GPIO��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x)
void GPIO_DeInit(void)
{
  P0CON = P1CON = P2CON = P3CON = P4CON = P5CON = 0x00;
  P0PH = P1PH = P2PH = P3PH = P4PH = P2PH = 0x00;
  P0 = P1 = P2 = P3 = P4 = P5 = 0;
}
#endif
#if defined(RD8G05x) || defined(RD8T05x)
void GPIO_DeInit(void)
{
  P0CON = P1CON = P2CON = P5CON = 0x00;
  P0PH = P1PH = P2PH = P5PH = 0x00;
  P0 = P1 = P2 =  P5 = 0;
}
#endif
#if defined(RD8G403)
void GPIO_DeInit(void)
{
  P0CON = P1CON = P2CON = 0x00;
  P0PH = P1PH = P2PH = 0x00;
  P0 = P1 = P2 = 0;
}
#endif

/**************************************************
*��������:void GPIO_Init(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef PortPins, GPIO_Mode_TypeDef GPIO_Mode)
*��������:GPIO�����ó�ʼ��
*��ڲ���:
GPIO_TypeDef:GPIOx:��������GPIO��
GPIO_Pin_TypeDef:PortPins:GPIO�ܽ�Pxy��uint8_t��Ϊ��Σ��������λ�������
GPIO_Mode_TypeDef:GPIO_Mode:GPIO��ģʽ���������롢�������롢���������
*���ڲ���:void
**************************************************/
void GPIO_Init(GPIO_TypeDef GPIOx, uint8_t PortPins, GPIO_Mode_TypeDef GPIO_Mode)
{
  /* ѡ����Ҫ������GPIO */
  switch(GPIOx)
  {
    case GPIO0:
    {
      switch(GPIO_Mode)
      {
        /* ����IOΪ��������ģʽ */
        case GPIO_MODE_IN_HI:
          P0CON &= ~PortPins;
          P0PH &= ~PortPins;
          break;
        /* ����IOΪ��������ģʽ */
        case GPIO_MODE_IN_PU:
          P0CON &= ~PortPins;
          P0PH |= PortPins;
          break;
        /* ����IOΪ�������ģʽ */
        case GPIO_MODE_OUT_PP:
          P0CON |= PortPins;
          break;
        default:
          break;
      }
    }
    break;
    case GPIO1:
    {
      switch(GPIO_Mode)
      {
        /* ����IOΪ��������ģʽ */
        case GPIO_MODE_IN_HI:
          P1CON &= ~PortPins;
          P1PH &= ~PortPins;
          break;
        /* ����IOΪ��������ģʽ */
        case GPIO_MODE_IN_PU:
          P1CON &= ~PortPins;
          P1PH |= PortPins;
          break;
        /* ����IOΪ�������ģʽ */
        case GPIO_MODE_OUT_PP:
          P1CON |= PortPins;
          break;
        default:
          break;
      }
    }
    break;
    case GPIO2:
    {
      switch(GPIO_Mode)
      {
        /* ����IOΪ��������ģʽ */
        case GPIO_MODE_IN_HI:
          P2CON &= ~PortPins;
          P2PH &= ~PortPins;
          break;
        /* ����IOΪ��������ģʽ */
        case GPIO_MODE_IN_PU:
          P2CON &= ~PortPins;
          P2PH |= PortPins;
          break;
        /* ����IOΪ�������ģʽ */
        case GPIO_MODE_OUT_PP:
          P2CON |= PortPins;
          break;
        default:
          break;
      }
    }
    break;
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x)
    case GPIO3:
    {
      switch(GPIO_Mode)
      {
        /* ����IOΪ��������ģʽ */
        case GPIO_MODE_IN_HI:
          P3CON &= ~PortPins;
          P3PH &= ~PortPins;
          break;
        /* ����IOΪ��������ģʽ */
        case GPIO_MODE_IN_PU:
          P3CON &= ~PortPins;
          P3PH |= PortPins;
          break;
        /* ����IOΪ�������ģʽ */
        case GPIO_MODE_OUT_PP:
          P3CON |= PortPins;
          break;
        default:
          break;
      }
    }
    break;
    case GPIO4:
    {
      switch(GPIO_Mode)
      {
        /* ����IOΪ��������ģʽ */
        case GPIO_MODE_IN_HI:
          P4CON &= ~PortPins;
          P4PH &= ~PortPins;
          break;
        /* ����IOΪ��������ģʽ */
        case GPIO_MODE_IN_PU:
          P4CON &= ~PortPins;
          P4PH |= PortPins;
          break;
        /* ����IOΪ�������ģʽ */
        case GPIO_MODE_OUT_PP:
          P4CON |= PortPins;
          break;
        default:
          break;
      }
    }
    break;
#endif
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
    case GPIO5:
    {
      switch(GPIO_Mode)
      {
        /* ����IOΪ��������ģʽ */
        case GPIO_MODE_IN_HI:
          P5CON &= ~PortPins;
          P5PH &= ~PortPins;
          break;
        /* ����IOΪ��������ģʽ */
        case GPIO_MODE_IN_PU:
          P5CON &= ~PortPins;
          P5PH |= PortPins;
          break;
        /* ����IOΪ�������ģʽ */
        case GPIO_MODE_OUT_PP:
          P5CON |= PortPins;
          break;
        default:
          break;
      }
    }
    break;
#endif
    default:
      break;
  }
}

/**************************************************
*��������:void GPIO_Write(GPIO_TypeDef GPIOx, uint8_t PortVal)
*��������:GPIO�ڸ�ֵ
*��ڲ���:
GPIO_TypeDef:GPIOx:��������GPIO��
uint8_t:PortVal:GPIO�ڵ�ֵ
*���ڲ���:void
**************************************************/
void GPIO_Write(GPIO_TypeDef GPIOx, uint8_t PortVal)
{
  /* ѡ����Ҫ������GPIO */
  switch(GPIOx)
  {
    case GPIO0:
      P0 = PortVal;
      break;
    case GPIO1:
      P1 = PortVal;
      break;
    case GPIO2:
      P2 = PortVal;
      break;
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x)
    case GPIO3:
      P3 = PortVal;
      break;
    case GPIO4:
      P4 = PortVal;
      break;
#endif
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
    case GPIO5:
      P5 = PortVal;
      break;
#endif
    default:
      break;
  }
}

/**************************************************
*��������:void GPIO_WriteHigh(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef PortPins)
*��������:GPIO�ڹܽ�Pxy��λ
*��ڲ���:
GPIO_TypeDef:GPIOx:��������GPIO��
GPIO_Pin_TypeDef:PortPins:ѡ��GPIO�ڹܽ�Pxy��uint8_t��Ϊ��Σ��������λ�������
*���ڲ���:void
**************************************************/
void GPIO_WriteHigh(GPIO_TypeDef GPIOx, uint8_t PortPins)
{
  /* ѡ����Ҫ������GPIO */
  switch(GPIOx)
  {
    case GPIO0:
      P0 |= PortPins;
      break;
    case GPIO1:
      P1 |= PortPins;
      break;
    case GPIO2:
      P2 |= PortPins;
      break;
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x)
    case GPIO3:
      P3 |= PortPins;
      break;
    case GPIO4:
      P4 |= PortPins;
      break;
#endif
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
    case GPIO5:
      P5 |= PortPins;
#endif
      break;
    default:
      break;
  }
}

/**************************************************
*��������:void GPIO_WriteLow(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef PortPins)
*��������:GPIO�ڹܽ�Pxy��λ
*��ڲ���:
GPIO_TypeDef:GPIOx:��������GPIO��
GPIO_Pin_TypeDef:PortPins:ѡ��GPIO�ڹܽ�Pxy��uint8_t��Ϊ��Σ��������λ�������
*���ڲ���:void
**************************************************/
void GPIO_WriteLow(GPIO_TypeDef GPIOx, uint8_t PortPins)
{
  /* ѡ����Ҫ������GPIO */
  switch(GPIOx)
  {
    case GPIO0:
      P0 &= ~PortPins;
      break;
    case GPIO1:
      P1 &= ~PortPins;
      break;
    case GPIO2:
      P2 &= ~PortPins;
      break;
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x)
    case GPIO3:
      P3 &= ~PortPins;
      break;
    case GPIO4:
      P4 &= ~PortPins;
      break;
#endif
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
    case GPIO5:
      P5 &= ~PortPins;
      break;
#endif
    default:
      break;
  }
}

/**************************************************
*��������:uint8_t GPIO_ReadPort(GPIO_TypeDef GPIOx)
*��������:��GPIO��Px��ֵ
*��ڲ���:
GPIO_TypeDef:GPIOx:��������GPIO��
*���ڲ���:
uint8_t:����Px��ֵ
**************************************************/
uint8_t GPIO_ReadPort(GPIO_TypeDef GPIOx)
{
  /* ѡ����Ҫ������GPIO */
  switch(GPIOx)
  {
    case GPIO0:
      return P0;
    case GPIO1:
      return P0;
    case GPIO2:
      return P0;
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x)
    case GPIO3:
      return P0;
    case GPIO4:
      return P0;
#endif
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
    case GPIO5:
      return P0;
#endif
    default:
      return 0;
  }
}

/**************************************************
*��������:BitStatus GPIO_ReadPin(GPIO_TypeDef GPIOx, uint8_t PortPins)
*��������:��GPIO�ڹܽ�Pxy��ֵ
*��ڲ���:
GPIO_TypeDef:GPIOx:��������GPIO��
GPIO_Pin_TypeDef:PortPins:ѡ��GPIO�ڹܽ�Pxy��uint8_t��Ϊ��Σ��������λ�������
*���ڲ���:
BitStatus:����Pxy��ֵ
**************************************************/
BitStatus GPIO_ReadPin(GPIO_TypeDef GPIOx, uint8_t PortPins)
{
  /* ѡ����Ҫ������GPIO */
  switch(GPIOx)
  {
    case GPIO0:
      return (P0 & PortPins);
    case GPIO1:
      return (P1 & PortPins);
    case GPIO2:
      return (P2 & PortPins);
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x)
    case GPIO3:
      return (P3 & PortPins);
    case GPIO4:
      return (P4 & PortPins);
#endif
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
    case GPIO5:
      return (P5 & PortPins);
#endif
    default:
      return 0;
  }
}

/**************************************************
*��������:BitStatus GPIO_TogglePin(GPIO_TypeDef GPIOx, uint8_t PortPins)
*��������:��תGPIO�ڹܽ�Pxy��ֵ
*��ڲ���:
GPIO_TypeDef:GPIOx:��������GPIO��
GPIO_Pin_TypeDef:PortPins:ѡ��GPIO�ڹܽ�Pxy��uint8_t��Ϊ��Σ��������λ�������
*���ڲ���:
BitStatus:����Pxy��ֵ
**************************************************/
void GPIO_TogglePin(GPIO_TypeDef GPIOx, uint8_t PortPins)
{
  /* ѡ����Ҫ������GPIO */
  switch(GPIOx)
  {
    case GPIO0:
      P0 = (P0) ^ PortPins;
      break;
    case GPIO1:
      P1 = (P1) ^ PortPins;
      break;
    case GPIO2:
      P2 = (P2) ^ PortPins;
      break;
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x)
    case GPIO3:
      P3 = (P3) ^ PortPins;
      break;
    case GPIO4:
      P4 = (P4) ^ PortPins;
      break;
#endif
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
    case GPIO5:
      P5 = (P5) ^ PortPins;
      break;
#endif
    default:
      break;
  }
}

#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
/**************************************************
*��������:void GPIO_IOH_Config(GPIO_TypeDef GPIOx, uint8_t PortPins,GPIO_IOH_Grade_TypeDef GPIO_IOH_Grade)
*��������:����GPIO�ڹܽ�IOH�������
*��ڲ���:
GPIO_TypeDef:GPIOx:��������GPIO��
GPIO_Pin_TypeDef:PortPins:ѡ��GPIO�ڹܽ�Pxy
GPIO_IOH_Grade_TypeDef:GPIO_IOH_Grade:ѡ��IOH������ȼ�
*���ڲ���:void
**************************************************/
void GPIO_IOH_Config(GPIO_TypeDef GPIOx, GPIO_Pin_TypeDef PortPins, GPIO_IOH_Grade_TypeDef GPIO_IOH_Grade)
{
  /* ѡ����Ҫ������GPIO */
  switch(GPIOx)
  {
    case GPIO0:
      if(PortPins == GPIO_PIN_LNIB)
      {
        IOHCON0 &= 0xFC;
        IOHCON0 |= GPIO_IOH_Grade;
      }
      else if(PortPins == GPIO_PIN_HNIB)
      {
        IOHCON0 &= 0xF3;
        IOHCON0 |= GPIO_IOH_Grade << 2;
      }
      break;
    case GPIO1:
      if(PortPins == GPIO_PIN_LNIB)
      {
        IOHCON0 &= 0xCF;
        IOHCON0 |= GPIO_IOH_Grade << 4;
      }
      else if(PortPins == GPIO_PIN_HNIB)
      {
        IOHCON0 &= 0x3F;
        IOHCON0 |= GPIO_IOH_Grade << 6;
      }
      break;
    case GPIO2:
      if(PortPins == GPIO_PIN_LNIB)
      {
        IOHCON1 &= 0xFC;
        IOHCON1 |= GPIO_IOH_Grade;
      }
      else if(PortPins == GPIO_PIN_HNIB)
      {
        IOHCON1 &= 0xF3;
        IOHCON1 |= GPIO_IOH_Grade << 2;
      }
      break;
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x)
    case GPIO3:
      if(PortPins == GPIO_PIN_LNIB)
      {
        IOHCON1 &= 0xCF;
        IOHCON1 |= GPIO_IOH_Grade << 4;
      }
      break;
#endif
    default:
      break;
  }
}
#endif

/******************* (C) COPYRIGHT 2022 RDS Microelectronics *****END OF FILE****/
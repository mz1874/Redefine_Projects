//************************************************************
//  Copyright (c) �Ϸ����¶���������޹�˾
//	�ļ�����: 		rd8_timer2.c
//	����:					�¶���Ӧ���Ŷ�
//	ģ�鹦��: 		TIMER2�̼��⺯��C�ļ�
//  ����������: 2022��5��13��
// 	�汾: 				V1.10001
//  ˵��:���ļ���������RD8ϵ��оƬ
//*************************************************************

#include "rd8_timer2.h"

#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)

/**************************************************
*��������:void TIM2_DeInit(void)
*��������:TIMER2��ؼĴ�����λ����ʼֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void TIM2_DeInit()
{
  TXINX = 0x02; //TIMER2ѡ��
  TXCON = 0X00;
  TXMOD = 0X00;
  RCAPXH = 0X00;
  RCAPXL = 0X00;
  THX = 0X00;
  TLX = 0X00;
  IE1 &= 0X3F;
  IP1 &= 0X3F;
  ET2 = 0;
  IPT2 = 0;
}

/**************************************************
*��������:void TIM2_PrescalerSelection(TIM2_PresSel_TypeDef TIM2_PrescalerSelection)
*��������:TIMER2 Ԥ��Ƶѡ��
*��ڲ���:
TIM2_PresSel_TypeDef:TIM2_PrescalerSelection:Ԥ��Ƶѡ��
*���ڲ���:void
**************************************************/
void TIM2_PrescalerSelection(TIM2_PresSel_TypeDef TIM2_PrescalerSelection)
{
  TXINX = 0x02;

  if(TIM2_PrescalerSelection == TIM2_PRESSEL_FSYS_D12)
  {
    TXMOD &= 0X7F;
  }
  else if(TIM2_PrescalerSelection == TIM2_PRESSEL_FSYS_D1)
  {
    TXMOD |= 0X80;
  }
}

#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x)
/**************************************************
*��������:void TIM2_TimeBaseInit(TIM2_PresSel_TypeDef TIM2_PrescalerSelection,TIM2_CountMode_TypeDef TIM2_CountMode, TIM2_CountDirection_TypeDef TIM2_CountDirection)
*��������:TIMER2�����������ú���
*��ڲ���:
TIM2_PresSel_TypeDef:TIM2_PrescalerSelection:Ԥ��Ƶѡ��
TIM2_CountMode_TypeDef:TIM2_CountMode:����/��ʱģʽѡ��
TIM2_CountDirection_TypeDef:TIM2_CountDirection:��������ѡ��
*���ڲ���:void
**************************************************/
void TIM2_TimeBaseInit(TIM2_PresSel_TypeDef
                       TIM2_PrescalerSelection,
                       TIM2_CountMode_TypeDef TIM2_CountMode,
                       TIM2_CountDirection_TypeDef TIM2_CountDirection)
{
  TXINX = 0x02;
  /* ������ǰ�汾�����÷� */
  if((TIM2_CountMode == TIM2_COUNTDIRECTION_UP) || (TIM2_CountMode == TIM2_COUNTDIRECTION_DOWN_UP))
  {
    /* ��һ�����Ϊ ����/��ʱģʽѡ�� */
    if(TIM2_PrescalerSelection == TIM2_MODE_TIMER)
    {
      TXCON &= 0XFD;
    }
    else if(TIM2_PrescalerSelection == TIM2_MODE_COUNTER)
    {
      TXCON |= 0X02;
    }
    /* �ڶ������Ϊ ��������ѡ�� */
    if(TIM2_CountMode == TIM2_COUNTDIRECTION_UP)
    {
      TXMOD &= 0XFE;
    }
    else if(TIM2_CountMode == TIM2_COUNTDIRECTION_DOWN_UP)
    {
      TXMOD |= 0X01;
    }
  }
  else  /* н�汾�����������������չΪ���� */
  {
    /* Ԥ�������� */
    if(TIM2_PrescalerSelection == TIM2_PRESSEL_FSYS_D12)
    {
      TXMOD &= 0XFB;
    }
    else if(TIM2_PrescalerSelection == TIM2_PRESSEL_FSYS_D1)
    {
      TXMOD |= 0X04;
    }
    /* ��ʱ��ģʽ����*/
    if(TIM2_CountMode == TIM2_MODE_TIMER)
    {
      TXCON &= 0XFD;
    }
    else if(TIM2_CountMode == TIM2_MODE_COUNTER)
    {
      TXCON |= 0X02;
    }
    if(TIM2_CountDirection == TIM2_COUNTDIRECTION_UP)
    {
      TXMOD &= 0XFE;
    }
    else if(TIM2_CountDirection == TIM2_COUNTDIRECTION_DOWN_UP)
    {
      TXMOD |= 0X01;
    }
  }
}
#else
/**************************************************
*��������:void TIM2_TimeBaseInit(TIM2_PresSel_TypeDef TIM2_PrescalerSelection,TIM2_CountMode_TypeDef TIM2_CountMode, TIM2_CountDirection_TypeDef TIM2_CountDirection)
*��������:TIMER2�����������ú���
*��ڲ���:
TIM2_PresSel_TypeDef:TIM2_PrescalerSelection:Ԥ��Ƶѡ��
TIM2_CountMode_TypeDef:TIM2_CountMode:����/��ʱģʽѡ��
TIM2_CountDirection_TypeDef:TIM2_CountDirection:��������ѡ��
*���ڲ���:void
**************************************************/
void TIM2_TimeBaseInit(TIM2_PresSel_TypeDef
                       TIM2_PrescalerSelection,
                       TIM2_CountMode_TypeDef TIM2_CountMode,
                       TIM2_CountDirection_TypeDef TIM2_CountDirection)
{
  if(TIM2_PrescalerSelection == TIM2_PRESSEL_FSYS_D12)
  {
    TXMOD &= 0XFB;
  }
  else if(TIM2_PrescalerSelection == TIM2_PRESSEL_FSYS_D1)
  {
    TXMOD |= 0X04;
  }

  if(TIM2_CountDirection == TIM2_COUNTDIRECTION_UP)
  {
    TXMOD &= 0XFE;
  }
  else if(TIM2_CountDirection ==
          TIM2_COUNTDIRECTION_DOWN_UP)
  {
    TXMOD |= 0X01;
  }

  if(TIM2_CountMode == TIM2_MODE_TIMER)
  {
    TXMOD &= 0XFD;
  }
  else if(TIM2_CountMode == TIM2_MODE_COUNTER)
  {
    TXMOD |= 0X02;
  }
}


#endif

/**************************************************
*��������:void TIM2_WorkMode0Config(uint16_t TIM2_SetCounter)
*��������:TIMER2����ģʽ0���ú���
*��ڲ���:
uint16_t:TIM2_SetCounter:���ü�����ֵ
*���ڲ���:void
**************************************************/
void TIM2_WorkMode0Config(uint16_t TIM2_SetCounter)
{
  TXINX = 0x02;
  CP = 1;
  TLX = TIM2_SetCounter % 256;
  THX = TIM2_SetCounter / 256;
}

/**************************************************
*��������:void TIM2_WorkMode1Config(uint16_t TIM2_SetCounter)
*��������:TIMER2����ģʽ1���ú���
*��ڲ���:
uint16_t:TIM2_SetCounter:���ü�����ֵ
*���ڲ���:void
**************************************************/
void TIM2_WorkMode1Config(uint16_t TIM2_SetCounter)
{
  TXINX = 0x02;
  RCAPXL = TIM2_SetCounter % 256;
  RCAPXH = TIM2_SetCounter / 256;

  TLX = RCAPXL;
  THX = RCAPXH;
}

/**************************************************
*��������:void TIM2_WorkMode3Config(uint16_t TIM2_SetCounter)
*��������:TIMER2����ģʽ3���ú���
*��ڲ���:
uint16_t:TIM2_SetCounter:���ü�����ֵ
*���ڲ���:void
**************************************************/
void TIM2_WorkMode3Config(uint16_t TIM2_SetCounter)
{
  TXINX = 0x02;
  RCAPXL = TIM2_SetCounter % 256;
  RCAPXH = TIM2_SetCounter / 256;
  TXMOD |= 0X02;
}
/**************************************************
*��������:void TIM2_WorkModeConfig(TIM2_WorkMode_TypeDef TIM2_WorkMode, uint16_t TIM2_SetCounter)
*��������:TIMER2����ģʽ���ú���
*��ڲ���:
TIM2_WorkMode_TypeDef:TIM2_WorkMode:TIMER2����ģʽѡ��
uint16_t:TIM2_SetCounter:TIMER2������ֵ����
*���ڲ���:void
**************************************************/
void TIM2_WorkModeConfig(TIM2_WorkMode_TypeDef TIM2_WorkMode, uint16_t TIM2_SetCounter)
{
  switch(TIM2_WorkMode)
  {
    case TIM2_WORK_MODE0:
      TIM2_WorkMode0Config(TIM2_SetCounter);
      break;

    case TIM2_WORK_MODE1:
      TIM2_WorkMode1Config(TIM2_SetCounter);
      break;

    case TIM2_WORK_MODE3:
      TIM2_WorkMode3Config(TIM2_SetCounter);
      break;

    default:
      break;
  }
}
/*****************************************************
*��������:void TIM2_SetEXEN2(FunctionalState NewState)
*��������:TIMER2_EXEN2���ú���
*��ڲ���:
FunctionalState:NewState:EXEN2ʹ��ѡ��
*���ڲ���:void
*****************************************************/
void TIM2_SetEXEN2(FunctionalState NewState)
{
  TXINX = 0x02;

  if(NewState == DISABLE)
  {
    EXENX = 0;
  }
  else
  {
    EXENX = 1;
  }
}

/*****************************************************
*��������:void TIM2_Cmd(FunctionalState NewState)
*��������:TIMER2���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void TIM2_Cmd(FunctionalState NewState)
{
  TXINX = 0x02;

  if(NewState == DISABLE)
  {
    TRX = 0;
  }
  else
  {
    TRX = 1;
  }
}

/*******************************�꺯��*******************************/
/*****************************************************
*��������:uint16_t TIM2_GetCapture(void)
*��������:TIM2������ģʽ2ʱ����ȡ����ֵ
*��ڲ���:
*���ڲ���:
uint16_t:��ȡ���Ĳ���ֵ
*****************************************************/
uint16_t TIM2_GetCapture(void)
{
  TXINX = 0x02;
  return (((uint16_t)RCAPXH << 8) | RCAPXL);
}

/*****************************************************
*��������:uint16_t TIM2_GetCounter(void)
*��������:��ȡTIM2��ǰ����ֵ
*��ڲ���:
*���ڲ���:
uint16_t:��ȡ���Ĳ���ֵ
*****************************************************/
uint16_t TIM2_GetCounter(void)
{
  TXINX = 0x02;
  return (((uint16_t)THX << 8) | TLX);
}

/*****************************************************
*��������:void TIM2_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:TIMER2
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void TIM2_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  TXINX = 0x02;

  if(NewState == DISABLE)
  {
    ET2 = 0;
  }
  else
  {
    ET2 = 1;
  }

  if(Priority == LOW)
  {
    IPT2 = 0;
  }
  else
  {
    IPT2 = 1;
  }
}

/*****************************************************
*��������:FlagStatus TIM2_GetFlagStatus(void)
*��������:���TIMER2�жϱ�־״̬
*��ڲ���:
TIM2_Flag_TypeDef:TIM2_Flag:TIMER2��־ѡ��
*���ڲ���:
FlagStatus:TIMER2�жϱ�־״̬
*****************************************************/
FlagStatus TIM2_GetFlagStatus(TIM2_Flag_TypeDef TIM2_Flag)
{
  FlagStatus status = RESET;
  TXINX = 0x02;

  if((TIM2_Flag & TXCON) != (uint8_t)RESET)
  {
    status = SET;
  }
  else
  {
    status = RESET;
  }

  return status;
}

/*****************************************************
*��������:void TIMX_ClearFlag(void)
*��������:���TIMER2�жϱ�־״̬
*��ڲ���:
TIM2_Flag_TypeDef:TIM2_Flag:TIMER2��־ѡ��
*���ڲ���:void
*****************************************************/
void TIM2_ClearFlag(TIM2_Flag_TypeDef TIM2_Flag)
{
  TXINX = 0x02;
  TXCON &= (~TIM2_Flag);
}

#endif

#if defined (RD8G403)

/**************************************************
*��������:void TIM2_DeInit(void)
*��������:TIMER2��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void TIM2_DeInit(void)
{
  T2CON = 0X00;
  T2MOD = 0X00;
  TMCON &= 0XFB;
  TH2 = 0X00;
  TL2 = 0X00;
  RCAP2H = 0X00;
  RCAP2L = 0X00;
  ET2 = 0;
  IPT2 = 0;
}

/**************************************************
*��������:void TIM2_TimeBaseInit(TIM2_PresSel_TypeDef TIM2_PrescalerSelection,TIM2_CountMode_TypeDef TIM2_CountMode, TIM2_CountDirection_TypeDef TIM2_CountDirection)
*��������:TIMER2�����������ú���
*��ڲ���:
TIM2_PresSel_TypeDef:TIM2_PrescalerSelection:Ԥ��Ƶѡ��
TIM2_CountMode_TypeDef:TIM2_CountMode:����/��ʱģʽѡ��
TIM2_CountDirection_TypeDef:TIM2_CountDirection:��������ѡ��
*���ڲ���:void
**************************************************/
void TIM2_TimeBaseInit(TIM2_PresSel_TypeDef
                       TIM2_PrescalerSelection,
                       TIM2_CountMode_TypeDef TIM2_CountMode,
                       TIM2_CountDirection_TypeDef TIM2_CountDirection)
{
  if(TIM2_PrescalerSelection == TIM2_PRESSEL_FSYS_D12)
  {
    TMCON &= 0XFB;
  }
  else if(TIM2_PrescalerSelection == TIM2_PRESSEL_FSYS_D1)
  {
    TMCON |= 0X04;
  }
  if(TIM2_CountDirection == TIM2_COUNTDIRECTION_UP)
  {
    T2MOD &= 0XFE;
  }
  else if(TIM2_CountDirection ==
          TIM2_COUNTDIRECTION_DOWN_UP)
  {
    T2MOD |= 0X01;
  }

  if(TIM2_CountMode == TIM2_MODE_TIMER)
  {
    T2CON &= 0XFD;
  }
  else if(TIM2_CountMode == TIM2_MODE_COUNTER)
  {
    T2CON |= 0X02;
  }

}


/**************************************************
*��������:void TIM2_WorkMode1Config(uint16_t TIM2_SetCounter)
*��������:TIMER2����ģʽ1���ú���
*��ڲ���:
uint16_t:TIM2_SetCounter:���ü�����ֵ
*���ڲ���:void
**************************************************/
void TIM2_WorkMode1Config(uint16_t
                          TIM2_SetCounter)
{
  RCAP2L = TIM2_SetCounter % 256;
  RCAP2H = TIM2_SetCounter / 256;
  TL2 = RCAP2L;
  TH2 = RCAP2H;
}

/**************************************************
*��������:void TIM2_WorkModeConfig(TIM2_WorkMode_TypeDef TIM2_WorkMode, uint16_t TIM2_SetCounter)
*��������:TIMER2����ģʽ���ú���
*��ڲ���:
TIM2_WorkMode_TypeDef:TIM2_WorkMode:TIMER2����ģʽѡ��
uint16_t:TIM2_SetCounter:TIMER2������ֵ����
*���ڲ���:void
**************************************************/
void TIM2_WorkModeConfig(TIM2_WorkMode_TypeDef
                         TIM2_WorkMode, uint16_t TIM2_SetCounter)
{
  switch(TIM2_WorkMode)
  {
    case TIM2_WORK_MODE1:
      TIM2_WorkMode1Config(TIM2_SetCounter);
      break;
    case TIM2_WORK_MODE0:
      TIM2_WorkMode0Config(TIM2_SetCounter);
      break;
    case TIM2_WORK_MODE3:
      TIM2_WorkMode3Config(TIM2_SetCounter);
      break;
    default:
      break;
  }
}

/**************************************************
*��������:void TIM2_WorkMode0Config(uint16_t TIM2_SetCounter)
*��������:TIMER2����ģʽ0���ú���
*��ڲ���:
uint16_t:TIM2_SetCounter:���ü�����ֵ
*���ڲ���:void
**************************************************/
void TIM2_WorkMode0Config(uint16_t
                          TIM2_SetCounter)
{
  T2CON |= 0x09;
  TL2 = TIM2_SetCounter % 256;
  TH2 = TIM2_SetCounter / 256;
}

/**************************************************
*��������:void TIM2_WorkMode3Config(uint16_t TIM2_SetCounter)
*��������:TIMER2����ģʽ3���ú���
*��ڲ���:
uint16_t:TIM2_SetCounter:���ü�����ֵ
*���ڲ���:void
**************************************************/
void TIM2_WorkMode3Config(uint16_t
                          TIM2_SetCounter)
{
  RCAP2L = TIM2_SetCounter % 256;
  RCAP2H = TIM2_SetCounter / 256;
  T2MOD |= 0X02;
}

/*****************************************************
*��������:void TIM2_SetEXEN2(FunctionalState NewState)
*��������:TIMER2_EXEN2���ú���
*��ڲ���:
FunctionalState:NewState:EXEN2ʹ��ѡ��
*���ڲ���:void
*****************************************************/
void TIM2_SetEXEN2(FunctionalState NewState)
{
  if(NewState == DISABLE)
  {
    EXEN2 = 0;
  }
  else
  {
    EXEN2 = 1;
  }
}

/*****************************************************
*��������:void TIM2_Cmd(FunctionalState NewState)
*��������:TIMER2���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void TIM2_Cmd(FunctionalState NewState)
{
  if(NewState == DISABLE)
  {
    TR2 = 0;
  }
  else
  {
    TR2 = 1;
  }
}

/*****************************************************
*��������:void TIM2_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:TIMER2�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void TIM2_ITConfig(FunctionalState NewState,
                   PriorityStatus Priority)
{
  if(NewState == DISABLE)
  {
    ET2 = 0;
  }
  else
  {
    ET2 = 1;
  }

  /************************************************************/
  if(Priority == LOW)
  {
    IPT2 = 0;
  }
  else
  {
    IPT2 = 1;
  }
}

/*****************************************************
*��������:FlagStatus TIM2_GetFlagStatus(void)
*��������:���TIMER2�жϱ�־״̬
*��ڲ���:void
*���ڲ���:
FlagStatus:TIMER2�жϱ�־״̬
*****************************************************/
FlagStatus TIM2_GetFlagStatus(TIM2_Flag_TypeDef
                              TIM2_Flag)
{
  FlagStatus status = RESET;

  if((TIM2_Flag & T2CON) != (uint8_t)RESET)
  {
    status = SET;
  }
  else
  {
    status = RESET;
  }

  return status;
}

/*****************************************************
*��������:void TIM2_ClearFlag(void)
*��������:���TIMER2�жϱ�־״̬
*��ڲ���:void
*���ڲ���:void
*****************************************************/
void TIM2_ClearFlag(TIM2_Flag_TypeDef TIM2_Flag)
{
  T2CON &= (~TIM2_Flag);
}

#endif

/******************* (C) COPYRIGHT 2021 SinOne Microelectronics *****END OF FILE****/
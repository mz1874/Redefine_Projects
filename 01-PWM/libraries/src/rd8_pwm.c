//************************************************************
//  Copyright (c) �Ϸ����¶���������޹�˾
//	�ļ�����:			rd8_pwm.c
//	����:					�¶���Ӧ���Ŷ�
//	ģ�鹦��:			PWM�̼��⺯��C�ļ�
// ����������:	2022��6��9��
//	�汾:					V1.001
// ˵��:���ļ���������RD8ϵ��оƬ
//*************************************************************

#include "rd8_pwm.h"
//PWM2/3/4��TIM2/3/4���üĴ���
#include "rd8_timer2.h"
#include "rd8_timer3.h"
#include "rd8_timer4.h"

#include "string.h"

#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x)

uint16_t xdata PWMREG[14] _at_ 0x2034; //PWMռ�ձȵ��ڼĴ���

/**************************************************
*��������:void PWM_DeInit(void)
*��������:PWM0��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void PWM_DeInit(void)
{
  uint8_t i;
  //PWM0��ؼĴ�������
  PWMCON0 = 0X00;
  PWMCFG = 0X00;
  PWMCON1 = 0X00;
  PWMPDL = 0x00;
  PWMPDH = 0x00;
  IE1 &= 0XFD;
  IP1 &= 0XFD;

  //ռ�ձȼĴ���
  for(i = 0; i < 8; i++)
  {
    *(&PWMREG[6] + i) = 0;
  }
}

/**************************************************
*��������:void PWM_InitEX(PWM_Type_TypeDef PWM_Type)
*��������:PWM0��ؼĴ�����λ��ȱʡֵ
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWMԴ
*���ڲ���:void
**************************************************/
void PWM_DeInitEX(PWM_Type_TypeDef PWM_Type)
{
  /* PWM0��ؼĴ�����λ������ֵ */
  if(PWM_Type == PWM0_Type)
  {
    uint8_t i;

    //PWM0��ؼĴ�������
    PWMCON0 = 0X00;
    PWMCFG = 0X00;
    PWMCON1 = 0X00;
    PWMPDL = 0x00;
    PWMPDH = 0x00;
    IE1 &= 0XFD;
    IP1 &= 0XFD;

    //ռ�ձȼĴ���
    for(i = 0; i < 8; i++)
    {
      *(&PWMREG[6] + i) = 0;
    }
  }
  else /* PWM2/3/4��ؼĴ�����λ������ֵ */
  {
    TXINX = PWM_Type;
    TXCON &= ~0x04;
    TXMOD &= ~0x3C;

    switch(PWM_Type)
    {
      case PWM2_Type:
        ET2 = 0;
        IP &= ~0x20;
        (uint32_t)PWMREG[0] = 0;
        break;
      case PWM3_Type:
        IE1 &= ~0x40;
        IP1 &= ~0x40;
        (uint32_t)PWMREG[2] = 0;
        break;
      case PWM4_Type:
        IE1 &= ~0x80;
        IP1 &= ~0x80;
        (uint32_t)PWMREG[4] = 0;
        break;
    }
  }
}

/**************************************************
*��������:PWM_Init(PWM_Type_TypeDef PWM_Type,PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period)
*��������:PWM��ʼ�����ú���
*��ڲ���:
PWM_PresSel_TypeDef:PWM_PresSel:Ԥ��Ƶѡ��
uint16_t:PWM_Period:PWM��������
*���ڲ���:void
**************************************************/
void PWM_Init(PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period)
{
  if((PWM_PresSel & 0X0F) == PWM0_Type)
  {
    PWM_Period -= 1;
    PWMCON0 = (PWMCON0 & 0XCF) | (PWM_PresSel & 0XF0); //Ԥ��Ƶ
    PWMPDH = (uint8_t)(PWM_Period >> 8);               //���ڸ�8λ
    PWMPDL = (uint8_t)(PWM_Period & 0X00FF);           //���ڵ�8λ
  }
  else
  {
    TXINX = (PWM_PresSel & 0X0F);							//���ƼĴ���ָ��ָ���Ӧ��PWMԴ
    PWM_PresSel = DISABLE;										//PWM2��ƵΨһ����������
    RCAPXH = (uint8_t)(PWM_Period >> 8);			//���ڸ�8λ
    RCAPXL = (uint8_t)(PWM_Period & 0X00FF);	//���ڵ�8λ
  }
}

/*****************************************************
*��������:void PWM_Aligned_Mode_Select(void)
*��������:ѡ��PWM�Ķ���ģʽ
*��ڲ���:
PWM_Aligned_Mode_TypeDef:PWM_Aligned_Mode:ѡ�����ģʽ
*���ڲ���:void
*****************************************************/
void PWM_Aligned_Mode_Select(PWM_Aligned_Mode_TypeDef PWM_Aligned_Mode)
{

  //PWM0ѡ�����ģʽ����
  if(PWM_Aligned_Mode == PWM0_Edge_Aligned_Mode)
  {
    PWMCON0 &= 0XFE;
  }
  else if(PWM_Aligned_Mode == PWM0_Center_Alignment_Mode)
  {
    PWMCON0 |= 0X01;
  }
}

/**************************************************
*��������:void PWM_OutputStateConfig(uint8_t PWM_OutputPin, PWM_OutputState_TypeDef PWM_OutputState)
*��������:PWMx���ʹ��/ʧ�����ú���
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMxѡ��uint8_t��Ϊ��Σ��������λ�������
PWM_OutputState_TypeDef:PWM_OutputState:PWM���״̬����
*���ڲ���:void
**************************************************/
void PWM_OutputStateConfig(uint8_t PWM_OutputPin,
                           PWM_OutputState_TypeDef PWM_OutputState)
{
  unsigned char Reg_Data;
  if((PWM_OutputPin & 0xF0) == 0x00)
  {
    if(PWM_OutputState == PWM_OUTPUTSTATE_ENABLE)
    {
      PWMCON1 |= 1 << (PWM_OutputPin & 0x0F);
    }
    else
    {
      PWMCON1 &= ~(1 << (PWM_OutputPin & 0x0F));
    }
  }
  else
  {
    TXINX = (PWM_OutputPin & 0xF0) >> 4;

    if(PWM_OutputPin & 0x01)
    {
      Reg_Data = 0x20;
    }
    else
    {
      Reg_Data = 0x10;
    }

    if(PWM_OutputState == PWM_OUTPUTSTATE_ENABLE)
    {
      TXMOD |= Reg_Data;
    }
    else
    {
      TXMOD &= ~Reg_Data;
    }
  }
}

/**************************************************
*��������:void PWM_PolarityConfig(PWM_OutputPin_TypeDef PWM_OutputPin, PWM_Polarity_TypeDef PWM_Polarity)
*��������:PWMx��/����������ú���
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMxѡ��uint8_t��Ϊ��Σ��������λ�������
PWM_Polarity_TypeDef:PWM_Polarity:PWM�����/��������
*���ڲ���:void
**************************************************/
void PWM_PolarityConfig(uint8_t PWM_OutputPin,
                        PWM_Polarity_TypeDef PWM_Polarity)
{
  unsigned char Reg_Data;
  if((PWM_OutputPin & 0xF0) == 0x00)
  {
    if(PWM_Polarity == PWM_POLARITY_INVERT)
    {
      PWMCFG |= 1 << (PWM_OutputPin & 0x0F);
    }
    else
    {
      PWMCFG &= ~(1 << (PWM_OutputPin & 0x0F));
    }
  }
  else
  {
    TXINX = (PWM_OutputPin & 0xF0) >> 4;

    if(PWM_OutputPin & 0x0F)
    {
      Reg_Data = 0x08;
    }
    else
    {
      Reg_Data = 0x04;
    }

    if(PWM_Polarity == PWM_POLARITY_INVERT)
    {
      TXMOD |= Reg_Data;
    }
    else
    {
      TXMOD &= ~Reg_Data;
    }
  }
}

/**************************************************
*��������:void PWM_IndependentModeConfig(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle)
*��������:PWMx��������ģʽռ�ձ����ú���
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMx����ͨ��ѡ��
uint16_t:PWM_DutyCycle:PWMռ�ձ�����
*���ڲ���:void
**************************************************/
void PWM_IndependentModeConfig(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle)
{
  if((PWM_OutputPin & 0xF0) == 0x00)
  {
    PWMCON0 &= ~0x02;				//����Ϊ����ģʽ
    PWMREG[6 + PWM_OutputPin] = PWM_DutyCycle;
  }
  else
  {
    PWMREG[PWM_OutputPin & 0x0F] = PWM_DutyCycle;
  }
}

/**************************************************
*��������:void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin, uint16_t PWM_DutyCycle)
*��������:PWMxPWMy��������ģʽ���ú���
*��ڲ���:
PWM_ComplementaryOutputPin_TypeDef:PWM_ComplementaryOutputPin:PWMxPWMy����ͨ��ѡ��
uint16_t:PWM_DutyCycle:PWMռ�ձ�����
*���ڲ���:void
**************************************************/
void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin,
                                 uint16_t PWM_DutyCycle)
{
  PWMCON0 |= 0x02;				//����Ϊ����ģʽ
  PWMREG[6 + PWM_ComplementaryOutputPin] = PWM_DutyCycle;
}

/**************************************************
*��������:void PWM_DeadTimeConfig(uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime)
*��������:PWM��������ģʽ������ʱ�����ú���
*��ڲ���:
uint8_t:PWM_RisingDeadTime:PWM��������ʱ��00-FF
uint8_t:PWM_FallingDeadTime:PWM�����½�ʱ��00-FF
*���ڲ���:void
**************************************************/
void PWM_DeadTimeConfig(uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime)
{
  PWMDFR = (PWM_RisingDeadTime | (PWM_FallingDeadTime << 4));
}

/**************************************************
*��������:PWM_DeadTimeConfigEX(PWM_Type_TypeDef PWM_Type,uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime)
*��������:PWM��������ģʽ������ʱ�����ú���-��չ��
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWMԴѡ��
uint8_t:PWM_RisingDeadTime:PWM��������ʱ��	 00-FF
uint8_t:PWM_FallingDeadTime:PWM�����½�ʱ��  00-FF
*���ڲ���:void
**************************************************/
void PWM_DeadTimeConfigEX(PWM_Type_TypeDef PWM_Type, uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime)
{
  if(PWM_Type == PWM0_Type)
  {
    PWMDFR = (PWM_RisingDeadTime | (PWM_FallingDeadTime << 4));
  }
}

/*****************************************************
*��������:void PWM_Cmd(FunctionalState NewState)
*��������:PWM���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_Cmd(FunctionalState NewState)
{
  if(NewState != DISABLE)
  {
    PWMCON0 |= 0X80;
  }
  else
  {
    PWMCON0 &= 0X7F;
  }
}

/*****************************************************
*��������:void PWM_CmdEX(PWM_Type_TypeDef PWM_Type,FunctionalState NewState)
*��������:PWM���ܿ��غ���-��չ��
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWM����
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_CmdEX(PWM_Type_TypeDef PWM_Type,
               FunctionalState NewState)
{
  if(PWM_Type == PWM0_Type)
  {
    if(NewState != DISABLE)
    {
      PWMCON0 |= 0X80;
    }
    else
    {
      PWMCON0 &= 0X7F;
    }
  }
  else
  {
    TXINX = PWM_Type;
    if(NewState != DISABLE)
    {
      TXCON |= 0X04;
    }
    else
    {
      TXCON &= ~0X04;
    }
  }
}

/*****************************************************
*��������:void PWM_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:PWM�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_ITConfig(FunctionalState NewState,
                  PriorityStatus Priority)
{
  if(NewState != DISABLE)
  {
    IE1 |= 0X02;
  }
  else
  {
    IE1 &= 0XFD;
  }

  if(Priority == LOW)
  {
    IP1 &= ~0X02;
  }
  else
  {
    IP1 |= 0X02;
  }
}


/*****************************************************
*��������:void PWM_ITConfigEX(PWM_Type_TypeDef PWM_Type,FunctionalState NewState, PriorityStatus Priority)
*��������:PWM�ж����ú���-��չ��
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWMԴѡ��
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_ITConfigEX(PWM_Type_TypeDef PWM_Type, FunctionalState NewState, PriorityStatus Priority)
{
  switch(PWM_Type)
  {
    case PWM0_Type:
      PWM_ITConfig(NewState, Priority);
      break;
    case PWM2_Type:
    {
      if(NewState == DISABLE)
        ET2 = 0;
      else
        ET2 = 1;

      if(Priority == LOW)
        IPT2 = 0;
      else
        IPT2 = 1;
    }
    break;
    case PWM3_Type:
    {
      if(NewState == DISABLE)
        IE1 &= 0XBF;
      else
        IE1 |= 0X40;

      if(Priority == LOW)
        IP1 &= 0XBF;
      else
        IP1 |= 0X40;
    }
    break;
    case PWM4_Type:
    {
      if(NewState == DISABLE)
        IE1 &= 0X7F;
      else
        IE1 |= 0X80;

      if(Priority == LOW)
        IP1 &= 0X7F;
      else
        IP1 |= 0X80;
    }
    break;
    default:
      break;
  }
}

/*****************************************************
*��������:void PWM_IndependentModeConfigEX(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle, PWM_OutputState_TypeDef PWM_OutputState)
*��������:PWM����ģʽռ�ձ�����-��չ��
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_ComplementaryOutputPin:PWMͨ��
uint16_t:PWM_DutyCycle:PWMռ�ձ�����
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_IndependentModeConfigEX(PWM_OutputPin_TypeDef PWM_ComplementaryOutputPin,
                                 uint16_t PWM_DutyCycle,
                                 PWM_OutputState_TypeDef PWM_OutputState)
{
  PWM_IndependentModeConfig(PWM_ComplementaryOutputPin, PWM_DutyCycle); //����ռ�ձ�
  PWM_OutputStateConfig(PWM_ComplementaryOutputPin, PWM_OutputState);   //IO����PWM���ú���
  if(PWM_OutputState == ENABLE)
  {
    PWM_CmdEX(PWM_ComplementaryOutputPin >> 4, ENABLE); //����PWM
  }
}

/*****************************************************
*��������:void PWM_ComplementaryModeConfigEX(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle, PWM_OutputState_TypeDef PWM_OutputState)
*��������:PWM����ģʽռ�ձ�����-��չ��
*��ڲ���:
PWM_ComplementaryOutputPin_TypeDef:PWM_OutputPin:PWMͨ��
uint16_t:PWM_DutyCycle:PWMռ�ձ�����
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_ComplementaryModeConfigEX(PWM_ComplementaryOutputPin_TypeDef PWM_OutputPin,
                                   uint16_t PWM_DutyCycle,
                                   PWM_OutputState_TypeDef PWM_OutputState)
{
  PWM_ComplementaryModeConfig(PWM_OutputPin, PWM_DutyCycle); //����ռ�ձ�
  PWM_OutputStateConfig(PWM_OutputPin, PWM_OutputState);     //IO����PWM���ú���
  PWM_OutputStateConfig(PWM_OutputPin + 2, PWM_OutputState); //IO����PWM���ú���
  if(PWM_OutputState == ENABLE)
  {
    PWM_CmdEX(PWM_OutputPin >> 4, ENABLE); //����PWM
  }
}

/*****************************************************
*��������:PWM_GetFlagStatus(void)
*��������:��ȡPWM�жϱ�־λ
*��ڲ���:void
*���ڲ���:
FlagStatus��PWM�жϱ�־λ״̬
*****************************************************/
FlagStatus PWM_GetFlagStatus(void)
{
  return (bool)(PWMCON0 & 0X40);
}

/*****************************************************
*��������:PWM_GetFlagStatusEX(PWM_Type_TypeDef PWM_Type)
*��������:��ȡPWM�жϱ�־λ-��չ��
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWMԴѡ��
*���ڲ���:
FlagStatus��PWM�жϱ�־λ״̬
*****************************************************/
FlagStatus PWM_GetFlagStatusEX(PWM_Type_TypeDef PWM_Type)
{
  if((PWM_Type == PWM0_Type))
  {
    return (bool)(PWMCON0 & 0X40);
  }
  else if((PWM_Type == PWM2_Type) || (PWM_Type == PWM3_Type) || (PWM_Type == PWM0_Type))
  {
    TXINX = PWM_Type;
    return (bool)(TXCON & 0x80);
  }

  return RESET;
}

/*****************************************************
*��������:void PWM_ClearFlag(void)
*��������:���PWM0�жϱ�־λ
*��ڲ���:void
*���ڲ���:void
*****************************************************/
void PWM_ClearFlag(void)
{
  PWMCON0 &= ~0X40;
}

/*****************************************************
*��������:void PWM_ClearFlagEX(PWM_Type_TypeDef PWM_Type)
*��������:���PWM0�жϱ�־λ-��չ��
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWMԴѡ��
*���ڲ���:void
*****************************************************/
void PWM_ClearFlagEX(PWM_Type_TypeDef PWM_Type)
{
  if((PWM_Type == PWM0_Type))
  {
    PWMCON0 &= ~0X40;
  }
  else if((PWM_Type == PWM2_Type) || (PWM_Type == PWM3_Type) || (PWM_Type == PWM0_Type))
  {
    TXINX = PWM_Type;
    TXCON &= ~0x80;
  }
}

/*****************************************************
*��������:FlagStatus PWM_GetFaultDetectionFlagStatus(void)
*��������:���PWM���ϼ���־λ״̬
*��ڲ���:void
*���ڲ���:
FlagStatus:PWM���ϼ���־λ״̬
*****************************************************/
FlagStatus PWM_GetFaultDetectionFlagStatus(void)
{
  return (bool)(PWMFLT & 0X40);
}

/*****************************************************
*��������:PWM_GetFaultDetectionFlagStatusEX(PWM_Type_TypeDef PWM_Type)
*��������:���PWM���ϼ���־λ״̬-��չ��
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWM����
*���ڲ���:
FlagStatus:PWM���ϼ���־λ״̬
*****************************************************/
FlagStatus PWM_GetFaultDetectionFlagStatusEX(PWM_Type_TypeDef PWM_Type)
{
  if(PWM_Type == PWM0_Type)
  {
    return (bool)(PWMFLT & 0X40);
  }
  return RESET;
}

/*****************************************************
*��������:void PWM_ClearFaultDetectionFlag(void)
*��������:���PWM0���ϼ���־λ״̬   // ��ע��,��������ģʽ�£���λ��Ҫ������
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWM����
*���ڲ���:void
*****************************************************/
void PWM_ClearFaultDetectionFlag(void)
{
  PWMFLT &= 0XBF;
}

/*****************************************************
*��������:void PWM_ClearFaultDetectionFlagEX(PWM_Type_TypeDef PWM_Type)
*��������:���PWM���ϼ���־λ״̬-��չ��   // ��ע��,��������ģʽ�£���λ��Ҫ������
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWM����
*���ڲ���:void
*****************************************************/
void PWM_ClearFaultDetectionFlagEX(PWM_Type_TypeDef PWM_Type)
{
  if(PWM_Type == PWM0_Type)
  {
    PWMFLT &= 0XBF;
  }
}

/*****************************************************
*��������:void PWM_FaultDetectionConfig(FunctionalState NewState)
*��������:PWM���ϼ�⹦�ܿ���/�ر�
*��ڲ���:
FunctionalState:NewState:���ϼ�⹦�ܿ���/�ر�
*���ڲ���:void
*****************************************************/
void PWM_FaultDetectionConfig(FunctionalState NewState)
{
  if(NewState != DISABLE)
  {
    PWMFLT |= 0X80;
  }
  else
  {
    PWMFLT &= 0X7F;
  }
}

/*****************************************************
*��������:void PWM_FaultDetectionFunctionConfigEX(PWM_Type_TypeDef PWM_Type, FunctionalState NewState)
*��������:PWM���ϼ�⹦�ܿ���/�ر�-��չ��
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWM����ѡ��
FunctionalState:NewState:���ϼ�⹦�ܿ���/�ر�
*���ڲ���:void
*****************************************************/
void PWM_FaultDetectionConfigEX(PWM_Type_TypeDef PWM_Type, FunctionalState NewState)
{
  if(PWM_Type == PWM0_Type)
  {
    if(NewState != DISABLE)
    {
      PWMFLT |= 0X80;
    }
    else
    {
      PWMFLT &= 0X7F;
    }
  }
}

/*****************************************************
*��������:void PWM_FaultDetectionModeConfig(PWM_FaultDetectionMode_TypeDef FaultDetectionMode,
*                                    PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect,
*                                    PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime)
*��������:PWM���ϼ��ģʽ����-��չ��
*��ڲ���:
PWM_FaultDetectionMode_TypeDef:FaultDetectionMode:���ϼ�⹦��ģʽ����: ����ģʽ/����ģʽ
PWM_FaultDetectionVoltageSelect_TypeDef:FaultDetectionVoltageSelect:���ϼ���ƽѡ��
PWM_FaultDetectionWaveFilteringTime_TypeDef:FaultDetectionWaveFilteringTime:���ϼ�������ź��˲�ʱ��ѡ��
*���ڲ���:void
*****************************************************/
void PWM_FaultDetectionModeConfig(PWM_FaultDetectionMode_TypeDef FaultDetectionMode,
                                  PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect,
                                  PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime)
{
  PWMFLT = (PWMFLT & 0XC0) | FaultDetectionMode | FaultDetectionVoltageSelect |
           FaultDetectionWaveFilteringTime;
}

/*****************************************************
*��������:void PWM_FaultDetectionModeConfigEX(PWM_Type_TypeDef PWM_Type, PWM_FaultDetectionMode_TypeDef FaultDetectionMode, PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect, PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime)
*��������:PWM���ϼ��ģʽ����-��չ��
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWM����ѡ��
PWM_FaultDetectionMode_TypeDef:FaultDetectionMode:���ϼ�⹦��ģʽ����: ����ģʽ/����ģʽ
PWM_FaultDetectionVoltageSelect_TypeDef:FaultDetectionVoltageSelect:���ϼ���ƽѡ��
PWM_FaultDetectionWaveFilteringTime_TypeDef:FaultDetectionWaveFilteringTime:���ϼ�������ź��˲�ʱ��ѡ��
*���ڲ���:void
*****************************************************/
void PWM_FaultDetectionModeConfigEX(PWM_Type_TypeDef PWM_Type,
                                    PWM_FaultDetectionMode_TypeDef FaultDetectionMode,
                                    PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect,
                                    PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime)
{
  if(PWM_Type == PWM0_Type)
  {
    PWMFLT = (PWMFLT & 0XC0) | FaultDetectionMode | FaultDetectionVoltageSelect |
             FaultDetectionWaveFilteringTime;
  }
}

/*****************************************************
*��������:void PWM_DutyChange_Ex(void)
*��������:PWM����ģʽռ�ձ��޸�
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:���޸ĵ�PWM����ͨ��
PWM_DutyChange_TypeDef:Change_Direction:PWM�޸ķ���
uint16_t:DutyIncremental:�޸ĵ�����
*���ڲ���:
ErrorStatus:�����ɹ�/ʧ��
*****************************************************/
ErrorStatus PWM_IndependentMode_DutyChange(PWM_OutputPin_TypeDef PWM_OutputPin,
    PWM_DutyChange_TypeDef Change_Direction, uint16_t DutyIncremental)
{
  uint16_t tmpRegValue;
  uint16_t tmpRegAdress;
  uint16_t tmpPolarity = PWMPDL + (PWMPDH << 8);

  /* PWM0�����ͨ�� */
  if((PWM_OutputPin & 0xF0) == 0x00)
  {
    PWMCON0 &= ~0x02;			//����Ϊ����ģʽ
    tmpRegAdress = PWMREG + 6 + PWM_OutputPin;
  }
  else		/* PWM2/3/4��ռ�ձȼĴ�����ַ */
  {
    tmpRegAdress = PWMREG + (PWM_OutputPin & 0x0F);
  }

  tmpRegValue = *((uint16_t xdata*)tmpRegAdress);
  if(Change_Direction == PWM_DutyChange_Up)
  {
    tmpRegValue += DutyIncremental;				//ռ�ձ�����
  }
  else
  {
    tmpRegValue -= DutyIncremental;				//ռ�ձȼ���
  }
  /* ��������������� */
  if(tmpRegValue > tmpPolarity)
    return ERROR;
  *((uint16_t xdata*)tmpRegAdress) = tmpRegValue;		//ռ�ձȼĴ�����ֵ
  return SUCCESS;
}

/*****************************************************
*��������:void PWM_DutyChange_Ex(void)
*��������:PWM����ģʽռ�ձ��޸�
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:���޸ĵ�PWM����ͨ��
PWM_DutyChange_TypeDef:Change_Direction:PWM�޸ķ���
uint16_t:DutyIncremental:�޸ĵ�����
*���ڲ���:
ErrorStatus:�����ɹ�/ʧ��
*****************************************************/
ErrorStatus PWM_ComplementaryMode_DutyChange(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin, PWM_DutyChange_TypeDef Change_Direction, uint16_t DutyIncremental)
{
  uint16_t tmpRegValue;
  uint16_t tmpRegAdress;
  uint16_t tmpPolarity = PWMPDL + (PWMPDH << 8);
  /* PWM0��ռ�ձȼĴ�����ַ */
  if((PWM_ComplementaryOutputPin & 0xF0) == 0x00)
  {
    tmpRegAdress = PWMREG + 6 + PWM_ComplementaryOutputPin;
  }
  else	/* PWM2/3/4��ռ�ձȼĴ�����ַ */
  {
    tmpRegAdress = PWMREG + (PWM_ComplementaryOutputPin & 0x0F);
  }

  tmpRegValue = *(uint16_t xdata*)tmpRegAdress;
  if(Change_Direction == PWM_DutyChange_Up)
  {
    tmpRegValue += DutyIncremental;				//ռ�ձ�����
  }
  else
  {
    tmpRegValue -= DutyIncremental;				//ռ�ձȼ���
  }
  /* ��������������� */
  if(tmpRegValue > tmpPolarity)
    return ERROR;
  *((uint16_t xdata*)tmpRegAdress) = tmpRegValue;		//ռ�ձȼĴ�����ֵ
  return SUCCESS;
}

#endif
#if defined(RD8G05x) || defined(RD8T05x)
uint16_t xdata PWMREG[8] _at_ 0x0F40; //PWMռ�ձȵ��ڼĴ���
/**************************************************
*��������:void PWM_DeInit(void)
*��������:PWM��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void PWM_DeInit(void)
{
  uint8_t i;

  //PWM0��ؼĴ�������
  PWMCON0 = 0X00;
  PWMCFG = 0X00;
  PWMCON1 = 0X00;
  PWMPDL = 0x00;
  PWMPDH = 0x00;
  IE1 &= 0XFD;
  IP1 &= 0XFD;

  //ռ�ձȼĴ���
  for(i = 0; i < 8; i++)
  {
    PWMREG[i] = 0;
  }
}

/**************************************************
*��������:void PWM_InitEX(PWM_Type_TypeDef PWM_Type)
*��������:PWM0��ؼĴ�����λ��ȱʡֵ-��չ��
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWMԴ
*���ڲ���:void
**************************************************/
void PWM_DeInitEX(PWM_Type_TypeDef PWM_Type)
{
  if(PWM_Type == PWM0_Type)
  {
    uint8_t i;

    //PWM0��ؼĴ�������
    PWMCON0 = 0X00;
    PWMCFG = 0X00;
    PWMCON1 = 0X00;
    PWMPDL = 0x00;
    PWMPDH = 0x00;
    IE1 &= 0XFD;
    IP1 &= 0XFD;

    //ռ�ձȼĴ���
    for(i = 0; i < 8; i++)
    {
      PWMREG[i] = 0;
    }
  }
}
/**************************************************
*��������:PWM_Init(PWM_Type_TypeDef PWM_Type,PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period)
*��������:PWM��ʼ�����ú���
*��ڲ���:
PWM_PresSel_TypeDef:PWM_PresSel:Ԥ��Ƶѡ��
uint16_t:PWM_Period:PWM��������
*���ڲ���:void
**************************************************/
void PWM_Init(PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period)
{
  /* PWM0ʱ����ʼ�� */
  PWM_Period -= 1;
  PWMCON0 = ((PWMCON0 & 0XCF) | PWM_PresSel); //Ԥ��Ƶ
  PWMPDH = (uint8_t)(PWM_Period >> 8);               //���ڸ�8λ
  PWMPDL = (uint8_t)(PWM_Period & 0X00FF);           //���ڵ�8λ
}

/*****************************************************
*��������:void PWM_Aligned_Mode_Select(void)
*��������:ѡ��PWM�Ķ���ģʽ
*��ڲ���:
PWM_Aligned_Mode_TypeDef:PWM_Aligned_Mode:ѡ�����ģʽ
*���ڲ���:void
*****************************************************/
void PWM_Aligned_Mode_Select(PWM_Aligned_Mode_TypeDef PWM_Aligned_Mode)
{
  PWMCON0 &= ~0x01;	//���PWM����ģʽ����
  PWMCON0 |= (PWM_Aligned_Mode << 1);	//����PWM����ģʽ
}

/**************************************************
*��������:void PWM_OutputStateConfig(uint8_t PWM_OutputPin, PWM_OutputState_TypeDef PWM_OutputState)
*��������:PWMx���ʹ��/ʧ�����ú���
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMxѡ��uint8_t��Ϊ��Σ��������λ�������
PWM_OutputState_TypeDef:PWM_OutputState:PWM���״̬����
*���ڲ���:void
**************************************************/
void PWM_OutputStateConfig(uint8_t PWM_OutputPin,
                           PWM_OutputState_TypeDef PWM_OutputState)
{
  /* PWM0���ͨ��ʹ������ */
  if(PWM_OutputState == PWM_OUTPUTSTATE_ENABLE)
  {
    PWMCON1 |= 1 << (PWM_OutputPin & 0x0F);
  }
  else
  {
    PWMCON1 &= ~(1 << (PWM_OutputPin & 0x0F));
  }
}

/**************************************************
*��������:void PWM_PolarityConfig(PWM_OutputPin_TypeDef PWM_OutputPin, PWM_Polarity_TypeDef PWM_Polarity)
*��������:PWMx��/����������ú���
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMxѡ��uint8_t��Ϊ��Σ��������λ�������
PWM_Polarity_TypeDef:PWM_Polarity:PWM�����/��������
*���ڲ���:void
**************************************************/
void PWM_PolarityConfig(uint8_t PWM_OutputPin,
                        PWM_Polarity_TypeDef PWM_Polarity)
{
  if(PWM_Polarity == PWM_POLARITY_INVERT)
  {
    PWMCFG |= 1 << (PWM_OutputPin & 0x0F);
  }
  else
  {
    PWMCFG &= ~(1 << (PWM_OutputPin & 0x0F));
  }
}

/**************************************************
*��������:void PWM_IndependentModeConfig(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle)
*��������:PWMx��������ģʽ���ú���
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMx����ͨ��ѡ��
uint16_t:PWM_DutyCycle:PWMռ�ձ�����
*���ڲ���:void
**************************************************/
void PWM_IndependentModeConfig(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle)
{
  PWMCON0 &= ~0x02;	//����PWMΪ����ģʽ
  /* ����PWM���� */
  PWMREG[PWM_OutputPin] = PWM_DutyCycle;

}

/**************************************************
*��������:void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin, uint16_t PWM_DutyCycle)
*��������:PWMxPWMy��������ģʽ���ú���
*��ڲ���:
PWM_ComplementaryOutputPin_TypeDef:PWM_ComplementaryOutputPin:PWMxPWMy����ͨ��ѡ��
uint16_t:PWM_DutyCycle:PWMռ�ձ�����
*���ڲ���:void
**************************************************/
void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin,
                                 uint16_t PWM_DutyCycle)
{
  PWMCON0 |= 0x02;
  PWMREG[PWM_ComplementaryOutputPin] = PWM_DutyCycle;
}

/*****************************************************
*��������:void PWM_DutyChange_Ex(void)
*��������:PWM����ģʽռ�ձ��޸�
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:���޸ĵ�PWM����ͨ��
PWM_DutyChange_TypeDef:Change_Direction:PWM�޸ķ���
uint16_t:DutyIncremental:�޸ĵ�����
*���ڲ���:
ErrorStatus:�����ɹ�/ʧ��
*****************************************************/
ErrorStatus PWM_IndependentMode_DutyChange(PWM_OutputPin_TypeDef PWM_OutputPin,
    PWM_DutyChange_TypeDef Change_Direction, uint16_t DutyIncremental)
{
  uint8_t i;
  uint8_t tmpRegValue;

  for(i = 0; i < 8; i++)
  {
    if(PWM_OutputPin & (0x01 << i))
    {
      tmpRegValue = PWMREG[i];			//�ѵ�ǰռ�ձȼĴ����Ž���ʱ����
      if(Change_Direction == PWM_DutyChange_Up)
      {
        tmpRegValue += DutyIncremental;				//ռ�ձ�����

        /* ������������������� */
        if(tmpRegValue < PWMREG[i])
          return ERROR;
      }
      else
      {
        tmpRegValue -= DutyIncremental;				//ռ�ձȼ���

        /* ������������������� */
        if(tmpRegValue < PWMREG[i])
          return ERROR;
      }
      PWMREG[i] = tmpRegValue;		//ռ�ձȼĴ�����ֵ
    }
  }
  return SUCCESS;
}

/*****************************************************
*��������:void PWM_DutyChange_Ex(void)
*��������:PWM����ģʽռ�ձ��޸�
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:���޸ĵ�PWM����ͨ��
PWM_DutyChange_TypeDef:Change_Direction:PWM�޸ķ���
uint16_t:DutyIncremental:�޸ĵ�����
*���ڲ���:
ErrorStatus:�����ɹ�/ʧ��
*****************************************************/
ErrorStatus PWM_ComplementaryMode_DutyChange(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin,
    PWM_DutyChange_TypeDef Change_Direction, uint16_t DutyIncremental)
{
  uint8_t tmpRegValue;
  uint16_t tmpPolarity = PWMPDL + (PWMPDH << 8);

  tmpRegValue = PWMREG[PWM_ComplementaryOutputPin * 2];			//�ѵ�ǰռ�ձȼĴ����Ž���ʱ����
  if(Change_Direction == PWM_DutyChange_Up)
  {
    tmpRegValue += DutyIncremental;				//ռ�ձ�����
  }
  else
  {
    tmpRegValue -= DutyIncremental;				//ռ�ձȼ���
  }

  /* ������������������� */
  if(tmpRegValue > tmpPolarity)
    return ERROR;
  PWMREG[PWM_ComplementaryOutputPin] = tmpRegValue;		//ռ�ձȼĴ�����ֵ
  return SUCCESS;
}

/**************************************************
*��������:void PWM_DeadTimeConfig(uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime)
*��������:PWM��������ģʽ������ʱ�����ú���
*��ڲ���:
uint8_t:PWM_RisingDeadTime:PWM��������ʱ��00-FF
uint8_t:PWM_FallingDeadTime:PWM�����½�ʱ��00-FF
*���ڲ���:void
**************************************************/
void PWM_DeadTimeConfig(uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime)
{
  PWMDFR = (PWM_RisingDeadTime | (PWM_FallingDeadTime << 4));
}

/**************************************************
*��������:PWM_DeadTimeConfigEX(PWM_Type_TypeDef PWM_Type,uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime)
*��������:PWM��������ģʽ������ʱ�����ú���-��չ��
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWMԴѡ��
uint8_t:PWM_RisingDeadTime:PWM��������ʱ��	 00-FF
uint8_t:PWM_FallingDeadTime:PWM�����½�ʱ��  00-FF
*���ڲ���:void
**************************************************/
void PWM_DeadTimeConfigEX(PWM_Type_TypeDef PWM_Type, uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime)
{
  if(PWM_Type == PWM0_Type)
  {
    PWMDFR = (PWM_RisingDeadTime | (PWM_FallingDeadTime << 4));
  }
}

/*****************************************************
*��������:void PWM_Cmd(FunctionalState NewState)
*��������:PWM���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_Cmd(FunctionalState NewState)
{
  if(NewState != DISABLE)
  {
    PWMCON0 |= 0X80;
  }
  else
  {
    PWMCON0 &= 0X7F;
  }
}

/*****************************************************
*��������:void PWM_Cmd(PWM_Type_TypeDef PWM_Type,FunctionalState NewState)
*��������:PWM���ܿ��غ���
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWM����
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_CmdEX(PWM_Type_TypeDef PWM_Type,
               FunctionalState NewState)
{
  if(PWM_Type == PWM0_Type)
  {
    if(NewState != DISABLE)
    {
      PWMCON0 |= 0X80;
    }
    else
    {
      PWMCON0 &= 0X7F;
    }
  }
}

/*****************************************************
*��������:void PWM_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:PWM�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_ITConfig(FunctionalState NewState,
                  PriorityStatus Priority)
{
  if(NewState != DISABLE)
  {
    IE1 |= 0X02;
  }
  else
  {
    IE1 &= 0XFD;
  }

  if(Priority == LOW)
  {
    IP1 &= ~0X02;
  }
  else
  {
    IP1 |= 0X02;
  }
}

/*****************************************************
*��������:void PWM_ITConfigEX(PWM_Type_TypeDef PWM_Type,FunctionalState NewState, PriorityStatus Priority)
*��������:PWM�ж����ú���-��չ��
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWMԴѡ��
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_ITConfigEX(PWM_Type_TypeDef PWM_Type, FunctionalState NewState, PriorityStatus Priority)
{
  if(PWM_Type == PWM0_Type)
  {
    if(NewState != DISABLE)
    {
      IE1 |= 0X02;
    }
    else
    {
      IE1 &= 0XFD;
    }

    if(Priority == LOW)
    {
      IP1 &= ~0X02;
    }
    else
    {
      IP1 |= 0X02;
    }
  }
}

/*****************************************************
*��������:void PWM_IndependentModeConfigEX(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle, PWM_OutputState_TypeDef PWM_OutputState)
*��������:PWM����ģʽռ�ձ�����
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_ComplementaryOutputPin:PWMͨ��
uint16_t:PWM_DutyCycle:PWMռ�ձ�����
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_IndependentModeConfigEX(PWM_OutputPin_TypeDef PWM_ComplementaryOutputPin,
                                 uint16_t PWM_DutyCycle,
                                 PWM_OutputState_TypeDef PWM_OutputState)
{
  PWM_IndependentModeConfig(PWM_ComplementaryOutputPin, PWM_DutyCycle); //����ռ�ձ�
  PWM_OutputStateConfig(PWM_ComplementaryOutputPin, PWM_OutputState);   //IO����PWM���ú���
  if(PWM_OutputState == ENABLE)
  {
    PWM_CmdEX(PWM_ComplementaryOutputPin >> 4, ENABLE); //����PWM
  }
}

/*****************************************************
*��������:void PWM_ComplementaryModeConfigEX(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle, PWM_OutputState_TypeDef PWM_OutputState)
*��������:PWM����ģʽռ�ձ�����
*��ڲ���:
PWM_ComplementaryOutputPin_TypeDef:PWM_OutputPin:PWMͨ��
uint16_t:PWM_DutyCycle:PWMռ�ձ�����
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_ComplementaryModeConfigEX(PWM_ComplementaryOutputPin_TypeDef PWM_OutputPin,
                                   uint16_t PWM_DutyCycle,
                                   PWM_OutputState_TypeDef PWM_OutputState)
{
  PWM_ComplementaryModeConfig(PWM_OutputPin, PWM_DutyCycle); //����ռ�ձ�
  PWM_OutputStateConfig(PWM_OutputPin, PWM_OutputState);     //IO����PWM���ú���
  PWM_OutputStateConfig(PWM_OutputPin + 2, PWM_OutputState); //IO����PWM���ú���
  if(PWM_OutputState == ENABLE)
  {
    PWM_CmdEX(PWM_OutputPin >> 4, ENABLE); //����PWM
  }
}

/*****************************************************
*��������:PWM_GetFlagStatus(void)
*��������:��ȡPWM�жϱ�־λ
*��ڲ���:void
*���ڲ���:
FlagStatus��PWM�жϱ�־λ״̬
*****************************************************/
FlagStatus PWM_GetFlagStatus(void)
{
  return (bool)(PWMCON0 & 0X40);
}

/*****************************************************
*��������:PWM_GetFlagStatusEX(PWM_Type_TypeDef PWM_Type)
*��������:��ȡPWM�жϱ�־λ-��չ��
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWMԴѡ��
*���ڲ���:void
*****************************************************/
FlagStatus PWM_GetFlagStatusEX(PWM_Type_TypeDef PWM_Type)
{
  if((PWM_Type == PWM0_Type))
  {
    return (bool)(PWMCON0 & 0X40);
  }

  return RESET;
}

/*****************************************************
*��������:void PWM_ClearFlag(void)
*��������:���PWM0�жϱ�־λ
*��ڲ���:void
*���ڲ���:void
*****************************************************/
void PWM_ClearFlag(void)
{
  PWMCON0 &= ~0X40;
}

/*****************************************************
*��������:void PWM_ClearFlagEX(PWM_Type_TypeDef PWM_Type)
*��������:���PWM�ж�-��չ��
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWMԴѡ��
*���ڲ���:void
*****************************************************/
void PWM_ClearFlagEX(PWM_Type_TypeDef PWM_Type)
{
  if((PWM_Type == PWM0_Type))
  {
    PWMCON0 &= ~0X40;
  }
}

/*****************************************************
*��������:FlagStatus PWM_GetFaultDetectionFlagStatus(void)
*��������:���PWM���ϼ���־λ״̬
*��ڲ���:void
*���ڲ���:
FlagStatus:PWM���ϼ���־λ״̬
*****************************************************/
FlagStatus PWM_GetFaultDetectionFlagStatus(void)
{
  return (bool)(PWMFLT & 0X40);
}

/*****************************************************
*��������:FlagStatus PWM_GetFaultDetectionFlagStatus(void)
*��������:���PWM���ϼ���־λ״̬-��չ��
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWM����
*���ڲ���:
FlagStatus:PWM���ϼ���־λ״̬
*****************************************************/
FlagStatus PWM_GetFaultDetectionFlagStatusEX(PWM_Type_TypeDef PWM_Type)
{
  if(PWM_Type == PWM0_Type)
  {
    return (bool)(PWMFLT & 0X40);
  }
  return RESET;
}

/*****************************************************
*��������:void PWM_ClearFaultDetectionFlag(void)
*��������:���PWM���ϼ���־λ״̬   // ��ע��,��������ģʽ�£���λ��������
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWM����
*���ڲ���:void
*****************************************************/
void PWM_ClearFaultDetectionFlagEX(PWM_Type_TypeDef PWM_Type)
{
  if(PWM_Type == PWM0_Type)
  {
    PWMFLT &= 0XBF;
  }
}

/*****************************************************
*��������:void PWM_FaultDetectionConfig(FunctionalState NewState)
*��������:PWM���ϼ�⹦�ܿ���/�ر�
*��ڲ���:
FunctionalState:NewState:���ϼ�⹦�ܿ���/�ر�
*���ڲ���:void
*****************************************************/
void PWM_FaultDetectionConfig(FunctionalState NewState)
{
  if(NewState != DISABLE)
  {
    PWMFLT |= 0X80;
  }
  else
  {
    PWMFLT &= 0X7F;
  }
}

/*****************************************************
*��������:void PWM_FaultDetectionFunctionConfigEX(PWM_Type_TypeDef PWM_Type, FunctionalState NewState)
*��������:PWM���ϼ�⹦�ܿ���/�ر�-��չ��
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWM����ѡ��
FunctionalState:NewState:���ϼ�⹦�ܿ���/�ر�
*���ڲ���:void
*****************************************************/
void PWM_FaultDetectionConfigEX(PWM_Type_TypeDef PWM_Type, FunctionalState NewState)
{
  if(PWM_Type == PWM0_Type)
  {
    if(NewState != DISABLE)
    {
      PWMFLT |= 0X80;
    }
    else
    {
      PWMFLT &= 0X7F;
    }
  }
}

/*****************************************************
*��������:void PWM_FaultDetectionModeConfig(PWM_FaultDetectionMode_TypeDef FaultDetectionMode,
*                                    PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect,
*                                    PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime)
*��������:PWM���ϼ��ģʽ����
*��ڲ���:
PWM_FaultDetectionMode_TypeDef:FaultDetectionMode:���ϼ�⹦��ģʽ����: ����ģʽ/����ģʽ
PWM_FaultDetectionVoltageSelect_TypeDef:FaultDetectionVoltageSelect:���ϼ���ƽѡ��
PWM_FaultDetectionWaveFilteringTime_TypeDef:FaultDetectionWaveFilteringTime:���ϼ�������ź��˲�ʱ��ѡ��
*���ڲ���:void
*****************************************************/
void PWM_FaultDetectionModeConfig(PWM_FaultDetectionMode_TypeDef FaultDetectionMode,
                                  PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect,
                                  PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime)
{
  PWMFLT = (PWMFLT & 0XC0) | FaultDetectionMode | FaultDetectionVoltageSelect |
           FaultDetectionWaveFilteringTime;
}

/*****************************************************
*��������:void PWM_FaultDetectionModeConfigEX(PWM_Type_TypeDef PWM_Type, PWM_FaultDetectionMode_TypeDef FaultDetectionMode, PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect, PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime)
*��������:PWM���ϼ��ģʽ����
*��ڲ���:
PWM_Type_TypeDef:PWM_Type:PWM����ѡ��
PWM_FaultDetectionMode_TypeDef:FaultDetectionMode:���ϼ�⹦��ģʽ����: ����ģʽ/����ģʽ
PWM_FaultDetectionVoltageSelect_TypeDef:FaultDetectionVoltageSelect:���ϼ���ƽѡ��
PWM_FaultDetectionWaveFilteringTime_TypeDef:FaultDetectionWaveFilteringTime:���ϼ�������ź��˲�ʱ��ѡ��
*���ڲ���:void
*****************************************************/
void PWM_FaultDetectionModeConfigEX(PWM_Type_TypeDef PWM_Type,
                                    PWM_FaultDetectionMode_TypeDef FaultDetectionMode,
                                    PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect,
                                    PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime)
{
  if(PWM_Type == PWM0_Type)
  {
    PWMFLT = (PWMFLT & 0XC0) | FaultDetectionMode | FaultDetectionVoltageSelect |
             FaultDetectionWaveFilteringTime;
  }
}

#endif

#if defined (RD8G403)
/**************************************************
*��������:void PWM_DeInit(void)
*��������:PWM��ؼĴ�����λ��ȱʡֵ
*��ڲ���:void
*���ڲ���:void
**************************************************/
void PWM_DeInit(void)
{
  PWMCFG = 0X00;
  PWMCON0 = 0X00;
  PWMPRD = 0X00;
  PWMDTYA = 0X00;
  PWMDTY0 = 0X00;
  PWMDTY1 = 0X00;
  PWMDTY2 = 0X00;
  PWMCON1 = 0X00;
  PWMDTYB = 0X00;
  PWMDTY3 = 0X00;
  PWMDTY4 = 0X00;
  PWMDTY5 = 0X00;
  PWMDTY6 = 0X00;
  IE1 &= 0XFD;
  IP1 &= 0XFD;
}

/**************************************************
*��������:void PWM_Init(PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period)
*��������:PWM��ʼ�����ú���
*��ڲ���:
PWM_PresSel_TypeDef:PWM_PresSel:Ԥ��Ƶѡ��
uint16_t:PWM_Period:PWM��������
*���ڲ���:void
**************************************************/
void PWM_Init(PWM_PresSel_TypeDef PWM_PresSel,
              uint16_t PWM_Period)
{
  PWM_Period -= 1;
  PWMCON0 = (PWMCON0 & 0XCC) | PWM_PresSel |
            (uint8_t)(PWM_Period &
                      0X0003);	//Ԥ��Ƶ�����ڵĵ�2λ
  PWMPRD = (uint8_t)(PWM_Period >>
                     2);									    //���ڸ߰�λ
}

/**************************************************
*��������:void PWM_OutputStateConfig(uint8_t PWM_OutputPin, PWM_OutputState_TypeDef PWM_OutputState)
*��������:PWMx���ʹ��/ʧ�����ú���
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMxѡ��
PWM_OutputState_TypeDef:PWM_OutputState:PWM���״̬����
*���ڲ���:void
**************************************************/
void PWM_OutputStateConfig(uint8_t PWM_OutputPin,
                           PWM_OutputState_TypeDef PWM_OutputState)
{
  if(PWM_OutputState == PWM_OUTPUTSTATE_ENABLE)
  {
    PWMCON1 |= PWM_OutputPin;
  }
  else
  {
    PWMCON1 &= (~PWM_OutputPin);
  }
}

/**************************************************
*��������:void PWM_PWM2Selection(PWM2_OutputPin_TypeDef PWM2_OutputPin)
*��������:PWM2�ܽ�ѡ����
*��ڲ���:
PWM2_OutputPin_TypeDef:PWM2_OutputPin:PWM2�ܽ�ѡ��
*���ڲ���:void
**************************************************/
void PWM_PWM2Selection(PWM2_OutputPin_TypeDef
                       PWM2_OutputPin)
{
  PWMCON0 = PWMCON0 & 0XFB | PWM2_OutputPin;
}

/**************************************************
*��������:void PWM_PWM5Selection(PWM5_OutputPin_TypeDef PWM5_OutputPin)
*��������:PWM5�ܽ�ѡ����
*��ڲ���:
PWM5_OutputPin_TypeDef:PWM5_OutputPin:PWM5�ܽ�ѡ��
*���ڲ���:void
**************************************************/
void PWM_PWM5Selection(PWM5_OutputPin_TypeDef
                       PWM5_OutputPin)
{
  PWMCON0 = PWMCON0 & 0XF7 | PWM5_OutputPin;
}

/**************************************************
*��������:void PWM_PolarityConfig(uint8_t PWM_OutputPin, PWM_Polarity_TypeDef PWM_Polarity)
*��������:PWMx��/����������ú���
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMxѡ��
PWM_Polarity_TypeDef:PWM_Polarity:PWM�����/��������
*���ڲ���:void
**************************************************/
void PWM_PolarityConfig(uint8_t PWM_OutputPin,
                        PWM_Polarity_TypeDef PWM_Polarity)
{
  if(PWM_Polarity == PWM_POLARITY_INVERT)
  {
    PWMCFG |= PWM_OutputPin;
  }
  else
  {
    PWMCFG &= (~PWM_OutputPin);
  }
}

/**************************************************
*��������:void PWM_IndependentModeConfig(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle)
*��������:PWMx��������ģʽ���ú���
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:PWMx����ͨ��ѡ��
uint16_t:PWM_DutyCycle:PWMռ�ձ�����
*���ڲ���:void
**************************************************/
void PWM_IndependentModeConfig(PWM_OutputPin_TypeDef PWM_OutputPin,
                               uint16_t PWM_DutyCycle)
{
  if(PWM_OutputPin != PWM6)
  {
    PWMCON1 &= 0X7F;		//����PWMΪ����ģʽ
  }

  switch(PWM_OutputPin)	//����ռ�ձ�
  {
    case PWM0:
      PWMDTYA = PWMDTYA & 0XFC | (PWM_DutyCycle % 4);
      PWMDTY0 = (uint8_t)(PWM_DutyCycle >> 2);
      break;

    case PWM1:
      PWMDTYA = PWMDTYA & 0XF3 | ((PWM_DutyCycle % 4) <<
                                  2);
      PWMDTY1 = (uint8_t)(PWM_DutyCycle >> 2);
      break;

    case PWM2:
      PWMDTYA = PWMDTYA & 0XCF | ((PWM_DutyCycle % 4) <<
                                  4);
      PWMDTY2 = (uint8_t)(PWM_DutyCycle >> 2);
      break;

    case PWM3:
      PWMDTYA = PWMDTYA & 0X3F | ((PWM_DutyCycle % 4) <<
                                  6);
      PWMDTY3 = (uint8_t)(PWM_DutyCycle >> 2);
      break;

    case PWM4:
      PWMDTYB = PWMDTYB & 0XFC | (PWM_DutyCycle % 4);
      PWMDTY4 = (uint8_t)(PWM_DutyCycle >> 2);
      break;

    case PWM5:
      PWMDTYB = PWMDTYB & 0XF3 | ((PWM_DutyCycle % 4) <<
                                  2);
      PWMDTY5 = (uint8_t)(PWM_DutyCycle >> 2);
      break;

    case PWM6:
      PWMDTYB = PWMDTYB & 0XCF | ((PWM_DutyCycle % 4) <<
                                  4);
      PWMDTY6 = (uint8_t)(PWM_DutyCycle >> 2);
      break;

    default:
      break;
  }
}

/*****************************************************
*��������:ErrorStatus PWM_IndependentMode_DutyChange(PWM_OutputPin_TypeDef PWM_OutputPin,
																						PWM_DutyChange_TypeDef Change_Direction,
																						uint16_t DutyIncremental)
*��������:PWM����ģʽռ�ձ��޸�
*��ڲ���:
PWM_OutputPin_TypeDef:PWM_OutputPin:���޸ĵ�PWM����ͨ��
PWM_DutyChange_TypeDef:Change_Direction:PWM�޸ķ���
uint16_t:DutyIncremental:�޸ĵ�����
*���ڲ���:
ErrorStatus:�����ɹ�/ʧ��
*****************************************************/
ErrorStatus PWM_IndependentMode_DutyChange(PWM_OutputPin_TypeDef PWM_OutputPin,
    PWM_DutyChange_TypeDef Change_Direction,
    uint16_t DutyIncremental)
{
  uint16_t tmpRegValue;
  uint16_t tmpPolarity = ((PWMCON0 & 0x03) | (PWMPRD << 2));

  switch(PWM_OutputPin)	//����ռ�ձ�
  {
    case PWM0:
      tmpRegValue = ((PWMDTYA & 0xfc) | (PWMDTY0 << 2));
      break;

    case PWM1:
      tmpRegValue = (((PWMDTYA & 0xf3) >> 2) | (PWMDTY1 << 2));
      break;

    case PWM2:
      tmpRegValue = (((PWMDTYA & 0xcf) >> 4) | (PWMDTY2 << 2));
      break;

    case PWM3:
      tmpRegValue = (((PWMDTYA & 0x3f) >> 6) | (PWMDTY2 << 2));
      break;

    case PWM4:
      tmpRegValue = (((PWMDTYB & 0xfc)) | (PWMDTY3 << 2));
      break;

    case PWM5:
      tmpRegValue = (((PWMDTYB & 0xf3) >> 2) | (PWMDTY4 << 2));
      break;

    case PWM6:
      tmpRegValue = (((PWMDTYB & 0xcf) >> 4) | (PWMDTY5 << 2));
      break;

    default:
      break;
  }

  if(Change_Direction == PWM_DutyChange_Up)
  {
    tmpRegValue += DutyIncremental;				//ռ�ձ�����
  }
  else
  {
    tmpRegValue -= DutyIncremental;				//ռ�ձȼ���
  }

  /* ��������������� */
  if(tmpRegValue > tmpPolarity)
    return ERROR;

  switch(PWM_OutputPin)	//����ռ�ձ�
  {
    case PWM0:
      PWMDTYA = PWMDTYA & 0xfc | (tmpRegValue % 4);
      PWMDTY0 = (uint8_t)(tmpRegValue >> 2);
      break;

    case PWM1:
      PWMDTYA = PWMDTYA & 0xf3 | ((tmpRegValue % 4) << 2);
      PWMDTY1 = (uint8_t)(tmpRegValue >> 2);
      break;

    case PWM2:
      PWMDTYA = PWMDTYA & 0xcf | ((tmpRegValue % 4) << 4);
      PWMDTY2 = (uint8_t)(tmpRegValue >> 2);
      break;

    case PWM3:
      PWMDTYA = PWMDTYA & 0x3f | ((tmpRegValue % 4) << 6);
      PWMDTY2 = (uint8_t)(tmpRegValue >> 2);
      break;

    case PWM4:
      PWMDTYB = PWMDTYB & 0xfc | (tmpRegValue % 4);
      PWMDTY3 = (uint8_t)(tmpRegValue >> 2);
      break;

    case PWM5:
      PWMDTYB = PWMDTYB & 0xf3 | ((tmpRegValue % 4) << 2);
      PWMDTY4 = (uint8_t)(tmpRegValue >> 2);
      break;

    case PWM6:
      PWMDTYB = PWMDTYB & 0xcf | ((tmpRegValue % 4) << 4);
      PWMDTY5 = (uint8_t)(tmpRegValue >> 2);
      break;

    default:
      break;
  }
  return SUCCESS;
}

/**************************************************
*��������:void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin, uint16_t PWM_DutyCycle)
*��������:PWMxPWMy��������ģʽ���ú���
*��ڲ���:
PWM_ComplementaryOutputPin_TypeDef:PWM_ComplementaryOutputPin:PWMxPWMy����ͨ��ѡ��
uint16_t:PWM_DutyCycle:PWMռ�ձ�����
*���ڲ���:void
**************************************************/
void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin,
                                 uint16_t PWM_DutyCycle)
{
  PWMCON1 |= 0X80;					//����PWMΪ����ģʽ

  switch(PWM_ComplementaryOutputPin)	//����ռ�ձ�
  {
    case PWM0PWM3:
      PWMDTYA = PWMDTYA & 0XFC | (PWM_DutyCycle % 4);
      PWMDTY0 = (uint8_t)(PWM_DutyCycle >> 2);
      break;

    case PWM1PWM4:
      PWMDTYA = PWMDTYA & 0XF3 | ((PWM_DutyCycle % 4) <<
                                  2);
      PWMDTY1 = (uint8_t)(PWM_DutyCycle >> 2);
      break;

    case PWM2PWM5:
      PWMDTYA = PWMDTYA & 0XCF | ((PWM_DutyCycle % 4) <<
                                  4);
      PWMDTY2 = (uint8_t)(PWM_DutyCycle >> 2);
      break;

    default:
      break;
  }
}

/*****************************************************
*��������:void PWM_ComplementaryMode_DutyChange(PWM_OutputPin_TypeDef PWM_OutputPin,
																						PWM_DutyChange_TypeDef Change_Direction,
																						uint16_t DutyIncremental)
*��������:PWM����ģʽռ�ձ��޸�
*��ڲ���:
PWM_ComplementaryOutputPin_TypeDef:PWM_ComplementaryOutputPin:���޸ĵ�PWM����ͨ��
PWM_DutyChange_TypeDef:Change_Direction:PWM�޸ķ���
uint16_t:DutyIncremental:�޸ĵ�����
*���ڲ���:
ErrorStatus:�����ɹ�/ʧ��
*****************************************************/
ErrorStatus PWM_ComplementaryMode_DutyChange(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin,
    PWM_DutyChange_TypeDef Change_Direction,
    uint16_t DutyIncremental)
{
  uint16_t tmpRegValue;
  uint16_t tmpPolarity = ((PWMCON0 & 0x03) | (PWMPRD << 2));

  switch(PWM_ComplementaryOutputPin)	//����ռ�ձ�
  {
    case PWM0PWM3:
      tmpRegValue = ((PWMDTYA & 0xfc) | (PWMDTY0 << 2));
      break;

    case PWM1PWM4:
      tmpRegValue = (((PWMDTYA & 0xf3) >> 2) | (PWMDTY1 << 2));
      break;

    case PWM2PWM5:
      tmpRegValue = (((PWMDTYA & 0xcf) >> 4) | (PWMDTY2 << 2));
      break;

    default:
      break;
  }

  if(Change_Direction == PWM_DutyChange_Up)
  {
    tmpRegValue += DutyIncremental;				//ռ�ձ�����
  }
  else
  {
    tmpRegValue -= DutyIncremental;				//ռ�ձȼ���
  }

  /* ��������������� */
  if(tmpRegValue > tmpPolarity)
    return ERROR;

  switch(PWM_ComplementaryOutputPin)	//����ռ�ձ�
  {
    case PWM0PWM3:
      PWMDTYA = PWMDTYA & 0xfc | (tmpRegValue % 4);
      PWMDTY0 = (uint8_t)(tmpRegValue >> 2);
      break;

    case PWM1PWM4:
      PWMDTYA = PWMDTYA & 0xf3 | ((tmpRegValue % 4) << 2);
      PWMDTY1 = (uint8_t)(tmpRegValue >> 2);
      break;

    case PWM2PWM5:
      PWMDTYA = PWMDTYA & 0xcf | ((tmpRegValue % 4) << 4);
      PWMDTY2 = (uint8_t)(tmpRegValue >> 2);
      break;

    default:
      break;
  }
  return SUCCESS;
}

/**************************************************
*��������:void PWM_DeadTimeConfig(uint8_t PWM012_RisingDeadTime, uint8_t PWM345_fallingDeadTime)
*��������:PWM��������ģʽ������ʱ�����ú���
*��ڲ���:
uint8_t:PWM012_RisingDeadTime:PWM��������ʱ��
uint8_t:PWM345_fallingDeadTime:PWM�����½�ʱ��
*���ڲ���:void
**************************************************/
void PWM_DeadTimeConfig(uint8_t
                        PWM012_RisingDeadTime,
                        uint8_t PWM345_fallingDeadTime)
{
  PWMDTY3 = (PWM012_RisingDeadTime |
             (PWM345_fallingDeadTime << 4));
}

/*****************************************************
*��������:void PWM_Cmd(FunctionalState NewState)
*��������:PWM���ܿ��غ���
*��ڲ���:
FunctionalState:NewState:��������/�ر�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_Cmd(FunctionalState NewState)
{
  if(NewState != DISABLE)
  {
    PWMCON0 |= 0X80;
  }
  else
  {
    PWMCON0 &= ~0X80;
  }
}

/*****************************************************
*��������:void PWM_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:PWM�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
void PWM_ITConfig(FunctionalState NewState,
                  PriorityStatus Priority)
{
  if(NewState != DISABLE)
  {
    IE1 |= 0X02;
  }
  else
  {
    IE1 &= 0XFD;
  }

  if(Priority == LOW)
  {
    IP1 &= 0XFD;
  }
  else
  {
    IP1 |= 0X02;
  }
}

/*****************************************************
*��������:FlagStatus PWM_GetFlagStatus(void)
*��������:���PWM�жϱ�־״̬
*��ڲ���:void
*���ڲ���:
FlagStatus:PWM�жϱ�־״̬
*****************************************************/
FlagStatus PWM_GetFlagStatus(void)
{
  return (bool)(PWMCON0 & 0X40);
}

/*****************************************************
*��������:void PWM_ClearFlag(void)
*��������:���PWM�жϱ�־״̬
*��ڲ���:void
*���ڲ���:void
*****************************************************/
void PWM_ClearFlag(void)
{
  PWMCON0 &= 0XBF;
}

#endif

/******************* (C) COPYRIGHT 2022 RDS Microelectronics *****END OF FILE****/
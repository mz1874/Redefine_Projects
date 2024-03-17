//************************************************************
//  Copyright (c) �Ϸ����¶���������޹�˾
//	�ļ�����: 		rd8_pwm.h
//	����:					�¶���Ӧ���Ŷ�
//	ģ�鹦��: 		PWM�̼��⺯��ͷ�ļ�
//  ����������:	2022��7��6��
// 	�汾: 				V1.001
//  ˵��:���ļ���������RD8ϵ��оƬ
//*************************************************************

#ifndef _rd8_PWM_H_
#define _rd8_PWM_H_

#include "rd8.h"
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x)
//PWMԤ��Ƶѡ��
typedef enum
{
  PWM0_PRESSEL_FHRC_D1 = (uint8_t)0x00, //PWM0Ԥ��ƵΪFhrc/1
  PWM0_PRESSEL_FHRC_D2 = (uint8_t)0x10, //PWM0Ԥ��ƵΪFhrc/2
  PWM0_PRESSEL_FHRC_D4 = (uint8_t)0x20, //PWM0Ԥ��ƵΪFhrc/4
  PWM0_PRESSEL_FHRC_D8 = (uint8_t)0x30, //PWM0Ԥ��ƵΪFhrc/8
  PWM2_PRESSEL_FHRC_D1 = (uint8_t)0x02, //PWM2Ԥ��ƵΪFhrc/1
  PWM3_PRESSEL_FHRC_D1 = (uint8_t)0x03, //PWM3Ԥ��ƵΪFhrc/1
  PWM4_PRESSEL_FHRC_D1 = (uint8_t)0x04, //PWM4Ԥ��ƵΪFhrc/1
} PWM_PresSel_TypeDef;

//PWM���ͨ��ѡ��
typedef enum
{
  PWM00 = (uint8_t)0x00, //PWM���ͨ��ѡ��: PWM00
  PWM01 = (uint8_t)0x01, //PWM���ͨ��ѡ��: PWM01
  PWM02 = (uint8_t)0x02, //PWM���ͨ��ѡ��: PWM02
  PWM03 = (uint8_t)0x03, //PWM���ͨ��ѡ��: PWM03
  PWM04 = (uint8_t)0x04, //PWM���ͨ��ѡ��: PWM04
  PWM05 = (uint8_t)0x05, //PWM���ͨ��ѡ��: PWM05
  PWM06 = (uint8_t)0x06, //PWM���ͨ��ѡ��: PWM06
  PWM07 = (uint8_t)0x07, //PWM���ͨ��ѡ��: PWM07
  PWM20 = (uint8_t)0x20, //PWM���ͨ��ѡ��: PWM20
  PWM21 = (uint8_t)0x21, //PWM���ͨ��ѡ��: PWM21
  PWM30 = (uint8_t)0x32, //PWM���ͨ��ѡ��: PWM30
  PWM31 = (uint8_t)0x33, //PWM���ͨ��ѡ��: PWM31
  PWM40 = (uint8_t)0x44, //PWM���ͨ��ѡ��: PWM40
  PWM41 = (uint8_t)0x45, //PWM���ͨ��ѡ��: PWM41
} PWM_OutputPin_TypeDef;

//PWM����ģʽͨ��ѡ��
typedef enum
{
  PWM00PWM01 = (uint8_t)0x00, //PWM����ģʽͨ��ѡ��:PWM00��PWM01
  PWM02PWM03 = (uint8_t)0x02, //PWM����ģʽͨ��ѡ��:PWM02��PWM03
  PWM04PWM05 = (uint8_t)0x04, //PWM����ģʽͨ��ѡ��:PWM04��PWM05
  PWM06PWM07 = (uint8_t)0x06  //PWM����ģʽͨ��ѡ��:PWM06��PWM07
} PWM_ComplementaryOutputPin_TypeDef;

//PWMԴѡ��
typedef enum
{
  PWM0_Type = (uint8_t)0x00, //����PWM0
  PWM2_Type = (uint8_t)0x02, //����PWM2
  PWM3_Type = (uint8_t)0x03, //����PWM3
  PWM4_Type = (uint8_t)0x04, //����PWM4
} PWM_Type_TypeDef;

#endif

#if defined(RD8G05x) || defined(RD8T05x)
//PWMԤ��Ƶѡ��
typedef enum
{
  PWM_PRESSEL_FHRC_D1 = (uint8_t)0x00, //PWM0Ԥ��ƵΪFhrc/1
  PWM_PRESSEL_FHRC_D2 = (uint8_t)0x10, //PWM0Ԥ��ƵΪFhrc/2
  PWM_PRESSEL_FHRC_D4 = (uint8_t)0x20, //PWM0Ԥ��ƵΪFhrc/4
  PWM_PRESSEL_FHRC_D8 = (uint8_t)0x30, //PWM0Ԥ��ƵΪFhrc/8
} PWM_PresSel_TypeDef;

//PWM���ͨ��ѡ��
typedef enum
{
  PWM0 = (uint8_t)0x00, //PWM���ͨ��ѡ��: PWM00
  PWM1 = (uint8_t)0x01, //PWM���ͨ��ѡ��: PWM01
  PWM2 = (uint8_t)0x02, //PWM���ͨ��ѡ��: PWM02
  PWM3 = (uint8_t)0x03, //PWM���ͨ��ѡ��: PWM03
  PWM4 = (uint8_t)0x04, //PWM���ͨ��ѡ��: PWM04
  PWM5 = (uint8_t)0x05, //PWM���ͨ��ѡ��: PWM05
  PWM6 = (uint8_t)0x06, //PWM���ͨ��ѡ��: PWM06
  PWM7 = (uint8_t)0x07, //PWM���ͨ��ѡ��: PWM07
} PWM_OutputPin_TypeDef;

//PWM����ģʽͨ��ѡ��
typedef enum
{
  PWM0PWM1 = (uint8_t)0x00, //PWM����ģʽͨ��ѡ��:PWM00��PWM01
  PWM2PWM3 = (uint8_t)0x02, //PWM����ģʽͨ��ѡ��:PWM02��PWM03
  PWM4PWM5 = (uint8_t)0x04, //PWM����ģʽͨ��ѡ��:PWM04��PWM05
  PWM6PWM7 = (uint8_t)0x06  //PWM����ģʽͨ��ѡ��:PWM06��PWM07
} PWM_ComplementaryOutputPin_TypeDef;

//PWMԴѡ��
typedef enum
{
  PWM0_Type = (uint8_t)0x00, //����PWM0
} PWM_Type_TypeDef;

#endif

//PWM���ϼ��ģʽ
typedef enum
{
  PWM0_Latch_Mode = ((uint8_t)0x00),    //PWM���ϼ��ģʽ:����ģʽ
  PWM0_Immediate_Mode = ((uint8_t)0x20) //PWM���ϼ��ģʽ:����ģʽ
} PWM_FaultDetectionMode_TypeDef;

//PWM���ϼ���ƽѡ��
typedef enum
{
  PWM0_FaultDetectionVoltage_Low = ((uint8_t)0x00), //PWM���ϼ��͵�ƽѡ��
  PWM0_FaultDetectionVoltage_high = ((uint8_t)0x10) //PWM���ϼ��ߵ�ƽѡ��
} PWM_FaultDetectionVoltageSelect_TypeDef;

//PWM���ϼ�������ź��˲�ʱ��
typedef enum
{
  PWM0_WaveFilteringTime_0us = ((uint8_t)0x00), //PWM���ϼ�������ź��˲�ʱ��0us
  PWM0_WaveFilteringTime_1us = ((uint8_t)0x01), //PWM���ϼ�������ź��˲�ʱ��1us
  PWM0_WaveFilteringTime_4us = ((uint8_t)0x02), //PWM���ϼ�������ź��˲�ʱ��4us
  PWM0_WaveFilteringTime_16us = ((uint8_t)0x03) //PWM���ϼ�������ź��˲�ʱ��16us
} PWM_FaultDetectionWaveFilteringTime_TypeDef;

#endif

#if defined (RD8G403)
typedef enum
{
  PWM_PRESSEL_FOSC_D1  = (uint8_t)0x00,		//PWMԤ��ƵΪFosc/1
  PWM_PRESSEL_FOSC_D2  = (uint8_t)0x01,		//PWMԤ��ƵΪFosc/2
  PWM_PRESSEL_FOSC_D8  = (uint8_t)0x02,		//PWMԤ��ƵΪFosc/8
  PWM_PRESSEL_FOSC_D32 = (uint8_t)0x03		//PWMԤ��ƵΪFosc/32
} PWM_PresSel_TypeDef;

typedef enum
{
  PWM2_OutputPin_P26       = ((uint8_t)0x00),		//PWM2�����ѡ��P26
  PWM2_OutputPin_P14       = ((uint8_t)0x04)		//PWM2�����ѡ��P14
} PWM2_OutputPin_TypeDef;

typedef enum
{
  PWM5_OutputPin_P12       = ((uint8_t)0x00),		//PWM5�����ѡ��P12
  PWM5_OutputPin_P21       = ((uint8_t)0x08)		//PWM5�����ѡ��P21
} PWM5_OutputPin_TypeDef;

typedef enum
{
  PWM0 = (uint8_t)0x01,						//PWM���ͨ��ѡ��:PWM0
  PWM1 = (uint8_t)0x02,						//PWM���ͨ��ѡ��:PWM1
  PWM2 = (uint8_t)0x04,						//PWM���ͨ��ѡ��:PWM2
  PWM3 = (uint8_t)0x08,						//PWM���ͨ��ѡ��:PWM3
  PWM4 = (uint8_t)0x10,						//PWM���ͨ��ѡ��:PWM4
  PWM5 = (uint8_t)0x20,						//PWM���ͨ��ѡ��:PWM5
  PWM6 = (uint8_t)0x40,						//PWM���ͨ��ѡ��:PWM6
} PWM_OutputPin_TypeDef;

typedef enum
{
  PWM0PWM3 = (uint8_t)0x00,					//PWM����ģʽͨ��ѡ��:PWM0��PWM3
  PWM1PWM4 = (uint8_t)0x01,					//PWM����ģʽͨ��ѡ��:PWM1��PWM4
  PWM2PWM5 = (uint8_t)0x02					//PWM����ģʽͨ��ѡ��:PWM2��PWM5
} PWM_ComplementaryOutputPin_TypeDef;

//PWMԴѡ��
typedef enum
{
  PWM0_Type = (uint8_t)0x00, //����PWM0
} PWM_Type_TypeDef;
#endif

//PWM����ģʽ
typedef enum
{
  PWM0_Edge_Aligned_Mode = (uint8_t)0x00,     //PWM���ض���ģʽ
  PWM0_Center_Alignment_Mode = (uint8_t)0x01, //PWM�м����ģʽ
} PWM_Aligned_Mode_TypeDef;

//PWM���Ÿ���ѡ��
typedef enum
{
  PWM_OUTPUTSTATE_DISABLE = ((uint8_t)0x00), //��PIN����ΪGPIO
  PWM_OUTPUTSTATE_ENABLE = ((uint8_t)0x01)   //��PIN����ΪPWM
} PWM_OutputState_TypeDef;

//PWM���������ѡ��
typedef enum
{
  PWM_POLARITY_NON_INVERT = ((uint8_t)0x00), //PWM���������
  PWM_POLARITY_INVERT = ((uint8_t)0x01)      //PWM�������
} PWM_Polarity_TypeDef;

//PWMռ�ձȸı䷽��
typedef enum
{
  PWM_DutyChange_Up = (uint8_t)0x01, 		//PWMռ�ձ�����
  PWM_DutyChange_Dowm = (uint8_t)0x00, 	//PWMռ�ձȼ���
} PWM_DutyChange_TypeDef;

/* PWM0����������������������Ĭ��ΪPWM0 */
void PWM_DeInit(void);
// ��������ʱ��
void PWM_DeadTimeConfig(uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime);
// ʹ��PWM
void PWM_Cmd(FunctionalState NewState);

// ����PWM�ж�
void PWM_ITConfig(FunctionalState NewState,
                  PriorityStatus Priority);

// ��ȡ�ж�λ
FlagStatus PWM_GetFlagStatus(void);
//����ж�λ
void PWM_ClearFlag(void);

#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
FlagStatus PWM_GetFaultDetectionFlagStatus(void);
void PWM_ClearFaultDetectionFlag(void);
void PWM_FaultDetectionConfig(FunctionalState NewState);
void PWM_FaultDetectionModeConfig(PWM_FaultDetectionMode_TypeDef FaultDetectionMode,
                                  PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect,
                                  PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime);
#endif

/* ͨ�û������������� �βο���ѡ�������PWMԴ*/
void PWM_Init(PWM_PresSel_TypeDef PWM_PresSel, uint16_t PWM_Period);
// ����PWM ���������䷽ʽ
void PWM_Aligned_Mode_Select(PWM_Aligned_Mode_TypeDef PWM_Aligned_Mode);
//���ʹ��
void PWM_OutputStateConfig(uint8_t PWM_OutputPin,
                           PWM_OutputState_TypeDef PWM_OutputState);
//��������
void PWM_PolarityConfig(uint8_t PWM_OutputPin,
                        PWM_Polarity_TypeDef PWM_Polarity);
//����ģʽ����
void PWM_IndependentModeConfig(PWM_OutputPin_TypeDef PWM_OutputPin, uint16_t PWM_DutyCycle);
//����ģʽ����
void PWM_ComplementaryModeConfig(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin,
                                 uint16_t PWM_DutyCycle);
//����ģʽ����
void PWM_IndependentModeConfigEX(PWM_OutputPin_TypeDef PWM_ComplementaryOutputPin,
                                 uint16_t PWM_DutyCycle,
                                 PWM_OutputState_TypeDef PWM_OutputState);
//����ģʽ����
void PWM_ComplementaryModeConfigEX(PWM_ComplementaryOutputPin_TypeDef PWM_OutputPin,
                                   uint16_t PWM_DutyCycle,
                                   PWM_OutputState_TypeDef PWM_OutputState);
//���Ķ���ģʽռ�ձ�
ErrorStatus PWM_IndependentMode_DutyChange(PWM_OutputPin_TypeDef PWM_OutputPin,
    PWM_DutyChange_TypeDef Change_Direction,
    uint16_t DutyIncremental);
//���Ļ���ģʽռ�ձ�
ErrorStatus PWM_ComplementaryMode_DutyChange(PWM_ComplementaryOutputPin_TypeDef PWM_ComplementaryOutputPin,
    PWM_DutyChange_TypeDef Change_Direction,
    uint16_t DutyIncremental);


/* ��չ�������������PWM0������������������ѡ�������PWMԴ���β� */
void PWM_DeInitEX(PWM_Type_TypeDef PWM_Type);
void PWM_DeadTimeConfigEX(PWM_Type_TypeDef PWM_Type, uint8_t PWM_RisingDeadTime, uint8_t PWM_FallingDeadTime);
void PWM_CmdEX(PWM_Type_TypeDef PWM_Type,
               FunctionalState NewState);
void PWM_ITConfigEX(PWM_Type_TypeDef PWM_Type, FunctionalState NewState, PriorityStatus Priority);
FlagStatus PWM_GetFlagStatusEX(PWM_Type_TypeDef PWM_Type);
void PWM_ClearFlagEX(PWM_Type_TypeDef PWM_Type);
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
FlagStatus PWM_GetFaultDetectionFlagStatusEX(PWM_Type_TypeDef PWM_Type);
void PWM_ClearFaultDetectionFlagEX(PWM_Type_TypeDef PWM_Type);
void PWM_FaultDetectionConfigEX(PWM_Type_TypeDef PWM_Type, FunctionalState NewState);
void PWM_FaultDetectionModeConfigEX(PWM_Type_TypeDef PWM_Type,
                                    PWM_FaultDetectionMode_TypeDef FaultDetectionMode,
                                    PWM_FaultDetectionVoltageSelect_TypeDef FaultDetectionVoltageSelect,
                                    PWM_FaultDetectionWaveFilteringTime_TypeDef FaultDetectionWaveFilteringTime);
#endif



/* PWM�����ظ���ѡ�� */
#if defined (RD8G403)
void PWM_PWM2Selection(PWM2_OutputPin_TypeDef PWM2_OutputPin);
void PWM_PWM5Selection(PWM5_OutputPin_TypeDef PWM5_OutputPin);
#endif

#endif

/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/
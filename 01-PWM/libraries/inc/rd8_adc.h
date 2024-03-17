//************************************************************
//  Copyright (c) �Ϸ����¶���������޹�˾
//	�ļ�����: 		rd8_adc.h
//	����:					�¶���Ӧ���Ŷ�
//	ģ�鹦��: 		BTM�̼��⺯��C�ļ�
//  ����������: 2022��5��17��
// 	�汾: 				V1.000
//  ˵��: 
//*************************************************************

#ifndef _rd8_ADC_H_
#define _rd8_ADC_H_

#include "rd8.h"
//˵��:ADC�ο���Դö�ٶ�����option.h��ʹ��ADC��ע�⽫���ļ�����
#include "rd8_option.h"

#if defined (RD8G403)
/* ADC����ʱ�ӷ�Ƶö�� */
typedef enum
{
  ADC_PRESSEL_FHRC_D32 = (uint8_t)0x00, //Ԥ��Ƶ fADC = fHRC/32
  ADC_PRESSEL_FHRC_D24 = (uint8_t)0x01, //Ԥ��Ƶ fADC = fHRC/24
  ADC_PRESSEL_FHRC_D16 = (uint8_t)0x02, //Ԥ��Ƶ fADC = fHRC/16
  ADC_PRESSEL_FHRC_D12 = (uint8_t)0x03, //Ԥ��Ƶ fADC = fHRC/12
  ADC_PRESSEL_FHRC_D8 = (uint8_t)0x04,  //Ԥ��Ƶ fADC = fHRC/8
  ADC_PRESSEL_FHRC_D6 = (uint8_t)0x05,  //Ԥ��Ƶ fADC = fHRC/6
  ADC_PRESSEL_FHRC_D4 = (uint8_t)0x06,  //Ԥ��Ƶ fADC = fHRC/4
  ADC_PRESSEL_FHRC_D3 = (uint8_t)0x07   //Ԥ��Ƶ fADC = fHRC/3
} ADC_PresSel_TypeDef;

//ADC��������ѡ��ö��
typedef enum
{
  ADC_Cycle_6Cycle = (uint8_t)0x00, //ADC����ʱ��Ϊ6��ADC����ʱ������
  ADC_Cycle_36Cycle = (uint8_t)0x08 //ADC����ʱ��Ϊ36��ADC����ʱ������
} ADC_Cycle_TypeDef;
#else
/* ADC����ʱ�ӷ�Ƶö�� */
typedef enum
{
  ADC_PRESSEL_3CLOCK = (uint8_t)0x10,  //����ʱ��Ϊ3��ϵͳʱ��
  ADC_PRESSEL_6CLOCK = (uint8_t)0x14,  //����ʱ��Ϊ6��ϵͳʱ��
  ADC_PRESSEL_16CLOCK = (uint8_t)0x18, //����ʱ��Ϊ16��ϵͳʱ��
  ADC_PRESSEL_32CLOCK = (uint8_t)0x1c  //����ʱ��Ϊ32��ϵͳʱ��
} ADC_PresSel_TypeDef;

//ADC��������ѡ��ö��
typedef enum
{
  ADC_Cycle_Null = 0x00 //�ù�����Ч
} ADC_Cycle_TypeDef;
#endif

#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x)
//ADC����ͨ��ѡ��
typedef enum
{
  ADC_CHANNEL_0 = (uint8_t)0x00,     //ѡ��AIN0��AD�����
  ADC_CHANNEL_1 = (uint8_t)0x01,     //ѡ��AIN1��AD�����
  ADC_CHANNEL_2 = (uint8_t)0x02,     //ѡ��AIN2��AD�����
  ADC_CHANNEL_3 = (uint8_t)0x03,     //ѡ��AIN3��AD�����
  ADC_CHANNEL_4 = (uint8_t)0x04,     //ѡ��AIN4��AD�����
  ADC_CHANNEL_5 = (uint8_t)0x05,     //ѡ��AIN5��AD�����
  ADC_CHANNEL_6 = (uint8_t)0x06,     //ѡ��AIN6��AD�����
  ADC_CHANNEL_7 = (uint8_t)0x07,     //ѡ��AIN7��AD�����
  ADC_CHANNEL_8 = (uint8_t)0x08,     //ѡ��AIN8��AD�����
  ADC_CHANNEL_9 = (uint8_t)0x09,     //ѡ��AIN9��AD�����
  ADC_CHANNEL_10 = (uint8_t)0x0A,    //ѡ��AIN10��AD�����
  ADC_CHANNEL_11 = (uint8_t)0x0B,    //ѡ��AIN11��AD�����
  ADC_CHANNEL_12 = (uint8_t)0x0C,    //ѡ��AIN12��AD�����
  ADC_CHANNEL_13 = (uint8_t)0x0D,    //ѡ��AIN13��AD�����
  ADC_CHANNEL_14 = (uint8_t)0x0E,    //ѡ��AIN14��AD�����
  ADC_CHANNEL_15 = (uint8_t)0x0F,    //ѡ��AIN15��AD�����
  ADC_CHANNEL_VDD_D4 = (uint8_t)0x1f //ѡ���ڲ�1/4VDD��AD�����
} ADC_Channel_TypeDef;

//ADC����ͨ��ʹ��ö��
typedef enum
{
  ADC_EAIN_0 = (uint16_t)0x0001,  //ѡ��AIN0
  ADC_EAIN_1 = (uint16_t)0x0002,  //ѡ��AIN1
  ADC_EAIN_2 = (uint16_t)0x0004,  //ѡ��AIN2
  ADC_EAIN_3 = (uint16_t)0x0008,  //ѡ��AIN3
  ADC_EAIN_4 = (uint16_t)0x0010,  //ѡ��AIN4
  ADC_EAIN_5 = (uint16_t)0x0020,  //ѡ��AIN5
  ADC_EAIN_6 = (uint16_t)0x0040,  //ѡ��AIN6
  ADC_EAIN_7 = (uint16_t)0x0080,  //ѡ��AIN7
  ADC_EAIN_8 = (uint16_t)0x0100,  //ѡ��AIN8
  ADC_EAIN_9 = (uint16_t)0x0200,  //ѡ��AIN9
  ADC_EAIN_10 = (uint16_t)0x0400, //ѡ��AIN10
  ADC_EAIN_11 = (uint16_t)0x0800, //ѡ��AIN11
  ADC_EAIN_12 = (uint16_t)0x1000, //ѡ��AIN12
  ADC_EAIN_13 = (uint16_t)0x2000, //ѡ��AIN13
  ADC_EAIN_14 = (uint16_t)0x4000, //ѡ��AIN14
  ADC_EAIN_15 = (uint16_t)0x8000  //ѡ��AIN15
} ADC_EAIN_TypeDef;
#endif
#if defined(RD8G05x) || defined(RD8T05x)
typedef enum
{
  ADC_CHANNEL_0 = (uint8_t)0x00,     //ѡ��AIN0��AD�����
  ADC_CHANNEL_1 = (uint8_t)0x01,     //ѡ��AIN1��AD�����
  ADC_CHANNEL_2 = (uint8_t)0x02,     //ѡ��AIN2��AD�����
  ADC_CHANNEL_3 = (uint8_t)0x03,     //ѡ��AIN3��AD�����
  ADC_CHANNEL_4 = (uint8_t)0x04,     //ѡ��AIN4��AD�����
  ADC_CHANNEL_5 = (uint8_t)0x05,     //ѡ��AIN5��AD�����
  ADC_CHANNEL_6 = (uint8_t)0x06,     //ѡ��AIN6��AD�����
  ADC_CHANNEL_7 = (uint8_t)0x07,     //ѡ��AIN7��AD�����
  ADC_CHANNEL_8 = (uint8_t)0x08,     //ѡ��AIN8��AD�����
  ADC_CHANNEL_9 = (uint8_t)0x09,     //ѡ��AIN9��AD�����
  ADC_CHANNEL_VDD_D4 = (uint8_t)0x1f //ѡ���ڲ�1/4VDD��AD�����
} ADC_Channel_TypeDef;

typedef enum
{
  ADC_EAIN_0 = (uint16_t)0x0001, //ѡ��AIN0
  ADC_EAIN_1 = (uint16_t)0x0002, //ѡ��AIN1
  ADC_EAIN_2 = (uint16_t)0x0004, //ѡ��AIN2
  ADC_EAIN_3 = (uint16_t)0x0008, //ѡ��AIN3
  ADC_EAIN_4 = (uint16_t)0x0010, //ѡ��AIN4
  ADC_EAIN_5 = (uint16_t)0x0020, //ѡ��AIN5
  ADC_EAIN_6 = (uint16_t)0x0040, //ѡ��AIN6
  ADC_EAIN_7 = (uint16_t)0x0080, //ѡ��AIN7
  ADC_EAIN_8 = (uint16_t)0x0100, //ѡ��AIN8
  ADC_EAIN_9 = (uint16_t)0x0200, //ѡ��AIN9
} ADC_EAIN_TypeDef;
#endif

#if defined(RD8G403)
typedef enum
{
  ADC_CHANNEL_0 = (uint8_t)0x00,     //ѡ��AIN0��AD�����
  ADC_CHANNEL_1 = (uint8_t)0x01,     //ѡ��AIN1��AD�����
  ADC_CHANNEL_2 = (uint8_t)0x02,     //ѡ��AIN2��AD�����
  ADC_CHANNEL_3 = (uint8_t)0x03,     //ѡ��AIN3��AD�����
  ADC_CHANNEL_4 = (uint8_t)0x04,     //ѡ��AIN4��AD�����
  ADC_CHANNEL_5 = (uint8_t)0x05,     //ѡ��AIN5��AD�����
  ADC_CHANNEL_6 = (uint8_t)0x06,     //ѡ��AIN6��AD�����
  ADC_CHANNEL_VDD_D4 = (uint8_t)0x1f //ѡ���ڲ�1/4VDD��AD�����
} ADC_Channel_TypeDef;

typedef enum
{
  ADC_EAIN_0 = (uint16_t)0x0001, //ѡ��AIN0
  ADC_EAIN_1 = (uint16_t)0x0002, //ѡ��AIN1
  ADC_EAIN_2 = (uint16_t)0x0004, //ѡ��AIN2
  ADC_EAIN_3 = (uint16_t)0x0008, //ѡ��AIN3
  ADC_EAIN_4 = (uint16_t)0x0010, //ѡ��AIN4
  ADC_EAIN_5 = (uint16_t)0x0020, //ѡ��AIN5
  ADC_EAIN_6 = (uint16_t)0x0040  //ѡ��AIN6
} ADC_EAIN_TypeDef;
#endif

//ADCת��ƽ��ֵ��������
typedef enum
{
  ADC_SamplesNum_FourTimes = 0x04,			//��������Ϊ4��
	ADC_SamplesNum_SixTimes = 0x06,				//��������Ϊ6��
	ADC_SamplesNum_EightTimes = 0x08,			//��������Ϊ8��
	ADC_SamplesNum_TenTimes = 0x0A,				//��������Ϊ10��
} ADC_SamplesNum_TypeDef;

/*******************************�꺯��*******************************/
/*****************************************************
*��������:void ADC_StartConversion(void)
*��������:��ʼһ��ADת��
*��ڲ���:void
*���ڲ���:void
*****************************************************/
#define ADC_StartConversion() SET_BIT(ADCCON,0X40)

/*****************************************************
*��������:void ADC_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*��������:ADC�жϳ�ʼ��
*��ڲ���:
FunctionalState:NewState:�ж�ʹ��/�ر�ѡ��
PriorityStatus:Priority:�ж����ȼ�ѡ��
*���ڲ���:void
*****************************************************/
#define ADC_ITConfig(NewState,Priority)										\
					do{  																						\
							EADC = (bit)NewState;												\
							IPADC = (bit)Priority;											\
					}while(0)

/*****************************************************
*��������:FlagStatus ADC_GetFlagStatus(void)
*��������:���ADC�жϱ�־״̬
*��ڲ���:void
*���ڲ���:
FlagStatus:ADC�жϱ�־״̬
*****************************************************/
#define ADC_GetFlagStatus() ((READ_BIT(ADCCON,0x20)) ? (SET):(RESET))

/*****************************************************
*��������:void ADC_ClearFlag(void)
*��������:���ADC�жϱ�־״̬
*��ڲ���:void
*���ڲ���:void
*****************************************************/
#define ADC_ClearFlag() CLEAR_BIT(ADCCON,0x20)

void ADC_DeInit(void);
void ADC_Init(ADC_PresSel_TypeDef ADC_PrescalerSelection, ADC_Cycle_TypeDef ADC_Cycle);
void ADC_ChannelConfig(ADC_Channel_TypeDef ADC_Channel, FunctionalState NewState);
void ADC_EAINConfig(uint16_t ADC_EAIN_Select, FunctionalState NewState);
void ADC_Cmd(FunctionalState NewState);
uint16_t ADC_GetConversionValue(void);
void ADC_VrefConfig(ADC_Vref_TypeDef ADC_Vref);
uint16_t ADC_GetConversionAverageValue(ADC_SamplesNum_TypeDef ADC_SamplesNum);
#endif

/******************* (C) COPYRIGHT 2021 SinOne Microelectronics *****END OF FILE****/
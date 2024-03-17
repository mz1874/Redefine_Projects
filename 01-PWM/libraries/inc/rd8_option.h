//************************************************************
//  Copyright (c) �Ϸ����¶���������޹�˾
//	�ļ�����: 		rd8_option.h
//	����:					�¶���Ӧ���Ŷ�
//	ģ�鹦��: 		Customer Option�Ĵ�������ͷ�ļ�
//  ����������: 2022��5��20��
// 	�汾: 				V1.000
//  ˵��:���ļ���������RD8ϵ��оƬ
//*************************************************************

#ifndef _rd8_OPTION_H_
#define _rd8_OPTION_H_

#include "rd8.h"

//ϵͳʱ�ӷ�Ƶö��
typedef enum
{
  SYSCLK_PRESSEL_FOSC_D1 = (uint8_t)0x00, //Ԥ��Ƶ Fsys = Fosc/1
  SYSCLK_PRESSEL_FOSC_D2 = (uint8_t)0x10, //Ԥ��Ƶ Fsys = Fosc/2
  SYSCLK_PRESSEL_FOSC_D4 = (uint8_t)0x20, //Ԥ��Ƶ Fsys = Fosc/4
  SYSCLK_PRESSEL_FOSC_D8 = (uint8_t)0x30  //Ԥ��Ƶ Fsys = Fosc/8
} SYSCLK_PresSel_TypeDef;

//�͵�ѹ��λ��λѡ��
typedef enum
{
  LVR_INVALID = (uint8_t)0x04, //LVR��Ч
  LVR_1_9V = (uint8_t)0x00,    //LVR 1.9V��λ
  LVR_2_9V = (uint8_t)0x01,    //LVR 2.9V��λ
  LVR_3_7V = (uint8_t)0x02,    //LVR 3.7V��λ
  LVR_4_3V = (uint8_t)0x03     //LVR 4.3V��λ
} LVR_Config_TypeDef;

//IAP������λö��
#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
typedef enum
{
  IAP_OPERATERANGE__LAST_0K_CODEREGION = (uint8_t)0x00, //���������IAP����
  IAP_OPERATERANGE__LAST_1K_CODEREGION = (uint8_t)0x04, //����ROM���1k����IAP����
  IAP_OPERATERANGE__LAST_2K_CODEREGION = (uint8_t)0x08, //����ROM���2k����IAP����
  IAP_OPERATERANGE__ALL_CODEREGION = (uint8_t)0x0c      //����ROM�����������IAP����
} IAP_OperateRange_TypeDef;
#endif
#if defined(RD8G403)
typedef enum
{
  IAP_OPERATERANGE_ONLY_EEPROM 		    = (uint8_t)0x00,	//ֻ����EEPROM����IAP����
  IAP_OPERATERANGE__LAST_0_5K_CODEREGION  = (uint8_t)0x04,	//����ROM���0.5k��EEPROM����IAP����
  IAP_OPERATERANGE__LAST_1K_CODEREGION    = (uint8_t)0x08,	//����ROM���1k��EEPROM����IAP����
  IAP_OPERATERANGE__ALL_CODEREGION 	    = (uint8_t)0x0c		//����ROM��EEPROM�����������IAP����
} IAP_OperateRange_TypeDef;
#endif

#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x)
/* ADC�ο���ѹ��λö�� */
typedef enum
{
  ADC_VREF_VDD = 0x00,    //VDD���ο�ADC��ѹ
  ADC_VREF_2_048V = 0x40,	//�ڲ�2.048V��ADC�ο���ѹ
  ADC_VREF_1_024V = 0x80, //�ڲ�1.024V��ADC�ο���ѹ
  ADC_VREF_2_4V = 0xC0  	//�ڲ�2.4V��ADC�ο���ѹ
} ADC_Vref_TypeDef;
#endif 
#if defined(RD8G403)
typedef enum
{
  ADC_VREF_VDD  = 0x00,					//ѡ��VDD��ADC�ο���ѹ
  ADC_VREF_2_4V = 0x80,   			//ѡ���ڲ�2.4V��ADC�ο���ѹ
} ADC_Vref_TypeDef;
#endif

#if defined(RD8G05x) || defined(RD8T05x)
/* ADC�ο���ѹ��λö�� */
typedef enum
{
  ADC_VREF_VDD  = 0x00,					//ѡ��VDD��ADC�ο���ѹ
  ADC_VREF_1_024V = 0x40,   		//ѡ���ڲ�1.024V��ADC�ο���ѹ
  ADC_VREF_2_4V = 0x80,   			//ѡ���ڲ�2.4V��ADC�ο���ѹ
  ADC_VREF_2_048V = 0xC0,				//ѡ���ڲ�2.048V��ADC�ο���ѹ
} ADC_Vref_TypeDef;
#endif

void OPTION_WDT_Cmd(FunctionalState NewState);
void OPTION_XTIPLL_Cmd(FunctionalState NewState);
void OPTION_SYSCLK_Init(SYSCLK_PresSel_TypeDef SYSCLK_PresSel);
void OPTION_LVR_Init(LVR_Config_TypeDef LVR_Config);
void OPTION_ADC_VrefConfig(ADC_Vref_TypeDef ADC_Vref);
void OPTION_IAP_SetOperateRange(IAP_OperateRange_TypeDef IAP_OperateRange);
void OPTION_JTG_Cmd(FunctionalState NewState);

#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
#else
void OPTION_RST_PIN_Cmd(FunctionalState NewState);
#endif

#endif
//************************************************************
//  Copyright (c) 合肥市新定义电子有限公司
//	文件名称:			rd8_adc.c
//	作者:					新定义应用团队
//	模块功能:			BTM固件库函数C文件
//  最后更正日期:	2022年6月8日
// 	版本: 				V1.001
//  说明:
//*************************************************************
#include "rd8_adc.h"

#if defined (RD8G403)
void ADC_DeInit(void)
{
  ADCCON = 0x00;
  ADCCFG0 = 0X00;
  ADCCFG1 = 0X00;
  ADCVL = 0X00;
  ADCVH = 0X00;
  EADC = 0;
  IPADC = 0;
}

void ADC_Init(ADC_PresSel_TypeDef ADC_PrescalerSelection,
              ADC_Cycle_TypeDef ADC_Cycle)
{
  /* 配置ADC时钟分频和采样周期 */
  ADCCFG1 = ADC_PrescalerSelection | ADC_Cycle;
}

void ADC_ChannelConfig(ADC_Channel_TypeDef ADC_Channel, FunctionalState NewState)
{
  uint8_t TempReg;
  /* 配置ADC转换通道 */
  ADCCON = (ADCCON & 0xE0) | ADC_Channel;

  /* 配置ADC采样通道 */
  if(ADC_Channel < ADC_CHANNEL_VDD_D4)	//内部采样通道无需配置
  {
    TempReg = (0x01 << ADC_Channel);
    if(ADC_Channel < ADC_CHANNEL_VDD_D4)
    {
      if(NewState == DISABLE)	//失能ADC采样通道
      {
        ADCCFG0 &= (~TempReg);
      }
      else	//使能ADC采样通道
      {
        ADCCFG0 |= TempReg;
      }
    }
  }
}

/**************************************************
*函数名称:void ADC_EAINConfig(uint16_t ADC_Channel, FunctionalState NewState)
*函数功能:将对应的ADC输入口设置为模拟输入模式
*入口参数:
ADC_EAIN_TypeDef:ADC_EAIN_Select:选择需要设置的ADC口
FunctionalState:NewState:ADC通道使能/关闭选择
*出口参数:void
**************************************************/
void ADC_EAINConfig(uint16_t ADC_EAIN_Select,
                    FunctionalState NewState)
{
  if(NewState == DISABLE)
  {
    ADCCFG0 &= (~(uint8_t)ADC_EAIN_Select);
  }
  else
  {
    ADCCFG0 |= ((uint8_t)ADC_EAIN_Select);
  }
}

/*****************************************************
*函数名称:uint16_t ADC_GetConversionAverageValue(ADC_SamplesNum_TypeDef ADC_SamplesNum)
*函数功能:获得多次AD转换的平均数据
*入口参数:
ADC_SamplesNum_TypeDef:ADC_SamplesNum:AD转换次数
*出口参数:uint16_t
*****************************************************/
uint16_t ADC_GetConversionAverageValue(ADC_SamplesNum_TypeDef ADC_SamplesNum)
{
  uint8_t tmpCnt;
  uint16_t tmpValueSum = 0, tmpValue;
  uint16_t tmpValue_Max = 0, tmpValue_Min = 0xFFFF;
  bit tmpStaus = EADC;
  EADC = 0;

  for(tmpCnt = 0; tmpCnt < ADC_SamplesNum; tmpCnt ++)
  {
    ADC_StartConversion();			//开启一次ADC转换
    while(!ADC_GetFlagStatus());			//等待ADC转换结束
    ADC_ClearFlag();			//清除ADC转换标志位
    tmpValue = ADC_GetConversionValue();			//获取单次转换值

    /* 获取多次转换值中的最大值 */
    if(tmpValue > tmpValue_Max)
      tmpValue_Max = tmpValue;
    /* 获取多次转换值中的最小值 */
    if(tmpValue < tmpValue_Min)
      tmpValue_Min = tmpValue;

    tmpValueSum += tmpValue;//累加多次转换值的和
  }

  /* 软件计算平均值 */
  {
    tmpValue = (tmpValueSum - tmpValue_Max - tmpValue_Min);
    tmpValue /= (ADC_SamplesNum - 2);
  }

  EADC = tmpStaus;			//恢复EADC
  return tmpValue;			//返回平均值
}

#else

/**************************************************
*函数名称:void ADC_DeInit(void)
*函数功能:ADC相关寄存器复位至缺省值
*入口参数:void
*出口参数:void
**************************************************/
void ADC_DeInit(void)
{
  ADCCON = 0x00;
  ADCCFG0 = 0X00;
  ADCCFG1 = 0X00;
  ADCCFG2 = 0X00;
  ADCVL = 0X00;
  ADCVH = 0X00;
  EADC = 0;
  IPADC = 0;
}

/**************************************************
*函数名称:void ADC_Init(ADC_PresSel_TypeDef ADC_PrescalerSelection,ADC_Cycle_TypeDef ADC_Cycle)
*函数功能:ADC初始化配置函数
*入口参数:
ADC_PresSel_TypeDef:ADC_PrescalerSelection:ADC预分频选择
ADC_Cycle_TypeDef:ADC_Cycle:采样时间选择
*出口参数:void
**************************************************/
void ADC_Init(ADC_PresSel_TypeDef ADC_PrescalerSelection, ADC_Cycle_TypeDef ADC_Cycle)
{
  /* 配置ADC采样时钟分频 */
  ADCCFG2 = ADC_PrescalerSelection;
  /* 该入参在RDS系列无效 */
  ADC_Cycle = 0x00;
}

/**************************************************
*函数名称:void ADC_ChannelConfig(ADC_Channel_TypeDef ADC_Channel, FunctionalState NewState)
*函数功能:ADC输入口配置函数
*入口参数:
ADC_Channel_TypeDef:ADC_Channel:ADC输入口选择
FunctionalState:NewState:ADCx使能/关闭选择
*出口参数:void
**************************************************/
void ADC_ChannelConfig(ADC_Channel_TypeDef ADC_Channel, FunctionalState NewState)
{
  uint16_t tmpreg;

  /* ADC采样通道选择外部通道，将对应的ADC输入口设置为模拟输入模式 */
  if(ADC_Channel < ADC_CHANNEL_VDD_D4)
  {
    tmpreg = (0x0001 << ADC_Channel);			//通过移位得到ADCCFG寄存器·配置值
    if(NewState == DISABLE)
    {
      /* ADC输入口退出模拟输入模式 */
      ADCCFG0 &= (~(uint8_t)tmpreg);
      ADCCFG1 &= (~(uint8_t)(tmpreg >> 8));
    }
    else
    {
      /* ADC输入口设置为模拟输入模式 */
      ADCCFG0 |= ((uint8_t)tmpreg);
      ADCCFG1 |= ((uint8_t)(tmpreg >> 8));
    }
  }

  /* 配置ADC采样时钟分频 */
  ADCCON = (ADCCON & 0XE0) | ADC_Channel;
}

/**************************************************
*函数名称:void ADC_EAINConfig(ADC_EAIN_TypeDef ADC_Channel, FunctionalState NewState)
*函数功能:将对应的ADC输入口设置为模拟输入模式
*入口参数:
ADC_EAIN_TypeDef:ADC_EAIN_Select:选择需要设置的ADC口（uint16_t作为入参，方便进行位或操作）
FunctionalState:NewState:ADC通道使能/关闭选择
*出口参数:void
**************************************************/
void ADC_EAINConfig(uint16_t ADC_EAIN_Select, FunctionalState NewState)
{
  if(NewState == DISABLE)
  {
    /* ADC输入口退出模拟输入模式 */
    ADCCFG0 &= (~(uint8_t)ADC_EAIN_Select);
    ADCCFG1 &= (~(uint8_t)(ADC_EAIN_Select >> 8));
  }
  else
  {
    /* ADC输入口设置为模拟输入模式 */
    ADCCFG0 |= ((uint8_t)ADC_EAIN_Select);
    ADCCFG1 |= ((uint8_t)(ADC_EAIN_Select >> 8));
  }
}


/*****************************************************
*函数名称:void ADC_VrefConfig(ADC_Vref_TypeDef ADC_Vref)
*函数功能:配置ADC的参考电压
*入口参数:
ADC_Vref_TypeDef:ADC_Vref:选择ADC参考电压
*出口参数:void
*****************************************************/
void ADC_VrefConfig(ADC_Vref_TypeDef ADC_Vref)
{
  OPINX = 0xC2;

  if(ADC_Vref == ADC_VREF_2_048V)
  {
    OPREG &= 0x3f;
    OPREG |= 0x40; //选择参考内部电压2.048V。
  }

  if(ADC_Vref == ADC_VREF_1_024V)
  {
    OPREG &= 0x3f;
    OPREG |= 0x80; //选择参考内部电压1.024V。
  }

  if(ADC_Vref == ADC_VREF_VDD)
  {
    OPREG &= 0x3f; //选择参考电压VDD。
  }
}


/*****************************************************
*函数名称:uint16_t ADC_GetConversionAverageValue(ADC_SamplesNum_TypeDef ADC_SamplesNum)
*函数功能:获得多次AD转换的平均数据
*入口参数:
ADC_SamplesNum_TypeDef:ADC_SamplesNum:AD转换次数
*出口参数:uint16_t
*****************************************************/
uint16_t ADC_GetConversionAverageValue(ADC_SamplesNum_TypeDef ADC_SamplesNum)
{
  uint8_t tmpCnt = 0;
  uint16_t tmpValueSum = 0, tmpValue = 0;
  uint16_t tmpValue_Max = 0, tmpValue_Min = 0xFFFF;
  bit tmpStaus = EADC;
  EADC = 0;

  for(tmpCnt = 0; tmpCnt < ADC_SamplesNum; tmpCnt ++)
  {
    ADC_StartConversion();			//开启一次ADC转换
    while(!ADC_GetFlagStatus());			//等待ADC转换结束
    ADC_ClearFlag();			//清除ADC转换标志位
    tmpValue = ADC_GetConversionValue();			//获取单次转换值

    /* 获取多次转换值中的最大值 */
    if(tmpValue > tmpValue_Max)
      tmpValue_Max = tmpValue;
    /* 获取多次转换值中的最小值 */
    if(tmpValue < tmpValue_Min)
      tmpValue_Min = tmpValue;

    tmpValueSum += tmpValue;//累加多次转换值的和
  }

  /* 通过硬件乘除法器来计算平均值 */
  {
    OPERCON |= 0X40;
    /* 被除数为16位数据 */
    tmpValueSum -= (tmpValue_Max + tmpValue_Min);
    EXA0 = tmpValueSum;
    EXA1 = tmpValueSum >> 8;
    EXBL = ADC_SamplesNum - 2;			//除数为8位数据

    OPERCON |= 0x80;				//开始除法计算
    while(OPERCON & 0x80);			//等待计算完毕

    //获取商
    tmpValue = (uint16_t)EXA0;
    tmpValue |= EXA1 << 8;
  }

  EADC = tmpStaus;			//恢复EADC
  return tmpValue;			//返回平均值
}

#endif

/*****************************************************
*函数名称:uint16_t ADC_GetConversionValue(void)
*函数功能:获得一次AD转换数据
*入口参数:void
*出口参数:uint16_t
*****************************************************/
uint16_t ADC_GetConversionValue(void)
{
  return ((ADCVH << 4) + (ADCVL >> 4));
}

/*****************************************************
*函数名称:void ADC_Cmd(FunctionalState NewState)
*函数功能:ADC功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
*****************************************************/
void ADC_Cmd(FunctionalState NewState)
{
  /* 使能/失能ADC功能 */
  if(NewState == DISABLE)
  {
    ADCCON &= 0X7F;
  }
  else
  {
    ADCCON |= 0x80;
  }
}

/******************* (C) C.OPYRIGHT 2022 SinOne Microelectronics *****END OF FILE****/
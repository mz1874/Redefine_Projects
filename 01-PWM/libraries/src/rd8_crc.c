//************************************************************
//  Copyright (c) 合肥市新定义电子有限公司
//	文件名称:			rd8_CRC.c
//	作者:					新定义应用团队
//	模块功能:			CRC固件库函数C文件
//  最后更正日期:	2022年6月8日
// 	版本:					V1.001
//  说明:该文件仅适用于RD8系列芯片
//*************************************************************

#include "rd8_CRC.h"
#include "intrins.H"

#if defined(RD8G36x) || defined(RD8G37x) || defined(RD8T36x) || defined(RD8T37x) || defined(RD8G05x) || defined(RD8T05x)
/**************************************************
*函数名称:unsigned long CRC_All()
*函数功能:求本工程HEX的CRC32校验值，该计算结果会根据OPTION的IAR Range不同而变化
*入口参数:void
*出口参数:
uint32_t:返回CRC计算结果
**************************************************/
uint32_t CRC_All()
{
  uint32_t CRC_Result;
  OPERCON |= 0x01;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  CRCINX = 0x00;

  {
    /* keil C51 数据存储为大端模式 */
    *((uint8_t*)&CRC_Result + 3) = CRCREG;

    *((uint8_t*)&CRC_Result + 2) = CRCREG;

    *((uint8_t*)&CRC_Result + 1) = CRCREG;

    *((uint8_t*)&CRC_Result) = CRCREG;
  }

  return CRC_Result;
}

/**************************************************
*函数名称:uint32_t CRC_Frame(uint8_t* buff,uint8_t Length)
*函数功能:求输入帧的CRC校验值
*入口参数:
uint8_t*:buff:传入需要进行CRC计算的数组
uint8_t:Length:传入需要计算的数组长度
*出口参数:
uint32_t:CRC计算结果
**************************************************/
uint32_t CRC_Frame(uint8_t* buff, uint8_t Length)
{
  uint8_t i;
  uint32_t CRC_Result = 0;

  EA = 0;
  OPERCON |= 0x02;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();

  for(i = 0; i < Length; i++)
  {
    CRC_Result = *(buff + i);
    CRCREG = CRC_Result;
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
  }

  CRCINX = 0x00;
  {
    /* keil C51 数据存储为大端模式 */
    *((uint8_t*)&CRC_Result + 3) = CRCREG;

    *((uint8_t*)&CRC_Result + 2) = CRCREG;

    *((uint8_t*)&CRC_Result + 1) = CRCREG;

    *((uint8_t*)&CRC_Result) = CRCREG;
  }
  EA = 1;

  return CRC_Result;
}

#endif

/******************* (C) COPYRIGHT 2022 RDS Microelectronics *****END OF FILE****/
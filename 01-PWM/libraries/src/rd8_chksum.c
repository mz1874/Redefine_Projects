//************************************************************
//  Copyright (c) 合肥市新定义电子有限公司
//	文件名称:			rd8_chksum.c
//	作者:					新定义应用团队
//	模块功能:			CHKSUN固件库函数C文件
//  最后更正日期:	2022年7月6日
// 	版本: 				V1.001
//  说明:
//*************************************************************

#include "rd8_chksum.h"

#if defined(RD8G403)
/**************************************************
*函数名称:void CHKSUM_DeInit(void)
*函数功能:CHKSUM相关寄存器复位至缺省值
*入口参数:void
*出口参数:void
**************************************************/
void CHKSUM_DeInit(void)
{
  OPERCON &= 0XFE;
  CHKSUML = 0X00;
  CHKSUMH = 0X00;
}

/**************************************************
*函数名称:void CHKSUM_StartOperation(void)
*函数功能:触发一次check sum计算
*入口参数:void
*出口参数:void
**************************************************/
void CHKSUM_StartOperation(void)
{
  OPERCON |= 0X01;

  while(OPERCON & 0x01);
}

/**************************************************
*函数名称:uint16_t CHKSUM_GetCheckValue(void)
*函数功能:获取一次check sum计算值
*入口参数:void
*出口参数:
uint16_t:check sum计算值
**************************************************/
uint16_t CHKSUM_GetCheckValue(void)
{
  uint16_t checktemp;
  checktemp = (uint16_t)(CHKSUMH << 8) +
              (uint16_t)CHKSUML;
  return checktemp;
}
#endif
/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/
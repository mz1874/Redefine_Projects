//************************************************************
//  Copyright (c) 合肥市新定义电子有限公司
//	文件名称: 		rd8_btm.h
//	作者: 				新定义应用团队
//	模块功能: 		BTM固件库函数H文件
//  最后更正日期: 2022年7月6日
// 	版本: 				V1.005
//  说明:该文件仅适用于RD8系列芯片
//*************************************************************

#ifndef _rd8_H
#define _rd8_H

#ifdef RD8G36x
  #include "RD8G36x_C.H"
#endif
#ifdef RD8G37x
  #include "RD8G37x_C.H"
#endif
#ifdef RD8T36x 
  #include "RD8T36x_C.H"
#endif
#ifdef RD8T37x
  #include "RD8T37x_C.H"
#endif
#ifdef RD8G05x
	#include "RD8G05x_C.H"
#endif
#ifdef RD8T05x
	#include "RD8T05x_C.H"
#endif
#ifdef RD8G403
	#include "RD8G403x_C.H"
#endif

#define enableInterrupts()    EA=1	 /** 开启总中断	 **/
#define disableInterrupts()   EA=0	 /** 关闭总中断	 **/

#define     __I     volatile const   /*!< defines 'read only' permissions     */
#define     __O     volatile         /*!< defines 'write only' permissions    */
#define     __IO    volatile         /*!< defines 'read / write' permissions  */

/*!< Signed integer types  */
typedef   signed char     int8_t;
typedef   signed short    int16_t;
typedef   signed long     int32_t;

/*!< Unsigned integer types  */
typedef unsigned char     uint8_t;
typedef unsigned short    uint16_t;
typedef unsigned long     uint32_t;

typedef int32_t  s32;
typedef int16_t  s16;
typedef int8_t   s8;

typedef uint32_t  u32;
typedef uint16_t  u16;
typedef uint8_t   u8;


typedef enum {FALSE = 0, TRUE = !FALSE} bool;

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus, BitStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

typedef enum {LOW = 0, HIGH = !LOW} PriorityStatus;

typedef enum 
{
  Status_ERROR		= 0x00U,
  Status_OK			= 0x01U,
  Status_BUSY		= 0x02U,
  Status_TIMEOUT	= 0x03U
} StatusTypeDef;

#define SET_BIT(SFR,BIT)				((SFR) |= (BIT))

#define CLEAR_BIT(SFR,BIT)			((SFR) &= ~(BIT))

#define READ_BIT(SFR, BIT)    	((SFR) & (BIT))

#define CLEAR_REG(SFR)        	((SFR) = (0x0))

#define WRITE_REG(SFR, VAL)   	((SFR) = (VAL))

#endif
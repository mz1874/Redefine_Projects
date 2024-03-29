/*--------------------------------------------------------------------------
RD8G403x_C.H

C Header file for RD8G403x microcontroller.
Copyright (c) 2022 Hefei Redefine electronic Co., Ltd.
All rights reserved.
合肥市新定义电子有限公司
版本号:  V1.0    
日期:  2022.05.30
--------------------------------------------------------------------------*/
#ifndef _RD8G403x_C_H_
#define _RD8G403x_C_H_

/* ------------------- 字节寄存器-------------------- */
/*CPU*/
sfr   ACC	  = 0xE0;		//累加器Ａ
sfr   B	      = 0xF0;		//通用寄存器B		
sfr   PSW	  = 0xD0;		//程序状态字		
sfr   DPH	  = 0x83;		//数据指针高8位		
sfr   DPL	  = 0x82;		//数据指针低8位		
sfr   SP	  = 0x81;		//堆栈指针	
		
/*system*/
sfr   PCON    = 0x87;		//电源管理控制寄存器

/*interrupt*/
sfr   IP1     = 0XB9;       //中断优先级控制寄存器1
sfr   IP	  = 0xB8;		//中断优先权控制寄存器
sfr   IE	  = 0xA8;		//中断控制寄存器
sfr   IE1     = 0XA9;  	    //中断控制寄存器1

/*PORT*/
sfr   P2PH	  = 0xA2;		//P2口模式控制寄存器		
sfr	  P2CON	  = 0xA1;		//P2口模式控制寄存器		
sfr   P2	  = 0xA0;		//P2口数据寄存器
sfr   P1PH    = 0x92;		//P1口模式控制寄存器		
sfr	  P1CON	  = 0x91;		//P1口模式控制寄存器	
sfr   P1	  = 0x90;		//P1口数据寄存器
sfr	  P0PH	  = 0x9B;		//P0口模式控制寄存器		
sfr	  P0CON	  = 0x9A;		//P0口模式控制寄存器		
sfr   P0	  = 0x80;		//P0口数据寄存器

/*TIMER*/
sfr   TMCON	  = 0x8E;		//定时器频率控制寄存器
sfr   TH1	  = 0x8D;		//定时器1高8位
sfr   TH0	  = 0x8C;		//定时器0高8位
sfr   TL1	  = 0x8B;		//定时器1低8位
sfr   TL0	  = 0x8A;		//定时器0低8位
sfr   TMOD	  = 0x89;		//定时器工作模式寄存器
sfr   TCON	  = 0x88;		//定时器控制寄存器
sfr   T2CON   = 0xC8;       //定时器2控制寄存器
sfr   T2MOD   = 0xC9; 	    //定时器2工作模式寄存器
sfr   RCAP2L  = 0xCA;       //定时器2重载/捕捉低8位
sfr   RCAP2H  = 0xCB;       //定时器2重载/捕捉高8位
sfr   TL2     = 0xCC;       //定时器2低8位
sfr   TH2     = 0xCD;       //定时器2高8位

/*ADC*/
sfr	  ADCCFG1 = 0xAA;		//ADC功能配置寄存器0
sfr	  ADCCFG0 = 0xAB;		//ADC功能配置寄存器1
sfr   ADCCON  = 0XAD;       //ADC控制寄存器
sfr   ADCVL	  = 0xAE;		//ADC 结果寄存器
sfr   ADCVH	  = 0xAF;		//ADC 结果寄存器

/*PWM*/
sfr   PWMCFG  = 0xD1;		//PWM设置寄存器
sfr   PWMCON0 = 0xD2;		//PWM控制寄存器
sfr   PWMPRD  = 0xD3;		//PWM周期设置寄存器
sfr   PWMDTYA = 0xD4;		//PWM占空比设置寄存器A
sfr   PWMDTY0 = 0xD5;		//PWM0设置寄存器
sfr   PWMDTY1 = 0xD6;		//PWM1设置寄存器
sfr   PWMDTY2 = 0xD7;		//PWM2设置寄存器
sfr   PWMCON1 = 0xDA;		//PWM控制寄存器
sfr   PWMDTYB = 0xDB;		//PWM占空比设置寄存器B
sfr   PWMDTY3 = 0xDC;		//PWM3设置寄存器
sfr   PWMDTY4 = 0xDD;		//PWM4设置寄存器
sfr   PWMDTY5 = 0xDE;		//PWM5设置寄存器
sfr   PWMDTY6 = 0xDF;		//PWM6设置寄存器

/*BTM*/
sfr	  BTMCON  = 0XCE;       //低频定时器控制寄存器

/*WatchDog*/
sfr   WDTCON  = 0xCF;		//WDT控制寄存器

/*INT*/
sfr   INT0F   = 0XBA; 	    //INT0 下降沿中断控制寄存器
sfr   INT0R   = 0XBB; 	    //INT0 上降沿中断控制寄存器
sfr   INT1F   = 0XBC; 	    //INT1 下降沿中断控制寄存器
sfr   INT1R   = 0XBD; 	    //INT1 上降沿中断控制寄存器
sfr   INT2F   = 0XC6; 	    //INT2 下降沿中断控制寄存器
sfr   INT2R   = 0XC7; 	    //INT2 上降沿中断控制寄存器

/*IAP */
sfr   IAPCTL  = 0xF6;		//IAP控制寄存器
sfr   IAPDAT  = 0xF5;		//IAP数据寄存器
sfr   IAPADE  = 0xF4;       //IAP扩展地址寄存器
sfr   IAPADH  = 0xF3;		//IAP写入地址高位寄存器
sfr   IAPADL  = 0xF2;		//IAP写入地址低8位寄存器
sfr   IAPKEY  = 0xF1;		//IAP保护寄存器

/*uart0*/
sfr   OTCON   = 0X8F;		//输出控制寄存器
sfr   SCON    = 0X98;       //uart控制寄存器
sfr   SBUF    = 0X99;       //uart0数据寄存器

/*三合一*/
sfr   SSCON0  = 0X9D;       //SSI控制寄存器0
sfr   SSCON1  = 0X9E;       //SSI控制寄存器1
sfr   SSCON2  = 0X95;       //SSI控制寄存器2
sfr   SSDAT   = 0X9F;       //SSI数据寄存器

sfr   OPINX   = 0XFE; 
sfr   OPREG   = 0XFF;

/*Check Sum*/
sfr   CHKSUML = 0XFC;       //Check Sum结果寄存器低位
sfr   CHKSUMH = 0XFD;	    //Check Sum结果寄存器高位

sfr   OPERCON = 0xEF;       //运算控制寄存器

///* ------------------- 位寄存器-------------------- */
/*PSW*/
sbit 	CY	  = PSW^7;	    //标志位		0:加法运算最高位无进位，或者减法运算最高位无借位时		1:加法运算最高位有进位，或者减法运算最高位有借位时
sbit 	AC	  = PSW^6;	    //进位辅助标志位	0:无借位、进位		1:加法运算时在bit3位有进位，或减法运算在bit3位有借位时
sbit 	F0	  = PSW^5;	    //用户标志位
sbit 	RS1	  = PSW^4;	    //工作寄存器组选择位
sbit 	RS0	  = PSW^3;	    //工作寄存器组选择位
sbit 	OV	  = PSW^2;	    //溢出标志位
sbit 	F1	  = PSW^1;	    //F1标志
sbit 	P	  = PSW^0;	    //奇偶标志位		0:ACC中1的个数为偶数（包括0个）		1:ACC中1的个数为奇数

/*T2CON*/
sbit  TF2     = T2CON^7;
sbit  EXF2	  = T2CON^6;
sbit  RCLK    = T2CON^5;
sbit  TCLK	  = T2CON^4;
sbit  EXEN2	  = T2CON^3;
sbit  TR2	  = T2CON^2;
sbit  T2      = T2CON^1;
sbit  CP	  = T2CON^0;


/*IP*/
sbit 	IPADC	= IP^6;	  //ADC中断优先控制位      0:设定 ADC的中断优先权是 “低”		1:设定 ADC的中断优先权是 “高”
sbit	IPT2	= IP^5;	  //Timer2中断优先控制位   0:设定 Timer2的中断优先权是 “低”		1:设定Timer2的中断优先权是 “高”
sbit 	IPUART	= IP^4;	  //UART中断优先控制位	   0:设定 UART的中断优先权是 “低”		1:设定UART的中断优先权是 “高”
sbit 	IPT1	= IP^3;	  //Timer1中断优先控制位   0:设定 Timer 1的中断优先权是 “低”	1:设定 Timer 1的中断优先权是 “高”		   
sbit    IPINT1  = IP^2;	  //INT1中断优先控制位     0:设定 INT1中断优先权是 “低”		    1:设定INT1的中断优先权是 “高”
sbit 	IPT0	= IP^1;	  //Timer0中断优先控制位   0:设定 Timer 0的中断优先权是 “低”	1:设定 Timer 0的中断优先权是 “高”
sbit	IPINT0	= IP^0;   //INT0中断优先控制位	   0:设定 INT0中断优先权是 “低”		    1:设定INT0的中断优先权是 “高”

/*IE*/
sbit 	EA	    = IE^7;	  //中断使能的总控制	0:关闭所有的中断	1:打开所有的中断
sbit 	EADC    = IE^6;	  //ADC中断使能控制	    0:关闭ADC中断		1:打开ADC中断
sbit 	ET2     = IE^5;	  //Timer2中断使能控制	0:关闭Timer2中断    1:打开Timer2中断
sbit	EUART   = IE^4;	  //UART中断使能控制	0:关闭UART中断		1:打开UART中断
sbit 	ET1     = IE^3;	  //Timer1中断使能控制	0:关闭TIMER1中断	1:打开TIMER1中断
sbit    EINT1   = IE^2;	  //INT1中断使能控制	0:关闭INT1中断      1:打开INT1中断
sbit 	ET0	    = IE^1;	  //Timer0中断使能控制	0:关闭TIMER0中断	1:打开TIMER0中断
sbit	EINT0   = IE^0;	  //INT0中断使能控制	0:关闭INT0中断      1:打开INT0中断

/*TCON*/
sbit  TF1	  = TCON^7;	    //T1溢出中断请求标志位	T1产生溢出，发生中断时，硬件将TF1置为“1”，申请中断，CPU响应时，硬件清“0”。
sbit  TR1	  = TCON^6;	    //定时器T1的运行控制位	0:Timer1禁止计数		1:Timer1开始计数
sbit  TF0	  = TCON^5;	    //T0溢出中断请求标志位	T0产生溢出，发生中断时，硬件将TF0置为“1”，申请中断，CPU响应时，硬件清“0”。
sbit  TR0	  = TCON^4;	    //定时器T0的运行控制位	0:Timer0禁止计数		1:Timer0开始计数

/*SCON*/
sbit  SM0	  = SCON^7;
sbit  SM1	  = SCON^6;
sbit  SM2	  = SCON^5;
sbit  REN	  = SCON^4;
sbit  TB8	  = SCON^3;
sbit  RB8	  = SCON^2;
sbit  TI	  = SCON^1;
sbit  RI	  = SCON^0;

/* P0 */
sbit  P01	  = P0^1;
sbit  P00	  = P0^0;

/* P1 */
sbit  P17	  = P1^7;
sbit  P16	  = P1^6;
sbit  P15	  = P1^5;
sbit  P14	  = P1^4;
sbit  P13	  = P1^3;
sbit  P12	  = P1^2;
sbit  P11	  = P1^1;
sbit  P10	  = P1^0;

/* P2 */
sbit  P27	  = P2^7;
sbit  P26	  = P2^6;
sbit  P25	  = P2^5;
sbit  P24	  = P2^4;
sbit  P23	  = P2^3;
sbit  P22	  = P2^2;
sbit  P21	  = P2^1;
sbit  P20	  = P2^0;

#endif
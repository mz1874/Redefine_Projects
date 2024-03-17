#include "rd8_gpio.h"
#include "rd8_pwm.h"

void SC_PWM0_Init(void)
{
	PWM_Init(PWM0_PRESSEL_FHRC_D1, 3200);
	 /*PWM0*/
	PWM_Aligned_Mode_Select(PWM0_Edge_Aligned_Mode);
  /*PWM00 ����ģʽ*/
	PWM_ComplementaryModeConfigEX(PWM00, 1600, PWM_OUTPUTSTATE_ENABLE);
	PWM_PolarityConfig(PWM01,PWM_POLARITY_INVERT);
	//��������ʱ��
	PWM_DeadTimeConfig(0X00,0X0f);
	PWM_ComplementaryModeConfigEX(PWM01, 1600, PWM_OUTPUTSTATE_ENABLE);
	
  /*PWM0����*/
	PWM_CmdEX(PWM0_Type, ENABLE);
}

void Delay(unsigned int time)
{
	unsigned int Single_Time;
	while(time--)
	{
		Single_Time = 4095;
		while(Single_Time --);
	}
}
  
void main(void)
{
	SC_PWM0_Init();

	while(1)
	{
	
	};
}


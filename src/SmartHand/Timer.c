/********************************************************************
created:	2011/12/28
created:	28:12:2011   18:55
filename: 	C:\Users\zhaoyiming\Desktop\�������\temp.cpp
file path:	C:\Users\zhaoyiming\Desktop\�������
file base:	temp
file ext:	cpp
author:		��һ��


purpose:	ʱ����ص�Ӳ������
*********************************************************************/
#include "config.h"


u8 CPUFrequene; 
/***************************��ʱ����*******************************/
/*******************************************
�������ƣ�delay_Nus
��    �ܣ���ʱN��us��ʱ��
��    ����n--��ʱ����
����ֵ  ����
ע�⣺��ʱ��һ��׼ȷ������Ϊһ����ʱʹ��
********************************************/
void delay_us(unsigned int n)
{

	while(n>0)
	{
		n--;   
	}
} 
/*******************************************
�������ƣ�delay_1ms
��    �ܣ���ʱԼ1ms��ʱ��
��    ������
����ֵ  ����
********************************************/
void delay_1ms(void)
{
	unsigned int i=40*CPUFrequene;;
	while(i>0)
	{
		delay_us(1);
		i--;
	}
}  
/*******************************************
�������ƣ�delay_Nms
��    �ܣ�Ӳ����ʱ2.5��ms��ʱ��
��    ������
����ֵ  ����
********************************************/  
void HardDelay2Ms()
{
	TA0CCR0 = 2000*CPUFrequene;
	__bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt

}






/*******************************************
�������ƣ�delay_Nms
��    �ܣ���ʱN��ms��ʱ��
��    ������
����ֵ  ����
********************************************/  
void delay_ms(unsigned int n)
{

	if(n<3)  //��ʱС��2ms,���������ʱ
	{
		unsigned int i = 0;

		for(i = n;i > 0;i--)
			delay_1ms();
	}
	else
	{
		while(n>3)
		{
			HardDelay2Ms();
			n-=2;
		}
	}


}
/*******************************************
�������ƣ�SetCPUSpeed
��    �ܣ�����CPU�ٶ�
��    ������Ϊ16,8,1, ����λMHZ��
����ֵ  ����
********************************************/  
void SetCPUSpeed(u8 FreNum)
{
	switch(FreNum)
	{
	case 8:
		if (CALBC1_8MHZ ==0xFF || CALDCO_8MHZ == 0xFF)                                     
		{  
			while(1);                               // If calibration constants erased                             // do not load, trap CPU!!
		}   
		BCSCTL1 = CALBC1_8MHZ;                    // Set DCO to 8MHz
		DCOCTL = CALDCO_8MHZ;
		CPUFrequene=FreNum;
		break;
	case 16:
		if (CALBC1_16MHZ ==0xFF || CALDCO_16MHZ == 0xFF)                                     
		{  
			while(1);                               // If calibration constants erased                             // do not load, trap CPU!!
		}   
		BCSCTL1 = CALBC1_16MHZ;                    // Set DCO to 8MHz
		DCOCTL = CALDCO_16MHZ;
		CPUFrequene=FreNum;
		break;
	case 1:
		if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ == 0xFF)                                     
		{  
			while(1);                               // If calibration constants erased                             // do not load, trap CPU!!
		}   
		BCSCTL1 = CALBC1_1MHZ;                    // Set DCO to 8MHz
		DCOCTL = CALDCO_1MHZ;
		CPUFrequene=FreNum;
		break;
	}
}
void TimerInit()
{
	TA0CTL = TASSEL_2 + MC_2;                  // SMCLK, contmode
	
	TA0CCTL0 = CCIE;                           // TA0CCR0 interrupt enabled
	TA0CCR0 = 2000*CPUFrequene;
}
//��ʱ��������
u16 TimerCounter=0;

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0 (void)
{

	LPM0_EXIT;

	
	TimerCounter++;


}


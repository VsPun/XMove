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
	unsigned int i;
	for(i = 1000;i > 0;i--)	; delay_us(1);
}  
/*******************************************
�������ƣ�delay_Nms
��    �ܣ���ʱN��ms��ʱ��
��    ������
����ֵ  ����
********************************************/  
void delay_ms(unsigned int n)
{
	unsigned int i = 0;

	for(i = n;i > 0;i--)
		delay_1ms();
}
/*******************************************
�������ƣ�SetCPUSpeed
��    �ܣ�����CPU�ٶ�
��    ������Ϊ16,8,1, ����λMHZ��
����ֵ  ����
********************************************/  
void SetCPUSpeed(u8 FreNum)
{
  DCOCTL = DCO0 + DCO1 + DCO2;              // Max DCO
	BCSCTL1 = RSEL0 + RSEL1 + RSEL2;          // XT2on, max RSEL
	BCSCTL2 |= SELS;                          // SMCLK = XT2     
  

}
void TimerInit()
{
  
  CCTL0 = CCIE;                             // CCR0 interrupt enabled
  CCR0 = 6400;
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, contmode
}
	
//��ʱ��������
u16 TimerCounter=0;


// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
 
  TimerCounter++;                    // Toggle P1.0
  LPM0_EXIT;
}


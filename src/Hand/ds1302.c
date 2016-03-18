
#include "config.h"
/*
config.h
ELPOS2.0��ʵʱʱ����������������:DS1302
Copyright (c) 2010����һ��
buptzym@bupt.edu.cn
All rights reserved.
���������ѧϰ�ο������ṩ�κοɿ��Է���ĵ���������������ҵĿ��
*/


/***************DS1302�궨��*********************/
#define DS_RST  BIT7        //DS_RST = P2.7 
#define DS_SCL  BIT3        //DS_SCL = P3.3 
#define DS_SDA  BIT6        //DS_SDA = P2.6
#define DS_RST_IN P2DIR &= ~DS_RST
#define DS_RST_OUT P2DIR |= DS_RST
#define DS_RST0 P2OUT &= ~DS_RST
#define DS_RST1 P2OUT |= DS_RST
#define DS_SCL_IN P3DIR &= ~DS_SCL
#define DS_SCL_OUT P3DIR |= DS_SCL
#define DS_SCL0 P3OUT &= ~DS_SCL
#define DS_SCL1 P3OUT |= DS_SCL
#define DS_SDA_IN P2DIR &= ~DS_SDA
#define DS_SDA_OUT P2DIR |= DS_SDA
#define DS_SDA0 P2OUT &= ~DS_SDA
#define DS_SDA1 P2OUT |= DS_SDA
#define DS_SDA_BIT P2IN & DS_SDA
/************ϵͳ���Ķ���******************/



/*******************************************
�������ƣ�Reset_DS1302
��    �ܣ���DS1302���и�λ����
��    ������
����ֵ  ����
********************************************/
void Reset_DS1302(void)
{
	DS_RST_OUT;  //RST��Ӧ��IO����Ϊ���״̬
	DS_SCL_OUT;  //SCLK��Ӧ��IO����Ϊ���״̬
	DS_SCL0;     //SCLK=0
	DS_RST0;     //RST=0
	delay_us(100);
	DS_SCL1;    //SCLK=1
}
/*******************************************
�������ƣ�Write1Byte
��    �ܣ���DS1302д��1���ֽڵ�����
��    ����wdata--д�������
����ֵ  ����
********************************************/
void Write1Byte(uchar wdata) 
{ 
	uchar i;

	DS_SDA_OUT;     //SDA��Ӧ��IO����Ϊ���״̬
	DS_RST1;        //REST=1;

	for(i = 8; i > 0; i--) 
	{
		if(wdata&0x01)  DS_SDA1;
		else            DS_SDA0;
		DS_SCL0;
		delay_us(10); 
		DS_SCL1;
		delay_us(10); 
		wdata >>= 1; 
	} 
}
/*******************************************
�������ƣ�Read1Byte
��    �ܣ���DS1302����1���ֽڵ�����
��    ������
����ֵ  ��������һ���ֽ�����
********************************************/
uchar Read1Byte(void) 
{ 
	uchar i;
	uchar rdata = 0X00;

	DS_SDA_IN;  //SDA��Ӧ��IO����Ϊ����״̬
	DS_RST1;    //REST=1;

	for(i = 8; i > 0; i--)
	{
		DS_SCL1;
		delay_us(10);
		DS_SCL0;
		delay_us(10);
		rdata >>= 1;
		if(DS_SDA_BIT)  rdata |= 0x80;
	} 

	return(rdata); 
}
/*******************************************
�������ƣ�W_Data
��    �ܣ���ĳ���Ĵ���д��һ���ֽ�����
��    ����addr--�Ĵ�����ַ
wdata--д�������
����ֵ  ����
********************************************/
void W_Data(uchar addr, uchar wdata)
{
	DS_RST0; 
	DS_SCL0;   
	_NOP();
	DS_RST1;
	Write1Byte(addr);   //д���ַ
	Write1Byte(wdata);  //д������
	DS_SCL1;
	DS_RST0;
} 
/*******************************************
�������ƣ�R_Data
��    �ܣ���ĳ���Ĵ�������һ���ֽ�����
��    ����addr--�Ĵ�����ַ
����ֵ  ������������
********************************************/
uchar R_Data(uchar addr)
{
	uchar rdata;

	DS_RST0; 
	DS_SCL0; 
	_NOP();
	DS_RST1;
	Write1Byte(addr);    //д���ַ
	rdata = Read1Byte();  //�������� 
	DS_SCL1;
	DS_RST0;

	return(rdata);
}

/*******************************************
�������ƣ�Set_DS1302
��    �ܣ�����DS1302�ڲ���ʱ��
��    ����ptr--ָ�������ݵ�ַ��ָ��
����ֵ  ����
˵��    ��д�����ݵĸ�ʽ��
�� �� ʱ �� �� ���� ��  ����7���ֽڡ�
********************************************/
void Set_DS1302(uchar *ptr) 
{
	uchar i;
	uchar addr = 0x80; 

	W_Data(0x8e,0x00);    //����д��

	for(i = 7;i > 0;i--)
	{ 
		W_Data(addr,*ptr++); 
		addr += 2;
	}
	W_Data(0x8e,0x80);      //��ֹ
}
/******************************************************************** 
*
* ����: Get_DS1302
* ˵��: 
* ����: ��ȡDS1302��ǰʱ��
* ����: R_Data(uchar addr) 
* ����: ucCurtime: ���浱ǰʱ���ַ����ǰʱ���ʽΪ: �� �� ʱ �� �� ���� �� 
* 7Byte (BCD��) 1B 1B 1B 1B 1B 1B 1B
* ����ֵ: ��
***********************************************************************/
/*******************************************
�������ƣ�Get_DS1302
��    �ܣ���ȡDS1302�ڲ���ʱ��
��    ����ptr--ָ�����ݴ�ŵ�ַ��ָ��
����ֵ  ����
˵��    ���������ݵĸ�ʽ��
�� �� ʱ �� �� ���� ��  ����7���ֽڡ�
********************************************/
void Get_DS1302(uchar *ptr) 
{
	uchar i;
	uchar addr = 0x81;

	for(i = 0;i < 7;i++)
	{
		ptr[i] = R_Data(addr);
		addr += 2;
	}
}

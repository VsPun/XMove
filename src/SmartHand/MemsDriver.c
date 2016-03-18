#include "config.h"
/*
MemsDriver.c
ELPOS2.0��MEMS�����������������ϲ����ã�����ADXL345,ITG3200,BMP085��HMC5883
Copyright (c) 2010����һ��
buptzym@bupt.edu.cn
All rights reserved.
���������ѧϰ�ο������ṩ�κοɿ��Է���ĵ���������������ҵĿ��
*/



#define L3G4200D 0
#define  HMC5883L 1
#define  ADXL345 2


#define L3G4200D_I2C_ADDR   0X68
#define  HMC5883L_I2C_ADDR  0X1E
#define  ADXL345_I2C_ADDR  0X53


//��ADXL345�ڲ��ļĴ�����ַ
#define ADXL345_BW_RATE   0X2C
#define ADXL345_POWER_CTL  0X2D
#define ADXL345_DATA_FORMAT 0X31
#define ADXL345_THRESH_TAP  0X1D
#define ADXL345_DUR 0X21
#define ADXL345_Latent 0x22
#define ADXL345_Window 0x23
#define ADXL345_THRESH_ACT  0X24
#define ADXL345_THRESH_INACT  0X25
#define ADXL345_TIME_INACT  0X26
#define ADXL345_INACT_CTL  0X27
#define ADXL345_THRESH_FF  0X28
#define ADXL345_TIME_FF  0X29
#define ADXL345_TAP_AXES 0X2A
#define ADXL345_ACT_TAP_STATUS 0X2B
#define ADXL345_INT_ENABLE 0X2E
#define ADXL345_INT_MAP 0X2F
#define ADXL345_INT_SOURCE 0X30


//����HMC5883L�ڲ��Ĵ�����ַ���ӵ�ַ��
#define HMC5883L_CfgA  0X00
#define HMC5883L_CfgB   0X01
#define HMC5883L_Mode 0X02
#define HMC5883L_XMSB  0X03
#define HMC5883L_XLSB  0X04
#define HMC5883L_YMSB  0X05
#define HMC5883L_YLSB  0X06
#define HMC5883L_ZMSB   0X07
#define HMC5883L_ZLSB    0X08
#define HMC5883L_StaReg 0x09


struct str_TWI         					//TWI���ݽṹ
{
	volatile u8 STATUS;    	   //TWI_����״̬
	u8  R_W;
	u8  SLA;      					//���豸��������ַ
	u16 ADDR;      					//���豸�����ݵ�ַ
	u8  DUB_OR_SIN;               //���豸���ݵ�ַ���ֽ���
	u8 *pBUF;      					//���ݻ�����ָ��
	u8 DATALEN;     				//���ݳ���
	u8 STATE;      					//TWI��д��������
	u8 FAILCNT;     					//ʧ�����Դ���
}strTWI;
/**********************************************************
�������ƣ�I2C��д���ֽڳ���												
�������ڣ���																
������ڣ�R_W  --0д������1������											
sla  --������ַ																												
addr --�����ӵ�ַ	
dub_sin --�����ӵ�ַ�ֽ�����0Ϊ���ֽڣ�1Ϊ˫�ֽ�
*ptr --��д���ݻ�����												
len  -- ��д���ݳ���		
��ע��I2C������Щ���������ӵ�ַ�����ֽڣ��е���һ���ֽڣ�����
�������ӵ�ַʱ��ע�⡣
***********************************************************/
u8 TWI_RW(u8 R_W,u8 sla,u16 addr,u8 dub_sin,u8 *ptr,u8 len)
{
	u8 i;

	//i=(addr>>8)<<1;
	//i&=0x06;         //������24C04/08��EEPROM��ַ��λ����SLA����
	strTWI.R_W        = R_W;
	strTWI.SLA        = sla;//+i;
	strTWI.ADDR       = addr;
	strTWI.DUB_OR_SIN = dub_sin;
	strTWI.pBUF       = ptr;
	strTWI.DATALEN    = len;
	strTWI.STATE      = 0;
	strTWI.FAILCNT    = 0;

	UCB0I2CSA      = strTWI.SLA;
	if(0 == strTWI.R_W)                           //д����
	{
		while(UCB0CTL1 & UCTXSTP);                //�����Ƿ����
		UCB0CTL1  |= UCTXSTT + UCTR;              //����I2C������

		if(1 == strTWI.DUB_OR_SIN)             //��������ַ�Ƿ�Ϊ˫�ֽ�
		{
			UCB0TXBUF  = (u8)(strTWI.ADDR>>8);  //���������ӵ�ַ��8λ
			while(!(IFG2 & UCB0TXIFG))             //�ж��Ƿ������ 
			{
				if((UCB0STAT & UCNACKIFG) == 1)    //���豸��Ӧ���򷵻�
					return 1;
			}
			UCB0TXBUF  = (u8)strTWI.ADDR;       //���������ӵ�ַ��8λ 
			while(!(IFG2 & UCB0TXIFG))
			{
				if((UCB0STAT & UCNACKIFG) == 1)     //���豸��Ӧ���򷵻�
					return 1;
			} 
		}
		else   
		{
			UCB0TXBUF  = (u8)strTWI.ADDR;       //���ֽڷ��������ӵ�ַ 
			 while(!(IFG2 & UCB0TXIFG))   
			{
				if((UCB0STAT & UCNACKIFG) == 1)      //���豸��Ӧ���򷵻�
					return 1;
			} 
		}

		for(i=0; i<strTWI.DATALEN; i++)            //��������
		{
			UCB0TXBUF = *strTWI.pBUF++;
			while((IFG2 & UCB0TXIFG) == 0)
			{
				if((UCB0STAT & UCNACKIFG) == 1)     //���豸��Ӧ���򷵻�
					return 1;
			}
		}
		UCB0CTL1 |= UCTXSTP;                       //����ֹͣλ
		while(UCB0CTL1 & UCTXSTP);                 //�����Ƿ����
	}
	else if(1 == strTWI.R_W)                       //������
	{
		while(UCB0CTL1 & UCTXSTP);                 //�����Ƿ����
		UCB0CTL1  |= UCTXSTT + UCTR;               //����I2C������ 

		if(1 == strTWI.DUB_OR_SIN)              //��������ַ�Ƿ�Ϊ˫�ֽ�
		{
			UCB0TXBUF  = (u8)(strTWI.ADDR>>8); //���������ӵ�ַ��8λ
			while((IFG2 & UCB0TXIFG) == 0)        //�ж��Ƿ������ 
			{
				if((UCB0STAT & UCNACKIFG) == 1)  //���豸��Ӧ���򷵻�
					return 1;
			}
			UCB0TXBUF  = (u8)strTWI.ADDR;      //���������ӵ�ַ��8λ 
			while((IFG2 & UCB0TXIFG) == 0)
			{
				if((UCB0STAT & UCNACKIFG) == 1)  //���豸��Ӧ���򷵻�
					return 1;
			}
		}
		else
		{
			UCB0TXBUF  = (u8)strTWI.ADDR;      //���ֽڷ��������ӵ�ַ
			while((IFG2 & UCB0TXIFG) == 0)
			{
				if((UCB0STAT & UCNACKIFG) == 1)  //���豸��Ӧ���򷵻�
					return 1;
			}
		}
		UCB0CTL1  &= ~UCTR;                        //ȷ��Ϊ���� 
		//while (UCB0CTL1 & UCTXSTP);               //�ж������Ƿ��ͷ� 
		UCB0CTL1  |= UCTXSTT;                      //���·�����ʼλ 
		//while((UCB0CTL1 & UCTXSTT) == 1);         //�ж���ʼλ�Ƿ��ͳɹ� 

	}
	delay_ms(4);
	return 0;
}
/*********************************************************
�������ƣ�I2C_Init()
�������ܣ�I2C��ʼ��
��ڲ�������
���ڲ�������
��ע��
**********************************************************/
void I2C_Init(void)
{

	P3SEL |= BIT1 + BIT2;                     //P3.2(SCK),P3.1(SDA)
	UCB0CTL1 |= UCSWRST;                      //Ready for configurating I2C register  
	UCB0CTL0 |= UCMST+UCMODE_3 +UCSYNC;    //I2C�� ������ͬ��ģʽ
	//================= Starting Of I2C FUNCTION CONFIGURATION========================//

	UCB0CTL1 = UCSSEL_2 + UCSWRST;            //ʱ��ԴACLK
	UCB0BR0  =40;                          //100KHz��16MHz
	UCB0BR1  = 0;
	UCB0CTL1 &= ~UCSWRST;
	IE2      |= UCB0RXIE;                     //ʹ�ܽ����ж�
	//================= End Of I2C FUNCTION CONFIGURATION========================// 

}


/*********************************************************
�������ƣ�USCIAB0_ISR()
�������ܣ�I2C�����ж�
��ڲ�������
���ڲ�������
��ע��
**********************************************************/
#pragma vector=USCIAB0TX_VECTOR 
__interrupt void USCIAB0_ISR(void) 
{ 
	if(IFG2  & UCB0RXIFG)                       // �����ж� 
	{ 
		//Sendbyte(UCB0RXBUF);
		if(strTWI.DATALEN > 1)
		{
			*strTWI.pBUF++ = UCB0RXBUF;
		}
		else if(1 == strTWI.DATALEN)
		{

			*strTWI.pBUF++ = UCB0RXBUF;
			UCB0CTL1 |= UCTXSTP + UCTXNACK;        // ����ֹͣλ��NACKλ

		}
		--strTWI.DATALEN;                         // �������ݳ����Լ�          
	} 
}


//***************Ӧ�ò�ӿں���***********************************/
/*
������MEMS_WriteReg()
���ܣ��򴫸�����ĳ���ڲ��Ĵ���д������
������
ICID������������ID
dat��Ҫд�������
RegAddr�������ڲ��Ĵ�����ַ
���أ�
0������
1�����ʴ�����ʱ�����쳣
*/
unsigned char MEMS_WriteReg(unsigned char ICID,unsigned char RegAddr, unsigned char dat)
{
	unsigned char  b;
	switch(ICID)
	{
	case L3G4200D:
		b=   TWI_RW(0,L3G4200D_I2C_ADDR,RegAddr,0,&dat,1);		
		break;
	case HMC5883L:
		b=   TWI_RW(0,HMC5883L_I2C_ADDR,RegAddr,0,&dat,1);	
		break;

	case ADXL345:
		b=   TWI_RW(0,ADXL345_I2C_ADDR,RegAddr,0,&dat,1);	
		break;

	}
	return b;
}

/*
������MEMS_ReadReg()
���ܣ��򴫸�����ĳ���ڲ��Ĵ�����������
������
ICID������������ID
dat��Ҫд�������
RegAddr�������ڲ��Ĵ�����ַ
���أ�
0������
1�����ʴ�����ʱ�����쳣
*/
unsigned char  MEMS_ReadReg(unsigned char ICID,unsigned char RegAddr, unsigned char *dat)
{
	unsigned char b;
	switch(ICID)
	{
	case L3G4200D:
		b=   TWI_RW(1,L3G4200D_I2C_ADDR,RegAddr,0,dat,1);	
		break;
	case HMC5883L:
		b=   TWI_RW(1,HMC5883L_I2C_ADDR,RegAddr,0,dat,1);	
		break;

	case ADXL345:
		b=   TWI_RW(1,ADXL345_I2C_ADDR,RegAddr,0,dat,1);	
		break;

	}
	return b;
}




//***********************************�ӿ�ת������**************/



//====================================================
//�������������� ��L3G4200D��
//====================================================

/*
������u8 L3G4200DReadData()
���ܣ���ȡ�����ǵ�����
��������
���أ�1  
ע�⣺�洢λ����myMEMSData��ƫ����L3G4200DDF
*/
u8 L3G4200DReadData()
{
	for (u8 i=0;i<6;i++)
	{
		MEMS_ReadReg(L3G4200D,29+i,myMEMSData+L3G4200DDF+i);
	}


	return 1;

}
/*
������u8 L3G4200DSleepActiveChange(u8 Type)
���ܣ������ǵ����ߺ͹����л�����
������TYPE 0������״̬ 1������״̬
���أ�1  
ע�⣺
*/

void L3G4200DInit()
{
	while(MEMS_WriteReg(L3G4200D,0x16,0x07));  //125HZ������	
}

u8 L3G4200DPowerMGR(u8 Mode)
{
    u8 Data,Data2;
     while(MEMS_ReadReg(L3G4200D,0x16,&Data));
	while(MEMS_ReadReg(L3G4200D,0x3E,&Data2));
	if (Mode==1)  //����״̬
	{
		setbit(Data,6);
		clrbit(Data2,6);
	}
	else
	{
		clrbit(Data,6);
		setbit(Data2,6);


	}
	while(MEMS_WriteReg(L3G4200D,0x16,Data));
	while(MEMS_WriteReg(L3G4200D,0x3E,Data2));
	return 1;
}
                    
/*
������float L3G4200DDataProcess(u8 D1,u8 D2)  //d1��λ��D2��λ
���ܣ������ǵ����ݴ���ӿں���
������D1:���ݸ�λ��D2�����ݵ�λ
���أ���õĸ���ֵ
ע�⣺
*/
float L3G4200DDataProcess(u8 D1,u8 D2)  //d1��λ��D2��λ
{
	unsigned int temp=D1;
	temp=temp<<8;
	temp+=D2;
	signed int temp2=(signed int)temp;
	return (float)(temp2)*0.061;



}
/*
������u8 L3G4200DShowData(float* x,float* y,float* z)
���ܣ������ǵ����ݻ�ú���
������float* x,float* y,float* z�ֱ�洢��ǰ��X,Y��Z������ٶ�
���أ�1
ע�⣺
*/
u8 L3G4200DShowData()
{

	GyroX=L3G4200DDataProcess(myMEMSData[L3G4200DDF],myMEMSData[L3G4200DDF+1]);
	GyroY=L3G4200DDataProcess(myMEMSData[L3G4200DDF+2],myMEMSData[L3G4200DDF+3]);
	GyroZ=L3G4200DDataProcess(myMEMSData[L3G4200DDF+4],myMEMSData[L3G4200DDF+5]);
	return 1;
}



//====================================================
//���ٶȴ���������������ADXL345��
//====================================================

/*
������u8 ADXL345Init(u8 Mode) 
���ܣ���ʼ�����ٶȼƵ���������״̬
������Mode������״̬0-3 2G,4G,8G,16G?
���أ�1
ע��:
*/

u8 ADXL345Init(u8 Mode)    //����ģʽ�µĳ�ʼ������
{
	//mode��ʾ��ǰ�Ĺ���״̬��0-3 2G,4G,8G,16G?
	while(MEMS_WriteReg(ADXL345,ADXL345_BW_RATE,0X0A));  //��������ģʽ��100HZ���
	while(MEMS_WriteReg(ADXL345,ADXL345_POWER_CTL,0x28));
	while(MEMS_WriteReg(ADXL345,ADXL345_DATA_FORMAT,0x20+Mode));
	return 1;
}


/*
������u8 ADXL345Init(u8 Mode) 
���ܣ���ʼ�����ٶȼƵ��ж�����״̬
������Mode����
���أ�1
ע��:����ϸ������ڲ�����ע��
*/
u8 ADXL345IntConfig()
{
	//while (MEMS_WriteReg(ADXL345,ADXL345_THRESH_TAP,20));    //�û���ֵ���62.5mg*20
	//while (MEMS_WriteReg(ADXL345,ADXL345_DUR,3));      //������ֵ�����ʱ��625us��λ
	//while (MEMS_WriteReg(ADXL345,ADXL345_Latent,20));      //�����Ĵ��ʱ��� 1.25mg��λ
	//while (MEMS_WriteReg(ADXL345,ADXL345_Window,80));      //�ڶ����Ĵ�ĵ�ʱ�䴰1.25mg
	while (MEMS_WriteReg(ADXL345,ADXL345_THRESH_ACT,80));      //��⵽�״̬����ֵ1.25mg
	while (MEMS_WriteReg(ADXL345,ADXL345_THRESH_INACT,20));      //��⵽���״̬����ֵ1.25mg
	while (MEMS_WriteReg(ADXL345,ADXL345_TIME_INACT,2));     //��⵽���˶���ʱ��2.0s
	while (MEMS_WriteReg(ADXL345,ADXL345_INACT_CTL,0x17));    //�˶��Ͳ��˶��������00010111
	//while (MEMS_WriteReg(ADXL345,ADXL345_TAP_AXES,0x07));    //�Ĵ��⣬��X,Y,Z�ᶼ��Ч
	while (MEMS_WriteReg(ADXL345,ADXL345_INT_ENABLE,0x18));   //�жϼ�⣬������˫����������Ǽ���ȫ������01111000  0x78    ��ǰֻ��������ͷǼ����ж�
	while (MEMS_WriteReg(ADXL345,ADXL345_INT_MAP,0x18));  //����ܽ��趨,��˫����1pin,����ͷǼ�����2pin  00011000
	return 1;
}
/*
������u8 ADXL345DataRevise()  
���ܣ����ٶȼƵ���������
��������
���أ�1
ע��:����ϸ������ڲ�����ע��
*/
u8 ADXL345DataRevise()  //����У������
{
	MEMS_WriteReg(ADXL345,0X1F,0X02);  
	//YУ��
	MEMS_WriteReg(ADXL345,0x1E,0X00);    //XУ��

	MEMS_WriteReg(ADXL345,0X20,0X00);  //ZУ��
	return 1;

}
/*
������u8 ADXL345ReadData()
���ܣ����ٶȼƵĶ�ȡ����
��������
���أ�1
ע��:���ݴ洢��myMEMSData[]��ƫ����ADXL345DF
*/
u8 ADXL345ReadData()
{

	for (u8 i=0;i<6;i++)
	{
		MEMS_ReadReg(ADXL345,0x32+i,myMEMSData+ADXL345DF+i);
	}

	return 1;
}
/*
������float ADXL345DataProcess(u8 D1,u8 D2,u8 Config)
���ܣ����ٶȼƵ�����ת������
������D1,D2���ߵ�λ ,���ݴ��ҵ���config������ģʽ���μ�ADXL345Init��mode ����
���أ�1
ע��:���ݴ洢��myMEMSData[]��ƫ����ADXL345DF
*/
float ADXL345DataProcess(u8 D1,u8 D2,u8 Config)
{

	//���鷳�ı��ؼ�����ת���㷨!!!!

	u8 DataSelect[4]={0x1,0x3,0x7,0xf};  //ɸѡ����
	//u16 DataRange[4]={256,512,1024,2048};
	u8 FUCK[4]={1,2,4,8};
	u8 Numflag=0x01<<(Config+1);  //����λ�ı�׼λ��
	unsigned int temp=0;


	if((D1&Numflag)!=Numflag)  //����
	{
		D1&=DataSelect[Config];
		temp=D1<<8;
		temp +=D2;
		return (float)temp/25.6*FUCK[Config];

	}
	else   //����
	{
		D1=~D1;
		D2=~D2;
		D1&=DataSelect[Config];
		temp=D1<<8;
		temp+=(D2+1);

		return  -(float)temp/25.6*FUCK[Config];
	}

}
/*
������u8 ADXL345ShowData(float *x,float *y,float *z)
���ܣ����ٶȼƵ�ʵ�����ݺ���
��������õ�ǰx,y,z������ٶ�ֵ
���أ�1
ע��:���ݴ洢��myMEMSData[]��ƫ����ADXL345DF
*/
u8 ADXL345ShowData(u8 Config )
{

	AccX=ADXL345DataProcess(myMEMSData[ADXL345DF+1],myMEMSData[ADXL345DF],Config);
	AccY=ADXL345DataProcess(myMEMSData[ADXL345DF+3],myMEMSData[ADXL345DF+2],Config);
	AccZ=ADXL345DataProcess(myMEMSData[ADXL345DF+5],myMEMSData[ADXL345DF+4],Config);
	return 1;

}	


//====================================================
//�ų�������������HMC5883L��������Ѿ�ĵȵ������ˣ�������
//====================================================
/*
������u8 HMC5883Init(u8 Mode) 
���ܣ���ʼ���ų�����������״̬
������Mode������״̬0-3 2G,4G,8G,16G?
���أ�1
ע��:
*/

void HMC5883LInit()
{
	//mode��ʾ��ǰ�Ĺ���״̬��0-3 2G,4G,8G,16G?
	while(MEMS_WriteReg(HMC5883L,HMC5883L_CfgA,  0x18));      //����bit7Ϊ0��8������,30Hz����ʣ�000��������ģʽ�� 011,101,00   //0704
	while(MEMS_WriteReg(HMC5883L,HMC5883L_CfgB,   0x20));     //����Ĭ�ϴų���Χ��0010000
	
	
}
void HMC5883LPowerMGR(u8 Mode)   //1��ʼ������0,Ϊ����
{
  if(Mode)
       while(MEMS_WriteReg(HMC5883L,HMC5883L_Mode,0x00));  //������������ģʽ����ʱÿ��һ����������Ĵ�������ʼһ���µĲ��� 
  else
       while(MEMS_WriteReg(HMC5883L,HMC5883L_Mode,0x11));  //������������ģʽ����ʱÿ��һ����������Ĵ�������ʼһ���µĲ���

}
/*
������u8 HMC5883LReadData()
���ܣ���ȡ�ų��Ƶ�����
��������
���أ�1  
ע�⣺�洢λ����myMEMSData��ƫ����HMC5883DF
*/
void HMC5883LReadData()
{
	for (u8 i=0;i<6;i++)
	{
		MEMS_ReadReg(HMC5883L,HMC5883L_XMSB+i,myMEMSData+HMC5883DF+i);

	}


	

}

/*
������float HMC5883LDataProcess(u8 D1,u8 D2)  //d1��λ��D2��λ
���ܣ��ų��Ƶ����ݴ���ӿں���
������D1:���ݸ�λ��D2�����ݵ�λ
���أ���õĸ���ֵ
ע�⣺
*/
float HMC5883LDataProcess(u8 D1,u8 D2)  //d1��λ��D2��λ
{
	float fuck;
	unsigned int temp=D1;
	temp=temp<<8;
	temp+=D2;
	signed int temp2=(signed int)temp;
	fuck= (float)(temp2)*0.00092;  //��˹��1W gause ==1T
	return fuck;
}

/*
������u8 HMC5883L(float* x,float* y,float* z)
����:  �ų��Ƶ����ݻ�ú���
������float* x,float* y,float* z�ֱ�洢��ǰ��X,Y��Z������ٶ�
���أ�1
ע�⣺
*/
u8 HMC5883LShowData()
{
	ComX=HMC5883LDataProcess(myMEMSData[HMC5883DF],myMEMSData[HMC5883DF+1]);
	ComZ=HMC5883LDataProcess(myMEMSData[HMC5883DF+2],myMEMSData[HMC5883DF+3]);
	ComY=HMC5883LDataProcess(myMEMSData[HMC5883DF+4],myMEMSData[HMC5883DF+5])+0.136;
	return 1;
}
void InitAllSensor()
{ 
  L3G4200DInit();
  ADXL345Init(3);
  HMC5883LInit();

}
void StartAllSensor()
{
  
  
  HMC5883LPowerMGR(1);
  L3G4200DPowerMGR(1);
}
void CloseAllSensor()
{
    HMC5883LPowerMGR(0);
  L3G4200DPowerMGR(0);
}
                   
void GetAllSensorData()
{
      
      ADXL345ReadData();
      L3G4200DReadData();
      HMC5883LReadData();
}
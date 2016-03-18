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








//����Sensor��SPI��������ס�Լ��ɹ���
#define Sensor_CSN BIT7//P2.5

#define  Sensor_SCK BIT0//P2.6
#define Sensor_MOSI BIT1//P3.3
#define  Sensor_MISO BIT2//P3.7

#define Sensor_CSN_DIR P6DIR
#define Sensor_SCK_DIR P1DIR
#define Sensor_MOSI_DIR P1DIR
#define Sensor_MISO_DIR P1DIR


#define Sensor_CSN_OutPort P6OUT
#define  Sensor_SCK_OutPort P1OUT
#define Sensor_MOSI_OutPort P1OUT
#define  Sensor_MISO_InPort P1IN

#define Sensor_CSN_OutDIR() setbit(Sensor_CSN_DIR,Sensor_CSN)
#define Sensor_SCK_OutDIR() setbit(Sensor_SCK_DIR,Sensor_SCK)
#define Sensor_MOSI_OutDIR() setbit(Sensor_MOSI_DIR,Sensor_MOSI)
#define Sensor_MISO_InDIR() clrbit(Sensor_MISO_DIR,Sensor_MISO)

#define Sensor_Set_CE() setbit(Sensor_CE_OutPort,Sensor_CE)
#define Sensor_Clear_CE() clrbit(Sensor_CE_OutPort,Sensor_CE)
#define Sensor_Set_CSN() setbit(Sensor_CSN_OutPort,Sensor_CSN)
#define Sensor_Clear_CSN() clrbit(Sensor_CSN_OutPort,Sensor_CSN)
#define Sensor_Set_SCK() setbit(Sensor_SCK_OutPort,Sensor_SCK)
#define Sensor_Clear_SCK() clrbit(Sensor_SCK_OutPort,Sensor_SCK)
#define Sensor_Set_MOSI() setbit(Sensor_MOSI_OutPort,Sensor_MOSI)
#define Sensor_Clear_MOSI() clrbit(Sensor_MOSI_OutPort,Sensor_MOSI)


void Init_Sensor_IO(void)
{

	Sensor_CSN_OutDIR();
	Sensor_SCK_OutDIR();
	Sensor_MOSI_OutDIR();
	Sensor_MISO_InDIR();
	Sensor_Set_CSN();
	Sensor_Clear_SCK();
	Sensor_Clear_MOSI();
}
void I2C_Init()
{
  Init_Sensor_IO();
}
//
//
//function SpiWrite();
/******************************************************************************************/
void SensorSpiWrite(unsigned char byte)
{
	unsigned char i;

	Sensor_Clear_SCK();
	for (i=0;i<8;i++) // Setup byte circulation bits
	{
		if ((byte&0x80)==0x80) // Put DATA_BUF.7 on data line
			Sensor_Set_MOSI(); //MOSI=1;
		else
			Sensor_Clear_MOSI(); //MOSI=0;
		Sensor_Set_SCK(); // Set clock line high
		byte=byte<<1;
		Sensor_Clear_SCK(); // Set clock line low
	}

}
//
//
//function SpiRead();
/*****************************************************************************************/
unsigned char SensorSpiRead(void)
{
	unsigned char i;
	unsigned char temp=0;
	Sensor_Clear_SCK();
	for (i=0;i<8;i++) // Setup byte circulation bits
	{
		Sensor_Set_SCK(); // Set clock line high
		temp=temp<<1; // Right shift DATA_BUF
		if ((Sensor_MISO_InPort&Sensor_MISO)==Sensor_MISO)
		{temp|=1;} // Read data
		Sensor_Clear_SCK(); // Set clock line low

	}

	return temp; // Return function parameter
}
void SensorSpiWriteReg(unsigned char SpiCommand,unsigned char Content)
{
	SpiCommand=((SpiCommand&0x3f)<<1)|0x80;
	Sensor_Set_CSN();
	Sensor_Clear_CSN();
	SensorSpiWrite(SpiCommand);
	SensorSpiWrite(Content);
	Sensor_Set_CSN();
}

u8 SensorSpiReadReg(unsigned char Reg)//Payload Out
{
	unsigned char DataBuff;
	Reg=((Reg&0x3f))<<1;
	Sensor_Set_CSN();
	Sensor_Clear_CSN();
	SensorSpiWrite(Reg);
	DataBuff=SensorSpiRead();	
	Sensor_Set_CSN();
	return DataBuff;
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
	switch(ICID)
	{
	case L3G4200D:
		//b=   TWI_RW(0,L3G4200D_I2C_ADDR,RegAddr,0,&dat,1);		
		break;
	case HMC5883L:
		//b=   TWI_RW(0,HMC5883L_I2C_ADDR,RegAddr,0,&dat,1);	
		break;

	case ADXL345:
             SensorSpiWriteReg(RegAddr,dat);
		
		break;

	}
	return 0;
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
	
	switch(ICID)
	{
	case L3G4200D:
		//b=   TWI_RW(1,L3G4200D_I2C_ADDR,RegAddr,0,dat,1);	
		break;
	case HMC5883L:
		//b=   TWI_RW(1,HMC5883L_I2C_ADDR,RegAddr,0,dat,1);	
		break;

	case ADXL345:
              *dat = SensorSpiReadReg(RegAddr);
           
	//	b=   TWI_RW(1,ADXL345_I2C_ADDR,RegAddr,0,dat,1);	
		break;

	}
	return 1;
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
        Init_Sensor_IO();
     
     
	ADXL345Init(3);
	HMC5883LInit();
	L3G4200DInit();
	isGyroExisted=0;
	isAccExisted=1;
	isComExisted=0;
	clrbit(myMEMSData[NODETYPEDF],6);  //GYRO
	clrbit(myMEMSData[NODETYPEDF],5);  //COM
	clrbit(myMEMSData[NODETYPEDF],4);  //ACC
	if(HIDENABLE)
	{
		setbit(myMEMSData[NODETYPEDF],7);// HID
	}
	if(PRESSUREENABLE)
	{
		setbit(myMEMSData[NODETYPEDF],3);// pressure
	}
}
void StartAllSensor()
{
	if(isComExisted)
		HMC5883LPowerMGR(1);


	if(isGyroExisted&&isGyroEnable)
		L3G4200DPowerMGR(1);


}
void CloseAllSensor()
{
	if(isComExisted)
		HMC5883LPowerMGR(0);
	if(isGyroExisted)
	{

		L3G4200DPowerMGR(0);
	}
}

void GetAllSensorData()
{
	if(isAccExisted)
		ADXL345ReadData();
	if(isGyroExisted&&isGyroEnable)
		L3G4200DReadData();
	if(isComExisted)
		HMC5883LReadData();
}
void CalAllSensorData()
{
   HMC5883LShowData();
    ADXL345ShowData(3);
   L3G4200DShowData();
}
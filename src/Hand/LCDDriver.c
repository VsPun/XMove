#include "config.h"
/*
LCDDriver.c
ELPOS2.0�Ĳ�����������������:MZTH
Copyright (c) 2010����һ��
buptzym@bupt.edu.cn
All rights reserved.
���������ѧϰ�ο������ṩ�κοɿ��Է���ĵ���������������ҵĿ��
*/



DOTBYTE X_Witch=8;							//���µ�ǰ��ѡ���ASCIIӢ���ֿ���ַ�����X����
DOTBYTE Y_Witch=16;							//���µ�ǰ��ѡ���ASCIIӢ���ֿ���ַ�����Y��߶�
DOTBYTE X_Witch_cn=16;						//���µ�ǰ��ѡ��������ֿ���ַ�����X����
DOTBYTE Y_Witch_cn=16;						//���µ�ǰ��ѡ��������ֿ���ַ�����Y��߶�

 

unsigned char Send_Buffer[SEND_BUFFER_SIZE];
/******************************Ӳ��������******************************************/
//========================================================================
// ����: void LCD_Initial(void)
// ����: LCDģ���ʼ��,�ڴ˳�ʼ��MCU���ڿ���ģ���UART�ӿڣ��Լ�һЩ���ڿ���
//			ģ��������Ҫ�˿ڻ�����Ӳ��
// ����: ��
// ����: ��
// ��ע: ģ���ϵ��Ĭ�ϵĲ�����Ϊ9600
// �汾:
//      2010/03/04      First version
//========================================================================

void LCD_Initial(void)
{
	P5DIR |= BIT4;				//����ģ�鸴λ
	P5OUT&=~BIT4;
	delay_ms(600);
	P5OUT|=BIT4;
	delay_ms(100);
	
	
}

/****************************�ײ���������**************************/
void UART_SendOneByte(unsigned char Dat)
{
	while (!(IFG1 & UTXIFG0));    //�ȴ����ͼĴ���Ϊ��         
	TXBUF0 = Dat; 
}
void PutString_Test(unsigned char *ptr)
{
	while(*ptr != '\0')
	{
		UART_SendOneByte(*ptr++);                     // ��������
	}
      
}
void UART_SendPacked(unsigned char Command,unsigned char * p,unsigned char num)
{
	//unsigned char Index=0;
	unsigned char check=0;
	
	
	/*UART_TX_Buffer[Index++] = 0x55;
	UART_TX_Buffer[Index++] = num+1;
	UART_TX_Buffer[Index++] = Command;
	check = Command;
	while(num--)
	{
	UART_TX_Buffer[Index++] = *p;
	check += *p++;
	}
	UART_TX_Buffer[Index++] = check;
	UART_TX_Buffer[Index++] = 0xaa;*/
	UART_SendOneByte(0x55);
	UART_SendOneByte(num+1);
	UART_SendOneByte(Command);
	check = Command;
	while(num--)
	{
		UART_SendOneByte(*p);
		check += *p++;
	}
	UART_SendOneByte(check);
	UART_SendOneByte(0xaa);
	
	
}

//========================================================================
// �ļ���: LCD_Dis.c
// ��  ��: Xinqiang Zhang(email: Xinqiang@Mzdesign.com.cn)
//			www.Mzdesign.com.cn
// ��  ��: 2010/03/04
// ��  ��: ͨ�ð�LCD�û��ӿڲ����
//
// ��  ��: ��ο�������ʾ����Ӳ������˵���������DataSheet,���Դ�����д����
//			��ӿڳ���;������������STM32ϵ��MCU����Ӧ����ʾģ��ΪMzTH24 V10
// ��  ��:
//      2010/03/04      First version    Mz Design
//========================================================================

/*
LCDBYTE BMP_Color;
LCDBYTE Char_Color;

  BYTE	Font_type;
  BYTE	Font_Cover;								//
LCDBYTE	Char_BackColor;						 */






//========================================================================
// ����: void FontSet_cn(LCDBYTE Font_NUM,LCDBYTE Color)
// ����: ���ֿ�ѡ��
// ����: Font_NUM 	�����ֿ����Դ���кţ���ο�����ʹ��ʱ����Դ�еĺ��ֿ���ţ�
//		 Color  	�ı���ɫ,�����ں�����ʾ�Լ�Ӣ���ַ���ʾ���ַ���ʾ�Ĳ��� 
// ����: ��
// ��ע: 
// �汾:
//      2010/03/04      First version
//========================================================================
void FontSet_cn(LCDBYTE Font_NUM,LCDBYTE Color)
{
	Send_Buffer[0] = Font_NUM>>8;
	Send_Buffer[1] = (unsigned char) Font_NUM;
	Send_Buffer[2] = Color>>8;
	Send_Buffer[3] = (unsigned char) Color;
	UART_SendPacked(0x83,Send_Buffer,4);
	switch(Font_NUM)
	{
	case 0:					//ѡ��ģ����������Դ�е������ֿ��1��
		X_Witch_cn = 12;
		Y_Witch_cn = 12;
		break;
	case 1:					//ѡ��ģ����������Դ�е������ֿ��1��
		X_Witch_cn = 16;
		Y_Witch_cn = 16;
		break;
	case 2:					//ѡ��ģ����������Դ�е������ֿ��1��
		X_Witch_cn = 24;
		Y_Witch_cn = 24;
		break;
	default:break;
	}
}
//========================================================================
// ����: void BuadRateSet(unsigned int Br) 
// ����: ����ģ�鲨����
// ����: Br Ҫ���õĲ�����
// ����: ��
// ��ע: ģ���ϵ��Ĭ�ϵĲ�����Ϊ9600
// �汾:
//      2010/03/04      First version
//========================================================================
void BuadRateSet(unsigned long Br) 
{
	Send_Buffer[0] = (unsigned char)(Br>>24);
	Send_Buffer[1] = (unsigned char)(Br>>16);
	Send_Buffer[2] = (unsigned char)(Br>>8);
	Send_Buffer[3] = (unsigned char) Br;

	UART_SendPacked(0x8B,Send_Buffer,4);
}
//========================================================================
// ����: void FontSet_rs(int Font_NUM,unsigned int Color)
// ����: Ӣ���������ã��ù���Ϊ����ģ�������ص���Դ�е�Ӣ���ֿ�
// ����: Font_NUM 	����ѡ��,ģ����ص���Դ��Ӣ���ֿ�����Ӧ����Դ���
//		 Color  	�ı���ɫ,�����ں�����ʾ�Լ�Ӣ���ַ���ʾ���ַ���ʾ�Ĳ���
// ����: ��
// ��ע: 
// �汾:
//      2010/03/04      First version
//========================================================================
void FontSet_rs(LCDBYTE Font_NUM,LCDBYTE Color)
{
	Send_Buffer[0] = Font_NUM>>8;
	Send_Buffer[1] = (unsigned char) Font_NUM;
	Send_Buffer[2] = Color>>8;
	Send_Buffer[3] = (unsigned char) Color;
	UART_SendPacked(0x82,Send_Buffer,4);
	switch(Font_NUM)
	{
	case 3:					//ѡ��ģ����������Դ�е�ASCIIӢ���ֿ��0��
		X_Witch = 8;
		Y_Witch = 16;
		break;
	case 4:					//ѡ��ģ����������Դ�е�ASCIIӢ���ֿ��0��
		X_Witch = 20;
		Y_Witch = 40;
		break;
	default:break;
	}
}

//========================================================================
// ����: void FontSet(int Font_NUM,unsigned int Color)
// ����: Ӣ����������  ѡ��ģ���й̼���������Ӣ���ֿ�
// ����: Font_NUM 	����ѡ��,��ģ��̼����ֿ�Ϊ׼
//		 Color  	�ı���ɫ,�����ں�����ʾ�Լ�Ӣ���ַ���ʾ���ַ���ʾ�Ĳ���  
// ����: ��
// ��ע: 
// �汾:
//      2010/03/04      First version
//========================================================================
void FontSet(LCDBYTE Font_NUM,LCDBYTE Color)
{
	Send_Buffer[0] = 0x00;//Font_NUM>>8;
	Send_Buffer[1] = (unsigned char) Font_NUM;
	Send_Buffer[2] = Color>>8;
	Send_Buffer[3] = (unsigned char) Color;
	UART_SendPacked(0x81,Send_Buffer,4);
	switch(Font_NUM)
	{
	case 0:					//ѡ��ģ��̼��Դ�ASCIIӢ���ֿ��0��
		X_Witch = 6;
		Y_Witch = 10;
		break;
	case 1:					//ѡ��ģ��̼��Դ�ASCIIӢ���ֿ��1��
		X_Witch = 8;
		Y_Witch = 16;
		break;
	case 2:					//ѡ��ģ��̼��Դ�ASCIIӢ���ֿ��2��
		X_Witch = 10;
		Y_Witch = 20;
		break;
	case 3:					//ѡ��ģ��̼��Դ�ASCIIӢ���ֿ��3��
		X_Witch = 16;
		Y_Witch = 32;
		break;
	default:break;
	}
}

//========================================================================
// ����: void NumberDis(LCDBYTE x,LCDBYTE y,signed int Num,unsigned char len,unsigned char type)  
// ����: ֱ��������ʾ
// ����: x	Ҫ��ʾ�����ֵ����Ͻ�x����ʼλ��
//		 y	Ҫ��ʾ�����ֵ����Ͻ�y����ʼλ��
//		 Num	Ҫ��ʾ������
//		 len	Ҫ��ʾ�����ֵ�ʮ����λ�ĸ���
//		 type	��ʾģʽ
//			0: ȫ��ʾ
//			1��������ʾ
//			2��������ʾ
// ����: ��
// ��ע: ʹ�õ�ǰ���õ�Ӣ�����壬�����ַ�����ģʽ����
// �汾:
//      2010/03/04      First version
//========================================================================
void NumberDis(LCDBYTE x,LCDBYTE y,signed long Num,unsigned char len,unsigned char type) 
{
	unsigned char *temp;
	Send_Buffer[0] = x>>8;
	Send_Buffer[1] = (unsigned char) x;
	Send_Buffer[2] = y>>8;
	Send_Buffer[3] = (unsigned char) y;
	temp = (unsigned char*)&Num;
	Send_Buffer[7] = *temp++;
	Send_Buffer[6] = *temp++;
	Send_Buffer[5] = *temp++;
	Send_Buffer[4] = *temp;
	Send_Buffer[8] = len;
	Send_Buffer[9] = type;
	
	UART_SendPacked(0x0a,Send_Buffer,10);
}

//========================================================================
// ����: void PutBitmap(LCDBYTE x,LCDBYTE y,unsigned short Index,LCDBYTE Color)  
// ����: ��ʾһ��ģ����Դ�е�λͼ��ָ��λ����
// ����: x  X������     y  Y������
//		 Index  λͼ��Դ����Դ���е����к� 
//		 Color	λͼ��ʾʱ��Ч��
//			0x0000��������ʾλͼ
//			����:	��ָ����ɫ��ʹλͼƫɫ��ʾ 
// ����: ��
// ��ע: 
// �汾:
//      2010/03/04      First version
//========================================================================
void PutBitmap(LCDBYTE x,LCDBYTE y,unsigned short Index,LCDBYTE Color) 
{
	Send_Buffer[0] = x>>8;
	Send_Buffer[1] = (unsigned char) x;
	Send_Buffer[2] = y>>8;
	Send_Buffer[3] = (unsigned char) y;
	Send_Buffer[4] = Index>>8;
	Send_Buffer[5] = (unsigned char) Index;
	if(Color==0)
		UART_SendPacked(0x09,Send_Buffer,6);
	else
	{
		Send_Buffer[6] = Color>>8;
		Send_Buffer[7] = (unsigned char)Color;
		UART_SendPacked(0x0d,Send_Buffer,8);
	}
     
}
//========================================================================
// ����: void PutChar_cn(unsigned char x,unsigned char y,unsigned short * GB) 
// ����: д��һ���������ֿ⺺��
// ����: x  X������     y  Y������
//		 a  GB��  
// ����: ��
// ��ע: ��ע��MCU�Ĵ�С��
// �汾:
//      2010/03/04      First version
//========================================================================

void PutChar_cn(LCDBYTE x,LCDBYTE y,unsigned char * GB) 
{
	Send_Buffer[0] = x>>8;
	Send_Buffer[1] = (unsigned char) x;
	Send_Buffer[2] = y>>8;
	Send_Buffer[3] = (unsigned char) y;
	Send_Buffer[4] = *(GB++);		//���Ͷ����ֿ��к���GB��ĸ߰�λֵ
	Send_Buffer[5] = *GB;	//���Ͷ����ֿ��к���GB��ĵͰ�λֵ
	UART_SendPacked(0x08,Send_Buffer,6);
}

//========================================================================
// ����: void PutString_cn(unsigned char x,unsigned char y,unsigned short *p)
// ����: ��x��yΪ��ʼ���괦д��һ�������ַ�
// ����: x  X������     y  Y������
//		 p  Ҫ��ʾ���ַ���  
// ����: ��
// ��ע: ͬPutChar_cn�еĽ���
// �汾:
//      2010/03/04      First version
//========================================================================



//========================================================================
void PutString_cn(LCDBYTE x,LCDBYTE y,unsigned char *p)
{
	unsigned char Index;
	Send_Buffer[0] = x>>8;
	Send_Buffer[1] = (unsigned char) x;
	Send_Buffer[2] = y>>8;
	Send_Buffer[3] = (unsigned char) y;
	Index = 4;
	while(*p!='\0'&&Index<68)
	{
		Send_Buffer[Index++] = *p++;
		//Send_Buffer[Index++] = (unsigned char)((*p++)>>8);
	}
	UART_SendPacked(0x0c,Send_Buffer,Index);
}
//========================================================================
// ����: void FontMode(BYTE Mode,LCDBYTE FontBackColor) 
// ����: �����ַ���ʾ��ģʽ,�����ñ���ɫ
// ����: Mode	0: �ַ���ʾʱ�����ַ�����Ч�������ʾ����,Ҳ���ǲ�����������
//					Ϊ����ģʽ
//				1: ����ģʽ
//		FontBackColor	���ø���ģʽʱ,�ַ��ı���ɫ 
// ����: ��
// ��ע: �����ַ���ʾ��Ч
// �汾:
//      2010/03/04      First version
//========================================================================
void FontMode(BYTE Mode,LCDBYTE FontBackColor)
{
	Send_Buffer[0] = Mode;//>>8;
	//	Send_Buffer[1] = (unsigned char) Font_NUM;
	Send_Buffer[1] = FontBackColor>>8;
	Send_Buffer[2] = (unsigned char) FontBackColor;
	UART_SendPacked(0x85,Send_Buffer,3);
}
//========================================================================
// ����: void PutChar(DOTBYTE x,DOTBYTE y,char a) 
// ����: д��һ����׼�ַ�
// ����: x  X������     y  Y������
//		 a  Ҫ��ʾ���ַ����ֿ��е�ƫ����  
// ����: ��
// ��ע: ASCII�ַ���ֱ������ASCII�뼴��
// �汾:
//      2010/03/04      First version
//========================================================================
void PutChar(DOTBYTE x,DOTBYTE y,char a)       
{
	Send_Buffer[0] = x>>8;
	Send_Buffer[1] = (unsigned char) x;
	Send_Buffer[2] = y>>8;
	Send_Buffer[3] = (unsigned char) y;
	Send_Buffer[4] = (unsigned char) a;
	UART_SendPacked(0x07,Send_Buffer,5);
}

//========================================================================
// ����: void PutString(DOTBYTE x,DOTBYTE y,char *p)
// ����: ��x��yΪ��ʼ���괦д��һ����׼�ַ�
// ����: x  X������     y  Y������
//		 p  Ҫ��ʾ���ַ���  
// ����: ��
// ��ע: ���������Դ���ASCII�ַ�����ʾ
// �汾:
//      2010/03/04      First version
//========================================================================
void PutString(DOTBYTE x,DOTBYTE y,u8 *p)
{
	unsigned char Index;
	Send_Buffer[0] = x>>8;
	Send_Buffer[1] = (unsigned char) x;
	Send_Buffer[2] = y>>8;
	Send_Buffer[3] = (unsigned char) y;
	Index = 4;
	while(*p&&Index<68)
	{
		Send_Buffer[Index++] = *p++;
	}
	UART_SendPacked(0x0b,Send_Buffer,Index);
}
//========================================================================
// ����: void SetPaintMode(BYTE Mode,LCDBYTE Color)
// ����: ��ͼģʽ����
// ����: Mode ��ͼģʽ    Color  ���ص����ɫ,�൱��ǰ��ɫ  
// ����: ��
// ��ע: Mode��Ч
// �汾:
//      2010/03/04      First version
//========================================================================
void SetPaintMode(BYTE Mode,LCDBYTE Color)
{
	//	LCDBYTE temp;
	//	temp = BMP_Color;
	Mode = Mode;//Plot_Mode = Mode;		//������Ϊ�˱���������������һ���ԣ���ͼģʽ�ڸð�������δ��
	//	BMP_Color = Color;
	Send_Buffer[0] = Color>>8;
	Send_Buffer[1] = (unsigned char) Color;
	UART_SendPacked(0x84,Send_Buffer,2);
	
}
//========================================================================
// ����: void PutPixel(DOTBYTE x,DOTBYTE y)
// ����: ��x��y���ϻ���һ��ǰ��ɫ�ĵ�
// ����: x  X������     y  Y������
// ����: ��
// ��ע: ʹ��ǰ��ɫ
// �汾:
//      2010/03/04      First version
//========================================================================
void PutPixel(DOTBYTE x,DOTBYTE y)
{
	Send_Buffer[0] = x>>8;
	Send_Buffer[1] = (unsigned char) x;
	Send_Buffer[2] = y>>8;
	Send_Buffer[3] = (unsigned char) y;
	UART_SendPacked(0x01,Send_Buffer,4); 	
}
//========================================================================
// ����: void Line(LCDBYTE s_x,LCDBYTE s_y,LCDBYTE e_x,LCDBYTE e_y)
// ����: ��s_x��s_yΪ��ʼ���꣬e_x��e_yΪ�����������һ��ֱ��
// ����: x  X������     y  Y������
// ����: ��
// ��ע: ʹ��ǰ��ɫ
// �汾:
//      2010/03/04      First version
//========================================================================
void Line(LCDBYTE s_x,LCDBYTE s_y,LCDBYTE e_x,LCDBYTE e_y)
{  
	Send_Buffer[0] = s_x>>8;
	Send_Buffer[1] = (unsigned char) s_x;
	Send_Buffer[2] = s_y>>8;
	Send_Buffer[3] = (unsigned char) s_y;
	Send_Buffer[4] = e_x>>8;
	Send_Buffer[5] = (unsigned char) e_x;
	Send_Buffer[6] = e_y>>8;
	Send_Buffer[7] = (unsigned char) e_y;
	UART_SendPacked(0x02,Send_Buffer,8);   
}
//========================================================================
// ����: void Circle(DOTBYTE x,DOTBYTE y,DOTBYTE r,BYTE Mode)
// ����: ��x,yΪԲ��RΪ�뾶��һ��Բ(mode = 0) or Բ��(mode = 1)
// ����: 
// ����: ��
// ��ע: ��Բ����ִ�н��������MCU�п��Ź����������幷�Ĳ���
// �汾:
//      2010/03/04      First version
//========================================================================
void Circle(DOTBYTE x,DOTBYTE y,DOTBYTE r,BYTE Mode)
{
	Send_Buffer[0] = x>>8;
	Send_Buffer[1] = (unsigned char) x;
	Send_Buffer[2] = y>>8;
	Send_Buffer[3] = (unsigned char) y;
	Send_Buffer[4] = r>>8;
	Send_Buffer[5] = (unsigned char) r;
	if(Mode==0)
		UART_SendPacked(0x05,Send_Buffer,6);
	else
        {
		UART_SendPacked(0x06,Send_Buffer,6);
            //    delay_ms(10);
        }
        
}	

//========================================================================
// ����: void Rectangle(DOTBYTE left, DOTBYTE top, DOTBYTE right, 
//						DOTBYTE bottom, BYTE Mode)
// ����: ��x,yΪԲ��RΪ�뾶��һ��Բ(mode = 0) or Բ��(mode = 1)
// ����: left - ���ε����ϽǺ����꣬��Χ0��118
//		 top - ���ε����Ͻ������꣬��Χ0��50
//		 right - ���ε����½Ǻ����꣬��Χ1��119
//		 bottom - ���ε����½������꣬��Χ1��51
//		 Mode - ����ģʽ��������������ֵ֮һ��
//				0:	���ο򣨿��ľ��Σ�
//				1:	�����棨ʵ�ľ��Σ�
// ����: ��
// ��ע: 
// �汾:
//      2010/03/04      First version
//========================================================================
void Rectangle(DOTBYTE left, DOTBYTE top, DOTBYTE right, DOTBYTE bottom, BYTE Mode)
{
	Send_Buffer[0] = left>>8;
	Send_Buffer[1] = (unsigned char) left;
	Send_Buffer[2] = top>>8;
	Send_Buffer[3] = (unsigned char) top;
	Send_Buffer[4] = right>>8;
	Send_Buffer[5] = (unsigned char) right;
	Send_Buffer[6] = bottom>>8;
	Send_Buffer[7] = (unsigned char) bottom;
	if(Mode==0)
		UART_SendPacked(0x03,Send_Buffer,8);
	else
		UART_SendPacked(0x04,Send_Buffer,8);
     
}
//========================================================================
// ����: void ClrScreen(BYTE Mode)
// ����: ����������ִ��ȫ��Ļ��������ǰ��ɫ
// ����: Mode   0:ȫ������
//				1:ȫ�����ǰ��ɫ
// ����: ��
// ��ע: 
// �汾:
//      2010/03/04      First version
//========================================================================
void ClrScreen(BYTE Mode)
{
	if(Mode==0)
		Send_Buffer[0] = 0xaa;
	else Send_Buffer[0] = 0x55;
	UART_SendPacked(0x80,Send_Buffer,1);
}

//========================================================================
// ����: void BackLightSet(unsigned short Gra)
// ����: ���õ�ǰ�������ȵȼ�
// ����: Gra   0~500
// ����: ��
// ��ע: 
// �汾:
//      2010/03/04      First version
//========================================================================
void BackLightSet(unsigned short Gra)
{
	Send_Buffer[0] = Gra>>8;
	Send_Buffer[1] = (unsigned char) Gra;
	UART_SendPacked(0x8A,Send_Buffer,2);	
   
}

//========================================================================
// ����: void BackLightTo(unsigned short Gra)
// ����: ���ñ������ȣ���ʹģ���ɵ�ǰ�ı������Ƚ��䵽���趨��ֵ
// ����: Gra   0~500
// ����: ��
// ��ע: 
// �汾:
//      2010/03/04      First version
//========================================================================
void BackLightTo(unsigned short Gra)
{
	Send_Buffer[0] = Gra>>8;
	Send_Buffer[1] = (unsigned char) Gra;
	UART_SendPacked(0x89,Send_Buffer,2);	
        delay_ms(50);
}

//========================================================================
// ����: void BackLightStep(unsigned char Step)
// ����: ���⻺��/�����ٶ�����
// ����: Step   5~100   ��ֵԽС��������ٶ�Խ��
// ����: ��
// ��ע: 
// �汾:
//      2010/03/04      First version
//========================================================================
void BackLightStep(unsigned char Step)
{
	Send_Buffer[0] = Step;
	UART_SendPacked(0x88,Send_Buffer,1);	
}

//========================================================================
// ����: void LCDSetSleep(void)
// ����: ����ģ�����ʡ��ģʽ
// ����: 
// ����: ��
// ��ע: 
// �汾:
//      2010/03/04      First version
//========================================================================
void LCDSetSleep(void)
{
	Send_Buffer[0] = 0x5a;
	UART_SendPacked(0x8c,Send_Buffer,1);	
         delay_ms(100);
}
//========================================================================
// ����: void LCDWakeup(void)
// ����: ��ģ���ʡ��ģʽ�л���
// ����: ��
// ����: ��
// ��ע: ģ�鱻���Ѻ���õ�10ms�����ٶ�ģ����в���
// �汾:
//      2010/03/04      First version
//========================================================================
void LCDWakeup(void)
{
	UART_SendOneByte(0x00);	
}


void Lcd_disp(unsigned int x,unsigned int y,unsigned char *p)
{
	
	unsigned char Index;
	u8 flag=0,s=1,b=0;
      
	u8 length=strlenExt(p);
	while(flag<length)
	{
		Send_Buffer[0] = x>>8;
		Send_Buffer[1] = (unsigned char) x;
		Send_Buffer[2] = y>>8;
		Send_Buffer[3] = (unsigned char) y;
		Index = 4;
                
	        while(flag<length&&*(p+flag)<0x80&&s==1)
		{
			Send_Buffer[Index++] = *(p+flag); 
			flag++;
			x += X_Witch;
                        if((x + X_Witch) >Dis_X_MAX)
			{
				x = 0;
				if((Dis_Y_MAX - y) < Y_Witch) break;
				else y += Y_Witch_cn;
                                s=0;
                              
			}
                          b=1;
			
		}
		if(b==1)
		{
			
			UART_SendPacked(0x0b,Send_Buffer,Index);
		}
		b=0,s=1;
                Send_Buffer[0] = x>>8;
		Send_Buffer[1] = (unsigned char) x;
		Send_Buffer[2] = y>>8;
		Send_Buffer[3] = (unsigned char) y;
		Index = 4;
		while(flag<length&&*(p+flag)>0x80&&s==1)
		{
			Send_Buffer[Index++] = *(p+flag); 
			Send_Buffer[Index++] = *(p+flag+1); 
			flag+=2;
			x += X_Witch_cn;
                        if((x + X_Witch_cn) >Dis_X_MAX)
			{
				x = 0;
                                s=0;
				if((Dis_Y_MAX - y) < Y_Witch_cn) break;
				else y += Y_Witch_cn;
			}
			
          
                        b=2;
		}
		if(b==2)
		{
			
			UART_SendPacked(0x0c,Send_Buffer,Index);
		}
	}
	
    
	
	
	
}

void FontSetTotal(LCDBYTE Color)
{
	FontSet( 1, Color);
	//ѡ�������ֿ�,�ú���ֻ��ѡ��ģ�������ص���Դ�е����ĺ����ֿ�
	FontSet_cn( 1, Color);
}
void Lcd_disp_limlen(unsigned int x,unsigned int y,unsigned char *p,unsigned char Tlength)
{
  unsigned char Index;
	u8 flag=0,s=1,b=0;
       
	u8 length=strlenExt(p);
        if(Tlength<length)
          length=Tlength;
	while(flag<length)
	{
		Send_Buffer[0] = x>>8;
		Send_Buffer[1] = (unsigned char) x;
		Send_Buffer[2] = y>>8;
		Send_Buffer[3] = (unsigned char) y;
		Index = 4;
                
	        while(flag<length&&*(p+flag)<0x80&&s==1)
		{
			Send_Buffer[Index++] = *(p+flag); 
			flag++;
			x += X_Witch;
                        if((x + X_Witch) >Dis_X_MAX)
			{
				x = 0;
				if((Dis_Y_MAX - y) < Y_Witch) break;
				else y += Y_Witch_cn;
                                s=0;
                              
			}
                          b=1;
			
		}
		if(b==1)
		{
			
			UART_SendPacked(0x0b,Send_Buffer,Index);
		}
		b=0,s=1;
                Send_Buffer[0] = x>>8;
		Send_Buffer[1] = (unsigned char) x;
		Send_Buffer[2] = y>>8;
		Send_Buffer[3] = (unsigned char) y;
		Index = 4;
		while(flag<length&&*(p+flag)>0x80&&s==1)
		{
			Send_Buffer[Index++] = *(p+flag); 
			Send_Buffer[Index++] = *(p+flag+1); 
			flag+=2;
			x += X_Witch_cn;
                        if((x + X_Witch_cn) >Dis_X_MAX)
			{
				x = 0;
                                s=0;
				if((Dis_Y_MAX - y) < Y_Witch_cn) break;
				else y += Y_Witch_cn;
			}
			
          
                        b=2;
		}
		if(b==2)
		{
			
			UART_SendPacked(0x0c,Send_Buffer,Index);
		}
	}
	
  
}


void PutString_limit(DOTBYTE x,DOTBYTE y,u8 *p,u8 length)
{
	unsigned char Index,i=0;
	Send_Buffer[0] = x>>8;
	Send_Buffer[1] = (unsigned char) x;
	Send_Buffer[2] = y>>8;
	Send_Buffer[3] = (unsigned char) y;
	Index = 4;
	while(*p&&Index<68&&i<length)
	{
		Send_Buffer[Index++] = *p++;
                i++;
	}
	UART_SendPacked(0x0b,Send_Buffer,Index);
}
void BitRateConfig()
{
       BuadRateSet(115200);
        delay_ms(50);
     
  UTCTL0 |= SSEL1;                          // UCLK = SMCLK
  UBR00 = 0x45;                             // 8Mhz/115200 - 69.44
  UBR10 = 0x00;                             //
  UMCTL0 = 0x4A;                            // modulation
   
  delay_ms(40);
  
  
}



/*
GUIPack.c
LCDͼ�οؼ��⣬�������ͬ����˾����ϵ�е�LCD�����Ż�
Copyright (c) 2010����һ��
buptzym@bupt.edu.cn
All rights reserved.
���������ѧϰ�ο������ṩ�κοɿ��Է���ĵ���������������ҵĿ��
*/



#include "config.h"
#include "string.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/*
������BoxGUI(unsigned char *title) 
���ܣ���LCD�ϲ���������Ļ������
��������
*/
void BoxGUI(unsigned char *title)    //ͼ�λ����洰�ں���
{ 
	SetPaintMode(0,COLOR_Cyan);
	ClrScreen(1);
	SetPaintMode(0,OSColor);
	Rectangle(0,0,319,17,1);
	Rectangle(0,239,319,223,1);
	FontMode(0,1);
	FontSetTotal(COLOR_White);
	Lcd_disp(2,223,title);
	Lcd_disp(2,2,"xOS Super Edition");
        Lcd_disp(240,2,"ID:");
        ShowMountGUI(280,2,PCID,1,COLOR_White,1);
       
        
}
void DrawMovingBackColor(u16 x1,u16 y1,u16 x2,u16 y2,LCDBYTE COLOR,u8 Direction,u8 MoveEN)
{
	SetPaintMode(0,COLOR);
	if(x2-x1+y2-y1>350&&(MoveEN==0))
		Rectangle(x1,y1,x2,y2,1);
	else
	{
		switch(Direction)
		{
		case 1:  //��
			for (u8 i=y1;i<y2;i++)
			{
				Line(x1,i,x2,i);
				delay_ms(5);
			}
			break;
		case 2:  //��
			for (u8 i=y2;i>y1;i--)
			{
				Line(x1,i,x2,i);
			}
			break;
		case 3:  //��
			for (u8 i=x1;i<x2;i++)
			{
				Line(i,y1,i,y2);
			}
			break;
		case 4:  //��
			for (u8 i=x2;i>x1;i--)
			{
				Line(i,y1,i,y2);
			}
			break;
		}
	}
	
}

/*
������TaskBoxGUI_P(u16 x1,u16 y1,u16 x2,u16 y2,u8 *title)
���ܣ���LCD�ϲ����ɱ��С������׿�
��������x1,y1�����Ͻ����꣬(X2,Y2)���½�����,titleΪ���ڱ���
*/
void TaskBoxGUI_P(u16 x1,u16 y1,u16 x2,u16 y2,u8 *title,u8 MoveEN)    //ͼ�λ����洰�ں���
{
	
	
	DrawMovingBackColor(x1+3,y1+3,x2+3,y2+3,COLOR_Black,1,MoveEN);
	
	
	
	Rectangle(x1,y1,x2,y2,0);
	SetPaintMode(0,OSColor);
	Rectangle(x1,y1+1,x2,y1+16,1);
	
	SetPaintMode(0,COLOR_White);
	
	Rectangle(x1+1,y1+Y_Witch+1,x2-1,y2-1,1);
	
	FontMode(0,COLOR_White);
	FontSetTotal(COLOR_White);
	Lcd_disp(x1,y1,title);
	FontSetTotal(COLOR_Black);
}
/*
������ShowMountGUI(u16 x,u16 y,float Mount,u8 Range,u16 Color,u8 Font)
���ܣ���LCD����ʾ�ɱ�λ�õĸ���ֵ
��������x,y)�������Ͻ�����ֵ��mountҪ��ʾ�ĸ�������range�Ը�����ʾ�ĳ��ȣ�����ʼ
Color��ʾ��ɫ��Font�������ͣ��μ�LCDʹ��˵��
*/

void ShowMountGUI(u16 x,u16 y,float Mount,u8 Range,u16 Color,u8 Font)
{
	unsigned char MountTemp[8];
	
	sprintf((char*)MountTemp,"%f", Mount);
	FontSet(Font,Color);
	
	PutString_limit(x,y,MountTemp,Range);
	
	
}
/*
������u8  MenuGUI()  
���ܣ���ʾ��ͬ���Ĳ˵�����
������(ȫ�ֱ���)MenuTypeָ����ǰ��ʾ�Ľ����񣬲μ�����༭�����˵��
����ֵ���̶�Ϊ1
*/

u8  MenuGUI()    //ͼ�λ����洰�ں���
{
	switch(MenuType)
	{    
	case 0:
		MainMenuListGUI(1,3,200,64);
		break;
	case 1:
		MainMenuListGUI(1,8,0,25);
		break;
	case 2:
		MainMenuListGUI(3,2,100,90);
		break;
		
	}
	return 1;
}


/*
������void TaskBoxGUI(unsigned char *title)  
���ܣ���LCD����ʾ�̶���С��λ�õ�����׿�
������tilte:��ʾ�ı���
����ֵ����
*/
void TaskBoxGUI(unsigned char *title)   
{ 
	TaskBoxGUI_P(7,27,307,197,title,0);
}

/*
������unsigned char myListGUI(u8 x,u8 y,u8 ** list, u8 mount)
���ܣ���LCD����ʾ�̶���С���ɱ�λ�õ��б��Ͳ˵�����
��������x,y��Ҫ��ʾ���꣬**list�洢�б��ָ�����飬mount��Ҫ��ʾ���б�������
ע�ⲻ�ܳ��������С
����ֵ��0����ʾ�û�ǿ���˳���1-mount�����ص�ǰ�û���ѡ���ע�⣺��1��ʼ��
*/
unsigned char myListGUI(u8 x,u8 y,u8 ** list,u8 *title, u8 MaxMount,u8 LRMaxMount,u8 UDMaxMount,u8 OneLRLength,u8 OneUDLength)
{
    u8  func_state=0, menu_flag=1,flag=1,UDListMount,TotalFreshEN,FreshEN=1;  //UDListMountʵ�ʵ��б�����
	
	if(LRMaxMount==1)
		UDListMount=UDMaxMount;
	else
		UDListMount=MaxMount/LRMaxMount+1;
    
	if(func_state==0)
	{
		
		
		TaskBoxGUI_P(x+1,y+1,x+3+LRMaxMount*OneLRLength,y+Y_Witch_cn+UDListMount*OneUDLength+5,title,1);
		
		func_state=1;
	}
	while(func_state==1)
		
	{
		
		if(FreshEN==1)
		{
			SetPaintMode(0,COLOR_White); 
			Rectangle(x+2,y+2+Y_Witch_cn,x+2+LRMaxMount*OneLRLength,y+UDListMount*OneUDLength+11,1);
			SetPaintMode(0,COLOR_Black); 
		}
		
		for (u8 UDflag=0;UDflag<UDMaxMount;UDflag++)
		{
			for(u8 LRflag=0;LRflag<LRMaxMount;LRflag++)
			{
				if (menu_flag-1+UDflag*LRMaxMount+LRflag>=MaxMount)
				{
					break;
				}
				DrawTitle(x+1+LRflag*OneLRLength,y+Y_Witch_cn+4+UDflag*OneUDLength,list[menu_flag-1+UDflag*LRMaxMount+LRflag],LRflag+UDflag*LRMaxMount+1==flag?1:0,0,FreshEN);
			}//
		}
		
		
		
		FontMode(1,COLOR_White);
		FontSetTotal(COLOR_Black);
		switch(UpdownListInputControl(&menu_flag,&flag,MaxMount,LRMaxMount,UDMaxMount,0,&FreshEN,&TotalFreshEN))
		{
		case 0:
			OSTaskClose();
			func_state=2;
			return 0;
			
		case 1:
			func_state=2;
			break;
			
			
		}    
	}		
	return menu_flag+flag-1;
}
/*
������unsigned char MessageGui(unsigned char *title,unsigned char *message,unsigned char Type)
���ܣ���LCD����ʾ�̶���С���Ƿ���ѡ�����
������*titleҪ��ʾ�ı��⣬message��Ҫ��ʾ����Ϣ��Type:��ʾ��� 0������ȷ���������ʾ��1�����Ƿ�����ѡ�2������ȷ�ϵ���ʾ��
����ֵ��1:�û�ѡ���ǣ�0���û�ѡ�����Type==0��2������ֵΪ1
*/
unsigned char MessageGui(unsigned char *title,unsigned char *message,unsigned char Type)
{
	if(Type==2)
	{
		TaskBoxGUI_P(65,70,253,144,title,1);
		
		FontSetTotal(COLOR_Black);
		Lcd_disp(68,86,message);
		delay_ms(400);
		return 1;
	}
	
	u8* temp[2];
	temp[0]="ȷ��";
	temp[1]="ȡ��";
	TaskBoxGUI_P(70,70-Y_Witch_cn,253,144,title,0);
	switch(myListGUI(80,72,temp,message,Type+1,2,1,4*X_Witch_cn,1*Y_Witch_cn))
	{
	case 0:
		return 0;
	case 1:
		return 1;
	case 2:
		return 0;
	}
	return 1;
	
	
}

/*
������unsigned char ListGUI(unsigned char** list,unsigned char *title,unsigned char mount)
���ܣ���LCD����ʾ�̶���С�͹̶�λ�ã���LCD���룩���б��Ͳ˵�����
�������μ�myListGUI()�ĺ�������
����ֵ���μ�myListGUI()�ĺ�������
*/
unsigned char ListGUI(unsigned char** list,unsigned char *title,unsigned char mount)
{
	u8 temp,WidthMax=0,LRMount,UDMount;
	for(u8 t=0;t<mount;t++)
	{
		temp=strlenExt(*(list+t));
		if(temp>WidthMax)
			WidthMax=temp;		
	}
	if(WidthMax>12)
	{
		LRMount=1;
		if(mount<5)
			UDMount=mount;
		else
			UDMount=5;
		
		
	}
	else
	{
		LRMount=2;
		UDMount=mount/2+mount%2;
	}
	
	
	return myListGUI(40,80,list,title,mount,LRMount,UDMount,(WidthMax+4)*X_Witch,24);
	
}
/*
������unsigned char  TextGUI(unsigned char *Text,unsigned char *title,unsigned char UpLimit,unsigned char DownLimit,u8 type)
���ܣ���LCD����ʾ����������ֵ�ͼ�ν���ؼ�
������Text:Ҫ��ʾ������ָ��,UpLimit��LCD����ʾ���������λ�ã���16����Ϊ׼��,DownLimit,��ײ�����λ�ã�type:ָ����ǰ��ȷ�ϼ����Ƿ������⹦�ܳ���
����ֵ��1���û���ѡȷ�ϣ���Ȼ������2�������⹦�ܴ��ڵ�����£��û����ȷ�� 0���������������ʱ����0
*/
unsigned char  TextGUI(unsigned char *Text,unsigned char *title,unsigned char UpLimit,unsigned char DownLimit,u8 type)
{
	//type����ָ����ǰ��ȷ�ϼ����Ƿ������⹦�ܳ���
	unsigned char page=1;
	unsigned char ReturnValue=0;   //������ֵΪ1ʱ��Ӧ�����ú���
	unsigned char func_state=0;
	unsigned char Temp;
	unsigned char OS_count=9;
	
	unsigned char Interval=DownLimit-UpLimit+1;  //����������޵ļ�� �����޷�Χ��Ϊ0-4���Ͻ�һ��С�ڵ����½�
	
	u8   Tpage;
	FontSetTotal(COLOR_Black);
	
	if(func_state==0)
	{  
		//BoxGUI(Title);
		OS_count=strlenExt(Text)/30;  
		Tpage=OS_count/Interval+1;
		func_state=1;
	}
	while(func_state==1)
	{       
		
		SetPaintMode(0,COLOR_Black); 
		
		Rectangle(1,Y_Witch*(UpLimit-1),319,Y_Witch*(DownLimit-1),1);
		SetPaintMode(0,COLOR_White); 
		Rectangle(2,Y_Witch*(UpLimit)+1,318,Y_Witch*(DownLimit-1)-1,1);
		
		FontSetTotal(COLOR_White);
		FontMode(0,COLOR_Black);
		Lcd_disp(2,Y_Witch*(UpLimit-1),"�ı��Ķ�--");
		
		Lcd_disp(2+X_Witch_cn*5,Y_Witch*(UpLimit-1),title);
		FontSetTotal(COLOR_Black);    
		if( Tpage>1)
			Lcd_disp_limlen(1,Y_Witch*(UpLimit)+1,*(Text+(page-1)*30)>0x80?Text+(page-1)*30-1:Text+(page-1)*30,Interval*30);
		else 
			Lcd_disp_limlen(1,Y_Witch*(UpLimit)+1,Text,Interval*30);
		//Rectangle(1,1,127,63,0);
		Temp=(unsigned char)(Y_Witch*(UpLimit)+1+(Y_Witch*Interval)*((float)page/(float)OS_count));
		Line(317,Y_Witch*(UpLimit)+1,317,Y_Witch*(DownLimit+1)+2);
		Rectangle(318,Temp,319,Temp+(unsigned char )((Y_Witch*Interval)*(float)page/(float)OS_count),1);
		InputControl();
		switch(key_data)
		{
		case KEYENTER_UP   :
			ReturnValue=1; 
			func_state=2;
			page=1;
			break;
		case KEYCANCEL_UP    :
			if(type==1)
			{
				if(MessageGui("��ʾ��Ϣ","���빦�ܲ˵�",0))
					ReturnValue=2;    //�������⹦��
				page=1;
				func_state=2;
			}
			break;
		case KEYUP_UP  :
			if(page>1)
				page--;
			break;
		case KEYUP_DOWN :
			if(page<OS_count&&Tpage>1)
				page++;
			break;
			
			
		}
		
	}
	return ReturnValue;
	
}

/*
������void SystemOpenGUI()
���ܣ���LCD����ʾϵͳ��ʼ�����棬����ϵͳ��������
��������
����ֵ����
*/
void SystemOpenGUI()
{    
	BitRateConfig();
	BackLightSet(OSBackLight);
         OSLightControl(2);
	PutBitmap(0,0,5,0);
	delay_ms(2000);
          OSLightControl(2);
	SetPaintMode(0,COLOR_Black);
	ClrScreen(1);
	FontMode(0,1);
	FontSetTotal(COLOR_White);
	PutString(2,2,"ELPOS Enhanced Edition 2.0");
          OSLightControl(2);
	delay_ms(200);
	FontSet(3,COLOR_Red);
          OSLightControl(2);
	PutString(200,50,"ELPOS");
	FontSet(2,OSColor); 
	PutString(200,100,"X-MOVE");
	FontSet(1,COLOR_White);
          OSLightControl(2);
	PutString(2,2+Y_Witch,"System Check...");
          OSLightControl(2);
	delay_ms(200);
	PutString(2,2+3*Y_Witch,"Flash:64KB,RAM:2KB");
          OSLightControl(2);
	delay_ms(200);
         
	PutString(2,2+4*Y_Witch,"CPU:MSP430F149 OC 16MHz");
          OSLightControl(2);
	delay_ms(400);
	PutString(2,2+5*Y_Witch,"DC IN 3.3V INPUT");
	delay_ms(200);
          OSLightControl(2);
	PutString(2,2+6*Y_Witch,"Loading The Data...");
	delay_ms(500);
	PutString(2,2+7*Y_Witch,"Please Wait");
          OSLightControl(0);
	//��ʼ������
	myMEMSData[0]=PCID;  //��ǰ��������ַ
#if PCID==1
        MenuType=2;
        OSColor=COLOR_Black;
#endif 
#if PCID==2
          MenuType=0;
        OSColor=COLOR_Blue;
#endif 

   #if PCID==3
          MenuType=2;
        OSColor=COLOR_Blue;
#endif 
        
        
	
}
/*
������void Clear_Screen()
���ܣ�LCD��������
������COLOR_Cyan��ȫ�ֱ�������ǰϵͳ��������ɫ
����ֵ����
*/

void Clear_Screen()
{
	SetPaintMode(0,COLOR_Cyan);
	Rectangle(1,1+Y_Witch,LCD_X_MAX,LCD_Y_MAX-Y_Witch,1);
}
/*
������void calendar_GUI(u16 x,u16 y,u8 *rdata)
���ܣ�LCD��ʾ�����Ŀؼ�����
������(x,y)Ҫ��ʾ�Ŀؼ����꣬rdata��ʾ�洢ʱ���ȫ�ֱ���ָ��
����ֵ����
*/
void calendar_GUI(u16 x,u16 y,u8 *rdata,u8 TotalFreshEN)
{
	u8 tTime;
	if(TotalFreshEN==1)
	{
		TaskBoxGUI_P(x,y,x+X_Witch_cn*7,y+3+3*Y_Witch_cn,"������Ϣ",0);
		
		SetPaintMode(0,COLOR_Black);
		
		Lcd_disp(x,y+1+Y_Witch_cn,"20  ��  ��  ��");
		Line(x,y+2*X_Witch_cn+1,x+X_Witch_cn*7,y+2*X_Witch_cn+1);
		
		tTime=(rdata[6]/16)*10+rdata[6]%16;  //������
		NumberDis(x+X_Witch*2,y+X_Witch_cn+1,tTime,2,1);
		tTime=(rdata[4]/16)*10+rdata[4]%16;  //������
		NumberDis(x+X_Witch*6,y+X_Witch_cn+1,tTime,2,1);
		tTime=(rdata[3]/16)*10+rdata[3]%16;  //������
		NumberDis(x+X_Witch*10,y+X_Witch_cn+1,tTime,2,1);
		tTime=rdata[5]%16;
		switch(tTime)
		{
		case 1:
			PutString_cn(x,y+2+2*Y_Witch_cn,"����һ");
			break;
		case 2:
			PutString_cn(x,y+2+2*Y_Witch_cn,"���ڶ�");
			break;
		case 3:
			PutString_cn(x,y+2+2*Y_Witch_cn,"������");
			break;
		case 4:
			PutString_cn(x,y+2+2*Y_Witch_cn,"������");
			break;
		case 5:
			PutString_cn(x,y+2+2*Y_Witch_cn,"������");
			break;
		case 6:
			PutString_cn(x,y+2+2*Y_Witch_cn,"����������ĩ");
			break;
		case 7:
			PutString_cn(x,y+2+2*Y_Witch_cn,"�����죬��ĩ");
			break;   
		}
	}
}


void DrawClockPoint(u8 r,u8 x,u8 y,u8 hour,u8 min,u8 sec,u8 Color)
{
	if(Color==1)
		SetPaintMode(0,COLOR_Black);
	else
		SetPaintMode(0,COLOR_White);
	Line(x,y,x+(s8)(r*0.4*sin((float)hour*3.14/6.0)),y-(s8)(r*0.4*cos((float)hour*3.14/6.0)));
	Line(x,y,x+(s8)(r*0.6*sin((float)min*3.14/30.0)),y-(s8)(r*0.6*cos((float)min*3.14/30.0)));
	Line(x,y,x+(s8)(r*0.8*sin((float)sec*3.14/30.0)),y-(s8)(r*0.8*cos((float)sec*3.14/30.0)));
	
}
/*
������void clock_GUI(u16 x,u16 y,u16 r,u8 *rdata,u8 TotalFreshEN)
���ܣ�LCD��ʾʱ���ʱ�ӿؼ�
������(x,y)Ҫ��ʾ�Ŀؼ����Ͻ����꣬rdata��ʾ�洢ʱ���ȫ�ֱ���ָ�룬r��ʾԲ��뾶��ע�ⲻҪ����LCD����Χ
����ֵ����
*/
void clock_GUI(u16 x,u16 y,u16 r,u8 *rdata,u8 TotalFreshEN)
{  
	unsigned char sec,min,hour;
	
	if(TotalFreshEN==1)
	{
		
		CircleShowGUI(x,y,r,COLOR_White);
		TaskBoxGUI_P(x-r,y+r,x+8*6,y+r+2*Y_Witch,"ʱ����Ϣ",0);
		SetPaintMode(0,COLOR_Black);
		
	}
	
	sec=(rdata[0]/16)*10+rdata[0]%16;
	min=(rdata[1]/16)*10+rdata[1]%16;
	hour=(rdata[2]/16)*10+rdata[2]%16;
	SetPaintMode(0,COLOR_White);
	Rectangle(x-r,y+r+X_Witch_cn,x+8*6,y+r+2*X_Witch_cn,1);
	NumberDis(x-r,y+r+X_Witch_cn,hour,2,1);
	NumberDis(x-r+X_Witch*3,y+r+X_Witch_cn,min,2,1);
	NumberDis(x-r+X_Witch*6,y+r+X_Witch_cn,sec,2,1);
	
	DrawClockPoint(r,x,y,hour,min,sec,1);
	delay_ms(1000);
	DrawClockPoint(r,x,y,hour,min,sec,0)  ;  //ˢ�±���
    
}
/*
������void CurveDraw(u16 x,u16 y,u16 Wide,u16 Long,u16 unit,u16 Color,u8 *title,float mount,u16 flag)
���ܣ�LCD��ʾ���߿ؼ���ͼ�κ���
������(x,y)Ҫ��ʾ�Ŀؼ����Ͻ����꣬Wide��ʾ�ؼ���ȣ����¼��㣬���أ���LONG�����ȣ����Ҽ��㣬���أ���Unit��������ʾ��ֵ��COLOR:Ҫ��ʾ����ɫ
title:��ʾ�ı��⣬float:��ʾ����ֵ��flag:��ʾ��λ�ñ��λ����flag==0��ʱ�򣬿ؼ�ȫ��ˢ��
����ֵ��1:��ʾ�ɹ� 0.��ʾʧ��
*/
u8 CurveDraw(u16 x,u16 y,u16 Wide,u16 Long,u16 unit,u16 Color,u8 *title,float mount,u16 flag)
{
	//x,y���Ͻ����꣬wide ��ȣ�long ���ȣ�Uint�����̣�mode=0��ʼ̬
	float t=(float)Wide/2/(float)unit;
	signed int temp=(signed int)(t*mount);
	if(mount>(signed int)unit)
	{
		MessageGui("�ؼ�����","�����������",0);
		return 0;
	}
	
	
	if(flag==0)  //��ʼ̬
	{
		FontSetTotal(COLOR_Black);
		Lcd_disp(x,y,title);
		FontSet(0,COLOR_Black);
		y+=15;
		NumberDis(x,y,unit,2,1);
		NumberDis(x,y+Wide/4,unit/2,2,1);
		NumberDis(x,y+Wide/2,0,3,1);   
		NumberDis(x,y+3*Wide/4,unit/2,2,1);
		NumberDis(x,y+Wide,unit,3,1);
		SetPaintMode(0,COLOR_Black);
		y-=5;
		Rectangle(x+15,y+12,x+X_Witch+Long,y+12+Wide,1);
		SetPaintMode(0,COLOR_White);
		Line(x+15,y+12+Wide/2,x+X_Witch+Long,y+12+Wide/2);
		FontMode(1,COLOR_White);
		
		
	}
	else
	{
		//��ͼ̬
		SetPaintMode(0,Color);
		ShowMountGUI(x+X_Witch_cn*8,y,mount,6, COLOR_Black,1);
		u16 fuck=y+12+Wide/2-temp;
		PutPixel(x+15+flag,fuck+10);
	}
	return 1;
}
/*
������void DrawTitle(u16 x,u16 y,u8* mTitle,u8 Type,u8 style)
���ܣ��˵����ӹ��ܺ��������ڲ������׵�����
������(x,y)Ҫ��ʾ�Ŀؼ����Ͻ����꣬Index��ʾ���Ӳ˵��б��еľ���λ�ã�TYPEΪ����ѡ��0�����ף�1���ף�mTitleҪ��ʾ���ַ���style������Ĭ��Ϊ0
����ֵ����
*/
u8 DrawTitle(u16 x,u16 y,u8* mTitle,u8 Type,u8 style,u8 FreshEN)

{  
	if(FreshEN==0)
		return 0;
	//TYPE����ѡ������Ƿ񷴰ף�0�����ף�1����
	if (Type==0)    
	{
		FontMode(0,OSColor);
		FontSetTotal(COLOR_Red);
		
	}
	else
	{
		FontMode(1,OSColor);
		FontSetTotal(COLOR_White);
	}
	switch(style)
	{
	case 0:
		
		Lcd_disp(x,y,mTitle);
		break;
		
		
	}
	return 1;
	
	
	
	
}
/*
������void DrawIconAndTitle(u16 x,u16 y,u8 Index, u8 PictSize,u8 Type,u8 TitleOrPict)
���ܣ����˵�������Ӻ��������ڲ�������
������(x,y)Ҫ��ʾ�Ŀؼ����Ͻ����꣬Index��ʾ���Ӳ˵��б��еľ���λ�ã�PictSizeΪҪ��ʾ��ͼƬ��С��TYPEΪ����ѡ��0�����ף�1����,TitleOrPict������д�ֻ�ͼ���������Ը���
����ֵ����
*/
void DrawIconAndTitle(u16 x,u16 y,u8 Index, u8 PictSize,u8 Type,u8 TitleOrPict)

{  
	
	u8* mTitle=myTaskPCB[myTaskPCB[OS_index_data].SubTaskList[Index+2]].Name;
	u8* mDetail=myTaskPCB[myTaskPCB[OS_index_data].SubTaskList[Index+2]].Detail;
	//TYPE����ѡ������Ƿ񷴰ף�0�����ף�1����
	if (Type==0)    
	{
		FontMode(1,COLOR_White);
		FontSetTotal(COLOR_Red);
		
	}
	else
	{
		FontMode(1,OSColor);
		FontSetTotal(COLOR_White);
	}
	switch(MenuType)
	{
	case 0:
		if(TitleOrPict==1)
			PutBitmap(x,y,myTaskPCB[myTaskPCB[OS_index_data].SubTaskList[Index+2]].PicIndex,0);
		else
		{
			Lcd_disp(x+PictSize,y,mTitle);
			FontSetTotal(COLOR_Black);
			FontMode(0,COLOR_White);	
			
			Lcd_disp(x+65,y+Y_Witch_cn,mDetail);
		}
		
		
		break;
	case 1:
		if(TitleOrPict==0)
		{
			Lcd_disp(x,y,mTitle);
			
			FontSetTotal(COLOR_Black);	
			FontMode(0,COLOR_White);	
			Lcd_disp(x+7*X_Witch_cn,y,mDetail);
			Line(x,y+Y_Witch_cn,x+18*X_Witch_cn,y+Y_Witch_cn);
		}
		break;
	case 2:
	       
		if(TitleOrPict==1) 
			PutBitmap(x,y,myTaskPCB[myTaskPCB[OS_index_data].SubTaskList[Index+2]].PicIndex,0);
		else 
			Lcd_disp(x,y+65,mTitle);
		break;
	case 3:
		
		Lcd_disp(x,y+PictSize,mTitle);
		break;
		
		
	}
	
	
	
	
}

u8  MenuDataRefreshGUI(u8 MenuFlag,u8 MaxMount,u8 flag,u8 LastFlag,u8 LRMaxMount,u8 UDMaxMount,u8 OneLRLength,u8 OneUDLength,u8 FreshEN,u8 TotalFreshEN)
{
	if(!FreshEN)
		return 0;
	if(TotalFreshEN)
	{
		
		SetPaintMode(0,COLOR_White);
		Rectangle(X_Witch_cn+1,2*Y_Witch_cn,Dis_X_MAX-X_Witch_cn-1,Dis_Y_MAX-Y_Witch_cn-1,1);
		
		//ȫ�ֲ˵����޷������ʾ
		SetPaintMode(0,COLOR_Black);
		
		for(u8 TitleORPictFlag=0;TitleORPictFlag<2;TitleORPictFlag++)
			for (u8 UDflag=0;UDflag<UDMaxMount;UDflag++)
			{
				for(u8 LRflag=0;LRflag<LRMaxMount;LRflag++)
				{
					if (MenuFlag-1+UDflag*LRMaxMount+LRflag>=MaxMount)
					{
						break;
					}
					DrawIconAndTitle(X_Witch_cn+1+LRflag*OneLRLength,2*Y_Witch_cn+UDflag*OneUDLength,MenuFlag-1+UDflag*LRMaxMount+LRflag,OneUDLength,LRflag+UDflag*LRMaxMount+1==flag?1:0,TitleORPictFlag);
					
				}
			}
	}
	else
	{
		u8 UDflag,LRflag;
		for(u8 i=0;i<2;i++)
		{
			
			
			if(i==1)
			{
				UDflag	=(flag-1)/LRMaxMount;
				LRflag=flag-1-UDflag*LRMaxMount;
			}
			else
			{
				UDflag	=(LastFlag-1)/LRMaxMount;
				LRflag=LastFlag-1-UDflag*LRMaxMount;
				
			}
			
			DrawIconAndTitle(X_Witch_cn+1+LRflag*OneLRLength,2*Y_Witch_cn+UDflag*OneUDLength,MenuFlag-1+UDflag*LRMaxMount+LRflag,OneUDLength,i,0);
		}	
	}
	return 1;
}
/*
u8 UpdownListInputControl(u8 *Menuflag,u8 *ThisPageflag,u8 *TotolFlag,u8 *ThisPageMax)
���ܣ��˵�������Ʒ����������������͵Ĳ˵�
������Menuflag��ȫҳ���־��������ThisPageflag��ǰҳ���־��������TotolFlag��ҳ��������ThisPageMax��ǰҳ���������,PromptEN���Ƿ���ʾ��Ŀ¼ͷ���߽�β
����ֵ��0���˳� 1�� ȷ�ϣ�2������ѡ�����ƶ�λ��
*/

u8 UpdownListInputControl(u8 *Menuflag,u8 *ThisPageflag,u8 TotolFlag,u8 ThisPageLRMax, u8 ThisPageUDMax,u8 PromptEN,u8 *FreshEN,u8* TotalFreshEN)
{
	u8 LastMenuFlag=*Menuflag;
	u8 PromptFlag=0;
	u8 GyroKey=KEYNULL;
	*FreshEN=0;
	u8 myKey=KEYNULL;
	if(GyroControlEN==1)
		PromptEN=0; //���������ݼ��ʱ���ر���ʾ
	if(GyroControlEN==1&&back_light>1&&GyroMenuEN)
	{
		
		delay_ms(300-20*TotolFlag);
		L3G4200DReadData();
		L3G4200DShowData();
		
		delay_ms(300-20*TotolFlag);
	}
	
	else
		InputControl(); 
	if(GyroMenuEN!=0)
        GyroKey=GyroKeyBoardInputMethod(0,1,300-30*ThisPageLRMax,300-20*ThisPageUDMax);
	
	if(GyroKey!=KEYNULL)
		myKey=GyroKey;
	else
		myKey=key_data;
	GyroKey=KEYNULL;
	
	switch(myKey)
	{  
	case KEYENTER_UP   :
		
		return 1;
		//break;
		
	case KEYUP_UP  :
		if(*ThisPageflag>ThisPageLRMax)
			(*ThisPageflag)-=ThisPageLRMax;
		else
		{if(*Menuflag>ThisPageLRMax)
		(*Menuflag)-=ThisPageLRMax;
		else
			if(*ThisPageflag==1&&PromptEN)
			{
				PromptFlag=1;
				MessageGui("��ʾ��Ϣ","�ѵ�Ŀ¼��ͷ",2);
			}
			//else 
			//*ThisPageflag=1;
		}	
		break;
	case KEYDOWN_UP  :
		if(*ThisPageflag<=ThisPageLRMax*(ThisPageUDMax-1)&&*ThisPageflag+ThisPageLRMax<=TotolFlag)
			(*ThisPageflag)+=ThisPageLRMax;
		else
		{if(*Menuflag+*ThisPageflag-1<=TotolFlag-ThisPageLRMax)
		(*Menuflag)+=ThisPageLRMax;
		else
		{
			if(TotolFlag==*ThisPageflag&&PromptEN)
			{
				PromptFlag=1;
				MessageGui("��ʾ��Ϣ","�ѵ�Ŀ¼��β",2);
				
			}
			//else
			//*ThisPageflag= TotolFlag-*Menuflag+1;
		}
		}
		break;
    case  KEYLEFT_UP    :
		if(*ThisPageflag>1)
			(*ThisPageflag)--;
		else
		{if(*Menuflag>1)
		(*Menuflag)--;
		else
			if(PromptEN)
			{
				MessageGui("��ʾ��Ϣ","�ѵ�Ŀ¼��ͷ",2);
				PromptFlag=1;
			}
		}
		
		break;
	case KEYRIGHT_UP  :
		if(*ThisPageflag<TotolFlag)
			(*ThisPageflag)++;
		else
		{if(*Menuflag+*ThisPageflag-1<TotolFlag)
		(*Menuflag)++;
		else
			if(PromptEN)
			{
				MessageGui("��ʾ��Ϣ","�ѵ�Ŀ¼��β",2);
				PromptFlag=1;
			}
		}
		break;
		
	case KEYCANCEL_UP    :
		
		return 0;
	} 
	if(key_data!=KEYNULL)
		*FreshEN=1;
	
	if(LastMenuFlag==*Menuflag&&PromptFlag==0)
		*TotalFreshEN=0;
	else
		*TotalFreshEN=1;
	return 2;
	
}

u8  GyroKeyBoardInputMethod(u8 HeadDirectionDefine,u8 CancelEN,float Xthreshold,float Ythreshold)
{
	//HeadDirectionDefine  ���豸����Ϊ׼������Ϊ0������Ϊ1
	u8 key=KEYNULL;
	if(GyroControlEN==0||back_light<2)
		return KEYNULL;
	if (HeadDirectionDefine==0)
	{
		
		if (GyroX>Xthreshold)
		{
			key=KEYRIGHT_UP  ;
		}
		else if(GyroX<-Xthreshold)
			key=KEYLEFT_UP    ;
		if (GyroY>Ythreshold)
		{
			key=KEYUP_UP  ;
		}
		else if(GyroY<-Ythreshold)
		{
			key=KEYDOWN_UP  ;
		}
		if(CancelEN==1&&GyroZ>1800)
			key=KEYCANCEL_UP  ;
		
	}
	else
	{
		if (GyroY>Ythreshold)
		{
			key=KEYLEFT_UP    ;
		}
		else if(GyroY<-Ythreshold)
		{
			key=KEYRIGHT_UP  ;
		}
		if (GyroX>Xthreshold)
		{
			key=KEYDOWN_UP  ;
		}
		else if(GyroX<-Xthreshold)
			key=KEYUP_UP  ;
		
		
	}
	return key;
	
}
/*
������u8  MainMenuListGUI()
���ܣ����˵�����ĺ����������ͼ�ͺͻ���û�ѡ��
��������
����ֵ���̶�����1
*/
u8  MainMenuListGUI(u8 LRMaxMount,u8 UDMaxMount,u8 OneLRLength,u8 OneUDLength)
{
	
	if (myTaskPCB[OS_index_data].function!=MenuGUI)
	{
		return 0;
	}
	
	u8 MaxMount=myTaskPCB[OS_index_data].SubTaskList[1];
	
	u8 func_state=0,menu_flag=1,LastFlag,TotalFreshEN=1,flag=1,FreshEN=1;
	
	if(func_state==0)
	{
		
		
		TaskBoxGUI_P(X_Witch_cn,Y_Witch_cn,Dis_X_MAX-X_Witch_cn,Dis_Y_MAX-Y_Witch_cn-3,(u8 *)myTaskPCB[OS_index_data].Name,0);
		func_state=1;
		
	}
	while(func_state==1)
		
	{     
		
		MenuDataRefreshGUI( menu_flag, MaxMount, flag, LastFlag, LRMaxMount,UDMaxMount, OneLRLength, OneUDLength,FreshEN,TotalFreshEN);
		LastFlag=flag;
		switch(UpdownListInputControl(&menu_flag,&flag,MaxMount,LRMaxMount,UDMaxMount,1,&FreshEN,&TotalFreshEN))
		{
		case 0:
			OSTaskClose();
			func_state=2;
			return 1;
			
		case 1:
			func_state=2;
			break;
			
			
		}
		
		
	}		
	OS_index_data= myTaskPCB[OS_index_data].SubTaskList[menu_flag+flag];
	return 1;	
	
}
/*
������u8 SliderGUI(u16 x,u16 y,u16 Length,u8* title,u16 RangeLow,u16 RangeHigh,u8 step,u16* Data)
���ܣ�����ģʽ����ֵѡ��ؼ�
������(x,y)�ؼ����Ͻ����꣬length����ʾ�Ŀؼ����ȣ������ң�,RangeLow:��ֵ��Ϳ�ѡֵ��RangeHigh:��ֵ��߿�ѡֵ��step������ѡ�񲽽���data:�洢���ݵ�ָ��
����ֵ��0:�ؼ�������û�ȡ��ѡ��1���û��ɹ�ʹ�ÿؼ������ݴ���data��
*/
u8 SliderGUI(u16 x,u16 y,u16 Length,u8* title,u16 RangeLow,u16 RangeHigh,u8 step,u16* Data)
{ 
	u16 OriginData=*Data; //����ԭʼ��������Ϣ������ʱ���Իָ�
	u8 fuck;
	if (*Data>RangeHigh||*Data<RangeLow)
	{
		MessageGui("��ʾ��Ϣ���������","ԭʼֵ�����������С",0);
		*Data=RangeLow;
		return 0;
	}
	TaskBoxGUI_P(x,y,x+Length+2*X_Witch,y+4*Y_Witch_cn,title,1);
	FontMode(1,COLOR_White);
	Lcd_disp(x+X_Witch,y+Y_Witch_cn+1,"��ǰ��ֵ");
	delay_ms(5);
	
	NumberDis(x+X_Witch,y+3*Y_Witch_cn,RangeLow,3,2);
	NumberDis(x+Length-2*X_Witch_cn,y+3*Y_Witch_cn,RangeHigh,3,2);
	
	while (1)
	{
		
		NumberDis(x+Length/2,y+Y_Witch_cn+1,*Data,3,2);
		
		SetPaintMode(0,COLOR_Red);
		Rectangle(x+X_Witch,y+2*Y_Witch_cn+X_Witch,x+X_Witch+Length,y+2*Y_Witch_cn+X_Witch+1,1);
		Rectangle(x+X_Witch+Length*(*Data-RangeLow)/(RangeHigh-RangeLow)-2,y+2*Y_Witch_cn+X_Witch-4,x+X_Witch+Length*(*Data-RangeLow)/(RangeHigh-RangeLow)+2,y+2*Y_Witch_cn+X_Witch+4,1);
		
		InputControl();
		SetPaintMode(0,COLOR_White);   //���ԭ���ķ���
		Rectangle(x+X_Witch+Length*(*Data-RangeLow)/(RangeHigh-RangeLow)-2,y+2*Y_Witch_cn+X_Witch-4,x+X_Witch+Length*(*Data-RangeLow)/(RangeHigh-RangeLow)+2,y+2*Y_Witch_cn+X_Witch+4,1);
		switch(key_data)
		{
			
		case KEYENTER_UP   :
			return 1;
		case KEYCANCEL_UP    :
			MessageGui("��ʾ��Ϣ","�ѷ�������",0);
			*Data=OriginData;
			return 0;
		default:
			FourDirectionInputMethod(key_data,1,0,step,1,RangeLow,RangeHigh,0,3,0,0,(u8*)Data,&fuck);
			break;
		}
		
	}
	
	
}
/*
������u8 VirtualFullKeyBoardInput(u16 x,u16 y,u8* KeyX,u8* KeyY,u8 *Key)
���ܣ�����ȫ���̵������Ӻ���
������(x,y)�ؼ����Ͻ����꣬KeyX,KeyY��ʾ��ǰ�����ּ����ϵ�X,Y����λ�ã���Χ�ֱ�Ϊ0-10,0-4��KeyΪ���ص�ѡ�������μ�FullKeyBoardData[]��������
����ֵ��0:�û�������ѡ�����⹦�ܼ���1���û�ѡ������ͨ���ַ������÷��μ��������
*/

u8 VirtualFullKeyBoardInput(u16 x,u16 y,u8* KeyX,u8* KeyY,u8 *Key)
{
	InnerFuncState=1;
	u8 GyroKey;
	
	while(InnerFuncState==1)
	{
		
		key_data=KEYNULL;
		SetPaintMode(0,COLOR_Red);
		Rectangle(x+5+*KeyX*21,y+LCD_Y_MAX-Y_Witch_cn-127+*KeyY*21,x+5+*KeyX*21+21,y+LCD_Y_MAX-Y_Witch_cn-127+*KeyY*21+21,0);
		if(GyroControlEN==1)
		{
			L3G4200DReadData();
			L3G4200DShowData();
			
			delay_ms(150);
		}
		
		else
			
			InputControl();
		
		GyroKey=GyroKeyBoardInputMethod(0,1,100,300);
		if(GyroKey!=KEYNULL)
			key_data=GyroKey;
		GyroKey=KEYNULL;
		
		SetPaintMode(0,COLOR_Black);
		Rectangle(x+5+*KeyX*21,y+LCD_Y_MAX-Y_Witch_cn-127+*KeyY*21,x+5+*KeyX*21+21,y+LCD_Y_MAX-Y_Witch_cn-127+*KeyY*21+21,0);
		
		switch(key_data)
		{
		case  KEYCANCEL_UP   :
			*Key=0;
			return 0;   //�˸��
		case  KEYENTER_UP   :
			if (*KeyY*11+*KeyX==43)
			{
				*Key=1;
				return 0;   //�˸��
			}
			
			else
				
				*Key=FullKeyBoardData[*KeyY*11+*KeyX];
			return 1;
		default:
			FourDirectionInputMethod(key_data,1,1,1,1,0,10,0,3,1,0,KeyX,KeyY);
			break;
		}
		
	}	
	return 1;
}

/*
u8 VirtualFullKeyBoard(u16 x,u16 y,u8 *Buff,u8 *BuffFlag,u8 Max)
���ܣ�����ȫ���̵����뺯��
������(x,y)�ؼ����Ͻ����꣬BuffΪ�洢�������ݵ����飬BuffFlagΪ��ǰ�洢�����鳤�ȣ�MaxΪ����ɵõ������̬����
����ֵ��0:�û�����1���û�ѡ����ȷ��
*/

u8 VirtualFullKeyBoard(u16 x,u16 y,u8 *Buff,u8 *BuffFlag,u8 Max)
{
	u8 InputKey;
	
	u8 mkeyx=5,mkey=2;
	//�������
	if (x>LCD_X_MAX-240)
	{
		x=LCD_X_MAX-242;
	}
	if (y>LCD_Y_MAX-95)
		
	{
		y=LCD_Y_MAX-97;
	}
	
	TaskBoxGUI_P(x+3,y+Y_Witch_cn+2,x+243,y+LCD_Y_MAX-3*Y_Witch_cn-2,"����ȫ��������",0);
	FontMode(1,COLOR_White);
	FontSetTotal(COLOR_Black);
	PutBitmap(3+x,y+LCD_Y_MAX-3*Y_Witch_cn-97,VKFULL,0);
	SetPaintMode(0,OSColor);
	//�������ݹ���
	InnerFuncState=1;
	while(InnerFuncState)
	{
		if (	VirtualFullKeyBoardInput(x,y,&mkeyx,&mkey,&InputKey))   //���������ַ�
		{
			*(Buff+*BuffFlag)=InputKey;
			if((*BuffFlag)<Max)
				(*BuffFlag)++;
		}
		else
		{
			switch(InputKey)
			{
				
				
			case 0:
				if(MessageGui("��ʾ��Ϣ","������룿",1))
					return 1;
				else
					return 0;
				
			case 1:
				if(*BuffFlag>0)
				{
					SetPaintMode(0,COLOR_White);
					Rectangle(x+5+X_Witch*(*BuffFlag),y+3*Y_Witch_cn+3,x+5+X_Witch*(*BuffFlag)+X_Witch,y+4*X_Witch+2,1);
					SetPaintMode(0,OSColor);
					
					(*BuffFlag)--;
				}
				
				break;
			}
			
			
			
		}
		
		Rectangle(x+5+X_Witch*(*BuffFlag),y+3*Y_Witch_cn+3,x+5+X_Witch*(*BuffFlag)+X_Witch,y+4*X_Witch+2,1);
		PutString_limit(x+5,y+2*Y_Witch_cn+3,Buff,*BuffFlag);
		delay_ms(40);
	}
	return 1;
	
}

/*
������u8 PictureShowBox(u8 x,u8 y,u8* title)
���ܣ�ͼƬ��ʾ�ؼ�
������(x,y)�ؼ����Ͻ����꣬*titileΪ��ʾ�ı���
����ֵ��0:�����ÿؼ���1������
ע������ú��������Ժܴ��ڲ�����Index��������LCD�����д洢��ͼƬλ�ã������ܳ�������Χ����������
*/
u8 PictureShowBox(u16 x,u16 y,u8* title)
{
	u8 Index=6;
	u8 FUCK;
	//���ķ�Χֻ�ܴﵽ240��160
	TaskBoxGUI_P(x,y,x+240,y+160,title,0);
	
	InnerFuncState=1;
	while(InnerFuncState)
	{
		SetPaintMode(0,COLOR_White);
		Rectangle(x,y+Y_Witch_cn,x+239,y+159,1);
		PutBitmap(x,y+Y_Witch_cn,Index,0);
		if(GyroControlEN==1)
		{
			L3G4200DReadData();
			L3G4200DShowData();
			delay_ms(1000);
		}
		
		else
			InputControl();
		if(GyroControlEN==1)
		{
			if(GyroZ>600)
				key_data=KEYUP_UP  ;
			else if(GyroZ<-600)
				key_data=KEYDOWN_UP  ;
			
		}
		switch(key_data)
		{
            
		case KEYCANCEL_UP    :
			if(MessageGui("��ʾ��Ϣ","�Ƿ��˳�ͼƬ���",1))
			{
				return 0;
			}
			else
				break;
		case KEYENTER_UP   :
			break;
		default:
			FourDirectionInputMethod(key_data,0,1,1,1,6,25,6,25,0,1,&FUCK,&Index);
			break;
		}
		
		key_data=KEYNULL;
	}
	return 1;
	
}
/*
������u8 CircleShowGUI(u16 x,u16 y, u8 r,LCDBYTE COLOR)
���ܣ���ʾһ��Բ��
��������
����ֵ���̶�Ϊ1
ע������ų�������δ�ɹ����ԣ��ù��ܲ�����
*/

u8 CircleShowGUI(u16 x,u16 y, u8 r,LCDBYTE COLOR)   //ָ����ͼ�ν���
{ 
	
	SetPaintMode(0,COLOR_Black);
	Circle(x+2,y+2,r,1);
	SetPaintMode(0,COLOR);
	Circle(x,y,r,1);
	SetPaintMode(0,COLOR_Black);
	Circle(x,y,r,0);
	return 1;
	
}
/*
u8 VirtualFullKeyBoard(u16 x,u16 y,u8 *Buff,u8 *BuffFlag,u8 Max)
���ܣ��������ּ��̵������뺯��
������(x,y)�ؼ����Ͻ����꣬KeyX,KeyY��ʾ��ǰ�����ּ����ϵ�X,Y����λ�ã���Χ�ֱ�Ϊ0-2,0-3��KeyΪ���ص�ѡ�������μ�NumKeyBoardData[]��������
����ֵ��0:�û�������ѡ�����⹦�ܼ���1���û�ѡ������ͨ���ַ������÷��μ��������
*/
u8 VirtualNumKeyBoardInput(u16 x,u16 y,u8* KeyX,u8* KeyY,u8 *Key,u8 FuncEN,u8 HardKeyTransEN)  //Ox,oy ��ԭʼ��x,y����ֵ
{
	u8 GyroKey;
	while(1)
	{
		key_data=KEYNULL;
		SetPaintMode(0,COLOR_Red);
		Rectangle(x+2+*KeyX*31,y+2*Y_Witch_cn+3+*KeyY*27,x+2+*KeyX*31+31,y+2*Y_Witch_cn+*KeyY*27+30,0);
		if(GyroControlEN==1)
		{
			L3G4200DReadData();
			L3G4200DShowData();
			delay_ms(150);
		}
		
		else
			
			InputControl();
		if(key_data==KEYNULL)
			GyroKey=GyroKeyBoardInputMethod(0,1,300,300);
		else
		{
			if(key_data!=KEYENTER_UP&&key_data!=KEYCANCEL_UP)
			{
				if(HardKeyTransEN&&GyroControlEN)
				{
                                        *Key=key_data;
					return 2;  
				}
			}
		}
		if(GyroKey!=KEYNULL)
			key_data=GyroKey;
		GyroKey=KEYNULL;
		
		
		SetPaintMode(0,COLOR_Black);
		Rectangle(x+2+*KeyX*31,y+2*Y_Witch_cn+3+*KeyY*27,x+2+*KeyX*31+31,y+2*Y_Witch_cn+*KeyY*27+30,0);
		
		switch(key_data)
		{
		case KEYCANCEL_UP    :
			*Key=0;   //����̬
			return 0;
		case KEYENTER_UP   :
			if(FuncEN==1)
				switch(*KeyX+*KeyY*3)
			{
		case 9:
			
			*Key=1;
			return 0;  //ȷ��̬
			
		case 11:
			
			*Key=2;  //ɾ��̬
			return 0;
			
		default:
			*Key=NumKeyBoardData[*KeyX+*KeyY*3];
			return 1;
			}
			else
			{
				*Key=*KeyX+*KeyY*3;
				return 1;
			}
			
		default:
			FourDirectionInputMethod(key_data,1,1,1,1,0,2,0,3,0,0, KeyX,  KeyY);
			break;
		}
		
	}
	
	
}
/*
u8 VirtualFullKeyBoard(u16 x,u16 y,u8 *Buff,u8 *BuffFlag,u8 Max)
���ܣ��������ּ��̵����뺯��
������(x,y)�ؼ����Ͻ����꣬BuffΪ�洢�������ݵ����飬BuffFlagΪ��ǰ�洢�����鳤�ȣ�MaxΪ����ɵõ������̬����
����ֵ��0:�û�����1���û�ѡ����ȷ��
*/
u8 VirtualNumKeyBoard(u16 x,u16 y,u8 *Buff,u8 *BuffFlag,u8 Max,u8 *title)

{
	u8 mkeyx=1,mkey=2,InputKey;
	if (x>LCD_X_MAX-100)
	{
		x=LCD_X_MAX-100;
	}
	if (y>50)
	{
		y=50;
	}
	TaskBoxGUI_P(x,y,x+100,y+2*Y_Witch_cn+108,title,0);
	PutBitmap(x,y+2*Y_Witch,VKNUM,0);
	FontMode(1,COLOR_White);
	InnerFuncState=1;
	while (InnerFuncState)
	{
		if (VirtualNumKeyBoardInput(x,y,&mkeyx,&mkey,&InputKey,1,0))
		{
			*(Buff+*BuffFlag)=InputKey;
			if((*BuffFlag)<Max)
				(*BuffFlag)++;
		} 
		else
		{
			switch(InputKey)
			{
			case 0:
				MessageGui("��ʾ��Ϣ","������",0);
				return 0;
			case 2:
				if(*BuffFlag>0)
				{
					SetPaintMode(0,COLOR_White);
					Rectangle(x+5+X_Witch*(*BuffFlag),y+Y_Witch_cn,x+5+X_Witch*(*BuffFlag)+X_Witch,y+2*Y_Witch_cn,1);
					SetPaintMode(0,OSColor);
					(*BuffFlag)--;
				}
				break;
			case 1:
				return 1;
			}
		}
		
		Rectangle(x+5+X_Witch*(*BuffFlag),y+Y_Witch_cn,x+5+X_Witch*(*BuffFlag)+X_Witch,y+2*Y_Witch_cn,1);
		PutString_limit(x+5,y+Y_Witch_cn,Buff,*BuffFlag);
	}
	return 1;
	
	
}
/*
������u8 InputLongNum(u8* title,long *LData)
���ܣ����볤�������ֵ�ͼ�οؼ�
������title���⣬LDataҪ���������
����ֵ��0:�û�����1���û���������������
*/
u8 InputLongNum(u8* title,long *LData)
{
	u8 Num[8];
	*LData=0;
	long Ltemp;
	u8 Flag=0,mTemp=0;
	
	if(!VirtualNumKeyBoard(30,80,Num,&Flag,8,title))
		return 0;
	
	mTemp=Flag;
	while(Flag>0)
	{
		Ltemp=(long)pow(10,mTemp-Flag);
		*LData+=(Num[Flag-1]-0X30)*Ltemp;
		Flag--;
		
	}
	return 1;
}
/*
������u8 PassWordCheck()
���ܣ����ּ�麯����Ҫ���û��������֣�����ԭ�е����ֱȽ�
��������
����ֵ��0�������ֲ�ͬ��1��������ͬ��
*/
u8 PassWordCheck()
{
	long temp=0;
	while(1)
	{
		if(!	InputLongNum("����������",&temp))
		{
			MessageGui("��ʾ��Ϣ","���ݸ�ʽ����",0);
			
		}
		else
		{
			if (temp==mPassWord)
			{
				MessageGui("��ϲ","������ȷ",0)	;
				return 1;
			} 
			else
			{	MessageGui("��ʾ��Ϣ","��������",0);
			}
		}
		
	}
	
}
/*
������u8 HistogramGUI(u8** List,u16* Num,u8 num,u8* title)
���ܣ���ʾ��״ͼ�ؼ�
������List,�洢��ͬ���������飬Num�洢��ͬ�����ֵ�����飬numҪ��ʾ�����������title�ؼ�����
����ֵ��0�������ֲ�ͬ��1��������ͬ��
*/
u8 HistogramGUI(u8** List,u16* Num,u8 num,u8* title)
{
	u16 MaxNum=0;
	
	u16 XStep=270/(num+1);  //X����
	if (num>4)
	{
		num=4;
	}
	for(u8 i=0;i<num;i++)
	{
		MaxNum=MaxNum>Num[i]?MaxNum:Num[i];
	}
	u16 RangeHigh=(u16)(1.2*MaxNum);
	TaskBoxGUI(title);
	SetPaintMode(0,COLOR_Black);
	Line(15,48,15,170);
	Line(15,170,289,170);
	SetPaintMode(0,COLOR_Red);
	FontSet_cn(0,COLOR_Black);
	for (u8 i=0;i<num;i++)
	{
		Lcd_disp(60+i*XStep-20,172,List[i]);
		Rectangle(50+i*XStep,170-(u16)(((float)Num[i]/(float)MaxNum)*(float)RangeHigh),80+i*XStep,170,1);
		NumberDis(50+i*XStep,190-(u16)(((float)Num[i]/(float)MaxNum)*(float)RangeHigh),Num[i],3,2);
	}
	
	
	InputControl();
	return 1;
	
}

u8 TimeSetGUI()
{
#if PCID==1
	if(!MessageGui("ʱ��Ӳ��������","�Ƿ������",1))
		return 0;
#endif
	if (!MessageGui("ȷ���޸�ʱ�䣿","�Ƿ������",1))
		return 0;
	u16 TimeTemp=1;
	
	if(!SliderGUI(20,40,150,"���",1,60,1,&TimeTemp))
		return 0;
	rdata[6]=DecToHexFunc(TimeTemp);
	TimeTemp=1;
	if(!SliderGUI(20,100,150,"����",1,7,1,&TimeTemp))
		return 0;
	
	rdata[5]=DecToHexFunc(TimeTemp);
	TimeTemp=1;
	if(!SliderGUI(20,160,150,"�·�",1,12,1,&TimeTemp))
		return 0;
	rdata[4]=DecToHexFunc(TimeTemp);
	TimeTemp=1;
	if(!SliderGUI(20,40,150,"����",1,31,1,&TimeTemp))
		return 0;
	rdata[3]=DecToHexFunc(TimeTemp);
	TimeTemp=1;
	if(!SliderGUI(20,100,150,"Сʱ",1,24,1,&TimeTemp))
		return 0;
	rdata[2]=DecToHexFunc(TimeTemp);
	TimeTemp=1;
	if(!SliderGUI(20,160,150,"����",1,60,1,&TimeTemp))
		return 0;
	rdata[1]=DecToHexFunc(TimeTemp);
	rdata[0]=0;
	if(MessageGui("Ҫд��ʱ����Ϣ��","�Ƿ������",1))     
	{
		Set_DS1302(rdata);
		return 1;
	}
	else
	{
		return 0;
	}
	
	
}





u8 KeyBoardFuncIntroGUI(u8 HandleID,u8 *KeyUp,u8 *KeyDown,u8 *KeyLeft,u8 *KeyRight,u8 *KeyEnter,u8* KeyEsc)
{   
  u8  *Title;
switch(HandleID)
{
case 0:
	Title="����������λ��";
	break;
case 1:
	Title="�ӿ�������λ��";
	break;
default:
	return 0;
} 
TaskBoxGUI_P(1,LCD_Y_MAX-(5-2*HandleID)*Y_Witch_cn,LCD_X_MAX,LCD_Y_MAX-(3-2*HandleID)*Y_Witch_cn,Title,1);
FontMode(0,OSColor);

Lcd_disp(0,LCD_Y_MAX-(4-2*HandleID)*Y_Witch_cn,KeyUp);
Lcd_disp(3*X_Witch_cn*1,LCD_Y_MAX-(4-2*HandleID)*Y_Witch_cn,KeyDown);

Lcd_disp(3*X_Witch_cn*2,LCD_Y_MAX-(4-2*HandleID)*Y_Witch_cn,KeyLeft);
Lcd_disp(3*X_Witch_cn*3,LCD_Y_MAX-(4-2*HandleID)*Y_Witch_cn,KeyRight);
Lcd_disp(3*X_Witch_cn*4,LCD_Y_MAX-(4-2*HandleID)*Y_Witch_cn,KeyEnter);
Lcd_disp(3*X_Witch_cn*5,LCD_Y_MAX-(4-2*HandleID)*Y_Witch_cn,KeyEsc);

InputControl();
return 1;




}

u8 FourDirectionInputMethod(u8 key,u8 LREN,u8 UDEN,u8 LRStep,u8 UDStep,u8 LRMin,u16 LRMAX,u8 UDMin,u8 UDMax,u8 CircleEN,u8 PromtEN,u8 *KeyX,u8 *KeyY)
{
	
    if(key==KEYRIGHT_UP||key==KEYLEFT_UP)
		if(!LREN)
			return 0;
		if(key==KEYUP_UP||key==KEYDOWN_UP)
			if(!UDEN)
				return 0;
			switch(key)
			{
			case KEYRIGHT_UP  :
				if (*KeyX+LRStep<=LRMAX)
				{
					(*KeyX)+=LRStep;
				} 
				else
				{
					if (CircleEN)
					{
						(*KeyX)=LRMin;
					}
					if(PromtEN)
						MessageGui("��ʾ��Ϣ","�ѵ�Ŀ¼���",2);
					
				}
				break;
			case KEYLEFT_UP :
				if ((*KeyX)-LRStep>=LRMin)
				{
					(*KeyX)-=LRStep;
				} 
				else
				{
					if (CircleEN)
					{
						(*KeyX)=LRMAX;
					}
					if(PromtEN)
						MessageGui("��ʾ��Ϣ","�ѵ�Ŀ¼��ǰ",2);
					
					
				}
				break;
			case KEYDOWN_UP:
				if ((*KeyY)+UDStep<=UDMax)
				{
					(*KeyY)+=UDStep;
				} 
				else
				{
					if(CircleEN)
						(*KeyY)=UDMin;
					if(PromtEN)
						MessageGui("��ʾ��Ϣ","�ѵ�Ŀ¼���",2);
					
				}
				break;
			case KEYUP_UP  :
				if ((*KeyY)-UDStep>=UDMin)
				{
					(*KeyY)-=UDStep;
				} 
				else
				{
					if(CircleEN)
						(*KeyY)=UDMax;
					if(PromtEN)
						MessageGui("��ʾ��Ϣ","�ѵ�Ŀ¼��ǰ",2);
				}
				break;
				
				
			}
			return 1;
}




#include "config.h"
u8 time_show()
{
      u8 TotalFreshEN=1;
	
	TaskBoxGUI("ʱ�Ӻ�������ʾ");
	OS_func_state=1;

	while(OS_func_state==1)
	{

		Get_DS1302(rdata);

		clock_GUI(80,90,60,rdata,TotalFreshEN);
		calendar_GUI(150,3*X_Witch_cn,rdata,TotalFreshEN);
                TotalFreshEN=0;
    
        if(key_data==KEYCANCEL_UP    )
        {
            OSTaskClose();
            return 0;
        }
	}
	
	return 1;
}



u8 AccShow()
{
	u8* temp[4];
	
	u8 AccRange=0;
	u16 flag=0;
	temp[0]="2G�߾���ģʽ";
	temp[1]="4G���";
	temp[2]="8G�߷�Χ���";
	temp[3]="16G���߷�Χ���";
	u8 mUnit[4]={20,40,80,160};
	AccRange=ListGUI(temp,"��ѡ������",4);
	if (AccRange==0)
	{
		OSTaskClose();
		return 0;
	}
	TaskBoxGUI_P(2,X_Witch_cn,307,224,temp[AccRange-1],0);
	ADXL345Init(AccRange-1);
	OS_func_state=1;
	
	while (OS_func_state==1)
	{
		ADXL345ReadData();
		ADXL345ShowData(AccRange-1);
		CurveDraw(20,2*X_Witch_cn,40,200,mUnit[AccRange-1],COLOR_Red,"x����ٶ�",AccX,flag);
		CurveDraw(20,2*X_Witch_cn+65,40,200,mUnit[AccRange-1],COLOR_Blue,"y����ٶ�",AccY,flag);
		CurveDraw(20,2*X_Witch_cn+130,40,200,mUnit[AccRange-1],COLOR_Yellow,"z����ٶ�",AccZ,flag);
		
		delay_ms(100);
		if(flag<185)
			flag++;
		else
			flag=0;
		if(key_data==KEYCANCEL_UP    )
			return 0;
		
	}
	return 1;
	
}




u8 GyroKeyboard()
{
	u8 fuck[30];
	u8 flag=0;
	
	VirtualFullKeyBoard(20,20,fuck,&flag,30);
	OSTaskClose();
	return 1;
	
}



u8 OSThemeSet()
{
	TaskBoxGUI("��ӭʹ��ͼ�ν���������");
	u8 *mOSTheme[2];
	mOSTheme[0]="�˵���ʽ";
	mOSTheme[1]="�����趨";
	u8 choose1=ListGUI(mOSTheme,"������ѡ��",2);
	if (choose1==0)
	{
		OSTaskClose();
		return 0;
	}
	u8* mThemeSet[3];
	u8 choose2;
	switch(choose1)
	{
	case 1:
		mThemeSet[0]="��ϸ�б�";
		mThemeSet[1]="��ͼ���б�";
		mThemeSet[2]="��ͼ�깬��";
		choose2=ListGUI(mThemeSet,"��ѡ��˵���ʽ",3);
		if (choose2==0)
		{
			return 1;
		}
		else
			MenuType=choose2-1;
		break;
	case 2:
		mThemeSet[0]="տ�����";
		mThemeSet[1]="��ɧ��ɫ";
		mThemeSet[2]="��˿�ջ�";
		choose2=ListGUI(mThemeSet,"��ѡ������Ҫ������",3);
		switch(choose2)
		{
		case 0:
			return 1;
		case 1:
			OSColor=COLOR_Blue;
			break;
		case 2:
			OSColor=COLOR_Red;
			break;
		case 3:
			OSColor=COLOR_Black;
			break;
		}
		break;

	}

	BoxGUI("X-MOVE������Ӧϵͳ");
	OSTaskClose();
	return 1;
}

u8 OSPictureShow()
{
	PictureShowBox(20,20,"ϵͳͼƬ���");
	OSTaskClose();
	return 1;
}
u8 OSCompass()
{       
        TaskBoxGUI("����ָ����(��˹)");
        
 
        float AngleXY=0;
        float XVaule,YValue;   //���ڴ洢��ǰ��Ҫ����ˮƽ�ߵ�����
          HMC5883LInit();   //��ʼ��HMC5883;
      
          CircleShowGUI(80,120,70,COLOR_Green);
          TaskBoxGUI_P(200,3*X_Witch_cn,200+5*Y_Witch_cn,5*X_Witch_cn,"X���ǿ",0);
	TaskBoxGUI_P(200,6*X_Witch_cn,200+5*Y_Witch_cn,8*X_Witch_cn,"Y���ǿ",0);
        TaskBoxGUI_P(200,9*X_Witch_cn,200+5*Y_Witch_cn,11*X_Witch_cn,"Z���ǿ",0);
        OS_func_state=1;
	
	while(OS_func_state==1)
	{
		back_light=back_light_set;
		FontMode(1,COLOR_White);
		XVaule=70*sin(AngleXY);
		YValue=70*cos(AngleXY);
		SetPaintMode(0,COLOR_Red);
		
		Line((u16)(80-XVaule),(u16)(120+YValue),(u16)(80+XVaule),(u16)(120-YValue));
		  delay_ms(100);
		SetPaintMode(0,COLOR_Green);
		
                 HMC5883LReadData();
      
                   HMC5883LShowData();
			AngleXY=atan((float)(ComX/ComY));
			Line((u16)(80-XVaule),(u16)(120+YValue),(u16)(80+XVaule),(u16)(120-YValue));
	               ShowMountGUI(201,4*X_Witch_cn,ComX,7,COLOR_Red,1);
			ShowMountGUI(201,7*X_Witch_cn,ComY,7,COLOR_Red,1);
                        ShowMountGUI(201,10*X_Witch_cn,ComZ,7,COLOR_Red,1);

		if (key_data==KEYCANCEL_UP)
		{
			OS_func_state=0;
                      
			OSTaskClose();
		}
              
		
		
	}
                           
	OSTaskClose();
	return 1;

}
u8 OSUsualStatic()
{
	u8 *fuck[4];
	u16 num[4]={30,80,100,30};
	fuck[0]="���ݼ���";
	fuck[1]="ʱ����ʾ";
	fuck[2]="�������";
	fuck[3]="��������";
	HistogramGUI(fuck,num,4,"�������ʹ��ͳ�ƣ�������");
	OSTaskClose();
	return 1; 
}
u8 PressureTest()
{
	long mPressure,mTemper;
	u8 flag=0;
	
	u8* temp[2];
	u8 choose=0;
	temp[0]="����ģʽ";
	temp[1]="����ֱ��ģʽ";	
	choose=ListGUI(temp,"ѡ��������ʾģʽ",2);
        OS_func_state=1;
	if(choose==0)
	{
		OSTaskClose();
		return 0;
	}
	TaskBoxGUI_P(7,27,307,224,"��ѹ���¶�״̬",0);
	switch(choose)
	{
		
	case 2:
		while(OS_func_state==1)
		{
			BMP085ReadData(3,&mPressure,&mTemper);
			if(!CurveDraw(9,30,60,240,180,COLOR_Red,"��ѹֵ��˹��",(float)(mPressure)/1000,flag))
                            if(!MessageGui("������в���","�Ƿ������",1))
                              break;
                              
			if(!CurveDraw(9,120,60,240,60,COLOR_Blue,"�¶����϶�",(float)(mTemper)/10,flag))
                          if(!MessageGui("������в���","�Ƿ������",1))
                              break;
			delay_ms(700);
			if (flag==240)
			{
				flag=0;
			}
			else
				flag++;
			if (key_data==KEYCANCEL_UP    )
			{
				OSTaskClose();
				return 0;
				
			}
     	
		}
                break;
		
		
	case 1:
		FontSet(3,COLOR_Red);
		FontSet_cn(4,COLOR_Red);
		FontMode(1,COLOR_White);
		Lcd_disp(20,3*X_Witch_cn,"��ǰ��ѹ����λ��˹��");
		Lcd_disp(20,7*X_Witch_cn,"��ǰ�¶ȣ���λ���϶�");
		while (OS_func_state==1)
		{
			BMP085ReadData(3,&mPressure,&mTemper);
			NumberDis(20,4*X_Witch_cn, mPressure,6,3);
			ShowMountGUI(20,8*X_Witch_cn, mTemper/10,4,COLOR_Red,3);
			delay_ms(700);
			if (key_data==KEYCANCEL_UP    )
			{
				OSTaskClose();
				return 0;
			}
		}
                break;
		
	}
	
	
	return 1;
}
u8 SkyMouse()
{

	u8 CurrentKey,LastPort;
	u8  LeftKeyDelay=0;
        u8 choose;
	u8 *temp[7];
	temp[0]="��ͼ";
	temp[1]="������";
	temp[2]="���������";
	temp[3]="���±�";
	temp[4]="���������";
	temp[5]="�ı����빤��";
         temp[6]="�õ�Ƭ��ʾ����";
	
	TaskBoxGUI("�������ģʽ");
        ADXL345Init(0);
          KeyBoardFuncIntroGUI(0,"���","�Ҽ�","����","�л�","����","����");
	if(!MessageGui("LCD��������","�Ƿ������",1))
	{
		OSTaskClose();
		return 0;
	}
	BackLightTo(0);
	
	delay_ms(1000);
	LCDSetSleep();
	OS_func_state=1;
	while (OS_func_state==1)
	{   OSLightControl(2);   
             L3G4200DReadData();
               ADXL345ReadData();
          
             
	if(!GetCurrentKey(&LastPort,&CurrentKey,1)) 
	{
			
	}
	switch(CurrentKey)
	{
        case KEYUP_UP:
          LeftKeyDelay=0;
           CurrentKey=KEYNULL;
          break;
          case KEYLEFT_DOWN:
                   myMEMSData[KEYDF]=KEYLEFT_DOWN;
                 SendWirelessData();
                 delay_ms(10);	
        case KEYUP_DOWN:
             //myMEMSData[KEYDF]=KEYUP_DOWN;
             if(LeftKeyDelay==0)
             {
               delay_ms(200);
               LeftKeyDelay=1;
             }
             else
             {
                 SendWirelessData();
                 delay_ms(10);	
             }
             break;
          case KEYRIGHT_DOWN:
              myMEMSData[KEYDF]=KEYRIGHT_DOWN;
             SendWirelessData();
             delay_ms(800);
             break;
          case KEYENTER_DOWN:
       
                  myMEMSData[KEYDF]=KEYENTER_DOWN;
                   SendWirelessData();
                   delay_ms(10);
                
             break;
      
	
	case  KEYSPECIAL:
		BackLightSet(OSBackLight);
		
                delay_ms(500);
                _EINT();
                 choose=ListGUI(temp,"��ѡ���ݲ˵�",7);
		_DINT();
		if (choose==0)
		{
			 OSTaskClose();
			return 0;
		}
		else if (choose==6)  // �ı����빤��
		{	
			u8 flag=0;
                        u8 Buff[20];
			_EINT();
			//myMEMSData[PRODF]=choose;
			while(MessageGui("��ʾ��Ϣ","�����ַ���",1))
			{
                       
				if(VirtualFullKeyBoard(20,20,Buff,&flag,20))
                                {
                                  for(u8 i=0;i<20;i++)
                                  {
                                     myMEMSData[L3G4200DDF+i] =Buff[i];
                                  }
                                  
				SendWirelessData();
                                }
                               for(u8 i=0;i<20;i++)
                                Buff[i]=0;
                        
                                flag=0;
                        }
            
		}
		else 
		{
			myMEMSData[PRODF]=choose;
                           myMEMSData[KEYDF]=KEYNULL;
			SendWirelessData();
                        delay_ms(1000);
                     
			
		}
               _DINT();
                myMEMSData[PRODF]=0; //һ���ǵô˴����㣡
	         myMEMSData[KEYDF]=KEYNULL;
		delay_ms(2000);
		LCDSetSleep();  
                    _EINT();
		break; 
        default:
          SendWirelessData();
	  delay_ms(5);
          break;

	}
        
      
	
	
	}
	return 1;
}

u8 HeightTest()
{
	TaskBoxGUI("¥��͸߶ȼ��");
	u8 *temp[3];
	u8 myFloor=0;
	long myPressure;
        long myAveragePressure;
        float myHeight=0;
	long T;
	temp[0]="���μ��";
        temp[1]="¥����";
	temp[2]="��������";
	u8 choose=ListGUI(temp, "��ѡ����",3);
	OS_func_state=1;
	switch(choose)
	{
	case 0:
		return 0;
        case 1:
                TaskBoxGUI("�߶���Ϣ,�����ο�");
                   FontMode(3,COLOR_White);
                while (OS_func_state)
		{
                  myAveragePressure=0;
                 for(u8 i=0;i<5;i++)  //��ƽ������ø��ȶ��Ķ�ֵ
                 {
                     BMP085ReadData(3,&myPressure,&T);
                      myAveragePressure+=myPressure;
                 }
                 myAveragePressure=myAveragePressure/5;
           
                 myHeight=(float)(101325-myAveragePressure)/10.0;
                 ShowMountGUI(20,4*X_Witch_cn,myHeight,5,COLOR_Red,3);
                 if (key_data==KEYCANCEL_UP    )
			{
				OSTaskClose();
				return 0;
			}
                 delay_ms(1000);
                  
                }
                break;
          
	case 2:
		TaskBoxGUI("��ǰ¥����Ϣ");
		FontSet(3,COLOR_Red);
                FontMode(1,COLOR_White);
		Lcd_disp(20,3*X_Witch_cn,"��ǰ¥����");
		while (OS_func_state)
		{        
			BMP085ReadData(3,&myPressure,&T);
			myFloor=myHeightInfo.OriginFloor+(myHeightInfo.OriginPressure-myPressure)/(12*myHeightInfo.FloorStep);
			NumberDis(20,4*X_Witch_cn, myFloor,2,3);
			InputControl();
			if (key_data==KEYCANCEL_UP    )
			{
				OSTaskClose();
				return 0;
			}
		}
                break;
	case 3:
		TaskBoxGUI("�߳�����������");
		if(!SliderGUI(20,80,160,"¥����",2,5,1,&myHeightInfo.FloorStep))
		{
			OSTaskClose();
			return 0;
		}
		if (!SliderGUI(20,80,160,"��ǰ¥��ֵ",1,20,1,&myHeightInfo.OriginFloor))
		{
			OSTaskClose();
			return 0;
		}
		if(MessageGui("��ʾ��Ϣ","ˢ��ԭʼ��ѹ��",1))
			BMP085ReadData(3,&myHeightInfo.OriginPressure,&T);
		MessageGui("��ʾ��Ϣ","����ˢ�����",2);
                break;

	}
	return 1;
}
u8 OSConfigSet()
{
	TaskBoxGUI("��ӭʹ��ϵͳ������");
	u8 *temp[6];
	temp[0]="��ת���";
	temp[1]="���ٶȼ��";
	temp[2]="����ʱ��";
	temp[3]="��������";
	temp[4]="��ʱ��";
	temp[5]="ʱ���趨";
	u8 choose=ListGUI(temp,"����ѡ��",6);
	
	switch(choose)
	{
	case 0:
		OSTaskClose();
		return 0;
	case 1:
		GyroControlEN=	MessageGui("����ѡ��","������ת��⣿",1);
		break;
	case 2:
		AccControlEN=	MessageGui("����ѡ��","�������ٶȼ�⣿",1);
		break;
	case 3:
		SliderGUI(20,80,150,"����ʱ���趨",1,60,1,&back_light_set);
		
		break;
	case 4:
		SliderGUI(20,80,150,"����ǿ���趨",1,500,25,&OSBackLight);
		BackLightTo(OSBackLight);
		break;
	case 5:
		TickControlEN=MessageGui("����ѡ��","������ʱ����",1);
		break;
	case 6:
          if(TimeSetGUI())
            MessageGui("��ʾ��Ϣ","ʱ���趨�ɹ���",0);
          else
                      MessageGui("��ʾ��Ϣ","�趨��ȡ��",0);
              

                         break;
	
			

	}
	return 1;
}

u8 NFS()
{
	
          KeyBoardFuncIntroGUI(0,"ǰ��","����","���","�ҹ�","ȷ��","����");
	
	  return  CommonControl();
               
                  
            
  
}
u8  COD()
{

	u8 LastPort,CurrentKey;
        KeyBoardFuncIntroGUI(0,"ǰ��","����","���ܼ�","��ǹ","����","����");
	if (!MessageGui("�ڶ��ֱ��Ѿ�����","�����޷�����",1))
	{
		OSTaskClose();
		return 0;
	}
          KeyBoardFuncIntroGUI(1,"��ǹ","��׼","����","�Ե�","��","��");
   
        if(!NetProEnterConfirm())
           return 0;
        SendWirelessData();  //��ǰ��������
      
       
	
	OS_func_state=1;
	while (OS_func_state)
	{      OSLightControl(2);
              L3G4200DReadData();
               if(!GetCurrentKey(&LastPort,&CurrentKey,1)) 
               {
                  if(CurrentKey!=KEYENTER_DOWN)
                  {
                    L3G4200DShowData();
                    {
                      if(GyroX>20||GyroX<-20||GyroZ>20||GyroZ<-20)
                        SendWirelessData();
                    }
                 
                  }
                    delay_ms(15);
                
               }
              
                 
             if(  NetProCloseConfirm(CurrentKey))
                   return 1;
            
  
         }
         return 1;
    
}

u8 AHRS()
{
    return  CommonControl();
}

u8  Gravity()
{
	
	TaskBoxGUI("PC������Ӧ��Ļ");
	
        if(!NetProEnterConfirm())
           return 0;
	
        key_data=KEYNULL;
        ADXL345Init(0);
	while(OS_func_state==1)
	{
                  OSLightControl(2);
		ADXL345ReadData();
		ADXL345ShowData(0);
		if (AccX>8)
		{
			//myMEMSData[PRODF]=1;   //���ϣ�
		}
		else if (AccX<-8)
		{
			//myMEMSData[PRODF]=2;  //����
		}
		else if (AccY>8)
		{
			//myMEMSData[PRODF]=3;
		}
		else if (AccY<-8)
		{
			//myMEMSData[PRODF]=4;
		}
		//if (myMEMSData[PRODF]!=0)
		{

			MessageGui("��ʾ��Ϣ","���Խ���Ļ��ת",2);
			TaskBoxGUI("PC������Ӧ��Ļ");
			SendWirelessData();
			
		
		}
                delay_ms(3000);
                myMEMSData[PRODF]=0;

		  if(key_data==KEYCANCEL_UP)
                  {
                    OSTaskClose();
				OSLightControl(0);
				
                   return 1;
                  }
	}
        return 1;
	
	
}

u8 Thunder()
{
	u8 LastPort,CurrentKey;
	u8* temp[3];
	u8 choose;
	temp[0]="�˵�ģʽ";
	temp[1]="��Ϸģʽ";
	temp[2]="����";
	KeyBoardFuncIntroGUI(0,"��ǹ","����","��","�˵�","��","����");
	   if(!NetProEnterConfirm())
           return 0;
        ADXL345Init(0);
	
	
	myMEMSData[PRODF]=1;
	while (OS_func_state==1)
	{
		OSLightControl(2);
		 GetAllSensorData();
		if (!GetCurrentKey(&LastPort,&CurrentKey,1))
		{
			SendWirelessData();
			delay_ms(15);	
		}
		if(CurrentKey==KEYSPECIAL)
		{
			BackLightSet(OSBackLight);
			_EINT();
			choose=	ListGUI(temp,"��ѡ����ģʽ",3);
			if(choose==3&&MessageGui("��ʾ��Ϣ","ȷ��������",1))
			{
				OSTaskClose();
				OSLightControl(0);
				return 1;
			}
			else
				myMEMSData[PRODF]=choose;
			
			_DINT();
			delay_ms(1000);
			LCDSetSleep();  
		}
		
	}
	return 1;
}

u8 BodyFit()
{
   return  HandRecongiton();
  
}

u8 CommonControl()
{
     u8 LastPort,CurrentKey;
	   if(!NetProEnterConfirm())
           return 0;
	   ADXL345Init(0);
        
	   while(OS_func_state==1)
           {
	   OSLightControl(2);
	   if(!GetCurrentKey(&LastPort,&CurrentKey,1))
	   {
		    HMC5883LReadData();
		   ADXL345ReadData();
	           L3G4200DReadData();
		   SendWirelessData();
		   delay_ms(40);
	   }
	   if(  NetProCloseConfirm(CurrentKey))
           {
         
                   return 1;	   
           }
		   
	}
        return 1;
}
u8 GeoWar()
{
           return  CommonControl();
        
}
u8 HAWX()
{
  
	u8 LastPort,CurrentKey;
    u8* temp[3];
	u8 choose;
	temp[0]="�˵�ģʽ";
	temp[1]="��Ϸģʽ";
	temp[2]="����";
       KeyBoardFuncIntroGUI(0,"����","����","��","�˵�","��","����");
     if(!NetProEnterConfirm())
           return 0;
        ADXL345Init(0);
	//myMEMSData[PRODF]=1;
        while (OS_func_state==1)
	{
		OSLightControl(2);
	GetAllSensorData();
		if (!GetCurrentKey(&LastPort,&CurrentKey,1))
		{
			SendWirelessData();
			delay_ms(15);	
		}
		if(CurrentKey==KEYSPECIAL)
		{
			BackLightSet(OSBackLight);
			_EINT();
			choose=	ListGUI(temp,"��ѡ����ģʽ",3);
			if(choose==3&&MessageGui("��ʾ��Ϣ","ȷ��������",1))
			{
				OSTaskClose();
				OSLightControl(0);
				return 1;
			}
			else
				myMEMSData[PRODF]=choose;
			
			_DINT();
			delay_ms(1000);
			LCDSetSleep();  
                        CurrentKey=KEYNULL;
		}
	}
        return 1;
}

u8 WirelessControl()
{

    TaskBoxGUI("ͨ�Ź���������");
	
	u8 *temp[2];
	temp[0]="�������߷�ʽ�л�";
	temp[1]="��������ʱ�л�";
	MessageGui("�����ѡ��","����������ͨ��ʧЧ",0);

	u8 choose=ListGUI(temp,"����ѡ��",2);
	
	switch(choose)
	{
	case 0:
		OSTaskClose();
		return 0;
	case 1:
		WirelessEN=MessageGui("ͨ���ŵ��л�","�ǣ����ߣ�������",1);
		break;
	case 2:
		SliderGUI(20,80,150,"�������л�",0,3,1,(u16*)(&UserID));
		break;

	}
	OSTaskClose();
	return 1;
	
}
u8 Waterlevel()
{
	float AngleXY,AngleYZ,AngleZX,AnverageAccX,AnverageAccY,AnverageAccZ;
	TaskBoxGUI("ˮ׼�Ǻ���ǲ���");
	float XVaule,YValue;   //���ڴ洢��ǰ��Ҫ����ˮƽ�ߵ�����

        
	CircleShowGUI(80,120,70,COLOR_Blue);
	ADXL345Init(0);
	TaskBoxGUI_P(200,3*X_Witch_cn,200+5*Y_Witch_cn,5*X_Witch_cn,"X-Z�Ƕ�",0);
	TaskBoxGUI_P(200,6*X_Witch_cn,200+5*Y_Witch_cn,8*X_Witch_cn,"Y-Z�Ƕ�",0);
	OS_func_state=1;
	
	while(OS_func_state==1)
	{
		back_light=back_light_set;
		FontMode(1,COLOR_White);
		XVaule=70*sin(AngleXY);
		YValue=70*cos(AngleXY);
		SetPaintMode(0,COLOR_White);
		
		Line((u16)(80-XVaule),(u16)(120+YValue),(u16)(80+XVaule),(u16)(120-YValue));
		
		SetPaintMode(0,COLOR_Blue);
		for(u8 i=0;i<10;i++)
		{
			ADXL345ReadData();
			ADXL345ShowData(0);
			AnverageAccX+=AccX;
			AnverageAccY+=AccY;
			AnverageAccZ+=AccZ;
			delay_ms(10);
		}
		AnverageAccX/=10;
		AnverageAccY/=10;
		AnverageAccZ/=10;
		if(AnverageAccZ<2&&AnverageAccZ>-2)
		{
 
			AngleXY=atan((float)(AnverageAccY/AnverageAccX));
			Line((u16)(80-XVaule),(u16)(120+YValue),(u16)(80+XVaule),(u16)(120-YValue));
	    
				
		}
		else
		{
                 
			AngleYZ=atan((float)(AnverageAccY/AnverageAccZ));
			AngleZX=atan((float)(AnverageAccX/AnverageAccZ));
			ShowMountGUI(201,4*X_Witch_cn,AngleYZ*57,7,COLOR_Red,1);
			ShowMountGUI(201,7*X_Witch_cn,AngleZX*57,7,COLOR_Red,1);
			delay_ms(500);
			
		}
		
		if (key_data==KEYCANCEL_UP)
		{
			OS_func_state=0;
			OSTaskClose();
		}
		
		
	}
	
	
	return 1;
}

u8 HandRecongiton()
{
	u8 LastPort,CurrentKey;

	TaskBoxGUI("Gesture Recognition");
	
	KeyBoardFuncIntroGUI(0,"��","��","��","��","�ʴ�","����");
      
      if(!NetProEnterConfirm())
        return 0;
	
	while(OS_func_state==1)
	{   
         
		
		if (!GetCurrentKey(&LastPort,&CurrentKey,0))
		{
                  
			switch(CurrentKey)
			{
			case KEYENTER_DOWN:
                              OSLightControl(2);
                                 L3G4200DReadData();
                                myMEMSData[KEYDF]=CurrentKey;
                                
				SendWirelessData();
                                delay_ms(10);	
				break;
			case KEYSPECIAL:
				OS_func_state=44;
				break;
                        case KEYENTER_UP: 
                              OSLightControl(0);
                              myMEMSData[KEYDF]=CurrentKey;
                                 
				SendWirelessData();
                                CurrentKey=KEYNULL;
				break;
			}
                        
			
			
		}
               
              
	}
        _EINT();
	if (MessageGui("��ʾ��Ϣ","ȷ��������?",1))
	{
	OSTaskClose();
	return 1;
	}
        return 1;

  
}

u8 TextInput()
{
  u8 Buff[30];
  u8 Buffflag=0;
   if(!T9InputTask( 5, 20, Buff,&Buffflag,30))
   {
#if PCID==3
       MessageGui("��ʾ��Ϣ","����������",1))
#endif 
      OSTaskClose();
   }
   return 1;
}
u8 RemoteCtl()
{
  u8 LastPort,CurrentKey;
	//KeyBoardFuncIntroGUI(0,"��ǹ","����","��","�˵�","��","����");
	   if(!NetProEnterConfirm())
           return 0;
        ADXL345Init(0);
	
	
	
	while (OS_func_state==1)
	{
		OSLightControl(2);
		ADXL345ReadData();
		L3G4200DReadData();
		if (!GetCurrentKey(&LastPort,&CurrentKey,1))
		{
                      
			
                        switch(CurrentKey)
			{
			case KEYLEFT_DOWN:
                        case KEYRIGHT_DOWN: 
                       case KEYENTER_DOWN: 
                            
                               myMEMSData[KEYDF]=CurrentKey;
				break;
			}
                        SendWirelessData();
			delay_ms(15);
                         if(  NetProCloseConfirm(CurrentKey))
                       {
          
                          return 1;	   
                      }
		}
		
		
	}
        return 1;
         
	
 
}
u8 Demo()
{
  return COD();
}
u8 Picasa()
{
  KeyBoardFuncIntroGUI(0,"ǰ","��","�Ŵ�","��С","��Ӧ","����");
   return  CommonControl();
}
u8 Ball()
{      MessageGui("��ʾ��Ϣ","δ����ù���",0);
      OSTaskClose();
  return 1;

  
}

u8 Fighter()
{
       u8 LastPort,CurrentKey;
	   if(!NetProEnterConfirm())
           return 0;
	   ADXL345Init(3);
      
	   while(OS_func_state==1)
           {
	   OSLightControl(2);
	   if(!GetCurrentKey(&LastPort,&CurrentKey,1))
	   {
		     L3G4200DReadData();
                     ADXL345ReadData();
                     L3G4200DShowData();
                        ADXL345ShowData(3);
                      OSLightControl(2);
                     if(AccX>40)
                     {
                          myMEMSData[MOVEFLAG]=1;
                          SendWirelessData();
                           delay_ms(1000);	
                              myMEMSData[MOVEFLAG]=0;
                     }                   
		      switch(CurrentKey)
			{

                         case KEYENTER_DOWN:
                                 
                                myMEMSData[KEYDF]=CurrentKey;
                                
				SendWirelessData();
                                delay_ms(30);	
				break;
                            default:
                            
                              delay_ms(30);	
				break;
                        }
                
	   }
	   if(  NetProCloseConfirm(CurrentKey))
           {
          
                   return 1;	   
           }
		   
	}
        return 1;
}
u8 Crysis()
{
     return  COD();
}
u8 Sky()
{
    u8 LastPort,CurrentKey;
	   if(!NetProEnterConfirm())
           return 0;
	   ADXL345Init(0);
         
	   while(OS_func_state==1)
           {
	   OSLightControl(2);
	   if(!GetCurrentKey(&LastPort,&CurrentKey,1))
	   {
		     L3G4200DReadData();
                      OSLightControl(2);
		switch(CurrentKey)
			{
                    
                           
                         case KEYENTER_DOWN:
                                
                                
                                myMEMSData[KEYDF]=CurrentKey;
                                
				SendWirelessData();
                                delay_ms(30);	
				break;
                            default:
                              SendWirelessData();
                              delay_ms(30);	
				break;
                        }
                
	   }
	   if(  NetProCloseConfirm(CurrentKey))
           {
          
                   return 1;	   
           }
		   
	}
        return 1;
}

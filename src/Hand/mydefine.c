#include "config.h"

/*
mydefine.c
ELPOS2.0�ĵײ����������ȫ�ֱ�������
Copyright (c) 2010����һ��
buptzym@bupt.edu.cn
All rights reserved.
���������ѧϰ�ο������ṩ�κοɿ��Է���ĵ���������������ҵĿ��
*/





unsigned char    OS_index_data,key_data,OS_count=0,OS_func_state=0,WirelessProcessFlag=0,MenuType=2,OS_index_ago=0,
                GyroControlEN=1,AccControlEN=1,TickControlEN=1,WirelessEN=1,UserID=PCID,GyroMenuEN=0,InnerFuncState,
                 KeyRepeatEN=0;

u16 OSBackLight=300,back_light=10,back_light_set=10,OSColor=COLOR_Blue;
long mPassWord=123;



u8 isGyroExisted; 
u8 isAccExisted; 
u8 isComExisted; 
u8 isGyroEnable=1;
u8  myNodeFreshSpeed=2;  //ˢ���ٶ�
u8 myWorkMode=0X40;
 
u8 ChanelID=0; 
const u16 GetCounterByNodeFreshSpeed[]={2000,1000,500,250,125,62,31,15};
u16 GetSendCounter()
{
  return GetCounterByNodeFreshSpeed[myNodeFreshSpeed];
}









#if CHSORENG==0
const struct  TaskPCB  myTaskPCB[SIZE_OF_Task]= //�˵�����
{
	{"ϵͳ���˵�",MenuGUI,"ȫ�ֹ�����ʾ",5,{0,6,14,20,8,33,9,10}},   //0
	{"ϵͳʱ��",time_show,"�鿴��ǰϵͳ��ʱ��",8,{8,0}},    //1
	{"���ٶȼ��",AccShow,"������ٶȼ��",24,{8,0}},   //2
	{"������",Five,"�˻������߶�ս",23,{9,0}},   //3
	{"����˹����",TerisBrick,"������Ϸ,֧�ֺ�����",8,{9,0}},   //4
	{"��ѹ���¶�",PressureTest,"��ʾ�¶Ⱥ���ѹ״̬",24,{8,0}},    //5
	{"������Ӧ����",GyroKeyboard,"����ȫ�µ��ַ���������",17,{14,0}},   //6
	{"ͨ�Ź���",WirelessControl,"����ͨ�ŷ�ʽ��Э��",11,{10,0}},   //7
	{"���������",MenuGUI,"��⵱ǰ����״̬",20,{0,6,1,2,5,19,12,16}},   //8
	{"���ֹ���",MenuGUI,"����ʹ�ø�ϵͳ�Դ���Ϸ",22,{0,4,3,4,15,28}},   //9
	{"ϵͳ����",MenuGUI,"���ɶԸ�ϵͳ���ú͹���",11,{0,4,7,11,13,17}},   //10
	{"��������",OSConfigSet,"�Թ��ĺ͹��ܵ�����",19,{10,0}},   //11
	{"ˮ׼��",Waterlevel,"ˮƽ�ǶȲ�����",18,{8,0}},   //12   ��ʱ����
	{"�����趨",OSThemeSet,"���ò˵���ʽ�������",9,{10,0}},    //13
	{"����������",MenuGUI,"��Խʱ���ľ��ᶯ����Ӧ",21,{0,6,18,22,6,27,31,32}},   //14
	{"ͼƬ���",OSPictureShow,"���ϵͳ�����ͼƬ",25,{9,0}},   //15
	{"����ָ����",OSCompass,"����ָ�����ṩ������Ϣ",10,{8,0}},   //16
	{"���ù���ͳ��",OSUsualStatic,"��ù���ͳ��",23,{10,0}},   //17
	{"������꣡",SkyMouse,"���߶�����Ӧ��꣡",7,{14,0}},   //18
        {"�߶ȼ��",HeightTest,"��õ�ǰ�߶���Ϣ",21,{8,0}},   //19
        {"������Ӧ��Ϸ",MenuGUI,"Զ�̶������Ƶ�����Ϸ",25,{0,8,21,36,37,23,25,26,29,30}},   //20
        {"��Ʒ�ɳ�",NFS,"��۵糸�Ŀ��",16,{20,0}},   //21
         {"AHRS��̬",AHRS,"ʵʱ��̬����Ϳ���",24,{14,0}},   //22
         {"ʹ���ٻ�",COD,"˫ϵͳ��FPS��ˬ���ܣ�",15,{20,0}},   //23
         {"PC������Ӧ",Gravity,"�ɸı������Ļ����",9,{20,0}},   //24
         {"�׵�3D��",Thunder,"������ά��ս��Ϸ",7,{20,0}},   //25
         {"����ս��",GeoWar,"˫�ֱ�������Ϸ",6,{20,0}},   //26
         {"����ʶ��",HandRecongiton,"",22,{14,0}},   //27
         {"�ı�����",TextInput,"",8,{14,0}},   //28
         {"ӥ������",HAWX,"",14,{20,0}},   //29
         {"��֫����",BodyFit,"",22,{20,0}},   //30
          {"Զ�̻�е����",RemoteCtl,"����ͬ�����ٿ���",11,{14,0}},   //31
           {"����ʵ��",Demo,"",21,{14,0}},   //32
           {"PC��������",MenuGUI,"��ݿ�������",21,{0,4,24,34,35,38}},   //33
            {"PCͼƬ���",Picasa,"",21,{33,0}},   //34
            {"������",Ball,"",21,{33,0}},   //35
             {"��ͷ����",Fighter,"",21,{20,0}},   //36
              {"�µ�Σ��",Crysis,"",21,{20,0}},   //37
               {"̫��̽��",Sky,"",9,{33,0}},   //38
	
};

#endif

#if CHSORENG==1
const struct  TaskPCB  myTaskPCB[SIZE_OF_Task]= //�˵�����
{
	{"Main Menu",MenuGUI,"ȫ�ֹ�����ʾ",5,{0,5,14,20,8,9,10}},   //0
	{"System Time",time_show,"�鿴��ǰϵͳ��ʱ��",6,{8,0}},    //1
	{"Acc Watch",AccShow,"������ٶȼ��",9,{8,0}},   //2
	{"Go Bang",Five,"����������,�˻������߶�ս",8,{9,0}},   //3
	{"Terris",TerisBrick,"������Ϸ,֧�ֺ�����",10,{9,0}},   //4
	{"Temp.&Press.",PressureTest,"��ʾ�¶Ⱥ���ѹ״̬",11,{10,0}},    //5
	{"Motion Keys",GyroKeyboard,"����ȫ�µ��ַ���������",12,{14,0}},   //6
	{"Wireless Net",WirelessControl,"����ͨ�ŷ�ʽ��Э��",13,{10,0}},   //7
	{"EnvirWatch",MenuGUI,"��⵱ǰ����״̬",5,{0,3,1,2,5}},   //8
	{"Recreation",MenuGUI,"����ʹ�ø�ϵͳ�Դ���Ϸ",6,{0,4,3,4,15,28}},   //9
	{"SysManage",MenuGUI,"���ɶԸ�ϵͳ���ú͹���",8,{0,4,7,11,13,17}},   //10
	{"RunConfig.",OSConfigSet,"�Թ��ĺ͹��ܵ�����",9,{10,0}},   //11
	{"WaterLevel",Waterlevel,"ˮƽ�ǶȲ�����",6,{14,0}},   //12   ��ʱ����
	{"UI Set",OSThemeSet,"���ò˵���ʽ�������",6,{10,0}},    //13
	{"Miracle",MenuGUI,"��Խʱ���ľ��ᶯ����Ӧ",8,{0,7,18,6,12,16,19,22,27}},   //14
	{"PictrueView",OSPictureShow,"���ϵͳ�����ͼƬ",5,{9,0}},   //15
	{"ECompass",OSCompass,"����ָ�����ṩ������Ϣ",6,{14,0}},   //16
	{"Com.Statics",OSUsualStatic,"��ù���ͳ��",9,{10,0}},   //17
	{"AirMouse",SkyMouse,"���߶�����Ӧ��꣡",9,{14,0}},   //18
        {"HeightTest",HeightTest,"��õ�ǰ���ڵ�¥�㣡",9,{14,0}},   //19
        {"Motion Games",MenuGUI,"Զ�̶������Ƶ�����Ϸ",9,{0,7,21,23,24,25,26,29,30}},   //20
         {"NFS",NFS,"��۵糸�Ŀ��",9,{20,0}},   //21
         {"AHRS",AHRS,"ʵʱ��̬����Ϳ���",9,{14,0}},   //22
         {"COD",COD,"˫ϵͳ��FPS��ˬ���ܣ�",9,{20,0}},   //23
         {"PCGravity",Gravity,"�ɸı������Ļ����",9,{20,0}},   //24
         {"Thunder3D",Thunder,"������ά��ս��Ϸ",9,{20,0}},   //25t
         {"GeoWar",GeoWar,"˫�ֱ�������Ϸ",9,{20,0}},   //26
         {"HandRecog.",HandRecongiton,"",9,{14,0}},   //27
         {"TextInput",TextInput,"",9,{14,0}},   //28
         {"HAWX",HAWX,"",9,{20,0}},   //29
         {"RehabCenter",BodyFit,"",9,{20,0}},   //30
	

};
#endif
struct HeightInfo  myHeightInfo={1,4,101325};





u8 (* OS_func)();  //ȫ�ֺ���ָ��


const unsigned char Rx_Address[3]={104,103,102 };   //���͵�ַ����ʱ����ͨ������޸ĸ�ֵ
const unsigned char Tx_Address[3]={100,101,102};     //������ַ������SPI����ģʽ
u8 InputPortState;

u8 myMEMSData[PACKETLENGTH];
u8 uart_rxbuff[PACKETLENGTH];
float AccX,AccY,AccZ,GyroX,GyroY,GyroZ,ComX,ComY,ComZ;
/*MEMS���������ݴ洢��������
0:�ӻ�ID  1:����ģʽ 2:������Ӧ��� 3-9:ר������  10-15  �����ǣ�16-21 �ų��ƣ�22-28:���ٶȼƣ�28-31��ѹ���¶�*/



long  strlenExt(const unsigned char *pucSrc)
{
	long  i = 0;
	
	while(*(pucSrc+i) != '\0')
		i++;
	
	return i;
}
void InputControl()
{

    
#if  SIM_JTAG_CHANGE==1
      if(KeyRepeatEN==1)
      {
        if(key_data%2)
          key_data++;
        delay_ms(200);
      }
      else
      {
          key_data=KEYNULL;
	 delay_ms(3);
	  LPM3;
         delay_ms(3);
      }
	
#else 
	_NOP();
#endif 
        

}

void input_command(uchar key_data_temp)
{
	key_data=key_data_temp;
	
}
uint random(uint x,uint y) 
{ 
	
	Get_DS1302(rdata);
	uint ran=0; 
	srand(rdata[0]); //������� 
	ran=rand()%(y-x+1)+x; 
	return ran; 
} 
void OSTaskClose()
{
	OS_index_data=myTaskPCB[OS_index_data].SubTaskList[0];
      //  myMEMSData[PRODF]=0;
        
        SendWirelessData();  //�������������Ըı���λ��������ʽ
	OS_func_state=44;
             _EINT();   
	
}

u8 SendWirelessData()
{
         myMEMSData[IDDF]=UserID;
	
       
        
        if(WirelessEN==1)
	W_PutString(myMEMSData);
        else 
        {
          Uart_PutString(myMEMSData);
        }
	return 0;
	
}

u8 GetCurrentKey(u8 *PortStatus1,u8* KeyValue,u8 ThisOrNet) //��һ������Ϊ�ϴζ˿�״ֵ̬���ڶ���Ϊ���صļ�ֵ
{
	u8 PortStatus2,ReturnValue=0;
	u8 KeyFlag;
	_DINT();
	delay_ms(15);
        PortStatus2=P2IN; 
        if(0X2B==PortStatus2&0x3F)  //���ⰴ��
        {
          *KeyValue=KEYSPECIAL;
          ReturnValue=2;
          return ReturnValue;
        }
	for (u8 i=0;i<6;i++)
	{   KeyFlag=1<<i;
		if ((*PortStatus1&KeyFlag)>(PortStatus2&KeyFlag))  // ����
		{
			*KeyValue=2*i+1;
                        if(ThisOrNet)
                        {
                        myMEMSData[KEYDF]=*KeyValue;
			SendWirelessData();
                        }
			ReturnValue=1;
		} 
		else if((*PortStatus1&KeyFlag)<(PortStatus2&KeyFlag))  //����
		{
		                *KeyValue=2*i+2;
                                if(ThisOrNet)
                                {
                                 myMEMSData[KEYDF]=*KeyValue;
			 	SendWirelessData(); 
                                }
				ReturnValue=1;
		}
		
	}
 
        *PortStatus1=PortStatus2;
         myMEMSData[KEYDF]=0;
     
	
return ReturnValue;
}
//�룬�֣�ʱ���գ��£����ڣ���

unsigned char wdata[7]={0x30,0x05,0x17,0x08,0x02,0x02,0x11};
unsigned char rdata[7]={0x30,0x22,0x23,0x26,0x09,0x07,0x10};
const u8 FullKeyBoardData[44]=
{
	'1','2','3','4','5','6','7','8','9','0','!',
		'q','w','e','r','t','y','u','i','o','p','?',
		'a','s','d','f','g','h','j','k','l',':','!',
		'z','x','c','v','b','n','m','.','l',' ',' '
};
const u8 NumKeyBoardData[12]=
{
	'7','8','9',
		'4','5','6',
		'1','2','3',
		' ','0',' '
		
};
void FloatToChar(float OriData,u8* Result)
{
      OriData*=1000;   //ͳһ����10K,�Լ�С�������
	*Result=(u8)(OriData/256);
	*(Result+1)=(u8)(OriData-*Result*256);
}
void OSLightControl(u8 Mode)
{
  //0���䰵��1 ����  2��ȡ��
  switch(Mode)
  {
  case 0:
    P4OUT&=~BIT7;
    break;
  case 1:
    P4OUT|=BIT7;
    break;
  case 2:
     P4OUT^=BIT7;
    break;
  }
}

u8 DecToHexFunc(u16 Dec)
{
  return (Dec/10)*16+Dec%10;
}

u8 KeyPressDownConfirm(u8 Time)
{
  while( (!GetCurrentKey(&InputPortState,&key_data,0))&&Time>0)
  {
    delay_ms(50);
    Time--;
  }
  if(Time==0)
    return 1;
  else 
  {
    return 0;
  }
}
  
u8 OSFuncKeyInputProcess()
{
        GyroMenuEN=0;
         KeyRepeatEN=0;
       
	if(key_data==KEYENTER_DOWN)
        {
          if(KeyPressDownConfirm(5))
		GyroMenuEN=1;
           else 
           {
              key_data=KEYENTER_UP;
              
           }
        }
        else
            GyroMenuEN=0;
        if(key_data==KEYUP_DOWN||key_data==KEYDOWN_DOWN||key_data==KEYLEFT_DOWN||key_data==KEYRIGHT_DOWN)
        {
           u8 KeyTemp=key_data;
          if(KeyPressDownConfirm(10))
		KeyRepeatEN=1;
           else 
           {
              key_data=KeyTemp+1;
           }
        }
        else
            KeyRepeatEN=0;
        
	
        return 1;
}   

u8   NetProEnterConfirm()
{
      if(!MessageGui("LCD��������","�Ƿ������",1))
    { OSTaskClose();
		return 0;
    }
    else
    {
        BackLightTo(0);
	delay_ms(1000);
	LCDSetSleep();
        OS_func_state=1;
        return 1;
    }

}
u8   NetProCloseConfirm(u8 CurrentKey)
{
      if(CurrentKey==KEYSPECIAL)
                {
                 
                       _EINT();
                             OSLightControl(0);
                       if(MessageGui("���˳�����","�Ƿ�������",1))
                       {
                       OSTaskClose();
                       return 1;  //ȷ���˳�
                         }
                       else
                       {
                         BackLightTo(0);
	              delay_ms(1000);
	                  LCDSetSleep();
                          return 0;  // ���˳�
                         
                       }
               
                }
      return 0;
      
}
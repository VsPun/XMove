
#include "config.h"



void main(void)
{


   
     HardwareInit();
   
 
	StartAllSensor();
    
         SetRFChannel(0); 
 
	while(1)
	{

		if(TimerCounter==MAXCounter)  
			TimerCounter=0;  //����



		u8 counter=GetSendCounter();
		if(TimerCounter%counter==0)  //�ﵽ��������
		{
                 
			StartAllSensor();
		}
		if(TimerCounter%OneSec==0)  //�ﵽ�������ڣ�ʵ�ֲ�����ѹ

		{
			GetVCCValue();     //�ⶨ��ѹ
                       // OSLEDControl(1);
                         RxWayConfig() ;    //   ��ʮ��֮һʱ϶�ڽ�������ͨ��
			
		}
		if(TimerCounter%OneSec==100)  //
		{
                       //   OSLEDControl(0);
		     SetStandbyMode();
		}
                
		if(TimerCounter%counter==3)  //��ɲ����ͷ�������
		{
			
                       OSLEDControl(2);
			GetAllSensorData();
			CalAllSensorData();
			W_PutString();
                     
			CloseAllSensor();

		}
		LPM0;
	}
}




#include "config.h"



void main(void)
{

    HardwareInit();
   
 
	//StartAllSensor();
    
 

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
			RxWayConfig() ;    //   ��ʮ��֮һʱ϶�ڽ�������ͨ��
		}
		if(TimerCounter%OneSec==50)  //
		{
                  OSLEDControl(2);
                  
                  
			SetStandbyMode();
		}



		if(TimerCounter%counter==5)  //��ɲ����ͷ�������
		{
			OSLEDControl(2);

			GetAllSensorData();
			//CalAllSensorData();
			W_PutString();
			CloseAllSensor();

		}
		LPM0;
	}
}


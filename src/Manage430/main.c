
#include "config.h"






u8 SendingTime=0;
void  main(void)
{

  
	HardwareInit();
	SetRFChannel(0,0);  //�趨����Ƶ��
        
	RxWayConfig(0);
        delay_ms(1000);
	while(1) 
	{  

		ProcessReceivedData();
                
                if(TimerCounter==MAXCounter) 
                {
                    SendSensorData(myMEMSData);
                 
			TimerCounter=0;  //����
                }

               
                if(UartReceiveFlag==1)  //���������������
                {

                    if(myReceiveBuff[0]!=PCID)
                      continue;
                    if(myReceiveBuff[1]==1)  //���ýڵ�״̬
                    {
                       while(SendingTime<100)
                       {
                          W_PutStringPtr(0,myReceiveBuff);
                          SendingTime++;
                       }
                       SendingTime=0;

                    }
                    
                    else if(myReceiveBuff[1]==2) //�����ŵ�״̬
                      
                    {
                      
                    }
                    else
                    {
                      
                    }
                }
           
                UartReceiveFlag=0;
	}
        

}

#include "config.h"  



void InitVar()
{
	myMEMSData[IDDF]=PCID;
      
   
        myMEMSData[NODETYPEDF]= NODEGENE<<5;
        myMEMSData[NODETYPEDF]  +=GENEID; 
}



void HardwareInit()
{
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
        SetCPUSpeed(16);
	
       UartInit();
        _EINT();
    
	I2C_Init();
	WirelessInit();
        SetRFChannel( 0);  //id  0-7;
      
              
        InitAllSensor();
        InitVar();
      
       
       
        TimerInit();
        

}

///���յ��������ݵĴ�����
void ProcessCallBackData()
{
      
      

}
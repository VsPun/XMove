#include "config.h"
#include "string.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void system_init()
{ 

    HardwareInit();
 InitVar();
    
        //�ж�����
	//�����ж��趨
	P2DIR&=0XC0;
	P2OUT|=0X3F;
	//P2IES|=0X3f;
        P2IES&=0XC0;   //1�Ӹߵ��ͣ�0�ӵ͵���
	P2IE|=0X3F;
	//���ٶȴ������ж�P1.0
	P1DIR&=0XFD;
	P1IES&=0XFD; 
	P2OUT|=0X03;
	P1IE|=0X03;
        //����ģ���ж��趨
	//P1DIR &= ~BIT4;
	//P1IE |= BIT4;    
	//P1IES |=BIT4; 
	
	
	
	
	Reset_DS1302();
	//Set_DS1302(wdata);
	I2C_Init();
	WirelessInit();
	LCD_Initial();
 
	P4DIR|=BIT7;
	OSLightControl(0);

       
    
      
#if DEBUG_EN==0
	
	TACTL|=MC1;
        
#endif
	
}
u8 counter=0;
u8 fuck1,fuck2;
void OS_funcn()            //��ֵ��������ֱ�ӵ���
{
	OS_func=myTaskPCB[OS_index_data].function;
	OS_func(); 
}
void  main(void)
{
	
	
        system_init();
 
        
        SystemOpenGUI();
	BoxGUI("X-MOVE������Ӧϵͳ");
       
	
	//PassWordCheck();   

        _EINT();
	
   
           OS_funcn() ;
	while(1)
	{
		if(OS_index_ago==OS_index_data)
		{      
			OS_func();
#if  SIM_OR_ITAG==1                  
			LPM3;
#endif 
			
		}
		else
		{   
			
			OS_index_ago=OS_index_data;
			
			OS_func_state=0;
			OS_funcn();
			
#if  SIM_OR_ITAG==1                  
			LPM3;
#endif 
		}   
	}
}
#pragma vector=USART1RX_VECTOR
__interrupt void usart1_rx (void)
{  
  
}
#pragma vector=USART0RX_VECTOR
__interrupt void usart0_rx (void)
{

}


/*******************************************
�������ƣ�PORT1_ISR 
��    �ܣ�p1�˿ڵ��жϷ�����
��    ������
����ֵ  ����
********************************************/
#pragma vector=PORT1_VECTOR
__interrupt void  PORT1_ISR(void)
{
	switch(P1IFG)
	{
	case 0x10:  //��������ģ����ж�
               
               
		break;
	case 0x02:
		break;
		
		
	}
        P1IFG = 0;
}
/*******************************************
�������ƣ�PORT2_ISR 
��    �ܣ�p2�˿ڵ��жϷ�����
��    ������
����ֵ  ����
********************************************/
#pragma vector=PORT2_VECTOR
__interrupt void  PORT2_ISR(void)
{
   
  
    if( GetCurrentKey(&InputPortState,&key_data,0))
    {
           OSFuncKeyInputProcess();
            LPM3_EXIT;
            back_light=back_light_set;
	BackLightSet(OSBackLight);
    
        OSLightControl(0);
    }
        P2IES=InputPortState;          
	
	P2IFG = 0;
	
	
}




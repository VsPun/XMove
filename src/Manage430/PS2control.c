#include "config.h"




void SendKeyChar(uchar sendchar)
{
	while (!(IFG1 & UTXIFG0));    //�ȴ����ͼĴ���Ϊ��         
	TXBUF0 = sendchar; 
	
}

u8 DataLengthReturn(u8 ID,u8 Mood)
{
	u8 ReTemp=0;
	
	while(scan_code[ID*16+ReTemp+8*Mood]!=0)
		ReTemp++;
	
	
	return ReTemp;
	
}

void PressKey(u8 KeyData,u8 DelayTime)
{
	
	SendKeyData(KeyData,0);
	delay_ms(40*DelayTime);
	SendKeyData(KeyData,1);
	
}
void PressLongKey(u8 KeyData)  //����������,ֱ�������ı�
{
	if(KeyData!=LastAction)
	{
		
		SendKeyData(LastAction,1);
		delay_ms(2);
		SendKeyData(KeyData,0);
	}
        LastAction=KeyData;
	
}

void MouseHeader()
{
	SendKeyChar(0xEB);
	SendKeyChar(0x90);  //������ʵ�ֽ�
	SendKeyChar(0x04);
	SendKeyChar(0x01);
	SendKeyChar(0x00);   
	
}
void SendMouseKeyData(u8* LastMouseKeyStatus,u8 KeyID,u8 Mode)//mode==0��ʾ�ɿ���Mode==1��ʾ����
{
  //ID =0��1,2  ������Ҽ����м�

   MouseHeader();
  if(Mode==0)  //�ɿ�
    *LastMouseKeyStatus&=~(1<<KeyID);
  else
    *LastMouseKeyStatus|=(1<<KeyID);
  SendKeyChar(*LastMouseKeyStatus);
      for(u8 i=0;i<4;i++)
	{
		SendKeyChar(0x00);
	}
  
  
  
}
void PressMouseKey(u8 KeyID)  
{
	//ID =0��1,2  ��������֡��Ҽ�
	u8 temp,i;
	MouseHeader();
	temp=0x08+(1<<KeyID);
	SendKeyChar(temp);
	for(i=0;i<4;i++)
	{
		SendKeyChar(0x00);
	}
        
        delay_ms(5);
	MouseHeader();
	for(i=0;i<5;i++)
	{
		SendKeyChar(0x00);
	}
	
}
void MoveMouse(signed char X,signed char Y)
{
	MouseHeader();
	if(X>0&&Y>0)
        SendKeyChar(0x08);
	else if(X<0&&Y<0)
		SendKeyChar(0x38);
	else if(X>0&&Y<0)
		SendKeyChar(0x18);
	else 
        SendKeyChar(0x28);
	SendKeyChar(X); 
	SendKeyChar(Y);
	SendKeyChar(0X00);
	SendKeyChar(0X1C);

}
void MoveBall (signed char X)
{
    MouseHeader();
	SendKeyChar(0x08);
	SendKeyChar(0X00);
	SendKeyChar(0X00);
	SendKeyChar(Z);
	SendKeyChar(0X1C);
	
}

//***********************************************************//
u8  rd_pc_kb_buf[10];
u8 pc_kb_buf[10];
u8 pc_kb_bufcnt;

void ps2_init(void)
{
	PS2_DAT_OutDIR();
	PS2_CLK_OutDIR();
        PS2_Clear_DAT();
	PS2_Clear_CLK();
	
	
}
/*F**************************************************************************
* NAME:	rd_pc_kb	
*----------------------------------------------------------------------------
* PARAMS:  None
*
* return:	True or fail
*   
*----------------------------------------------------------------------------
* PURPOSE: read one byte data from pc, suppose the start status has been 
*	Detected by main   
*----------------------------------------------------------------------------
*****************************************************************************/
u8 ReadPCKB(void)
{
	u8 temp;
	u8 p = 1,p_temp;

	temp = 0;
	PS2_CLK_OutDIR();
	PS2_DAT_InDIR();
	// read 8bit data	
	for(u8 x=0;x<8;x++)  
	{
		delay_us(20);
		PS2_Clear_CLK();
		delay_us(40);
		PS2_Set_CLK();
		delay_us(40); // dly_20us  
		if(PS2_DAT_InPort&PS2_DAT ==PS2_DAT) 
		{

			if(p) p = 0;
			else p = 1;
			temp |= 0x01u<<x;

		}
		else
		{
			temp &= ~(0x01u<<x);
		}

	}
	// read parity bit
	delay_us(20);
        PS2_Clear_CLK();
	delay_us(40);
	PS2_Set_CLK() ;
	delay_us(20);
	if(PS2_DAT_InPort&PS2_DAT ==PS2_DAT)
	{
		p_temp = 1;
	}
	else
	{
		p_temp = 0;
	}
	// read stop bit
	delay_us(20);
	PS2_Clear_CLK();
	delay_us(40);
	PS2_Set_CLK();
	delay_us(20);
	if(PS2_DAT_InPort&PS2_DAT !=PS2_DAT)
	{
		return 0;
	}
	// ack
	delay_us(15);

	PS2_DAT_OutDIR();
	PS2_Clear_DAT();
	delay_us(5);
	PS2_CLK_OutDIR();
	 PS2_Clear_CLK();
	delay_us(40);
	PS2_Set_CLK() ;
	delay_us(5);
	PS2_Set_DAT();
	PS2_DAT_InDIR();
        PS2_CLK_InDIR() ;
	

	// check data
	if (p == p_temp)
	{
		rd_pc_kb_buf[0] = temp;  //��������
		return 1;
	}
	else
	{
		return 0;
	}
	
}
u8  WritePCKB (u8 data)
{
	u8 x;
	u8 p = 1;

	PS2_CLK_InDIR();
	PS2_DAT_InDIR();

	// check if the bus is busy  ʱ��Ϊ��ʱ�������߲�æ
	if(PS2_CLK_InPort&PS2_CLK !=PS2_CLK) 
	{
		delay_us(20);
		if(PS2_CLK_InPort&PS2_CLK !=PS2_CLK)
		{
			return 0;
		}
		
	}
	delay_us(40);
	if(PS2_CLK_InPort&PS2_CLK !=PS2_CLK)
	{
		return 0;
	}
	if(PS2_DAT_InPort&PS2_DAT ==PS2_DAT)  //Ĭ��δ����ʱDATΪ�ߵ�ƽ
	{
		return 0;
	}
        //���Դ���
	// --- start transmit --- //
	
	PS2_CLK_OutDIR();
	PS2_DAT_OutDIR();
	// tx start bit
	PS2_Clear_DAT();
	delay_us(20);   //��ʼλ
	PS2_Clear_CLK();
	delay_us(20);
	PS2_Set_CLK();
	delay_us(20);
	// tx 8bit data
	for(x=0;x<8;x++)
	{
		//if( (data&(0x01<<x)) == 1 )  // С��!
		//if( data&(0x01<<x))
		if(data&0x01)
		{
			//p = ~p;
			if(p) p = 0;
			else p = 1;  //p����żУ��
			PS2_Set_DAT();
		}
		else
		{
			PS2_Clear_DAT();
		}
		delay_us(10);
		PS2_Clear_CLK();
		delay_us(40);
		PS2_Set_CLK();
		delay_us(20);
		// test if host driven the ck
		PS2_CLK_InDIR();
		if(PS2_CLK_InPort&PS2_CLK !=PS2_CLK)
		{
			PS2_CLK_InDIR();
			PS2_DAT_InDIR();
			return 0;
		}
		PS2_CLK_OutDIR();
		data = data>>0x01;
	}
	// tx parity bit
	if( p )
	{
		PS2_Set_DAT();
	}
	else
	{
		PS2_Clear_DAT();
	}
	delay_us(20);
	PS2_Clear_CLK();
	delay_us(20);
	PS2_Set_CLK();
	delay_us(20);
	PS2_CLK_InDIR();
	if(PS2_CLK_InPort&PS2_CLK !=PS2_CLK)
	{
		PS2_CLK_InDIR();
		PS2_DAT_InDIR();
		return 0;
	}
	PS2_CLK_OutDIR();

	// stop bit
	PS2_Set_DAT();
      delay_us(20);
	PS2_Clear_CLK();
           delay_us(20);
	PS2_Set_CLK();
	PS2_CLK_InDIR();
	PS2_DAT_InDIR();

	// dly50us̫���ˣ���Vista����������XP�Ͳ���
	delay_ms(2);
	return 1;
}
// �ӻ�����ɾ����ǰ����һ��byte
void rm_pc_kb_buf(void)
{
          u8 x;
	

        for(x=0;x<9;x++)
	{
		pc_kb_buf[x] = pc_kb_buf[x+1];
	}
	pc_kb_buf[9] = 0;
	
	if(pc_kb_bufcnt>0)
		pc_kb_bufcnt--;

}
void add_pc_kb_buf( u8 data )
{
	pc_kb_buf[pc_kb_bufcnt] = data;
	pc_kb_bufcnt++;
	if(pc_kb_bufcnt == 10)  // if overflow, ɾ��ǰ��Ļ���
	{
		//pc_kb_bufcnt = 7;
		rm_pc_kb_buf();
	}
}

void pc_kb_prc(void)
{
	u8 data;
	data = rd_pc_kb_buf[0];
	
	if( data == 0xfe ) // resend 
	{
		return;
	}
	else if(data == 0xee) //echo
	{
		add_pc_kb_buf(0xee);
	}
	else if( data == 0xf2 )
	{
		add_pc_kb_buf(0xfa);
		add_pc_kb_buf(0xab);
		add_pc_kb_buf(0x83);

		
		
	}
	else if( data == 0xf4 )   //��������̵��йأ�������
	{
		
	}
	else if( data < 0x08u )
	{
		if(rd_pc_kb_buf[1] == 0xed)
		{
			
		}
		else if(rd_pc_kb_buf[1] == 0xf0)
		{
			if(data < 0x04u )
			{
				
			} 
		}
		add_pc_kb_buf(0xfa);
	}
	else if(data == 0xff)    //�豸��λ
	{
		pc_kb_bufcnt = 0;			// clear buffer
		add_pc_kb_buf(0xfa);
		add_pc_kb_buf(0xaa);

		
		// boot 
		

	}
	else // ��ʱ����������������
	{
		add_pc_kb_buf(0xfa);
	}
	rd_pc_kb_buf[1] = data;   // �ݴ��յ��������Ա���һ�η���

}
u8  KeyBDCheck()  //����PS2�����Լ칦��
{
  	if(PS2_DAT_InPort&PS2_DAT!=PS2_DAT)    //˵��������Ҫ��
		{
			delay_us(40);
			if(PS2_CLK_InPort&PS2_CLK==PS2_CLK) // ȷ��Ҫ��
			{	
				if ( ReadPCKB() )
				{
					pc_kb_prc();

				}
			}	

		}
		if( pc_kb_bufcnt > 0 )
		{
			if( WritePCKB(pc_kb_buf[0]) )
			{
				rm_pc_kb_buf();
			}
		}
        return 1;
}
  void SendKeyData(u8 KeyData,u8 Mode)  //�ض���SendKeyData����  //mode==0��ʾ�ɿ���Mode==1��ʾ����
{
  

  
	u8 DataLength,i=0;
	DataLength=DataLengthReturn(KeyData,Mode);
        
#if PS2ORUART_EN==1  //PS2ģʽ
  if(Mode==0)
      add_pc_kb_buf(0XF0);
  
	while(i<DataLength)
	{
          add_pc_kb_buf(scan_code[KeyData*16+8*Mode+i]);
	    i++;
        }
    
     
#else
	SendKeyChar(0xEB);
	SendKeyChar(0x90);  //������ʵ�ֽ�
	SendKeyChar(DataLength);
	SendKeyChar(0x00);
	SendKeyChar(0x00);
	
	while(i<DataLength)
	{
		SendKeyChar(scan_code[KeyData*16+8*Mode+i]);
		i++;
	}
	SendKeyChar(0x1C);
	
#endif
  
  
}

/*void PutString_T(unsigned char *ptr)     
{
	while(*ptr != '\0')
	{
		SendKeyChar(*ptr++);                     // ��������
	}
	SendKeyChar(0x0D);
	SendKeyChar(0x0A); //���ͻ���ָ��
}*/
void LooseKey()
{
	SendKeyData(LastAction,1);
}

void NormalKeyboardInput(u8 key)
{
	switch(key)
				{
				case KEYUP_DOWN:
					SendKeyData(VK_UP,VK_KEYDOWN);
					break;
				case KEYUP_UP:
					SendKeyData(VK_UP,VK_KEYUP);
					break;
				case KEYDOWN_DOWN:
					SendKeyData(VK_DOWN,VK_KEYDOWN);
					break;
				case KEYDWUP:
					SendKeyData(VK_DOWN,VK_KEYUP);
					break;
				case KEYLEFT_DOWN:
					SendKeyData(VK_LEFT,VK_KEYDOWN);
					break;
				case KEYLEFT_UP:
					SendKeyData(VK_LEFT,VK_KEYUP);
					break;
				case KEYRIGHT_DOWN:
					SendKeyData(VK_RIGHT,VK_KEYDOWN);
					break;
				case KEYRIGHT_UP:
					SendKeyData(VK_RIGHT,VK_KEYUP);
					break;
				case KEYENTER_DOWN:
					PressKey(VK_ENTER,1);
					break;
				case KEYCANCEL_DOWN:
					PressKey(VK_ESC,1);
					break;
					
					
					
				}

}
u8 DataProcess()
{
     if(Rx_Buff[CHECKDF]!='%')
       return 0;
        WorkID=Rx_Buff[IDDF];
	
	if(WorkMode!=Rx_Buff[WORKMODEDF])
	{
		myMEMSData[IDDF]=100;
#if PCID==8
              if(WorkID==1)
              {
                  WorkMode=Rx_Buff[WORKMODEDF];
              }
#else
                if(WorkID==2)
              {
                  WorkMode=Rx_Buff[WORKMODEDF];
              }
#endif
              
                
		myMEMSData[WORKMODEDF]=WorkMode;
		PutString_SPI(myMEMSData);
             P4OUT&=~BIT7;
              delay_ms(1000);
		P4OUT|=BIT7;	
		
		
	}
	
	//u8 Key=Rx_Buff[KEYDF];
	//u8 Action=Rx_Buff[MOVEFLAG];
	
	if(WorkMode==Rx_Buff[1])
	{
	
				SendAccData(Rx_Buff);   //����ȼ򻯵��м�ڵ���
	
	}
	
	return 1;
	
}
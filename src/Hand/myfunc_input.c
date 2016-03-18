#include "config.h"

#if INPUT_CONTROL_EN==1

#include "textdata.h"
#include "string.h"
u8 PY_index;
  struct t9py_struct t9pyfun; 
void py_init()
{

	
	t9pyfun.pysrf=T9PY;
        t9pyfun.t9PY_addr=t9PY_index1;
        t9pyfun.t9py=0;  
	t9pyfun.firstno=' ';
	t9pyfun.mblen =0;
	
	
}



/*******************************************************************************
**���ܣ����뷨��������
**������magicchip
**���ڣ�20080509
*******************************************************************************/
void py_index_sub(void)
{
	uchar i;
	uchar flag = 0x55;
	unsigned long temp;
	uchar mblentemp;
	mblentemp = t9pyfun.mblen;

	t9pyfun.mblen = 0x00;
	if ((t9pyfun.pysrf == T9PY) && (t9pyfun.firstno != ' '))		   //ƴ�����뷨
	{
		for (i=0;i<t9PY_indexlen[t9pyfun.firstno];i++)
		{
			if (t9pyfun.t9py == (*(t9PY_index_headno[t9pyfun.firstno]+i)).t9PY)
			{
				t9pyfun.mblen++;
				flag = 0xaa;
				t9pyfun.t9PY_addr = (t9PY_index_headno[t9pyfun.firstno]+i);
				for (i++;i<t9PY_indexlen[t9pyfun.firstno];i++)
				{
					if (t9pyfun.t9py == (*(t9PY_index_headno[t9pyfun.firstno]+i)).t9PY)
						t9pyfun.mblen++;
					else 
						break;
				}
				break;
			}
		}
		if (flag == 0x55)		   //û�в�����ȫ��Ӧ��ƴ����ϣ�
		{
			for (i=0;i<t9PY_indexlen[t9pyfun.firstno];i++)
			{
				temp = (*(t9PY_index_headno[t9pyfun.firstno]+i)).t9PY;
				while (temp > t9pyfun.t9py)
				{
					temp >>= 4;
					if (temp == t9pyfun.t9py)
				 {
					 t9pyfun.t9PY_addr = t9PY_index_headno[t9pyfun.firstno]+i;
					 t9pyfun.mblen++;
					 i = t9PY_indexlen[t9pyfun.firstno];
					 flag = 0xaa;
					 break;
				 }
				}			 
			}
			if (flag == 0x55)
			{
				t9pyfun.t9py >>= 4;
				t9pyfun.mblen = mblentemp;
			}
		}

	}
	else if(t9pyfun.pysrf == T9SZ)			 //��������
	{
		t9pyfun.mblen++;
		t9pyfun.t9PY_addr = &t9PY_sz[t9pyfun.firstno];
	}
	else if(t9pyfun.pysrf == T9BD)			//�������
	{
		t9pyfun.mblen++;
		t9pyfun.t9PY_addr = t9PY_index0;
	} 
	else if(t9pyfun.pysrf == T9DX)			//��дӢ����ĸ����
	{
		if ((t9pyfun.firstno>1)&&(t9pyfun.firstno<10))
		{
			t9pyfun.mblen++;
			t9pyfun.t9PY_addr = &t9PY_ABC[t9pyfun.firstno];
		}
	} 
	else if(t9pyfun.pysrf == T9XX)			//СдӢ����ĸ����
	{
		if ((t9pyfun.firstno>1)&&(t9pyfun.firstno<10))
		{
			t9pyfun.mblen++;
			t9pyfun.t9PY_addr = &t9PY_abc[t9pyfun.firstno];
		}
	}
}


void dispsrf(u8 x,u8 y)
{
  u8 *String;
     	 TaskBoxGUI_P(x,y+8*Y_Witch_cn,x+4*X_Witch_cn,y+10*Y_Witch_cn,"���뷽ʽ",0);
                      	FontMode(0,COLOR_Black);
                      
	switch (t9pyfun.pysrf)
	{
	case T9PY:
		String="ƴ��";
		break;
	case T9BD:
		String="���";
		break;
	case T9XX:
		String="Сд";
		break;

	case T9DX:
		String="��д";
		break;
	case T9SZ:
		String="����";
		break;
	default:
		String="δ֪";
		break;
	}
        PutString_cn(x,y+9*Y_Witch_cn,String);

}


void dispsf(u8 x,u8 y,uchar *buff,uchar bufflen)
{
  clrindex(x,y,0);
  Lcd_disp_limlen(x+100,y+Y_Witch_cn,buff,bufflen<19?bufflen:18);
        if(bufflen>18)
        {
          Lcd_disp_limlen(x+100,y+2*Y_Witch_cn,buff+18,bufflen-18<19?bufflen-18:18);
        }
        if(bufflen>36)
            Lcd_disp_limlen(x+100,y+3*Y_Witch_cn,buff+36,bufflen-36);
        SetPaintMode(0,COLOR_Red);
        Line(x+100,y+4*Y_Witch_cn,x+100+9*Y_Witch_cn,y+4*Y_Witch_cn);
	PutString_limit(x+100,y+5*Y_Witch_cn,(u8*)t9pyfun.t9PY_addr->PY,strlenExt(t9pyfun.t9PY_addr->PY));
	Lcd_disp_limlen(x+100,y+6*Y_Witch_cn,(u8*)t9pyfun.t9PY_addr->PY_mb+PY_index*2,18);
	
}


void clrindex(u8 x,u8 y,u8 InitEN)
{
  if(InitEN)
  {
	//  t9pyfun.pysrf=T9PY;
        t9pyfun.t9PY_addr=t9PY_index1;
        t9pyfun.t9py=0;  
	t9pyfun.firstno=' ';
	t9pyfun.mblen =0;
          PY_index=0;
	
  }
      
	SetPaintMode(0,COLOR_White);
	Rectangle(x+100,y+Y_Witch_cn,x+100+9*Y_Witch_cn,y+8*X_Witch_cn-3,1);
	
	
}
void select_data(u8 x,u8 y,uchar *buff,uchar *buffin,uchar bufflen)   //ѡ���ֺ���
{
	
	InnerFuncState=1;
	u8 FlagSet=0;
	u8 GyroKey;		
	while(InnerFuncState==1)
	{      key_data=KEYNULL;
                SetPaintMode(0,COLOR_Red);
                Circle(x+108+FlagSet*X_Witch_cn,y+7*Y_Witch_cn+5,4,1);		
		   	if(GyroControlEN==1)
		{
			ITG3200ReadData();
			ITG3200ShowData();
			delay_ms(150);
		}
		
		else
			
			InputControl();
		
		GyroKey=GyroKeyBoardInputMethod(0,1,200,1000);
		 if(GyroKey!=KEYNULL)
                 key_data=GyroKey;
                GyroKey=KEYNULL;
                  SetPaintMode(0,COLOR_White);
                Circle(x+108+FlagSet*X_Witch_cn,y+7*Y_Witch_cn+5,4,1);
		switch(key_data)
		{
		case KEYUP_UP:
			if(PY_index>8)
			PY_index-=9;
			
		        dispsf(x,y,buff,*buffin);
			break;
		case KEYDOWN_UP:
			if((strlenExt(t9pyfun.t9PY_addr->PY_mb)-(2*(PY_index+8)))>0)
			{
                          PY_index+=9;
			
	    	        dispsf(x,y,buff,*buffin);
			}
			break;
		case KEYCANCEL_UP:
			InnerFuncState=0;
			break;
		case KEYLEFT_UP:
			if(FlagSet>0)
			FlagSet--;
			break;
		case KEYRIGHT_UP:
                      if(FlagSet<8)
			FlagSet++;
             
                        
			break;
	        case KEYENTER_UP:
			PY_index+=(FlagSet);
			if (*(*t9pyfun.t9PY_addr).PY_mb > 0x80)		  //���뺺��
			{
				
				
				buff[(*buffin)++] = *((*t9pyfun.t9PY_addr).PY_mb+PY_index*2);
				buff[(*buffin)++] = *((*t9pyfun.t9PY_addr).PY_mb+PY_index*2+1);
				InnerFuncState=0;
				clrindex(x,y,1);
				
			}
			else 			  //�����ַ�
			{
				
				buff[(*buffin)++] = *((*t9pyfun.t9PY_addr).PY_mb+PY_index);
				//buff[(*buffin)++] = ' ';				
				InnerFuncState=0;
				clrindex(x,y,1);
				
			}
			break;
			
		}
		

		
	}
	
}


/*********************************************************************************************************
** create by :           magicchip
** create data:          2008-06-04
** ��������: 
** ���ܣ�    �������뷨����
** ��ڲ�����
** ���ڲ�����      
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
u8 T9InputChoose(u8 x,u8 y,u8 input_data,u8 *buff,u8 *buffin,uchar bufflen)
{
        
	
	if (input_data==0)		   // ���뷨�л�
	{
		if ((++t9pyfun.pysrf) > T9SZ)
			t9pyfun.pysrf = T9DX; 
		dispsrf(x,y);
		
	}
        
	else if (input_data==KEYLEFT_UP+20)	   // ��������ţ�
	{
		t9pyfun.mblen++;
		t9pyfun.t9PY_addr = t9PY_index0;

	}
	else if ((input_data>0&&input_data<9)||input_data==10||input_data==KEYDOWN_UP+20)	  //��������
	{
		if (t9pyfun.pysrf == T9PY)
		{
			if (input_data>0&&input_data<9)	  //��������
			{
				t9pyfun.mbtimes = 0;
				PY_index = 0;
				if (t9pyfun.firstno == ' ')
					t9pyfun.firstno = input_data+1;
				t9pyfun.t9py = ((t9pyfun.t9py<<4) |  DecToHexFunc(input_data+1) );
				py_index_sub();

			}
			else if (input_data== 10||input_data==KEYDOWN_UP+20)					  //�����л�.
			{
				t9pyfun.t9PY_addr++;
				t9pyfun.mbtimes++;
				PY_index = 0;
				if (t9pyfun.firstno != ' ')
				{
					if (t9pyfun.mbtimes >= t9pyfun.mblen)
					{
						t9pyfun.mbtimes = 0;
						t9pyfun.t9PY_addr -= t9pyfun.mblen;
					}
				}


			}

		}
		else if (t9pyfun.pysrf == T9SZ)				//��������
		{
			
				buff[(*buffin)++] =0x30+input_data+1;
				clrindex(x,y,0);
                              

			
		}
		else if ((t9pyfun.pysrf == T9DX) || (t9pyfun.pysrf == T9XX)) //������ĸ
		{
			if (input_data>0&&input_data<9)	  //��������
			{
				if (t9pyfun.firstno == ' ')
				{
					t9pyfun.mbtimes = 0;
					PY_index = 0;						
					t9pyfun.firstno = input_data;
					t9pyfun.t9py = ((t9pyfun.t9py<<4) | DecToHexFunc(input_data+1));
					py_index_sub();


				} 						
			}

		}											
	}
	else if (input_data==11||input_data==KEYRIGHT_UP+20)    // ɾ����
	{
		if (t9pyfun.mblen > 0)
		{ 										
			if (PY_index == 0)			//ɾ������ƴ��	
			{
				if ((t9pyfun.t9py > 0) && (t9pyfun.pysrf == T9PY))
				{
					t9pyfun.t9py >>= 4;
					if (t9pyfun.t9py == 0)
						clrindex(x,y,1);
					else
					{ 
						py_index_sub();
                                                 clrindex(x,y,0);
					};
				}
				else 
				{
					clrindex(x,y,1);

				}	
                                

			}
                        
			

		}
		else if (bufflen > 2)		   //ɾ������ĺ���.
		{
			buff[--(*buffin)] = 0;
			buff[--(*buffin)] = 0;

		}				
	}

	else if (input_data==9||input_data==KEYUP_UP+20)   //ȷ�ϼ�
	{
		if (t9pyfun.mblen>0)
		{
			if (*buffin < bufflen)
			{       
                           
				select_data(x,y,buff, buffin, bufflen);
                               
			}
			else 
			{
				clrindex(x,y,1);
                                

			}					
		}


	}
	else if (input_data==10)  //����
	{
          return 0;

	}
	return 1;
	
}




u8 T9InputTask(u8 x,u8 y, u8 *Buff,u8 *BuffFlag,u8 Max)
{
 
    u8 VnKbX=1,VnKbY=1,VnKey;
	TaskBoxGUI_P(x,y,x+100+9*Y_Witch_cn,y+Y_Witch_cn+108,"�����������",0);
    
        PutBitmap(x,y+Y_Witch_cn,VKNUM,0);
	FontMode(1,COLOR_White);
        py_init();
         dispsrf(x,y);
	 OS_func_state=1;
	 while (OS_func_state==1)
	 {
                  dispsf(x,y,Buff,*BuffFlag);
		 switch(VirtualNumKeyBoardInput(x,y-Y_Witch_cn,&VnKbX,&VnKbY,&VnKey,0,1))
                 {
                 case 0:
                      return  0;
                 case 1:
                      break;
                 case 2:
                       VnKey+=20;  //��20ƫ����
                       break;
                 }
		T9InputChoose(x,y,VnKey,Buff,BuffFlag,Max);
                
  
	 }
	
         return 1;
	
}

#else 


void clrindex(u8 x,u8 y,u8 InitEN)
{
}
u8 T9InputChoose(u8 x,u8 y,u8 input_data,u8 *buff,u8 *buffin,uchar bufflen)
{
  return 1;
}
void select_data(u8 x,u8 y,uchar *buff,uchar *buffin,uchar bufflen) {}
void dispsf(u8 x,u8 y,uchar *buff,uchar bufflen){}

u8 T9InputTask(u8 x,u8 y, u8 *Buff,u8 *BuffFlag,u8 Max)
{
  MessageGui("��ʾ��Ϣ","�ð汾�޴˹���",0);

  return 0;
}

#endif
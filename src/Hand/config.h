/*
config.h
ELPOS2.0�ĺ��Ŀ����ļ����漰ͷ�ļ������ú�Ԥ����ͷ
Copyright (c) 2010����һ��
buptzym@bupt.edu.cn
All rights reserved.
���������ѧϰ�ο������ṩ�κοɿ��Է���ĵ���������������ҵĿ��




*/
//�������ĺ궨��
#define PCID 1
#define HIDENABLE  0
#define PRESSUREENABLE 0
#define PACKETLENGTH 24
#define NODEGENE 3   //XMOVE�Ĵ���
#define GENEID 0   //����ID




#define SIM_JTAG_CHANGE 1  //Ӳ��ģʽ��1�����������0
#define INPUT_CONTROL_EN  0



#define DEBUG_EN  0


#define  GAME_CONTROL_EN 1



#include <msp430x14x.h>

#include "mydefine.h"
#include "Timer.h"
#include "Nrf24l01.h"
#include "LCDDriver.h"

#include "GUIPack.h"
#include "MemsDriver.h"
#include "ds1302.h"
#include "OS_func.h"
#include "myfunc_game.h"
#include "uart.h"
#include "myfunc_input.h"


#include "BasicAPI.h"

#define UART_SPI_MOOD 1

#define CHSORENG  0  // 0���ģ�1Ӣ��

#define KEY_WirelessReply  1

#include "math.h"
#include "stdlib.h"
#include "string.h"
#include <math.h>
#include <stdio.h>





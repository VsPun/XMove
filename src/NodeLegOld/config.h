/*
config.h
ELPOS2.0�ĺ��Ŀ����ļ����漰ͷ�ļ������ú�Ԥ����ͷ
Copyright (c) 2010����һ��
buptzym@bupt.edu.cn
All rights reserved.
���������ѧϰ�ο������ṩ�κοɿ��Է���ĵ���������������ҵĿ��
*/



//�������ĺ궨��
#define PCID 4
#define HIDENABLE  1
#define PRESSUREENABLE 0
#define PACKETLENGTH 24
#define NODEGENE 1  //XMOVE�Ĵ���
#define GENEID 0   //����ID
 
//��ص��Ժ궨��
 

#define SIM_JTAG_CHANGE 1  //Ӳ��ģʽ��1�����������0
#define DEBUG_EN  0

#include "msp430x14X.h"

#include "mydefine.h"
#include "Timer.h"
#include "Nrf24l01.h"
#include "MemsDriver.h"
#include "math.h"
#include "LEDLight.h"
#include <math.h>

#include "BasicAPI.h"


 
 
#include <msp430x14x.h>
#include "mydefine.h"
#include "Timer.h"
#include "uart.h"
#include "nRF24L01.h"
#include "LEDDriver.h"
#include "BasicAPI.h"
 

//�������ĺ궨��
#define PCID 1
#define HIDENABLE  0
#define PRESSUREENABLE 0
#define PACKETLENGTH 24
#define UARTPACKETLENGTH 24

#define RFMODULENUM 1
 



#define NODEGENE 3   //XMOVE�Ĵ���
#define GENEID 2   //����ID



//��ص��Ժ궨��
 

#define SIM_JTAG_CHANGE 1  //Ӳ��ģʽ��1�����������0
#define DEBUG_EN  0



//�ڶ��׼���ɨ����
#include "config.h"





u8 myMEMSData[PACKETLENGTH];
u8 myReceiveBuff[UARTPACKETLENGTH];
u8 UartReceiveFlag;

u8 Uart_ExMood=0;  //����״̬��
u8 Uart_RxFlag;
const unsigned char Tx_Address[3]={104,103,102};   //���͵�ַ����ʱ����ͨ������޸ĸ�ֵ
const unsigned char Rx_Address[3]={100,101,102};     //������ַ������SPI����ģʽ
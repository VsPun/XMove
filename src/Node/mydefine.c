#include "config.h"
u8 myMEMSData[PACKETLENGTH];
u8 sdddd[PACKETLENGTH];
u8 myReceiveBuff[PACKETLENGTH];
float AccX,AccY,AccZ,GyroX,GyroY,GyroZ,ComX,ComY,ComZ;
/*MEMS���������ݴ洢��������
0:�ӻ�ID  1:����ģʽ 2:������Ӧ��� 3-9:ר������  10-15  �����ǣ�16-21 �ų��ƣ�22-28:���ٶȼƣ�28-31��ѹ���¶�*/

const unsigned char Rx_Address[3]={104,103,102};   //���͵�ַ����ʱ����ͨ������޸ĸ�ֵ
const unsigned char Tx_Address[3]={100,101,102};     //������ַ������SPI����ģʽ



u8 isGyroExisted; 
u8 isAccExisted; 
u8 isComExisted; 
u8 isGyroEnable=1;
u8  myNodeFreshSpeed=2;  //ˢ���ٶ�
u8 myWorkMode=0X40;
 
u8 ChanelID=0; 
const u16 GetCounterByNodeFreshSpeed[]={2000,1000,250,125,62,31,16,7};
u16 GetSendCounter()
{
  return GetCounterByNodeFreshSpeed[myNodeFreshSpeed];
}






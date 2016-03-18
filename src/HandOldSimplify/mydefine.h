/**************�궨��***************/

typedef unsigned char u8;
typedef unsigned int u16;
typedef signed char s8;



#define clrbit(reg,bit) reg &= ~(bit) /*��Ĵ�����ĳ1 ����λ*/
#define bitclr(reg,bit) reg &= ~(bit) /*��Ĵ�����ĳ1 ����λ*/
#define setbit(reg,bit) reg |= (bit) /*���üĴ�����ĳ1 ����λ*/
#define bitset(reg,bit) reg |= (bit) /*���üĴ�����ĳ1 ����λ*/
#define cplbit(reg,bit) reg ^= (bit) /*�ԼĴ�����ĳ1 ����λȡ��*/
#define bitcpl(reg,bit) reg ^= (bit) /*�ԼĴ�����ĳ1 ����λȡ��*/



extern u8 myMEMSData[];
extern u8 myReceiveBuff[];

extern u8 myWorkMode;
extern u8 isGyroEnable;
extern u8 ChanelID; 
extern u8  myNodeFreshSpeed; 



extern u8 isGyroExisted; 
extern u8 isAccExisted; 
extern u8 isComExisted; ; 



u16 GetSendCounter();












extern const unsigned char Rx_Address[];     //������ַ������SPI����ģʽ
extern const unsigned char Tx_Address[];   //���͵�ַ����ʱ����ͨ������޸ĸ�ֵ





extern float AccX,AccY,AccZ,GyroX,GyroY,GyroZ,ComX,ComY,ComZ;

//����洢ƫ�����궨��
#define L3G4200DDF  6
#define HMC5883DF  18
#define ADXL345DF 12

#define KEYDF  4




#define IDDF  0  
#define WORKMODEDF  3
#define NODETYPEDF 1
#define NODEABILITYDF 2


#define VCCFLAG 5
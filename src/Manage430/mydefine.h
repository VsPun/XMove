typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned char u8;
typedef unsigned int u16;
/****************SPI�ṹ����ģ��궨��************/

#define clrbit(reg,bit) reg &= ~(bit) /*��Ĵ�����ĳ1 ����λ*/
#define bitclr(reg,bit) reg &= ~(bit) /*��Ĵ�����ĳ1 ����λ*/
#define setbit(reg,bit) reg |= (bit) /*���üĴ�����ĳ1 ����λ*/
#define bitset(reg,bit) reg |= (bit) /*���üĴ�����ĳ1 ����λ*/
#define cplbit(reg,bit) reg ^= (bit) /*�ԼĴ�����ĳ1 ����λȡ��*/
#define bitcpl(reg,bit) reg ^= (bit) /*�ԼĴ�����ĳ1 ����λȡ��*/




extern unsigned char myMEMSData[];
extern unsigned char myReceiveBuff[];

extern const unsigned char Rx_Address[];   //���͵�ַ����ʱ����ͨ������޸ĸ�ֵ
extern const unsigned char Tx_Address[];   //������ַ������SPI����ģʽ
extern u8 Uart_RxFlag;
extern u8 Uart_ExMood; 
extern u8 UartReceiveFlag;


//����洢ƫ�����궨��
#define L3G4200DDF  6
#define HMC5883DF  18
#define ADXL345DF 12

#define KEYDF  4




#define IDDF  0  
#define WORKMODEDF  3
#define NODETYPEDF 1
#define NODEABILITYDF 2
#define VCCFLAG 4


typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned char u8;
typedef unsigned int u16;
typedef signed char s8;





#define clrbit(reg,bit) reg &= ~(bit) /*��Ĵ�����ĳ1 ����λ*/
#define bitclr(reg,bit) reg &= ~(bit) /*��Ĵ�����ĳ1 ����λ*/
#define setbit(reg,bit) reg |= (bit) /*���üĴ�����ĳ1 ����λ*/
#define bitset(reg,bit) reg |= (bit) /*���üĴ�����ĳ1 ����λ*/
#define cplbit(reg,bit) reg ^= (bit) /*�ԼĴ�����ĳ1 ����λȡ��*/
#define bitcpl(reg,bit) reg ^= (bit) /*�ԼĴ�����ĳ1 ����λȡ��*/





extern unsigned char    OS_index_data,key_data,OS_count,OS_func_state,WirelessProcessFlag,MenuType,
              OS_index_ago,GyroControlEN,AccControlEN,TickControlEN,WirelessEN,UserID,InputPortState,GyroMenuEN,InnerFuncState,KeyRepeatEN;
extern u16 OSBackLight,back_light,back_light_set,OSColor;

extern long mPassWord;
long  strlenExt(const unsigned char *pucSrc);
void InputControl();
uchar uart_key_transform(uchar temp);
void input_command(uchar key_data_temp);
u8 OSFuncKeyInputProcess();
u8 KeyPressDownConfirm(u8 Time);
void FloatToChar(float OriData,u8* Result);
/**************�궨��***************/






extern float AccX,AccY,AccZ,GyroX,GyroY,GyroZ,ComX,ComY,ComZ;

//����洢ƫ�����궨��
#define L3G4200DDF  6
#define HMC5883DF  18
#define ADXL345DF 12
#define BMP085DF 26
#define KEYDF  4
#define PRODF 2

#define IDDF  0  
#define WORKMODEDF  3
 
#define NODETYPEDF 1
 

#define MOVEFLAG 5
 





#define  SIZE_OF_Task 40

struct TaskPCB                     //�˵��ṹ
{
    
	unsigned char *Name;
        u8  (* function)(); 
         unsigned char *Detail;
         u8 PicIndex;
         u8 SubTaskList[10];
      
      
};
struct HeightInfo 
{
	u16 OriginFloor;   //ԭʼ¥����
	u16 FloorStep;     //��׼¥��
	long OriginPressure,T;  //Ĭ���µĴ���ѹ��ֵ
};
extern struct HeightInfo  myHeightInfo;


extern u8 myMEMSData[];
extern u8 myReceiveBuff[];

extern u8 myWorkMode;
extern u8 isGyroEnable;
extern u8 ChanelID; 
extern u8  myNodeFreshSpeed; 



extern u8 isGyroExisted; 
extern u8 isAccExisted; 
extern u8 isComExisted; ; 








const extern struct TaskPCB  myTaskPCB[];
const extern  u8  FullKeyBoardData[];
const extern u8 NumKeyBoardData[];
u8 SendWirelessData();
extern u8 (* OS_func)();  
uint random(uint x,uint y);
u8 GetCurrentKey(u8 *PortStatus1,u8* KeyValue,u8 ThisOrNet) ;
void OSTaskClose();
u8   NetProEnterConfirm();
u8   NetProCloseConfirm(u8 CurrentKey);
void OSLightControl(u8 Mode);
u8 DecToHexFunc(u16 Dec);
extern const unsigned char Rx_Address[];     //������ַ������SPI����ģʽ
extern const unsigned char Tx_Address[];   //���͵�ַ����ʱ����ͨ������޸ĸ�ֵ
extern float AccX,AccY,AccZ,GyroX,GyroY,GyroZ,ComX,ComY,ComZ;
extern unsigned char uart_txbuff[];
extern unsigned char uart_rxbuff[]; 

extern unsigned char wdata[];
extern unsigned char rdata[];


extern u8 myMEMSData[];
//0:�ӻ�ID  1:����ģʽ 2:������Ӧ��� 3-9:ר������  10-15  �����ǣ�16-21 �ų��ƣ�22-28:���ٶȼƣ�28-32��ѹ���¶�*/
//

/************ƴ�����뷨�궨��******************/
#define   T9BD        0x00	  //�������
#define   T9DX        0x01	  //��дӢ��
#define   T9XX        0x02	  //СдӢ��
#define   T9PY        0x03	  //T9ƴ������
#define   T9SZ        0x04	  //T9��������

#define   T9NULL      0x00    //��ѯ���Ϊ��





#define KEYUP_UP  2
#define KEYUP_DOWN 1 
#define KEYDOWN_UP  12
#define KEYDOWN_DOWN   11
#define KEYLEFT_UP    4
#define KEYLEFT_DOWN  3
#define KEYRIGHT_UP  8
#define KEYRIGHT_DOWN   7
#define KEYSPECIAL  88
#define KEYENTER_DOWN  5
#define KEYENTER_UP   6
#define KEYCANCEL_UP    10 
#define KEYCANCEL_DOWN  9
#define KEYNULL  0


#define VKNUM    13
#define VKFULL  12

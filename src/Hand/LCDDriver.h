


/**************************���������ͺ궨��*********************/

#define COLOR_Red		0xf800			//��
#define COLOR_Orange	0xfc00			//��
#define COLOR_Yellow	0xffe0			//��
#define COLOR_Green		0x07e0			//��
#define COLOR_Cyan		0x07ff			//��
#define COLOR_Blue		0x001f			//��
#define COLOR_Purple	0x8010			//��
#define COLOR_Black		0x0000			//��ɫ
#define COLOR_White		0xffff			//��ɫ
#define COLOR_LBlue		0x8618			//����ɫ
#define COLOR_Chess		0x8A65			//����ɫ
#define LCD_X_MAX			320-1			//��Ļ��X���������
#define LCD_Y_MAX			240-1			//��Ļ��Y���������

#define Dis_X_MAX			LCD_X_MAX
#define Dis_Y_MAX			LCD_Y_MAX

#define LCD_INITIAL_COLOR	COLOR_Blue			//����LCD����ʼ��ʱ�ı���ɫ





#define SEND_BUFFER_SIZE	128

typedef	unsigned short LCDBYTE;			//�ض����й�LCD��,Ҳ��LCD���е�����λ��
typedef unsigned short DOTBYTE;			//�ض����й�LCD��,Ҳ��LCD�ĵ�������
typedef signed short  DISWORD;			//�ض�����LCD_Dis.c�ļ���һЩ�м䴦������ݵĿ��


typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef unsigned int   BOOL;

//LCD ��ʼ������
void UART_SendOneByte(unsigned char Dat);
extern void LCD_Initial(void);	//���б�Ҫ�ú�����������˿ڳ�ʼ������λ�Ȳ���
//��ֱ�ߺ�����s_x��s_yΪ��ʼ�㣬e_x��e_yΪ������
extern void Line(LCDBYTE s_x,LCDBYTE s_y,LCDBYTE e_x,LCDBYTE e_y);
void PutString_Test(unsigned char *ptr);
//��ͼģʽ����ǰ��ͼ��ɫ����
extern void SetPaintMode(BYTE Mode,LCDBYTE Color);
//ѡ��Ӣ��(ASCII �ֿ�),�ú���ֻ��ѡ��ģ���ڲ���Ӣ���ֿ�,������ο�ģ��ʹ���ֲ�
extern void FontSet(DOTBYTE Font_NUM,LCDBYTE Color);
//ѡ��Ӣ��(ASCII�ֿ�),�ú���ֻ��ѡ��ģ�������ص���Դ�е�Ӣ���ֿ�
extern void FontSet_rs(LCDBYTE Font_NUM,LCDBYTE Color);
//ѡ�������ֿ�,�ú���ֻ��ѡ��ģ�������ص���Դ�е����ĺ����ֿ�
extern void FontSet_cn(LCDBYTE Font_NUM,LCDBYTE Color);
//��ʾһ������
extern void PutChar_cn(LCDBYTE x,LCDBYTE y,unsigned char  * GB) ;
//��ʾһ�������ַ���
extern void PutString_cn(LCDBYTE x,LCDBYTE y,unsigned char *p);
//�����ַ���ʾ��ģʽ,�����ñ���ɫ
extern void FontMode(BYTE Mode,LCDBYTE FontBackColor);
//��x��y��������д��һ����׼�ַ�
extern void PutChar(DOTBYTE x,DOTBYTE y,char a);
//��x��y������Ϊ��ʼд��һ����׼�ַ���
extern void PutString(DOTBYTE x,DOTBYTE y,u8 *p);

//��x��y������Ϊ���ģ�����һ����
extern void PutPixel(DOTBYTE x,DOTBYTE y);
//��x��y������Ϊ���ģ�����һ��Բ�߻�ʵ��Բ
extern void Circle(DOTBYTE x,DOTBYTE y,DOTBYTE r,BYTE mode);
//����һ����left��top��right��bottomΪ�����Խǵľ��ο����ʵ�ľ���
extern void Rectangle(DOTBYTE left, DOTBYTE top, DOTBYTE right, DOTBYTE bottom, BYTE Mode);
//ֱ��������ʾ
extern void NumberDis(LCDBYTE x,LCDBYTE y,signed long Num,unsigned char len,unsigned char type);
//����������ִ��ȫ��Ļ��������ǰ��ɫ
extern void ClrScreen(BYTE Mode);
//������������
extern void BackLightSet(unsigned short Gra);

//������������,��ʹģ��ı����ɵ�ǰ���Ȼ��䵽���õ�����
extern void BackLightTo(unsigned short Gra);
//���ñ��⻺����ٶ�
extern void BackLightStep(unsigned char Step);
//����ģ�����ʡ��ģʽ
extern void LCDSetSleep(void);
//ʹģ���˳�ʡ��ģʽ
extern void LCDWakeup(void);
//��ʾһ��ģ����Դ�е�λͼ��ָ��λ����

extern void PutBitmap(LCDBYTE x,LCDBYTE y,unsigned short Index,LCDBYTE Color);
void BuadRateSet(unsigned long Br);
extern void Lcd_disp(unsigned int x,unsigned int y,unsigned char *p);
void FontSetTotal(LCDBYTE Color);
void Lcd_disp_limlen(unsigned int x,unsigned int y,unsigned char *p,unsigned char Tlength);
void PutString_limit(DOTBYTE x,DOTBYTE y,u8 *p,u8 length);
void WideLine(u16 x,u16 y,u8 Wide);
void BitRateConfig();

extern DOTBYTE X_Witch;							//���µ�ǰ��ѡ���ASCIIӢ���ֿ���ַ�����X����
extern DOTBYTE Y_Witch;							//���µ�ǰ��ѡ���ASCIIӢ���ֿ���ַ�����Y��߶�
extern DOTBYTE X_Witch_cn;						//���µ�ǰ��ѡ��������ֿ���ַ�����X����
extern DOTBYTE Y_Witch_cn;						//���µ�ǰ��ѡ��������ֿ���ַ�����Y��߶�



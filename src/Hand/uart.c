#include "config.h"





/*******************************************
�������ƣ�Send1Char
��    �ܣ���PC������һ���ַ�
��    ����sendchar--Ҫ���͵��ַ�
����ֵ  ����
********************************************/
void Send1Char(uchar sendchar)
{
	while (!(IFG2 & UTXIFG1));    //�ȴ����ͼĴ���Ϊ��         
	TXBUF1 = sendchar; 
	
}
/*******************************************
�������ƣ�PutSting
��    �ܣ���PC�������ַ���
��    ����ptr--ָ�����ַ�����ָ��
����ֵ  ����
********************************************/
void PutString_C(unsigned char *ptr)     
{
	while(*ptr != '\0')
	{
		Send1Char(*ptr++);                     // ��������
	}
	Send1Char(0x0D);
	Send1Char(0x0A); //���ͻ���ָ��
}

void  Uart_PutString(unsigned char *ptr)
{

		Send1Char('#');
		
		for(u8 i=0;i<32;i++)
	      {
		Send1Char(*(ptr+i));                     // ��������
	      }
		Send1Char('$'); //���ͻ���ָ��

	
}
void UartInit()
{
  //�����趨
	P3SEL |= 0x30;                            // P3.4,5 = USART0 TXD/RXD
	ME1 |= UTXE0 + URXE0;                     // Enable USART0 TXD/RXD
	UCTL0 |= CHAR;                            // 8-bit character
	UTCTL0 |= SSEL1;                          // UCLK = ACLK
	UBR00 = 0x41;                             //  9600
	UBR10 = 0x03;
	UMCTL0 = 0x00;                            // Modulation
	UCTL0 &= ~SWRST;                          // Initialize USART state machine
	//IE1 |= URXIE0;                            // Enable           // Enable    
	
    
	
	P3SEL |= 0xC0;                            // P3.4,5 = USART0 TXD/RXD
	ME2 |= UTXE1 + URXE1;                     // Enable USART0 TXD/RXD
	UCTL1 |= CHAR;                            // 8-bit character
	UTCTL1 |= SSEL1;                          // UCLK = SMCLK
	UBR01 = 0x45;                             // 32k/2400 - 13.65
	UBR11 = 0x00;                             //
	UMCTL1 = 0x4A;                           // Modulation
	UCTL1 &= ~SWRST;                          // Initialize USART state machine
	//IE2 |= URXIE1;                            // Enable USART0 RX interrupt     
}

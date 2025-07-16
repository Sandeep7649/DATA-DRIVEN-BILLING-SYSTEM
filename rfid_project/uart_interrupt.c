#include <lpc21xx.h>  /* lpc21xx definitions         */

#include <string.h>

#include "lcd_defines.h"
#include "lcd.h"
#include "delay.h"

#define uart_int_enable 1

void InitUART1 (void); /* initialize serial interface       */ 
void uart1_tx(char ch);  
char uart1_rx(void);    
void UART1_isr(void) __irq;
void UART0_isr(void) __irq;
char* UART0_RxStr(void);
extern unsigned char i,ch,r_flag;
extern char buff[100];
int j;
char s[30];

void InitUART1 (void) /* initialize serial interface       */ 

{  
  PINSEL0 |=0x00040000;

  U1LCR = 0x83;         /* 8 bits, no parity, 1 stop bit     */

  U1DLL = 97;           /* 9600 baud rate @ cclk/4 vpb clock  */

  U1LCR = 0x03;         /* dlab = 0  */

 

 	
 	#if uart_int_enable > 0

	VICIntSelect = 0x00000000; // IRQ
	
	VICVectAddr0 = (unsigned)UART1_isr;
	
	VICVectCntl0 = 0x20 | 7; /* UART1 Interrupt */
	
	VICIntEnable = 1 << 7; 

 

 // u0iir = 0xc0;

 // u0fcr = 0xc7;

 	U1IER =(0x03);       /* enable uart0 rx and thre interrupts */   

  #endif
}

void uart1_tx(char ch)  /* write character to serial port    */  

{ 

  while (!(U1LSR & 0x20));

  U1THR = ch;                

}
char uart1_rx(void)    /* read character from serial port   */
{                     

  while (!(U1LSR & 0x01));

  return (U1RBR);

}
void uart1_str(char *s)
{

   while(*s)
       uart1_tx(*s++);

}
void uart1_int(unsigned int n)
{

  unsigned char a[10]={0,0,0,0,0,0,0,0,0,0};

  int i=0;

  if(n==0)

  {

    uart1_tx('0');

	return;

  }

  else

  {

     while(n>0)

	 {

	   a[i++]=(n%10)+48;

	   n=n/10;

	 }

	 --i;

	 for(;i>=0;i--)

	 {

	   uart1_tx(a[i]);

	 }

   }

}


void uart1_float(float f)

{

  int x;

  float temp;

  x=f;

  uart1_int(x);

  uart1_tx('.');

  temp=(f-x)*100;

  x=temp;

  uart1_int(x);

}


void  delays(unsigned int  dly)

{  unsigned int  i;


   for(; dly>0; dly--) 

      for(i=1200000; i>0; i--);

}


void InitUART0 (void) /* initialize serial interface       */ 

{  

            		

  PINSEL0 |= 0x00000005; /* enable rxd0 and txd0              */

  U0LCR = 0x83;         /* 8 bits, no parity, 1 stop bit     */

  U0DLL = 97;           /* 9600 baud rate @ cclk/4 vpb clock  */

  U0LCR = 0x03;         /* dlab = 0  */
   
  #if uart_int_enable > 0

  
  VICIntSelect = 0x00000000; // IRQ

  
  VICVectAddr4 = (unsigned)UART0_isr;

  
  VICVectCntl4 = 0x20 | 6; 

  
  VICIntEnable = 1 << 6;   

 

 U0IIR = 0xc0;

 // U0FCR = 0xc7;

  U0IER = 0x03;          

             

  #endif 


}




void uart0_tx(char ch)  /* write character to serial port    */  

{  

	 U0THR = ch;
  while (((U0LSR>>6)&1)==0);                

}


 char uart0_rx(void)    /* read character from serial port   */

{                     

  while (((U0LSR>>0)&1)==0);

  return (U0RBR);

}


void UART0_Str(char *s)

{

   while(*s)
   {

       uart0_tx(*s++);
	   //delay_ms(10);
	}
	uart0_tx(*s);
	//delay_ms(10);

}
char* UART0_RxStr(void)
{
	 j=0;
  	 do{

       s[j]=uart0_rx();
	   delay_ms(10);
	}while(s[j++]!='\n');
	s[j]='\0';
	return s;

}

unsigned int num;


								

/*int main()									 

{

  	inituart1();

 	inituart0();

 	initlcd();

	strlcd("hello");
			delay_s(5);

	cmdlcd(0x01);

  while(1)

  {

		i=0;r_flag=0;

		while(r_flag<2); 

		strlcd("hi");

		cmdlcd(0xc0);

		strlcd(buff);

		uart0_str(buff);

		uart0_str("\r\n");


  }

}	*/


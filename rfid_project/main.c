#include "header.h"
unsigned char r_flag,flag,choice,c;
char buff[100],dummy,pin[5],ch,ch1,rx[30],msg[10]="quit",msg1[10]="exit",msg2[10]="delete";
int i,cs=0,amount,m;
void UART0_isr(void) __irq
{
	int j;
	j=U0IIR;	
	
	if((j & 0x0f)==0x04) //check if receive interrupt
	  {
//	  	CmdLCD(0x01);
	   	ch1= U0RBR;
	  	//CharLCD(ch1);
	   	if(ch1=='$')
		{
		  //CmdLCD(0x01);
		 flag=1;
		 
		 i=0;
		}
		else if((flag==1)&&(ch1!='&'))
		{
			rx[i++]=ch1;
		}
		else if(ch1=='&')
		{
			rx[i]='\0';
			flag=2;
			i=0;
			CmdLCD(0x01);	
		}
	} 
	else
	{
		dummy=U0IIR;
	}
	VICVectAddr = 0; 
} 
void UART1_isr(void) __irq
{
	if((U1IIR & 0x04)) //check if receive interrupt
	  {
	  ch = U1RBR;	/* Read to Clear Receive Interrupt */
	  if(ch==0x02)
		{
			r_flag=1;
			i=0;
	   	}
		else if((r_flag==1)&&(ch!= 0x03))
		{  
				buff[i++] = ch;
		}
		else
		{
			buff[i] = '\0';
			r_flag = 2;
			i=0;
		}
	}
	else
  	{
      dummy=U1IIR;
  	}
   VICVectAddr = 0; /* dummy write */
}

int main()
{
	InitUART1();
	InitUART0();
	Keypad_Init();
	InitLCD(); 
	Int_Enable();
	StrLCD("**V24HE5P7**");
	delay_s(5);
	CmdLCD(0x01);
	StrLCD("RFID BILLING SYSTEM");
	delay_s(5);
	CmdLCD(0x01);
	StrLCD("1:Entry 2:coustmer");
	CmdLCD(0x01);
	StrLCD("3:DELETE");
	CmdLCD(0x01);
	StrLCD("press entry key");
	while(1)
	{
		m:cs=0;
		if(cs==1)
		{
			cs=0;
			CmdLCD(CLEAR_LCD);
			StrLCD("Waiting for card..");
			r_flag=0;
			while(r_flag<2);
			CmdLCD(0x01);
			StrLCD("card read:");
			StrLCD(buff);
			UART0_Str(buff);
			flag=0;
			while(flag<2);
			if(rx[i]=='m')
			{
				StrLCD("manager");
			    delay_s(3);
			}
			else if(rx[i]=='c')
			{
				StrLCD("customer");
			    delay_s(3);
			}
			else
			{
				StrLCD(rx);
			}
			memset(buff,'\0',sizeof(buff));
			memset(rx,'\0',sizeof(rx));
			goto m;		   
			}
		if(cs==3)
		{
			UART0_Str(msg);
			UART0_Str(msg1);
			cs=0;
			r_flag=0;
			while(flag<2);
			CmdLCD(0x01);
			if(strcmp(rx,"list is empty")==0)
			{
				CmdLCD(0x01);
				StrLCD(rx);
				delay_ms(2000);
				CmdLCD(0x01);
				StrLCD("press entry key");
				goto m;
			}
			b:StrLCD("1.cash 2.card");			
			choice=KeyDetect();
			 CmdLCD(0x01);
			 CharLCD(choice);
			 delay_ms(1000);
			CmdLCD(0x01);
			if(choice=='2')
			{
				uart0_tx(choice);		
				a:StrLCD("Waiting for card..");
				r_flag=0;			
				memset(rx,'\0',30);
				while(r_flag<2);
				CmdLCD(0x01);
				StrLCD("card read:");
				StrLCD(buff);
				UART0_Str(buff);
				flag=0;
				while(flag<2);
				StrLCD(rx);
				if(strcmp(rx,"account found")==0)
				{
			
					p:CmdLCD(0x01);
					StrLCD("enter the pin");
					CmdLCD(0xc0);
					for(m=0;m<4;m++)
					{
						pin[m]=KeyDetect();
						delay_ms(200);
						CharLCD(pin[m]);
					}
					pin[m]='\0';
					UART0_Str(pin);
					memset(rx,'\0',sizeof(rx));
					flag=0;
					while(flag<2);
					StrLCD(rx);
					if(strcmp(rx,"wrong_pin")==0)
					{
						 goto p;
					}
					/*memset(rx,'\0',sizeof(rx));
					flag=0;
					while(flag<2);
					StrLCD(rx);*/
					delay_ms(2000);
					if(strcmp(rx,"insuff_balance")==0)
					{													
						CmdLCD(0x01);			    
						goto b;
					}
					else if(strcmp(rx,"paytm success")==0)
					{
						CmdLCD(0x01);
						StrLCD("THANK YOU !");
						delay_ms(2000);
						CmdLCD(0x01);
						StrLCD("press entry key");
						goto m;
					}
					else if(strcmp(rx,"paytm_failed")==0)
					{
					  goto a;
					}

				}
				else
				{
					goto a;
				}
				delay_s(3);
				memset(buff,'\0',sizeof(buff));
				memset(rx,'\0',sizeof(rx));
			}
			else
			{
				uart0_tx(choice);
			l:	CmdLCD(0x01);
					StrLCD("enter the amount");
					CmdLCD(0xC0);
					m=0;
					while(1)
					{
						c=KeyDetect();
						delay_ms(100);
						if((c>='0')&&(c<='9'))
						{
							pin[m]=c;
							CharLCD(pin[m++]);
						}
						else
						{
							pin[m]='\0';
							break;
						}
					}
					UART0_Str(pin);
					flag=0;
					while(flag<2);
					CmdLCD(0x01);
					StrLCD(rx);
					if(strcmp(rx,"retry")==0)
					{
						goto l;
					}
					else if(strcmp(rx,"paymt failed")==0)
					{
						delay_ms(2000);
						CmdLCD(0x01);
						StrLCD("press entry key");
						cs=0;
					}
					if(strcmp(rx,"paymt sucess"))
					{
						CmdLCD(0x01);
						StrLCD("Thank You");
						delay_ms(2000);
						CmdLCD(0x01);
						StrLCD("press entry key");
						cs=0;
					}
		 			}
		}
		if(cs==2)
		{
			UART0_Str(msg);
			UART0_Str(msg2);
			cs=0;
			CmdLCD(0x01);
			StrLCD("delete item");
			r_flag=0;
			while(r_flag<2);
			CmdLCD(0x01);
			StrLCD("card read:");
			StrLCD(buff);
			UART0_Str(buff);
		//	UART0_Str("\r\n");
			flag=0;
			while(flag<2);
		 	if(strcmp(rx,"item deleted")==0)
		 	{
				StrLCD(rx);
				delay_s(3);
			}
			else
			{
				StrLCD("item not found");
				delay_s(2);
			}
			memset(buff,'\0',sizeof(buff));
			memset(rx,'\0',sizeof(rx));	
		}
	}
}

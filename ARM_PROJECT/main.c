#include"myheader.h"
//#define SERIALPORT  1
int found(char * card,BANK *head);
int pin_check(char * card_pin,int card,BANK *head);
void withdraw(int total_amount,char * card,BANK *head);

int  fd,tx=0,total_amount,attempt,pin,choice,balance;
char card_num[10],ch,acc_no[10];
int main()
{
        STOCK *head=NULL,*item=NULL;
	BANK * account=NULL;
        head=syncfromfile(head);
	account=sync_bank(account);
	puts("Opening serial port\n");
	if ((fd = serialOpen ("/dev/ttyUSB0",9600)) < 0)
        {

                fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
                return 1 ;
        }
        puts("serial port is opened\n");
	usleep(10);
	printf(".....STOCK DETAILS....\n");
	print(head);
	printf(".....BANK DETAILS.....\n");
	print_bank(account);
	while(1)
	{
w:
		#ifdef SERIALPORT
		{
			 printf("enter the card number\n");
	       	 	 scanf("%s",card_num);
		}
		#else
		{
			  printf("waiting for the card\n");
			  serialGetstr(fd,card_num);
			  puts(card_num);
			  
		}
		#endif
		if(strcmp(card_num,"12547508")==0)
		{       
			printf(".....manager section.....\n");
		//	ch='m';
		//	sleep(1);
		//	write(fd,&ch,1);
			serialPutstr(fd,"$manager&");
			l1:printf("1 bank 2 stock 3 exit\n");
			scanf("%d",&choice);
			if(choice==3)
				goto w;
			else if(choice==2)
			{
				while(1)
				{
					#ifdef SERIALPORT
					{
						scanf("%s",card_num);
					}
					#else
					{
						serialGetstr(fd,card_num);
					}
					#endif
					if(strcmp(card_num,"quit")!=0)
					{	
						head=add(head,card_num);
						printf("item added\n");
						serialPutstr(fd,"$item added&");

						goto l1;
					}
					else
					{
						break;
					}
				}
				save(head);
			}
			else if(choice==1)
			{
				 while(1)
                        	{
					printf("create new account\n");
					 #ifdef SERIALPORT
                                        {
						 printf("enter the card number\n");
                                                 scanf("%s",card_num);
                                        }
                                        #else
                                        {
						 printf("waiting for the  card number\n");
                                                 serialGetstr(fd,card_num);
                                        }
                                        #endif
                        		if(strcmp(card_num,"quit")!=0)
                        		{
                                		account=add_account(account,card_num);
						goto l1;
                        		}
                        		else
                        		{
						break;
					}
                        	}
				save_bank(account);

			}
			else
			{
				goto l1;
			}
		}
		if(strcmp(card_num,"12553473")==0)
		{
			printf(".....STOCK DETAILS....\n");
			print(head);
			printf("....customer section....\n");
			serialPutstr(fd,"$customer&");
			while(1)
			{
				 #ifdef SERIALPORT
                                   {
					   printf("enter the  card number\n");
                                           scanf("%s",card_num);
                                    }
                                 #else
                                    {
					    printf("waiting for the  card number\n");
                                            serialGetstr(fd,card_num);
                                    }
                                  #endif
				if(strcmp(card_num,"quit")!=0)
				{
  					item=cust_item(head,item,card_num);
				}
				else
				{
					break;
				}
			}		
		}
		if(strcmp(card_num,"exit")==0)
		{
			char ch,k=0;
			print(item);
			total_amount=0;
			if(item==NULL)
			{
				serialPutstr(fd,"$list is empty&");
				goto w;
			}
			else 
			{
				serialPutstr(fd,"$ok&");
			}
			while(item)
			{
				total_amount+=(item->quentity)*(item->cost);
				item=item->link;
			}
			printf("Total Amount:%d\n",total_amount);
			//serialGetstr(fd,card_num);
		a:	ch=serialGetchar(fd);
			if(ch=='1')
			{
l:				printf("offline paymt\n");
				serialGetstr(fd,card_num);
                                int i,amount=0;
				for(i=0;card_num[i];i++)
                                {
					amount=(amount*10+card_num[i])-48;
                                }
				printf("%d",amount);
				if(amount==total_amount)
				{
					printf("paymt sucess\n");
					serialPutstr(fd,"$paymt sucess&");
					goto w;
				}
				else
				{
					k++;
					printf("paymt failed\n");
					if(k<3)
					{
						serialPutstr(fd,"$retry&");
						goto l;
					}
					else
					{
						serialPutstr(fd,"$paymt failed &");
						goto w;
					}
				}				
			}
			else
			{
			#ifdef SERIALPORT
			{
				printf("enter the  card number\n");
				l3:scanf("%s",card_num);
			}
			#else
			{
				printf("waiting for the  card number\n");
				//memset(card_num,'\0',10);
				l3:serialGetstr(fd,card_num);
			}
			#endif
			if(found(card_num,account))
			 {
				 strcpy(acc_no,card_num);
				serialPutstr(fd,"$account found&");
			       	attempt=0;
				 #ifdef SERIALPORT
				 {
					l2: printf("enter the  pin number\n");
					scanf("%d",&pin);
                                 }
                                 #else
                                 {
					l2:printf("waiting for the pin number\n");
               				serialGetstr(fd,card_num);
					int i;
					pin=0;
        	                           for(i=0;i<4;i++)
	                                   {
                	                           pin=(pin*10+card_num[i])-48;
                        	           }
						//printf("PIN=%d\n",pin);

                                 }
                                 #endif
				 if(balance=(pin_check(acc_no,pin,account)))
				 {
					 if(total_amount<balance)
					 {
						 withdraw(total_amount,card_num,account);
						 printf("paymt successfully\n");
						 serialPutstr(fd,"$paytm success&");
						 save(head);
						 total_amount=0;
						 goto w;
						// return 0;
					 }
					 else
					 {
						 printf("insufficient balance\n");
						 serialPutstr(fd,"$insuff_balance&");
						 goto a;

					 }
				 }
				 else if(attempt==3)
				 {
					 printf("paytm falied\n");
					 serialPutstr(fd,"$paytm failed&");
					goto w;
					// break;
				 }
				 else
				 {
					 attempt++;
					 printf("wrong pin\n");
					 serialPutstr(fd,"$wrong pin&");
					 goto l2;
				 }
			 }
			 else
			 {
				 printf("not found\n");
				 serialPutstr(fd,"$not found&");
				 goto l3;
			 }

		}
		}
		if(strcmp(card_num,"delete")==0)
                {
                        printf("....Delete Item....\n");
                        while(1)
                        {
				 #ifdef SERIALPORT
                                  {
					  printf("enter the card number\n");
					  scanf("%s",card_num);
                                  }
				#else
                                  {
					printf("waiting for the  card number\n");
                               		serialGetstr(fd,card_num);
                                  }
                                #endif
                                if(strcmp(card_num,"quit")!=0)
                                {
                                	item=del_item(item,card_num);
                                	printf("item deleted\n");
					serialPutstr(fd,"$item deleted&");

                                }
                                else
                                {
                                        break;
                                }
                        }
                }

	}
	serialClose(fd);
        puts("Closing serial port\n");
        return 0 ;
}

int found(char * card,BANK *head)
{
	BANK *check=NULL;
	check=head;
	printf("Cardno: %s\n",card);
	while(check!=NULL)
	{
		if(strcmp(check->bank_no,card)==0)
		{
			return 1;
		}
		check=check->link;
	}
	return 0;
}
int pin_check(char * card_pin,int card,BANK *head)
{
        BANK *check=NULL;
        check=head;
	printf("card no=%s\n",card_pin);
//	printf("PIN=%d\n",card);
        while(check!=NULL)
        {
                if(strcmp(check->bank_no,card_pin)==0)
                {
			printf("PIN=%d\n",card);
			if(check->pin==card)
			{
				return check->amount;
			}
                }
                check=check->link;
        }
        return 0;
}  
void withdraw(int total_amount,char * card,BANK *head)
{
        BANK *check=NULL;
        check=head;
        while(check!=NULL)
        {
                if(strcmp(check->bank_no,card)==0)
                {
                        check->amount=check->amount-total_amount;
			break;
                }
                check=check->link;
        }
	save_bank(head);
}


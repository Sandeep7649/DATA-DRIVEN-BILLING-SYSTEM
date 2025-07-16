#include"myheader.h"
BANK* add_account(BANK *head,char *card_num)
{
	int flag=0;
        BANK *nu=NULL,*temp=NULL,*check=NULL;
        nu=calloc(1,sizeof(BANK));
        if(nu==NULL)
        {
                printf("node not created\n");
                return head;
	}
	check=head;
	while(check!=NULL)
	{
		
		if(strcmp(check->bank_no,card_num)==0)
		{
			flag++;
	//		return NULL;
			printf("already card is existed\n");
			return head;
		//	break;
		}
		check=check->link;
	}
	if(flag==0)
	{
        	strcpy(nu->bank_no,card_num);
        	printf("enter the name\n");
        	scanf("%s",nu->bank_name);
		printf("enter the pin\n");
		scanf("%d",&nu->pin);
		printf("enter the amount\n");
		scanf("%d",&nu->amount);
		printf("account added\n");
        if(head==NULL)
        {
                head=nu;
        }
        else
        {
                temp=head;
                while(temp->link !=NULL)
                {
                        temp=temp->link;
                }
        	temp->link=nu;
        }
	}
	save_bank(head);
        return head;
}
  

#include"myheader.h"
BANK *sync_bank(BANK *head)
{
        FILE*fp;
        BANK var;
        long int size=sizeof(BANK)-sizeof(BANK *);
        BANK *nu=NULL,*temp=NULL;
        fp=fopen("bank.txt","r");
        if(fp==NULL)
        {
                return head;
        }
        else
        {
                while(fread(&var,size,1,fp)==1)
                {
                        nu=calloc(1,sizeof(BANK));
                        if(nu==NULL)
                        {
                                printf("Node not created\n");
                                return head;
                        }
                        strcpy(nu->bank_no,var.bank_no);
                        strcpy(nu->bank_name,var.bank_name);
			nu->pin=var.pin;
			nu->amount=var.amount;
                        if(head==NULL)
                        {
                                head=nu;
                        }
                        else
                        {
                                for(temp=head;temp->link;temp=temp->link);
                                temp->link=nu;
                        }

                }
        }
        fclose(fp);
	return head;
}

#include"myheader.h"

void save_bank(BANK *head)
{
        FILE *fp;
        long int size=sizeof(BANK)-sizeof(BANK *);
        if(head==NULL)
        {
                printf("List is empty\n");
        }
        else
        {
                fp=fopen("bank.txt","w");
                while(head)
                {
                        fwrite(head,size,1,fp);
                //      fscanf(fp,"%d %s",&head->id,head->name);
                        head=head->link;
                }
                fclose(fp);
        }
}


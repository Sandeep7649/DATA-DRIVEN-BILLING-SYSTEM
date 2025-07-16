#include"myheader.h"

void save(STOCK *head)
{
        FILE *fp;
        long int size=sizeof(STOCK)-sizeof(STOCK *);
        if(head==NULL)
        {
                printf("List is empty\n");
        }
        else
        {
                fp=fopen("stock.txt","w");
                while(head)
                {
                        fwrite(head,size,1,fp);
                //      fscanf(fp,"%d %s",&head->id,head->name);
                        head=head->link;
                }
                fclose(fp);
        }
}


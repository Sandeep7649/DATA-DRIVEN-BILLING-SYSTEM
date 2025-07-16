#include"myheader.h"
STOCK *syncfromfile(STOCK *head)
{
        FILE*fp;
        STOCK var;
        long int size=sizeof(STOCK)-sizeof(STOCK *);
        STOCK *nu=NULL,*temp=NULL;
        fp=fopen("stock.txt","r");
        if(fp==NULL)
        {
                return head;
        }
        else
        {
                while(fread(&var,size,1,fp)==1)
                {
                        nu=calloc(1,sizeof(STOCK));
                        if(nu==NULL)
                        {
                                printf("Node not created\n");
                                return head;
                        }
                        strcpy(nu->id,var.id);
                        strcpy(nu->name,var.name);
			nu->quentity=var.quentity;
			nu->cost=var.cost;
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

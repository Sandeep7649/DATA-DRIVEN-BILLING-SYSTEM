#include"myheader.h"
STOCK * add(STOCK *head,char *card_num)
{
	int flag=0;
        STOCK *nu=NULL,*temp=NULL,*check=NULL;
        nu=calloc(1,sizeof(STOCK));
        if(nu==NULL)
        {
                printf("node not created\n");
                return head;
	}
	check=head;
	while(check!=NULL)
	{
		
		if(strcmp(check->id,card_num)==0)
		{
			check->quentity=check->quentity+1;
			printf("%d",check->quentity);
			flag=1;
			break;
		}
		check=check->link;
	}
	if(flag!=1)
	{
        	strcpy(nu->id,card_num);
        	printf("enter the name\n");
        	scanf("%s",nu->name);
		printf("enter the quentity\n");
		scanf("%d",&nu->quentity);
		printf("enter the cost\n");
		scanf("%d",&nu->cost);

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
	save(head);
        return head;
}
  

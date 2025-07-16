#include"myheader.h"
extern int fd;
STOCK * cust_item(STOCK *head,STOCK *item,char *card_num)
{
	int flag=0,flag1=0;
        STOCK *nu=NULL,*temp=NULL,*check=NULL,*item_check=NULL;
        //nu=calloc(1,sizeof(STOCK));
        /*if(nu==NULL)
        {
                printf("node not created\n");
                return head;
	}*/
	check=head;
	while(check!=NULL)
	{
		
		if(strcmp(check->id,card_num)==0)
		{
			flag=1;
			item_check=item;
			while(item_check)
			{
				if(strcmp(item_check->id,card_num)==0)
	                	{
                        		item_check->quentity=item_check->quentity+1;
					check->quentity-=1;
                    			 flag1=2;
			 		printf("item quentity added\n");
		       			serialPutstr(fd,"$item quentity added&");			
        	        	}
				item_check=item_check->link;
			}
			if(flag1!=2)
			{
				nu=calloc(1,sizeof(STOCK));
				strcpy(nu->id,check->id);
			 	strcpy(nu->name,check->name);
			 	nu->quentity+=1;
			 	check->quentity-=1;
			 	nu->cost=check->cost;
				printf("item added\n");
				    serialPutstr(fd,"$item added&");
				break;
			}
		}
		check=check->link;
	}
	if(flag==0)
	{
		printf("item not found\n");
		    serialPutstr(fd,"$item not found&");

	}
        if(item==NULL)
        {
                item=nu;
        }
        else
        {
                temp=item;
                while(temp->link !=NULL)
                {
                        temp=temp->link;
                }
        temp->link=nu;
        }
        //save(head);
        return item;
}
  

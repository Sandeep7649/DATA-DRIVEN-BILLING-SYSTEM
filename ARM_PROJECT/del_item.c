#include"myheader.h"
STOCK * del_item(STOCK *head,char *card_num)
{
        STOCK *temp=NULL,*prev=NULL;
	if(head==NULL)
	{
		printf("list id empty\n");
	}
	else if(strcmp(card_num,head->id)==0)
	{
		temp=head;
		head=head->link;
		free(temp);
	}
	else
	{
		temp=head;
		while(temp!=NULL && strcmp(temp->id,card_num)!=0)
		{
			prev=temp;
			temp=temp->link;
		}	
		if (temp==NULL)	
		{
			printf("is not found\n");
		}
		else
		{
			prev->link=temp->link;
			free(temp);
			temp=NULL;
		}	
	
	}
        return head;
}
  

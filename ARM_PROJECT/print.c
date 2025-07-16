#include"myheader.h"

void print(STOCK *head)
{
        if(head==NULL)
        {
                printf("\n list is empty\n");
        }
        else
        {
                while(head)
                {
                        printf("%s %s %d %d \n",head->id,head->name,head->quentity,head->cost);
                        head=head->link;
                }
        }
}

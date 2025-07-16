#include"myheader.h"

void print(BANK *head)
{
        if(head==NULL)
        {
                printf("\n list is empty\n");
        }
        else
        {
                while(head)
                {
                        printf("%s %s %d \n",head->bank_no,head->name,head->amount);
                        head=head->link;
                }
        }
}

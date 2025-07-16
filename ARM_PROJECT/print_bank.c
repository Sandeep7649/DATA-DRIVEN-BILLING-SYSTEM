#include"myheader.h"

void print_bank(BANK *head)
{
        if(head==NULL)
        {
                printf("\n list is empty\n");
        }
        else
        {
                while(head)
                {
                        printf("%s %s %d  %d \n",head->bank_no,head->bank_name,head->amount,head->pin);
                        head=head->link;
                }
        }
}

#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <stdarg.h>
#include <unistd.h>
typedef struct stock
{
        char id[10];
        char name[20];
	int quentity;
	int cost; 
        struct stock *link;
}STOCK;
typedef struct bank
{
	char bank_no[10];
	char bank_name[10];
	int amount;
	int pin;
	struct bank *link;
}BANK;
//bank
BANK *add_account(BANK *, char *);
void print_bank(BANK *);
BANK *sync_bank(BANK *);
void save_bank(BANK *);
//delete
STOCK *del_item(STOCK *, char *);
//stock
STOCK *cust_item(STOCK *,STOCK *, char *);
STOCK *add(STOCK *, char *);
STOCK *syncfromfile(STOCK *);
void print(STOCK *);
void save(STOCK *);

#ifndef _UART_H_
#define _UART_H_

int   serialOpen      (const char *device, const int baud) ;
void  serialClose     (const int fd) ;
void  serialFlush     (const int fd) ;
void  serialPutchar   (const int fd, const unsigned char c) ;
char  serialGetchar   (const int fd) ;
int serialGetstr(const int fd,char *ptr);
void serialPutstr(const int fd,char *ptr);

#endif

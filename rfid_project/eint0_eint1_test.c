//eint0_eint1_test.c
#include <LPC21xx.h>
#include "types.h"

#/*define IDLE   0

#define ENTRY  1

#define DELETE 2

#define EXIT   3
   */

#define E0 16    //PINS

#define E1 14

#define E2 15

// channels

#define E0_CH 14

#define E1_CH 15

#define E2_CH 16
extern int cs;


void Int_Enable(void);

void Entry(void)__irq 
{

	cs=1;

	EXTINT=(1<<0);

	VICVectAddr=0;

}

void Delete(void)__irq {

	cs=2;

	EXTINT=(1<<1);

	VICVectAddr=0;

}

void Exit(void)__irq {

	cs=3;

	EXTINT=(1<<2);

	VICVectAddr=0;

}
void Int_Enable(void)
{

	PINSEL0|=0xA0000000;

	PINSEL1|=0x00000001;

	VICIntEnable=(1<<E0_CH)|(1<<E1_CH)|(1<<E2_CH);

	VICVectCntl1=(1<<5)|(E0_CH);

	VICVectAddr1=(u32)Entry;

	VICVectCntl2=(1<<5)|(E1_CH);

	VICVectAddr2=(u32)Delete;

	VICVectCntl3=(1<<5)|(E2_CH);

	VICVectAddr3=(u32)Exit;

	EXTMODE = ((1<<0) | (1<<1) | (1<<2));

	//configure EINT0,EINT1&EINT2 as Falling Edge Triggerd (use EXTPOLAR SFR)

}


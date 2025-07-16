#ifndef _HEADER_H
#define _HEADER_H
#include "types.h"
#include<LPC21XX.h>
#include <string.h>
#include "lcd_defines.h"
#include "lcd.h"
#include "keypad.h"
#include "delay.h"
#include "pin_cfg.h"
#include "pin_cfg_defines.h"

void InitUART1(void); /* Initialize Serial Interface       */ 
void uart0_tx(char ch);  
char UART0_Rx(void);
void InitUART0(void); /* Initialize Serial Interface       */ 
void UART0_Tx(char ch);  
char UART0_Rx(void);
void UART0_Str(char *s);
char * UART0_RxStr(void);
void Int_Enable(void);

#endif

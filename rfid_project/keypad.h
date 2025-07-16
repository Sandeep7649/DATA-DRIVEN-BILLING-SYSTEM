#ifndef _KEYPAD_H
#define _KEYPAD_H
#include "types.h"

#define ROW0 24
#define ROW1 25
#define ROW2 26
#define ROW3 27

#define COL0 28
#define COL1 29
#define COL2 30
#define COL3 31

void Keypad_Init(void);                                                                                                                 

u8 ColScan(void);

u8 RowScan(void);

u8 KeyDetect(void);
#endif


#include<LPC21XX.h>
#include "delay.h"
#include "types.h"
#include "keypad.h"
u8 keypad_lut[4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
 
void Keypad_Init(void)                                                                                                                 
{
	IODIR1|=(15<<ROW0);
}
unsigned char ColScan(void)

{

      return (((IOPIN1>>COL0)&15)<15)?1:0;

}

unsigned char RowCheck(void)
{
	unsigned char rNo;
	for(rNo=0;rNo<4;rNo++)
	{
		IOPIN1=((IOPIN1&~(15<<ROW0))|((~(1<<rNo))<<ROW0));
		if(ColScan()==1)
		{
			break;
		}
	}
	IOPIN1=(IOPIN1&~(15<<ROW0))|(0x0<<ROW0);
	 return rNo;

}
unsigned char ColCheck(void)
{

         unsigned char cNo;
		for(cNo=0;cNo<4;cNo++)
		{
		if(((IOPIN1>>(COL0+cNo))&1)==0)
		{
			break;
		}
		}
       return cNo;

}


unsigned char KeyDetect(void)

{

        unsigned char rowval,colval,keyv;
		
		while(ColScan()==0);
		rowval=RowCheck();
		colval=ColCheck();
		keyv=keypad_lut[rowval][colval];
		while(ColScan());
		return keyv;
}

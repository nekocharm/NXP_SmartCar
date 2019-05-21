#include "include.h"


void ultrasonic_deal()
{
  PIT->CHANNEL[PIT2].TCTRL &= ~PIT_TCTRL_TEN_MASK;//停止定时器
  PIT->CHANNEL[PIT2].LDVAL = 20;//20us
  Trig=1;
	PIT->CHANNEL[PIT2].TCTRL |= PIT_TCTRL_TEN_MASK;//启动定时器
}
/*延时*/
void Delay_Us(uint32 us)
{
  uint32 i, j;   
  for(i=0; i<=us; i++ )
  {
    for(j=0; j<=16; j++)
    {
      asm("nop");
    }
  } 
}
void Delay_Ms(uint32 ms)
{
  uint32 i, j;  
  for(i=0; i<=ms; i++ )
  {
    for(j=0; j<=15000; j++)
    {
      asm("nop");
    }
  } 
}
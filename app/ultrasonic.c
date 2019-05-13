#include "include.h"

extern int32 Distance;

int32 ultrasonic_deal()
{
  Trig=1;
  Delay_Us(20);
  Trig=0;
  return Distance;
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
#include "include.h"

uint16 speed_right()  //b轮子用的是正交解码
{
  uint16 B_rightMotor;
  B_rightMotor=LPLD_FTM_GetCounter(FTM2); //2
  LPLD_FTM_ClearCounter(FTM2);//2
  if(B_rightMotor>31678)
    B_rightMotor=65536-B_rightMotor;
  return B_rightMotor;
}

uint16 speed_left()  //a轮子用的是脉冲累加
{
  uint16 A_leftMotor;
  A_leftMotor = get_counter_value();
  lptmr_init();
  return A_leftMotor;
}

uint16 get_counter_value()  //此段函数为获得脉冲CNR
{
  uint16 dataGet=0;
  dataGet=LPLD_LPTMR_GetPulseAcc();
  LPLD_LPTMR_ResetCounter();  
  lptmr_init();
  return dataGet;
}
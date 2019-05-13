#include "include.h"

void display(uint8 xx)
{
  switch(xx)
  {
  case 1:   //舵机
    GUI_wrlval(0, 2,(int32)(servo_Kp*10),4,1);
    GUI_wrlval(60, 2,(int32)(servo_Kd*10),4,1);
    GUI_wrlval(0, 4,(int32)differ,4,0);
    GUI_wrlval(60, 4,(int32)g_lu_flag,4,0);
    GUI_wrlval(0, 6,(int32)jian_bian,4,0);
    GUI_wrlval(60, 6,(int32)speed_hope,4,0);
    break;
  case 2:  //电机
    GUI_wrlval(0, 2,(int32)leftMotorSpeed,4,0);
    GUI_wrlval(60, 2,(int32)rightMotorSpeed,4,0);
    GUI_wrlval(0, 4,(int32)speed_hope,4,0);
    GUI_wrlval(0, 0,(int32)L_Adjust,4,0);
    GUI_wrlval(60, 0,(int32)R_Adjust,4,0);
    GUI_wrlval(60, 4,(int32)(motor_Kp*10),4,1);
    GUI_wrlval(0, 6,(int32)(motor_Ki*10),4,1);
    GUI_wrlval(60, 6,(int32)(motor_Kd*10),4,1);
    break;
  }
}
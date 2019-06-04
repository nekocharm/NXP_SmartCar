#include "include.h"

void display(uint8 xx)
{
  switch(xx)
  {
  case 1:   //舵机
    GUI_wrlval(0, 2,(int32)(servo_Kp*10),4,1);
    GUI_wrlval(60, 2,(int32)(servo_Kd*10),4,1);
    GUI_wrlval(0, 4,(int32)differ,4,0);
    GUI_wrlval(60, 4,(int32)duty,4,0);
    GUI_wrlval(0, 6,(int32)shangbian,4,0);
    GUI_wrlval(60, 6,(int32)g_lu_flag,4,0);
    break;
  case 2:  //电机
    //GUI_wrlval(0, 2,(int32)leftMotorSpeed,4,0);
    //GUI_wrlval(60, 2,(int32)rightMotorSpeed,4,0);
    //GUI_wrlval(0, 4,(int32)speed_hope,4,0);
    GUI_wrlval(0, 0,(int32)jian_bian ,4,0);
    GUI_wrlval(60, 0,(int32)speed_hope,4,0);
    //GUI_wrlval(60, 4,(int32)(motor_Kp*10),4,1);
    //GUI_wrlval(0, 6,(int32)(motor_Ki*10),4,1);
    //GUI_wrlval(60, 6,(int32)(motor_Kd*10),4,1);
    break;
  case 3:  //电磁
    GUI_wrlval(0, 2,(int32)Inductance[0],4,0);
    GUI_wrlval(60, 2,(int32)Inductance[1],4,0);
    GUI_wrlval(0, 4,(int32)Inductance[2],4,0);//
    GUI_wrlval(60, 4,(int32)Inductance[3],4,0);
    GUI_wrlval(0, 6,(int32)Inductance[4],4,0);
    GUI_wrlval(60, 6,(int32)Inductance[5],4,0);
    break;
  case 4:  //超声波
    GUI_wrlval(0, 2,(int32)Distance,4,1);
    break;
  case 5:  //时间
    GUI_wrlval(0, 4,(int32)second-2,4,0);
    GUI_wrlval(60, 4,(int32)TIME1count,4,0);
  case 6:  //断路
    GUI_wrlval(0, 4,(int32)shangyan,4,0);
    GUI_wrlval(60, 4,(int32)shangbian,4,0);
  case 7:  //断路
    GUI_wrlval(0, 4,(int32)DirectionOut,4,0);
    GUI_wrlval(60, 4,(int32)differ,4,0);
    GUI_wrlval(0, 6,(int32)DirectionErr[0]*100,4,2);
    GUI_wrlval(60, 6,(int32)DirectionErr[2]*100,4,2);
  }
}
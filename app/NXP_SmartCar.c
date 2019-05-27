/**
 * --------------基于"拉普兰德K60底层库V3"的工程（NXP_SmartCar）-----------------
 * @file NXP_SmartCar.c
 * @version 0.0
 * @date 2019-3-20
 * @brief 关于该工程的描述
 *
 * 版权所有:北京拉普兰德电子技术有限公司
 * http://www.lpld.cn
 * mail:support@lpld.cn
 * 硬件平台:  LPLD K60 Card / LPLD K60 Nano
 *
 * 本工程基于"拉普兰德K60底层库V3"开发，
 * 所有开源代码均在"lib"文件夹下，用户不必更改该目录下代码，
 * 所有用户工程需保存在"project"文件夹下，以工程名定义文件夹名，
 * 底层库使用方法见相关文档。 
 *
 */
#include "include.h"

void main (void)
{
  DisableInterrupts;
  init();
  //Delay_Ms(2000);
  EnableInterrupts;
  switch (dip)
  {
    //空程序
    case 0:
      while(1)
      {
        display(1);
      }
    //图像输出
    case 1:
      while(1)
      {
        GUI_wrlval(0, 0,(int32)dip,4,0);
        if(image_getted)
        {
          display(1);
          image_getted=0;  
          image_select((uint8 *)Image_Data, (uint8 *)Pix_Data);
          shanwai_send(1);
        } 
      }
    //电磁输出
    case 2:
      while(1)
      { 
        GUI_wrlval(0, 0,(int32)dip,4,0);
        Sample();
        display(3);
      }
    //调舵机
    case 3:
      while(1)
      { 
        LPLD_FTM_PWM_ChangeDuty(FTM1, FTM_Ch1,1170);//
      }
    //调超声波
    case 4:
      while(1)
      { 
        display(4);
      }
    case 5:
      while(1)
      { 
        display(1);
      }
    /*****************摄像头运行******************/
    case 16:
      par(1);
      Delay_Ms(2000);
      //GUI_wrlval(0, 0,(int32)dip,4,0);
      while(1)
      {
        GO1();
      }
    case 17:
      par(1);
      GUI_wrlval(0, 0,(int32)dip,4,0);
      while(1)
      {
        GO1();
        display(2);
        shanwai_wave();
      }
    /*********************************************/
    
    /******************电磁运行*******************/
    case 32:
      par(1);
      
      GUI_wrlval(0, 0,(int32)dip,4,0);
      while(1)
      {
        GO2();
      }
    case 33:
      par(1);
      
      GUI_wrlval(0, 0,(int32)dip,4,0);
      while(1)
      {
        Sample();
        magnet_deal();
        speedcontrol();
        display(1);
      }
    /*********************************************/
    
    /******************摄像头和电磁运行*******************/
    case 64:
      par(1);
      GUI_wrlval(0, 0,(int32)dip,4,0);
      while(1)
      {
        GO3();
        GUI_wrlval(0, 4,(int32)g_lu_flag,4,0);
      }
    /*********************************************/
  }
}
void GO1()
{
  if(image_getted)
  {
    image_getted=0;  
    image_deal();
    speedcontrol();    
  }
  Servo_PD(differ);
  if(qipao_flag==1)
  {
    speed_hope=0;
		while(1)
    {
      Motor_pid_Stop(leftMotorSpeed,rightMotorSpeed);
    }
  }
  
}
void GO2()
{
  Sample();
  magnet_deal();
  speedcontrol();
  Servo_PD(differ);
}
void GO3()
{
  if(image_getted)
  {
    if(g_lu_flag==8)
    {
      image_getted=0;  
      image_deal();
      speedcontrol();
      Sample();
      magnet_deal();
      Servo_PD(differ);
    }
    else
    {
      image_getted=0;  
      image_deal();
      speedcontrol();
      Servo_PD(differ);
    }
   }
}

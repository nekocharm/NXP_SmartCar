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
  //LPLD_UART_PutChar(UART4, 0x30);
  EnableInterrupts;
  switch (dip)
  {
    case 0:
      while(1)
      {
        GUI_wrlval(0, 0,(int32)dip,4,0);
      }
    case 1:
      while(1)
      {
        GUI_wrlval(0, 0,(int32)dip,4,0);
        if(image_getted)
        {
          image_getted=0;  
          image_select((uint8 *)Image_Data, (uint8 *)Pix_Data);
          shanwai_send(1);
        } 
      }
    case 2:
      while(1)
      { 
        GUI_wrlval(0, 0,(int32)dip,4,0);
      }
    /*****************摄像头运行******************/
    case 16:
      GUI_wrlval(0, 0,(int32)dip,4,0);
      while(1)
      {
        GO1();
        display(1);
        shanwai_wave();
      }
    /*********************************************/
    
    /******************电磁运行*******************/
    case 32:
      GUI_wrlval(0, 0,(int32)dip,4,0);
      while(1)
      {
        GO2();
      }
    /*********************************************/
    
    /******************摄像头和电磁运行*******************/
    case 64:
      GUI_wrlval(0, 0,(int32)dip,4,0);
      while(1)
      {
        GO3();
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
    Servo_PD(differ);
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
    image_getted=0;  
    image_deal();
    speedcontrol();
    Servo_PD(differ);
   }
}

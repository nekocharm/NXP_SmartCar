#ifndef __include_H__
#define __include_H__

#include "common.h"
#include "init.h" //初始化
#include "SCCB.h" //sccb通信
#include "oled.h" //oled显示屏
#include "display.h" //显示信息
#include "Speed_Get.h"  //编码器测速
#include "camera_deal.h" //摄像头处理
#include "eagle.h"  //鹰眼摄像头
#include "image_deal.h"  //图像处理
#include "UART.h" //蓝牙串口通信
#include "control.h"  //电机舵机控制
#include "isr.h"  //中断函数
#include "ultrasonic.h"
#include "par.h"
#include "magnetic.h"

void GO1(void);
void GO2(void);
void GO3(void);

/*舵机参数*/
#define ServoMid 1520
//#define ServoPoint 519
#define ServoLeft 1650//最左pwm波值707
#define ServoRight 1390//最右pwm波值519
extern int16_t differ;//舵机打角

/*图像参数*/
extern GPIO_InitTypeDef Camera1Href;
extern uint8 image_getted;     // 图像采集完成标志，处理后置0
extern uint8 Pix_Data[H][V/8];
extern uint8 Image_Data[ROW][COLUMN];

/*蓝牙串口*/
extern uint8 wait;
extern uint8 recv;  //串口接收字符

/*电机速度*/
extern uint16 leftMotorSpeed;
extern uint16 rightMotorSpeed;

/*拨码开关*/
extern uint8 dip; //拨码开关模式






#endif
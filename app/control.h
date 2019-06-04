#ifndef __control_H__
#define __control_H__
#include "include.h"

/*电机函数*/
void getSpeed();
void speedcontrol();
void Motor_pid(uint16,uint16,uint16);
void Motor_Stop(uint16,uint16);

/*舵机函数*/

void Servo_PD(int16 differ);

/*电机变量*/

extern uint16 speed_hope;
extern uint16 speed_fast;
extern uint16 speed_mid;
extern uint16 speed_low;
extern uint16 speed_huan;
extern uint8 temp_ij;
extern uint8 temp_qp;
extern uint16 speed_jilu[200];
extern uint8 jilu;
extern float Start_Accelerate_Counter;
extern float Start_Accelerate_Step;
extern uint16 rightMotorSpeed;
extern uint16 leftMotorSpeed;
//电机pid参数及临时变量
//输出功率增量=kp*[e(k)-e(k-1)]+ki*e(k)+kd*[e(k)-2e(k-1)+e(k-2)];
extern int16 L_Err_curr;//偏差
extern int16 L_Err_last;//上次偏差
extern int16 L_D_error;//本次偏差减上次偏差
extern int16 L_Err_prelast;//e(k-2)
extern int16 L_DD_error;//e(k)-2e(k-1)+e(k-2)
extern int16 R_Err_curr;//偏差
extern int16 R_Err_last;//上次偏差
extern int16 R_D_error;//本次偏差减上次偏差
extern int16 R_Err_prelast;//e(k-2)
extern int16 R_DD_error;//e(k)-2e(k-1)+e(k-2)

extern float motor_Kp;
extern float motor_Kd;
extern float motor_Ki;
extern int16 L_Adjust;//电机的转速
extern int16 R_Adjust;//电机的转速


/*舵机变量*/

extern int16_t differ;//舵机打角
/*舵机pd参数*/
extern float servo_Kp;//舵机的p值
extern float servo_Kd;//舵机的d值

extern float Err_Curr_Servo;
extern float Err_Last_Servo;
extern float D_Error_Servo;

extern int16 Servo_Control;
//int16 Servo_Control_last = 0;
extern int16 duty;



#endif
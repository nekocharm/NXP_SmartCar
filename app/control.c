#include "include.h"

/*电机变量*/

uint16 speed_hope = 0;
uint16 speed_fast = 0;
uint16 speed_mid = 0;
uint16 speed_low = 0;
uint16 speed_huan=0;
uint8 temp_ij = 0;
uint8 temp_qp = 0;
uint16 speed_jilu[200];
uint8 jilu=1;
float Start_Accelerate_Counter = 0;
float Start_Accelerate_Step = 1;
uint16 rightMotorSpeed=0;
uint16 leftMotorSpeed=0;
//电机pid参数及临时变量
//输出功率增量=kp*[e(k)-e(k-1)]+ki*e(k)+kd*[e(k)-2e(k-1)+e(k-2)];
int16 L_Err_curr=0;//偏差
int16 L_Err_last=0;//上次偏差
int16 L_D_error=0;//本次偏差减上次偏差
int16 L_Err_prelast=0;//e(k-2)
int16 L_DD_error=0;//e(k)-2e(k-1)+e(k-2)
int16 R_Err_curr=0;//偏差
int16 R_Err_last=0;//上次偏差
int16 R_D_error=0;//本次偏差减上次偏差
int16 R_Err_prelast=0;//e(k-2)
int16 R_DD_error=0;//e(k)-2e(k-1)+e(k-2)

float motor_Kp=36;
float motor_Kd=1;
float motor_Ki=5.5;
int16 L_Adjust=0;//电机的转速
int16 R_Adjust=0;//电机的转速


/*舵机变量*/

int16_t differ=0;//舵机打角
/*舵机pd参数*/
float servo_Kp=2;//舵机的p值
float servo_Kd=6;//舵机的d值

float Err_Curr_Servo=0;
float Err_Last_Servo=0;
float D_Error_Servo=0;

int16 Servo_Control=0;
//int16 Servo_Control_last = 0;
int16 duty=0;




/*电机速度控制*/


void getSpeed()
{
	rightMotorSpeed = speed_right();
	leftMotorSpeed = speed_left();
  /*if(!rightMotorSpeed)
		rightMotorSpeed = leftMotorSpeed;
	if(!leftMotorSpeed)
		leftMotorSpeed = rightMotorSpeed;*/
}

void speedup() //加速UniformJia
{
	LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch0, 6000);
	LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, 0);   //3200
	LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch2, 0);
	LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch3, 6000);  //左轮
}

void speeddown()  //减速UniformJian
{
	LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch0, 0);
	LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, 6000);
	LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch2, 6000);
	LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch3, 0);
}

//期望速度选择
void speedcontrol()   //速度控制
{
  //speed_low=1400;
  //Start_Accelerate_Counter = speed_low;
  //speed_hope = speed_low;
	//高速
	if(jian_bian <= 3 )
	{
		temp_ij++;
		if(temp_ij >= 4)
		{
			speed_hope = speed_fast;
			temp_ij = 0;
		}
	}
   //中速
	else if(jian_bian < 12) //10
	{
    speed_hope = speed_mid;
	}
  //低速
  else if(jian_bian<60)
	{
    speed_hope = speed_low;
	}
  /*else if(g_lu_flag==7)
	{
    speed_hope=speed_huan;
	}*/
  if(R_Huan_Flag)
    speed_hope = speed_huan;
}

void Motor_pid(uint16 speedhope,uint16 L_speed_actual,uint16 R_speed_actual)   
{
  
  //pid计算
	L_Err_curr=speedhope-L_speed_actual;
	L_D_error=L_Err_curr-L_Err_last;
	L_DD_error=L_Err_curr+L_Err_prelast-2*L_Err_last;
  L_Adjust+=(int16)(motor_Kp*L_D_error+motor_Ki*L_Err_curr+motor_Kd*L_DD_error);
  
  R_Err_curr=speedhope-R_speed_actual;
	R_D_error=R_Err_curr-R_Err_last;
	R_DD_error=R_Err_curr+R_Err_prelast-2*R_Err_last;
  R_Adjust+=(int16)(motor_Kp*R_D_error+motor_Ki*R_Err_curr+motor_Kd*R_DD_error);

  
	if(L_Adjust<=0)
	{
		if(L_Adjust <= -9000)
			L_Adjust = -9000;
	}
	else if(L_Adjust>=6000)
    L_Adjust=6000;
  if(R_Adjust<=0)
	{
		if(R_Adjust <= -9000)
			R_Adjust = -9000;
	}
	else if(R_Adjust>=6000)
		R_Adjust=6000;
  
	L_Err_prelast=L_Err_last;
	L_Err_last=L_Err_curr;
  R_Err_prelast=R_Err_last;
	R_Err_last=R_Err_curr;

	if(L_Adjust > 0)
	{
    //LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch0, 0);
		//LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, L_Adjust);
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch2, 0);
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch3, L_Adjust);
	}
  else
  {
   // LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch0, 9500);
    //LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, 10000+L_Adjust);
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch2, 9500);
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch3, 10000+L_Adjust);
  }
  if(R_Adjust > 0)
	{
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, 0);
		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch0, R_Adjust);
    //LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch2, 0);
    //LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch3, R_Adjust);
	}
  else
  {
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, 9500);
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch0, 10000+R_Adjust);
   // LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch2, 9500);
    //LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch3, 10000+R_Adjust);
  }
  
}

void Motor_pid_Stop(uint16 L_speed_actual,uint16 R_speed_actual)
{
  if(L_speed_actual>100&&R_speed_actual>100)
    speeddown();
  if(L_speed_actual<10&&R_speed_actual<10)
  {
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch0, 0);
		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, 0);
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch2, 0);
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch3, 0);
    LPLD_FTM_DisableChn(FTM0,FTM_Ch0);
    LPLD_FTM_DisableChn(FTM0,FTM_Ch1);
    LPLD_FTM_DisableChn(FTM0,FTM_Ch2);
    LPLD_FTM_DisableChn(FTM0,FTM_Ch3);
    //Buzzer=1;
    while(1);
  }
	L_Err_curr=0-L_speed_actual;
	L_D_error=L_Err_curr-L_Err_last;
	L_DD_error=L_Err_curr+L_Err_prelast-2*L_Err_last;
  L_Adjust+=(int16)(motor_Kp*L_D_error+motor_Ki*L_Err_curr+motor_Kd*L_DD_error);
  
  R_Err_curr=0-R_speed_actual;
	R_D_error=R_Err_curr-R_Err_last;
	R_DD_error=R_Err_curr+R_Err_prelast-2*R_Err_last;
  R_Adjust+=(int16)(motor_Kp*R_D_error+motor_Ki*R_Err_curr+motor_Kd*R_DD_error);

  
	if(L_Adjust<=0)
	{
		if(L_Adjust <= -9000)
			L_Adjust = -9000;
	}
	else if(L_Adjust>=6000)
    L_Adjust=6000;
  if(R_Adjust<=0)
	{
		if(R_Adjust <= -9000)
			R_Adjust = -9000;
	}
	else if(R_Adjust>=6000)
		R_Adjust=6000;
  
	L_Err_prelast=L_Err_last;
	L_Err_last=L_Err_curr;
  R_Err_prelast=R_Err_last;
	R_Err_last=R_Err_curr;

	if(L_Adjust > 0)
	{
    //LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch0, 0);
		//LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, L_Adjust);
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch2, 0);
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch3, L_Adjust);
	}
  else
  {
   // LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch0, 9500);
    //LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, 10000+L_Adjust);
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch2, 9500);
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch3, 10000+L_Adjust);
  }
  if(R_Adjust > 0)
	{
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, 0);
		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch0, R_Adjust);
    //LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch2, 0);
    //LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch3, R_Adjust);
	}
  else
  {
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch1, 9500);
    LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch0, 10000+R_Adjust);
   // LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch2, 9500);
    //LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch3, 10000+R_Adjust);
  }
}

/*舵机控制*/

void Servo_PD(int16 hope_differ)
{
  Err_Curr_Servo=hope_differ;
  D_Error_Servo=Err_Curr_Servo-Err_Last_Servo;
  Servo_Control=(int16)(servo_Kp*Err_Curr_Servo+servo_Kd*D_Error_Servo);
  Err_Last_Servo=Err_Curr_Servo;
  duty=(int16)(ServoMid+Servo_Control); 
	if(duty <= ServoRight)
		duty=ServoRight;
	else if(duty > ServoLeft)
		duty=ServoLeft;
  LPLD_FTM_PWM_ChangeDuty(FTM1, FTM_Ch1, duty);//PWM改变占空比
}
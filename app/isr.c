#include "include.h"



extern int32 Distance=3000;

uint8 TIME0flag_1ms=0;
uint8 TIME0flag_2ms=0;
uint8 TIME0flag_5ms=0;
uint8 TIME0flag_10ms=0;
uint8 TIME0flag_20ms=0;//定时模块布尔数
uint8 TIME1flag_100ms=0;
uint8 TIME1flag_1s=0;
uint8 TIME1count=0;
uint16 count_pit0 = 0;
uint8 jishi=0;
uint8 dingshijishi=0;
uint8 buzzer_Flag= 0;
uint8 Isr_Count=0;
int16 microsecond=0;
int8 second=0;
uint16 magnet_count=0;
uint8 stop=0;

void pit0_isr(void)                               //测速子程序
{
	static uint8 count_pit0=0;
  LPLD_PIT_DisableIrq(pit0_init_struct);                         //关pit0中断
  TIME0flag_1ms=1;
  count_pit0++;
  /*Uart_Ms_Counter++;
  if(Uart_Ms_Counter > 1000)
    Uart_Ms_Counter = 999;*/
  if(count_pit0%2==0)
    TIME0flag_2ms=1;
  /*microsecond++;
  if(!(microsecond%1000))
  {
     microsecond=0;
     second++;
  }
  if(count_pit0%1000)
  {
    second++;
  }*/
  if(magnet_flag)
  {
    magnet_count++;
    if(magnet_count>999)
    {
      magnet_flag=0;
      magnet_flag1=0;
    }
  }
  if(magnethuan)
  {
    magnet_count++;
    if(magnet_count>1699)
      magnethuan=0;  
  }
  if(qipao_flag)
  {
    magnet_count++;
    if(magnet_count>10)
      stop=1;
  }
  if(second>9)
    jiance_qi=1;
    //duanlu1=1;
  if(second>5)
    duanlu1=1;
  if(count_pit0%5==0)
  {
    TIME0flag_5ms=1;
    Inductance_Get();
  }
  if(count_pit0%10==0)
    TIME0flag_10ms=1; 
  if(count_pit0%20==0)
  {
    TIME0flag_20ms=1;
    getSpeed();
    if(!qipao_flag)
      Motor_pid(speed_hope,leftMotorSpeed,rightMotorSpeed);
    else
      Motor_Stop(leftMotorSpeed,rightMotorSpeed);
    
  }
  if(count_pit0%59==0)
  {
    ultrasonic_deal();
    
  }
  if(count_pit0%100==0)
  {
    TIME1flag_100ms=1;
    TIME1count+=1;
    /*if(buzzer_Flag)
      Buzzer=!Buzzer;
    else
      Buzzer=0;*/
  }
  if(count_pit0==200)
    count_pit0=0;
  if(TIME1count==10)
  {
    TIME1count=0;
    TIME1flag_1s=1;
    second++;
  }
  LPLD_PIT_EnableIrq(pit0_init_struct);                           //开pit0中断
}
void pta_isr(void)
{
	if(LPLD_GPIO_IsPinxExt(PORTA, GPIO_Pin5))
	{
    int32 UltrasonicTime=0;
		LPLD_GPIO_ClearIntFlag(PORTA);
		if(PTA5_I==1)//检测到IO口是高电平，那么就是上升沿
		{
			//如果是上升沿中断
			PIT->CHANNEL[PIT1].TCTRL &= ~PIT_TCTRL_TEN_MASK;//停止定时器
			PIT->CHANNEL[PIT1].LDVAL = 0xFFFFFFFF;//32位定时器，装最大值即可
			PIT->CHANNEL[PIT1].TCTRL |= PIT_TCTRL_TEN_MASK;//启动定时器
		}
		else
		{
			UltrasonicTime = (0xFFFFFFFF - PIT->CHANNEL[PIT1].CVAL)/100;//50M总线时钟，计算得到时间，单位是微秒//50
			Distance = UltrasonicTime * 340/1000;//一秒钟的声音速度假设为340米，由于chaoshengboTime单位是微秒，/1000后得到单位是mm
			PIT->CHANNEL[PIT1].TCTRL &= ~PIT_TCTRL_TEN_MASK;//停止定时器
		}
    if(!Distance)
      Distance=3000;
	}
  if(LPLD_GPIO_IsPinxExt(PORTA, GPIO_Pin12))
	{
		LPLD_GPIO_ClearIntFlag(PORTA);
    Delay_Ms(5);
    if(PTA12_I==0)
    { 
      speed_hope=0;
      display(5);
      while(1)
      {
        getSpeed();
        //Motor_pid_Stop(leftMotorSpeed,rightMotorSpeed);
      }
    } 
	}
}
void ultr_isr()
{
  //Buzzer=!Buzzer;
  PIT->CHANNEL[PIT2].TCTRL &= ~PIT_TCTRL_TEN_MASK;//停止定时器
  Trig=0;
}

  
 
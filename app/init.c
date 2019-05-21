#include "include.h"

/*结构体定义*/
GPIO_InitTypeDef CameraDataPin; 
GPIO_InitTypeDef CameraPclk; 
GPIO_InitTypeDef CameraVsyn;
DMA_InitTypeDef Camera1DMAPin;  //摄像头

FTM_InitTypeDef servo_init_struct;  //舵机
FTM_InitTypeDef motor_init_struct;  //电机

FTM_InitTypeDef ftm_init_struct;  
LPTMR_InitTypeDef lptmr_init_struct;  //编码器

ADC_InitTypeDef adc0_init_struct;
ADC_InitTypeDef adc1_init_struct;   //电磁信号AD
UART_InitTypeDef uart_init_struct;    //蓝牙串口通信
GPIO_InitTypeDef gpio_switch_struct;  //拨码开关
NVIC_InitTypeDef nvic_struct;   //中断优先级设置初始化
GPIO_InitTypeDef ultrasonic_init_struct;   //超声波传感器
PIT_InitTypeDef pit0_init_struct;  //定时器
GPIO_InitTypeDef buzzer_init_struct; //蜂鸣器

/*全局变量定义*/
uint8 dip=0; //拨码开关模式


/*总初始化*/
void init()
{
  switch_init();
  camera_init();  
  Servo_init();
  ADC_init();
  Motor_init();
  Nvic_Init();
  OLED_Init();
  buzzer_init();
  lptmr_init();
  Encoder_init();
  uart_init();
  ultrasonic_init(); 
  pit0_init();
  
}
/*摄像头初始化*/
void camera_init()
{
  SCCB_GPIO_Init();
  while(OV7725_eagle_reg_init()==0);
  
  //CameraDataPin 定义摄像头并行输出引脚
  CameraDataPin.GPIO_PTx = PTC;              //PTC8~15
  CameraDataPin.GPIO_Pins = GPIO_Pin8_15;
  CameraDataPin.GPIO_Dir = DIR_INPUT;        //端口方向为输入
  CameraDataPin.GPIO_Output = OUTPUT_L;         //初始化时输出低电平
  CameraDataPin.GPIO_PinControl = IRQC_DIS| INPUT_PULL_DIS;
  LPLD_GPIO_Init(CameraDataPin);
  
  //CameraPclk 定义摄像头像素中断引脚
  CameraPclk.GPIO_PTx = PTE;              //PTE0
  CameraPclk.GPIO_Pins = GPIO_Pin0;
  CameraPclk.GPIO_Dir = DIR_INPUT;        //端口方向为输入
  CameraPclk.GPIO_Output = OUTPUT_L;         //初始化时输出低电平
  CameraPclk.GPIO_PinControl = IRQC_DMARI| INPUT_PULL_DOWN|INPUT_PULL_DIS;
  LPLD_GPIO_Init(CameraPclk);
  
  //CameraVsyn 定义摄像头场中断引脚
  CameraVsyn.GPIO_PTx = PTC;              //PTB2
  CameraVsyn.GPIO_Pins = GPIO_Pin16;
  CameraVsyn.GPIO_Dir = DIR_INPUT;        //端口方向为输入
  CameraVsyn.GPIO_Output = OUTPUT_L;         //初始化时输出低电平
  CameraVsyn.GPIO_PinControl = IRQC_RI | INPUT_PULL_DOWN|INPUT_PF_EN ;//上升沿触发外部中断，开启上拉或下拉电阻
  CameraVsyn.GPIO_Isr = vsy_isr;
  LPLD_GPIO_Init(CameraVsyn);
  LPLD_GPIO_EnableIrq(CameraVsyn);
 
  //Camera1DMAPin 
  Camera1DMAPin.DMA_CHx = DMA_CH0;
  Camera1DMAPin.DMA_Req = PORTE_DMAREQ;
  Camera1DMAPin.DMA_MajorLoopCnt =V*H/8;
  Camera1DMAPin.DMA_MinorByteCnt = 1;
  Camera1DMAPin.DMA_SourceAddr = (uint32)&PTC->PDIR+1;
  Camera1DMAPin.DMA_SourceAddrOffset = 0;
  Camera1DMAPin.DMA_DestAddr = (uint32)Pix_Data;
  Camera1DMAPin.DMA_DestAddrOffset = 1;
  Camera1DMAPin.DMA_AutoDisableReq = TRUE;
  LPLD_DMA_Init(Camera1DMAPin);
}
/*舵机*/
void Servo_init()
{
  //FTM_InitTypeDef servo_init_struct;
  servo_init_struct.FTM_Ftmx = FTM1;
  servo_init_struct.FTM_Mode = FTM_MODE_PWM ;
  servo_init_struct.FTM_PwmFreq = 75 ;//100
  //servo_init_struct.FTM_PwmDeadtimeCfg = DEADTIME_CH01; 
  //servo_init_struct.FTM_PwmDeadtimeVal=10;
  LPLD_FTM_Init(servo_init_struct);
  
  LPLD_FTM_PWM_Enable( FTM1,FTM_Ch1,ServoMid, PTB1, ALIGN_LEFT );//ServoMid=1438
}

/*电机调速*/
void Motor_init(void)
{
  //FTM_InitTypeDef motor_init_struct;
  motor_init_struct.FTM_Ftmx = FTM0;
	motor_init_struct.FTM_Mode = FTM_MODE_PWM;
	motor_init_struct.FTM_PwmFreq = 10000;
	LPLD_FTM_Init(motor_init_struct);
	LPLD_FTM_PWM_Enable(FTM0,FTM_Ch0,0,PTC1, ALIGN_LEFT);

	motor_init_struct.FTM_Ftmx = FTM0;
	motor_init_struct.FTM_Mode = FTM_MODE_PWM;
	motor_init_struct.FTM_PwmFreq = 10000;
	LPLD_FTM_Init(motor_init_struct);
	LPLD_FTM_PWM_Enable(FTM0,FTM_Ch1,0,PTC2, ALIGN_LEFT);

	motor_init_struct.FTM_Ftmx = FTM0;
	motor_init_struct.FTM_Mode = FTM_MODE_PWM;
	motor_init_struct.FTM_PwmFreq = 10000;
	LPLD_FTM_Init(motor_init_struct);
	LPLD_FTM_PWM_Enable(FTM0,FTM_Ch2,0,PTC3, ALIGN_LEFT);//0

	motor_init_struct.FTM_Ftmx = FTM0;
	motor_init_struct.FTM_Mode = FTM_MODE_PWM;
	motor_init_struct.FTM_PwmFreq = 10000;
	LPLD_FTM_Init(motor_init_struct);
	LPLD_FTM_PWM_Enable(FTM0,FTM_Ch3,0,PTC4, ALIGN_LEFT);//0
}

/*编码器测速正交解码*/
void Encoder_init(void)
{
  //FTM_InitTypeDef ftm_init_struct;
  
  ftm_init_struct.FTM_Ftmx = FTM2;              
  ftm_init_struct.FTM_Mode = FTM_MODE_QD;       
  ftm_init_struct.FTM_QdMode = QD_MODE_CNTDIR;//QD_MODE_PHAB 
  LPLD_FTM_Init(ftm_init_struct);
  
  LPLD_FTM_QD_Enable(FTM2, PTB18, PTB19);
  
  
}

/*电磁信号采集*/
void ADC_init(void)                                             
{ 
  //ADC_InitTypeDef adc0_init_struct;
  //ADC_InitTypeDef adc1_init_struct;
  
  adc0_init_struct.ADC_Adcx = ADC0;
  adc0_init_struct.ADC_DiffMode = ADC_SE;
  adc0_init_struct.ADC_BitMode = SE_10BIT;
  adc0_init_struct.ADC_SampleTimeCfg = SAMTIME_SHORT;
  adc0_init_struct.ADC_HwAvgSel = HW_4AVG;
  adc0_init_struct.ADC_CalEnable = TRUE;
  LPLD_ADC_Init(adc0_init_struct);
  
  LPLD_ADC_Chn_Enable(ADC0 , AD14 );  //C0

  adc1_init_struct.ADC_Adcx = ADC1;
  adc1_init_struct.ADC_DiffMode = ADC_SE;
  adc1_init_struct.ADC_BitMode = SE_10BIT;
  adc1_init_struct.ADC_SampleTimeCfg = SAMTIME_SHORT;
  adc1_init_struct.ADC_HwAvgSel = HW_4AVG;
  adc1_init_struct.ADC_CalEnable = TRUE;
  LPLD_ADC_Init(adc1_init_struct);
  
  LPLD_ADC_Chn_Enable(ADC1 , AD8 );//B0
  LPLD_ADC_Chn_Enable(ADC1 , AD14 );//B10
  LPLD_ADC_Chn_Enable(ADC1 , AD15 );//B11
  LPLD_ADC_Chn_Enable(ADC1 , AD17 );//A17
  LPLD_ADC_Chn_Enable(ADC1 , AD5 );//E1
  

}

/*编码器测速脉冲累加*/
void lptmr_init(void)
{
  //LPTMR_InitTypeDef lptmr_init_struct; 
  
  lptmr_init_struct.LPTMR_Mode=LPTMR_MODE_PLACC;
  lptmr_init_struct.LPTMR_PluseAccInput=LPTMR_ALT2;//PTC15 
  LPLD_LPTMR_Init(lptmr_init_struct);
}

/*蓝牙串口通信*/
void uart_init()
{
  uart_init_struct.UART_Uartx = UART4; 
  uart_init_struct.UART_BaudRate =115200; 
  uart_init_struct.UART_RxPin = PTE25;  
  uart_init_struct.UART_TxPin = PTE24;
  LPLD_UART_Init(uart_init_struct);
}

/*拨码开关*/
void switch_init()
{
  uint8 dipmat[8];
  uint8 aaa,bbb=128;
  gpio_switch_struct.GPIO_PTx =PTD;     
  gpio_switch_struct.GPIO_Pins =GPIO_Pin5|GPIO_Pin6|GPIO_Pin7;
  gpio_switch_struct.GPIO_Dir = DIR_INPUT;  //输入
  gpio_switch_struct.GPIO_PinControl =INPUT_PULL_UP|IRQC_DIS;
  LPLD_GPIO_Init(gpio_switch_struct);
  gpio_switch_struct.GPIO_PTx =PTB;      
  gpio_switch_struct.GPIO_Pins =GPIO_Pin16|GPIO_Pin17|GPIO_Pin20|GPIO_Pin21|GPIO_Pin22;
  LPLD_GPIO_Init(gpio_switch_struct);
  dipmat[0]=PTD5_I;
  dipmat[1]=PTD6_I;
  dipmat[2]=PTD7_I;
  dipmat[3]=PTB16_I;  
  dipmat[6]=PTB21_I;
  dipmat[7]=PTB22_I;//
  dipmat[4]=PTB17_I;//7
  dipmat[5]=PTB20_I;//8
  
  for(aaa=0;aaa<8;aaa++)
  {
    dip=(!dipmat[aaa])*bbb+dip;
    bbb=bbb/2;
  }
}

/*中断优先级设置初始化*/
void Nvic_Init()
{
  nvic_struct.NVIC_IRQChannel=PIT0_IRQn; //定时器中断
  nvic_struct.NVIC_IRQChannelGroupPriority=NVIC_PriorityGroup_3;
  nvic_struct.NVIC_IRQChannelPreemptionPriority=0;
  nvic_struct.NVIC_IRQChannelSubPriority=0;
  nvic_struct.NVIC_IRQChannelEnable=TRUE;
  LPLD_NVIC_Init(nvic_struct);
  
  nvic_struct.NVIC_IRQChannel=PORTC_IRQn; //场中断
  nvic_struct.NVIC_IRQChannelGroupPriority=NVIC_PriorityGroup_3;
  nvic_struct.NVIC_IRQChannelPreemptionPriority=1;
  nvic_struct.NVIC_IRQChannelSubPriority=0;
  nvic_struct.NVIC_IRQChannelEnable=TRUE;
  LPLD_NVIC_Init(nvic_struct); 
}

/*超声波*/
void ultrasonic_init()
{
  ultrasonic_init_struct.GPIO_PTx = PTA;
  ultrasonic_init_struct.GPIO_Pins = GPIO_Pin4;  //trig
  ultrasonic_init_struct.GPIO_Dir = DIR_OUTPUT;
  LPLD_GPIO_Init(ultrasonic_init_struct); 
  
  ultrasonic_init_struct.GPIO_PTx = PTA;
  ultrasonic_init_struct.GPIO_Pins = GPIO_Pin5;  //echo
  ultrasonic_init_struct.GPIO_Dir = DIR_INPUT;
  ultrasonic_init_struct.GPIO_PinControl = IRQC_ET | INPUT_PULL_DOWN; //边沿触发中断,INPUT_PULL_DOWN
  ultrasonic_init_struct.GPIO_Isr = ultrasonic_isr;  
  LPLD_GPIO_Init(ultrasonic_init_struct);  
  LPLD_GPIO_EnableIrq(ultrasonic_init_struct);
  
  pit0_init_struct.PIT_Pitx = PIT1;
  pit0_init_struct.PIT_PeriodUs = 0xffffffff; 
  LPLD_PIT_Init(pit0_init_struct);  
  LPLD_PIT_EnableIrq(pit0_init_struct);
  
  pit0_init_struct.PIT_Pitx=PIT2;
  pit0_init_struct.PIT_PeriodUs=20;
  pit0_init_struct.PIT_Isr=ultr_isr;
  LPLD_PIT_Init(pit0_init_struct);
  LPLD_PIT_EnableIrq(pit0_init_struct);
  PIT->CHANNEL[PIT2].TCTRL &= ~PIT_TCTRL_TEN_MASK;//停止定时器
  
}

/*定时器*/
void pit0_init()
{
  pit0_init_struct.PIT_Pitx=PIT0;
  pit0_init_struct.PIT_PeriodUs=1000;
  pit0_init_struct.PIT_Isr=pit0_isr;
  LPLD_PIT_Init(pit0_init_struct);
  LPLD_PIT_EnableIrq(pit0_init_struct);
}

/*蜂鸣器*/
void buzzer_init(void)
{
  buzzer_init_struct.GPIO_PTx = PTC;//C
  buzzer_init_struct.GPIO_Pins = GPIO_Pin17;//17
  buzzer_init_struct.GPIO_Dir = DIR_OUTPUT;
  buzzer_init_struct.GPIO_Output = OUTPUT_L;
  buzzer_init_struct.GPIO_PinControl = IRQC_DIS;
  LPLD_GPIO_Init(buzzer_init_struct);
}
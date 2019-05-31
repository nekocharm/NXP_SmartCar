#include "include.h"

/**********全局变量定义********/ 
float Direction_P = 1000;	//方向控制P  提高P偏差响应变快 如果发现转弯及时但是过不了就应增大P
float Direction_D = 0;	//方向控制D2000
float DirectionErr[3];	//方向偏差（g_fDirectionError[0]为一对水平电感的差比和偏差）
float DirectionErr_dot[3];//方向偏差微分（g_fDirectionError_dot[0]为一对水平电感的差比和偏差微分）
float DirectionOut=0;	//方向控制输出
float DirectionErrTemp[3][5]={0};
float zhang=1;
float chi=0;
uint8 Flag_Round=0;

uint16 ADGet_Inductance[6][5]={0};
uint16 Inductance[6]={0};
uint16 CircularJudge[6]={0};
float kpyu=0;
float kdyu=0;

void Inductance_Get(void)
{
  int16 i,j,k,temp;
  int16 ad_valueF[5],ad_sum[5];
  for(Isr_Count=0;Isr_Count<5;Isr_Count++)
  {
   // ADGet_Inductance[0][Isr_Count] = (uint16)(LPLD_ADC_Get(ADC0,AD14));//C0//左斜
    //ADGet_Inductance[1][Isr_Count] = (uint16)(LPLD_ADC_Get(ADC1,AD8));//B0//右竖  
    //ADGet_Inductance[2][Isr_Count] = (uint16)(LPLD_ADC_Get(ADC1,AD14));//B10//左竖     
    //ADGet_Inductance[3][Isr_Count] = (uint16)(LPLD_ADC_Get(ADC1,AD15));//B11//右斜  
    ADGet_Inductance[4][Isr_Count] = (uint16)(LPLD_ADC_Get(ADC1,AD17)); //A17//左横  
    ADGet_Inductance[5][Isr_Count] = (uint16)(LPLD_ADC_Get(ADC1,AD5));//E1//右横
  }
  for(i=4;i<6;i++)
  {
    for(j=0;j<4;j++)
    {
      for(k=0;k<4-j;k++)  //五个点感知只需要交换4次
      {
        if(ADGet_Inductance[i][k]>ADGet_Inductance[i][k+1]) //前面的比后面的大则进行交换
        {
          temp=ADGet_Inductance[i][k+1];
          ADGet_Inductance[i][k+1]=ADGet_Inductance[i][k];
          ADGet_Inductance[i][k]= temp;
        }
      }
    }
  }
  for(i=4;i<6;i++)    //求中间三项的和
  {
    ad_sum[i] =ADGet_Inductance[i][1]+ADGet_Inductance[i][2]+ADGet_Inductance[i][3];  //舍去最大最小取中间三项
    ad_valueF[i]=ad_sum[i]/3;  //求平均值
  }	
	for(i=0;i<6;i++)  //将数值中个位数除掉,降低过高精度
  {
	  Inductance[i] = (int16)(ad_valueF[i]/10*10);  //
	}
}
/*void Sample(void)//化简
{ 
  int i;
  Inductance[0]=0;
  Inductance[1]=0;
  Inductance[2]=0;
  Inductance[3]=0;
  Inductance[4]=0;
  Inductance[5]=0;
 
  for(i=0;i<5;i++)
  { 
    Inductance[0]+=ADGet_Inductance[0][i];  
    Inductance[1]+=ADGet_Inductance[1][i];  
    Inductance[2]+=ADGet_Inductance[2][i];
    Inductance[3]+=ADGet_Inductance[3][i];
    Inductance[4]+=ADGet_Inductance[4][i];
    Inductance[5]+=ADGet_Inductance[5][i];  
  }
  Inductance[0]=(uint16)(Inductance[0]/5.0);
  Inductance[1]=(uint16)(Inductance[1]/5.0);
  Inductance[2]=(uint16)(Inductance[2]/5.0);//
  Inductance[3]=(uint16)(Inductance[3]/5.0);
  Inductance[4]=(uint16)(Inductance[4]/5.0);
  Inductance[5]=(uint16)(Inductance[5]/5.0);
  
  /*CircularJudge[0]= Inductance[0]/100;
  CircularJudge[1]= Inductance[1]/100;
  CircularJudge[2]= Inductance[2]/100;
  CircularJudge[3]= Inductance[3]/100;
  CircularJudge[4]= Inductance[4]/100;
  CircularJudge[5]= Inductance[5]/100;
  
}*/
void magnet_deal()
{
  DirectionErr[0] = (float)(Inductance[4]-Inductance[5])/(Inductance[4]+Inductance[5]);//左-右水平电感的差比和作为偏差
  DirectionErr[0] = (DirectionErr[0]>= 1? 1:DirectionErr[0]);    //偏差限幅	
	DirectionErr[0] = (DirectionErr[0]<=-1?-1:DirectionErr[0]);
  //DirectionErr[1] = (float)(Inductance[2]-Inductance[1])/(Inductance[2]+Inductance[1]);//左-右垂直电感的差比和作为偏差
	//DirectionErr[1] = (DirectionErr[1]>= 1? 1:DirectionErr[1]);	//偏差限幅
	//DirectionErr[1] = (DirectionErr[1]<=-1?-1:DirectionErr[1]);	
  //DirectionErr[2] = (float)(Inductance[0]-Inductance[3])/(Inductance[0]+Inductance[3]);//左-右斜电感的差比和作为偏差
	//DirectionErr[2] = (DirectionErr[1]>= 1? 1:DirectionErr[1]);	//偏差限幅
	//DirectionErr[2] = (DirectionErr[1]<=-1?-1:DirectionErr[1]);	
  
   //水平电感偏差微分计算(历史误差队列循环) 
  DirectionErrTemp[0][4] = DirectionErrTemp[0][3];
	DirectionErrTemp[0][3] = DirectionErrTemp[0][2];
	DirectionErrTemp[0][2] = DirectionErrTemp[0][1];
	DirectionErrTemp[0][1] = DirectionErrTemp[0][0];
	DirectionErrTemp[0][0] = DirectionErr[0];
	DirectionErr_dot[0] = 5*(DirectionErrTemp[0][0]-DirectionErrTemp[0][3]);//水平电感的偏差微分
	DirectionErr_dot[0] = (DirectionErr_dot[0]> 0.7? 0.7:DirectionErr_dot[0]);//偏差微分限幅
	DirectionErr_dot[0] = (DirectionErr_dot[0]<-0.7?-0.7:DirectionErr_dot[0]);
  
  //垂直电感偏差微分计算(历史误差队列循环)  
	/*DirectionErrTemp[1][4] = DirectionErrTemp[1][3];
	DirectionErrTemp[1][3] = DirectionErrTemp[1][2];
	DirectionErrTemp[1][2] = DirectionErrTemp[1][1];
	DirectionErrTemp[1][1] = DirectionErrTemp[1][0];
	DirectionErrTemp[1][0] = DirectionErr[1];
	DirectionErr_dot[1] = 5*(DirectionErrTemp[1][0]-DirectionErrTemp[1][3]);//垂直电感的偏差微分
	DirectionErr_dot[1] = (DirectionErr_dot[1]> 0.7? 0.7:DirectionErr_dot[1]);//偏差微分限幅
	DirectionErr_dot[1] = (DirectionErr_dot[1]<-0.7?-0.7:DirectionErr_dot[1]);	*/
  
  /*if(DirectionErr[2]>0.3||DirectionErr[2]<-0.3)
  {
    if(Flag_Round==0)
      Flag_Round=1;
  }
	if(Flag_Round>50) 
		Flag_Round=0;  */   
  
	if(Flag_Round==0)
  {
    if(DirectionErr[0]<0.15&&DirectionErr[0]>-0.15)
    {
      servo_Kp=kpyu;
      servo_Kd=kdyu;
      DirectionOut=DirectionErr[0]*(Direction_P)+DirectionErr_dot[0]*(Direction_D);//这一部分由于水平电感位置不同要根据一定规律设置
    }
    else
    {
      servo_Kp=kpyu;
      servo_Kd=kdyu;
      DirectionOut=DirectionErr[0]*Direction_P+DirectionErr_dot[0]*Direction_D;
    }
  }
	else
  { 
    DirectionOut=DirectionErr[1]*700+DirectionErr_dot[1]*1600;
    Flag_Round=Flag_Round+1;
  }
  differ=(int16)DirectionOut;
}

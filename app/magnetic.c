#include "include.h"

uint16 ADGet_Inductance[6][5]={0};
uint16 Inductance[6]={0};
uint16 CircularJudge[6]={0};

void Inductance_Get(void)
{
  ADGet_Inductance[0][Isr_Count] = (uint16)(LPLD_ADC_Get(ADC0,AD14));//C0
  ADGet_Inductance[1][Isr_Count] = (uint16)(LPLD_ADC_Get(ADC1,AD8));//B0  
  ADGet_Inductance[2][Isr_Count] = (uint16)(LPLD_ADC_Get(ADC1,AD14));//B10     
  ADGet_Inductance[3][Isr_Count] = (uint16)(LPLD_ADC_Get(ADC1,AD15));//B11  
  ADGet_Inductance[4][Isr_Count] = (uint16)(LPLD_ADC_Get(ADC1,AD17)); //A17  
  ADGet_Inductance[5][Isr_Count] = (uint16)(LPLD_ADC_Get(ADC1,AD5));//E1
}
void Sample(void)//化简
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
  Inductance[2]=(uint16)(Inductance[2]/5.0);
  Inductance[3]=(uint16)(Inductance[3]/5.0);
  Inductance[4]=(uint16)(Inductance[4]/5.0);
  Inductance[5]=(uint16)(Inductance[5]/5.0);
  
  CircularJudge[0]= Inductance[0]/100;
  CircularJudge[1]= Inductance[1]/100;
  CircularJudge[2]= Inductance[2]/100;
  CircularJudge[3]= Inductance[3]/100;
  CircularJudge[4]= Inductance[4]/100;
  CircularJudge[5]= Inductance[5]/100;
  
}
void magnet_deal()
{
  
}

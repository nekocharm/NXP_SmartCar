#include "include.h"

int temps;
uint8 shuzu;
uint16 Uart_Ms_Counter=0;
int OutData[4];

void Send_Timer_Start()
{
  Uart_Ms_Counter = 0;
}
void Send_Timer_End()
{
  LPLD_UART_PutChar(UART4,Uart_Ms_Counter/100+0x30);
  LPLD_UART_PutChar(UART4,(Uart_Ms_Counter/10)%10+0x30);
  LPLD_UART_PutChar(UART4,Uart_Ms_Counter%10+0x30);
  LPLD_UART_PutChar(UART4,0x3B);
  Uart_Ms_Counter = 0;
}

unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
{
  unsigned short CRC_Temp;
  unsigned char i,j;
  CRC_Temp = 0xffff;
  for (i=0;i<CRC_CNT; i++)
  {      
    CRC_Temp ^= Buf[i];
    for (j=0;j<8;j++) 
    {
      if (CRC_Temp & 0x01)
        CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
      else
        CRC_Temp = CRC_Temp >> 1;
    }
  }
  return(CRC_Temp);
}

void OutPut_Data(void)
{
	int temp[4] = {0};
	unsigned int temp1[4] = {0};
	unsigned char databuf[10] = {0};
	unsigned char i;
	unsigned short CRC16 = 0;
	for(i=0; i<4; i++)
	{
    temp[i]  = (int)OutData[i];
		temp1[i] = (unsigned int)temp[i];
	}
	for(i=0; i<4; i++)
	{
		databuf[i*2]   = (unsigned char)(temp1[i]%256);
		databuf[i*2+1] = (unsigned char)(temp1[i]/256);
	}
	CRC16 = CRC_CHECK(databuf,8);
	databuf[8] = CRC16%256;
	databuf[9] = CRC16/256;
	for(i=0; i<10; i++)
	{
    LPLD_UART_PutChar(UART4,(int8)databuf[i]);//白点
	}
}

void Send_Wave()
{
  if(differ > 0)
  {
    OutData[0] = 50;
    OutData[1] = Actuall_Ekk;
    OutData[2] = 0;
  }
  else
  {
    OutData[0] = -50;
    OutData[1] = 0;
    OutData[2] = 0-Actuall_Ekk;
  }
  //OutData[3] = suduz;
  OutPut_Data();
}

void shanwai_wave()
{
  LPLD_UART_PutChar(UART4, 0x03);
  LPLD_UART_PutChar(UART4, 0xfc);
  LPLD_UART_PutChar(UART4, (int8)differ);
  LPLD_UART_PutChar(UART4, 0);
  LPLD_UART_PutChar(UART4, 0xfc);
  LPLD_UART_PutChar(UART4, 0x03);
}

/*
发送山外串口图像
s=1：发送160*60压缩图像
s=2：发送未处理边线(160*60)
s=3：发送最终边界(160*60)
*/

void shanwai_send(int s)
{
  int i = 0, j = 0,k = 0;
  uint8 send_date;
  uint8 temp;
  LPLD_UART_PutChar(UART4, 0x01);
  LPLD_UART_PutChar(UART4, 0xfe);
  switch(s)
  {
  case 1:
    for(i=0;i<ROW;i++)             
    {
      for(j=0;j<COLUMN;j += 8)
      { 
        temp = 128;
        send_date = 0;
        for(k=j;k<j+8;k++)
        {
          send_date += Image_Data[i][k]*temp;
          temp = temp/2;
        }
        LPLD_UART_PutChar(UART4,send_date);//发1
      }
    }
    break;
  case 2:
    for(i=0;i<ROW;i++)              
    {
      for(j=0;j<COLUMN;j += 8)
      { 
        temp = 128;
        send_date = 0xff;
        for(k=j;k<j+8;k++)
        {
          if(le_left[i]==k)
            send_date = send_date - temp;
          if(le_right[i]==k)
            send_date = send_date - temp;
          temp /= 2;
        }
        LPLD_UART_PutChar(UART4,send_date);
      }
    }
    break;
  case 3:
    for(i=0;i<ROW;i++)              
    {
      for(j=0;j<COLUMN;j += 8)
      {  
        temp = 128;
        send_date = 0xff;
        for(k=j;k<j+8;k++)
        {
          if(fa_left[i]==k)
            send_date = send_date - temp;
          if(fa_right[i]-1==k)
            send_date = send_date - temp;
          temp /= 2;
        }
        LPLD_UART_PutChar(UART4,send_date);
      }
    } 
    break;
  default:
    break;
  }
  LPLD_UART_PutChar(UART4, 0xfe);
  LPLD_UART_PutChar(UART4, 0x01);
}

/*
发送友善串口图像
*/

void youshan_send()
{
  for(i=0;i<ROW;i++)  
  {
    shuzu=le_right[i]-le_left[i];
    LPLD_UART_PutChar(UART4,(shuzu/100)%10+0x30);
    LPLD_UART_PutChar(UART4,(shuzu/10)%10+0x30);
    LPLD_UART_PutChar(UART4,shuzu%10+0x30);  
  }
  LPLD_UART_PutChar(UART4,0x5b);
  uint16 i=0,j=0; 
  for(i=0;i<10;i++)            //分隔符  发送前九个数字
  {
    LPLD_UART_PutChar(UART4,i+0x30);
    for(j=0;j<9;j++)
      LPLD_UART_PutChar(UART4,0x20);
  }
    for(i=0;i<6;i++)//发送后面8个数字
  {
    LPLD_UART_PutChar(UART4,i+0x30);//发送数字
    for(j=0;j<9;j++)
      LPLD_UART_PutChar(UART4,0x20);
  }
  LPLD_UART_PutChar(UART4,0x0d);//回车键
  LPLD_UART_PutChar(UART4,0x0a);//换行键
  for(i=0;i<10;i++)                //列数符
  {
    for(j=0;j<10;j++)
      LPLD_UART_PutChar(UART4,j+0x30);
  }
  for(i=0;i<6;i++)
  {
    for(j=0;j<10;j++)
      LPLD_UART_PutChar(UART4,j+0x30);
  }
  LPLD_UART_PutChar(UART4,0x0d);
  LPLD_UART_PutChar(UART4,0x0a);
  for(i=0;i<H;i++)               //发图像
  {
    for(j=0;j<V;j++)
    {
      if(!image_pri[i][j])
        LPLD_UART_PutChar(UART4,0x31);//发1
      else
        LPLD_UART_PutChar(UART4,0x20);//白点
    }
    LPLD_UART_PutChar(UART4,0x20);
    LPLD_UART_PutChar(UART4,(i/10) +0x30);//发送列数符号
    LPLD_UART_PutChar(UART4,(i%10) +0x30);
    LPLD_UART_PutChar(UART4,0x0d);
    LPLD_UART_PutChar(UART4,0x0a);
  }
  LPLD_UART_PutChar(UART4,0x5d);
  LPLD_UART_PutChar(UART4,0x0d);
  LPLD_UART_PutChar(UART4,0x0a);
  LPLD_UART_PutChar(UART4,0x7b);
  for(i=0;i<ROW;i++)               //发处理后的图像
  {
    for(j=0;j<COLUMN;j++)
    {
    if(j==fa_left[i])
      LPLD_UART_PutChar(UART4,0x3c);
    else if(j==fa_mid[i])
      LPLD_UART_PutChar(UART4,0x3d);
    else if(j==fa_right[i])
      LPLD_UART_PutChar(UART4,0x3e);
    else if(!Image_Data[i][j])
      LPLD_UART_PutChar(UART4,0x31);//发1
    else
      LPLD_UART_PutChar(UART4,0x20);//白点
    }
    LPLD_UART_PutChar(UART4,0x20);
    LPLD_UART_PutChar(UART4,(i/10) +0x30);//发送列数符号
    LPLD_UART_PutChar(UART4,(i%10) +0x30);
    LPLD_UART_PutChar(UART4,0x0d);
    LPLD_UART_PutChar(UART4,0x0a);
  }
  LPLD_UART_PutChar(UART4,0x0d);
  LPLD_UART_PutChar(UART4,0x0a);
  LPLD_UART_PutChar(UART4,0x7d); 
  LPLD_UART_PutChar(UART4,0x28);
  for(i=0;i<ROW;i++)               //发处理后的图像
  {
    for(j=0;j<COLUMN;j++)
    {
      if(j==le_left[i])
        LPLD_UART_PutChar(UART4,0x3c);
      else if(j==le_mid[i])
        LPLD_UART_PutChar(UART4,0x3d);
      else if(j==le_right[i])
        LPLD_UART_PutChar(UART4,0x3e);
      else if(!Image_Data[i][j])
        LPLD_UART_PutChar(UART4,0x31);//发1
      else
        LPLD_UART_PutChar(UART4,0x20);//白点
    }
    LPLD_UART_PutChar(UART4,0x20);
    LPLD_UART_PutChar(UART4,(i/10) +0x30);//发送列数符号
    LPLD_UART_PutChar(UART4,(i%10) +0x30);
    LPLD_UART_PutChar(UART4,0x0d);
    LPLD_UART_PutChar(UART4,0x0a);
  }
  LPLD_UART_PutChar(UART4,0x0d);
  LPLD_UART_PutChar(UART4,0x0a);
  LPLD_UART_PutChar(UART4,0x29);
  LPLD_UART_PutChar(UART4,0x2a);
  for(i=0;i<ROW;i++)               //发处理后的图像
  {
    for(j=0;j<COLUMN;j++)
    {
      if(j==le_left[i])
        LPLD_UART_PutChar(UART4,0x3c);
      else if(j==le_mid[i])
        LPLD_UART_PutChar(UART4,0x3d);
      else if(j==le_right[i])
        LPLD_UART_PutChar(UART4,0x3e);
      else
        LPLD_UART_PutChar(UART4,0x20);//白点
    }
    LPLD_UART_PutChar(UART4,0x20);
    LPLD_UART_PutChar(UART4,(i/10) +0x30);//发送列数符号
    LPLD_UART_PutChar(UART4,(i%10) +0x30);
    LPLD_UART_PutChar(UART4,0x0d);
    LPLD_UART_PutChar(UART4,0x0a);
  }
  LPLD_UART_PutChar(UART4,0x0d);
  LPLD_UART_PutChar(UART4,0x0a);
  LPLD_UART_PutChar(UART4,0x2b);   
  LPLD_UART_PutChar(UART4,0x23);
  for(i=0;i<ROW;i++)               //发处理后的图像
  {
    for(j=0;j<COLUMN;j++)
    {
      if(i==serTempX[j])
        LPLD_UART_PutChar(UART4,0x3c);
      else
        LPLD_UART_PutChar(UART4,0x20);//白点
    }
    LPLD_UART_PutChar(UART4,0x20);
    LPLD_UART_PutChar(UART4,(i/10) +0x30);//发送列数符号
    LPLD_UART_PutChar(UART4,(i%10) +0x30);
    LPLD_UART_PutChar(UART4,0x0d);
    LPLD_UART_PutChar(UART4,0x0a);
  }
  LPLD_UART_PutChar(UART4,0x0d);
  LPLD_UART_PutChar(UART4,0x0a);
  
  for(i=0;i<ROW;i++)               //发处理后的图像
  {
    if(Lost_Left[i])
      LPLD_UART_PutChar(UART4,0x31);//发1
    else
      LPLD_UART_PutChar(UART4,0x30);//发1
  }
  LPLD_UART_PutChar(UART4,0x0d);
  LPLD_UART_PutChar(UART4,0x0a);
  
  for(i=0;i<ROW;i++)               //发处理后的图像
  {
    if(Lost_Right[i])
      LPLD_UART_PutChar(UART4,0x31);//发1
    else
      LPLD_UART_PutChar(UART4,0x30);//发1
  }
  LPLD_UART_PutChar(UART4,0x0d);
  LPLD_UART_PutChar(UART4,0x0a);
  
  for(i=0;i<ROW;i++)  
  {
    LPLD_UART_PutChar(UART4,(Track_Width[i]/100)+0x30);
    LPLD_UART_PutChar(UART4,(Track_Width[i]/10)%10+0x30);
    LPLD_UART_PutChar(UART4,Track_Width[i]%10+0x30);
    LPLD_UART_PutChar(UART4,0x3B);
  }
  
  LPLD_UART_PutChar(UART4,0x0a);
  LPLD_UART_PutChar(UART4,0x24);
}
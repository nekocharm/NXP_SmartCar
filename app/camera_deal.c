#include "include.h"

extern uint8 Image_Data[ROW][COLUMN]={0};
extern uint8 image_pri[H][V]={0};
extern uint8 Pix_Data[H][V/8]={0};
extern GPIO_InitTypeDef Camera1Vsyn;
extern uint8 image_getted=0;  //采集完成标志

 uint16 SampleRow[ROW] = {
  35,36,37,38,39,40,41,42,43,44,
  45,46,47,48,49,50,51,52,53,54,
  55,56,57,58,59,60,61,63,65,66,
  68,70,72,74,77,79,82,84,87,90,
	93,96,100,104,107,112,116,121,125,131,
	136,142,148,155,161,169,176,185,193,202};//抽样
  /*8,9,10,11,12,13,14,15,16,17,18,
19,20,21,22,23,24,25,26,27,29,31,33,35,37,39,41,43,45,
47,50,52,54,57,59,62,65,69,72,75,79,83,87,92,96,102
,107,113,118,125,132,139,146,155,163,173,182,192,202,213*/

void img_extract(uint8 *dst,uint8 *src,uint32 srclen)
{
	uint8 colour[2]= {1,0};	//0 和 1 分别对应的颜色
	//注：野火的摄像头 0 表示 白色，1表示 黑色
	uint8 tmpsrc;
	while(srclen --)
	{
		src++;
		tmpsrc = *src;
		*dst++ = colour[ (tmpsrc >> 7 ) & 0x01 ];
		*dst++ = colour[ (tmpsrc >> 5 ) & 0x01 ];
		*dst++ = colour[ (tmpsrc >> 3 ) & 0x01 ];
		*dst++ = colour[ (tmpsrc >> 1 ) & 0x01 ];
	}
}

void image_select(uint8 *dst,uint8 *src)
{
	int16 line=0;
	uint8 colour[2]= {1,0};	//0 和 1 分别对应的颜色
	int16 i=0,j=0;
	uint8 tmpsrc=0;
	for(i=0; i<H; i++)
	{
		if(i==SampleRow[line])
		{
			line++;
			for(j=1; j<=V/8; j++)
			{
				tmpsrc = *(src+i*V/8+j);
				*dst++ = colour[ (tmpsrc >> 6 ) & 0x01 ];
				*dst++ = colour[ (tmpsrc >> 4 ) & 0x01 ];
				*dst++ = colour[ (tmpsrc >> 2 ) & 0x01 ];
				*dst++ = colour[ (tmpsrc >> 0 ) & 0x01 ];

			}
		}
	}
}

void vsy_isr()
{
  if(LPLD_GPIO_IsPinxExt(PORTC, GPIO_Pin16))//如果场中断引脚触发中断                                                                                                                                                                        ))//如果场中断引脚触发中断
  {
  //  LPLD_GPIO_DisableIrq(Camera1Vsyn);
    LPLD_DMA_LoadDstAddr(DMA_CH0, Pix_Data);  //检测到场开始信号，加载目的地址
    LPLD_GPIO_ClearIntFlag(PORTE);
    //检测到行开始信号，使能DMA请求
    LPLD_DMA_EnableReq(DMA_CH0);  
    LPLD_GPIO_ClearIntFlag(PORTE);
    image_getted=1;
  }
}
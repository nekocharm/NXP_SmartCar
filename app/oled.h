#ifndef _OLED_H
#define _OLED_H

#include "common.h"
void OLED_Init(void); //初始化
void OLED_CLS(void);  //清除整个屏幕
void OLED_P6x8Str(uint8 x,uint8 y,uint8 ch[]);  //写入一组(6x8)标准ASCII字符串
void OLED_P8x16Str(uint8 x,uint8 y,uint8 ch[]); //写入一组(8x16)标准ASCII字符串
void OLED_PutPixel(uint8 x,uint8 y);  //绘制一个点（x,y）
void OLED_Fill(uint8 dat);      //清屏
void Dly_ms(int ms); //延时
void GUI_wrlval(uint8 x, uint16 y,int32 num,uint8 bits,uint8 dp); //以十进制形式显示长变量，包括小数
uint32 abs(int32 num);  //绝对值
void Draw_BMP(uint8 x0,uint8 y0,uint8 x1,uint8 y1,uint8 bmp[]);
void Draw_image();
#endif
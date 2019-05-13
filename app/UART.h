#include "include.h"
extern uint8 image_pri[H][V];
extern uint8 Image_Data[ROW][COLUMN];
extern uint8 Pix_Data[H][V/8];
extern uint8 serTempX[COLUMN];
extern uint16 Uart_Ms_Counter;

void Send_Timer_Start();
void Send_Timer_End();
void Send_Wave();
void shanwai_send(int s);
void youshan_send();
void shanwai_wave();

#ifndef _INIT_H
#define _INIT_H

#include "common.h"

#define  Buzzer  PTC17_O
#define  Trig    PTA4_O

void init();
void camera_init();
void Servo_init();
void Motor_init(void);
void Encoder_init(void);
void ADC_init(void);                                             
void lptmr_init(void);
void uart_init();
void switch_init();
void Nvic_Init();
void buzzer_init(void);
void ultrasonic_init();
void pit0_init();

#endif
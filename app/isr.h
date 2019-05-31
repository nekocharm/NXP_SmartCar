extern uint8 Isr_Count;
extern int32 Distance;
extern uint8 buzzer_Flag;
extern int16 microsecond;
extern int8 second;
extern int8 minute;
extern PIT_InitTypeDef pit0_init_struct;
extern uint8 TIME1count;

void pit0_isr(void);
void pta_isr(void);
void ultr_isr(void);
//void stop_isr();
//void gpio_isr();
//void image_select(uint8 *,uint8 *);
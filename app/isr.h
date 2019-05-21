extern uint8 Isr_Count;
extern int32 Distance;
extern uint8 buzzer_Flag;

void pit0_isr(void);
void ultrasonic_isr(void);
void ultr_isr(void);
//void image_select(uint8 *,uint8 *);
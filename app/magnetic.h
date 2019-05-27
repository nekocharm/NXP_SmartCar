extern uint16 ADGet_Inductance[6][5];
extern uint16 Inductance[6];
extern uint16 CircularJudge[6];

extern float Direction_P;	//方向控制P  提高P偏差响应变快 如果发现转弯及时但是过不了就应增大P
extern float Direction_D;	//方向控制D
extern float DirectionErr[2];	//方向偏差（g_fDirectionError[0]为一对水平电感的差比和偏差）
extern float DirectionErr_dot[2];//方向偏差微分（g_fDirectionError_dot[0]为一对水平电感的差比和偏差微分）
extern float DirectionOut;	//方向控制输出
extern float DirectionErrTemp[2][5];
extern float kpyu;
extern float kdyu;

extern uint8 Flag_Round;

void Inductance_Get(void);
void Sample(void);
void magnet_deal();

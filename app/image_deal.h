extern uint8 qipaojiance;
extern uint8 le_left[ROW],le_right[ROW],le_mid[ROW];    //左右边线与中线寄存器
extern uint8 fa_left[ROW],fa_mid[ROW],fa_right[ROW];//原始中边线的寄存器
extern uint8 bu_left[ROW],bu_right[ROW];//补线标志位
extern uint8 xun_left[ROW],xun_right[ROW];//是否寻到线了
extern uint8 Lost_Right[ROW];        //右边界丢线
extern uint8 Lost_Left[ROW];        //左边界丢线
extern uint8 Track_Width[ROW];       //赛道宽度
extern int R_Huan_Time_Counter ;    //右环岛辅助计时器
extern int  Actuall_Ekk;         //实际偏差
extern uint8 R_Huan_Flag; 
//extern uint16 le_mid2[ROW];

extern float  kpzhi;//直道的p值
extern float  kdzhi;
extern float  kpyul;//弯道左的p值
extern float  kpyur;

extern float  kdyul;
extern float  kdyul_1;
extern float  kdyul_2;
extern float  kdyul_3;

extern float  kdyur;
extern float  kdyur_1;
extern float  kdyur_2;
extern float  kdyur_3;
extern float  kpyuhuan;
extern float  kdyuhuan;
extern float  kpyuhuan2;
extern float  kdyuhuan2;

extern float weitiao_zhi;
extern float kdweitiao;
extern float weitiaol_1; //用于弯道时舵机p值得调整
extern float weitiaor_1;
extern float weitiaol_2; //用于弯道时舵机p值得调整
extern float weitiaor_2;
extern float weitiaol_3; //用于弯道时舵机p值得调整
extern float weitiaor_3;


extern uint8 qufenl_1; //判断大弯小弯赋予不同的pd值
extern uint8 qufenl_2;
extern uint8 qufenl_3;
extern uint8 qufenr_1;
extern uint8 qufenr_2;
extern uint8 qufenr_3;
extern uint8  daoluyuzhi;//直道的前瞻值
extern uint8  daoluyuwanl;//弯道前瞻值
extern uint8  daoluyuwanr;
extern uint8  daoluyuzhi_temp;
extern uint8  daoluyuwanl_temp;
extern uint8  daoluyuwanr_temp;
extern uint8  yuhuanyuzhi;//圆环前瞻
extern uint8  yuhuanwanl;
extern uint8  yuhuanwanr;
extern uint8  shangyanyu;
extern uint16  shangbian;
extern uint16 shangyan;
extern uint16 daolu;
extern uint16 daolub;//道路有效点
extern uint8 g_lu_flag;

extern uint8 jian_bian;
extern uint8 jian_r;
extern uint8 jian_l;
extern uint8 shang_r;
extern uint8 shang_l;




extern uint8 barjia;
extern uint8 barjian;
extern float kpbar;
extern float kdbar;

extern  uint8 Image_Data[ROW][COLUMN];

extern uint16 i;
extern uint16 j;

extern uint8 qipao_flag;
/*舵机变量*/
extern int16_t differ;//舵机打角
/*舵机pd参数*/
extern float servo_Kp;//舵机的p值
extern float servo_Kd;//舵机的d值

extern float Err_Curr_Servo;
extern float Err_Last_Servo;
extern float D_Error_Servo;

extern int16 Servo_Control;
//int16 Servo_Control_last = 0;
extern int16 duty;




/***************函数*******************/
uint8 Abs(uint8 n,uint8 m);//返回m，n的差值的绝对值
//求长度为iFilterlen的数组bArray的最大值，中间值，最小值，
//传值给mid_num,max_num，min_num
void Get(uint8 *bArray, uint8 iFilterLen) ;
void image_deal();//图像处理模块
uint8 Abs(uint8 n,uint8 m);
void Get(uint8 *bArray, uint8 iFilterLen);
void Qipaojiance();
void Bu_Clear_Flag();  //补线标志位清零
void Find_Bound();   //寻边线
void Save_Bound();   //初始边线保存
void Filters(); //中值滤波
void Bu();  //补线
void Bu_Crossroad(); //十字补线
void Bu_Curve();   //弯道补线
void Start_Flag();  //起跑检测
void Find_Mid();  //补完线重新计算中点
void Calculation_Differ(); //计算打角differ
void Calculation_Pd();//计算舵机Pd值
void Huan_Bu();
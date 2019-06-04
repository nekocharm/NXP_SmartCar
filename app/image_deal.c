#include "include.h"

#define ABS(i) (((i)>=0)?(i):(0-i))//绝对值
uint8  Image_Data_1[ROW/2][COLUMN/2]; //储存压缩后的图像
uint8 Temp;
uint8 Temp_1;
uint16 i = 0;
uint16 j = 0;
uint8 magnet_flag=0;
uint8 magnet_flag1=0;
uint8 huan_turnon=1;
uint8 magnethuan=0;
uint8 duanlu1=0;
uint8 s_flag1=0;
uint8 s_flag2=0;
uint8 zhangchi=0;



/*****************初始寻中线，边线*********/
uint8 le_left[ROW],le_mid[ROW],le_right[ROW];    //左边界列数，右边界列数，中线列数
uint8 fa_left[ROW],fa_mid[ROW],fa_right[ROW];//保存寻得边线
uint8 xun_left[ROW],xun_right[ROW]; //是否寻到线标志位
uint8  bu_left[ROW],bu_right[ROW];//补线标志位，该行补线后，标志位变1
uint8 yu_wid[3]= {74,73,71};   //第60，59,58行赛道宽度
uint8 zhongdian=80;          //实际的时候再改
uint8 track=80;          //赛道的中值
/********************************************/

/*************起跑线检测******************/
uint8 Qipao_be = 0;  //主函数赋值是否执行起跑线检测程序,0不执行，1执行
/********************************************/


/************赛道类型判别*******/
uint16  daolu=0,daolub=0;     //道路有效点
uint16  shangbian=0,shangyan=0;//赛道上边沿
uint8 jian_bian = 0;
uint8 jian_r = 0;
uint8 jian_l =0;
uint8 shang_r = 0;
uint8 shang_l = 0;
uint8  shangyanyu;//判断弯道直道
uint16 leijia=0;  //取平均值确定打角点
/********************************************/


/*************前瞻数值********************/
uint8  daoluyuzhi;//直道的前瞻值
uint8  daoluyuwanl;//弯道前瞻值
uint8  daoluyuwanr;
uint8  daoluyuzhi_temp;
uint8  daoluyuwanl_temp;
uint8  daoluyuwanr_temp;
uint8  yuhuanyuzhi;//圆环前瞻
uint8  yuhuanwanl;
uint8  yuhuanwanr;
int Actuall_Ekk;         //实际偏差
int Actuall_Mid;
/********************************************/


/**********舵机P D值计算的相关参数***********/

float  kpzhi;//直道的p值
float  kdzhi;//直道的d值
float  kpyul;//弯道左的p值
float  kpyur;//弯道右的p值
float  kdyul;//弯道左的d值
float  kdyur;//弯道右的d值

float  kdyul_1;
float  kdyul_2;
float  kdyul_3;
float  kdyur_1;
float  kdyur_2;
float  kdyur_3;

float  kpyuhuan;//弯道p值
float  kdyuhuan;//弯道d值
float  kpyuhuan2;//进弯道p值
float  kdyuhuan2;//进弯道d值

float weitiao_zhi = 0;//直道的p值微调
float kdweitiao = 0;

float weitiaol_1=0; //用于弯道时舵机p值得调整
float weitiaor_1= 0;
float weitiaol_2=0; //用于弯道时舵机p值得调整
float weitiaor_2= 0;
float weitiaol_3=0; //用于弯道时舵机p值得调整
float weitiaor_3= 0;

uint8 qufenl_1=0; //判断大弯小弯赋予不同的pd值
uint8 qufenl_2 = 0;
uint8 qufenl_3 = 0;
uint8 qufenr_1 = 0;
uint8 qufenr_2 = 0;
uint8 qufenr_3 = 0;
/********************************************/


/*****************赛道类型参数*********/
uint8 g_lu_flag=10;
//g_lu_flag=0 十字路口
//g_lu_flag=1 道路急右转
//g_lu_flag=2 道路急左转
//g_lu_flag=3;道路左转
//g_lu_flag=4;道路右转
//g_lu_flag=5 直道
//g_lu_flag=6 障碍
//g_lu_flag=7;环岛
//g_lu_flag=8;断路
//9s
uint8  wan_flag=0;//赛道限幅十使用
uint8 g_shi_flag=0;//十字标志位;
/********************************************/


/************限幅模块参数（弯道使用）*********/
uint8 xf_flag=0;//限幅标志
uint8 xf_left=0;//限幅左标志
uint8 xf_right=0;//限幅右标志
uint8 xf_leftz=1;
uint8 xf_lefty=3;
uint8 xf_rightz=COLUMN-3;
uint8 xf_righty=COLUMN-1;
/********************************************/


/********************一般补线****************/
int    chazhil,chazhil1,chazhil2,//左边线两行间差值
  chazhir,chazhir1,chazhir2;//右边线两行间差值
/********************************************/


/*****************中值滤波***************/
uint8   mid_num=0;
uint8   max_num=0;
uint8   min_num=0;
#define shuzu_num   3         //每行采集点数
uint8 zhongzhi[shuzu_num];
/********************************************/


/*****************十字补线***************/
int   shi_cha=0;//十字路口的差值
int   le_cha=0;//路差值
uint8  shi_left_be;//十字左边开始
uint8  shi_left_en;//十字左边结束
uint8  shi_right_be;//十字右边开始
uint8  shi_right_en;//十字右边结束
uint8  shi_lie=0;// 找寻十字的中值行数
/********************************************/


/*********************障碍***************/
uint8 leftbar_flag = 0;
uint8 leftbar_begin = 0;
uint8 rightbar_flag = 0;
uint8 rightbar_begin = 0;
uint8 barjia = 0;
uint8 barjian = 0;
float kpbar = 0;
float kdbar = 0;
uint8 bar_flag=0;
/******************************************/


/***************起跑线检测*****************/
void Start_Flag();   //起跑线检测
uint8 jiance_qi=0;//检测起跑线标志，如果有圆环之后，开始检测起跑线
uint8 qipao_flag=0;//起跑线标志
uint8 qi_temp=0;
uint8 qi_temp2=0;
/******************************************/


/*****************圆环赛道参数*********/
uint8 serTempX[COLUMN]= {0};  //横向扫描结果
uint8 Lost_Right[ROW];        //右边界丢线
uint8 Lost_Left[ROW];        //左边界丢线
uint8 Track_Width[ROW];       //赛道宽度
uint8 Straight_Length = 0;        //直道长度
uint8 Huan_Flag = 0;          //环岛标志位
uint8 Track_Width_Actuall[60]=
{36,36,36,37,38,38,38,38,39,40,
 40,40,40,42,42,42,44,44,44,45,
 46,46,48,48,50,50,51,52,53,54,
 55,56,57,58,59,61,63,65,65,65,
 67,69,71,72,74,77,78,82,83,86,
 89,91,94,98,100,104,108,111,115,119};

int R_Huan_Time_Counter = 0;    //右环岛辅助计时器
uint8 R_Huan_Flag = 0;        //右环岛标志位
uint8 R_Huan_Entry_Flag = 0;  //右环岛入口标志位
uint8 R_Huan_In_Flag = 0;     //右环岛进入内部标志位
uint8 R_Huan_Exit_Flag = 0;   //右环岛出口标志位
uint8 R_Huan_Exit_Temp_Flag = 0;   //右环岛出口标志位
uint8 R_Huan_Exit_Temp_Y = 0;  //右环岛出口拐点坐标
uint8 R_Huan_Predict1_Flag = 0;     //右环岛预判第一阶段标志位
uint8 R_Huan_Predict2_Flag = 0;     //右环岛预判第二阶段标志位
uint8 R_Huan_Cliff_Flag = 0;       //右环岛拐点
float R_Huan_K_Entry = 0;   //左环岛补线斜率
int L_Huan_Time_Counter = 0;    //左环岛辅助计时器
uint8 L_Huan_Flag = 0;        //左环岛标志位
uint8 L_Huan_Entry_Flag = 0;  //左环岛入口标志位
uint8 L_Huan_In_Flag = 0;     //左环岛进入内部标志位
uint8 L_Huan_Exit_Flag = 0;   //左环岛出口标志位
uint8 L_Huan_Exit_Temp_Flag = 0;   //左环岛出口标志位
uint8 L_Huan_Exit_Temp_Y = 0;  //左环岛出口拐点坐标
uint8 L_Huan_Predict1_Flag = 0;     //左环岛预判第一阶段标志位
uint8 L_Huan_Predict2_Flag = 0;     //左环岛预判第二阶段标志位
uint8 L_Huan_Cliff_Flag = 0;       //左环岛拐点
float L_Huan_K_Entry = 0;   //左环岛补线斜率
/******************************************/

uint8 zhongzhuanl=0,zhongzhuanr=0;//临时变量
uint8 temp2=0,temp3=0;//临时使用的变量;

/********************************************/



/*****************环岛参数******************/
uint8 Circle_Flag = 0;          //环岛标志位
uint8 R_Circle_Flag = 0;        //右环岛标志位
uint8 L_Circle_Flag = 0;        //左环岛标志位
/******************************************/

/*****************断路******************/
uint32 Duan_count = 0; 
uint8 Duan_flag = 0;
/******************************************/





/*******************图像处理***********************/
void image_deal()
{
  image_select((uint8 *)Image_Data, (uint8 *)Pix_Data);
  Bu_Clear_Flag();  //补线标志位清零
	Find_Bound();   //寻边线
	Save_Bound();   //初始边线保存
	Filters() ;//中值滤波
	Bu();  //补线
  Duanlu();
  Bu_Circle() ;//环岛  
	Bu_Crossroad(); //十字补线
	Bu_Curve() ;  //弯道补线
	Start_Flag();  //起跑检测
	Find_Mid() ; //补完线重新计算中点 
	Calculation_Differ() ;//计算打角differ
	Calculation_Pd();//计算舵机Pd值;
  //Bar();
  
}
/*****************************************************/





void Bu_Clear_Flag()  //补线标志位清零
{
	for(i=0; i<ROW; i++) //补线标志位
	{
		bu_left[i]=0;
		bu_right[i]=0;
		xun_left[i]=0;
		xun_right[i]=0;
    Lost_Right[i]=0;   //右边界丢线
    Lost_Left[i]=0;    //左边界丢线
    Track_Width[i]=0;
    bar_flag=0;
	}
}
//寻找边线
void Find_Bound()   //寻边线
{
	le_left[ROW-1]=0;           //左边界为最左
	le_right[ROW-1]=COLUMN;     //右边界为最右
  /*寻找最后一行边线*/
	for(j=track; j>0; j--) 
	{
		if(Image_Data[ROW-1][j]&&!Image_Data[ROW-1][j-1])    //0是黑点   1是白点
		{
			le_left[ROW-1]=j;
			break;
		}
	}
  
	for(j=track; j<COLUMN-1; j++)
	{
		if(Image_Data[ROW-1][j]&&!Image_Data[ROW-1][j+1])
		{
			le_right[ROW-1]=j;
			break;
		}
	} 
	le_mid[ROW-1]=(le_left[ROW-1]+le_right[ROW-1])>>1; //除2
  /*寻找其余边线*/
	for(i=ROW-1; i>0; i--)
	{
		le_left[i-1]=0;
		for(j=le_mid[i]; j>0; j--)
			if(Image_Data[i-1][j]&&!Image_Data[i-1][j-1])
			{
				le_left[i-1]=j;
				break;
			}
		if(!le_left[i-1]&&!(!Image_Data[i-1][le_mid[i]-1]&&!Image_Data[i-1][le_mid[i]-2]))
			xun_left[i-1]=1;//为了避免黑底

		le_right[i-1]=COLUMN;
		for(j=le_mid[i]; j<COLUMN-1; j++)
			if(Image_Data[i-1][j]&&!Image_Data[i-1][j+1])
			{
				le_right[i-1]=j;
				break;
			}

		if(le_right[i-1]==COLUMN&&!(!Image_Data[i-1][le_mid[i]+1]&&!Image_Data[i-1][le_mid[i]+2]))
			xun_right[i-1]=1;//为了避免黑底

		le_mid[i-1]=(le_left[i-1]+le_right[i-1])>>1;
	}
	track=(uint8)((le_mid[57]+le_mid[59]+le_mid[58])/3);     //赋值下一次寻线中点
}

void Save_Bound()   //初始边线保存
{
	for(i=ROW; i>1; i--)
	{
		fa_left[i-1]=le_left[i-1];
		fa_mid[i-1]=le_mid[i-1];
		fa_right[i-1]=le_right[i-1];
	}
}

void Filters() //中值滤波
{
	max_num=0;//  主要的目的是为了前面的三个点不错
	min_num=0;
	mid_num=0;
	for(i=ROW-shuzu_num; i>55; i--) //中值滤波
	{
		for(j=0; j<shuzu_num; j++)
		{
			zhongzhi[j]=le_left[i+j];
		}
		Get(zhongzhi,shuzu_num);
		if(Abs(max_num,mid_num)>20)
		{
			for(j=0; j<shuzu_num; j++)
			{
				if(le_left[i+j]==max_num)
					le_left[i+j]=le_left[i+j-1];
			}
		}
		else if(Abs(min_num,mid_num)>40)
		{
			for(j=0; j<shuzu_num; j++)
			{
				if(le_left[i+j]==min_num)
					le_left[i+j]=le_left[i+j-1];
			}
		}
	}
	max_num=0;
	min_num=0;
	mid_num=0;
	for(i=ROW-shuzu_num; i>55; i--) //中值滤波
	{
		for(j=0; j<shuzu_num; j++)
		{
			zhongzhi[j]=le_right[i+j];
		}
		Get(zhongzhi,shuzu_num);
		if(Abs(max_num,mid_num)>40)
		{
			for(j=0; j<shuzu_num; j++)
			{
				if(le_right[i+j]==max_num)
					le_right[i+j]=le_right[i+j-1];
			}
		}
		else if(Abs(min_num,mid_num)>40)
		{
			for(j=0; j<shuzu_num; j++)
			{
				if(le_right[i+j]==min_num)
					le_right[i+j]=le_right[i+j-1];
			}
		}
	}
}
void Bu()  //补线
{
	zhongzhuanl=0;
	zhongzhuanr=0;
	chazhil=0;
	chazhil1=0;
	chazhil2=0;
	chazhir=0;
	chazhir1=0;
	chazhir2=0;

	//第60,59,58行补线
	int Tempi;
	for(Tempi=0; Tempi<3; Tempi++)
	{
		if(!le_left[ROW-Tempi-1]&&le_right[ROW-Tempi-1]==COLUMN)
		{
			le_left[ROW-Tempi-1]=zhongdian-yu_wid[Tempi];
			le_right[ROW-Tempi-1]=zhongdian+yu_wid[Tempi];
			bu_left[ROW-Tempi-1]=1;
			bu_right[ROW-Tempi-1]=1;
		}
		else if(le_right[ROW-Tempi-1]==COLUMN)
		{
			if(le_left[ROW-Tempi-1]<10)//调整
			{
				le_left[ROW-Tempi-1]=zhongdian-yu_wid[Tempi];
				le_right[ROW-Tempi-1]=zhongdian+yu_wid[Tempi];
				bu_left[ROW-Tempi-1]=1;
				bu_right[ROW-Tempi-1]=1;
			}
			else
			{
				if(le_left[ROW-Tempi-1]>COLUMN-yu_wid[Tempi]-yu_wid[Tempi]-1)
					le_right[ROW-Tempi-1]=COLUMN-1;
				else
					le_right[ROW-Tempi-1]=le_left[ROW-Tempi-1]+yu_wid[Tempi]+yu_wid[Tempi];
				bu_right[ROW-Tempi-1]=1;
			}
		}
		else if(!le_left[ROW-Tempi-1])
		{
			if(le_right[ROW-Tempi-1]>COLUMN-10)//调整
			{
				le_left[ROW-Tempi-1]=zhongdian-yu_wid[Tempi];
				le_right[ROW-Tempi-1]=zhongdian+yu_wid[Tempi];
				bu_left[ROW-Tempi-1]=1;
				bu_right[ROW-Tempi-1]=1;
			}
			else
			{
				if(le_right[ROW-Tempi-1]<yu_wid[Tempi]+yu_wid[Tempi]+1)
					le_left[ROW-Tempi-1]=1;
				else
					le_left[ROW-Tempi-1]=le_right[ROW-Tempi-1]-yu_wid[Tempi]-yu_wid[Tempi];
				bu_left[ROW-Tempi-1]=1;
			}
		}
	}
//第ROW-4行补线
	chazhil=0;
	chazhil1=0;
	chazhil2=0;
	chazhir=0;
	chazhir1=0;
	chazhir2=0;
	if(!le_left[ROW-4])
	{
		chazhil1=le_left[ROW-2]-le_left[ROW-3];
		chazhil2=le_left[ROW-1]-le_left[ROW-3];
		chazhil=(int)(chazhil2/2);
		if(chazhil!=0)
			chazhil=(int)((chazhil1+(chazhil2/2))/2);
		if((le_left[ROW-3]>chazhil)&&(le_left[ROW-3]<COLUMN+chazhil))
			le_left[ROW-4]=le_left[ROW-3]-chazhil;
		else if(le_left[ROW-3]<chazhil+1)
			le_left[ROW-4]=1;
		else
			le_left[ROW-4]=COLUMN-1;
	}
	if(le_right[ROW-4]==COLUMN)
	{
		chazhir1=le_right[ROW-1]-le_right[ROW-2];
		chazhir2=le_right[ROW-1]-le_right[ROW-3];
		chazhir=(int)(chazhir2/2);
		if(chazhir!=0)
			chazhir=(int)((chazhir1+(chazhir2/2))/2);
		if((le_right[ROW-3]>chazhir)&&(le_right[ROW-3]<COLUMN+chazhir))
			le_right[ROW-4]=le_right[ROW-3]-chazhir;
		else if(le_right[ROW-3]<chazhir+1)
			le_right[ROW-4]=1;
		else
			le_right[ROW-4]=COLUMN-1;
	}
}

// R_Huan_Time_Counter   //右环岛辅助计时器
// R_Huan_Flag = 0;        //右环岛标志位
// R_Huan_Entry_Flag = 0;  //右环岛入口标志位
// R_Huan_In_Flag = 0;     //右环岛进入内部标志位
// R_Huan_Exit_Flag = 0;   //右环岛出口标志位
// R_Huan_Exit_Temp_Flag = 0;   //右环岛出口标志位
// R_Huan_Exit_Temp_Y = 0;  //右环岛出口拐点坐标
// R_Huan_Predict1_Flag = 0;     //右环岛预判第一阶段标志位
// R_Huan_Predict2_Flag = 0;     //右环岛预判第二阶段标志位
// R_Huan_Cliff_Flag = 0;       //右环岛拐点
// R_Huan_K_Entry = 0;   //右环岛补线斜率

void Bu_Circle()   //环岛补线
{
  Straight_Length = 0 ;
  int i;
  int temp1,temp2;
  
  R_Huan_Exit_Temp_Y = 0;
  L_Huan_Exit_Temp_Y  = 0;
  R_Huan_Time_Counter ++;
  L_Huan_Time_Counter ++;
  R_Huan_Exit_Temp_Flag = 0;
  L_Huan_Exit_Temp_Flag = 0;
  
  if(R_Huan_Time_Counter > 2000)
    R_Huan_Time_Counter = 1999;
  R_Huan_Cliff_Flag = 0;
    
  if(L_Huan_Time_Counter > 2000)
    L_Huan_Time_Counter = 1999;
  L_Huan_Cliff_Flag = 0;
  
  for(i=15; i<ROW-5; i++)       //找到右边从没有线到出现线的位置
	{
    if((fa_right[i-2]-fa_right[i])>20&&
      ((fa_right[i+1]-fa_right[i])>=0)&&((fa_right[i+1]-fa_right[i])<4)&&
      ((fa_right[i+2]-fa_right[i+1])>=0)&&((fa_right[i+2]-fa_right[i+1])<4)&&
      ((fa_right[i+3]-fa_right[i+2])>=0)&&((fa_right[i+3]-fa_right[i+2])<4)&&
      (fa_right[i-2]>COLUMN-5)&&(fa_right[i-3]>COLUMN-5)&&
      (fa_right[i-4]>COLUMN-5)&&(fa_right[i-5]>COLUMN-5))
      R_Huan_Cliff_Flag = 1;//拐点标志位
	}
  for(i=5; i<ROW-5; i++)    //出环岛标志左边出现边线   
	{
    if((fa_left[i]-fa_left[i-2])>0&&(fa_left[i-1]-fa_left[i-3])>0&&(fa_left[i-2]-fa_left[i-4])>0&&
      (fa_left[i]-fa_left[i+2])>0&&(fa_left[i+1]-fa_left[i+3])>0&&(fa_left[i+2]-fa_left[i+4])>0)
    {
      R_Huan_Exit_Temp_Y = i;
      break;
    }
	}
  if(R_Huan_Exit_Temp_Y>30)
    R_Huan_Exit_Temp_Flag = 1;
  for(i=0; i<ROW; i++)       //丢线判断
	{
    if(fa_left[i]<5)
      Lost_Left[i]=1;
    if(fa_right[i]>COLUMN-5)
      Lost_Right[i]=1;
    Track_Width[i] = fa_right[i] - fa_left[i]; 
	}
  for(i=ROW-1; i>0; i--)       //直道长度计算
	{
    if(!Image_Data[i][80])//弯道跳出循环
      break;
	}
  Straight_Length = 59 - i;//直道长度
  
  temp1 = fa_right[ROW-3]-3;
  for(i=55;i>0;i--)
  {
    if(!Image_Data[i][temp1])
      break;
  }
  R_Huan_K_Entry=10*(fa_right[ROW-3]-35)/(59-i);//右环岛补线斜率/35
  
  /******************右环岛识别***********/
  if(R_Huan_Cliff_Flag&&!R_Huan_Flag&&Lost_Right[30]&&Lost_Right[32]&&!Lost_Left[30]&&!Lost_Left[32])  //第一阶段:右丢线，左不丢线,直道长度大于57，赛道宽度大于110小于150
  {
    R_Huan_Predict1_Flag = 1;       //右环岛第一阶段预判
    R_Huan_Time_Counter = 0;
  }

   
  if(R_Huan_Predict1_Flag)
  {
    if(R_Huan_Time_Counter>30||Lost_Left[30]||Lost_Left[32])       //左边线丢失，或时间过长//拐弯
    {
      R_Huan_Time_Counter = 0;
      R_Huan_Predict1_Flag = 0;
    }
    if(!Lost_Right[30]&&!Lost_Right[32]&&!Lost_Left[30]&&!Lost_Left[32]&&R_Huan_Time_Counter>2)  //第二阶段:左右均不丢线，直道长度大于50，时间超过3
    {
      R_Huan_Predict2_Flag = 1;
      R_Huan_Predict1_Flag = 0;
      R_Huan_Time_Counter = 0;
    }
  }
  if(!Duan_flag&&!magnethuan&&huan_turnon&&R_Huan_Predict2_Flag&&Lost_Right[30]&&Lost_Right[32]&&!Lost_Left[30]&&!Lost_Left[32])//环岛入口（第三阶段）：右丢线，左不丢线
    {
      //magnet_flag=1;
      R_Huan_Flag = 1;
      R_Huan_Entry_Flag = 0;
      R_Huan_In_Flag = 0;     
      R_Huan_Exit_Flag = 0;  
      R_Huan_Predict1_Flag = 0;
      R_Huan_Predict2_Flag = 0;
      R_Huan_Time_Counter = 0;
    }
  if(R_Huan_Predict2_Flag&&R_Huan_Time_Counter>50)       //左边线丢失，或时间过长
    {
      R_Huan_Time_Counter = 0;
      R_Huan_Predict2_Flag = 0;
    }
  if(!R_Huan_Exit_Flag&&R_Huan_Flag&&R_Huan_Time_Counter<20)//40  //判断为环岛，且时间小于20，为环岛入口 
  {
    R_Huan_Entry_Flag = 1; 
  }
  else
  {
    R_Huan_Entry_Flag = 0; 
  }
  
  if(R_Huan_Entry_Flag)
  {
    //buzzer_Flag=1;
    //Buzzer=1;
    //LPLD_UART_PutChar(UART4,(int8)speed_hope);
    g_lu_flag=7;
  }
  
  if(R_Huan_Flag&&R_Huan_Exit_Temp_Flag&&R_Huan_Time_Counter > 100) //进环岛后，时间超过50，且左边丢线，判为出环岛
  {
    Buzzer=0;//Buzzer
    R_Huan_Exit_Flag = 1;
    R_Huan_Time_Counter = 0;
  }
 
  
  if(R_Huan_Exit_Flag && R_Huan_Time_Counter > 30)  //判断为出环岛后，时间超过20，环岛结束//40
  {
    magnet_flag=1;
    //buzzer_Flag=0;
    R_Huan_Exit_Flag = 0;
    R_Huan_Flag = 0;
    R_Huan_Time_Counter = 0;
    par(zhangchi);
  }
   
  if(R_Huan_Flag&&!R_Huan_Entry_Flag&&!R_Huan_Exit_Flag) //判断为环岛，既不是入口，也不是出口，为环岛内
    
  {
    R_Huan_In_Flag = 1;
    //Buzzer=0;
  }
  else
    R_Huan_In_Flag = 0;
  /***********************************************/
  /*******************右环岛补线******************/
  if(R_Huan_Entry_Flag)      //进环岛补线
  {
    for(i=ROW-1; i>0; i--)
      le_left[i] = (uint8)((R_Huan_K_Entry*(59-i)/10));   
    for(i=ROW-1; i>0; i--)
    {
      if(le_left[i]>le_right[i])
        le_right[i] = COLUMN-2;
    }
  }
  if(R_Huan_Exit_Flag)      //出环岛顺着右边跑
  {
    for(i=ROW-1; i>0; i--)
    {
      //if(((le_right[i]+le_right[i])/2)<130)
      le_right[i] = COLUMN-2;
      le_left[i]=COLUMN-20; 
    }
    
  } 
 
  
  /****************************************/
  /*             左环岛识别               */
  /****************************************/
  
  for(i=15; i<ROW-5; i++)       //找到左边从没有线到出现线的位置
	{
    if((fa_left[i]-fa_left[i-2])>20&&
      ((fa_left[i]-fa_left[i+1])>=0)&&((fa_left[i]-fa_left[i+1])<4)&&
      ((fa_left[i+1]-fa_left[i+2])>=0)&&((fa_left[i+1]-fa_left[i+2])<4)&&
      ((fa_left[i+2]-fa_left[i+3])>=0)&&((fa_left[i+2]-fa_left[i+3])<4)&&
      (fa_left[i-2]<5)&&(fa_left[i-3]<5)&&
      (fa_left[i-4]<5)&&(fa_left[i-5]<5))
    {
      L_Huan_Cliff_Flag = 1;//左边拐点标志位
      //Buzzer=1;
    }
	}
  //
  for(i=5; i<ROW-5; i++)    //出环岛标志右边出现边线   
	{
    if((fa_right[i]-fa_right[i-2])<0&&(fa_right[i-1]-fa_right[i-3])<0&&(fa_right[i-2]-fa_right[i-4])<0&&
      (fa_right[i]-fa_right[i+2])<0&&(fa_right[i+1]-fa_right[i+3])<0&&(fa_right[i+2]-fa_right[i+4])<0)
    {
      L_Huan_Exit_Temp_Y  = i;
      break;
    }
	}
  
  if(L_Huan_Exit_Temp_Y >30)
    L_Huan_Exit_Temp_Flag = 1;
  
  for(i=0; i<ROW; i++)       //丢线判断
	{
    if(fa_right[i]>COLUMN-5)
      Lost_Right[i]=1;
    if(fa_left[i]<5)
      Lost_Left[i]=1;
    Track_Width[i] = fa_right[i] - fa_left[i]; 
	}
  //
  for(i=ROW-1; i>0; i--)       //直道长度计算
	{
    if(!Image_Data[i][80])//弯道跳出循环
      break;
	}
  Straight_Length = 59 - i;//直道长度
  //
  
  temp2 = fa_left[ROW-3]+3;
  
  
  
  for(i=55;i>0;i--)
  {
    if(!Image_Data[i][temp2])
      break;
  }
  
  L_Huan_K_Entry=10*(fa_left[ROW-3]+35)/(59-i);//左环岛补线斜率
  
  /******************左环岛识别***********/
  if(L_Huan_Cliff_Flag&&!L_Huan_Flag&&!Lost_Right[30]&&!Lost_Right[32]&&Lost_Left[30]&&Lost_Left[32])  //第一阶段:右丢线，左不丢线,直道长度大于57，赛道宽度大于110小于150
  {
    //Buzzer=1;
    L_Huan_Predict1_Flag = 1;       //右环岛第一阶段预判
    L_Huan_Time_Counter = 0;
  }

   
  if(L_Huan_Predict1_Flag)
  {
    if(L_Huan_Time_Counter>30||Lost_Right[30]||Lost_Right[32])       //左边线丢失，或时间过长//拐弯
    {
      L_Huan_Time_Counter = 0;
      L_Huan_Predict1_Flag = 0;
    }
    if(!Lost_Right[30]&&!Lost_Right[32]&&!Lost_Left[30]&&!Lost_Left[32]&&L_Huan_Time_Counter>3)  //第二阶段:左右均不丢线，直道长度大于50，时间超过3
    {
      //Buzzer=1;
      L_Huan_Predict2_Flag = 1;
      L_Huan_Predict1_Flag = 0;
      L_Huan_Time_Counter = 0;
    }
  }
  if(!Duan_flag&&!magnethuan&&huan_turnon&&L_Huan_Predict2_Flag&&!Lost_Right[30]&&!Lost_Right[32]&&Lost_Left[30]&&Lost_Left[32])//环岛入口（第三阶段）：右丢线，左不丢线
    {
      //magnet_flag=1;
      L_Huan_Flag = 1;
      L_Huan_Entry_Flag = 0;
      L_Huan_In_Flag = 0;     
      L_Huan_Exit_Flag = 0;  
      L_Huan_Predict1_Flag = 0;
      L_Huan_Predict2_Flag = 0;
      L_Huan_Time_Counter = 0;
    }
  if(L_Huan_Predict2_Flag&&L_Huan_Time_Counter>50)       //左边线丢失，或时间过长
    {
      L_Huan_Time_Counter = 0;
      L_Huan_Predict2_Flag = 0;
    }
  if(!L_Huan_Exit_Flag&&L_Huan_Flag&&L_Huan_Time_Counter<40)//40  //判断为环岛，且时间小于20，为环岛入口 
  {
    L_Huan_Entry_Flag = 1; 
  }
  else
  {
    L_Huan_Entry_Flag = 0; 
  }
  
  if(L_Huan_Entry_Flag)
  {
    //buzzer_Flag=1;
    //Buzzer=1;
    g_lu_flag=7;
  }
  
  if(L_Huan_Flag&&L_Huan_Exit_Temp_Flag&&L_Huan_Time_Counter > 90) //进环岛后，时间超过50，且左边丢线，判为出环岛
  {
    Buzzer=0;
    L_Huan_Exit_Flag = 1;
    L_Huan_Time_Counter = 0;
  }
 
  
  if(L_Huan_Exit_Flag && L_Huan_Time_Counter > 30)  //判断为出环岛后，时间超过20，环岛结束//40
  {
    //Buzzer=0;
    magnet_flag=1;
    L_Huan_Exit_Flag = 0;
    L_Huan_Flag = 0;
    L_Huan_Time_Counter = 0;
  }
   
  if(L_Huan_Flag&&!L_Huan_Entry_Flag&&!L_Huan_Exit_Flag) //判断为环岛，既不是入口，也不是出口，为环岛内
  {
    L_Huan_In_Flag = 1;
  }
  else
    L_Huan_In_Flag = 0;
  /***********************************************/
  /*******************左环岛补线******************/
  if(L_Huan_Entry_Flag)      //进环岛补线
  {
    //Buzzer=1;
    for(i=ROW-1; i>0; i--)
      le_right[i] = (uint8)((L_Huan_K_Entry*(59-i)/10));   
    for(i=ROW-1; i>0; i--)
    {
      if(le_left[i]<le_right[i])
        le_left[i] = 1;
    }
  }
  if(L_Huan_Exit_Flag)      //出环岛顺着左边跑
  {
    for(i=ROW-1; i>0; i--)
    {
      //if(((le_right[i]+le_right[i])/2)<130)
      le_right[i] = 20;
      le_left[i]=1; 
    }
    
  }
  /****************************************/
}




void Bu_Crossroad() //十字补线
{
	//从一点起连续八行左边无边线，记录该点行数
	for(i=ROW-1; i>4; i--)
	{
		if((le_left[i]<10)&&(le_left[i-1]<10)&&(le_left[i-2]<10)&&(le_left[i-3]<10)&&(le_left[i-4]<10)&&(le_left[i-5]<10)&&(le_left[i-6]<10)
		        &&xun_left[i]&&xun_left[i-1]&&xun_left[i-2]&&xun_left[i-3]&&xun_left[i-4]&&xun_left[i-5]&&xun_left[i-6])//连续8行左边无边线
		{

			zhongzhuanl=i;      //记录位置
			break;
		}
	}
	//从一点起连续八行右边无边线，记录该点行数
	for(i=ROW-1; i>4; i--)
	{
		if((le_right[i]>150)&&(le_right[i-1]>150)&&(le_right[i-2]>150)&&(le_right[i-3]>150)&&
		        (le_right[i-4]>150)&&(le_right[i-5]>150)&&(le_right[i-6]>150)&&xun_right[i]&&
		        xun_right[i-1]&&xun_right[i-2]&&xun_right[i-3]&&xun_right[i-4]&&xun_right[i-5]&&xun_right[i-6])  //连续8行右边无边线
		{

			zhongzhuanr=i;                                  //记录位置
			break;
		}
	}

	if(zhongzhuanl&&zhongzhuanr)//可能是十字   zhongzhuanl&&zhongzhuanr
	{

		shi_left_en=zhongzhuanl;                          //十字结束行
		for(i=shi_left_en; i<ROW-3; i++)
			if(le_left[i]&&le_left[i+1]&&le_left[i]>le_left[i+2]&&le_left[i]>le_left[i-1])//找拐角
			{
				shi_left_en=i;                                //记录左边结束行，即左下拐角
				break;
			}
		shi_right_en=zhongzhuanr;                       //记录十字右边结束行
		for(i=shi_right_en; i<ROW-3; i++)
			if(le_right[i]<COLUMN&&le_right[i+1]<COLUMN&&le_right[i]<le_right[i+2]&&le_right[i]<le_right[i-1])
			{
				shi_right_en=i;                               //记录右边结束行，即右下拐角
				break;
			}

		temp2=0;
		temp3=0;
		shi_lie=0;
		//重新判断十字
		for(j=le_left[shi_left_en]+1; j<le_right[shi_right_en]-6; j++)
		{
			for(i=ROW-1; i>15&&Image_Data[i][j]&&Image_Data[i][j+2]&&Image_Data[i][j+4]&&
			        Image_Data[i][j+6]&&Image_Data[i][j+8]&&Image_Data[i][j+10]; i--)
			{
				if(i==16)
				{
					temp3=1;//不在循环标定
					shi_lie=j+6;
					break;
				}
			}
			if(temp3==1)
				break;
		}
		//如果十字拐点与左右转标志差太远，则不是十字
		if(shi_left_en>zhongzhuanl+20)//再次判断是否是十字主要是弯道
		{
			shi_lie=0;
		}
		else if(shi_right_en>zhongzhuanr+20)
		{
			shi_lie=0;
		}

		if(shi_right_en>25&&shi_left_en>25&&shi_lie&&
		        (le_left[shi_left_en]<zhongdian+40&&le_right[shi_right_en]>zhongdian-40))//有效的十字
		{
			if(shi_left_en<shi_right_en)
				temp2=shi_left_en;
			else
				temp2=shi_right_en;//找到前面的行数寻标点
			if(shi_lie)//重新寻线1
			{
				for(i=temp2; i>0; i--)
				{
					if(i<=16)//寻线方式选择
						j=le_mid[i+1];
					else
						j=shi_lie;
					le_right[i]=COLUMN;
					for(; j<COLUMN-1; j++)
						if(Image_Data[i][j]&&!Image_Data[i][j+1])
						{
							le_right[i]=j;
							break;
						}
					if(i<=16)//寻线方式选择
						j=le_mid[i+1];
					else
						j=shi_lie;
					le_left[i]=0;
					for(; j>0; j--)
						if(Image_Data[i][j]&&!Image_Data[i][j-1])
						{
							le_left[i]=j;
							break;
						}
					le_mid[i]=(le_left[i]+le_right[i])>>1;
				}

			}
			shi_left_be=zhongzhuanl-4;//减去4是因为上面七行没有点
			for(i=shi_left_be; i>3; i--)
				if(le_left[i]>le_left[shi_left_en]&&le_left[i+1]>10&&
				        le_left[i]<le_left[i-1]+3&&le_left[i]>le_left[i-1]-4)
				{
					shi_left_be=i;                               //记录左边开始行。即左上拐角
					break;
				}
			shi_cha=le_left[shi_left_be]-le_left[shi_left_en];
			for(i=shi_left_be+1; i<shi_left_en; i++)
			{
				bu_left[i]=1;
				le_cha=(int)(shi_cha/(shi_left_en-i+1));
				le_left[i]=le_left[i-1]-le_cha;
				shi_cha-=le_cha;                                //左十字边补线
			}

			shi_right_be=zhongzhuanr-4;
			for(i=shi_right_be+1; i>3; i--)
				if(le_right[i]<le_right[shi_right_en]&&le_right[i+1]<COLUMN-10&&
				        le_right[i]<le_right[i-1]+4&&le_right[i]>le_right[i-1]-3)
				{
					shi_right_be=i;                               //记录右边开始行，即右上拐角
					break;
				}
			shi_cha=le_right[shi_right_be]-le_right[shi_right_en];
			for(i=shi_right_be+1; i<shi_right_en; i++)
			{
				bu_right[i]=1;
				le_cha=(int)(shi_cha/(shi_right_en-i+1));
				le_right[i]=le_right[i-1]-le_cha;
				shi_cha-=le_cha;                                //右十字边补线
			}
			g_shi_flag=1;                                       //十字类型标志
			g_lu_flag=0;//十字

		}
	}
}



void Bu_Curve()   //弯道补线
{
	zhongzhuanl=0;
	zhongzhuanr=0;
	xf_left=0;
	xf_right=0;
	xf_leftz=1;
	xf_lefty=3;
	xf_rightz=COLUMN-3;
	xf_righty=COLUMN-1;
	wan_flag=0;

	for(i=ROW-1; i>3; i--)//从下向上查找
	{
		if(Abs(le_left[i],le_left[i-1])>40
      &&Abs(le_left[i],le_left[i-2])>40
      &&Abs(le_left[i],le_left[i-3])>40)   //左边线跳变点
		{
      zhongzhuanl=i;  //左转点
			break;
		}
	}
	for(i=ROW-1; i>3; i--)//从下向上查找  
	{
		//连续三点，两两绝对差值超过四十
		if(Abs(le_right[i],le_right[i-1])>40
      &&Abs(le_right[i],le_right[i-2])>40
      &&Abs(le_right[i],le_right[i-3])>40)  //右边线跳变点
		{
			zhongzhuanr=i;    //右转点
			break;
		}
	}
	if(zhongzhuanl&&le_left[zhongzhuanl]>zhongdian)//找到没有右边线的地方
	{
		for(i=zhongzhuanl; i<ROW-6; i++)  //跳变点向下查找
		{
			if(le_right[i]==COLUMN-1
        &&le_right[i+1]==COLUMN-1
        &&le_right[i+2]==COLUMN-1
        &&le_right[i+3]==COLUMN-1
        &&le_right[i+4]==COLUMN-1
        &&le_right[i+5]==COLUMN-1)  //右边线为最右边
			{
				xf_right=1;  //右限幅
				temp2=i;
				break;
			}
		}

	}
	if(zhongzhuanr&&le_right[zhongzhuanr]<zhongdian)//找到没有左边线的地方
	{
		for(i=zhongzhuanr; i<ROW-6; i++)
		{
			if(!le_left[i]
        &&!le_left[i+1]
        &&!le_left[i+2]
        &&!le_left[i+3]
        &&!le_left[i+4]
        &&!le_left[i+5])    //左边线为最左边 
			{

				xf_left=1;  //左限幅
				temp3=i;
				break;
			}
		}
	}
	if(xf_right)//左边限幅，左右边线均在最右边
	{
		wan_flag=1;
		for(i=zhongzhuanl; i>0; i--)  //从跳变点向上查找
		{
			le_left[i]=xf_rightz;
		}
		for(i=temp2; i>0; i--)
		{
			le_right[i]=xf_righty;
		}
	}
	if(xf_left)//右边限幅，左右边线均在最左边
	{
		wan_flag=1;
		for(i=zhongzhuanr; i>0; i--)
		{
			le_right[i]=xf_lefty;
		}
		for(i=temp3; i>0; i--)
		{
			le_left[i]=xf_leftz;
		}

	}
	/**************************************/
	/***************一般补线***************/
  
	zhongzhuanl=0;
	zhongzhuanr=0;
	for(i=ROW-4; i>0; i--)  //从下向上查找
	{
		if(i>6&&le_left[i]<30
      &&!le_left[i-1]&&!le_left[i-2]&&!le_left[i-3]&&!le_left[i-4]
      &&!le_left[i-5]&&!le_left[i-6]&&!le_left[i-7]&&!le_left[i-8]&&!le_left[i-9])//总共7个点，十字是8个点//左边线连续九行为零
		{
			le_left[i-1]=1;
			le_left[i-2]=1;
			le_left[i-3]=1;
			le_left[i-4]=1;
			le_left[i-5]=1;
			le_left[i-6]=1;
			le_left[i-7]=1;
			le_left[i-8]=1;
			le_left[i-9]=1;//这个是为了不让在十字的地方补线使用
			if(i>25)
				wan_flag=1;
		}
		if(i>6&&le_right[i]>COLUMN-30
      &&le_right[i-1]==COLUMN&&le_right[i-2]==COLUMN&&le_right[i-3]==COLUMN&&le_right[i-4]==COLUMN
      &&le_right[i-5]==COLUMN&&le_right[i-6]==COLUMN&&le_right[i-7]==COLUMN&&le_right[i-8]==COLUMN&&le_right[i-9]==COLUMN)
		{
			le_right[i-1]=COLUMN-1;
			le_right[i-2]=COLUMN-1;
			le_right[i-3]=COLUMN-1;
			le_right[i-4]=COLUMN-1;
			le_right[i-5]=COLUMN-1;
			le_right[i-6]=COLUMN-1;
			le_right[i-7]=COLUMN-1;
			le_right[i-8]=COLUMN-1;
			le_right[i-9]=COLUMN-1;  //这个是为了不让在十字的地方补线使用
			if(i>25)
				wan_flag=1;
		}
    
    
		if(le_left[i]>((i/40)+1)*14)//跳变点的阈值
			zhongzhuanl=le_left[i];
		else
			zhongzhuanl=((i/40)+1)*14;
    
    
		if(le_right[i]>((i/40)+1)*14)
			zhongzhuanr=le_right[i];
		else
			zhongzhuanr=((i/40)+1)*14;
    
    
		//bu_  ==3  是直角  ==1是十字
		if(bu_left[i-1]!=3&&bu_left[i-1]!=1&&(!le_left[i-1]
      ||(le_left[i-1]<zhongzhuanl-((i/40)+1)*14
      ||le_left[i-1]>zhongzhuanl+((i/40)+1)*14)
      ||(le_left[i]>le_left[i-1]+5&&le_left[i-1]+5<le_left[i-2])
		  ||(le_left[i]+5<le_left[i-1]&&le_left[i-1]>le_left[i-2]+5)))//考虑往外情况，往内没考虑
		{
			chazhil1=le_left[i+2]-le_left[i+1];
			chazhil2=le_left[i+3]-le_left[i+1];
			chazhil=(int)(chazhil2/2);
      
      
			if(chazhil)//间隔超过2时
				chazhil=(int)((chazhil1+(chazhil2/2))/2);
			else if(chazhil2<2&&chazhil2>-2)//否则就按照间隔两点的差值补线
				chazhil=(int)chazhil2;
			if((le_left[i]>chazhil)&&(le_left[i]<COLUMN+chazhil))//在中间的时候
				le_left[i-1]=le_left[i]-chazhil;
			else if(le_left[i]<chazhil+1)//在最左边
				le_left[i-1]=1;
			else                         //在最右边
				le_left[i-1]=COLUMN-1;
        
			bu_left[i-1]=2;//补线标志变成2     下同
		}
		if(bu_right[i-1]!=3&&bu_right[i]!=1&&(le_right[i-1]==COLUMN
      ||(le_right[i-1]<zhongzhuanr-((i/40)+1)*14
      ||le_right[i-1]>zhongzhuanr+((i/40)+1)*14)
		  ||(le_right[i]+5<le_right[i-1]&&le_right[i-1]>le_right[i-2]+5)
		  ||(le_right[i]>le_right[i-1]+5&&le_right[i-1]+5<le_right[i-2])))
		{
			chazhir1=le_right[i+2]-le_right[i+1];
			chazhir2=le_right[i+3]-le_right[i+1];
			chazhir=(int)(chazhir2/2);
      
      
			if(chazhir!=0)
				chazhir=(int)((chazhir1+(chazhir2/2))/2);
			else if(chazhir2<2&&chazhir2>-2)
				chazhir=(int)chazhir2;
			if((le_right[i]>chazhir)&&(le_right[i]<COLUMN+chazhir))
				le_right[i-1]=le_right[i]-chazhir;
			else if(le_right[i]<=chazhir)
				le_right[i-1]=1;
			else
				le_right[i-1]=COLUMN-1;
      
			bu_right[i-1]=2;
		}
    
		if(le_right[i-1]<le_left[i-1])//防止补线补反掉了
		{
			if(le_right[i]>zhongdian-1&&le_left[i]>zhongdian-1)
				le_right[i-1]=le_left[i-1]+2;
			else if(le_right[i]<zhongdian+1&&le_left[i]<zhongdian+1)
				le_left[i-1]=le_right[i-1]-2;
		}
    
		le_mid[i-1]=(le_left[i-1]+le_right[i-1])>>1;
    
		if(le_left[i]>COLUMN-44&&le_left[i-1]>COLUMN-39)//当左边线或者右边线超过一定的值得时候就把他补线过去
		{
			zhongzhuanl=le_left[i-1];//
			zhongzhuanr=COLUMN-2;
      
			for(; i>0; i--)
			{
				le_left[i-1]=zhongzhuanl;
				le_right[i-1]=zhongzhuanr;
				le_mid[i-1]=(le_left[i-1]+le_right[i-1])>>1;
			}
			i=1;
			break;
		}
    
		if(le_right[i]<45&&le_right[i-1]<40)
		{
			zhongzhuanr=le_right[i-1];//
			zhongzhuanl=2;
			for(; i>0; i--)
			{
				le_left[i-1]=zhongzhuanl;
				le_right[i-1]=zhongzhuanr;
				le_mid[i-1]=(le_left[i-1]+le_right[i-1])>>1;
			}
			i=1;
			break;
		}
    
	}
}

void Start_Flag()  //起跑检测
{
	qi_temp2=0;
	uint8 qi_temp3=0;
	uint8 qi_temp4=0;
	if(1)
	{
		for(i=0; i<58; i++)
			for(j=le_left[i]; j<le_right[i]; j++)
			{
				if(Image_Data[i][j]&&!Image_Data[i][j+1])
				{
					qi_temp++;
					if(qi_temp>5&&((i-qi_temp3)<2||(qi_temp3==0))&&((j-qi_temp4<4)||(qi_temp4==0)))
					{
						qi_temp2++;
						qi_temp=0;
						qi_temp3=i;
						qi_temp4=j;
						if(qi_temp2>2
						        &&le_left[2]<80&&le_left[3]<80&&le_left[4]<80&&le_left[5]<80&&le_left[6]<80
						        &&le_right[2]>80&&le_right[3]>80&&le_right[4]>80&&le_right[5]>80&&le_right[6]>80&&jiance_qi)
						{
							qi_temp2=0;
							qipao_flag=1;
              //differ=0;
              //Buzzer=1;
						}
						break;
					}
				}
			}
		qi_temp=0;
	}
}

void Find_Mid()  //补完线重新计算中点
{
	for(i=ROW; i>1; i--) //跟新中点
	{
		le_mid[i-1]=(le_right[i-1]+le_left[i-1])>>1;
	}
}

void Calculation_Differ() //计算打角differ
{
	daolub=0;//道路开始
  s_flag1=0;
  s_flag2=0;

	for(shangbian=ROW-3; shangbian>2&&(le_left[shangbian]<COLUMN-shang_r||
	                                   le_left[shangbian-1]<COLUMN-shang_r||le_left[shangbian-2]<COLUMN-shang_r)&&
	        (le_right[shangbian]>shang_l||le_right[shangbian-1]>shang_l||le_right[shangbian-2]>shang_l); shangbian--);

	for(jian_bian=ROW-3; jian_bian>2&&(le_left[jian_bian]<COLUMN-jian_r||
	                                   le_left[jian_bian-1]<COLUMN-jian_r||le_left[jian_bian-2]<COLUMN-jian_r)&&
	        (le_right[jian_bian]>jian_l||le_right[jian_bian-1]>jian_l||le_right[jian_bian-2]>jian_l); jian_bian--);


	for(shangyan=ROW-3; (shangyan>2)&&(le_left[shangyan-2]<zhongdian||
	                                   le_left[shangyan-1]<zhongdian||le_left[shangyan]<zhongdian)&&
	        (le_right[shangyan-2]>zhongdian||le_right[shangyan-1]>zhongdian||
	         le_right[shangyan]>zhongdian); shangyan--);   //寻找赛道上边沿
  

	daoluyuzhi=daoluyuzhi_temp;
  daoluyuwanl=daoluyuwanl_temp;
  daoluyuwanr=daoluyuwanr_temp;
	if(shangbian>4)//说明是弯道
	{
		if(le_mid[shangbian+4]<zhongdian&&le_mid[shangbian+5]<zhongdian)
		{
			//这是左弯道
			g_lu_flag=3;
			//如果上边小于前瞻值，道路有效点为前瞻值，否则为上边值
			if(shangbian<daoluyuwanl)
				daolu=daoluyuwanl;
			else
				daolu=shangbian;
			daolub=(uint16)((le_mid[daolu]+le_mid[daolu+2]+le_mid[daolu+1])/3);
			//根据道路有效值中点与实际中点差值，算出舵机打角
			differ=(int)(1*(zhongdian-daolub));
      if(shangbian > daoluyuwanl)
			{
				if(differ>0)
					differ=differ+3*(daolu-daoluyuwanl);  //改动   //
				else
					differ=differ-3*(daolu-daoluyuwanl);//沿直线把它归一化
			}
		}
		if(le_mid[shangbian+4]>zhongdian&&le_mid[shangbian+5]>zhongdian)
		{
			//这是右弯道
			g_lu_flag=4;

			if(shangbian<daoluyuwanr)
				daolu=daoluyuwanr;
			else
				daolu=shangbian;

			daolub=(uint16)((le_mid[daolu]+le_mid[daolu+2]+le_mid[daolu+1])/3);
			differ=(int)(1*(zhongdian-daolub));
      if(shangbian > daoluyuwanr)
			{
				if(differ>0)
					differ=differ+3*(daolu-daoluyuwanr);//3
				else
					differ=differ-3*(daolu-daoluyuwanr);//沿直线把它归一化
			}
		}
	}


	if(shangbian<=4)            //直道
	{
		g_lu_flag=5;
		if(shangbian<daoluyuzhi)
			daolu=daoluyuzhi;
		else
			daolu=shangbian+5;
		leijia=0;
		//根据道路有效点上下点的中线平均值与中点差值确定舵机打角
		leijia=le_mid[daolu-2]+le_mid[daolu-1]+le_mid[daolu]+le_mid[daolu+1];
		daolub=(uint16)(leijia/4);
		differ=(int)(zhongdian-daolub);
	}
	//判断障碍
	if(g_lu_flag == 5 && !g_shi_flag)
	{
		for(i = ROW-6; i > 20; i--)
			if( (fa_left[i]-fa_left[i+3]>17 && fa_left[i]-fa_left[i+4]>17
			        && Abs(fa_left[i],fa_left[i-1])<3 && Abs(fa_left[i], fa_left[i-2])<3
			        && Abs(fa_left[i],fa_left[i-3])<3)  && (fa_right[10]<150
			                && fa_right[5]<150 && fa_right[15]<150 && fa_right[20]<150
			                && fa_left[5]>10 && fa_left[10]>10 && fa_left[15]>10 && fa_left[20]>10) )
			{
				leftbar_begin = i;
				leftbar_flag = 1;
				break;
			}
		for(i = ROW-6; i > 20; i--)
			if(((fa_right[i]-fa_right[i+3]<-17 && fa_right[i]-fa_right[i+4]<-17
			        && Abs(fa_right[i],fa_right[i-1])<3 && Abs(fa_right[i], fa_right[i-2])<3
			        && Abs(fa_right[i],fa_right[i-3])<3)) && (fa_right[5]<150 && fa_right[10]<150
			                && fa_right[15]<150 && fa_right[20]<150 &&fa_left[5]>10 && fa_left[10]>10
			                && fa_left[15]>10 && fa_left[20]>10) )
			{
				rightbar_begin = i;
				rightbar_flag = 1;
				break;
			}


	}
	i=0;
	if(leftbar_flag || rightbar_flag)  //通过判成直道判断
	{
		g_lu_flag = 6;
		if(leftbar_flag == 1)
		{
			leftbar_flag = 0;
			for(i = ROW; i > 20; i--)
				le_left[i]  = fa_left[leftbar_begin]+barjia;
		}
		if(rightbar_flag == 1)
		{
			rightbar_flag = 0;
			for(i = ROW; i > 20; i--)
				le_right[i]  = fa_right[rightbar_begin]-barjian;
		}
		for(i=ROW; i>1; i--) //更新中点
		{
			le_mid[i-1]=(le_right[i-1]+le_left[i-1])>>1;
		}
		differ = zhongdian-(le_mid[37]+le_mid[36])/2;
	}
  Actuall_Mid = fa_mid[57];
  Actuall_Ekk = Actuall_Mid - 80;
  if(/*R_Huan_Entry_Flag*//*R_Huan_Flag*//*&&!R_Huan_In_Flag*//*(R_Huan_Predict2_Flag||*/R_Huan_Flag&&!R_Huan_In_Flag)
    differ=-50;
  /*for(i=0;i<ROW-5;i++)
  {
    if(Image_Data[i][le_right[i]]==!Image_Data[i+1][le_right[i]]&&Image_Data[i][le_right[i]]==!Image_Data[i+2][le_right[i]])
    {
      s_flag1++;
    }
    if(Image_Data[59-i][le_left[59-i]]==!Image_Data[58-i][le_left[59-i]]&&Image_Data[59-i][le_left[59-i]]==!Image_Data[57-i][le_left[59-i]])
    {
      s_flag2++;
    }
    
  }
  if(Abs(s_flag1,s_flag2)>=0)
  {
    Buzzer=1;
    g_lu_flag=9;
      //break;
  }
  else
  {
    Buzzer=0;
  }*/

}

void Calculation_Pd()//计算舵机Pd值
{
	/***判断出不同赛道类型后赋予舵机不同的pd数值*****/
	//根据实际情况进行调整
	//用不到
	if(g_lu_flag==5)//直道
	{
		servo_Kp=kpzhi;
		servo_Kd=kdzhi;
		if(differ > 35)
		{
			servo_Kp= kpzhi+ABS(differ)*weitiao_zhi;
			servo_Kd=kdweitiao;
		}

	}
	else if(g_lu_flag==3)//这是左弯道
	{
		servo_Kp=kpyul;
		servo_Kd=kdyul;
		if(ABS(differ)>=qufenl_1)  //50
		{
			servo_Kp=kpyul+ABS(differ)*weitiaol_1;
			servo_Kd=kdyul_1;
		}
		if(ABS(differ)>=qufenl_2)
		{
			servo_Kp = kpyul+ABS(differ)*weitiaol_2;
			servo_Kd=kdyul_2;
		}

		if(ABS(differ)>qufenl_3)//63
		{
			servo_Kp=kpyul+ABS(differ)*weitiaol_3;//0.0085;
			servo_Kd=kdyul_3;
		}
	}
	else if(g_lu_flag==4)//这是右弯道
	{
		servo_Kp=kpyur;
		servo_Kd=kdyur;
		if(ABS(differ)>=qufenr_1)  //50
		{
			servo_Kp=kpyur+ABS(differ)*weitiaor_1;
			servo_Kd=kdyur_1;
		}
		if(ABS(differ)>=qufenr_2)
		{
			servo_Kp =kpyur+ABS(differ)*weitiaor_2;
			servo_Kd=kdyur_2;
		}

		if(ABS(differ)>qufenr_3)//63
		{
			servo_Kp=kpyur+ABS(differ)*weitiaor_3;//0.0085;
			servo_Kd=kdyur_3;
		}
	}
	else if(g_lu_flag==1||g_lu_flag==2)//道路急转
	{

		servo_Kp=kpyur;
		servo_Kd=kdyur;
	}
	else if(g_lu_flag == 6)   //障碍
	{
		servo_Kp=kpbar;
		servo_Kd=kdbar;
	}
  if(R_Huan_Flag)
  {
    servo_Kp=kpyuhuan;
    servo_Kd=kdyuhuan;
  }
}



uint8 Abs(uint8 n,uint8 m)
{
	int16 k;
	k=n-m;
	if(k<0)
		return (-k);
	else
		return k;
}

void Get(uint8 *bArray, uint8 iFilterLen)
{
	uint8 i,j;// 循环变量
	uint8 bTemp;
	for (j = 0; j < iFilterLen - 1; j ++)  // 用冒泡法对数组进行排序
	{
		for (i = 0; i < iFilterLen - j - 1; i ++)
		{
			if (bArray[i] > bArray[i + 1])
			{
				// 互换
				bTemp = bArray[i];
				bArray[i] = bArray[i + 1];
				bArray[i + 1] = bTemp;
			}
		}
	}
	if ((iFilterLen & 1) > 0)   // 计算中值  //奇数为1，偶数为零
	{
		bTemp = bArray[(iFilterLen + 1) / 2];// 数组有奇数个元素，返回中间一个元素
	}
	else
	{
		bTemp = (bArray[iFilterLen / 2] + bArray[iFilterLen / 2 + 1]) / 2;// 数组有偶数个元素，返回中间两个元素平均值
	}
	mid_num=bTemp;
	max_num=bArray[iFilterLen-1];
	min_num=bArray[0];
}

void Bar()
{
  for(i=0;i<15&&Image_Data[i+2][le_mid[i+2]]&&Image_Data[i+4][le_mid[i+4]]&&Image_Data[i+6][le_mid[i+6]]
      &&Image_Data[i+14][40]==Image_Data[i+14][120]&&Image_Data[i+14][100]==Image_Data[i+14][60]&&g_lu_flag==5;i++)
    bar_flag=1;
  if(bar_flag&&Distance<1000)
  {
    buzzer_Flag=1;
    differ=30;
    Servo_PD(differ);
    Delay_Ms(400);
    differ=0;
    Servo_PD(differ);
    Delay_Ms(400);
    differ=-30;
    Servo_PD(differ);
    Delay_Ms(500);
    differ=0;
    Servo_PD(differ);
    Delay_Ms(10);
    buzzer_Flag=0;   
  }
}
void Duanlu()//白1黑0
{
  /*for(i=ROW-1; i>3; i--)//从下向上查找
	{
		if((le_left[i]-le_left[i+1]>30
      &&le_left[i]-le_left[i+2]>30
      &&le_left[i]-le_left[i-3]>30)||(le_right[i+1]-le_right[i]>30
      &&le_right[i+2]-le_right[i]>30
      &&le_right[i+3]-le_right[i]>30))    
		{
      if(i>ROW-20&&((!Image_Data[i][le_left[i]]&&!Image_Data[i][le_left[i]+10]&&!Image_Data[i][le_left[i]-10])
        ||(!Image_Data[i][le_right[i]]&&!Image_Data[i][le_right[i]+10]&&!Image_Data[i][le_right[i]-10]))
        &&Image_Data[i+5][70]==Image_Data[i+5][90]&&Image_Data[i+5][60]==Image_Data[i+5][100])
      {
        g_lu_flag=8;//
        Duan_flag=1;
        Duan_count++;
        Buzzer=1;
        break;
      }
		}
	}
  
  if(Duan_count>2000)
    Duan_count=1999;
  for(i=0; i<ROW-15; i++)       //
	{
    if(Abs(le_left[i],le_left[i-1])>20
      &&Abs(le_left[i],le_left[i-2])>20
      &&Abs(le_left[i],le_left[i-3])>20&&Abs(le_right[i],le_right[i-1])>30
      &&Abs(le_right[i],le_right[i-2])>30
      &&Abs(le_right[i],le_right[i-3])>30)
    {
      Duan_flag=0;
      Duan_count=0;
      Buzzer=0;
      break;
    }
	}*/
  if(shangyan>ROW-12&&duanlu1)
  {
    Duan_flag=1;
    //Buzzer=1;
    Duan_count++;
  }
  if(Duan_count>2000)
    Duan_count=1999;
  
  if(/*!Image_Data[56][10]&&!Image_Data[56][20]&&!Image_Data[56][30]&&!Image_Data[56][40]&&!Image_Data[56][50]
     &&!Image_Data[56][60]&&!Image_Data[56][70]&&!Image_Data[56][80]&&!Image_Data[56][90]&&!Image_Data[56][100]
     &&!Image_Data[56][110]&&!Image_Data[56][120]&&!Image_Data[56][130]&&!Image_Data[56][140]&&!Image_Data[56][150] 
     &&(Image_Data[55][80]||Image_Data[54][80]||Image_Data[53][80]||Image_Data[52][80]||Image_Data[51][80]
        ||Image_Data[50][80]||Image_Data[49][80]||Image_Data[48][80]||Image_Data[47][80]||
          Image_Data[46][80]||Image_Data[45][80]||Image_Data[44][80])*/
     Image_Data[56][80]&&Image_Data[50][80]&&Image_Data[45][80]&&Image_Data[40][80]&&Image_Data[35][80]&&Image_Data[30][80]&&
       Image_Data[25][80]&&Image_Data[20][80]&&Image_Data[15][80]&&Image_Data[10][80])
  {
    Duan_flag=0;
    if(Duan_count>80)
      magnethuan=1;
    Duan_count=0;
    GUI_wrlval(0, 4,(int32)Duan_count,4,0);
    //Buzzer=0;
  }
}

#include "include.h"

#define ABS(i) (((i)>=0)?(i):(0-i))//����ֵ
uint8  Image_Data_1[ROW/2][COLUMN/2]; //����ѹ�����ͼ��
uint8 Temp;
uint8 Temp_1;
uint16 i = 0;
uint16 j = 0;



/*****************��ʼѰ���ߣ�����*********/
uint8 le_left[ROW],le_mid[ROW],le_right[ROW];    //��߽��������ұ߽���������������
uint8 fa_left[ROW],fa_mid[ROW],fa_right[ROW];//����Ѱ�ñ���
uint8 xun_left[ROW],xun_right[ROW]; //�Ƿ�Ѱ���߱�־λ
uint8  bu_left[ROW],bu_right[ROW];//���߱�־λ�����в��ߺ󣬱�־λ��1
uint8 yu_wid[3]= {74,73,71};   //��60��59,58���������
uint8 zhongdian=80;          //ʵ�ʵ�ʱ���ٸ�
uint8 track=80;          //��������ֵ
/********************************************/

/*************�����߼��******************/
uint8 Qipao_be = 0;;   //��������ֵ�Ƿ�ִ�������߼�����,0��ִ�У�1ִ��
/********************************************/


/************���������б�*******/
uint16  daolu=0,daolub=0;     //��·��Ч��
uint16  shangbian=0,shangyan=0;//�����ϱ���
uint8 jian_bian = 0;
uint8 jian_r = 0;
uint8 jian_l =0;
uint8 shang_r = 0;
uint8 shang_l = 0;
uint8  shangyanyu;//�ж����ֱ��
uint16 leijia=0;  //ȡƽ��ֵȷ����ǵ�
/********************************************/


/*************ǰհ��ֵ********************/
uint8  daoluyuzhi;//ֱ����ǰհֵ
uint8  daoluyuwanl;//���ǰհֵ
uint8  daoluyuwanr;
uint8  daoluyuzhi_temp;
uint8  daoluyuwanl_temp;
uint8  daoluyuwanr_temp;
uint8  yuhuanyuzhi;//Բ��ǰհ
uint8  yuhuanwanl;
uint8  yuhuanwanr;
int Actuall_Ekk;         //ʵ��ƫ��
int Actuall_Mid;
/********************************************/


/**********���P Dֵ�������ز���***********/

float  kpzhi;//ֱ����pֵ
float  kdzhi;//ֱ����dֵ
float  kpyul;//������pֵ
float  kpyur;//����ҵ�pֵ
float  kdyul;//������dֵ
float  kdyur;//����ҵ�dֵ

float  kdyul_1;
float  kdyul_2;
float  kdyul_3;
float  kdyur_1;
float  kdyur_2;
float  kdyur_3;

float  kpyuhuan;//���pֵ
float  kdyuhuan;//���dֵ
float  kpyuhuan2;//�����pֵ
float  kdyuhuan2;//�����dֵ

float weitiao_zhi = 0;//ֱ����pֵ΢��
float kdweitiao = 0;

float weitiaol_1=0; //�������ʱ���pֵ�õ���
float weitiaor_1= 0;
float weitiaol_2=0; //�������ʱ���pֵ�õ���
float weitiaor_2= 0;
float weitiaol_3=0; //�������ʱ���pֵ�õ���
float weitiaor_3= 0;

uint8 qufenl_1=0; //�жϴ���С�丳�費ͬ��pdֵ
uint8 qufenl_2 = 0;
uint8 qufenl_3 = 0;
uint8 qufenr_1 = 0;
uint8 qufenr_2 = 0;
uint8 qufenr_3 = 0;
/********************************************/


/*****************�������Ͳ���*********/
uint8 g_lu_flag=10;
//g_lu_flag=0 ʮ��·��
//g_lu_flag=1 ��·����ת
//g_lu_flag=2 ��·����ת
//g_lu_flag=3;��·��ת
//g_lu_flag=4;��·��ת
//g_lu_flag=5 ֱ��
//g_lu_flag=6 �ϰ�
//g_lu_flag=7;����
uint8  wan_flag=0;//�����޷�ʮʹ��
uint8 g_shi_flag=0;//ʮ�ֱ�־λ;
/********************************************/


/************�޷�ģ����������ʹ�ã�*********/
uint8 xf_flag=0;//�޷���־
uint8 xf_left=0;//�޷����־
uint8 xf_right=0;//�޷��ұ�־
uint8 xf_leftz=1;
uint8 xf_lefty=3;
uint8 xf_rightz=COLUMN-3;
uint8 xf_righty=COLUMN-1;
/********************************************/


/********************һ�㲹��****************/
int    chazhil,chazhil1,chazhil2,//��������м��ֵ
  chazhir,chazhir1,chazhir2;//�ұ������м��ֵ
/********************************************/


/*****************��ֵ�˲�***************/
uint8   mid_num=0;
uint8   max_num=0;
uint8   min_num=0;
#define shuzu_num   3         //ÿ�вɼ�����
uint8 zhongzhi[shuzu_num];
/********************************************/


/*****************ʮ�ֲ���***************/
int   shi_cha=0;//ʮ��·�ڵĲ�ֵ
int   le_cha=0;//·��ֵ
uint8  shi_left_be;//ʮ����߿�ʼ
uint8  shi_left_en;//ʮ����߽���
uint8  shi_right_be;//ʮ���ұ߿�ʼ
uint8  shi_right_en;//ʮ���ұ߽���
uint8  shi_lie=0;// ��Ѱʮ�ֵ���ֵ����
/********************************************/


/*********************�ϰ�***************/
uint8 leftbar_flag = 0;
uint8 leftbar_begin = 0;
uint8 rightbar_flag = 0;
uint8 rightbar_begin = 0;
uint8 barjia = 0;
uint8 barjian = 0;
float kpbar = 0;
float kdbar = 0;
/******************************************/


/***************�����߼��*****************/
void Qipaojiance();   //�����߼��

uint8 jiance_qi=0;//��������߱�־�������Բ��֮�󣬿�ʼ���������
uint8 qipao_flag=0;//�����߱�־
uint8 qi_temp=0;
uint8 qi_temp2=0;
/******************************************/


/*****************Բ����������*********/
uint8 serTempX[COLUMN]= {0};  //����ɨ����
uint8 Lost_Right[ROW];        //�ұ߽綪��
uint8 Lost_Left[ROW];        //��߽綪��
uint8 Track_Width[ROW];       //�������
uint8 Straight_Length = 0;        //ֱ������
uint8 Huan_Flag = 0;          //������־λ
uint8 Track_Width_Actuall[60]=
{36,36,36,37,38,38,38,38,39,40,
 40,40,40,42,42,42,44,44,44,45,
 46,46,48,48,50,50,51,52,53,54,
 55,56,57,58,59,61,63,65,65,65,
 67,69,71,72,74,77,78,82,83,86,
 89,91,94,98,100,104,108,111,115,119};

int R_Huan_Time_Counter = 0;    //�һ���������ʱ��
uint8 R_Huan_Flag = 0;        //�һ�����־λ
uint8 R_Huan_Entry_Flag = 0;  //�һ�����ڱ�־λ
uint8 R_Huan_In_Flag = 0;     //�һ��������ڲ���־λ
uint8 R_Huan_Exit_Flag = 0;   //�һ������ڱ�־λ
uint8 R_Huan_Exit_Temp_Flag = 0;   //�һ������ڱ�־λ
uint8 R_Huan_Exit_Temp_Y = 0;  //�һ������ڹյ�����
uint8 R_Huan_Predict1_Flag = 0;     //�һ���Ԥ�е�һ�׶α�־λ
uint8 R_Huan_Predict2_Flag = 0;     //�һ���Ԥ�еڶ��׶α�־λ
uint8 R_Huan_Cliff_Flag = 0;       //�һ����յ�
float R_Huan_K_Entry = 0;   //�һ�������б��
/******************************************/

uint8 zhongzhuanl=0,zhongzhuanr=0;//��ʱ����
uint8 temp2=0,temp3=0;//��ʱʹ�õı���;

/********************************************/



/*****************��������******************/
uint8 Circle_Flag = 0;          //������־λ
uint8 R_Circle_Flag = 0;        //�һ�����־λ
uint8 L_Circle_Flag = 0;        //�󻷵���־λ
/******************************************/




/*******************ͼ����***********************/
void image_deal()
{
  image_select((uint8 *)Image_Data, (uint8 *)Pix_Data);
  Bu_Clear_Flag();  //���߱�־λ����
	Find_Bound();   //Ѱ����
	Save_Bound();   //��ʼ���߱���
	Filters() ;//��ֵ�˲�
	Bu();  //����
  Huan_Bu(); //��������
	Bu_Crossroad(); //ʮ�ֲ���
	Bu_Curve() ;  //�������
	//Start_Flag();  //���ܼ��
	Find_Mid() ; //���������¼����е�
	Calculation_Differ() ;//������differ
	Calculation_Pd();//������Pdֵ;
}
/*****************************************************/





void Bu_Clear_Flag()  //���߱�־λ����
{
	for(i=0; i<ROW; i++) //���߱�־λ
	{
		bu_left[i]=0;
		bu_right[i]=0;
		xun_left[i]=0;
		xun_right[i]=0;
    Lost_Right[i]=0;   //�ұ߽綪��
    Lost_Left[i]=0;    //��߽綪��
    Track_Width[i]=0;
	}
}
//Ѱ�ұ���
void Find_Bound()   //Ѱ����
{
	le_left[ROW-1]=0;           //��߽�Ϊ����
	le_right[ROW-1]=COLUMN;     //�ұ߽�Ϊ����
  /*Ѱ�����һ�б���*/
	for(j=track; j>0; j--) 
	{
		if(Image_Data[ROW-1][j]&&!Image_Data[ROW-1][j-1])    //0�Ǻڵ�   1�ǰ׵�
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
	le_mid[ROW-1]=(le_left[ROW-1]+le_right[ROW-1])>>1; //��2
  /*Ѱ���������*/
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
			xun_left[i-1]=1;//Ϊ�˱���ڵ�

		le_right[i-1]=COLUMN;
		for(j=le_mid[i]; j<COLUMN-1; j++)
			if(Image_Data[i-1][j]&&!Image_Data[i-1][j+1])
			{
				le_right[i-1]=j;
				break;
			}

		if(le_right[i-1]==COLUMN&&!(!Image_Data[i-1][le_mid[i]+1]&&!Image_Data[i-1][le_mid[i]+2]))
			xun_right[i-1]=1;//Ϊ�˱���ڵ�

		le_mid[i-1]=(le_left[i-1]+le_right[i-1])>>1;
	}
	track=(uint8)((le_mid[57]+le_mid[59]+le_mid[58])/3);     //��ֵ��һ��Ѱ���е�
}

void Save_Bound()   //��ʼ���߱���
{
	for(i=ROW; i>1; i--)
	{
		fa_left[i-1]=le_left[i-1];
		fa_mid[i-1]=le_mid[i-1];
		fa_right[i-1]=le_right[i-1];
	}
}

void Filters() //��ֵ�˲�
{
	max_num=0;//  ��Ҫ��Ŀ����Ϊ��ǰ��������㲻��
	min_num=0;
	mid_num=0;
	for(i=ROW-shuzu_num; i>55; i--) //��ֵ�˲�
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
	for(i=ROW-shuzu_num; i>55; i--) //��ֵ�˲�
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
void Bu()  //����
{
	zhongzhuanl=0;
	zhongzhuanr=0;
	chazhil=0;
	chazhil1=0;
	chazhil2=0;
	chazhir=0;
	chazhir1=0;
	chazhir2=0;

	//��60,59,58�в���
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
			if(le_left[ROW-Tempi-1]<10)//����
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
			if(le_right[ROW-Tempi-1]>COLUMN-10)//����
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
//��ROW-4�в���
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

void Huan_Bu()   //��������
{
Straight_Length = 0 ;
  int i;
  int temp;
  R_Huan_Exit_Temp_Y = 0;
  R_Huan_Time_Counter ++;
  R_Huan_Exit_Temp_Flag = 0;
  if(R_Huan_Time_Counter > 2000)
    R_Huan_Time_Counter = 1999;
  R_Huan_Cliff_Flag = 0;
  for(i=15; i<ROW-5; i++)       
	{
          if((fa_right[i-2]-fa_right[i])>20
            &&((fa_right[i+1]-fa_right[i])>=0)&&((fa_right[i+1]-fa_right[i])<4)&&((fa_right[i+2]-fa_right[i+1])>=0)&&((fa_right[i+2]-fa_right[i+1])<4)&&((fa_right[i+3]-fa_right[i+2])>=0)&&((fa_right[i+3]-fa_right[i+2])<4)
            &&(fa_right[i-2]>COLUMN-5)&&(fa_right[i-3]>COLUMN-5)&&(fa_right[i-4]>COLUMN-5)&&(fa_right[i-5]>COLUMN-5))
            R_Huan_Cliff_Flag = 1;
	}
  for(i=5; i<ROW-5; i++)       
	{
          if((fa_left[i]-fa_left[i-2])>0&&(fa_left[i-1]-fa_left[i-3])>0&&(fa_left[i-2]-fa_left[i-4])>0&&
             (fa_left[i]-fa_left[i+2])>0&&(fa_left[i+1]-fa_left[i+3])>0&&(fa_left[i+2]-fa_left[i+4])>0
            )
          {
            R_Huan_Exit_Temp_Y = i;
            break;
          }
	}
    if(R_Huan_Exit_Temp_Y>30)
      R_Huan_Exit_Temp_Flag = 1;
  for(i=0; i<ROW; i++)       //�����ж�
	{
          if(fa_left[i]<5)
            Lost_Left[i]=1;
          if(fa_right[i]>COLUMN-5)
            Lost_Right[i]=1;
          Track_Width[i] = fa_right[i] - fa_left[i]; 
	}
  for(i=ROW-1; i>0; i--)       //ֱ�����ȼ���
	{
          if(!Image_Data[i][80])
            break;
	}
  Straight_Length = 59 - i;
  
  temp = fa_right[ROW-3]-3;
  for(i=55;i>0;i--)
  {
    if(!Image_Data[i][temp])
      break;
  }
  R_Huan_K_Entry=10*(fa_right[ROW-3]-35)/(59-i);
  
  /******************�һ���ʶ��***********/
  if(R_Huan_Cliff_Flag&&!R_Huan_Flag&&Lost_Right[30]&&Lost_Right[32]&&!Lost_Left[30]&&!Lost_Left[32])  //��һ�׶�:�Ҷ��ߣ��󲻶���,ֱ�����ȴ���57��������ȴ���110С��150
  {
    R_Huan_Predict1_Flag = 1;       //�һ�����һ�׶�Ԥ��
    R_Huan_Time_Counter = 0;
  }

   
  if(R_Huan_Predict1_Flag)
  {
    if(R_Huan_Time_Counter>30||Lost_Left[30]||Lost_Left[32])       //����߶�ʧ����ʱ�����
    {
      R_Huan_Time_Counter = 0;
      R_Huan_Predict1_Flag = 0;
    }
    if(!Lost_Right[30]&&!Lost_Right[32]&&!Lost_Left[30]&&!Lost_Left[32]&&R_Huan_Time_Counter>3)  //�ڶ��׶�:���Ҿ������ߣ�ֱ�����ȴ���50��ʱ�䳬��3
    {
      R_Huan_Predict2_Flag = 1;
      R_Huan_Predict1_Flag = 0;
      R_Huan_Time_Counter = 0;
    }
  }
  if(R_Huan_Predict2_Flag&&Lost_Right[30]&&Lost_Right[32]&&!Lost_Left[30]&&!Lost_Left[32])//������ڣ������׶Σ����Ҷ��ߣ��󲻶���
    {
      R_Huan_Flag = 1;
      R_Huan_Entry_Flag = 0;
      R_Huan_In_Flag = 0;     
      R_Huan_Exit_Flag = 0;  
      R_Huan_Predict1_Flag = 0;
      R_Huan_Predict2_Flag = 0;
      R_Huan_Time_Counter = 0;
    }
  if(R_Huan_Predict2_Flag&&R_Huan_Time_Counter>50)       //����߶�ʧ����ʱ�����
    {
      R_Huan_Time_Counter = 0;
      R_Huan_Predict2_Flag = 0;
    }
  if(!R_Huan_Exit_Flag&&R_Huan_Flag&&R_Huan_Time_Counter<40)  //�ж�Ϊ��������ʱ��С��20��Ϊ������� 
  {
    R_Huan_Entry_Flag = 1; 
  }
  else
  {
    R_Huan_Entry_Flag = 0; 
  }
  
  if(R_Huan_Entry_Flag)
    //Buzzer=1;
 
  
  
  if(R_Huan_Flag&&R_Huan_Exit_Temp_Flag&&R_Huan_Time_Counter > 100) //��������ʱ�䳬��50������߶��ߣ���Ϊ������
  {
          // Buzzer=0;
    R_Huan_Exit_Flag = 1;
    R_Huan_Time_Counter = 0;
  }
 
  
  if(R_Huan_Exit_Flag && R_Huan_Time_Counter > 40)  //�ж�Ϊ��������ʱ�䳬��20����������
  {

    R_Huan_Exit_Flag = 0;
    R_Huan_Flag = 0;
    R_Huan_Time_Counter = 0;
  }
   
  if(R_Huan_Flag&&!R_Huan_Entry_Flag&&!R_Huan_Exit_Flag) //�ж�Ϊ�������Ȳ�����ڣ�Ҳ���ǳ��ڣ�Ϊ������
    R_Huan_In_Flag = 1;
  else
    R_Huan_In_Flag = 0;
  /***********************************************/
  /*******************�һ�������******************/
  if(R_Huan_Entry_Flag)      //����������
  {
    for(i=ROW-1; i>0; i--)
      le_left[i] = (uint8)(R_Huan_K_Entry*(59-i)/10);   
    for(i=ROW-1; i>0; i--)
    {
      if(le_left[i]>le_right[i])
        le_right[i] = COLUMN-2;
    }
  }
  if(R_Huan_Exit_Flag)      //������˳���ұ���
  {
    for(i=ROW-1; i>0; i--)
    {
      //if(((le_right[i]+le_right[i])/2)<130)
        le_right[i] = COLUMN-2;
      le_left[i]=COLUMN-20; 
    }
    
  }
  /****************************************/
}



void Bu_Circle()   //��������
{
  
}




void Bu_Crossroad() //ʮ�ֲ���
{
	//��һ����������������ޱ��ߣ���¼�õ�����
	for(i=ROW-1; i>4; i--)
	{
		if((le_left[i]<10)&&(le_left[i-1]<10)&&(le_left[i-2]<10)&&(le_left[i-3]<10)&&(le_left[i-4]<10)&&(le_left[i-5]<10)&&(le_left[i-6]<10)
		        &&xun_left[i]&&xun_left[i-1]&&xun_left[i-2]&&xun_left[i-3]&&xun_left[i-4]&&xun_left[i-5]&&xun_left[i-6])//����8������ޱ���
		{

			zhongzhuanl=i;      //��¼λ��
			break;
		}
	}
	//��һ�������������ұ��ޱ��ߣ���¼�õ�����
	for(i=ROW-1; i>4; i--)
	{
		if((le_right[i]>150)&&(le_right[i-1]>150)&&(le_right[i-2]>150)&&(le_right[i-3]>150)&&
		        (le_right[i-4]>150)&&(le_right[i-5]>150)&&(le_right[i-6]>150)&&xun_right[i]&&
		        xun_right[i-1]&&xun_right[i-2]&&xun_right[i-3]&&xun_right[i-4]&&xun_right[i-5]&&xun_right[i-6])  //����8���ұ��ޱ���
		{

			zhongzhuanr=i;                                  //��¼λ��
			break;
		}
	}

	if(zhongzhuanl&&zhongzhuanr)//������ʮ��   zhongzhuanl&&zhongzhuanr
	{

		shi_left_en=zhongzhuanl;                          //ʮ�ֽ�����
		for(i=shi_left_en; i<ROW-3; i++)
			if(le_left[i]&&le_left[i+1]&&le_left[i]>le_left[i+2]&&le_left[i]>le_left[i-1])//�ҹս�
			{
				shi_left_en=i;                                //��¼��߽����У������¹ս�
				break;
			}
		shi_right_en=zhongzhuanr;                       //��¼ʮ���ұ߽�����
		for(i=shi_right_en; i<ROW-3; i++)
			if(le_right[i]<COLUMN&&le_right[i+1]<COLUMN&&le_right[i]<le_right[i+2]&&le_right[i]<le_right[i-1])
			{
				shi_right_en=i;                               //��¼�ұ߽����У������¹ս�
				break;
			}

		temp2=0;
		temp3=0;
		shi_lie=0;
		//�����ж�ʮ��
		for(j=le_left[shi_left_en]+1; j<le_right[shi_right_en]-6; j++)
		{
			for(i=ROW-1; i>15&&Image_Data[i][j]&&Image_Data[i][j+2]&&Image_Data[i][j+4]&&
			        Image_Data[i][j+6]&&Image_Data[i][j+8]&&Image_Data[i][j+10]; i--)
			{
				if(i==16)
				{
					temp3=1;//����ѭ���궨
					shi_lie=j+6;
					break;
				}
			}
			if(temp3==1)
				break;
		}
		//���ʮ�ֹյ�������ת��־��̫Զ������ʮ��
		if(shi_left_en>zhongzhuanl+20)//�ٴ��ж��Ƿ���ʮ����Ҫ�����
		{
			shi_lie=0;
		}
		else if(shi_right_en>zhongzhuanr+20)
		{
			shi_lie=0;
		}

		if(shi_right_en>25&&shi_left_en>25&&shi_lie&&
		        (le_left[shi_left_en]<zhongdian+40&&le_right[shi_right_en]>zhongdian-40))//��Ч��ʮ��
		{
			if(shi_left_en<shi_right_en)
				temp2=shi_left_en;
			else
				temp2=shi_right_en;//�ҵ�ǰ�������Ѱ���
			if(shi_lie)//����Ѱ��1
			{
				for(i=temp2; i>0; i--)
				{
					if(i<=16)//Ѱ�߷�ʽѡ��
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
					if(i<=16)//Ѱ�߷�ʽѡ��
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
			shi_left_be=zhongzhuanl-4;//��ȥ4����Ϊ��������û�е�
			for(i=shi_left_be; i>3; i--)
				if(le_left[i]>le_left[shi_left_en]&&le_left[i+1]>10&&
				        le_left[i]<le_left[i-1]+3&&le_left[i]>le_left[i-1]-4)
				{
					shi_left_be=i;                               //��¼��߿�ʼ�С������Ϲս�
					break;
				}
			shi_cha=le_left[shi_left_be]-le_left[shi_left_en];
			for(i=shi_left_be+1; i<shi_left_en; i++)
			{
				bu_left[i]=1;
				le_cha=(int)(shi_cha/(shi_left_en-i+1));
				le_left[i]=le_left[i-1]-le_cha;
				shi_cha-=le_cha;                                //��ʮ�ֱ߲���
			}

			shi_right_be=zhongzhuanr-4;
			for(i=shi_right_be+1; i>3; i--)
				if(le_right[i]<le_right[shi_right_en]&&le_right[i+1]<COLUMN-10&&
				        le_right[i]<le_right[i-1]+4&&le_right[i]>le_right[i-1]-3)
				{
					shi_right_be=i;                               //��¼�ұ߿�ʼ�У������Ϲս�
					break;
				}
			shi_cha=le_right[shi_right_be]-le_right[shi_right_en];
			for(i=shi_right_be+1; i<shi_right_en; i++)
			{
				bu_right[i]=1;
				le_cha=(int)(shi_cha/(shi_right_en-i+1));
				le_right[i]=le_right[i-1]-le_cha;
				shi_cha-=le_cha;                                //��ʮ�ֱ߲���
			}
			g_shi_flag=1;                                       //ʮ�����ͱ�־
			g_lu_flag=0;//ʮ��

		}
	}
}

void Bu_Curve()   //�������
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

	for(i=ROW-1; i>3; i--) //�ҵ������      ����������
	{
		if(Abs(le_left[i],le_left[i-1])>40&&Abs(le_left[i],le_left[i-2])>40&&
		        Abs(le_left[i],le_left[i-3])>40)   //��ֵ����ֵ
		{
			zhongzhuanl=i;
			break;
		}
	}
	for(i=ROW-1; i>3; i--)     //�ҵ������
	{
		//�������㣬�������Բ�ֵ������ʮ
		if(Abs(le_right[i],le_right[i-1])>40&&Abs(le_right[i],le_right[i-2])>40&&
		        Abs(le_right[i],le_right[i-3])>40)
		{
			zhongzhuanr=i;
			break;
		}
	}
	if(zhongzhuanl&&le_left[zhongzhuanl]>zhongdian)//�ҵ�û�б��ߵĵط�
	{
		for(i=zhongzhuanl; i<ROW-6; i++)
		{
			if(le_right[i]==COLUMN&&le_right[i+1]==COLUMN&&le_right[i+2]==COLUMN&&le_right[i+3]==COLUMN&&
			        le_right[i+4]==COLUMN&&le_right[i+5]==COLUMN)
			{
				xf_right=1;
				temp2=i;
				break;
			}
		}

	}
	if(zhongzhuanr&&le_right[zhongzhuanr]<zhongdian)//�ҵ�û�б��ߵĵط�
	{
		for(i=zhongzhuanr; i<ROW-6; i++)
		{
			if(!le_left[i]&&!le_left[i+1]&&!le_left[i+2]&&!le_left[i+3]&&
			        !le_left[i+4]&&!le_left[i+5])
			{

				xf_left=1;
				temp3=i;
				break;
			}
		}
	}
	if(xf_right)//����޷������ұ��߾������ұ�
	{
		wan_flag=1;
		for(i=zhongzhuanl; i>0; i--)
		{
			le_left[i]=xf_rightz;
		}
		for(i=temp2; i>0; i--)
		{
			le_right[i]=xf_righty;
		}
	}
	if(xf_left)//�ұ��޷������ұ��߾��������
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
	/***************һ�㲹��***************/
	zhongzhuanl=0;
	zhongzhuanr=0;
	for(i=ROW-4; i>0; i--)
	{
		if(i>6&&le_left[i]<30&&!le_left[i-1]&&!le_left[i-2]&&!le_left[i-3]&&!le_left[i-4]&&
		        !le_left[i-5]&&!le_left[i-6]&&!le_left[i-7]&&!le_left[i-8]&&!le_left[i-9])//�ܹ�7���㣬ʮ����8����
		{
			le_left[i-1]=1;
			le_left[i-2]=1;
			le_left[i-3]=1;
			le_left[i-4]=1;
			le_left[i-5]=1;
			le_left[i-6]=1;
			le_left[i-7]=1;
			le_left[i-8]=1;
			le_left[i-9]=1;//�����Ϊ�˲�����ʮ�ֵĵط�����ʹ��
			if(i>25)
				wan_flag=1;
		}
		if(i>6&&le_right[i]>COLUMN-30&&le_right[i-1]==COLUMN&&le_right[i-2]==COLUMN&&le_right[i-3]==COLUMN&&
		        le_right[i-4]==COLUMN&&le_right[i-5]==COLUMN&&le_right[i-6]==COLUMN&&le_right[i-7]==COLUMN&&
		        le_right[i-8]==COLUMN&&le_right[i-9]==COLUMN)
		{
			le_right[i-1]=COLUMN-1;
			le_right[i-2]=COLUMN-1;
			le_right[i-3]=COLUMN-1;
			le_right[i-4]=COLUMN-1;
			le_right[i-5]=COLUMN-1;
			le_right[i-6]=COLUMN-1;
			le_right[i-7]=COLUMN-1;
			le_right[i-8]=COLUMN-1;
			le_right[i-9]=COLUMN-1;
			if(i>25)
				wan_flag=1;
		}
		if(le_left[i]>((i/40)+1)*14)//��������ֵ
			zhongzhuanl=le_left[i];
		else
			zhongzhuanl=((i/40)+1)*14;
		if(le_right[i]>((i/40)+1)*14)
			zhongzhuanr=le_right[i];
		else
			zhongzhuanr=((i/40)+1)*14;
		//bu_  ==3  ��ֱ��  ==1��ʮ��
		if(bu_left[i-1]!=3&&bu_left[i-1]!=1&&(!le_left[i-1]
		                                      ||(le_left[i-1]<zhongzhuanl-((i/40)+1)*14||le_left[i-1]>zhongzhuanl+((i/40)+1)*14)
		                                      ||(le_left[i]>le_left[i-1]+5&&le_left[i-1]+5<le_left[i-2])
		                                      ||(le_left[i]+5<le_left[i-1]&&le_left[i-1]>le_left[i-2]+5)))//�����������������û����
		{
			chazhil1=le_left[i+2]-le_left[i+1];
			chazhil2=le_left[i+3]-le_left[i+1];
			chazhil=(int)(chazhil2/2);
			if(chazhil)//�������2ʱ
				chazhil=(int)((chazhil1+(chazhil2/2))/2);
			else if(chazhil2<2&&chazhil2>-2)//����Ͱ��ռ������Ĳ�ֵ����
				chazhil=(int)chazhil2;
			if((le_left[i]>chazhil)&&(le_left[i]<COLUMN+chazhil))//���м��ʱ��
				le_left[i-1]=le_left[i]-chazhil;
			else if(le_left[i]<chazhil+1)//�������
				le_left[i-1]=1;
			else                         //�����ұ�
				le_left[i-1]=COLUMN-1;
			bu_left[i-1]=2;//���߱�־���2     ��ͬ
		}
		if(bu_right[i-1]!=3&&bu_right[i]!=1&&(le_right[i-1]==COLUMN
		                                      ||(le_right[i-1]<zhongzhuanr-((i/40)+1)*14||le_right[i-1]>zhongzhuanr+((i/40)+1)*14)
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
		if(le_right[i-1]<le_left[i-1])//��ֹ���߲�������
		{
			if(le_right[i]>zhongdian-1&&le_left[i]>zhongdian-1)
				le_right[i-1]=le_left[i-1]+2;
			else if(le_right[i]<zhongdian+1&&le_left[i]<zhongdian+1)
				le_left[i-1]=le_right[i-1]-2;
		}
		le_mid[i-1]=(le_left[i-1]+le_right[i-1])>>1;
		if(le_left[i]>COLUMN-44&&le_left[i-1]>COLUMN-39)//������߻����ұ��߳���һ����ֵ��ʱ��Ͱ������߹�ȥ
		{
			zhongzhuanl=le_left[i-1];
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
			zhongzhuanr=le_right[i-1];
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
void Start_Flag()  //���ܼ��
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
						}
						break;
					}
				}
			}
		qi_temp=0;
	}
}

void Find_Mid()  //���������¼����е�
{
	for(i=ROW; i>1; i--) //�����е�
	{
		le_mid[i-1]=(le_right[i-1]+le_left[i-1])>>1;
	}
}

void Calculation_Differ() //������differ
{
	daolub=0;//��·��ʼ

	for(shangbian=ROW-3; shangbian>2&&(le_left[shangbian]<COLUMN-shang_r||
	                                   le_left[shangbian-1]<COLUMN-shang_r||le_left[shangbian-2]<COLUMN-shang_r)&&
	        (le_right[shangbian]>shang_l||le_right[shangbian-1]>shang_l||le_right[shangbian-2]>shang_l); shangbian--);

	for(jian_bian=ROW-3; jian_bian>2&&(le_left[jian_bian]<COLUMN-jian_r||
	                                   le_left[jian_bian-1]<COLUMN-jian_r||le_left[jian_bian-2]<COLUMN-jian_r)&&
	        (le_right[jian_bian]>jian_l||le_right[jian_bian-1]>jian_l||le_right[jian_bian-2]>jian_l); jian_bian--);


	for(shangyan=ROW-3; (shangyan>2)&&(le_left[shangyan-2]<zhongdian||
	                                   le_left[shangyan-1]<zhongdian||le_left[shangyan]<zhongdian)&&
	        (le_right[shangyan-2]>zhongdian||le_right[shangyan-1]>zhongdian||
	         le_right[shangyan]>zhongdian); shangyan--);   //Ѱ�������ϱ���
	daoluyuzhi=daoluyuzhi_temp;
  daoluyuwanl=daoluyuwanl_temp;
  daoluyuwanr=daoluyuwanr_temp;
	if(shangbian>4)//˵�������
	{
		if(le_mid[shangbian+4]<zhongdian&&le_mid[shangbian+5]<zhongdian)
		{
			//���������
			g_lu_flag=3;
			//����ϱ�С��ǰհֵ����·��Ч��Ϊǰհֵ������Ϊ�ϱ�ֵ
			if(shangbian<daoluyuwanl)
				daolu=daoluyuwanl;
			else
				daolu=shangbian;
			daolub=(uint16)((le_mid[daolu]+le_mid[daolu+2]+le_mid[daolu+1])/3);
			//���ݵ�·��Чֵ�е���ʵ���е��ֵ�����������
			differ=(int)(1*(zhongdian-daolub));
			/*if(shangbian > daoluyuwanl)
			{
				if(differ>0)
					differ=differ+3*(daolu-daoluyuwanl);  //�Ķ�   //
				else
					differ=differ-3*(daolu-daoluyuwanl);//��ֱ�߰�����һ��
			}*/
		}
		if(le_mid[shangbian+4]>zhongdian&&le_mid[shangbian+5]>zhongdian)
		{
			//���������
			g_lu_flag=4;

			if(shangbian<daoluyuwanr)
				daolu=daoluyuwanr;
			else
				daolu=shangbian;

			daolub=(uint16)((le_mid[daolu]+le_mid[daolu+2]+le_mid[daolu+1])/3);
			differ=(int)(1*(zhongdian-daolub));

			/*if(shangbian > daoluyuwanr)
			{
				if(differ>0)
					differ=differ+3*(daolu-daoluyuwanr);
				else
					differ=differ-3*(daolu-daoluyuwanr);//��ֱ�߰�����һ��
			}*/
		}
	}


	if(shangbian<=4)            //ֱ��
	{
		g_lu_flag=5;
		if(shangbian<daoluyuzhi)
			daolu=daoluyuzhi;
		else
			daolu=shangbian+5;
		leijia=0;
		//���ݵ�·��Ч�����µ������ƽ��ֵ���е��ֵȷ��������
		leijia=le_mid[daolu-2]+le_mid[daolu-1]+le_mid[daolu]+le_mid[daolu+1];
		daolub=(uint16)(leijia/4);
		differ=(zhongdian-daolub);
	}
	//�ж��ϰ�

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
	if(leftbar_flag || rightbar_flag)  //ͨ���г�ֱ���ж�
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
		for(i=ROW; i>1; i--) //�����е�
		{
			le_mid[i-1]=(le_right[i-1]+le_left[i-1])>>1;
		}
		differ = zhongdian-(le_mid[37]+le_mid[36])/2;
	}
        Actuall_Mid = fa_mid[57];
        Actuall_Ekk = Actuall_Mid - 80;

}

void Calculation_Pd()//������Pdֵ
{
	/***�жϳ���ͬ�������ͺ�������ͬ��pd��ֵ*****/
	//����ʵ��������е���
	//�ò���
	if(g_lu_flag==5)//ֱ��
	{
		servo_Kp=kpzhi;
		servo_Kd=kdzhi;
		if(differ > 35)
		{
			servo_Kp= kpzhi+ABS(differ)*weitiao_zhi;
			servo_Kd=kdweitiao;
		}

	}
	else if(g_lu_flag==3)//���������
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
	else if(g_lu_flag==4)//���������
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
	else if(g_lu_flag==1||g_lu_flag==2)//��·��ת
	{

		servo_Kp=kpyur;
		servo_Kd=kdyur;
	}
	else if(g_lu_flag == 6)   //�ϰ�
	{
		servo_Kp=kpbar;
		servo_Kd=kdbar;
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
	uint8 i,j;// ѭ������
	uint8 bTemp;
	for (j = 0; j < iFilterLen - 1; j ++)  // ��ð�ݷ��������������
	{
		for (i = 0; i < iFilterLen - j - 1; i ++)
		{
			if (bArray[i] > bArray[i + 1])
			{
				// ����
				bTemp = bArray[i];
				bArray[i] = bArray[i + 1];
				bArray[i + 1] = bTemp;

			}
		}
	}
	if ((iFilterLen & 1) > 0)   // ������ֵ  //����Ϊ1��ż��Ϊ��
	{
		bTemp = bArray[(iFilterLen + 1) / 2];// ������������Ԫ�أ������м�һ��Ԫ��
	}
	else
	{
		bTemp = (bArray[iFilterLen / 2] + bArray[iFilterLen / 2 + 1]) / 2;// ������ż����Ԫ�أ������м�����Ԫ��ƽ��ֵ
	}
	mid_num=bTemp;
	max_num=bArray[iFilterLen-1];
	min_num=bArray[0];
}
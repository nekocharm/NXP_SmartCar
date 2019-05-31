# include "include.h"


void par(uint8 aa)
{
	/*中速*/
	switch(aa)
	{ 
    case 1:
      //电磁pd
      Direction_P=690;//600
      Direction_D=100;
      //电机pid
      motor_Kp=36;//20//25
      motor_Ki=1;//1
      motor_Kd=5.5;//20
      //道路类型
      jian_r = 54;  //加监速度54/55
      jian_l = 55;
      shang_r = 46;  //46//判断弯道直道/50
      shang_l = 47;//47/50
      shangyanyu=52;
      //直道pd
      kpzhi=2;  //2.5
      kdzhi=20;   //6
      //弯道pd
      kpyu=2;
      kdyu=38;
      kpyul=2;//3.8/4.5/4.8/6.4
      kpyur=2;//3.8/6.7
      kdyul=40;//10/17/8/48
      kdyur=40;//10/17/8/50
      //圆环pd值
      kpyuhuan=5;
      kdyuhuan=5;
      
      
      //直道pd计算
      weitiao_zhi = 0.01;
      kdweitiao = 6.5;
      //判断大弯小弯赋予不同的pd值
      qufenl_1 = 10;//35
      qufenl_2 = 20;                    //50
      qufenl_3 = 30;
      qufenr_1 = 10;
      qufenr_2 = 20;//22
      qufenr_3 = 30;//32

      //用于弯道时舵机p值调整
      weitiaol_1 = 0.009;//0.00905  0.007/*0.02/0.01
      weitiaol_2 = 0.011;//0.00905//0.0019
      weitiaol_3=0.012;//0.05 88   0.02
      weitiaor_1 = 0.009;//0.
      weitiaor_2 = 0.011;//0.00905//0.0019
      weitiaor_3=0.012;//0.0588   0.02
      //弯道pd
      kdyul_1 = kdyul;//20
      kdyul_2 = kdyul;//23//15
      kdyul_3 = kdyul;
      kdyur_1 = kdyur;//20
      kdyur_2 = kdyur;    //15
      kdyur_3 = kdyur;
      
      //前瞻数值
      daoluyuzhi_temp=42;//37
      daoluyuwanl_temp=35;//37
      daoluyuwanr_temp=35;//37
      yuhuanyuzhi=44;//圆环前瞻
      yuhuanwanl=44;
      yuhuanwanr=44;

      //速度控制
      speed_fast = 250;//240
      speed_mid =230;//220
      speed_low = 220;//210
      speed_huan=211;//201

      
      //障碍
      /*barjia = 17;
      barjian = 17;
      kpbar = 1;
      kdbar = 6;
      break;*/
      break;
    case 2:
      Direction_P=1800;//600
      Direction_D=2000;
      //电机pid
      motor_Kp=36;//20//25
      motor_Ki=1;//1
      motor_Kd=5.5;//20
      //道路类型
      jian_r = 54;  //加监速度54/55
      jian_l = 55;
      shang_r = 57;  //46//判断弯道直道/50
      shang_l = 57;//47/50
      shangyanyu=52;
      //直道pd
      kpzhi=2.6;  //2.5
      kdzhi=20;   //6
      //弯道pd
      kpyu=2;
      kdyu=38;
      kpyul=4.8;//3.8/4.5/4.8/6.4
      kpyur=4.1;//3.8/6.7
      kdyul=48;//10/17/8
      kdyur=50;//10/17/8
      //圆环pd值
      kpyuhuan=5;
      kdyuhuan=5;
      
      
      //直道pd计算
      weitiao_zhi = 0.01;
      kdweitiao = 6.5;
      //判断大弯小弯赋予不同的pd值
      qufenl_1 = 10;//35
      qufenl_2 = 20;                    //50
      qufenl_3 = 30;
      qufenr_1 = 12;
      qufenr_2 = 22;
      qufenr_3 = 32;

      //用于弯道时舵机p值调整
      weitiaol_1 = 0.01;//0.00905  0.007/*0.02/0.01
      weitiaol_2 = 0.025;//0.00905//0.0019
      weitiaol_3=0.032;//0.05 88   0.02
      weitiaor_1 = 0.009;//0.
      weitiaor_2 = 0.022;//0.00905//0.0019
      weitiaor_3=0.029;//0.0588   0.02
      //弯道pd
      kdyul_1 = kdyul;//20
      kdyul_2 = kdyul;//23//15
      kdyul_3 = kdyul;
      kdyur_1 = kdyur;//20
      kdyur_2 = kdyur;    //15
      kdyur_3 = kdyur;
      
      //前瞻数值
      daoluyuzhi_temp=42;//37
      daoluyuwanl_temp=32;//37
      daoluyuwanr_temp=32;//37
      yuhuanyuzhi=44;//圆环前瞻
      yuhuanwanl=44;
      yuhuanwanr=44;

      //速度控制
      speed_fast = 240;//190
      speed_mid =200;//
      speed_low = 210;//160
      speed_huan=200;//*/

      
      //障碍
      /*barjia = 17;
      barjian = 17;
      kpbar = 1;
      kdbar = 6;
      break;*/
	}
}
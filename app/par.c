# include "include.h"


void par(uint8 aa)
{
	/*中速*/
	switch(aa)
	{ 
    case 1:
      //电磁pd
      Direction_P=900;//600
      Direction_D=1900;
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
      kpzhi=2.7;  //2.5
      kdzhi=20;   //6
      //弯道pd
      kpyu=6;
      kdyu=38;
      kpyul=6.8;//3.8/4.5/4.8/6.4
      kpyur=6.83;//3.8/6.7
      kdyul=38;//10/17/8
      kdyur=38;//10/17/8
      //圆环pd值
      kpyuhuan=5;
      kdyuhuan=5;
      
      
      //直道pd计算
      weitiao_zhi = 0.01;
      kdweitiao = 6.5;
      //判断大弯小弯赋予不同的pd值
      qufenl_1 = 10;//35
      qufenl_2 = 30;                    //50
      qufenl_3 = 40;
      qufenr_1 = 10;
      qufenr_2 = 25;
      qufenr_3 = 38;

      //用于弯道时舵机p值调整
      weitiaol_1 = 0.01;//0.00905  0.007/*0.02/0.01
      weitiaol_2 = 0.025;//0.00905//0.0019
      weitiaol_3=0.03;//0.05 88   0.02
      weitiaor_1 = 0.01;//0.
      weitiaor_2 = 0.026;//0.00905//0.0019
      weitiaor_3=0.03;//0.0588   0.02
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
      /*speed_fast = 220;//190
      speed_mid =205;//
      speed_low = 200;//
      speed_huan=190;//*/
      speed_fast = 215;//190
      speed_mid =190;//
      speed_low = 200;//160
      speed_huan=175;//*/

      
      //障碍
      /*barjia = 17;
      barjian = 17;
      kpbar = 1;
      kdbar = 6;
      break;*/
      break;
    case 2:
      //电磁pd
      Direction_P=600;
      Direction_D=2200;
      //电机pid
      motor_Kp=36;//20//25
      motor_Ki=1;//1
      motor_Kd=5.5;//20
      //道路类型
      jian_r = 53;  //加监速度
      jian_l = 54;
      shang_r = 45;  //46//判断弯道直道/50
      shang_l = 45;//47
      shangyanyu=52;
      //直道pd
      kpzhi=2.5;  //2.3
      kdzhi=5;   //6
      //弯道pd
      kpyul=6.4;//3.8/4.5/4.8
      kpyur=6.4;//3.8
      kdyul=8;//10/17
      kdyur=8;//10/17
      //圆环pd值
      /*kpyuhuan=7;
      kdyuhuan=5;
      kpyuhuan2=4;
      kdyuhuan2=5;//*/
      //直道pd计算
      weitiao_zhi = 0.01;
      kdweitiao = 6.5;
      //判断大弯小弯赋予不同的pd值
      qufenl_1 = 30;//35
      qufenl_2 = 40;                    //50
      qufenl_3 = 60;
      qufenr_1 = 10;
      qufenr_2 = 20;
      qufenr_3 = 30;

      //用于弯道时舵机p值调整
      weitiaol_1 = 0.01;//0.00905  0.007/*0.02/0.01
      weitiaol_2 = 0.02;//0.00905//0.0019
      weitiaol_3=0.03;//0.05 88   0.02
      weitiaor_1 = 0.01;//0.
      weitiaor_2 = 0.03;//0.00905//0.0019
      weitiaor_3=0.03;//0.0588   0.02
      //弯道pd
      kdyul_1 = kdyul;//20
      kdyul_2 = kdyul;//23//15
      kdyul_3 = kdyul;
      kdyur_1 = kdyur;//20
      kdyur_2 = kdyur;    //15
      kdyur_3 = kdyur;
      
      //前瞻数值
      daoluyuzhi_temp=42;//37
      daoluyuwanl_temp=37;//36 //32//37
      daoluyuwanr_temp=37;//38//32//37
      yuhuanyuzhi=44;//圆环前瞻
      yuhuanwanl=44;
      yuhuanwanr=44;

      //速度控制
      speed_fast = 150;//190
      speed_mid =100;//
      speed_low = 100;//
      speed_huan=100;

      
      //障碍
      /*barjia = 17;
      barjian = 17;
      kpbar = 1;
      kdbar = 6;
      break;*/
      break;
	}
}
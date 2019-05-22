# include "include.h"


void par(uint8 aa)
{
	/*中速*/
	switch(aa)
	{ 
    case 1:
      //电磁pd
      Direction_P=1000;//600
      Direction_D=2200;
      //电机pid
      motor_Kp=36;//20//25
      motor_Ki=1;//1
      motor_Kd=5.5;//20
      //道路类型
      jian_r = 70;  //加监速度54/55
      jian_l = 70;
      shang_r = 50;  //46//判断弯道直道/50
      shang_l = 50;//47/50
      shangyanyu=52;
      //直道pd
      kpzhi=3;  //2.5
      kdzhi=20;   //6
      //弯道pd
      kpyul=6.7;//3.8/4.5/4.8/6.4
      kpyur=6.7;//3.8
      kdyul=35;//10/17/8
      kdyur=35;//10/17/8
      //圆环pd值
      kpyuhuan=5;
      kdyuhuan=5;
      
      
      //直道pd计算
      weitiao_zhi = 0.01;
      kdweitiao = 6.5;
      //判断大弯小弯赋予不同的pd值
      qufenl_1 = 20;//35
      qufenl_2 = 40;                    //50
      qufenl_3 = 60;
      qufenr_1 = 20;
      qufenr_2 = 40;
      qufenr_3 = 60;

      //用于弯道时舵机p值调整
      weitiaol_1 = 0.01;//0.00905  0.007/*0.02/0.01
      weitiaol_2 = 0.02;//0.00905//0.0019
      weitiaol_3=0.025;//0.05 88   0.02
      weitiaor_1 = 0.01;//0.
      weitiaor_2 = 0.02;//0.00905//0.0019
      weitiaor_3=0.025;//0.0588   0.02
      //弯道pd
      kdyul_1 = kdyul;//20
      kdyul_2 = kdyul;//23//15
      kdyul_3 = kdyul;
      kdyur_1 = kdyur;//20
      kdyur_2 = kdyur;    //15
      kdyur_3 = kdyur;
      
      //前瞻数值
      daoluyuzhi_temp=42;//37
      daoluyuwanl_temp=37;//37
      daoluyuwanr_temp=37;//37
      yuhuanyuzhi=44;//圆环前瞻
      yuhuanwanl=44;
      yuhuanwanr=44;

      //速度控制
      /*speed_fast = 220;//190
      speed_mid =205;//
      speed_low = 200;//
      speed_huan=190;//*/
      speed_fast = 200;//190
      speed_mid =180;//
      speed_low = 160;//
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
      qufenl_1 = 20;//35
      qufenl_2 = 40;                    //50
      qufenl_3 = 60;
      qufenr_1 = 20;
      qufenr_2 = 40;
      qufenr_3 = 60;

      //用于弯道时舵机p值调整
      weitiaol_1 = 0.01;//0.00905  0.007/*0.02/0.01
      weitiaol_2 = 0.02;//0.00905//0.0019
      weitiaol_3=0.03;//0.05 88   0.02
      weitiaor_1 = 0.01;//0.
      weitiaor_2 = 0.02;//0.00905//0.0019
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
      speed_fast = 100;//190
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
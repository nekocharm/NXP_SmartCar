# include "include.h"


void par()
{
	/*����*/
	switch(dip)
	{
    
    case 16:
      //���pid
      motor_Kp=36;//20//25
      motor_Ki=1;//1
      motor_Kd=5.5;//20
      //��·����
      jian_r = 53;  //�Ӽ��ٶ�
      jian_l = 54;
      shang_r = 46;  //�ж����ֱ��
      shang_l = 47;
      shangyanyu=52;
      //ֱ��pd
      kpzhi=2.6;  //2.3
      kdzhi=6;   //6
      //���pd
      kpyul=7;//3.8/4.5/4.8
      kpyur=7;//3.8
      kdyul=0;//10/17
      kdyur=0;//10/17
      //Բ��pdֵ
      kpyuhuan=1;
      kdyuhuan=5;
      kpyuhuan2=0.5;
      kdyuhuan2=5;
      //ֱ��pd����
      weitiao_zhi = 0.01;
      kdweitiao = 6.5;
      //�жϴ���С�丳�費ͬ��pdֵ
      qufenl_1 = 20;//35
      qufenl_2 = 50;                    //50
      qufenl_3 = 70;
      qufenr_1 = 20;
      qufenr_2 = 50;
      qufenr_3 = 70;

      //�������ʱ���pֵ����
      weitiaol_1 = 0.01;//0.00905  0.007/*0.02/0.01
      weitiaol_2 = 0.02;//0.00905//0.0019
      weitiaol_3=0.03;//0.05 88   0.02
      weitiaor_1 = 0.01;//0.
      weitiaor_2 = 0.02;//0.00905//0.0019
      weitiaor_3=0.03;//0.0588   0.02
      //���pd
      kdyul_1 = kdyul;//20
      kdyul_2 = kdyul;//23//15
      kdyul_3 = kdyul;
      kdyur_1 = kdyur;//20
      kdyur_2 = kdyur;    //15
      kdyur_3 = kdyur;
      
      //ǰհ��ֵ
      daoluyuzhi_temp=42;//37
      daoluyuwanl_temp=37;//36 //32//37
      daoluyuwanr_temp=37;//38//32//37
      yuhuanyuzhi=44;//Բ��ǰհ
      yuhuanwanl=44;
      yuhuanwanr=44;

      //�ٶȿ���
      speed_fast = 195;//190
      speed_mid =170;//
      speed_low = 160;//
      speed_huan=150;

      
      //�ϰ�
      /*barjia = 17;
      barjian = 17;
      kpbar = 1;
      kdbar = 6;
      break;*/
      
      /*case 32:
      //dingshijishi=5;
      jian_r = 53;  //�Ӽ��ٶ�
      jian_l = 54;
      shang_r = 46;  //�ж����ֱ��
      shang_l = 47;


      shangyanyu=52;
      kpzhi=1.2; 
      kdzhi=2;   
      kpyul=1.3;//�����еñȽ������͸�Сһ��
      kpyur=1.3; 
      kdyul=1.5;
      kdyur=1.5;  
      kpyuhuan=2;
      kdyuhuan=4;
      kpyuhuan2=1.5;
      kdyuhuan2=4;

      weitiao_zhi = 0;
      kdweitiao = 5;

      qufenl_1 = 30;//35
      qufenl_2 = 60;                    //50
      qufenl_3 = 100;
      qufenr_1 = 40;
      qufenr_2 = 60;
      qufenr_3 = 100;



      weitiaol_1 = 0.01;
      weitiaol_2 = 0.01;
      weitiaol_3=0.01;
      weitiaor_1 = 0.01;
      weitiaor_2 = 0.01;
      weitiaor_3=0.01;

      kdyul_1 = kdyul;
      kdyul_2 = kdyul;
      kdyul_3 = kdyul;
      kdyur_1 = kdyur;
      kdyur_2 = kdyur;  
      kdyur_3 = kdyur;

      daoluyuzhi_temp=37;
      daoluyuwanl_temp=37;
      daoluyuwanr_temp=37;
      yuhuanyuzhi=45;
      yuhuanwanl=45;
      yuhuanwanr=45;

      speed_fast = 430;
      speed_mid =400;
      speed_low = 350;
      speed_huan=320;
      motor_Kp=10;
      motor_Ki=6;
      motor_Kd=10;

      barjia = 17;
      barjian = 17;
      kpbar = 1;
      kdbar = 6;
      break;*/
    /*case 64:
      //dingshijishi=8;
      jian_r = 53;  //�Ӽ��ٶ�
      jian_l = 54;
      shang_r = 46;  //�ж����ֱ��
      shang_l = 47;


      shangyanyu=52;
      kpzhi=2;  //1.051//2.5//2
      kdzhi=15;   //5
      kpyul=4;//1.5/*1.6//1.68//3/4
      kpyur=4; //1.8//////1.68/3/4
      kdyul=17;//23//24 //23  14////17
      kdyur=17;  //17///////////////17

      kpyuhuan=1;
      kdyuhuan=5;
      kpyuhuan2=0.5;
      kdyuhuan2=5;

      weitiao_zhi = 0;
      kdweitiao = 5;

      qufenl_1 = 30;//35
      qufenl_2 = 60;                    //50
      qufenl_3 = 100;
      qufenr_1 = 40;
      qufenr_2 = 60;
      qufenr_3 = 100;



      weitiaol_1 = 0.01;//0.00905  0.007/*0.02/0.01
      weitiaol_2 = 0.01;//0.00905//0.0019
      weitiaol_3=0.01;//0.05 88   0.02
      weitiaor_1 = 0.01;//0.
      weitiaor_2 = 0.01;//0.00905//0.0019
      weitiaor_3=0.01;//0.0588   0.02

      kdyul_1 = kdyul;//20
      kdyul_2 = kdyul;//23//15
      kdyul_3 = kdyul;
      kdyur_1 = kdyur;//20
      kdyur_2 = kdyur;    //15
      kdyur_3 = kdyur;

      daoluyuzhi_temp=45;//37
      daoluyuwanl_temp=37;//36 //32//37
      daoluyuwanr_temp=37;//38//32//37
      yuhuanyuzhi=44;//Բ��ǰհ
      yuhuanwanl=44;
      yuhuanwanr=44;


      speed_fast = 100;//180//140//200//180
      speed_mid =90;//125//180/////////160
      speed_low = 80;//135//120//180///150
      speed_huan=70;

      motor_Kp=10;//22  50  100
      motor_Ki=1;//17.57//6  12
      motor_Kd=50;//7jk

      barjia = 17;
      barjian = 17;
      kpbar = 1;
      kdbar = 6;
      break;*/
	}
}
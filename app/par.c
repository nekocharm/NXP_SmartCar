# include "include.h"


void par(uint8 aa)
{
	/*����*/
	switch(aa)
	{ 
    case 1:
      //���pd
      Direction_P=150;//600
      Direction_D=800;
      //���pid
      motor_Kp=36;//20//25
      motor_Ki=1;//1
      motor_Kd=5.5;//20
      //��·����
      jian_r = 54;  //�Ӽ��ٶ�54/55
      jian_l = 55;
      shang_r = 47;  //46//�ж����ֱ��/50
      shang_l = 47;//47/50
      shangyanyu=52;
      //ֱ��pd
      kpzhi=2;  //2.5
      kdzhi=20;   //6
      //���pd
      kpyu=2;
      kdyu=38;
      kpyul=2.1;//2.1
      kpyur=2.1;//2.2
      kdyul=20;//40
      kdyur=20;//40
      //Բ��pdֵ
      kpyuhuan=2.3;
      kdyuhuan=5;
      
      
      //ֱ��pd����
      weitiao_zhi = 0.01;
      kdweitiao = 6.5;
      
      //�жϴ���С�丳�費ͬ��pdֵ
      qufenl_1 = 10;
      qufenl_2 = 20;                    
      qufenl_3 = 30;
      qufenr_1 = 10;
      qufenr_2 = 20;
      qufenr_3 = 30;

      //�������ʱ���pֵ����
      weitiaol_1 = 0.009;
      weitiaol_2 = 0.011;
      weitiaol_3=0.012;
      weitiaor_1 = 0.009;
      weitiaor_2 = 0.011;
      weitiaor_3=0.012;
      //���pd
      kdyul_1 = kdyul;
      kdyul_2 = kdyul;
      kdyul_3 = kdyul;
      kdyur_1 = kdyur;
      kdyur_2 = kdyur;    
      kdyur_3 = kdyur;
      
      //ǰհ��ֵ
      daoluyuzhi_temp=42;//37
      daoluyuwanl_temp=37;//37
      daoluyuwanr_temp=37;//37
      yuhuanyuzhi=44;//Բ��ǰհ
      yuhuanwanl=44;
      yuhuanwanr=44;

      //�ٶȿ���
      speed_fast = 270;//240
      speed_mid =250;//220
      speed_low = 230;//210
      speed_huan=206;//201

      
      //�ϰ�
      /*barjia = 17;
      barjian = 17;
      kpbar = 1;
      kdbar = 6;
      break;*/
      break;
    case 2:
      //���pd
      Direction_P=150;//600
      Direction_D=800;
      //���pid
      motor_Kp=36;//20//25
      motor_Ki=1;//1
      motor_Kd=5.5;//20
      //��·����
      jian_r = 54;  //�Ӽ��ٶ�54/55
      jian_l = 55;
      shang_r = 47;  //46//�ж����ֱ��/50
      shang_l = 47;//47/50
      shangyanyu=52;
      //ֱ��pd
      kpzhi=2.2;  //2.5
      kdzhi=20;   //6
      //���pd
      kpyu=3.5;
      kdyu=50;
      kpyul=2.2;//2.1
      kpyur=2.2;//2.1
      kdyul=20;//40
      kdyur=20;//40
      //Բ��pdֵ
      kpyuhuan=2.2;
      kdyuhuan=30;
      
      
      //ֱ��pd����
      weitiao_zhi = 0.01;
      kdweitiao = 6.5;
      
      //�жϴ���С�丳�費ͬ��pdֵ
      qufenl_1 = 10;
      qufenl_2 = 20;                    
      qufenl_3 = 30;
      qufenr_1 = 10;
      qufenr_2 = 20;
      qufenr_3 = 30;

      //�������ʱ���pֵ����
      weitiaol_1 = 0.009;
      weitiaol_2 = 0.011;
      weitiaol_3=0.012;
      weitiaor_1 = 0.009;
      weitiaor_2 = 0.011;
      weitiaor_3=0.012;
      //���pd
      kdyul_1 = kdyul;
      kdyul_2 = kdyul;
      kdyul_3 = kdyul;
      kdyur_1 = kdyur;
      kdyur_2 = kdyur;    
      kdyur_3 = kdyur;
      
      //ǰհ��ֵ
      daoluyuzhi_temp=42;//37
      daoluyuwanl_temp=35;//37
      daoluyuwanr_temp=35;//37
      yuhuanyuzhi=44;//Բ��ǰհ
      yuhuanwanl=44;
      yuhuanwanr=44;

      //�ٶȿ���
      speed_fast = 320;//240
      speed_mid =250;//220
      speed_low = 230;//210
      speed_huan=206;//201

      
      //�ϰ�
      /*barjia = 17;
      barjian = 17;
      kpbar = 1;
      kdbar = 6;
      break;*/
      break;
    case 3:
      //���pd
      Direction_P=150;//600
      Direction_D=800;
      //���pid
      motor_Kp=36;//20//25
      motor_Ki=1;//1
      motor_Kd=5.5;//20
      //��·����
      jian_r = 54;  //�Ӽ��ٶ�54/55
      jian_l = 55;
      shang_r = 47;  //46//�ж����ֱ��/50
      shang_l = 47;//47/50
      shangyanyu=52;
      //ֱ��pd
      kpzhi=2.2;  //2.5
      kdzhi=30;   //6
      //���pd
      kpyu=3.5;
      kdyu=50;
      kpyul=2.2;//2.1
      kpyur=2.2;//2.1
      kdyul=20;//40
      kdyur=20;//40
      //Բ��pdֵ
      kpyuhuan=2.2;
      kdyuhuan=5;
      
      
      //ֱ��pd����
      weitiao_zhi = 0.01;
      kdweitiao = 6.5;
      
      //�жϴ���С�丳�費ͬ��pdֵ
      qufenl_1 = 10;
      qufenl_2 = 20;                    
      qufenl_3 = 30;
      qufenr_1 = 10;
      qufenr_2 = 20;
      qufenr_3 = 30;

      //�������ʱ���pֵ����
      weitiaol_1 = 0.009;
      weitiaol_2 = 0.011;
      weitiaol_3=0.012;
      weitiaor_1 = 0.009;
      weitiaor_2 = 0.011;
      weitiaor_3=0.012;
      //���pd
      kdyul_1 = kdyul;
      kdyul_2 = kdyul;
      kdyul_3 = kdyul;
      kdyur_1 = kdyur;
      kdyur_2 = kdyur;    
      kdyur_3 = kdyur;
      
      //ǰհ��ֵ
      daoluyuzhi_temp=42;//37
      daoluyuwanl_temp=30;//37
      daoluyuwanr_temp=30;//37
      yuhuanyuzhi=44;//Բ��ǰհ
      yuhuanwanl=44;
      yuhuanwanr=44;

      //�ٶȿ���
      speed_fast = 250;//240
      speed_mid =220;//220
      speed_low = 210;//210
      speed_huan=206;//201

      
      //�ϰ�
      /*barjia = 17;
      barjian = 17;
      kpbar = 1;
      kdbar = 6;
      break;*/
      break;
	}
}
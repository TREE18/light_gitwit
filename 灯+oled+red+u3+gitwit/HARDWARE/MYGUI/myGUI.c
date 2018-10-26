#include "myGUI.h"
#include "key.h"
#include "usart.h"
#include "delay.h"
#include "ws2812.h"
#include "oled.h"
#include "esp8266-ap.h"
#include "exti.h"
#include "usart3.h"
#include "usart4.h"

u8 keyFun=0;        //װ�ز˵�����
void (*keyFunPt)(); //ָ�뺯��

extern u8 music01[6],music02[6],music03[6],music04[6];
u8 keyFlag=0;				//���ؼ�ֵ
extern char red_flag;
char time_c=0,time_s=0,flag=0,homework_flag=0,posture_flag=0,night_flag=0,cmd=0;
int WIFI_Sign=33,Electricity_Sign=4,Flashlight_Sign=1;

void Fun_light(void)
{
	char k=0,tem=0,tem2=2;
	printf("guangqiang");
	OLED_CLS();
	OLED_P16x16Ch(0*16,2,44);//jiantou
	OLED_P16x16Ch(1*16,2,79);
	OLED_P16x16Ch(2*16,2,80);
	OLED_P16x16Ch(3*16,2,81);
	OLED_P16x16Ch(4*16,2,82);
	OLED_P16x16Ch(5*16,2,83);
	OLED_P16x16Ch(6*16,2,84);

	OLED_P16x16Ch(6*16,6,11);                   //��ʾ //
	OLED_P16x16Ch(7*16,6,12);                   //��ʾ //
	OLED_P16x16Ch(0*16,6,85);                   //��ʾ 
	OLED_P16x16Ch(1*16,6,86);                   //��ʾ 
	
	while(1)
	{
		keyFlag = KEY_Scan(0);

		if(keyFlag == KEY2_PRES||keyFlag == WKUP_PRES)break;
		
		if(keyFlag == KEY0_PRES)
		{	
			
			OLED_P16x16Ch(4*16,2,37);
			OLED_P16x16Ch(5*16,2,37);
			OLED_P16x16Ch(6*16,2,37);
			OLED_P16x16Ch(0*16,2,44);
			OLED_P16x16Ch(1*16,2,87);
			OLED_P16x16Ch(2*16,2,88);
			OLED_P16x16Ch(3*16,2,37);
			
			OLED_P16x16Ch(6*16,2,95);
			OLED_P16x16Ch(7*16,2,96);
			
			OLED_P16x16Ch(6*16,6,37);                   //��ʾ //
			OLED_P16x16Ch(7*16,6,37);                   //��ʾ //
			//OLED_P16x16Ch(0*16,6,44);
	        OLED_P16x16Ch(0*16,6,85);                   //��ʾ 
	        OLED_P16x16Ch(1*16,6,86);                   //��ʾ 
			
			time_s=0;
			time_c++;
			flag=0;
			
			tem=k;
			SendOneFrame_sample(&s6100[k++][0]);
			if(k==4)k=0;

		}
		
		if(keyFlag == KEY1_PRES)
		{
			OLED_P16x16Ch(4*16,2,37);
			//OLED_P16x16Ch(5*16,2,37);
			OLED_P16x16Ch(6*16,2,37);
			//OLED_P16x16Ch(0*16,2,44);
			OLED_P16x16Ch(1*16,2,87);
			OLED_P16x16Ch(2*16,2,88);
			OLED_P16x16Ch(3*16,2,37);
			
			OLED_P16x16Ch(6*16,2,95);
			OLED_P16x16Ch(7*16,2,96);
			
			OLED_P16x16Ch(6*16,6,37);                   //��ʾ //
			OLED_P16x16Ch(7*16,6,37);                   //��ʾ //
			//OLED_P16x16Ch(0*16,6,44);
	       // OLED_P16x16Ch(0*16,6,85);                   //��ʾ 
	        OLED_P16x16Ch(1*16,6,86);                   //��ʾ 
			
			OLED_P16x16Ch(0*16,2,37);
			OLED_P16x16Ch(5*16,2,44);
			
			SendOneFrame_stronge(&s6100[tem][0],&zero[0][0],tem2++);
			if(tem2==4)tem2=0;
																															
		}
		//------------------------------------------------------//
		cmd=zigbee_recevice_cmd("open_red","down_red","posture_good","posture_bad","homework_good","homework_bad");
		if( cmd==1&&night_flag==1)SendOneFrame_sample(&s2500[0][0]);
		else if(cmd==2)SendOneFrame_sample(&zero[0][0]);
		
		if( cmd==6&&homework_flag==1)Uart4_Send(music01,6);
		else if(cmd==5);
		
		if( cmd==4&&posture_flag==1)Uart4_Send(music03,6);
		else if(cmd==3)Uart4_Send(music04,6);
		//------------------------------------------------------//
	}
}

//**************************************************************************************************************//
void Fun_homework(void)
{	
	OLED_CLS();
	
	OLED_P16x16Ch(0*16,2,44);
	OLED_P16x16Ch(1*16,2,75);
	OLED_P16x16Ch(2*16,2,76);
	OLED_P16x16Ch(3*16,2,77);
	OLED_P16x16Ch(4*16,2,78);

	
	OLED_P16x16Ch(1*16,4,89);
	OLED_P16x16Ch(2*16,4,90);
	OLED_P16x16Ch(3*16,4,91);
	OLED_P16x16Ch(4*16,4,92);
	
	OLED_ShowNum(6*16,6,1,1,12);
	OLED_P6x8Str(6.5*16,7,"/");
	OLED_P6x8Str(7*16,7,"2");
	
	if(night_flag==1)
	{
		FlashlightDisplay();
		OLED_P16x16Ch(6*16,2,37);
	}
	if(homework_flag==1)
	{
		WifiDisplay();
		OLED_P8x16Str(6*16,2,"ON");
	}
	if(posture_flag==1)
	{
		OLED_P8x16Str(6*16,4,"ON");
	}

	while(1)
	{
		keyFlag = KEY_Scan(0);
		if(keyFlag==KEY0_PRES || keyFlag==KEY1_PRES||keyFlag==KEY2_PRES)break; //���а������¾�����
		if(keyFlag==WKUP_PRES)
		{	
			homework_flag++;
			
			if(homework_flag==2)
			{
				zigbee_send_cmd("homework_off","0",0);
				homework_flag=0;
				OLED_P16x16Ch(0,0,37);
				OLED_P16x16Ch(6*16,2,37);
			}
			else
			{
				open_ap();
				zigbee_send_cmd("homework_on","0",0);
				OLED_P8x16Str(6*16,2,"ON");
				WifiDisplay();
				printf("home_on");
			}
		}
	//-----------------------------------------------------------------------//	
		cmd=zigbee_recevice_cmd("open_red","down_red","posture_good","posture_bad","homework_good","homework_bad");
		if( cmd==1&&night_flag==1)SendOneFrame_sample(&s2500[0][0]);
		else if(cmd==2)SendOneFrame_sample(&zero[0][0]);
		
		if( cmd==6&&homework_flag==1)Uart4_Send(music01,6);
		else if(cmd==5);
		
		if( cmd==4&&posture_flag==1)Uart4_Send(music03,6);
		else if(cmd==3)Uart4_Send(music04,6);
	//-----------------------------------------------------------------------//			
	}
}
//**********************************************************************************************************************//

void Fun_posture(void)
{
	if(night_flag==1)
	{
		FlashlightDisplay();
		OLED_P16x16Ch(6*16,2,37);
	}
	if(homework_flag==1)
	{
		WifiDisplay();
		OLED_P8x16Str(6*16,2,"ON");
	}
	
	if(posture_flag==1)
	{
		OLED_P8x16Str(6*16,4,"ON");
	}

	OLED_P16x16Ch(0*16,2,37);
	OLED_P16x16Ch(0*16,4,44);

	while(1)
	{
		keyFlag = KEY_Scan(0);
		if(keyFlag==KEY0_PRES || keyFlag==KEY1_PRES||keyFlag==KEY2_PRES)break; //���а������¾�����
		if(keyFlag==WKUP_PRES)
		{
			posture_flag++;
			
			if(posture_flag==2)
			{	
				zigbee_send_cmd("posture_off","0",0);
				posture_flag=0;
				OLED_P16x16Ch(2*16,0,37);
				OLED_P16x16Ch(6*16,4,37);
			}
			else
			{	
				if(!zigbee_send_cmd("posture_on","posture_OK",0))OLED_P8x16Str(6*16,4,"ON");		
			}
			printf("pos_on");
		}
		//-------------------------------------------------------------//
		cmd=zigbee_recevice_cmd("open_red","down_red","posture_good","posture_bad","homework_good","homework_bad");
		if( cmd==1&&night_flag==1)SendOneFrame_sample(&s2500[0][0]);
		else if(cmd==2)SendOneFrame_sample(&zero[0][0]);
		
		if( cmd==6&&homework_flag==1)Uart4_Send(music01,6);
		else if(cmd==5);
		
		if( cmd==4&&posture_flag==1)Uart4_Send(music03,6);
		else if(cmd==3)Uart4_Send(music04,6);
		//------------------------------------------------------------//
	}
}

//****************************************************************************************************//
void Fun_night(void)
{
	//u8 *p;
	OLED_CLS();
	
	if(night_flag==1)
	{
		FlashlightDisplay();
		OLED_P8x16Str(6*16,2,"ON");
	}
	
	if(homework_flag==1)
	{
		WifiDisplay();
		//OLED_P16x16Ch(6*16,2,37);
	}
	
	if(posture_flag==1)
	{
		OLED_P16x16Ch(6*16,4,37);
	}

	
	OLED_P16x16Ch(0*16,2,37);
	OLED_P16x16Ch(0*16,2,44);
	OLED_P16x16Ch(1*16,2,93);
	OLED_P16x16Ch(2*16,2,94);

	OLED_ShowNum(6*16,6,2,1,12);
	OLED_P6x8Str(6.5*16,7,"/");
	OLED_P6x8Str(7*16,7,"2");
	
	
	printf("night");
	while(1)
	{
		keyFlag = KEY_Scan(0);
		if(keyFlag==KEY0_PRES || keyFlag==KEY1_PRES||keyFlag==KEY2_PRES)break; //���а������¾�����
		if(keyFlag==WKUP_PRES)
		{
			night_flag++;
			if(night_flag==2)
			{
				zigbee_send_cmd("night_off","0",0);
				night_flag=0;
				OLED_P16x16Ch(2*16,0,37);
				OLED_P16x16Ch(6*16,2,37);
	
			}
			else 
			{
				zigbee_send_cmd("night_on","0",0);
				red_Init();
				OLED_P8x16Str(6*16,2,"ON");
				FlashlightDisplay();
			}
			printf("nig_on");
		}
		//--------------------------------------------------------------------------//
		cmd=zigbee_recevice_cmd("open_red","down_red","posture_good","posture_bad","homework_good","homework_bad");
		if( cmd==1&&night_flag==1){SendOneFrame_sample(&s2500[0][0]);Uart4_Send(music01,6);}
		else if(cmd==2)SendOneFrame_sample(&zero[0][0]);
		
		if( cmd==6&&homework_flag==1)Uart4_Send(music01,6);
		else if(cmd==5);
		
		if( cmd==4&&posture_flag==1)Uart4_Send(music03,6);
		else if(cmd==3)Uart4_Send(music04,6);
		//--------------------------------------------------------------------------//
	}
}
//*****************************************************************************************************************//
/******************************************************************************************************************/
	/*�˵���4������10������*/
	/*��ǰ���¡��ϡ����롢����*/
// ��ǰ��������
// ɫ�°�����Ҫ��ת������ 0
// ��ǿ������Ҫ��ת������ 1
// ģʽ������Ҫ��ת������ 2
// ȷ�ϰ�����Ҫ��ת������ wkup
myGUIIndexTypeDef const keyTab[GUI_NUM]={
	{0,0,0,1,0,(*Fun_light)	},   //�˵���ʾ
	{1,0,0,2,1,(*Fun_homework)	}, 
	{2,0,0,3,2,(*Fun_posture)},  
	{3,0,0,1,3,(*Fun_night)},  
};


/*

* �������ܣ��������
* �����������
* �����������
* ����ֵ  ����
* ����    ��@����

*/
void displayOperation(void)
{
	switch(keyFlag)
	{
		case KEY0_PRES	:	keyFun = keyTab[keyFun].downIndex;	keyFlag=0;	break;   //ɫ��
		case KEY1_PRES		:	keyFun = keyTab[keyFun].upIndex;		keyFlag=0;	break;//��ǿ
		case KEY2_PRES	:	keyFun = keyTab[keyFun].enterIndex;	keyFlag=0;	break; //ģʽ
		case WKUP_PRES		:	keyFun = keyTab[keyFun].escIndex;		keyFlag=0;	break; //ȷ��
		
		default:break;
	}
		keyFunPt = keyTab[keyFun].function;
		(*keyFunPt)();                     //ִ�е�ǰ��������
}


//��ʾWIFI�����Ϣ
void WifiDisplay()                           //WIFI//33.34.35.36  
{
  OLED_P16x16Ch(0,0,WIFI_Sign);
}

//��ʾ��ص��������Ϣ
void ElectricityDisplay()                    //����
{
   OLED_P16x16Ch(111,0,Electricity_Sign);
}	

void FlashlightDisplay()                     //�ֵ�Ͳ
{
	if(Flashlight_Sign)
  OLED_P16x16Ch(2*16,0,40);
}





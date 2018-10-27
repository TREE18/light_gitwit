#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "ws2812.h"
#include "spi2.h"
#include "usart2.h"
#include "oled.h"
#include "myGUI.h"
#include "esp8266-ap.h"
#include "exti.h"
#include "usart3.h"
#include "usart4.h"
#include "gizwits_product.h"
#include "common.h"
#include "timer.h"

//----------------------------------------------------//
unsigned char zero[1][3]={{0,0,0}};
//	unsigned char a[8][3]={{50,5,5},{50,5,5},{50,5,5},{50,5,5},{50,5,5},{50,5,5},{50,5,5},{50,5,5}};	//����һ����ά��ÿ�������ڵ��������ݶ�Ӧһ�����ص�{G,R,B}
//	unsigned char b[8][3]={{20,220,60},{20,220,60},{20,220,60},{20,220,60},{20,220,60},{20,220,60},{20,220,60},{20,220,60}};
//	unsigned char c[8][3]={{0,255,00},{0,255,00},{0,255,00},{0,255,00},{0,255,00},{0,255,00},{0,255,00},{0,255,00}};
unsigned char s6100[4][3]={{242,255,236},{206,255,159},{185,255,105},{166,255,69}};
unsigned char s4500[1][3]={{206,255,159}};
unsigned char s3000[1][3]={{185,255,105}};	
unsigned char s2500[1][3]={{166,255,69}};
//----------------------------------------------------//									

u8 music01[6]={0xAA, 0x07, 0x02, 0x00, 0x01, 0xB4};	//����
u8 music02[6]={0xAA, 0x07, 0x02, 0x00, 0x02, 0xB5};	//����
u8 music03[6]={0xAA, 0x07, 0x02, 0x00, 0x03, 0xB6};	//����
u8 music04[6]={0xAA, 0x07, 0x02, 0x00, 0x04, 0xB7};	//����
//----------------------------------------------------//
//JTAGģʽ����,��������JTAG��ģʽ
//mode:jtag,swdģʽ����;00,ȫʹ��;01,ʹ��SWD;10,ȫ�ر�;	   
#define JTAG_SWD_DISABLE   0X02
#define SWD_ENABLE         0X01
//#define JTAG_SWD_ENABLE    0X00		
//----------------------------------------------------//
extern dataPoint_t currentDataPoint;
u16 link_time=0;
char link_flag=0,wifi_gizwit=0;
//----------------------------------------------------//
void Gizwits_Init()
{
	TIM3_Int_Init(9,7199);//1MSϵͳ��ʱ
    usart3_init(9600);//WIFI��ʼ��
}
//----------------------------------------------------//
void JTAG_Set(u8 mode)
{
	u32 temp;
	temp=mode;
	temp<<=25;
	RCC->APB2ENR|=1<<0;     //��������ʱ��	   
	AFIO->MAPR&=0XF8FFFFFF; //���MAPR��[26:24]
	AFIO->MAPR|=temp;       //����jtagģʽ
}
//----------------------------------------------------//
 int main(void)
 {	

	char key=0;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	JTAG_Set(JTAG_SWD_DISABLE);
	JTAG_Set(SWD_ENABLE);
///////////////////////////////////////////////////////////	 

//////////////////////////////////////////////////////////
	uart_init(9600);	 //���ڳ�ʼ��Ϊ115200
	USART2_Init(115200);
	usart3_init(115200);		//��ʼ������3 
	uart4_init(9600);
//////////////////////////////////////////////////////////
	Gizwits_Init();
	userInit();
    gizwitsInit();
 ///////////////////////////////////////////////////////////	
 	LED_Init();			     //LED�˿ڳ�ʼ��
	KEY_Init();          //��ʼ���밴�����ӵ�Ӳ���ӿ�
//////////////////////////////////////////////////////////
	SPI2_Init();
//////////////////////////////////////////////////////////	 
    IIC_Init();
	OLED_Init();
//////////////////////////////////////////////////////////

	printf("-----------------------");
  
 	while(1)
	{   
		printf("5s�ڰ�wkup��������ģʽ\r\n");
		while(link_flag==0)
		{
					key=KEY_Scan(0);	//�õ���ֵ
					if(key==WKUP_PRES && link_flag==0)
					{	
						printf("ѡ�� KEY1_PRES-->airlink,KEY0_PRES-->SOFT-link \r\n");
						printf("     WKUP_PRES-->link_resrt,KEY2_PRES-->null \r\n");
						while(1)
						{
							key=KEY_Scan(0);
							switch(key)
							{				 
								case WKUP_PRES:	//���Ʒ�����
									gizwitsSetMode(WIFI_RESET_MODE);//WIFI��λ
									printf("��λ");
									break;
								case KEY2_PRES:	//����LED0��ת
									LED0=!LED0;
									break;
								case KEY1_PRES:	//����LED1��ת	 
									gizwitsSetMode(WIFI_AIRLINK_MODE);//Air-linkģʽ����
									printf("Air-linkģʽ����");
									break;
								case KEY0_PRES:	//ͬʱ����LED0,LED1��ת 
									LED0=!LED0;
									LED1=!LED1;
									gizwitsSetMode(WIFI_SOFTAP_MODE);
									printf("SOFT-linkģʽ����");				
									break;
							}
							delay_ms(5);
						    userHandle();
							gizwitsHandle((dataPoint_t *)&currentDataPoint);
							
							if(wifi_gizwit==1)break;//�����ӳɹ����˳�����
						}
				}else delay_ms(10); 	
					userHandle();
					gizwitsHandle((dataPoint_t *)&currentDataPoint);	
		}
	 
					printf("displayOperation");
					userHandle();
					gizwitsHandle((dataPoint_t *)&currentDataPoint);	
					displayOperation();
	}	 
 }


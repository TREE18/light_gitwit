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
//	unsigned char a[8][3]={{50,5,5},{50,5,5},{50,5,5},{50,5,5},{50,5,5},{50,5,5},{50,5,5},{50,5,5}};	//定义一个二维，每个括号内的三个数据对应一个像素点{G,R,B}
//	unsigned char b[8][3]={{20,220,60},{20,220,60},{20,220,60},{20,220,60},{20,220,60},{20,220,60},{20,220,60},{20,220,60}};
//	unsigned char c[8][3]={{0,255,00},{0,255,00},{0,255,00},{0,255,00},{0,255,00},{0,255,00},{0,255,00},{0,255,00}};
unsigned char s6100[4][3]={{242,255,236},{206,255,159},{185,255,105},{166,255,69}};
unsigned char s4500[1][3]={{206,255,159}};
unsigned char s3000[1][3]={{185,255,105}};	
unsigned char s2500[1][3]={{166,255,69}};
//----------------------------------------------------//									

u8 music01[6]={0xAA, 0x07, 0x02, 0x00, 0x01, 0xB4};	//播放
u8 music02[6]={0xAA, 0x07, 0x02, 0x00, 0x02, 0xB5};	//播放
u8 music03[6]={0xAA, 0x07, 0x02, 0x00, 0x03, 0xB6};	//播放
u8 music04[6]={0xAA, 0x07, 0x02, 0x00, 0x04, 0xB7};	//播放
//----------------------------------------------------//
//JTAG模式设置,用于设置JTAG的模式
//mode:jtag,swd模式设置;00,全使能;01,使能SWD;10,全关闭;	   
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
	TIM3_Int_Init(9,7199);//1MS系统定时
    usart3_init(9600);//WIFI初始化
}
//----------------------------------------------------//
void JTAG_Set(u8 mode)
{
	u32 temp;
	temp=mode;
	temp<<=25;
	RCC->APB2ENR|=1<<0;     //开启辅助时钟	   
	AFIO->MAPR&=0XF8FFFFFF; //清除MAPR的[26:24]
	AFIO->MAPR|=temp;       //设置jtag模式
}
//----------------------------------------------------//
 int main(void)
 {	

	char key=0;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	JTAG_Set(JTAG_SWD_DISABLE);
	JTAG_Set(SWD_ENABLE);
///////////////////////////////////////////////////////////	 

//////////////////////////////////////////////////////////
	uart_init(9600);	 //串口初始化为115200
	USART2_Init(115200);
	usart3_init(115200);		//初始化串口3 
	uart4_init(9600);
//////////////////////////////////////////////////////////
	Gizwits_Init();
	userInit();
    gizwitsInit();
 ///////////////////////////////////////////////////////////	
 	LED_Init();			     //LED端口初始化
	KEY_Init();          //初始化与按键连接的硬件接口
//////////////////////////////////////////////////////////
	SPI2_Init();
//////////////////////////////////////////////////////////	 
    IIC_Init();
	OLED_Init();
//////////////////////////////////////////////////////////

	printf("-----------------------");
  
 	while(1)
	{   
		printf("5s内按wkup进入配置模式\r\n");
		while(link_flag==0)
		{
					key=KEY_Scan(0);	//得到键值
					if(key==WKUP_PRES && link_flag==0)
					{	
						printf("选择 KEY1_PRES-->airlink,KEY0_PRES-->SOFT-link \r\n");
						printf("     WKUP_PRES-->link_resrt,KEY2_PRES-->null \r\n");
						while(1)
						{
							key=KEY_Scan(0);
							switch(key)
							{				 
								case WKUP_PRES:	//控制蜂鸣器
									gizwitsSetMode(WIFI_RESET_MODE);//WIFI复位
									printf("复位");
									break;
								case KEY2_PRES:	//控制LED0翻转
									LED0=!LED0;
									break;
								case KEY1_PRES:	//控制LED1翻转	 
									gizwitsSetMode(WIFI_AIRLINK_MODE);//Air-link模式接入
									printf("Air-link模式接入");
									break;
								case KEY0_PRES:	//同时控制LED0,LED1翻转 
									LED0=!LED0;
									LED1=!LED1;
									gizwitsSetMode(WIFI_SOFTAP_MODE);
									printf("SOFT-link模式接入");				
									break;
							}
							delay_ms(5);
						    userHandle();
							gizwitsHandle((dataPoint_t *)&currentDataPoint);
							
							if(wifi_gizwit==1)break;//当连接成功后退出配置
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


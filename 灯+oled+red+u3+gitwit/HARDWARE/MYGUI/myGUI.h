#ifndef _MYGUI_H_
#define _MYGUI_H_

#include "sys.h"


#define  GUI_NUM 30

extern u8 keyFlag;
extern unsigned char s6100[4][3];
extern unsigned char s4500[1][3];
extern unsigned char s2500[1][3];
extern unsigned char zero[1][3];
//extern unsigned char s6100[16][3];
typedef struct{
	
	u8 curIndex;				// 当前界面索引
	u8 downIndex;				// 向下按键需要跳转的索引
	u8 upIndex;					// 向上按键需要跳转的索引
	u8 enterIndex;			// 确认按键需要跳转的索引
	u8 escIndex;				// 返回按键需要跳转的索引
	void (*function)(); // 当前索引执行函数的入口地址
		
}myGUIIndexTypeDef;

void Fun_menuDisplay(void);
void Fun_homework(void);

//void bootDisplay(void);
void displayOperation(void);
//void displayControl(controlCenterTypeDef *controlp);

void WifiDisplay         (void);          //WIFI
void ElectricityDisplay  (void);          //电量
void FlashlightDisplay   (void);                   //手电筒
#endif












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
	
	u8 curIndex;				// ��ǰ��������
	u8 downIndex;				// ���°�����Ҫ��ת������
	u8 upIndex;					// ���ϰ�����Ҫ��ת������
	u8 enterIndex;			// ȷ�ϰ�����Ҫ��ת������
	u8 escIndex;				// ���ذ�����Ҫ��ת������
	void (*function)(); // ��ǰ����ִ�к�������ڵ�ַ
		
}myGUIIndexTypeDef;

void Fun_menuDisplay(void);
void Fun_homework(void);

//void bootDisplay(void);
void displayOperation(void);
//void displayControl(controlCenterTypeDef *controlp);

void WifiDisplay         (void);          //WIFI
void ElectricityDisplay  (void);          //����
void FlashlightDisplay   (void);                   //�ֵ�Ͳ
#endif












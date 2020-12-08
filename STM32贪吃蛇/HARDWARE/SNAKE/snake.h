#ifndef __SNAKE_H
#define __SNAKE_H

#include "sys.h"
#include "lcd.h"
#include "delay.h"
#include "usart.h"
#include <stdio.h>

#define UP 2
#define DOWN 8
#define LEFT 4
#define RIGHT 6

#define MAP_WIDTH 29
#define MAP_HEIGTH 29

typedef struct
{
	u8 Snake_Head_X;
	u8 Snake_Head_Y;
	u8 Snake_Tail_X;
	u8 Snake_Tail_Y;
	u8 Snake_Length;
	u8 Food_X;
	u8 Food_Y;
	u8 direction;
	u8 cmd_dir;
} snake_t;

extern snake_t snake;

void GUI_Refresh(void);//����ˢ��
void Snake_Play(void);//�����ʼ��
void Create_Map(void);//��ʼ����ͼ�߽�
void Paint_Head(u8 x, u8 y);
void Paint_Body(u8 x, u8 y);//��������
void Paint_Food(u8 x, u8 y);
void Paint_Blank(u8 x, u8 y);
void Snake_Move(void);//�ƶ�
void Snake_Init(void);//�߼�ʳ���ʼ��
void New_Head(u8 t);  //��ͷ��
void GameOver(void);//��Ϸ����
void Create_Food(void);//����ʳ��
void Eat_Food(u8 t);//��ʳ��
void Show(void);//��ʾ


#endif

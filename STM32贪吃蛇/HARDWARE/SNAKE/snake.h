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

void GUI_Refresh(void);//界面刷新
void Snake_Play(void);//界面初始化
void Create_Map(void);//初始化地图边界
void Paint_Head(u8 x, u8 y);
void Paint_Body(u8 x, u8 y);//绘制身体
void Paint_Food(u8 x, u8 y);
void Paint_Blank(u8 x, u8 y);
void Snake_Move(void);//移动
void Snake_Init(void);//蛇及食物初始化
void New_Head(u8 t);  //新头部
void GameOver(void);//游戏结束
void Create_Food(void);//生成食物
void Eat_Food(u8 t);//吃食物
void Show(void);//显示


#endif

#include "snake.h"

int Snake_Map[MAP_WIDTH][MAP_HEIGTH] = {0};
snake_t snake;

void Snake_Play()//界面初始化
{
	Snake_Move();	      //运动
	GUI_Refresh();//界面刷新	
	Show();       //显示长度
}

void Show()//显示
{
	POINT_COLOR = RED;
	LCD_ShowString(8*(MAP_WIDTH+1)+4,8*(MAP_HEIGTH)/2-24,80,24,24,(u8 *)"Score");
	LCD_ShowNum(8*(MAP_WIDTH+1)+24,8*(MAP_HEIGTH+1)/2,snake.Snake_Length-3,2,24);//显示长度
}

void GUI_Refresh()//界面刷新
{
	u8 i,j;
	for(i=0;i<MAP_WIDTH;i++)
	for(j=0;j<MAP_HEIGTH;j++)
	{
		if(Snake_Map[i][j] > 0) Paint_Body(i,j);//绘制
		else if(Snake_Map[i][j] == 0) Paint_Blank(i,j);
	}
	Paint_Head(snake.Snake_Head_X,snake.Snake_Head_Y);//给蛇头填充实心
}

void Snake_Init()//蛇及食物初始化
{ 
	u8 i,j;
	for(i=0;i<MAP_WIDTH;i++)
	for(j=0;j<MAP_HEIGTH;j++)
	Snake_Map[i][j]=0;
	snake.Snake_Length=3;
	snake.direction=RIGHT;//向右 2468
	snake.cmd_dir=RIGHT;
	Snake_Map[7][7]=1;
	Snake_Map[6][7]=2;
	Snake_Map[5][7]=3;
	snake.Snake_Head_X=7;
	snake.Snake_Head_Y=7;
	snake.Snake_Tail_X=5;
	snake.Snake_Tail_X=7;
}

void Create_Map()//初始化地图边界
{
	POINT_COLOR = LIGHTBLUE;
	LCD_DrawRectangle(0,0,8*(MAP_WIDTH+1),8*(MAP_HEIGTH+1));
    LCD_DrawRectangle(1,1,8*(MAP_WIDTH+1)-1,8*(MAP_HEIGTH+1)-1);
	LCD_DrawRectangle(2,2,8*(MAP_WIDTH+1)-2,8*(MAP_HEIGTH+1)-2);
	LCD_DrawRectangle(3,3,8*(MAP_WIDTH+1)-3,8*(MAP_HEIGTH+1)-3);
}

void Create_Food( )//创建食物
{
	do{
		snake.Food_X=rand()%MAP_WIDTH;   //生成随机数
		snake.Food_Y=rand()%MAP_HEIGTH;   //生成随机数
		}
	while(Snake_Map[snake.Food_X][snake.Food_Y]!=0);//直到随机坐标处元素为空白0 避免在蛇上生成
	Snake_Map[snake.Food_X][snake.Food_Y]=-1;//给满足要求的坐标元素赋值食物-1
	Paint_Food(snake.Food_X, snake.Food_Y);
}

void Paint_Head(u8 x,u8 y)//绘制蛇头
{
	u16 i, j;
	POINT_COLOR = BLUE; 
	for(i=8*x+4;i<8*x+12;i++)    
	  for(j=8*y+4;j<8*y+12;j++)
		    LCD_DrawPoint(i,j);
}

void Paint_Body(u8 x,u8 y)//绘制身体
{
	POINT_COLOR = WHITE;
	LCD_DrawRectangle(8*x+6, 8*y+6, 8*x+9, 8*y+9);
	LCD_DrawRectangle(8*x+7, 8*y+7, 8*x+8, 8*y+8);
}

void Paint_Food(u8 x,u8 y)//绘制食物
{
	POINT_COLOR = BRRED;
	LCD_DrawRectangle(8*x+4, 8*y+4, 8*x+11, 8*y+11);
	LCD_DrawRectangle(8*x+5, 8*y+5, 8*x+10, 8*y+10);
}

void Paint_Blank(u8 x, u8 y)//绘制空白
{
	u16 i, j;
	POINT_COLOR = WHITE; 
	for(i=8*x+4;i<8*x+12;i++)    
	  for(j=8*y+4;j<8*y+12;j++)
		    LCD_DrawPoint(i,j);
}

void New_Head(u8 t)  //蛇头下一个位置处理函数
{
	switch(t)
	{
		case UP:
			if(snake.Snake_Head_Y-1<0)//判断是否越过上边界，如果是则在下边界生成蛇头
			{
				Snake_Map[snake.Snake_Head_X][MAP_HEIGTH-1]=1;
				snake.Snake_Head_Y=MAP_HEIGTH-1;
			}
			else
				Snake_Map[snake.Snake_Head_X][--snake.Snake_Head_Y]=1;//给左边下一个坐标的元素赋值1（蛇头）
			break;
			//以下参考UP
		case DOWN:
			if(snake.Snake_Head_Y+1>MAP_HEIGTH-1)
			{
				Snake_Map[snake.Snake_Head_X][0]=1;
				snake.Snake_Head_Y=0;
			}
			else
				Snake_Map[snake.Snake_Head_X][++snake.Snake_Head_Y]=1;		
			break;
			
		case LEFT:
			if(snake.Snake_Head_X-1<0)
			{
				Snake_Map[MAP_WIDTH-1][snake.Snake_Head_Y]=1;
				snake.Snake_Head_X=MAP_WIDTH-1;
			}
			Snake_Map[--snake.Snake_Head_X][snake.Snake_Head_Y]=1;
			break;
			
		case RIGHT:
		if(snake.Snake_Head_X+1>MAP_WIDTH-1)
			{
				Snake_Map[0][snake.Snake_Head_Y]=1;
				snake.Snake_Head_X=0;
			}
			else
				Snake_Map[++snake.Snake_Head_X][snake.Snake_Head_Y]=1;
			break;		
	}
			
}

void Eat_Food(u8 t)    //蛇吃掉食物后的处理函数
{
	switch(t)
	{
		case UP:New_Head(UP);break;
		case DOWN:New_Head(DOWN);break;
		case LEFT:New_Head(LEFT);break;
		case RIGHT:New_Head(RIGHT);break;
	}
	Snake_Map[snake.Snake_Tail_X][snake.Snake_Tail_Y]=snake.Snake_Length+1;		//给蛇尾赋值长度+1，之前去掉了蛇尾
	Create_Food();	//随机生成食物

}

void Game_Over()        //游戏结束处理函数
{
	POINT_COLOR=RED;
	LCD_ShowString(8*(MAP_WIDTH+1)/4,8*(MAP_HEIGTH+1)/2,108,24,24,(u8 *)"GAME OVER");	
	delay_ms(5000);
	LCD_Clear(WHITE);
	Snake_Init();
	Create_Map();//初始化地图边界
	Create_Food();	
}

void Snake_Move()      //蛇身移动处理
{
	u8 i,j;
	for(i=0;i<MAP_WIDTH;i++)
	for(j=0;j<MAP_HEIGTH;j++)
	{
		if(Snake_Map[i][j]>=snake.Snake_Length)//算出蛇尾坐标
		{
			snake.Snake_Length=Snake_Map[i][j];
			snake.Snake_Tail_X=i;
			snake.Snake_Tail_Y=j;
		}
		if(Snake_Map[i][j]==1)//算出蛇头坐标
		{
			snake.Snake_Head_X=i;
			snake.Snake_Head_Y=j;
		}
		if(Snake_Map[i][j]>0)
			Snake_Map[i][j]+=1;//二维遍历SNAKE所有元素，大于0的+1
	}
	Snake_Map[snake.Snake_Tail_X][snake.Snake_Tail_Y]=0;//除去蛇尾

	switch(snake.cmd_dir)//对控制方向进行选择处理
	{ 
	case UP:
		if(Snake_Map[snake.Snake_Head_X][snake.Snake_Head_Y-1]>3)  				//咬到蛇身
			Game_Over();																			//游戏结束
		else if(Snake_Map[snake.Snake_Head_X][snake.Snake_Head_Y-1]==-1)	//吃到食物
			Eat_Food(snake.cmd_dir);
		else if(snake.direction==DOWN)                          //运动方向是下，但是控制方向是上，违背
			New_Head(DOWN);                                 //按照原来的方向移动
		else{                                             //如果不违背则按照控制方向移动，运动方向变更为控制方向
			New_Head(UP);
			snake.direction=UP;
		}
		break;

	case DOWN:
		if(Snake_Map[snake.Snake_Head_X][snake.Snake_Head_Y+1]>3)
			Game_Over();
		else if(Snake_Map[snake.Snake_Head_X][snake.Snake_Head_Y+1]==-1)
			Eat_Food(snake.cmd_dir);
		else if(snake.direction==UP)
			New_Head(UP);
		else {
			New_Head(DOWN);
			snake.direction=DOWN;
		}
		break;

	case LEFT:
		if(Snake_Map[snake.Snake_Head_X-1][snake.Snake_Head_Y]>3)
			Game_Over();
		else if(Snake_Map[snake.Snake_Head_X-1][snake.Snake_Head_Y]==-1)
			Eat_Food(snake.cmd_dir);	
		else if(snake.direction==RIGHT)
			New_Head(RIGHT);	
		else {			
			New_Head(LEFT);
			snake.direction=LEFT;
		}	
		break;

	case RIGHT:
		if(Snake_Map[snake.Snake_Head_X+1][snake.Snake_Head_Y]>3)
			Game_Over();
		else if(Snake_Map[snake.Snake_Head_X+1][snake.Snake_Head_Y]==-1)
			Eat_Food(snake.cmd_dir);
		else if(snake.direction==LEFT)
			New_Head(LEFT);
		else {
			New_Head(RIGHT);
			snake.direction=RIGHT;
		}
		break;
	}	
}

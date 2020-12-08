#include "snake.h"

int Snake_Map[MAP_WIDTH][MAP_HEIGTH] = {0};
snake_t snake;

void Snake_Play()//�����ʼ��
{
	Snake_Move();	      //�˶�
	GUI_Refresh();//����ˢ��	
	Show();       //��ʾ����
}

void Show()//��ʾ
{
	POINT_COLOR = RED;
	LCD_ShowString(8*(MAP_WIDTH+1)+4,8*(MAP_HEIGTH)/2-24,80,24,24,(u8 *)"Score");
	LCD_ShowNum(8*(MAP_WIDTH+1)+24,8*(MAP_HEIGTH+1)/2,snake.Snake_Length-3,2,24);//��ʾ����
}

void GUI_Refresh()//����ˢ��
{
	u8 i,j;
	for(i=0;i<MAP_WIDTH;i++)
	for(j=0;j<MAP_HEIGTH;j++)
	{
		if(Snake_Map[i][j] > 0) Paint_Body(i,j);//����
		else if(Snake_Map[i][j] == 0) Paint_Blank(i,j);
	}
	Paint_Head(snake.Snake_Head_X,snake.Snake_Head_Y);//����ͷ���ʵ��
}

void Snake_Init()//�߼�ʳ���ʼ��
{ 
	u8 i,j;
	for(i=0;i<MAP_WIDTH;i++)
	for(j=0;j<MAP_HEIGTH;j++)
	Snake_Map[i][j]=0;
	snake.Snake_Length=3;
	snake.direction=RIGHT;//���� 2468
	snake.cmd_dir=RIGHT;
	Snake_Map[7][7]=1;
	Snake_Map[6][7]=2;
	Snake_Map[5][7]=3;
	snake.Snake_Head_X=7;
	snake.Snake_Head_Y=7;
	snake.Snake_Tail_X=5;
	snake.Snake_Tail_X=7;
}

void Create_Map()//��ʼ����ͼ�߽�
{
	POINT_COLOR = LIGHTBLUE;
	LCD_DrawRectangle(0,0,8*(MAP_WIDTH+1),8*(MAP_HEIGTH+1));
    LCD_DrawRectangle(1,1,8*(MAP_WIDTH+1)-1,8*(MAP_HEIGTH+1)-1);
	LCD_DrawRectangle(2,2,8*(MAP_WIDTH+1)-2,8*(MAP_HEIGTH+1)-2);
	LCD_DrawRectangle(3,3,8*(MAP_WIDTH+1)-3,8*(MAP_HEIGTH+1)-3);
}

void Create_Food( )//����ʳ��
{
	do{
		snake.Food_X=rand()%MAP_WIDTH;   //���������
		snake.Food_Y=rand()%MAP_HEIGTH;   //���������
		}
	while(Snake_Map[snake.Food_X][snake.Food_Y]!=0);//ֱ��������괦Ԫ��Ϊ�հ�0 ��������������
	Snake_Map[snake.Food_X][snake.Food_Y]=-1;//������Ҫ�������Ԫ�ظ�ֵʳ��-1
	Paint_Food(snake.Food_X, snake.Food_Y);
}

void Paint_Head(u8 x,u8 y)//������ͷ
{
	u16 i, j;
	POINT_COLOR = BLUE; 
	for(i=8*x+4;i<8*x+12;i++)    
	  for(j=8*y+4;j<8*y+12;j++)
		    LCD_DrawPoint(i,j);
}

void Paint_Body(u8 x,u8 y)//��������
{
	POINT_COLOR = WHITE;
	LCD_DrawRectangle(8*x+6, 8*y+6, 8*x+9, 8*y+9);
	LCD_DrawRectangle(8*x+7, 8*y+7, 8*x+8, 8*y+8);
}

void Paint_Food(u8 x,u8 y)//����ʳ��
{
	POINT_COLOR = BRRED;
	LCD_DrawRectangle(8*x+4, 8*y+4, 8*x+11, 8*y+11);
	LCD_DrawRectangle(8*x+5, 8*y+5, 8*x+10, 8*y+10);
}

void Paint_Blank(u8 x, u8 y)//���ƿհ�
{
	u16 i, j;
	POINT_COLOR = WHITE; 
	for(i=8*x+4;i<8*x+12;i++)    
	  for(j=8*y+4;j<8*y+12;j++)
		    LCD_DrawPoint(i,j);
}

void New_Head(u8 t)  //��ͷ��һ��λ�ô�����
{
	switch(t)
	{
		case UP:
			if(snake.Snake_Head_Y-1<0)//�ж��Ƿ�Խ���ϱ߽磬����������±߽�������ͷ
			{
				Snake_Map[snake.Snake_Head_X][MAP_HEIGTH-1]=1;
				snake.Snake_Head_Y=MAP_HEIGTH-1;
			}
			else
				Snake_Map[snake.Snake_Head_X][--snake.Snake_Head_Y]=1;//�������һ�������Ԫ�ظ�ֵ1����ͷ��
			break;
			//���²ο�UP
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

void Eat_Food(u8 t)    //�߳Ե�ʳ���Ĵ�����
{
	switch(t)
	{
		case UP:New_Head(UP);break;
		case DOWN:New_Head(DOWN);break;
		case LEFT:New_Head(LEFT);break;
		case RIGHT:New_Head(RIGHT);break;
	}
	Snake_Map[snake.Snake_Tail_X][snake.Snake_Tail_Y]=snake.Snake_Length+1;		//����β��ֵ����+1��֮ǰȥ������β
	Create_Food();	//�������ʳ��

}

void Game_Over()        //��Ϸ����������
{
	POINT_COLOR=RED;
	LCD_ShowString(8*(MAP_WIDTH+1)/4,8*(MAP_HEIGTH+1)/2,108,24,24,(u8 *)"GAME OVER");	
	delay_ms(5000);
	LCD_Clear(WHITE);
	Snake_Init();
	Create_Map();//��ʼ����ͼ�߽�
	Create_Food();	
}

void Snake_Move()      //�����ƶ�����
{
	u8 i,j;
	for(i=0;i<MAP_WIDTH;i++)
	for(j=0;j<MAP_HEIGTH;j++)
	{
		if(Snake_Map[i][j]>=snake.Snake_Length)//�����β����
		{
			snake.Snake_Length=Snake_Map[i][j];
			snake.Snake_Tail_X=i;
			snake.Snake_Tail_Y=j;
		}
		if(Snake_Map[i][j]==1)//�����ͷ����
		{
			snake.Snake_Head_X=i;
			snake.Snake_Head_Y=j;
		}
		if(Snake_Map[i][j]>0)
			Snake_Map[i][j]+=1;//��ά����SNAKE����Ԫ�أ�����0��+1
	}
	Snake_Map[snake.Snake_Tail_X][snake.Snake_Tail_Y]=0;//��ȥ��β

	switch(snake.cmd_dir)//�Կ��Ʒ������ѡ����
	{ 
	case UP:
		if(Snake_Map[snake.Snake_Head_X][snake.Snake_Head_Y-1]>3)  				//ҧ������
			Game_Over();																			//��Ϸ����
		else if(Snake_Map[snake.Snake_Head_X][snake.Snake_Head_Y-1]==-1)	//�Ե�ʳ��
			Eat_Food(snake.cmd_dir);
		else if(snake.direction==DOWN)                          //�˶��������£����ǿ��Ʒ������ϣ�Υ��
			New_Head(DOWN);                                 //����ԭ���ķ����ƶ�
		else{                                             //�����Υ�����տ��Ʒ����ƶ����˶�������Ϊ���Ʒ���
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

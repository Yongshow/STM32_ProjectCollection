#include "main.h"


int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	uart_init(115200);  	//���ڳ�ʼ��
	delay_init();	    	//��ʱ������ʼ��	  
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	DHT11_Init();       	//��ʪ�ȴ�������ʼ��
	DS1302_Init();      	//ʵʱʱ�ӳ�ʼ��
	OLED_Init();        	//OLED��ʼ��
	while(DS18B20_Init());	//�¶ȴ�������ʼ��
	LCD_Init();          	//LCD��ʼ��
	LCD_Display_Dir(1);  	//����LCD��ʾ����
	LCD_Clear(WHITE);    	//LCD����
	Snake_Init();        	//̰���߳�ʼ��
	
	 
	 //������ʼ����
	 xTaskCreate((TaskFunction_t )start_task, //������
				 (const char* )"start_task", //��������
				 (uint16_t )START_STK_SIZE, //�����ջ��С
				 (void* )NULL, //���ݸ��������Ĳ���
				 (UBaseType_t )START_TASK_PRIO, //�������ȼ�
				 (TaskHandle_t* )&StartTask_Handler); //������
	 vTaskStartScheduler();             //�����������
}

 void start_task(void *p_arg)
{
	taskENTER_CRITICAL(); //�����ٽ���
	//���� LED ����
	xTaskCreate(led0_task, "led0 task", LED0_STK_SIZE, NULL, LED0_TASK_PRIO, &LED0Task_Handler);
    //����ʱ���¶���ʾ����
	xTaskCreate(display_task, "display task", DISP_STK_SIZE, NULL, DISP_TASK_PRIO, &DispTask_Handler);
	//����̰��������
	xTaskCreate(snake_task, "snake task", SNAKE_STK_SIZE, NULL, SNAKE_TASK_PRIO, &SnakeTask_Handler);
	//��������ͨѶ����
	xTaskCreate(bluetooth_task, "bluetooth task", BT_STK_SIZE, NULL, BT_TASK_PRIO, &BTTask_Handler);
	vTaskDelete(StartTask_Handler); //ɾ����ʼ����
	taskEXIT_CRITICAL(); //�˳��ٽ���
}

//LED �����������ڼ��ϵͳ�Ƿ���������
void led0_task(void *p_arg)
{
	for(;;)
	{
		LED0=!LED0;
		LED1=!LED1;
		delay_ms(500);
	}
}

//OLED��ʾ����ʵʱ��ʾ��ǰʱ�����ʪ��
void display_task(void *p_arg)
{
	TimeData time;
	dht_data data;
	char data_array[4][20] = {0};
	for(;;)
	{
		time = DS1302_ReadTime();
		data = DHT11_GetData();
		sprintf(data_array[0], "%d-%d%d-%d%d",time.Year,
				time.Month / 10, time.Month % 10, time.Day / 10, time.Day % 10);
		sprintf(data_array[1], "%d%d:%d%d:%d%d",time.Hour / 10, time.Hour % 10,
				time.Minute / 10, time.Minute % 10, time.Second / 10, time.Second % 10);
		sprintf(data_array[2], "temper == %d.%d C",data.temp_int, data.temp_dec);
		sprintf(data_array[3], "humidi == %d.%dRH",data.hum_int, data.hum_dec);
		OLED_ShowString(0, 0, (u8 *)data_array[0], 16);
		OLED_ShowString(32, 2, (u8 *)data_array[1], 16);
		OLED_ShowString(0, 4, (u8 *)data_array[2], 16);
		OLED_ShowString(0, 6, (u8 *)data_array[3], 16);
		switch(time.Week)
		{
//			case 0:
//				OLED_ShowString(90, 0, (u8 *)"Sun", 16);
//				break;
			case 1:
				OLED_ShowString(90, 0, (u8 *)"Mon", 16);
				break;
			case 2:
				OLED_ShowString(90, 0, (u8 *)"Tue", 16);
				break;
			case 3:
				OLED_ShowString(90, 0, (u8 *)"Wed", 16);
				break;
			case 4:
				OLED_ShowString(90, 0, (u8 *)"Thu", 16);
				break;
			case 5:
				OLED_ShowString(90, 0, (u8 *)"Fri", 16);
				break;
			case 6:
				OLED_ShowString(90, 0, (u8 *)"Sat", 16);
				break;  
			case 7:
				OLED_ShowString(90, 0, (u8 *)"Sun", 16);
				break;
		}
		delay_ms(1000);
	}
}

//̰��������
void snake_task(void *p_arg)
{
	short delay, temp = 0;
	Create_Map();      //������ͼ
	Create_Food();     //����ʳ��
	for(;;)
	{
		temp = DS18B20_Get_Temp();
		if(temp <= 200 || temp >= 340) delay = 500;
		else delay = 500-3*(temp-200);
		Snake_Play();  //̰����������
		delay_ms(delay);
	}
}

//����ͨѶ�������ڽ��ա������ֻ��˷��͵�ָ����Ϣ
void bluetooth_task(void *p_arg)
{
	u16 t;  
	u16 len;
	u8 updata = 0;
	char command[20] = {0};
	for(;;)
	{
		if(USART_RX_STA&0x8000)
		{
			updata = 1;
			len = USART_RX_STA & 0x3FFF;
			for(t = 0; t < len; t++)
			command[t] = (char)USART_RX_BUF[t];
			USART_RX_STA=0;
		} else updata = 0;
		
		if(updata && strcmp(command, "up") == 0) snake.cmd_dir = UP;
		else if(updata && strcmp(command, "down") == 0) snake.cmd_dir = DOWN;
		else if(updata && strcmp(command, "left") == 0) snake.cmd_dir = LEFT;
		else if(updata && strcmp(command, "right") == 0) snake.cmd_dir = RIGHT;
		
		if(updata) memset(command, 0, len);
		delay_ms(100);
	}
}


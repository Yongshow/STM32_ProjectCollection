#ifndef __MAIN_H
#define __MAIN_H

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"
#include "oled.h"
#include "lcd.h"
#include "dht11.h"
#include "ds1302.h"
#include "ds18b20.h"
#include "snake.h"
#include <string.h>

#define START_TASK_PRIO 1 //�������ȼ�
#define START_STK_SIZE 128 //�����ջ��С
TaskHandle_t StartTask_Handler; //������
void start_task(void *p_arg); //������

#define LED0_TASK_PRIO 2 //�������ȼ�
#define LED0_STK_SIZE 128 //�����ջ��С
TaskHandle_t LED0Task_Handler; //������
void led0_task(void *p_arg); //������

#define DISP_TASK_PRIO 3 //�������ȼ�
#define DISP_STK_SIZE 256 //�����ջ��С
TaskHandle_t DispTask_Handler; //������
void display_task(void *p_arg); //������

#define SNAKE_TASK_PRIO 4 //�������ȼ�
#define SNAKE_STK_SIZE 512 //�����ջ��С
TaskHandle_t SnakeTask_Handler; //������
void snake_task(void *p_arg); //������

#define BT_TASK_PRIO 5 //�������ȼ�
#define BT_STK_SIZE 128 //�����ջ��С
TaskHandle_t BTTask_Handler; //������
void bluetooth_task(void *p_arg); //������

#endif

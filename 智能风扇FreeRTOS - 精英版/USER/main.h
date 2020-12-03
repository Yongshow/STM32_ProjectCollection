#ifndef __MAIN_H
#define __MAIN_H

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"
#include "oled.h"
#include "ds18b20.h"
#include "timer.h"
#include "rtc.h"
#include <string.h>

#define START_TASK_PRIO 1 //任务优先级
#define START_STK_SIZE 128 //任务堆栈大小
TaskHandle_t StartTask_Handler; //任务句柄
void start_task(void *p_arg); //任务函数

#define LED0_TASK_PRIO 2 //任务优先级
#define LED0_STK_SIZE 128 //任务堆栈大小
TaskHandle_t LED0Task_Handler; //任务句柄
void led0_task(void *p_arg); //任务函数

#define DISP_TASK_PRIO 3 //任务优先级
#define DISP_STK_SIZE 256 //任务堆栈大小
TaskHandle_t DispTask_Handler; //任务句柄
void display_task(void *p_arg); //任务函数

#define SPEED_TASK_PRIO 4 //任务优先级
#define SPEED_STK_SIZE 128 //任务堆栈大小
TaskHandle_t SpeedTask_Handler; //任务句柄
void speed_task(void *p_arg); //任务函数

#define BT_TASK_PRIO 5 //任务优先级
#define BT_STK_SIZE 128 //任务堆栈大小
TaskHandle_t BTTask_Handler; //任务句柄
void bluetooth_task(void *p_arg); //任务函数

#endif

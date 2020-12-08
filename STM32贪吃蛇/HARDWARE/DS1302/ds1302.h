#ifndef __DS1302_H
#define __DS1302_H

#include "sys.h"
#include "delay.h"


//CLK引脚定义
#define DS1302_CLK_Port GPIOA
#define DS1302_CLK_Pin GPIO_Pin_7
#define DS1302_CLK_RCC RCC_APB2Periph_GPIOA

//DAT引脚定义
#define DS1302_DAT_Port GPIOA
#define DS1302_DAT_Pin GPIO_Pin_6
#define DS1302_DAT_RCC RCC_APB2Periph_GPIOA

//RST引脚定义
#define DS1302_RST_Port GPIOA
#define DS1302_RST_Pin GPIO_Pin_5
#define DS1302_RST_RCC RCC_APB2Periph_GPIOA

//DAT模式
#define DS1302_IO_IN() {GPIOA->CRL &= 0xF0FFFFFF; GPIOA->CRL |= 0x8 << 24;}
#define DS1302_IO_OUT() {GPIOA->CRL &= 0xF0FFFFFF; GPIOA->CRL |= 0x3 << 24;}

#define DS1302_IN PAin(6)
#define DS1302_OUT PAout(6)
#define DS1302_RST PAout(5)
#define DS1302_CLK PAout(7)

//DS1302地址定义
#define DS1302_SEC_ADDR           0x80		//秒数据地址
#define DS1302_MIN_ADDR           0x82		//分数据地址
#define DS1302_HOUR_ADDR          0x84		//时数据地址
#define DS1302_DAY_ADDR           0x86		//日数据地址
#define DS1302_MONTH_ADDR         0x88		//月数据地址
#define DS1302_WEEK_ADDR          0x8a		//星期数据地址
#define DS1302_YEAR_ADDR          0x8c		//年数据地址
#define DS1302_CONTROL_ADDR       0x8e		//控制数据地址
#define DS1302_CHARGER_ADDR       0x90 		//充电功能地址			 
#define DS1302_CLKBURST_ADDR      0xbe
#define DS1302_FIRST_REG		  0xc0

//时间结构体定义
typedef struct
{
	u16 Year;
	u8 Month;
	u8 Day;
	u8 Hour;
	u8 Minute;
	u8 Second;
	u8 Week;
} TimeData;

//函数列表
void DS1302_Init(void);
void DS1302_WriteTime(TimeData* time);
TimeData DS1302_ReadTime(void);

#endif

#ifndef __I2C_MASTER_H
#define __I2C_MASTER_H

#include "sys.h"
#include "delay.h"

//SDA、SCL引脚定义
#define RCC_SCL RCC_APB2Periph_GPIOB
#define SCL_GPIO_Port GPIOB
#define SCL_GPIO_Pin GPIO_Pin_11

#define RCC_SDA RCC_APB2Periph_GPIOB
#define SDA_GPIO_Port GPIOB
#define SDA_GPIO_Pin GPIO_Pin_10

//IO方向设置
#define SDA_IN() {GPIOB->CRH &= 0xFFFFF0FF; GPIOB->CRH |= (u32)8 << 8;}
#define SDA_OUT() {GPIOB->CRH &= 0xFFFFF0FF; GPIOB->CRH |= (u32)3 << 8;}

//IO操作函数
#define IIC_SCL PBout(11)
#define IIC_SDA PBout(10)
#define READ_SDA PBin(10)

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(u8 ack);           //IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

#endif


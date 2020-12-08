#include "i2c_master.h"


//初始化IIC
void IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_SCL | RCC_SDA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = SCL_GPIO_Pin | SDA_GPIO_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SCL_GPIO_Port, &GPIO_InitStructure);
    GPIO_Init(SDA_GPIO_Port, &GPIO_InitStructure);

    GPIO_SetBits(SCL_GPIO_Port, SCL_GPIO_Pin);
    GPIO_SetBits(SDA_GPIO_Port, SDA_GPIO_Pin);
}

//产生IIC起始信号
void IIC_Start(void)
{
    SDA_OUT();
    IIC_SDA = 1;
    IIC_SCL = 1;
    delay_us(4);
    IIC_SDA = 0;
    delay_us(4);
    IIC_SCL = 0;
}

//产生IIC停止信号
void IIC_Stop(void)
{
    SDA_OUT();
    IIC_SCL = 0;
    IIC_SDA = 0;
    delay_us(4);
    IIC_SCL = 1;
    IIC_SDA = 1;
    delay_us(4);
}

//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
    u8 ucErrTime = 0;
    SDA_IN();
    IIC_SDA = 1;
    delay_us(1);
    IIC_SCL = 1;
    delay_us(1);
    while(READ_SDA)
    {
        ucErrTime++;
        if(ucErrTime > 250)
        {
            IIC_Stop();
            return 1;
        }
    }
    IIC_SCL = 0;
    return 0;
}

//产生ACK应答
void IIC_Ack(void)
{
    IIC_SCL = 0;
    SDA_OUT();
    IIC_SDA = 0;
    delay_us(2);
    IIC_SCL = 1;
    delay_us(2);
    IIC_SCL = 0;
}

//不产生ACK应答
void IIC_NAck(void)
{
    IIC_SCL = 0;
    SDA_OUT();
    IIC_SDA = 1;
    delay_us(2);
    IIC_SCL = 1;
    delay_us(2);
    IIC_SCL = 0;
}

//IIC发送一个字节
void IIC_Send_Byte(u8 txd)
{
    u8 t;
    SDA_OUT();
    IIC_SCL = 0;
    for(t = 0; t < 8; t++)
    {
        IIC_SDA = (txd & 0x80) >> 7;
        txd <<= 1;
        delay_us(2);
        IIC_SCL = 1;
        delay_us(2);
        IIC_SCL = 0;
        delay_us(2);
    }
}

//读1个字节，ack=1时，发送ACK，ack=0，发送nACK 
u8 IIC_Read_Byte(u8 ack)
{
    u8 i, receive = 0;
    SDA_IN();
    for(i = 0; i < 8; i++)
    {
        IIC_SCL = 0;
        delay_us(2);
        IIC_SCL = 1;
        receive <<= 1;
        if(READ_SDA) receive++;
        delay_us(1);
    }
    if(ack) IIC_Ack();
    else IIC_NAck();
    return receive;
}

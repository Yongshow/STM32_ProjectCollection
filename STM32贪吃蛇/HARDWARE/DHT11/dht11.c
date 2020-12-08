#include "dht11.h"


//IO口初始化
void DHT11_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(DHT_RCC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = DHT_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DHT_Port, &GPIO_InitStructure);
	
	GPIO_SetBits(DHT_Port, DHT_Pin);
}

//DHT11模块复位
void dht11_reset(void)
{
	DHT_IO_OUT();
	DHT_DATA_OUT = 0;
	delay_xms(20);
	DHT_DATA_OUT = 1;
	delay_us(13);
	DHT_IO_IN();
}

//读取一位数据
u8 dht11_read_bit(void)
{
	while(DHT_DATA_IN == RESET);
	delay_us(40);
	if(DHT_DATA_IN == SET)
	{
		while(DHT_DATA_IN == SET);
		return 1;
	}
	else return 0;
}

//读取一字节数据
u8 dht11_read_byte(void)
{
	u8 i;
	u8 data = 0;
	for(i = 0; i < 8; i++)
	{
		data <<= 1;
		data |= dht11_read_bit();
	}
	return data;
}

u8 buffer[5]; //数据缓存空间

//获取DHT11数据
u8 dht11_read_data(void)
{
	u8 i;
	u8 checksum;
	dht11_reset();
	if(DHT_DATA_IN == RESET)
	{
		while(DHT_DATA_IN == RESET);
		while(DHT_DATA_IN == SET);
		for(i = 0; i < 5; i++)
		{
			buffer[i] = dht11_read_byte();
		}
		
		while(DHT_DATA_IN == RESET);
		DHT_IO_OUT();
		DHT_DATA_OUT = 1;
		
		checksum = buffer[0] + buffer[1] + buffer[2] + buffer[3];
		if(checksum != buffer[4]) return 1;
	}
	return 0;
}

//返回DHT11数据结构体
dht_data DHT11_GetData(void)
{
	dht_data data;
	if(dht11_read_data() == 0)
	{
		data.hum_int = buffer[0];
		data.hum_dec = buffer[1];
		data.temp_int = buffer[2];
		data.temp_dec = buffer[3];
	}
	return data;
}

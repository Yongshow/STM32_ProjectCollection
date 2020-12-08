#ifndef __DHT11_H
#define __DHT11_H

#include "sys.h"
#include "delay.h"


#define DHT_Port GPIOB
#define DHT_Pin GPIO_Pin_1
#define DHT_RCC RCC_APB2Periph_GPIOB

#define DHT_IO_OUT() {GPIOB->CRL &= 0XFFFFFF0F; GPIOB->CRL |= 0x30;}
#define DHT_IO_IN() {GPIOB->CRL &= 0XFFFFFFF0F; GPIOB->CRL |= 0x40;}

#define DHT_DATA_OUT PBout(1)
#define DHT_DATA_IN PBin(1)

typedef struct
{
	u8 temp_int;      // �¶���������
	u8 temp_dec;      // �¶�С������
	u8 hum_int;       // ʪ����������
	u8 hum_dec;       // ʪ��С������
} dht_data;

void DHT11_Init(void);
dht_data DHT11_GetData(void);

#endif

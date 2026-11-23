#ifndef __GET_AO_H
#define __GET_AO_H



#include "main.h"
#include "adc.h"

#define adc_in_num 5
#define adc_num &hadc1

#define ADC_FIRE_THRESHOLD 3000		// 火焰检测阈值 (注意：逻辑上取最小值时，阈值的含义可能需要你重新确认)

extern uint32_t adc_value[adc_in_num];

void get_adc_vaule(void);

void OLED_Show_ADC_Value(void);

uint8_t check_fire_min(void);

uint8_t Get_MQ2_value(void);



#endif




#include "led.h"
#include "stdlib.h"

void led_set_level(pLED_Class pthis, const int led_n, const led_bit led_level);
void led_set_level_arr(pLED_Class pthis, const led_bits led_sta);

pLED_Class createLedClass(void)
{
	pLED_Class Led_c = (pLED_Class)malloc(sizeof(LED_Class));
	
	if(Led_c == NULL)
	{
		return NULL;
	}
	
	Led_c->led_amount = 0;
	Led_c->led_curent_level = (led_bits)0;
	
	Led_c->set_level = led_set_level;
	Led_c->set_level_arr = led_set_level_arr;
	
	Led_c->set_level_arr(Led_c, (led_bits)0);
	return Led_c;
}

pLED_Class createLedClassWtihArgs(int led_amount)
{
	pLED_Class Led_c = createLedClass();
	if(Led_c == NULL)
	{
		return NULL;
	}
	Led_c->led_amount = led_amount;
	return Led_c;
}

void led_set_level(pLED_Class pthis, const int led_n, const led_bit led_level)
{
	led_out_gpio((uint8_t)led_level, led_n);
	
	pthis->led_curent_level &= ~(0x01 << led_n);
	pthis->led_curent_level |= ~(led_level << led_n);
}

void led_set_level_arr(pLED_Class pthis, const led_bits led_sta)
{
	for(int i = 0; i < pthis->led_amount; i++)
	{
		led_out_gpio((uint8_t)(led_sta >> i) & 0x01, i);
	}
	pthis->led_curent_level = led_sta;
}


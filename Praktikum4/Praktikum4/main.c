/*
 * Praktikum4.c
 *
 * Created: 09.12.2023 16:35:58
 * Author : Tito1502
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <util/delay.h>

#include "dateien/keys.h"
#include "dateien/sevenseg.h"


int main(void)
{
	keys_init();
	sevenseg_init();
	
	sei();
	
	
    /* Replace with your application code */
    while (1) 
    {
		
		update_display();
		_delay_ms(18);
    }
}


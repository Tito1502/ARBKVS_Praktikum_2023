/*
 * Praktikum2.c
 *
 * Created: 12.11.2023 21:45:15
 * Author : Tito1502
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL#include<util/delay.h>volatile uint8_t state = 0;ISR(PCINT1_vect) {
	if (!(PINC & (1 << PINC5))) {
		if (state == 0 || state == 3 || state == 4) 
		{
			state = 2;
		}
		else if (state == 2 || state == 5)
		{
			PORTD &= ~(1 << PIND1);  // Ausschalten von LED D9
			state = 3;
		}
	}			
	if (!(PINC & (1 << PINC4))) {
		if (state == 0 || state == 5 || state == 2)
		{
			state = 4;
		}
		else if (state == 4 || state == 3)
		{
			PORTD &= ~(1 << PIND0);  // Ausschalten von LED D0
			state = 5;
		}
	}}void performStateAction() {
	switch (state) {
		case 0:
		PORTD &= ~((1 << PIND0) | (1 << PIND1));  // Beide LEDs aus
		break;
		case 2:
		PORTD |= (1 << PIND0);  // LED D0 eingeschaltet
		PORTD &= ~(1 << PIND1);
		break;
		case 3:
		PORTD ^= (1 << PIND0);  // LED D0 blinkt
		_delay_ms(500);  // Blinkzeit 500 ms
		break;
		case 4:
		PORTD |= (1 << PIND1);  // LED D9 eingeschaltet
		PORTD &= ~(1 << PIND0);
		break;
		case 5:
		PORTD ^= (1 << PIND1);  // LED D9 blinkt
		_delay_ms(500);  // Blinkzeit 500 ms
		break;
		default:
		break;
	}
}

void init() {
	// Konfiguration der Ports
	DDRD |= (1 << PIND0) | (1 << PIND1);
	PORTC |= (1 << PINC5) | (1 << PINC4);
	
	// Konfiguration der Pin Change Interrupts für PC4 und PC5
	PCICR |= (1 << PCIE1);  // Aktiviere Pin Change Interrupts für Gruppe 1 (PCINT8 bis PCINT14)
	PCMSK1 |= (1 << PCINT12) | (1 << PCINT13);  // Aktiviere PCINT12 (PC4) und PCINT13 (PC5)
}

int main(void)
{
	init();
	
	sei();
	
    while (1) 
    {
		performStateAction();
    }
}


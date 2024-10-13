/*
 * Praktikum2_Polling.c
 *
 * Created: 13.11.2023 16:54:24
 * Author : Tito1502
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

volatile uint8_t state = 0;

// Funktion zum Abfragen der Schalterzustände
void pollSwitches() {
	// Schalter SW1 (PINC4)
	if (!(PINC & (1 << PINC4))) {
		if (state == 0 || state == 5 || state == 2) 
		{
			state = 4;
		} else if (state == 4 || state == 3) 
		{
			PORTD &= ~(1 << PIND0);  // Ausschalten von LED D0
			state = 5;
		}
		_delay_ms(400);  // Kurze Verzögerung zwischen den Abfragen
	}
		

	// Schalter SW2 (PINC5)

	if (!(PINC & (1 << PINC5))) {
		if (state == 0 || state == 3 || state == 4) 
		{
			state = 2;
		} else if (state == 2 || state == 5) 
		{
			PORTD &= ~(1 << PIND1);  // Ausschalten von LED D9
			state = 3;
		}
		_delay_ms(400);  // Kurze Verzögerung zwischen den Abfragen
	}

}

void performStateAction() {
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
		_delay_ms(200);  // Blinkzeit 500 ms
		break;
		case 4:
		PORTD |= (1 << PIND1);  // LED D9 eingeschaltet
		PORTD &= ~(1 << PIND0);
		break;
		case 5:
		PORTD ^= (1 << PIND1);  // LED D9 blinkt
		_delay_ms(200);  // Blinkzeit 500 ms
		break;
		default:
		break;
	}
}

void init() {
	// Konfiguration der Ports
	DDRD |= (1 << PIND0) | (1 << PIND1);
	PORTC |= (1 << PINC5) | (1 << PINC4);
}

int main(void) {
	init();

	while (1) {
		pollSwitches();  // Abfrage der Schalterzustände
		performStateAction();
	}

	return 0;
}



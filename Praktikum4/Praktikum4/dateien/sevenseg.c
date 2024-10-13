/*
 * sevenseg.c
 *
 * Created: 09.12.2023 16:40:47
 *  Author: Tito1502
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <util/delay.h>
#include "sevenseg.h"

#define SEG_A (1 << PIND0)
#define SEG_B (1 << PIND1)
#define SEG_C (1 << PIND2)
#define SEG_D (1 << PIND3)
#define SEG_E (1 << PIND4)
#define SEG_F (1 << PIND5)
#define SEG_G (1 << PIND6)

// Definition der Zehnerstelle (active-Low)
#define TEN_DIGIT (1 << PINB0)

// Definition der Ziffern für die Sieben-Segment-Anzeige
const uint8_t digits[10] = {
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,           // 0
	SEG_B | SEG_C,                                           // 1
	SEG_A | SEG_B | SEG_G | SEG_E | SEG_D,                   // 2
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_G,                   // 3
	SEG_B | SEG_C | SEG_F | SEG_G,                           // 4
	SEG_A | SEG_F | SEG_G | SEG_C | SEG_D,                   // 5
	SEG_A | SEG_F | SEG_E | SEG_D | SEG_C | SEG_G,           // 6
	SEG_A | SEG_B | SEG_C,                                   // 7
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,   // 8
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G            // 9
};


volatile uint8_t counter = 0;

void sevenseg_init() {
	// Konfiguration der Segmente als Ausgänge
	DDRD |= (1 << PIND0) | (1 << PIND1) | (1 << PIND2) | (1 << PIND3) | (1 << PIND4) | (1 << PIND5) | (1 << PIND6);

	// Konfiguration der Zehnerstelle als Ausgang
	DDRB |= (1 << PINB0);
}

void update_display() {
	// Ziffern auf der Sieben-Segment-Anzeige darstellen
	int tens = counter / 10;
	int ones = counter % 10;

	display_digit(tens, 0);
	display_digit(ones, 1);
}

void display_digit(int digit, int is_tens) {
	
	
	// Anzeige der Ziffer auf der Sieben-Segment-Anzeige
	if (is_tens) 
	{
		//PORTB = 0x00;
		PORTB &= ~TEN_DIGIT; // Zehnerstelle aktivieren (active-Low)
	} else {
		PORTB |= TEN_DIGIT; // Einerstelle aktivieren (active-Low)
	}

	PORTD = ~digits[digit]; // Segmente entsprechend der Ziffer aktivieren (active-Low)

	// Kurze Verzögerung für die Anzeige (kann je nach Plattform angepasst werden)
	_delay_ms(2);             
}

void count_up() {
	// Inkrementiere den Zähler
	counter++;

	// Überlauf überprüfen
	if (counter > 99) {
		counter = 0;
	}
}

void count_down() {
	// Dekrementiere den Zähler
	counter--;

	// Überlauf überprüfen
	if (counter > 99) {
		counter = 99;
	}
}

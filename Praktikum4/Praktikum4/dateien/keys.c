/*
 * keys.c
 *
 * Created: 09.12.2023 16:41:14
 *  Author: Tito1502
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <util/delay.h>
#include "keys.h"
#include "sevenseg.h"

void keys_init() {
	PORTC |= (1 << PINC5) | (1 << PINC4);
	
	// Konfiguration der Pin Change Interrupts für PC4 und PC5
	PCICR |= (1 << PCIE1);  // Aktiviere Pin Change Interrupts für Gruppe 1 (PCINT8 bis PCINT14)
	PCMSK1 |= (1 << PCINT12) | (1 << PCINT13);  // Aktiviere PCINT12 (PC4) und PCINT13 (PC5)
}

ISR(PCINT1_vect) {
	if (!(PINC & (1 << PINC5))) {
		count_up();
	}			
	if (!(PINC & (1 << PINC4))) {
		count_down();
	}}
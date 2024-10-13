/*
 * Praktrikum3.c
 *
 * Created: 27.11.2023 17:54:10
 * Author : Tito1502
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint32_t systemClock = 0; // systemClock bleibt erhalten wegen volatile => Cache bleibt erhalten, jede Zeit zugreifbar

#define LED_ON(PORT,LED) PORT |= (1 << LED)
#define LED_OFF(PORT,LED) PORT &= ~(1 << LED)
#define LED_TOGGEL(PORT,LED) PORT ^= (1 << LED)
#define LED1 0
#define LED2 1


void init()
{
	DDRD |= (1 << LED1) | (1 << LED2);
	
	TCCR0B |= (1 << CS02) | (1 << CS00); //1024 prescaler
	
	TCCR0A |= (1 << WGM01); // ctc (Clear Timer on Compare Match) on stellen
	
	TIMSK0 |= (1 << OCIE0A); // aktiviere compare interrupt match a
	OCR0A = 15; //Zahl mit der man vergleicht um einen Interrupt zu starten
}
void waitFor(uint32_t ms)
{
	volatile uint32_t count_until = systemClock + ms;
	while (systemClock < count_until)
	{
		;
	}
}
void waitUntil(uint32_t ms)
{
	while(systemClock != ms)
	{
		;
	}
}
int main(void)
{
	init();
	
	sei();
	
	LED_ON(PORTD,LED2);
	waitUntil(3000);
	LED_OFF(PORTD,LED2);
	waitUntil(5000);


	while (1)
	{
		LED_TOGGEL(PORTD,LED1);
		LED_TOGGEL(PORTD, LED2);
		waitFor(100);
		
	}
}

ISR(TIMER0_COMPA_vect)
{
	systemClock++;
}
/*
 * sevenseg.h
 *
 * Created: 09.12.2023 16:40:54
 *  Author: Tito1502
 */ 


#ifndef SEVENSEG_H_
#define SEVENSEG_H_


// Initialisierung der Sieben-Segment-Anzeige
void sevenseg_init();

// Darstellung einer Ziffer auf der Sieben-Segment-Anzeige
void display_digit(int digit, int is_tens);

// Aufwärts zählen von 00 bis 99
void count_up();

// Abwärts zählen von 99 bis 00
void count_down();

void update_display();


#endif /* SEVENSEG_H_ */
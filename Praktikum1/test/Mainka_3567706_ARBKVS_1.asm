;
; Mainka_3567706_ARBKVS_1.asm
;
; Created: 13.10.2023 13:53:24
; Author : Tito1502
;
.include "m328pdef.inc"	; Prozessordefinitionen laden
.CSEG


.org 0x000		; Reset Vector
	rjmp start


start:
	; Stack Pointer initialisieren
	ldi r16, LOW( RAMEND )
	out SPL, r16
	ldi r16, HIGH( RAMEND )
	out SPH, r16

	;PB5 als Output
	ldi r16,0xff
	out DDRD, r16
	out DDRB, r16
	
main:
	; Laufrichtung nach rechts und links aufrufen
	rcall right_to_left
	rcall left_to_right

	rjmp main		;Ruecksprung

delay:
	; Assembly code auto-generated
; by utility from Bret Mulvey
; Delay 3 199 996 cycles
; 199ms 999us 750 ns at 16 MHz
	
    ldi  r18, 17
    ldi  r19, 60
    ldi  r20, 202
L1: dec  r20
    brne L1
    dec  r19
    brne L1
    dec  r18
    brne L1
    rjmp PC+1

	ret

; Laufrichtung nach rechts
right_to_left:
	in r17, PORTD
	cpi r17,0b00000001
	brne first_run

	ldi r16, 0x02
	jmp right_to_left_loopd

first_run:
	ldi r16, 0x01
right_to_left_loopd:
    out PORTD, r16
    call delay
    lsl r16
    brcc right_to_left_loopd
right_to_leftb:
	ldi r16, 0x00
	out PORTD, r16
	ldi r16, 0x01
right_to_left_loopb:
	out PORTB, r16
	call delay
	lsl r16
	cpi r16,3
	brlt right_to_left_loopb
    ret

; Laufrichtung nach rechts
left_to_right:
    ldi r16, 0x01
left_to_right_loopb:
	out PORTB, r16
	call delay
	lsr r16
	cpi r16,1
	brge left_to_right_loopb
left_to_rightd:
	ldi r16, 0x00
	out PORTB, r16
	ldi r16, 0x80
left_to_right_loopd:
    out PORTD, r16
    call delay
    lsr r16
    brcc left_to_right_loopd

    ret
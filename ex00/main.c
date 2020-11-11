#ifndef __AVR_ATmega328P__
# define __AVR_ATmega328P__
# define F_CPU 16000000
#endif
#include <avr/io.h>
#include <avr/interrupt.h>

int main()
{
	// On met OC1A (PB1) en OUTPUT
	DDRB |= 1 << PINB1;
	// On met le timer sur 500ms: 16MHz/(256 * 0.5) = 32250
	// OCR1A = F_CPU / 256 / 2 - 1;
	// // On met le prescaler sur 256 pour le timer 1 (16.11.2)
	// TCCR1B = (1 << WGM12) | (1 << CS12);
	// // On Toggle OC1A a chaque fois que le timer a match (Table 16-1)
	// TCCR1A = 1 << COM1A0;
	SREG|=(1<<7);
	EICRA|=(1<<ISC10); // Setting control register to Any logical change on INT1 means whenever the logic will change interrupt will occur
 	EIMSK|=(1<<INT1); // Enabling interrupt from INT1 //GLOBAL INTERRUPT
	for(;;);
}

 ISR(INT1_vect)
 {
   PORTB=~PORTB; //toggling the portB
 }
#ifndef __AVR_ATmega328P__
# define __AVR_ATmega328P__
# define F_CPU 16000000
#endif
#include <avr/interrupt.h>

#include <avr/io.h>


int main()
{
	// On met OC1A (PB1) en OUTPUT
	DDRB |= 1 << PINB1;
	SREG|=(1<<7);
	EICRA|=(1<<ISC10); // Setting control register to Any logical change on INT1 means whenever the logic will change interrupt will occur
 	EIMSK|=(1<<INT1); // Enabling interrupt from INT1 //GLOBAL INTERRUPT
	for(;;);
}

 ISR(INT1_vect)
 {
   PORTB=~PORTB; //toggling the portB
 }
#ifndef __AVR_ATmega328P__
# define __AVR_ATmega328P__
# define F_CPU 16000000
#endif
#include <avr/interrupt.h>
#include <avr/io.h>

volatile uint32_t timerCount = 0;
ISR(TIMER0_COMPA_vect)
{
        ++timerCount;
}

int main(void)
{
        DDRB |= 1 << PINB1;
        TIMSK0 |= 1 << OCIE0A;
        TCCR0A |= 1 << WGM00 | 1 << WGM01;
        TCCR0B |= 1 << WGM02;
        OCR0A = 124;
        //sei();
		SREG|=(1<<7);
        TCCR0B |= 1 << CS02 | 1 << CS00;
        while(1)
        {
        	if(timerCount >= 125)
            {
                    PORTB=~PORTB;
                        timerCount = 0;
        	}
        }
        return 0;
}
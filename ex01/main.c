#ifndef __AVR_ATmega328P__
# define __AVR_ATmega328P__
# define F_CPU 16000000
#endif
#include <avr/io.h>

#define ISR(vector, ...)            \
    void vector (void) __attribute__ ((signal,__INTR_ATTRS)) __VA_ARGS__; \
    void vector (void)

int sens = 1;
volatile uint32_t timerCount = 1;
ISR(TIMER0_COMPA_vect)
{
		timerCount += sens;
		if(timerCount > 255)
		{
			sens = -1;
		}
		else if (timerCount < 1)
		{
			sens = 1;
		}

        // OCR1A = (F_CPU / 1024) * 0.77;

        OCR1A = (F_CPU / 256) * ((float)timerCount/255.);
		
		// 		// On active le mode PWM sur OC1A (16.11.1)
		// TCCR1A = (1 << COM1A1) | (1 << WGM11);
		// // On active fast PWM et le prescaler sur 256 pour le timer 1 (16.11.2)
		// TCCR1B = (1 << WGM12) | (1 << CS12);
}

int main(void)
{
        DDRB |= 1 << PINB1;
        TIMSK0 |= 1 << OCIE0A;
        TCCR0A |= 1 << WGM00 | 1 << WGM01;
        TCCR0B |= (1 << WGM12) | 1 << WGM02;
        // OCR0A = 6250;
        OCR0A = 3125;
        //sei();
		SREG|=(1<<7);
        TCCR0B |= 1 << CS02 | 1 << CS00;
		// On met la frequence PWM sur 1Hz: 16MHz/(256 * 1Hz) = 62500
		ICR1 = (F_CPU / 256 - 1);
		// On met le duty-cycle sur 10%: 62500 * 0.1 = 6250
		OCR1A = (F_CPU / 256 - 1) * 0.1;
		// On active le mode PWM sur OC1A (16.11.1)
		TCCR1A = (1 << COM1A1) | (1 << WGM11);
		// On active fast PWM et le prescaler sur 256 pour le timer 1 (16.11.2)
		TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10);
        while(1)
        {
        }
        return 0;
}
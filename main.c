// Measuring distance using ultrasonic distance sensor

#include "includes/LCD.h"
#include "includes/USART.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

static volatile int pulse = 0;
static volatile int i = 0;

ISR(INT0_vect) {
    if (i == 0) {            // pulse har blitt sendt
        TCCR1B |= 1 << CS10; // starter klokke uten prescaler 1MHz
        i = 1;               // for at klokken skal stoppe nestegang
    } else {                 // pulse har blitt mottatt
        TCCR1B = 0;          // stopper klokke
        pulse = TCNT1;       // henter ut antall mikrosekunder
        TCNT1 = 0;           // resetter klokke
        i = 0;               // for å starte klokke igjen
    }
}

int main(void) {

    USART_Init(2400);
    setUpLCD();

    DDRD &= ~(1 << PIND2); // setter D2 til input
    DDRB |= (1 << PINB0);  // setter D7 til output

    int16_t count_a = 0;
    char show_a[16];

    _delay_ms(50);

    GICR |= 1 << INT0;   // setter PD2 til å være external interrupt
    MCUCR |= 1 << ISC00; // logical change sender interupt request

    sei(); // enabler interrupts

    int sent = 0;

    while (1) {
        PORTB |= 1 << PINB0;
        _delay_us(15);

        PORTB &= ~(1 << PINB0);
        count_a = pulse / 58;

        if (count_a < 10 && count_a > 0) {
            if (!sent) {
                USART_Transmit('1');
                sent = 1;
            }
        } else {
            sent = 0;
        }

        itoa(count_a, show_a, 10);
        sendString("Distance Sensor");
        setCursor(1, 2);
        sendString("Distance=");
        sendString("   ");
        setCursor(10, 2);
        sendString(show_a);
        setCursor(13, 2);
        sendString("cm");
        setCursor(1, 1);
    }
}

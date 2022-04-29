/*
 * alarm.c
 *
 * Created: 26.04.2022 14:30:28
 *  Author: Anders K Felde
 */
#include "alarm.h"
#include "USART.h"
#include <avr/interrupt.h>
#include <avr/io.h>

void initAlarm() {
    sei();

    DDRB |= 1 << PINB0;  // setter B port 0 til output
    PORTB |= 1 << PINB0; // skrur på port B

    TCCR1B |= 1 << CS10 | 1 << CS11; // setter prescaler til 64
    TCCR1B |= 1 << WGM12;
    // setter MC til CTC mode, som vil si at TOP i interrupt er OCR1A
}

void startTimer(int seconds) {
    // TIMSK |= 1 << OCIE1B; // Enabler sammenligning med OCR1"B"
    OCR1A = 15624 * seconds; // 60 sekunder
    TIMSK |= 1 << OCIE1A;    // Enabler sammenligning med OCR1"A"
}

void stopTimer() { TIMSK &= ~(1 << OCIE1A); }

ISR(TIMER1_COMPA_vect) {
    // funksjon som blir kallet til klokken har telt til OCR1A sin verdi
    triggerAlarm();
}

void triggerWarning() {
    ALARM = 2;
    USART_Transmit('2');
    startTimer(60);
}

void triggerAlarm() {
    ALARM = 1;
    USART_Transmit('1');
    stopTimer();
}

void stopAlarm() {
    ALARM = 0;
    USART_Transmit('0');
    stopTimer();
}

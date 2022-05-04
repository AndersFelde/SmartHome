/*
 * SmartHome-sound.c
 *
 * Created: 04.05.2022 09:07:24
 * Author : Anders K Felde
 */

#include "includes/USART.h"
#include <avr/io.h>

void startAlarm() {
    PORTB |= (1 << PINB0);
    PORTB |= (1 << PINB1);
}
void stopAlarm() {
    PORTB &= ~(1 << PINB0);
    PORTB &= ~(1 << PINB1);
}

int main(void) {
    /* Replace with your application code */
    USART_Init(2400);
    char receiveChar;

    DDRB |= (1 << PINB0);
    DDRB |= (1 << PINB1);

    while (1) {
        receiveChar = USART_Receive();

        if (receiveChar == '1') {
            startAlarm();
        } else if (receiveChar == '0') {
            stopAlarm();
        }
    }
}

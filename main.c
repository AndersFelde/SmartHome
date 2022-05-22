/*
 * SmartHome-sound.c
 *
 * Created: 04.05.2022 09:07:24
 * Author : Anders K Felde
 */

#include "includes/USART.h"
#include <avr/io.h>
#include <util/delay.h>

void startAlarm()
{
    // sender strøm på pins som er koblet til høyttaler
    PORTB |= (1 << PINB0);
    PORTB |= (1 << PINB1);
}

void stopAlarm()
{
    // sender ikke strøm på pins som er koblet til høyttaler
    PORTB &= ~(1 << PINB0);
    PORTB &= ~(1 << PINB1);
}

int main(void)
{
    USART_Init(2400);
    char receiveChar;

    // setter høyttaler PINS til å være output
    DDRB |= 1 << PINB0;
    DDRB |= 1 << PINB0;

    while (1)
    {
        // for å spille lyd i ujevn takt
        // PORTB ^= 1 << PINB0;
        // _delay_ms(100);
        // PORTB ^= 1 << PINB1;
        // _delay_ms(100);

        receiveChar = USART_Receive();

        if (receiveChar == '1')
        {
            startAlarm();
        }
        else if (receiveChar == '0')
        {
            stopAlarm();
        }
    }
}

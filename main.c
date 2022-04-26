/*
 * SmartHome.c
 *
 * Created: 26.04.2022 08:00:23
 * Author : Anders K Felde
 */

#include "includes/LCD.h"
#include "includes/USART.h"
#include "includes/button.h"
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

int Alarm = 0;

void handleButtonPress(int press) {
    char tall[20];

    itoa(press, tall, 10);

    if (press != -1) {
        clearScreen();
        sendString(tall);
    } else {
        setCursor(1, 2);
        sendString(tall);
    }

    itoa(PIND, tall, 2);
    sendString(tall);
}

void triggerAlarm() {
    Alarm = 1;
    USART_Transmit('0');
}

void stopAlarm() {
    Alarm = 0;
    USART_Transmit('1');
}

int main(void) {
    // test
    /* Replace with your application code */
    initButtons();
    setUpLCD();
    sendString("Det funker123");
    int press;
    while (1) {
        if (Alarm == 0) {

            press = checkButtonPress(); // sjekker om knapp er trykket
            handleButtonPress(press);

            // char receiveChar = USART_Receive();

            // if (receiveChar != -1) {
            //    triggerAlarm();
            // }
            sendString("ok");
        } else {
        }
    }
}

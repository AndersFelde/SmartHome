/*
 * SmartHome.c
 *
 * Created: 26.04.2022 08:00:23
 * Author : Anders K Felde
 */

#include "includes/LCD.h"
#include "includes/USART.h"
#include "includes/alarm.h"
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

void writeButtonPress(int press) {
    char tall[20];
    itoa(press, tall, 10);
    sendString(tall);
}

int main(void) {
    // test
    /* Replace with your application code */
    initButtons();
    setUpLCD();
    sendString("Det funker123");
    int press;
    while (1) {
        if (ALARM == 0) {

            press = checkButtonPress(); // sjekker om knapp er trykket
            handleButtonPress(press);

            char receiveChar = USART_Receive();

            if (receiveChar != -1) {
                triggerWarning();
            }

        } else if (ALARM == 2) {
            clearScreen();
            setCursor(1, 1);
            sendString("Du har 60 sekunder");
            setCursor(1, 2);
            sendString("PIN: ");

            int writtenNum = 0;
            int PIN = 0;

            while (writtenNum < 4) {
                press = checkButtonPress(); // sjekker om knapp er trykket
                if (press != -1) {
                    PIN += press;
                    writeButtonPress(press);
                }
            }

            if (PIN = 1 + 2 + 3 + 4) {
                stopAlarm();
            } else {
                triggerAlarm();
            }
        }
    }
}

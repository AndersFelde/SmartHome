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
char buf[30];

void handleButtonPress(int press) {
    itoa(press, buf, 10);

    if (press != -1) {
        clearScreen();
        sendString(buf);
    } else {
        setCursor(1, 2);
        sendString(buf);
    }

    itoa(PIND, buf, 2);
    sendString(buf);
}

void writeButtonPress(int press) {
    itoa(press, buf, 10);
    sendString(buf);
}

int test() {
    setUpLCD();
    sendString("Test");
    return 0;
}

int main(void) {
    Alarm = 0;
    initAlarm();
    initButtons();
    setUpLCD();
    USART_Init(2400);
    int press;
    char receiveChar;
    while (1) {
        if (Alarm == 0) {

            press = checkButtonPress(); // sjekker om knapp er trykket
            handleButtonPress(press);

            receiveChar = USART_Receive();

            if (receiveChar != '0') {
                clearScreen();
                sendString("Fikk alarm");
                setCursor(1, 2);

                sendCharacter(receiveChar);
                itoa(receiveChar, buf, 2);
                sendString(" ");
                sendString(buf);
                _delay_ms(2000);
                triggerWarning(60);
                clearScreen();
            } else {
                setCursor(1, 1);
                sendString("Ingen alarm");
            }

        } else if (Alarm == 2) {
            // clearScreen();
            setCursor(1, 1);
            sendString("Du har ");
            itoa(CountDown, buf, 10);
            sendString(buf);
            sendString(" sek igjen");
            setCursor(1, 2);
            sendString("PIN: ");

            int writtenNum = 0;
            int PIN = 0;

            // while (writtenNum < 4) {
            press = checkButtonPress(); // sjekker om knapp er trykket
            if (press != -1) {
                PIN += press;
                writeButtonPress(press);
            }
            // }

            // if (PIN == 1 + 2 + 3 + 4) {
            //   stopAlarm();
            //} else {
            //  triggerAlarm();
            //}
        } else if (Alarm == 1) {
            // clearScreen();
            setCursor(1, 1);
            sendString("ENDELIG ALARM");
        }
    }
}

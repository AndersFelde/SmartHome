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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

void handleButtonPress(int press) {
    // itoa(press, buf, 10);

    if (press != -1) {
        clearScreen();
        // sendString(buf);
    } else {
        setCursor(1, 2);
        // sendString(buf);
    }

    // itoa(PIND, buf, 2);
    // sendString(buf);
}

// void writeButtonPress(int press) {
// itoa(press, buf, 10);
//  sendString(buf);
//}

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
    char PIN[5];
    PIN[0] = '\0'; // for at string skal være tom
    int PIN_i = 0;
    char buf[30];

    while (1) {
        if (Alarm == 0) {

            press = checkButtonPress(); // sjekker om knapp er trykket
            handleButtonPress(press);

            receiveChar = USART_Receive();

            if (receiveChar != '0' && coolDown == 0) {
                clearScreen();
                sendString("Fikk alarm");
                //_delay_ms(2000);
                triggerWarning(60);
            } else {
                setCursor(1, 1);
                sendString("Ingen alarm");

                if (coolDown) {
                    setCursor(1, 2);
                    sprintf(buf, "Cooldown: %d", CountDown);
                    sendString(buf);
                }
            }

        } else if (Alarm == 2) {
            // clearScreen();
            setCursor(1, 1);
            sendString("Du har ");
            itoa(CountDown, buf, 10);
            sendString(buf);
            sendString(" sek");
            setCursor(1, 2);
            sendString("PIN: ");
            sendString(PIN);
            sendString("    "); // for å fjerne gamle pins

            // while (writtenNum < 4) {
            press = checkButtonPress(); // sjekker om knapp er trykket
            if (press != -1) {
                if (press != 7) {

                    press = press + '0';
                    PIN[PIN_i] = press;
                    PIN[PIN_i + 1] = '\0';
                    PIN_i++;
                } else {
                    if (PIN_i > 0) {
                        PIN_i--;
                        PIN[PIN_i] = '\0';
                    }
                }
                // writeButtonPress(press);
            }
            // }

            if (strcmp(PIN, "1234") == 0) {
                stopAlarm();
                strcpy(PIN, "");
                PIN_i = 0;
                // startCooldown();
                //_delay_ms(1000);
            } else if (strlen(PIN) == 4) {
                triggerAlarm();
                strcpy(PIN, "");
                PIN_i = 0;
            }

        } else if (Alarm == 1) {
            setCursor(1, 1);
            sendString("ENDELIG ALARM");
            setCursor(1, 2);
            sendString("PIN: ");
            sendString(PIN);
            sendString("    "); // for å fjerne gamle pins

            // while (writtenNum < 4) {
            press = checkButtonPress(); // sjekker om knapp er trykket
            if (press != -1) {
                if (press != 7) {

                    press = press + '0';
                    PIN[PIN_i] = press;
                    PIN[PIN_i + 1] = '\0';
                    PIN_i++;
                } else {
                    if (PIN_i > 0) {
                        PIN_i--;
                        PIN[PIN_i] = '\0';
                    }
                }
                // writeButtonPress(press);
            }
            // }

            if (strcmp(PIN, "1234") == 0) {
                stopAlarm();
                strcpy(PIN, "");
                PIN_i = 0;
                // startCooldown();
                //_delay_ms(1000);
            } else if (strlen(PIN) == 4) {
                strcpy(PIN, "");
                PIN_i = 0;
            }
        }
    }
}

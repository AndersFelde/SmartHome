/*
 * LCD.c
 *
 * Created: 27.01.2022 10:53:13
 *  Author: Anders K Felde
 */
#include "LCD.h"
#include <avr/io.h>
#include <util/delay.h>

void flashLCD() {
    ENABLE_ON;
    asm volatile("nop");
    asm volatile("nop");
    ENABLE_OFF;
}

// funker ikke
void checkIfBusy() {
    DATA_CONTROL = 0; // Put PortB in Input (read) Mode
    RW_ON;
    RS_OFF;

    while (DATA >= 0x80) {
        flashLCD();
    }

    DATA_CONTROL = 0xFF; // set portB as output
}

void sendCommand(unsigned char command) {
    // checkIfBusy();
    RS_OFF;
    RW_OFF;
    DATA = command;
    flashLCD();
    _delay_ms(10);
    DATA = 0;
}

void sendCharacter(unsigned char character) {
    // checkIfBusy();
    RW_OFF;
    RS_ON;
    DATA = character;
    flashLCD();
    DATA = 0;
}

void setCursor(char column, char row) {
    switch (row) {
    case 1:
        sendCommand(0x80 + column - 1);
        break;
    case 2:
        sendCommand(0xc0 + column - 1);
        break;
    default:
        break;
    }
}

void sendString(char *string) {
    while (*string != '\0') {
        sendCharacter(*string);
        string++;
    }
}

void spamTest(int max) {
    for (int i = 0; i < max; i++) {
        setCursor(1, 1);
        sendString("123456789101112");
        setCursor(1, 2);
        sendString("123456789101112");
        clearScreen();
        setCursor(1, 1);
        sendString("abcdefghi");
        setCursor(1, 2);
        sendString("jklmnopqr");
    }
    clearScreen();
    sendString("OK");
}

void setUpLCD() {
    CMD_CONTROL |= 1 << RS;
    CMD_CONTROL |= 1 << RW;
    CMD_CONTROL |= 1 << ENABLE;

    RS_OFF;
    RW_OFF;
    ENABLE_OFF;

    DATA_CONTROL = 0xFF;
    DATA = 0;

    sendCommand(0x38); // 2 data lines
    // sendCommand(0x0f); // display ON, cursor on
    sendCommand(0x0c); // display on, cursor off
    clearScreen();
    setCursor(1, 1);
}

void clearScreen() {
    sendCommand(0x01); // clear LCD screen
}

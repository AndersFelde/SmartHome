/*
 * LCD.h
 *
 * Created: 27.01.2022 10:53:02
 *  Author: Anders K Felde
 */

#ifndef LCD_H_
#define LCD_H_

// variable
#define F_CPU 1000000 // 1MHz
#define RS 5
#define RW 6
#define ENABLE 7
#define DATA_CONTROL DDRD
#define DATA PORTD
#define CMD_CONTROL DDRA
#define CMD PORTA

// konstante
#define ENABLE_ON (CMD |= (1 << ENABLE))
#define ENABLE_OFF (CMD &= ~(1 << ENABLE))
#define RW_ON (CMD |= (1 << RW))
#define RW_OFF (CMD &= ~(1 << RW))
#define RS_ON (CMD |= (1 << RS))
#define RS_OFF (CMD &= ~(1 << RS))

void flashLCD();
void checkIfBusy();
void sendCommand(unsigned char command);
void sendCharacter(unsigned char character);
void setCursor(char column, char row);
void sendString(char *string);
void spamTest(int max);
void setUpLCD();
void clearScreen();

//#warning deez nuts

#endif

/*
 * CFile1.c
 *
 * Created: 26.04.2022 08:50:05
 *  Author: Anders K Felde
 */

#include "button.h"
#include <avr/io.h>

void initButtons() {
    // bør kjøres før initLCD()
    DDRD = 0; // setter 5 første til å lese inn
    DDRC = 0;

    PORTD = 0b11111100;
    PORTC = 0b10000000;
}

int checkClearBit() {
    int bit_clear;

    if (bit_is_clear(PIND, 2))
        bit_clear = 1;
    else if (bit_is_clear(PIND, 3))
        bit_clear = 2;
    else if (bit_is_clear(PIND, 4))
        bit_clear = 3;
    else if (bit_is_clear(PIND, 5))
        bit_clear = 4;
    else if (bit_is_clear(PIND, 6))
        bit_clear = 5;
    else if (bit_is_clear(PIND, 7))
        bit_clear = 6;
    else if (bit_is_clear(PINC, 0))
        bit_clear = 7;
    else
        bit_clear = -1;

    return bit_clear;
}

int checkButtonPress() {

    int pressed = 0;
    int secure_press = 0;
    int secure_release = 0;

    int buttonPress = checkClearBit();
    if (buttonPress != -1) {
        while (1) {
            buttonPress = checkClearBit();

            if (buttonPress != -1) {

                // for hvert registrerte trykk øker man sikkerheten på at
                // det faktisk var trykk
                secure_press++;
                secure_release = 0;

                if (secure_press > 500 && pressed == 0) {
                    // når man har 500 trykk så flipper lampene som switcher
                    pressed = 1;
                    pressed = buttonPress;
                }
            } else {
                // samme tankegang som for press
                secure_release++;
                secure_press = 0;

                if (secure_release > 500) {
                    if (pressed != 0)
                        return pressed;
                    else
                        return -1;
                }
            }
        }
    }
    return -1;
}

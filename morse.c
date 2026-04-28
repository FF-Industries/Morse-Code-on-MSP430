//morse_code.c

#include "morse.h"
#include <io430.h>
#include <stdio.h>
#include "datatypes.h"

void dot(void) {
    P1OUT |= BIT0; // Turn on LED1 for dot
    __delay_cycles(150000); // Adjust this value for the dot duration
    printf(".");
    P1OUT &= ~BIT0; // Turn off LED1
    __delay_cycles(150000); // Add a small gap between dots and dashes
    
}

void dash(void) {
    P1OUT |= BIT6; // Turn on LED2 for dash
    __delay_cycles(450000); // Adjust this value for the dash duration
    printf("-");
    P1OUT &= ~BIT6; // Turn off LED2
    __delay_cycles(150000); // Add a small gap between dots and dashes
}

void space(void) {
    P1OUT &= ~(BIT0 | BIT6); // Turn off both LED1 and LED2 for space
    __delay_cycles(450000); // Adjust this value for the space duration
    printf(" ");
}

void morse_code_read(UINT16 ui_J) {
    UINT16 ui_K;
    int M[36][6] = {
        // Morse Code
        {2, 0, 1},    // A-Z
        {4, 1, 0, 0, 0},
        {4, 1, 0, 1, 0},
        {3, 1, 0, 0},
        {1, 0},
        {4, 0, 0, 1, 0},
        {3, 1, 1, 0},
        {4, 0, 0, 0},
        {2, 0, 0},
        {4, 0, 1, 1, 1},
        {3, 1, 0, 1},
        {4, 0, 1, 0, 0},
        {2, 1, 1},
        {2, 1, 0},
        {3, 1, 1, 1},
        {4, 0, 1, 1, 0},
        {4, 1, 1, 0, 1},
        {3, 0, 1, 0},
        {3, 0, 0, 0},
        {1, 1},
        {3, 0, 0, 1},
        {4, 0, 0, 0, 1},
        {3, 0, 1, 1},
        {4, 1, 0, 0, 1},
        {4, 1, 0, 1, 1},
        {4, 1, 1, 0, 0},
        {5, 1, 1, 1, 1, 1}, // 0-9
        {5, 0, 1, 1, 1, 1},
        {5, 0, 0, 1, 1, 1},
        {5, 0, 0, 0, 1, 1},
        {5, 0, 0, 0, 0, 1},
        {5, 0, 0, 0, 0, 0},
        {5, 1, 0, 0, 0, 0},
        {5, 1, 1, 0, 0, 0},
        {5, 1, 1, 1, 0, 0},
        {5, 1, 1, 1, 1, 0}
    };
    for (ui_K = 1; ui_K <= M[ui_J][0]; ui_K++) {
        if (M[ui_J][ui_K] == 0) {
            dot();
        } else if (M[ui_J][ui_K] == 1) {
            dash();
        }
    }
    space();
}

void play_morse_code(const char* str) {
    int index;
    for(index = 0; str[index] != '\0'; index++) {
        if(str[index] >= 'a' && str[index] <= 'z')
            morse_code_read(str[index]-'a');

        else if(str[index] >= 'A' && str[index] <= 'Z')
            morse_code_read(str[index]-'A');

        else if(str[index] >= '0' && str[index] <= '9')
            morse_code_read(str[index]-'0' + 26); // Add the former 26 letters to map to numbers.

        else if(str[index] == ' ') // Space character
        {
            P1OUT &= ~BIT0;
            __delay_cycles(200000); // (5-1) x Light off for space
           
        }
        else P1OUT |= 0x40; // Error checking
    }
}
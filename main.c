//main.c

#include <io430.h>
#include <stdio.h>
#include "datatypes.h"
#include "morse.h"
#include "led.h"

#define SIZE 70

char str[SIZE] = "Hello World"; 
unsigned int i;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;

    // Set P1.0 and P1.6 as output for LEDs
    P1DIR |= BIT0 | BIT6;
    P1OUT &= ~(BIT0 | BIT6); // Initialize LED1 and LED2 to OFF state.

     
    play_morse_code(str);

    // Turn off both LEDs after the code ends
    turn_off_leds();

    // Infinite loop to keep the program running and prevent it from exiting
    while(1);
}

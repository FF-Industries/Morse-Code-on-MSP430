//led.c

#include "led.h"
#include <io430.h>

void turn_off_leds(void) {
    P1OUT &= ~(BIT0 | BIT6); // Turn off both LED1 and LED2
}

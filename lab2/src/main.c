/***********************************************************************
 * 
 * Blink a LED in Arduino-style and use function from the delay library.
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2022 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/


/* Defines -----------------------------------------------------------*/
#define LED_GREEN PB5   // PB5 is AVR pin where green on-board LED
#define LED_BLUE PB0
#define BTN PB2
                        // is connected
#define SHORT_DELAY 100 // Delay in milliseconds
#ifndef F_CPU
#define F_CPU 16000000 // CPU frequency in Hz required for delay funcs
#endif

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>     // AVR device-specific IO definitions
#include <util/delay.h> // Functions for busy-wait delay loops
#include <gpio.h>


// -----
// This part is needed to use Arduino functions but also physical pin
// names. We are using Arduino-style just to simplify the first lab.
#include "Arduino.h"
#define PB5 5          // In Arduino world, PB5 is called "13"
#define PB0 0
#define PB2 2
// -----


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle one LED and use delay library.
 * Returns:  none
 **********************************************************************/

// #include "Arduino.h"
// #define PB5 13          // In Arduino world, PB5 is called "13"
// #define PB0 8

int main(void)
{
    uint8_t led_value = 0;  // Local variable to keep LED status
    uint8_t led_valueblue = 0;
    // Set pins where LEDs are connected as output
    // Ver 1: Arduino style
    // pinMode(LED_GREEN, OUTPUT);
    // pinMode(LED_RED, OUTPUT);

    // Ver 2: Low-level (register) style
    //DDRB = DDRB | (1<<LED_GREEN);
    //DDRB = DDRB | (1<<LED_BLUE);
    // Ver 3:
    GPIO_mode_output(&DDRB, LED_GREEN);
    GPIO_mode_output(&DDRB, LED_BLUE);
    GPIO_mode_input_pullup(&DDRB, PB2);

    // Infinite loop
    while (1)
    {
        if (!GPIO_read(&PINB, BTN))
        {
            // Pause several milliseconds
            _delay_ms(SHORT_DELAY);

            // Change LED value
            if (led_value == 0) {
                led_value = 1;
                // Set pin to HIGH
                //digitalWrite(LED_GREEN, HIGH);
                //digitalWrite(LED_BLUE, HIGH);
                //PORTB = PORTB | (1<<LED_GREEN);
                //PORTB = PORTB | (1<<LED_BLUE);
                GPIO_write_high(&PORTB, LED_GREEN);
                GPIO_write_high(&PORTB, LED_BLUE);
            }
            else {
                led_value = 0;
                // Clear pin to LOW
                //digitalWrite(LED_GREEN, LOW);
                //digitalWrite(LED_BLUE, LOW);
                //PORTB = PORTB & ~(1<<LED_GREEN);
                //PORTB = PORTB & ~(1<<LED_BLUE);
                GPIO_write_low(&PORTB, LED_GREEN);
                GPIO_write_low(&PORTB, LED_BLUE);
            }
        }
    }

    // Will never reach this
    return 0;
}
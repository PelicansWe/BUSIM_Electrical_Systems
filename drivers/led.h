// led.h - driver for an LED on a GPIO pin.
//
// This file lists the functions other code can use.
// How they work is in led.c.

#ifndef LED_H
#define LED_H

#include "pico/stdlib.h"

// Set up the pin for an LED. Call this once before using the other functions.
void configure_led(uint pin);

// Turn the LED on.
void turn_on_led(uint pin);

// Turn the LED off.
void turn_off_led(uint pin);

// Turn the LED off if it's on, or on if it's off.
void toggle_led(uint pin);

// Returns true if the LED is on, false if it's off.
bool get_led(uint pin);

#endif

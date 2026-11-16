// button.h - driver for a push button or 2-position toggle switch on a GPIO pin.
//
// This file lists the functions other code can use.
// How they work is in button.c.
//
// Wiring: one side of the button goes to the GPIO pin, the other side to GND.
// The pin is pulled up inside the Pico, so it reads high when the button is
// released and low when it's pressed. The functions below handle that, so
// "pressed" always means true.

#ifndef BUTTON_H
#define BUTTON_H

#include "pico/stdlib.h"

// Set up the pin for a button. Call this once before using the other functions.
void configure_button(uint pin);

// Read the button and filter out bounce. Call this every time through the
// main loop. Returns true only on the loop where the button changes
// (pressed to released, or released to pressed), and false otherwise.
bool update_button(uint pin);

// Returns true if the button is pressed, false if it's released.
// This is the filtered value from the last call to update_button.
bool get_button(uint pin);

#endif

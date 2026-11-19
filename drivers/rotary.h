// 8-position rotary switch. Common pin to GND, positions 0-7 on 8 consecutive
// GPIO pins starting at first_pin.

#ifndef ROTARY_H
#define ROTARY_H

#include "pico/stdlib.h"

void configure_rotary(uint first_pin);

// Call every loop. Returns true when the position changes.
bool update_rotary(uint first_pin);

int get_rotary(uint first_pin);

#endif

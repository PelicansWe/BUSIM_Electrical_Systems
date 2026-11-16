// led.c - how the LED functions work. See led.h for how to use them.

#include "led.h"

void configure_led(uint pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
    gpio_put(pin, false);   // start off
}

void turn_on_led(uint pin) {
    gpio_put(pin, true);
}

void turn_off_led(uint pin) {
    gpio_put(pin, false);
}

void toggle_led(uint pin) {
    // Flips just this pin in one step
    gpio_xor_mask(1u << pin);
}

bool get_led(uint pin) {
    // gpio_get_out_level tells us what we last set the pin to
    return gpio_get_out_level(pin);
}

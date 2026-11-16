// Example of using the LED driver from main.
//
// The onboard LED blinks. The LED on GP15 stays on for 5 seconds, then turns off.
// Wiring: an LED and a 330 ohm resistor in series from GP15 to GND.

#include "pico/stdlib.h"
#include "led.h"

#define ONBOARD_LED_PIN 25
#define EXTERNAL_LED_PIN 15

int main(void) {
    configure_led(ONBOARD_LED_PIN);
    configure_led(EXTERNAL_LED_PIN);

    turn_on_led(EXTERNAL_LED_PIN);

    int blinks = 0;
    while (true) {
        toggle_led(ONBOARD_LED_PIN);
        sleep_ms(250);

        blinks++;
        if (blinks == 20) {   // 20 x 250 ms = 5 seconds
            turn_off_led(EXTERNAL_LED_PIN);
        }
    }
}

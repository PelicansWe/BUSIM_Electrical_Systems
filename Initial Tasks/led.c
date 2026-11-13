#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define LED_PIN 25
#define MAX_INPUT_LEN 10

int main() {
    stdio_init_all();
   while (!stdio_usb_connected()) {
        sleep_ms(100);
    }
    sleep_ms(500); 
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(LED_PIN);
    pwm_set_wrap(slice_num, 100);
    pwm_set_gpio_level(LED_PIN, 0);
    pwm_set_enabled(slice_num, true);

    char buffer[MAX_INPUT_LEN];
    int buf_index = 0;

    printf("Enter a brightness level (0-100):\n");

    while (true) {
        int c = getchar_timeout_us(0);

        if (c != PICO_ERROR_TIMEOUT) {
            printf("got char code %d\n", c);
            if (c == '\r' || c == '\n') {
                if (buf_index > 0) {                    // ignore blank lines / second char of \r\n
                    buffer[buf_index] = '\0';
                    int brightness = atoi(buffer);

                    if (brightness >= 0 && brightness <= 100) {
                        pwm_set_gpio_level(LED_PIN, brightness);
                        printf("Success: LED brightness set to %d%%\n", brightness);
                        printf("Enter a brightness level (0-100):\n");
                    } else {
                        printf("Error: Number out of bounds. Please enter 0-100.\n");
                    }
                    buf_index = 0;                      // reset for the next entry
                }
            } else if (buf_index < MAX_INPUT_LEN - 1) {  // leave room for '\0'
                buffer[buf_index++] = (char)c;
            }
        }
    }
}

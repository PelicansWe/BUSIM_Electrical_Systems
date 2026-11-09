#include <stdio.h>
#include "pico/stdlib.h"

const int BUTTON_PIN = 2;
const int FLAP_UP_PIN = 1;
const int FLAP_DOWN_PIN = 0;

const int STABLE_TIME = 100; // milliseconds

int previous_flap_position = 1; // 0: down, 1: neutral, 2: up

typedef struct {
        bool stable_button_state;
        bool candidate_button_state;
        int button_stable_count;
    } Input;

void setup_input_button(int pin){
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin);
}

bool update_button_state(int pin, Input *input){
    bool button_state = !gpio_get(pin);
    if (button_state == input->candidate_button_state) {
        if(input->button_stable_count <= STABLE_TIME) {input->button_stable_count++;}
        if (input->button_stable_count >= STABLE_TIME) {
            if (button_state != input->stable_button_state) {
                input->stable_button_state = button_state;
                return true; // State changed
            }
        }
    } else {
        input->candidate_button_state = button_state;
        input->button_stable_count = 0;
    }
    return false; // No state change
}

int main()
{
    stdio_init_all();
    
    setup_input_button(BUTTON_PIN);
    setup_input_button(FLAP_UP_PIN);
    setup_input_button(FLAP_DOWN_PIN);

    Input button_input = {false, false, 0};

    Input flap_up = {false, false, 0};
    Input flap_down = {false, false, 0};

    while (true) {
        if (update_button_state(BUTTON_PIN, &button_input)) {
            if (button_input.stable_button_state) {
                printf("UFC_1 1 (Pressed)\n");
            } else {
                printf("UFC_1 0 (Released)\n");
            }
        }

        update_button_state(FLAP_UP_PIN, &flap_up);
        update_button_state(FLAP_DOWN_PIN, &flap_down);

        int flap_position = 1; // Default to neutral
        if(flap_up.stable_button_state && flap_down.stable_button_state) {
                ; //default to neutral if both are pressed
        } else if(flap_down.stable_button_state) {
            flap_position = 0; // Down
        } else if(flap_up.stable_button_state) {
            flap_position = 2; // Up
        }

        if(flap_position != previous_flap_position) {
            previous_flap_position = flap_position;
            printf("FLAP_SW %d\n", flap_position);
        }

        sleep_ms(1);
    }
}
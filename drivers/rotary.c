#include "rotary.h"

#define ROTARY_POSITIONS 8
#define STABLE_COUNT 100

static int stable_position[NUM_BANK0_GPIOS];
static int candidate_position[NUM_BANK0_GPIOS];
static int stable_count[NUM_BANK0_GPIOS];

// Returns -1 while the switch is between positions.
static int read_rotary(uint first_pin) {
    for (int i = 0; i < ROTARY_POSITIONS; i++) {
        if (!gpio_get(first_pin + i)) {
            return i;
        }
    }
    return -1;
}

void configure_rotary(uint first_pin) {
    for (int i = 0; i < ROTARY_POSITIONS; i++) {
        gpio_init(first_pin + i);
        gpio_set_dir(first_pin + i, GPIO_IN);
        gpio_pull_up(first_pin + i);
    }

    int position = read_rotary(first_pin);
    if (position < 0) {
        position = 0;
    }
    stable_position[first_pin] = position;
    candidate_position[first_pin] = position;
    stable_count[first_pin] = 0;
}

bool update_rotary(uint first_pin) {
    int position = read_rotary(first_pin);
    if (position < 0) {
        return false;
    }

    if (position != candidate_position[first_pin]) {
        candidate_position[first_pin] = position;
        stable_count[first_pin] = 0;
        return false;
    }

    if (stable_count[first_pin] < STABLE_COUNT) {
        stable_count[first_pin]++;
        return false;
    }

    if (position != stable_position[first_pin]) {
        stable_position[first_pin] = position;
        return true;
    }
    return false;
}

int get_rotary(uint first_pin) {
    return stable_position[first_pin];
}

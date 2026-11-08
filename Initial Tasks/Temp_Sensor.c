#include "hardware/adc.h"
#include "pico/stdlib.h"
#include <stdio.h>

int main() {
  stdio_init_all();
  adc_init();

  adc_set_temp_sensor_enabled(true);

  adc_select_input(4);

  uint16_t raw;
  float temp;
  float adc_voltage;

  while (true) {

    raw = adc_read();

    adc_voltage = raw * (3.3f / (1 << 12));

    temp = 27.0f - ((adc_voltage - 0.706f) / 0.001721f);

    printf("Temp: %.2f C\n", temp);

    sleep_ms(500);
  }
}

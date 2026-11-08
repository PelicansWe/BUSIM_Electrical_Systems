#include <stdio.h>
#include <ctype.h> 
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"


int main(){
    stdio_init_all();

    uart_init(uart0, 115200);
    gpio_set_function(0, GPIO_FUNC_UART); //tx pin
    gpio_set_function(1, GPIO_FUNC_UART); //rx pin


    while (true) {
        int input_char = getchar_timeout_us(0);

        if (input_char != PICO_ERROR_TIMEOUT && input_char != EOF){
            uart_putc(uart0, (char)input_char);
        
        }
        
        if(uart_is_readable(uart0)){
            char response_char = uart_getc(uart0);

            putchar(response_char);
            fflush(stdout);
        }
    }
}

#include <stdio.h>
#include <ctype.h> 
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"


int main(){
    uart_init(uart0, 115200);
    gpio_set_function(0, GPIO_FUNC_UART); //tx pin
    gpio_set_function(1, GPIO_FUNC_UART); //rx pin

    while(true){

        if(uart_is_readable(uart0)){
            char received_char = uart_getc(uart0);
            char upper_char = toupper((unsigned char)received_char);
            uart_putc(uart0, upper_char);
        }
    }
}

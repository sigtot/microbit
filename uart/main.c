#include "gpio.h"
#include "uart.h"

int main(){
    uart_init();

    // Configure buttons
    GPIO->PIN_CNF[17] = 0; // Button A
    GPIO->PIN_CNF[26] = 0; // Button B

    while(1){
        uart_send(uart_read());

        // Check if button A is pressed;
        if(!(GPIO->IN & (1 << 17))) {
            uart_send('A');
        }

        // Check if button B is pressed;
        if(!(GPIO->IN & (1 << 26))) {
            uart_send('B');
        }
    }

    return 0;
}

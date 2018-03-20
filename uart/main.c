#include "gpio.h"
#include "uart.h"
#include <stdio.h>

void toggle_leds();
ssize_t _write(int fd, const void *buf, size_t count);

int main(){
    // Configure LED Matrix
    for(int i = 4; i <= 15; i++){
        GPIO->DIRSET = (1 << i);
        GPIO->OUTCLR = (1 << i);
    }

    // Configure buttons
    GPIO->PIN_CNF[17] = 0; // Button A
    GPIO->PIN_CNF[26] = 0; // Button B

    uart_init();

    iprintf("Norway has %d counties.\n\r", 18);

    while(1){
        // Read value from computer
        char rx = uart_read();

        // Send read back to computer
        uart_send(rx);

        // Check if button A is pressed;
        if(!(GPIO->IN & (1 << 17))) {
            uart_send('A');
        }

        // Check if button B is pressed;
        if(!(GPIO->IN & (1 << 26))) {
            uart_send('B');
        }

        if(rx != '\0') toggle_leds();
    }

    return 0;
}

void toggle_leds() {
    static int leds_on;
    if(leds_on) {
        GPIO->OUTCLR = (1 << 13);
        GPIO->OUTCLR = (1 << 14);
        GPIO->OUTCLR = (1 << 15);
        leds_on = 0;
    } else {
        GPIO->OUTSET = (1 << 13);
        GPIO->OUTSET = (1 << 14);
        GPIO->OUTSET = (1 << 15);
        leds_on = 1;
    }
}

ssize_t _write(int fd, const void *buf, size_t count){
    char * letter = (char *)(buf);
    for(int i = 0; i < count; i++){
        uart_send(*letter);
        letter++;
    }
    return count;
}

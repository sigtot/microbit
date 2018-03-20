#include "gpio.h"
#include "uart.h"

int main(){
    uart_init();

    while(1) {
        uart_send('a');
    }

    while(1){
        char uart_read();
        int sleep = 10000;
        while(--sleep);
    }

    return 0;
}
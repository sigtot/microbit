#include "gpio.h"
#include "uart.h"

int main(){
    uart_init();

    while(1){
        uart_send(uart_read());
    }

    return 0;
}

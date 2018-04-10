#include "twi.h"
#include "utility.h"
#include "uart.h"
#include "accel.h"
#include "ubit_led_matrix.h"

#include <stdlib.h>

#define ACCEL_ADDR		0x01D
#define WHO_AM_I_ADDR   0x0D

int main() {
    uart_init();
    twi_init();
    accel_init();
    ubit_led_matrix_init();

    uint8_t * data_buffer;

    data_buffer = (uint8_t *)malloc(1 * sizeof(uint8_t));
    twi_multi_read(ACCEL_ADDR, WHO_AM_I_ADDR, 1, data_buffer);
    utility_print(&uart_send, "I am: %d\n\r", data_buffer[0]);
    free(data_buffer);

    // Configure buttons
    GPIO->PIN_CNF[17] = 0; // Button A
    GPIO->PIN_CNF[26] = 0; // Button B

    int * int_buffer;
    int_buffer = (int *)malloc(3 * sizeof(int));

    while(1){
        accel_read_x_y_z(int_buffer);
        utility_print(&uart_send, "Acc vector: (%d, %d, %d)\n\r", int_buffer[0], int_buffer[1], int_buffer[2]);

        int accX = int_buffer[0];
        int accY = int_buffer[1];

        float posX = 0;
        float posY = 0;



        int counter = 100000;
        while(--counter);
    }

    utility_print(&uart_send, ":)\n\r");
    return 0;
}

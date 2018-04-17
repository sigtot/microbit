#include "twi.h"
#include "utility.h"
#include "uart.h"
#include "accel.h"
#include "ubit_led_matrix.h"
#include "gpio.h"

#include <stdlib.h>
#include <math.h>

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

    double weight = 0.005;

    double posX = 0;
    double posY = 0;

    double velX = 0;
    double velY = 0;

    while(1){
        accel_read_x_y_z(int_buffer);

        double accX = (double) int_buffer[0];
        double accY = (double) int_buffer[1];

        velX += weight * accX;
        velY += weight * accY;

        posX += velX;
        posY += velY;

        /* Check if button A is pressed
         * Reset position and velocity if it is */
        if(!(GPIO->IN & (1 << 17))) {
            utility_print(&uart_send,"reset");
            posX = 0;
            posY = 0;

            velX = 0;
            velY = 0;
        }

        // Edge detection
        if(posX >= 2){
            // Right edge collision
            posX = 2;
            if(velX > 0) velX = 0; // No rightward motion
        }

        if(posX <= -2){
            // Left edge collision
            posX = -2;
            if(velX < 0) velX = 0; // No leftward motion
        }

        if(posY >= 2){
            // Top collision
            posY = 2;
            if(velY > 0) velY = 0; // No upward motion
        }

        if(posY <= -2){
            // Bottom edge collision
            posY = -2;
            if(velY < 0) velY = 0; // No downward motion
        }

        // Write position to led matrix
        ubit_led_matrix_light_only_at((int) round(posX), - (int) round(posY));

        //utility_print(&uart_send, "Acc: (%d, %d, %d)\tVel: (%d, %d)\tPos: (%d, %d)\n\r", int_buffer[0], int_buffer[1], int_buffer[2], (int) round(velX), (int) round(velY), (int) round(posX), (int) round(posY));
        utility_print(&uart_send, "Acc: (%d, %d)\tVel: (%d, %d)\tPos: (%d, %d)\n\r", (int) round(weight * accX), (int) round(accY), (int) round(velX), (int) round(velY), (int) round(posX), (int) round(posY));
        int counter = 100000;
        while(--counter);
    }

    utility_print(&uart_send, ":)\n\r");
    return 0;
}

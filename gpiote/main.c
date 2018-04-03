#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

int main() {
	// Configure A-button event
	GPIOTE->CONFIG[0] = (17 << 8) | 1 | (2 << 16); // PSEL = 17 | MODE = Event | POLARITY = HiToLo

	// Configure led-pins tasks
	GPIOTE->CONFIG[1] = (13 << 8) | 3 | (3 << 16); // PSEL = 13 | MODE = Task | POLARITY = Toggle
    GPIOTE->CONFIG[2] = (14 << 8) | 3 | (3 << 16); // PSEL = 14 | MODE = Task | POLARITY = Toggle
   	GPIOTE->CONFIG[3] = (15 << 8) | 3 | (3 << 16); // PSEL = 15 | MODE = Task | POLARITY = Toggle

   	// Configure ppi shit
   	PPI->PPI_CH[0].EEP = (uint32_t)&(GPIOTE->IN[0]);
	PPI->PPI_CH[0].TEP = (uint32_t)&(GPIOTE->OUT[1]);

	PPI->PPI_CH[1].EEP = (uint32_t)&(GPIOTE->IN[0]);
	PPI->PPI_CH[1].TEP = (uint32_t)&(GPIOTE->OUT[2]);

	PPI->PPI_CH[2].EEP = (uint32_t)&(GPIOTE->IN[0]);
	PPI->PPI_CH[2].TEP = (uint32_t)&(GPIOTE->OUT[3]);
	PPI->CHENSET = (1 << 0) | (1 << 1) | (1 << 2);

	while(1);

	return 0;
}

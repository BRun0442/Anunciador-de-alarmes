/*
 *  Created on: 5 de jul. de 2025
 *      Author: Osmar Bruno
 */

#include "../programa.h"

void iniciaLED(void);
void ligaLED(int);
void desligaLED(int);
void toggleLED(int);

void iniciaLED(void)
{
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_GPIO);
    LPC_IOCON->PIO0[6] = 0;

	Chip_GPIO_SetPinDIR(LPC_GPIO, 1, 24, 1); //LED 0
	Chip_GPIO_SetPinDIR(LPC_GPIO, 0, 6, 1);  //LED 1
    Chip_GPIO_SetPinDIR(LPC_GPIO, 0, 7, 1);  //LED 2
	Chip_GPIO_SetPinDIR(LPC_GPIO, 1, 28, 1); //LED 3


	Chip_GPIO_SetPinState(LPC_GPIO, 1, 24, 0);
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 6, 0);
	Chip_GPIO_SetPinState(LPC_GPIO, 0, 7, 0);
	Chip_GPIO_SetPinState(LPC_GPIO, 1, 28, 0);
}

void ligaLED(int led)
{
    switch(led) {
        case 0:
            Chip_GPIO_SetPinState(LPC_GPIO, 1, 24, 1);
            break;
        case 1:
            Chip_GPIO_SetPinState(LPC_GPIO, 0, 6, 1);
            break;
        case 2:
            Chip_GPIO_SetPinState(LPC_GPIO, 0, 7, 1);
            break;
        case 3:
            Chip_GPIO_SetPinState(LPC_GPIO, 1, 28, 1);
            break;
        default:
            break;
    }
}

void desligaLED(int led)
{
    switch(led) {
        case 0:
            Chip_GPIO_SetPinState(LPC_GPIO, 1, 24, 0);
            break;
        case 1:
            Chip_GPIO_SetPinState(LPC_GPIO, 0, 6, 0);
            break;
        case 2:
            Chip_GPIO_SetPinState(LPC_GPIO, 0, 7, 0);
            break;
        case 3:
            Chip_GPIO_SetPinState(LPC_GPIO, 1, 28, 0);
            break;
        default:
            break;
    }
}

void defineLED(int led, int state)
{
	switch(led) {
		case 0:
			Chip_GPIO_SetPinState(LPC_GPIO, 1, 24, state);
			break;
		case 1:
			Chip_GPIO_SetPinState(LPC_GPIO, 0, 6, state);
			break;
		case 2:
			Chip_GPIO_SetPinState(LPC_GPIO, 0, 7, state);
			break;
		case 3:
			Chip_GPIO_SetPinState(LPC_GPIO, 1, 28, state);
			break;
		default:
			break;
	}
}

void toggleLED(int led)
{
    switch(led) {
        case 0:
            Chip_GPIO_SetPinToggle(LPC_GPIO, 1, 24);
            break;
        case 1:
            Chip_GPIO_SetPinToggle(LPC_GPIO, 0, 6);
            break;
        case 2:
            Chip_GPIO_SetPinToggle(LPC_GPIO, 0, 7);
            break;
        case 3:
            Chip_GPIO_SetPinToggle(LPC_GPIO, 1, 28);
            break;
        default:
            break;
    }
}

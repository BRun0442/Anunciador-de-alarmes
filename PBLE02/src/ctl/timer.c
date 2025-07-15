/*
 *  Created on: 5 de jul. de 2025
 *      Author: Osmar Bruno
 */

#include "../programa.h"

void iniciaTimer(void)
{
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_CT32B0);

	// Clock do contador = 40MHz / (19 + 1) = 1MHz (tick de 1µs)
	LPC_TIMER32_0->PR = 39;
	LPC_TIMER32_0->MR[0] = 999;

	//(Interromper e Resetar)
	LPC_TIMER32_0->MCR = (1 << 0) | (1 << 1); // MR0I e MR0R

	NVIC_EnableIRQ(TIMER_32_0_IRQn);

	LPC_TIMER32_0->TCR = 1; // Habilita o contador
}

void TIMER32_0_IRQHandler(void) {
    // Verifica se a fonte da interrupção foi o match do MR0
    if (LPC_TIMER32_0->IR & (1 << 0)) {
        // Limpa a flag de interrupção do MR0
    	LPC_TIMER32_0->IR = (1 << 0);
    	millis_counter++;

    	//flag_interrupt = true;
    }
}

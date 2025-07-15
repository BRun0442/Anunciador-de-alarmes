/*
 *  Created on: 5 de jul. de 2025
 *      Author: Osmar Bruno
 */

#ifndef PROGRAMA_H
#define PROGRAMA_H
	#include <string.h>
	#include "chip.h"
	#include "board.h"
	#include "sysctl_11xx.h"
	#include "I2C.h"
    #include "util.h"
	#include "./ctl/var.h"
	#include "./ctl/stateMachine.h"
	#include "./hardware/RTC.h"
	#include "./hardware/LED.h"
	#include "./hardware/Serial.h"
	#include "./hardware/Teclado.h"
	#include "./hardware/LCD.h"
	#include "./hardware/ADC.h"
    #include "./hardware/DAC.h"

	extern volatile bool flag_interrupt;
	extern volatile uint32_t millis_counter;

	static inline void delayMS(uint32_t milliseconds) {
	    SysTick_Config(SystemCoreClock / 1000);

	    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;

	    for (uint32_t i = 0; i < milliseconds; i++) {
	        while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
	    }

	    SysTick->CTRL = 0;
	}


	static inline void configClock_PLL(void){
	    Chip_Clock_SetMainClockSource(SYSCTL_MAINCLKSRC_IRC);
	    SystemCoreClockUpdate();
	    Chip_SYSCTL_PowerUp(SYSCTL_POWERDOWN_SYSOSC_PD);
	    delayMS(50);
	    Chip_Clock_SetSystemPLLSource(SYSCTL_PLLCLKSRC_MAINOSC);
	    Chip_Clock_SetupSystemPLL(1, 0); // M = 1+1 = 2. 20MHz * 2 = 40MHz
	    Chip_SYSCTL_PowerUp(SYSCTL_POWERDOWN_SYSPLL_PD);
	    Chip_FMC_SetFLASHAccess(FLASHTIM_50MHZ_CPU);
	    Chip_Clock_SetMainClockSource(SYSCTL_MAINCLKSRC_PLLOUT);
	    SystemCoreClockUpdate();
	}
#endif

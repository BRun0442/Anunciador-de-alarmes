/*
 *  Created on: 5 de jul. de 2025
 *      Author: Osmar Bruno
 */

#include "../programa.h"

static ADC_CLOCK_SETUP_T ADCSetup;

static void Init_ADC_PinMux(void)
{
	#if (defined(BOARD_NXP_XPRESSO_11U14) || defined(BOARD_NGX_BLUEBOARD_11U24))
		Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 11, FUNC2);
	#elif defined(BOARD_NXP_XPRESSO_11C24)
		Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_11, FUNC2);
	#else
		#error "Pin muxing for ADC not configured"
	#endif
}

void iniciaADC()
{
	Init_ADC_PinMux();

	Chip_ADC_Init(LPC_ADC, &ADCSetup);
	Chip_ADC_EnableChannel(LPC_ADC, ADC_CH0, ENABLE);


	Chip_ADC_SetSampleRate(LPC_ADC, &ADCSetup, 500000);
	Chip_ADC_SetResolution(LPC_ADC, &ADCSetup, ADC_10BITS);
}

uint16_t leSensor()
{
	uint16_t dataADC;

	Chip_ADC_SetStartMode(LPC_ADC, ADC_START_NOW, ADC_TRIGGERMODE_RISING);
	while (Chip_ADC_ReadStatus(LPC_ADC, ADC_CH0, ADC_DR_DONE_STAT) != SET) {}

	Chip_ADC_ReadValue(LPC_ADC, ADC_CH0, &dataADC);

	return dataADC;

}

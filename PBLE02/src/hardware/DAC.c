/*
 *  Created on: 5 de jul. de 2025
 *      Author: Osmar Bruno
 */

#include "../programa.h"

void iniciaDAC(void)
{
	LPC_SYSCTL->SYSAHBCLKCTRL |= (1<<16);

	LPC_IOCON->PIO0[4]         = 0x01;
	LPC_IOCON->PIO0[5]         = 0x01;

	LPC_SYSCTL->SYSAHBCLKCTRL |= (1<<5);
	LPC_SYSCTL->PRESETCTRL    |= (1<<1);

	LPC_I2C->SCLH 			   = 240;
	LPC_I2C->SCLL 			   = 240;

	LPC_I2C->CONSET			   |= (1<<6);
}

void definirDAC(uint16_t valor)
{
	if (valor > 4095) {
		valor = 4095;
	}

	uint8_t i2c_buffer[2];
	i2c_buffer[0] = (valor >> 8) & 0x0F;
	i2c_buffer[1] = valor & 0xFF;

	I2C_Transmitir(MCP4725_ENDERECO_I2C, i2c_buffer, 2);
}

void senoideDAC(int vucIndice)
{
	uint16_t guiAmostra[16] = {
	    2048, 3072, 3863, 4095,
	    3863, 3072, 2048, 1024,
	    283,  0,    283,  1024,
	    2048, 3072, 3863, 4095
	};

	definirDAC( guiAmostra[ vucIndice ] );
}

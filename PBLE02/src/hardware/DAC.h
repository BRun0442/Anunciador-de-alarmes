/*
 *  Created on: 5 de jul. de 2025
 *      Author: Osmar Bruno
 */

#ifndef DAC_H
#define DAC_H
	#include "../programa.h"
	#define MCP4725_ENDERECO_I2C 0x60

	void iniciaDAC(void);
	void definirDAC(uint16_t valor);
	void senoideDAC(int);
#endif

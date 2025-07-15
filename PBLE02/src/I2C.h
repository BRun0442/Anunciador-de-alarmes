/*
 *  Created on: 5 de jul. de 2025
 *      Author: Osmar Bruno
 */

#ifndef I2C_H
#define I2C_H
	#include "programa.h"
	void iniciaI2C();
	void I2C_Transmitir(unsigned char endereco, unsigned char *valor, unsigned char qtd);
	void I2C_Receber(unsigned char endereco, unsigned char *valor, unsigned char qtd);
#endif

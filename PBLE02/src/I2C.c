/*
 *  Created on: 5 de jul. de 2025
 *      Author: Osmar Bruno
 */

#include "programa.h"

void iniciaI2C(){

	 LPC_SYSCTL->SYSAHBCLKCTRL |= 1<<16;

	// configurar o pino como SCL em modo I2C padrão (I2CMODE=00) (UM10398, 7.4.11)
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 4, IOCON_FUNC1 | IOCON_MODE_INACT); // SDA
	Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 5, IOCON_FUNC1 | IOCON_MODE_INACT); // SCL

    // garantir que o periférico I2C não esteja em estado de reset (UM10398, 3.5.2)
	//Chip_SYSCTL_PeriphReset(RESET_I2C0);
	 LPC_SYSCTL->SYSAHBCLKCTRL |= 1<<5;
	LPC_SYSCTL->PRESETCTRL |= 1<<1;



    // Estipular o clock I2C para 100kHz (UM10398, 15.7.5.1)
    LPC_I2C->SCLH = 240;
    LPC_I2C->SCLL = 240;

    // habilitar o periférico I2C como mestre (UM10398, 15.7.1 / 15.8.1)
    LPC_I2C->CONSET |= (1 << 6);
   // LPC_I2Cx(id)->CONCLR = (I2C_CON_AA | I2C_CON_SI | I2C_CON_STA | I2C_CON_I2EN);


}

void I2C_Transmitir(unsigned char endereco, unsigned char *valor, unsigned char qtd){
    unsigned char c;
    // requisitar o evento de START (UM10398, 15.7.1)
    LPC_I2C->CONSET = (1 << 5);

    // esperar pelo pelo fim do evento de START (bit SI, UM10398, 15.7.1)
    while (LPC_I2C->STAT != 0x08);

    // enviar o endereço do dispositivo escravo e espeficicação de escrita (R/W=0) (UM10398, 15.7.3)
    LPC_I2C->DAT = endereco << 1;

    // limpar a sinalizações SI e START (UM10398, 15.7.6)
    LPC_I2C->CONCLR = (5 << 3);

    // esperar por um estado 0x18 (ACK recebido) (UM10398, 15.10.1, tabela 236)
    while (LPC_I2C->STAT != 0x18);

    // Enviar os dados requisitados
    for (c = 0; c < qtd; c++)
    {
        // transmitir o dado (UM10398, 15.7.3)
        LPC_I2C->DAT = valor[c];
        // limpar o bit SI para transmitir um byte e esperar por um ACK (UM10398, 15.7.6 e tabela 236)
        LPC_I2C->CONCLR = (1 << 3);
        // esperar por um estado 0x28 (ACK recebido) (UM10398, 15.10.1, tabela 236)
        while (LPC_I2C->STAT != 0x28);
    }
    // requisitar o evento de STOP (UM10398, 15.7.1)
    LPC_I2C->CONSET = (1 << 4);
    // limpar o bit SI (UM10398, 15.7.6)
    LPC_I2C->CONCLR = (1 << 3);
}

void I2C_Receber(unsigned char endereco, unsigned char *valor, unsigned char qtd){
    unsigned char c;
    // requisitar o evento de START (UM10398, 15.7.1)
    LPC_I2C->CONSET = (1 << 5);
    // esperar pelo pelo fim do evento de START (bit SI, UM10398, 15.7.1)
    while (LPC_I2C->STAT != 0x08);

    // enviar o endereço do dispositivo escravo e espeficicação de leitura (R/W=1) (UM10398, 15.7.3)
    LPC_I2C->DAT = (endereco << 1) + 1;
    // limpar a sinalizações SI e START (UM10398, 15.7.6)
    LPC_I2C->CONCLR = (5 << 3);
    // esperar pela transmissão do endereço e recebimento de um ACK (estado 0x40) (UM10398, 15.10.1, tabela 237)
    while (LPC_I2C->STAT != 0x40);

    // Receber os dados requisitados
    for (c = 0; c < qtd; c++)
    {
        // Quando for receber o último byte, deve-se gerar
        // um NACK (Not Ack), caso contrário, um ACK

        // limpar os bits SI, START e AA para gerar um NACK (UM10398, 15.7.6 e tabela 237)
        LPC_I2C->CONCLR = 0x2C;
        if (c != (qtd - 1))
        {
            // estipular o AA para gerar um ACK (UM10398, 15.7.1 e tabela 2.3.7)
            LPC_I2C->CONSET = 0x4;
        }

        // esperar pelo recebimento de um byte (o estado deve assumir 0x50 ou 0x58) (UM10398, 15.10.2, tabela 237)
        while ((LPC_I2C->STAT != 0x50) && (LPC_I2C->STAT != 0x58));

        // recuperar e armazenar o byte recebido na lista de valores
        valor[c] = LPC_I2C->DAT;
    }
    // requisitar o evento de STOP (UM10398, 15.7.1)
    LPC_I2C->CONSET = (1 << 4);
    // limpar o bit SI (UM10398, 15.7.6)
    LPC_I2C->CONCLR = (1 << 3);
}

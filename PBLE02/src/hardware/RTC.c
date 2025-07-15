/*
 *  Created on: 5 de jul. de 2025
 *      Author: Osmar Bruno
 */

#include "../programa.h"

#define RTC_SECONDS_REG 0x00
#define RTC_MINUTES_REG 0x01
#define RTC_HOURS_REG 0x02

void getRTCData(char * data, char * config){
	I2C_Transmitir(K_ENDERECO_MCP7940, (unsigned char*)config, 1);
	I2C_Receber(K_ENDERECO_MCP7940,  (unsigned char*)data, 3);
}

static int getDezena(int numero) {
    return (numero / 10) % 10;
}

static int getUnidade(int numero) {
    return numero % 10;
}

void getRTCSegundos()
{
	char segundosData;
	unsigned int segundos;
	char address = RTC_SECONDS_REG;

	getRTCData(&segundosData, &address);

	segundos = ((segundosData & 0b01110000) >> 4) * 10;
	segundos += (segundosData & 0b00001111);

	setSeconds(segundos);
}

void setRTCSegundos(int valor)
{
	unsigned char regSegundos = 0;
	int segundos = valor;
	unsigned char data[2] = {RTC_SECONDS_REG, '0'};

	regSegundos |= 1 << 7; //liga o oscilador de cristal
	regSegundos |= ((unsigned char) getDezena(segundos) & 0b00000111) << 4;
	regSegundos |= ((unsigned char) getUnidade(segundos) & 0b00001111);

	data[1] = regSegundos;
	I2C_Transmitir(K_ENDERECO_MCP7940, &data[0], 2);
}

void getRTCMinutos()
{
	char minutosData;
	unsigned int minutos;
	char address = RTC_MINUTES_REG;

	getRTCData(&minutosData, &address);

	minutos = ((minutosData & 0b01110000) >> 4) * 10;
	minutos += (minutosData & 0b00001111);

	setMinutes(minutos);
}

void setRTCMinutos(int valor)
{
	unsigned char regMinutos = 0;
	int minutos = valor;
	unsigned char data[2] = {RTC_MINUTES_REG, '0'};

	regMinutos |= ((unsigned char) getDezena(minutos) & 0b00000111) << 4;
	regMinutos |= ((unsigned char) getUnidade(minutos) & 0b00001111);

	data[1] = regMinutos;
	I2C_Transmitir(K_ENDERECO_MCP7940, &data[0], 2);
}

void getRTCHoras()
{
	char horasData;
	unsigned int horas;
	char address = RTC_HOURS_REG;

	getRTCData(&horasData, &address);

	horas = ((horasData & 0b00110000) >> 4) * 10;
	horas += (horasData & 0b00001111);

	setHours(horas);
}

void setRTCHoras(int valor)
{
	unsigned char regHoras = 0;
	int horas = valor;
	unsigned char data[2] = {RTC_HOURS_REG, '0'};

	regHoras &= ~(1 << 6); //formato 24 horas
	regHoras |= ((unsigned char) getDezena(horas) & 0b00000011) << 4;
	regHoras |= ((unsigned char) getUnidade(horas) & 0b00001111);

	data[1] = regHoras;
	I2C_Transmitir(K_ENDERECO_MCP7940, &data[0], 2);
}

void iniciaRTC(void)
{
	setRTCSegundos(getSeconds());
	setRTCMinutos(getMinutes());
	setRTCHoras(getHours());
}

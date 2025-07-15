/*
 *  Created on: 5 de jul. de 2025
 *      Author: Osmar Bruno
 */

#ifndef RTC_H
#define RTC_H
	#include "../programa.h"
	#define K_ENDERECO_MCP7940 0x6F // Endereço em 7 bits 654 3210
	#define RTC_SECONDS_REG 0x00
	#define RTC_MINUTES_REG 0x01
	#define RTC_HOURS_REG 0x02

	void iniciaRTC(void);
	void getRTCData(char * data, char * config);
	void getRTCHoras(void);
	void getRTCSegundos(void);
	void getRTCMinutos(void);
	void setRTCHoras(int);
	void setRTCSegundos(int);
	void setRTCMinutos(int);
#endif

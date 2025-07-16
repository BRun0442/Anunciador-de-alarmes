/*
 *  Created on: 5 de jul. de 2025
 *      Author: Osmar Bruno
 */

#include "programa.h"
#include "./ctl/timer.h"

const uint32_t OscRateIn = 20000000;
volatile uint32_t millis_counter = 0;

int main(void)
{
	uint32_t last_sensor_read_time = 0;
	uint32_t last_rtc_update_time = 0;
	int valorLido = 0;

    configClock_PLL();

	iniciaSerial();
	iniciaLED();
	iniciaTeclado();
	iniciaLCD();
	iniciaADC();
    iniciaDAC();
	iniciaI2C();
	iniciaRTC();

	iniciaTimer();
	iniciaSM();


    while (1) {
		if (millis_counter - last_sensor_read_time >= 50) {
			static int i = 0;
			last_sensor_read_time = millis_counter;
			valorLido = leSensor();
			setSensorLevel(valorLido);

			//Essa linha faz o codigo nao funcionar muito bem pois pesa muito o
			//processamento do microcontrolador
			if(valorLido < getAlarmLevel_L() || valorLido > getAlarmLevel_H())
			{
				i = (i < 16) ? (i + 1) : 0;
				senoideDAC(i);
			}
		}

		if (millis_counter - last_rtc_update_time >= 1000) {
			last_rtc_update_time = millis_counter;
			if(getState() != STATE_TEMPO) {
				getRTCSegundos();
				getRTCMinutos();
				getRTCHoras();
			}

			if(valorLido < getAlarmLevel_L() || valorLido > getAlarmLevel_H())
			{
				serial_enviaString("#Alerta=Sensor fora dos parametros! - ");
				serial_enviaInt4Dig(valorLido);
				serial_enviaString(" - ");
				serial_enviaInt2Dig(getHours());
				serial_enviaString(":");
				serial_enviaInt2Dig(getMinutes());
				serial_enviaString(":");
				serial_enviaInt2Dig(getSeconds());
				serial_enviaString("#");
				serial_enviaString("\n");
			}else{
				serial_enviaString("#normal=#");
			}
		}


    	processaComandoSerial();

    	smLoop();
    }

    return 0;
}

#include <stdint.h>
#include "output.h"
#include "../programa.h"

#define NUM_IDIOMAS 2

//msgs com 16 caracteres
//1 msg por estado (apenas linha de cima)
static char * msgs[STATE_FIM][NUM_IDIOMAS] = {
    {"Alterar alarme L", "Change alarm  L"},
	{"Alterar alarme H", "Change alarm  H"},
    {"Alterar tempo   ", "Change time    "},
    {"Alterar idioma  ", "Change language"},
	{"Horario         ", "Time           "},
    {"Tensao no sensor", "Sensor voltage "},
	{"CUIDADO!        ", "WARNING!       "}
};

void outputInit(void) {
	iniciaLCD();
}

void outputPrint(int numTela, int idioma) {

    if (numTela == STATE_TEMPO) {
        LCD_comando(0x80);
        LCD_string(msgs[numTela][idioma]);
        LCD_comando(0xC0);
		LCD_int2Dig(getHours());
		LCD_string(":");
		LCD_int2Dig(getMinutes());
		LCD_string(":");
		LCD_int2Dig(getSeconds());
		LCD_string("        ");
    }

    if (numTela == STATE_ALARME_L) {
        float nivelAlarme = getAlarmLevel_L();
        char tensao[4] = {0};

        floatParaString(3.3 * nivelAlarme / (1023 * GANHO_AMPOP), tensao);

        LCD_comando(0x80);
        LCD_string(msgs[numTela][idioma]);
        LCD_comando(0xC0);
        LCD_int((int) nivelAlarme);
        LCD_string("      ");
        LCD_string(tensao);
        LCD_string("V");
    }

    if (numTela == STATE_ALARME_H) {
        float nivelAlarme = getAlarmLevel_H();
        char tensao[4] = {0};

        floatParaString(3.3 * nivelAlarme / (1023 * GANHO_AMPOP), tensao);

        LCD_comando(0x80);
        LCD_string(msgs[numTela][idioma]);
        LCD_comando(0xC0);
        LCD_int((int) nivelAlarme);
        LCD_string("      ");
        LCD_string(tensao);
        LCD_string("V");
    }

    if (numTela == STATE_IDIOMA) {
        LCD_comando(0x80);
        LCD_string(msgs[numTela][idioma]);
        LCD_comando(0xC0);
        if (getLanguage() == 0) {
            LCD_string("Portugues       ");
        }
        if (getLanguage() == 1) {
            LCD_string("English         ");
        }
    }

    if (numTela == STATE_HORAS) {
		LCD_comando(0x80);
		LCD_string(msgs[numTela][idioma]);
		LCD_comando(0xC0);
		LCD_int2Dig(getHours());
		LCD_string(":");
		LCD_int2Dig(getMinutes());
		LCD_string(":");
		LCD_int2Dig(getSeconds());
		LCD_string("        ");
	}

    if (numTela == STATE_SENSOR) {
		float tensaoSensor = getSensorLevel();
		char tensao[4] = {0};

		floatParaString((float) (3.3 * tensaoSensor / (1023 * GANHO_AMPOP)), tensao);

		LCD_comando(0x80);
		LCD_string(msgs[numTela][idioma]);
		LCD_comando(0xC0);
		LCD_int((int) tensaoSensor);
		LCD_string("      ");
		LCD_string(tensao);
		LCD_string("V");
	}

    if (numTela == STATE_OUT_OF_RANGE) {
		float tensaoSensor = getSensorLevel();
		char tensao[4] = {0};

		floatParaString((float) (3.3 * tensaoSensor / (1023 * GANHO_AMPOP)), tensao);

		LCD_comando(0x80);
		LCD_string(msgs[numTela][idioma]);
		LCD_comando(0xC0);

		if(tensaoSensor < getAlarmLevel_L())
		{
			LCD_string("Abaixo:");
		}else if(tensaoSensor > getAlarmLevel_H())
		{
			LCD_string("Acima:");
		}

		LCD_int((int) tensaoSensor);
		LCD_string("/");
		LCD_string(tensao);
		LCD_string("V");
	}
}

#include <stdint.h>
#include "var.h"
#include "stateMachine.h"
#include "event.h"
#include "output.h"
#include "../programa.h"

void iniciaSM(void) {
    setState(STATE_TEMPO);
    varInit();
}

void smLoop(void) {
    unsigned char evento;

    //maquina de estados
    evento = eventRead();

    switch (getState()) {
        case STATE_ALARME_L:
            //execucao de atividade
            if (evento == EV_RIGHT) {
                setAlarmLevel_L(getAlarmLevel_L() + 1);
            }
            if (evento == EV_LEFT) {
                setAlarmLevel_L(getAlarmLevel_L() - 1);
            }

            //gestao da maquina de estado
            if (evento == EV_ENTER) {
                setState(STATE_ALARME_H);
            }

            if (evento == EV_UP) {
				setState(STATE_TEMPO);
			}
            break;

        case STATE_ALARME_H:
                    //execucao de atividade
			if (evento == EV_RIGHT) {
				setAlarmLevel_H(getAlarmLevel_H() + 1);
			}
			if (evento == EV_LEFT) {
				setAlarmLevel_H(getAlarmLevel_H() - 1);
			}

			//gestao da maquina de estado
			if (evento == EV_ENTER) {
				setState(STATE_IDIOMA);
			}

			if (evento == EV_UP) {
				setState(STATE_TEMPO);
			}
			break;

        case STATE_TEMPO:
            //execucao de atividade
        	int s = (int)getSeconds();
        	int m = (int)getMinutes();
        	int h = (int)getHours();


            if (evento == EV_RIGHT) {
				s++;
            }

            if (evento == EV_LEFT) {
            	s--;
            }

            if (evento == EV_UP) {
            	m++;
			}

			if (evento == EV_DOWN) {
				m--;
			}

			ajustaTempo(&s, &m, &h);

            //gestao da maquina de estado
            if (evento == EV_ENTER) {
    			ajustaTempo(&s, &m, &h);

            	setRTCSegundos(getSeconds());
				setRTCMinutos(getMinutes());
				setRTCHoras(getHours());

                setState(STATE_IDIOMA);
            }

            break;

        case STATE_IDIOMA:

            //execucao de atividade
            if (evento == EV_RIGHT) {
                setLanguage(getLanguage() + 1);
            }
            if (evento == EV_LEFT) {
                setLanguage(getLanguage() - 1);
            }

            //gestao da maquina de estado
            if (evento == EV_ENTER) {
                setState(STATE_HORAS);
            }
            break;

        case STATE_HORAS:
			//gestao da maquina de estado
			if (evento == EV_ENTER) {
				setState(STATE_SENSOR);
			}
			break;

        case STATE_SENSOR:
			//gestao da maquina de estado
			if (evento == EV_ENTER) {
				setState(STATE_ALARME_L);
			}
			break;



        case STATE_OUT_OF_RANGE:
        	if(evento != EV_OUT_OF_RANGE)
        	{
        		setState(STATE_SENSOR);
        	}
        	break;
    }

    outputPrint(getState(), getLanguage());
}

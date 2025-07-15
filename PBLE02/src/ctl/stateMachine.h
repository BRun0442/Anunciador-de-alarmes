#ifndef STATEMACHINE_H
    #define	STATEMACHINE_H

    //estados da maquina de Estados
    enum {
        STATE_ALARME_L,
		STATE_ALARME_H,
        STATE_TEMPO,
        STATE_IDIOMA,
		STATE_HORAS,
		STATE_SENSOR,
		STATE_OUT_OF_RANGE,
        STATE_FIM,
    };

    void iniciaSM(void);
    void smLoop(void);
#endif

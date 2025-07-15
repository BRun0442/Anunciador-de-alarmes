#include "event.h"
#include "../programa.h"

void eventInit(void) {
    iniciaTeclado();
}

unsigned int eventRead(void) {
    int ev = EV_NOEVENT;
    int sensor_Level = getSensorLevel();

    if(lerBotao("right")) {
        ev = EV_RIGHT;
    }
    if(lerBotao("left")) {
        ev = EV_LEFT;
    }

    if(lerBotao("enter")) {
        ev = EV_ENTER;
    }

    if(lerBotao("up")) {
		ev = EV_UP;
	}

	if(lerBotao("down")) {
		ev = EV_DOWN;
	}

	if(sensor_Level < getAlarmLevel_L() || sensor_Level > getAlarmLevel_H())
	{
		setState(STATE_OUT_OF_RANGE);
		ev = EV_OUT_OF_RANGE;
		toggleLED(3);
	}else {
		desligaLED(3);
	}

    return ev;
}

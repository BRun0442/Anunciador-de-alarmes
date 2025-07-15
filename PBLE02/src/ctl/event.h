#ifndef EVENT_H
    #define	EVENT_H
    
    enum{
        EV_UP,
        EV_DOWN,
        EV_LEFT,
        EV_RIGHT,
        EV_ENTER,
		EV_OUT_OF_RANGE,
        EV_NOEVENT
    };
    void eventInit(void);
    unsigned int eventRead(void);
#endif

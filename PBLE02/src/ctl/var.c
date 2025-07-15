#include "var.h"
#include "../util.h"
#include "../hardware/RTC.h"

//variaveis a serem armazenadas
static char state;
static char language;
static int time;
static unsigned int alarmLevel_H;
static unsigned int alarmLevel_L;
static unsigned int sensorLevel;
static float sensorLevel_V;

static unsigned int seconds;
static unsigned int minutes;
static unsigned int hours;

void varInit(void) {
    state = 0;
    time = 1000;
    alarmLevel_H = 350;
    alarmLevel_L = 250;

    seconds = 0;
    minutes = 58;
    hours = 22;

	setRTCSegundos(seconds);
	setRTCMinutos(minutes);
	setRTCHoras(hours);
}


char getState(void) {
    return state;
}
void setState(char newState) {
    state = newState;
}


int getTime(void) {
    return time;
}
void setTime(int newTime) {
    time = newTime;
}


int getAlarmLevel_H(void) {
    return alarmLevel_H;
}
void setAlarmLevel_H(int newAlarmLevel) {
    alarmLevel_H = newAlarmLevel;
}


int getAlarmLevel_L(void) {
    return alarmLevel_L;
}
void setAlarmLevel_L(int newAlarmLevel) {
    alarmLevel_L = newAlarmLevel;
}


int getSensorLevel(void)
{
	return sensorLevel;
}
void setSensorLevel(int newSensorLevel) {
	sensorLevel_V = 3.3 * newSensorLevel / (1023.0 * GANHO_AMPOP);
	sensorLevel = newSensorLevel;
}

float getSensorLevel_V(void)
{
	return sensorLevel_V;
}

char getLanguage(void){
    return language;
}
void setLanguage(char newLanguage){
    //so tem 2 linguas
    //usando resto pra evitar colocar valor errado
    language = newLanguage%2;
}


int getSeconds(void) {
    return seconds;
}
void setSeconds(int newSeconds) {
    seconds = newSeconds;
}


int getMinutes(void) {
    return minutes;
}
void setMinutes(int newMinutes) {
    minutes = newMinutes;
}


int getHours(void) {
    return hours;
}
void setHours(int newHours) {
    hours = newHours;
}

void ajustaTempo(int* s, int* m, int* h)
{
    while (*s >= 60) { *s -= 60; (*m)++; }
    while (*s < 0)   { *s += 60; (*m)--; }

    while (*m >= 60) { *m -= 60; (*h)++; }
    while (*m < 0)   { *m += 60; (*h)--; }

    while (*h >= 24) *h -= 24;
    while (*h < 0)   *h += 24;

    int seg = *s;
    int min = *m;
    int hor = *h;

    setSeconds(seg);
    setMinutes(min);
    setHours(hor);
}

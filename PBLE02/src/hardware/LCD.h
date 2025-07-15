/*
 *  Created on: 5 de jul. de 2025
 *      Author: Osmar Bruno
 */

#ifndef LCD_H
#define LCD_H
	#include "../programa.h"
    void bit_set(int port, int pin);
    void bit_clr(int port, int pin);
    void delay_ms(uint32_t ms);
    void iniciaLCD();
    void LCD_comando(char v_cComando);
    void LCD_caractere(char v_cCaractere);
    void gravaDadosNoDisplay(char v_cComando);
    void LCD_string(const char *str);
    void LCD_int(int);
    void LCD_int2Dig(int);
#endif

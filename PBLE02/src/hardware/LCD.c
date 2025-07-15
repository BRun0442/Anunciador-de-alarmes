/*
 *  Created on: 5 de jul. de 2025
 *      Author: Osmar Bruno
 */

#include "../programa.h"

// Definições dos pinos de controle do LCD
#define PORTA_ENABLE 1
#define PINO_ENABLE 16
#define PORTA_RW 1
#define PORTA_RS 1
#define PINO_RS 29
#define PINO_RW 25
//----------------------------------------


// Definições dos pinos de dados do LCD
#define PORTA_DB4 0
#define PORTA_DB5 1
#define PORTA_DB6 0
#define PORTA_DB7 1

#define PINO_DB4 17
#define PINO_DB5 15
#define PINO_DB6 23
#define PINO_DB7 22
//----------------------------------------

// Mover para a segunda linha
//LCD_comando(0xC0);

// Função para colocar o pino em nível alto
void bit_set(int port, int pin)
{
    Chip_GPIO_SetPinOutHigh(LPC_GPIO, port, pin);
}

// Função para colocar o pino em nível baixo
void bit_clr(int port, int pin)
{
    Chip_GPIO_SetPinOutLow(LPC_GPIO, port, pin);
}

// Função de atraso usando for (pouco preciso, mas simples)
void delay_ms(uint32_t ms)
{
    for (uint32_t i = 0; i < ms * 3000; i++) {
        __NOP();
    }
}

// Função para enviar os dados para o display
void gravaDadosNoDisplay(char v_cDado)
{
    // Primeiro nibble de dados
    Chip_GPIO_SetPinState(LPC_GPIO, PORTA_DB7, PINO_DB7, (v_cDado >> 7) & 0x01);
    Chip_GPIO_SetPinState(LPC_GPIO, PORTA_DB6, PINO_DB6, (v_cDado >> 6) & 0x01);
    Chip_GPIO_SetPinState(LPC_GPIO, PORTA_DB5, PINO_DB5, (v_cDado >> 5) & 0x01);
    Chip_GPIO_SetPinState(LPC_GPIO, PORTA_DB4, PINO_DB4, (v_cDado >> 4) & 0x01);
    delay_ms(1);

    // Pulso de habilitação
    bit_set(PORTA_ENABLE, PINO_ENABLE);
    delay_ms(1);
    bit_clr(PORTA_ENABLE, PINO_ENABLE);

    // Segundo nibble de dados
    Chip_GPIO_SetPinState(LPC_GPIO, PORTA_DB7, PINO_DB7, (v_cDado >> 3) & 0x01);
    Chip_GPIO_SetPinState(LPC_GPIO, PORTA_DB6, PINO_DB6, (v_cDado >> 2) & 0x01);
    Chip_GPIO_SetPinState(LPC_GPIO, PORTA_DB5, PINO_DB5, (v_cDado >> 1) & 0x01);
    Chip_GPIO_SetPinState(LPC_GPIO, PORTA_DB4, PINO_DB4, (v_cDado >> 0) & 0x01);
    delay_ms(1);

    // Pulso de habilitação
    bit_set(PORTA_ENABLE, PINO_ENABLE);
    delay_ms(1);
    bit_clr(PORTA_ENABLE, PINO_ENABLE);
}

// Função para enviar um comando ao LCD
void LCD_comando(char v_cComando)
{
    bit_clr(PORTA_RS, PINO_RS);  // Indica que é comando
    gravaDadosNoDisplay(v_cComando);
}

// Função para iniciar o LCD
void iniciaLCD()
{
    // Configurar os pinos de controle do LCD como saída
    LPC_GPIO->DIR[PORTA_ENABLE] |= (1 << PINO_ENABLE);
    LPC_GPIO->DIR[PORTA_RS] |= (1 << PINO_RS);
    LPC_GPIO->DIR[PORTA_RW] |= (1 << PINO_RW);

    // Configurar os pinos de dados do LCD como saída
    LPC_GPIO->DIR[PORTA_DB4] |= (1 << PINO_DB4);
    LPC_GPIO->DIR[PORTA_DB5] |= (1 << PINO_DB5);
    LPC_GPIO->DIR[PORTA_DB6] |= (1 << PINO_DB6);
    LPC_GPIO->DIR[PORTA_DB7] |= (1 << PINO_DB7);

    // Pequeno atraso para estabilização
    delay_ms(1000);

    // Inicializar os pinos de controle e dados do LCD
    bit_clr(PORTA_ENABLE, PINO_ENABLE);
    bit_clr(PORTA_RS, PINO_RS);

    // Esperar pela inicialização do visor
    delay_ms(1000);

    // Sequência de inicialização conforme datasheet
    LCD_comando(0x03);
    delay_ms(5);
    LCD_comando(0x03);
    delay_ms(5);
    LCD_comando(0x03);
    delay_ms(5);
    LCD_comando(0x02);
    delay_ms(20);

    // Configurar o visor: ligar, com cursor piscante
    LCD_comando(0x0F);
    delay_ms(20);

    // Limpar o visor
    LCD_comando(0x01);
    delay_ms(20);

    // Incremento automático do cursor
    LCD_comando(0x06);
    delay_ms(20);
}

// Função para enviar um caractere ao LCD
void LCD_caractere(char v_cCaractere)
{
    bit_set(PORTA_RS, PINO_RS);  // Indica que é dado
    gravaDadosNoDisplay(v_cCaractere);
}

// Função para escrever uma string no LCD
void LCD_string(const char *str)
{
    while (*str) {
        LCD_caractere(*str);
        str++;
    }
}

void LCD_int(int val) {
    if (val < 0) {
        val = val * (-1);
        LCD_caractere('-');
    }
    LCD_caractere((val / 10000) % 10 + 48);
    LCD_caractere((val / 1000) % 10 + 48);
    LCD_caractere((val / 100) % 10 + 48);
    LCD_caractere((val / 10) % 10 + 48);
    LCD_caractere((val / 1) % 10 + 48);

}

void LCD_int2Dig(int val) {
    if (val < 0) {
        val = val * (-1);
        LCD_caractere('-');
    }

    LCD_caractere((val / 10) % 10 + 48);
    LCD_caractere((val / 1) % 10 + 48);
}

/*
 *  Created on: 5 de jul. de 2025
 *      Author: Osmar Bruno
 */

#include "../programa.h"

void iniciaTeclado(void)
{
    Chip_GPIO_SetPinDIR(LPC_GPIO, 0, 8, 0); //RIGHT
	Chip_GPIO_SetPinDIR(LPC_GPIO, 0, 9, 0); //UP
	Chip_GPIO_SetPinDIR(LPC_GPIO, 0, 22, 0); //LEFT
	Chip_GPIO_SetPinDIR(LPC_GPIO, 1, 31, 0); //ENTER
	Chip_GPIO_SetPinDIR(LPC_GPIO, 1, 21, 0); //DOWN
}

int lerBotaoPin(int port, int pin) {return !Chip_GPIO_GetPinState(LPC_GPIO, port, pin);}

int lerBotao(const char *botao)
{
    if(strcmp(botao, "up") == 0 || strcmp(botao, "UP") == 0)
    {
        return !Chip_GPIO_GetPinState(LPC_GPIO, 0, 9); //UP
    }
    else if(strcmp(botao, "down") == 0 || strcmp(botao, "DOWN") == 0)
    {
        return !Chip_GPIO_GetPinState(LPC_GPIO, 1, 21); //DOWN
    }
    else if(strcmp(botao, "left") == 0 || strcmp(botao, "LEFT") == 0)
    {
        return !Chip_GPIO_GetPinState(LPC_GPIO, 0, 22); //LEFT
    }
    else if(strcmp(botao, "right") == 0 || strcmp(botao, "RIGHT") == 0)
    {
        return !Chip_GPIO_GetPinState(LPC_GPIO, 0, 8); //RIGHT
    }
    else if(strcmp(botao, "enter") == 0 || strcmp(botao, "ENTER") == 0)
    {
        return !Chip_GPIO_GetPinState(LPC_GPIO, 1, 31); //ENTER
    }

    return -1;
}

void botaoLigaLED(void)
{
    //Le o botao enter
    if(lerBotaoPin(1, 31))
    {
        ligaLED(0);
        ligaLED(1);
        ligaLED(2);
        ligaLED(3);
    }else{

        //Le o botao down
        if(lerBotaoPin(1, 21))
        {
            ligaLED(0);
        }else {
            desligaLED(0);
        }

        //Le o botao left
        if(lerBotaoPin(0, 22))
        {
            ligaLED(1);
        }else {
            desligaLED(1);
        }

        //Le o botao up
        if(lerBotaoPin(0, 9))
        {
            ligaLED(2);
        }else {
            desligaLED(2);
        }

        //Le o botao right
        if(lerBotaoPin(0, 8))
        {
            ligaLED(3);
        }else {
            desligaLED(3);
        }
    }
}

/*
 *  Created on: 5 de jul. de 2025
 *      Author: Osmar Bruno
 */

#include "../programa.h"

#define UART_SRB_SIZE 128    /* Send */
#define UART_RRB_SIZE 32

RINGBUFF_T txring, rxring;
uint8_t rxbuff[UART_RRB_SIZE], txbuff[UART_SRB_SIZE];

static void Init_UART_PinMux(void)
{
#if (defined(BOARD_NXP_XPRESSO_11U14) || defined(BOARD_NGX_BLUEBOARD_11U24))
    Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 18, IOCON_FUNC1 | IOCON_MODE_INACT);    /* PIO0_18 used for RXD */
    Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 19, IOCON_FUNC1 | IOCON_MODE_INACT);    /* PIO0_19 used for TXD */
#elif (defined(BOARD_NXP_XPRESSO_11C24) || defined(BOARD_MCORE48_1125))
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_6, (IOCON_FUNC1 | IOCON_MODE_INACT));/* RXD */
    Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_7, (IOCON_FUNC1 | IOCON_MODE_INACT));/* TXD */
#else
#error "No Pin muxing defined for UART operation"
#endif
}

void UART_IRQHandler(void)
{
	/* Want to handle any errors? Do it here. */

	/* Use default ring buffer handler. Override this with your own
	   code if you need more capability. */
	Chip_UART_IRQRBHandler(LPC_USART, &rxring, &txring);
}

void iniciaSerial(void)
{
	Init_UART_PinMux();
    //Board_LED_Set(0, false);

    //Chip_UART_Init(LPC_USART);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_UART0);
	Chip_Clock_SetUARTClockDiv(1);

    Chip_UART_SetBaud(LPC_USART, 115200);
    Chip_UART_ConfigData(LPC_USART, (UART_LCR_WLEN8 | UART_LCR_SBS_1BIT));
    Chip_UART_SetupFIFOS(LPC_USART, (UART_FCR_FIFO_EN | UART_FCR_TRG_LEV2));
    Chip_UART_TXEnable(LPC_USART);

    RingBuffer_Init(&rxring, rxbuff, 1, UART_RRB_SIZE);
    RingBuffer_Init(&txring, txbuff, 1, UART_SRB_SIZE);

    //Interrupcao UART
    Chip_UART_IntEnable(LPC_USART, (UART_IER_RBRINT | UART_IER_RLSINT));
    NVIC_SetPriority(UART0_IRQn, 1);
    NVIC_EnableIRQ(UART0_IRQn);
}

void desligaSerial(void)
{
	NVIC_DisableIRQ(UART0_IRQn);
    Chip_UART_DeInit(LPC_USART);
}

uint8_t dadoRecebido(void)
{
    uint8_t key = 0;
    //int bytes;

	Chip_UART_ReadRB(LPC_USART, &rxring, &key, 1);

	return key;
}

void enviaDado(uint8_t dado)
{
	uint8_t key = dado;

	Chip_UART_SendRB(LPC_USART, &txring, &key, 1);
}

void serialLigaLED()
{
	static uint8_t key;

	key = dadoRecebido();

	if(key > 0)
	{
		switch(key) {
			case '0':
				toggleLED(0);
				break;

			case '1':
				toggleLED(1);
				break;

			case '2':
				toggleLED(2);
				break;

			case '3':
				toggleLED(3);
				break;

			default:
				break;
		}

		enviaDado(key);
	}
}

void serial_enviaString(const char *str)
{
    while (*str) {
        enviaDado(*str++);
    }
}

void serial_enviaInteiro(int val)
{
    char buffer[11]; // Suporta até um inteiro de 32 bits com sinal
    int i = 0;

    if (val == 0) {
        enviaDado('0');
        return;
    }

    if (val < 0) {
        enviaDado('-');
        val = -val;
    }

    while (val > 0) {
        buffer[i++] = (val % 10) + '0';
        val /= 10;
    }

    while (i > 0) {
        enviaDado(buffer[--i]);
    }
}

void serial_enviaInt2Dig(int val)
{
    if (val < 0) val = 0;
    enviaDado((val / 10) % 10 + '0');
    enviaDado((val % 10) + '0');
}

void serial_enviaInt4Dig(int val)
{
    if (val < 0) val = 0; // Tratamento para valores negativos
    enviaDado((val / 1000) % 10 + '0');
    enviaDado((val / 100)  % 10 + '0');
    enviaDado((val / 10)   % 10 + '0');
    enviaDado(val % 10 + '0');
}

void processaComandoSerial(void)
{
    static char command_buffer[32];
    static int buffer_index = 0;
    static int comando_ativo = 0;
    uint8_t byte_lido;

    while (Chip_UART_ReadRB(LPC_USART, &rxring, &byte_lido, 1) > 0)
    {
        enviaDado(byte_lido); // Eco do caractere recebido

        if (byte_lido == '(') {
            buffer_index = 0;
            comando_ativo = 1;
            continue;
        }

        if (comando_ativo) {
            if (byte_lido == ')') {
                command_buffer[buffer_index] = '\0';
                comando_ativo = 0;

                char lower_cmd[32];
                int k = 0;
                while(command_buffer[k] != '\0' && k < 31) {
                    char c = command_buffer[k];
                    if (c >= 'A' && c <= 'Z') c += 'a' - 'A';
                    lower_cmd[k] = c;
                    k++;
                }
                lower_cmd[k] = '\0';

                if (lower_cmd[0] == 'g' && lower_cmd[1] == 'e' && lower_cmd[2] == 't') {
                    char *cmd_body = lower_cmd + 3;

                    if (cmd_body[0] == 'a' && cmd_body[1] == 'l' && cmd_body[2] == 'a' && cmd_body[3] == 'r' && cmd_body[4] == 'm' && cmd_body[5] == 'e' && cmd_body[6] == 'l' && cmd_body[7] == 'o' && cmd_body[8] == 'w' && cmd_body[9] == '\0') {
                        serial_enviaString("#alarmeLow=");
                        serial_enviaInteiro(getAlarmLevel_L());
                        serial_enviaString("#");
                    }
                    else if (cmd_body[0] == 'a' && cmd_body[1] == 'l' && cmd_body[2] == 'a' && cmd_body[3] == 'r' && cmd_body[4] == 'm' && cmd_body[5] == 'e' && cmd_body[6] == 'h' && cmd_body[7] == 'i' && cmd_body[8] == 'g' && cmd_body[9] == 'h' && cmd_body[10] == '\0') {
                        serial_enviaString("#alarmeHigh=");
                        serial_enviaInteiro(getAlarmLevel_H());
                        serial_enviaString("#");
                    }
                    else if (cmd_body[0] == 't' && cmd_body[1] == 'i' && cmd_body[2] == 'm' && cmd_body[3] == 'e' && cmd_body[4] == '\0') {
                        serial_enviaString("#time=");
                        serial_enviaInt2Dig(getHours());
                        serial_enviaString(":");
                        serial_enviaInt2Dig(getMinutes());
                        serial_enviaString(":");
                        serial_enviaInt2Dig(getSeconds());
                        serial_enviaString("#");
                    }

                    else if (cmd_body[0] == 's' && cmd_body[1] == 'e' && cmd_body[2] == 'n' && cmd_body[3] == 's' && cmd_body[4] == 'o' && cmd_body[5] == 'r' && cmd_body[6] == '\0') {
                        float valor_raw = getSensorLevel();
                    	char tensao[4];
                        floatParaString(3.3 * valor_raw / (1023 * GANHO_AMPOP), tensao);

                        serial_enviaString("#sensor=");
                        serial_enviaInt4Dig((int) valor_raw);
                        serial_enviaString("/");
                        serial_enviaString(tensao);
                        serial_enviaString("V#");
                    }
                } else {
                    // Lógica para comandos SET (inalterada)
                    int i = 0; int match = 1;
                    const char *prefixo_low = "alarmelow:";
                    while (prefixo_low[i] != '\0') { if (lower_cmd[i] != prefixo_low[i]) { match = 0; break; } i++; }
                    if (match) {
                        int valor_alarme = 0;
                        while (command_buffer[i] >= '0' && command_buffer[i] <= '9') { valor_alarme = (valor_alarme * 10) + (command_buffer[i] - '0'); i++; }
                        setAlarmLevel_L(valor_alarme);
                    } else {
                        i = 0; match = 1;
                        const char *prefixo_high = "alarmehigh:";
                        while (prefixo_high[i] != '\0') { if (lower_cmd[i] != prefixo_high[i]) { match = 0; break; } i++; }
                        if (match) {
                            int valor_alarme = 0;
                            while (command_buffer[i] >= '0' && command_buffer[i] <= '9') { valor_alarme = (valor_alarme * 10) + (command_buffer[i] - '0'); i++; }
                            setAlarmLevel_H(valor_alarme);
                        } else {
                            int horas = 0, minutos = 0, segundos = 0, parte = 0; i = 0;
                            while (command_buffer[i] != '\0') {
                                if (command_buffer[i] >= '0' && command_buffer[i] <= '9') {
                                    if (parte == 0) horas = (horas * 10) + (command_buffer[i] - '0');
                                    else if (parte == 1) minutos = (minutos * 10) + (command_buffer[i] - '0');
                                    else if (parte == 2) segundos = (segundos * 10) + (command_buffer[i] - '0');
                                } else if (command_buffer[i] == ':') { parte++; }
                                i++;
                            }
                            if (parte == 2 && horas < 24 && minutos < 60 && segundos < 60) {
                                setRTCHoras(horas); setRTCMinutos(minutos); setRTCSegundos(segundos);
                            }
                        }
                    }
                }
            } else {
                if (buffer_index < (sizeof(command_buffer) - 1)) {
                    command_buffer[buffer_index++] = byte_lido;
                } else {
                    comando_ativo = 0;
                }
            }
        }
    }
}

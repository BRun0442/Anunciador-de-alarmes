/*
 *  Created on: 5 de jul. de 2025
 *      Author: Osmar Bruno
 */

/*
 *
 *
 * #include "chip.h"

#define IAP_LOCATION 0x1FFF1FF1
#define PAGE_SIZE    1024 // Tamanho da página da flash (1 KB)
#define FLASH_PAGE   28   // Escolha uma página segura da flash (ex: 28)
#define FLASH_ADDR   (FLASH_PAGE * PAGE_SIZE)

typedef void (*IAP)(unsigned int[], unsigned int[]);
IAP iap_entry = (IAP) IAP_LOCATION;


uint32_t valores_para_salvar[4] = {123, 456, 789, 101112}; //
uint32_t valores_lidos[4];

// Função para apagar uma página da flash
void apagar_pagina_flash(uint32_t page) {
    unsigned int cmd[5], res[4];

    // Preparar a página
    cmd[0] = 50; // Prepare sector for write operation
    cmd[1] = page;
    cmd[2] = page;
    iap_entry(cmd, res);

    // Apagar a página
    cmd[0] = 52; // Erase page
    cmd[1] = page;
    cmd[2] = page;
    cmd[3] = SystemCoreClock / 1000;
    iap_entry(cmd, res);
}

// Função para gravar na flash
void escrever_na_flash(uint32_t addr, uint32_t *dados, uint32_t tamanho) {
    unsigned int cmd[5], res[4];

    // Preparar o setor
    cmd[0] = 50;
    cmd[1] = addr / PAGE_SIZE;
    cmd[2] = addr / PAGE_SIZE;
    iap_entry(cmd, res);

    // Escrever
    cmd[0] = 51; // Copy RAM to flash
    cmd[1] = addr;
    cmd[2] = (uint32_t)dados;
    cmd[3] = tamanho;
    cmd[4] = SystemCoreClock / 1000;
    iap_entry(cmd, res);
}

// Função para salvar os 4 valores
void salvar_valores_na_flash(void) {
    // Apagar a página antes
    apagar_pagina_flash(FLASH_PAGE);

    // Escrever os dados (deve ser múltiplo de 256 bytes)
    uint32_t buffer[64] = {0}; // 64 * 4 bytes = 256 bytes
    buffer[0] = valores_para_salvar[0];
    buffer[1] = valores_para_salvar[1];
    buffer[2] = valores_para_salvar[2];
    buffer[3] = valores_para_salvar[3];

    escrever_na_flash(FLASH_ADDR, buffer, 256);
}

// Função para ler os valores
void ler_valores_da_flash(void) {
    uint32_t *p = (uint32_t*)FLASH_ADDR;
    for (int i = 0; i < 4; i++) {
        valores_lidos[i] = p[i];
    }
}*
 *
 *
 */

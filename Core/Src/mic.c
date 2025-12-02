#include "main.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>
#include "mic.h"

/* GLOBAL VARS */
extern I2S_HandleTypeDef hi2s1;

/* VARIABLES */
int16_t mic_dma_buff[MIC_BUFF_SIZE * 2] = {0};

/* FUNCTIONS */

// Initialize capturing mic input
void mic_init() {
    log_init();
    HAL_I2S_Receive_DMA(&hi2s1, (uint16_t *) mic_dma_buff, MIC_BUFF_SIZE * 2);
}

// Stuff to do once mic buffer is filled
void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s) {
    log_data(mic_dma_buff);
}

void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s) {
    log_data(&mic_dma_buff[MIC_BUFF_SIZE]);
}

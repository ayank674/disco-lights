#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include "mic.h"
#include "utils.h"

/* GLOBAL VARS */
extern I2S_HandleTypeDef hi2s1;

/* VARIABLES */
int16_t mic_dma_buff[MIC_BUFF_SIZE * 2] = {0};

/* FUNCTIONS */

// Initialize capturing mic input
void mic_init() {
    HAL_I2S_Receive_DMA(&hi2s1, (uint16_t *) mic_dma_buff, MIC_BUFF_SIZE * 2);
}

// Stuff to do once mic buffer is filled. Ideally, change LED brightness
void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s) {
    
}

void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s) {
}

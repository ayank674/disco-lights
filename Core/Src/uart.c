#include "main.h"
#include "mic.h"
#include "stm32f7xx_hal_def.h"
#include "stm32f7xx_hal_uart.h"
#include <stdint.h>
#include <stdio.h>


/* GLOBAL VARS */
extern UART_HandleTypeDef huart3;

/* VARIABLES */
uint32_t uart_rx_cmd = 0;
uint8_t volatile is_host_ready = 0; // Flag signalling if host computer ready to receive signal
int16_t uart_dma_tx_buff[MIC_BUFF_SIZE / 2] = {0};
uint8_t uart_dma_transfer_done = 1;

/* FUNCTIONS */

// Transmits data via UART
void transmit(uint8_t *tx_data, uint16_t length) {
    if (uart_dma_transfer_done && is_host_ready) {
        uart_dma_transfer_done = 0;
        HAL_UART_Transmit_DMA(&huart3, tx_data, length);
    }
}

// Logs data to COMM Port of host device
void log_data(int16_t *data) {
    if (!uart_dma_transfer_done || !is_host_ready) return; // First wait for previous transfer to complete / sync byte
    uint16_t idx = 0;
    for (int i = 0; i < MIC_BUFF_SIZE; i+=2) {
        uart_dma_tx_buff[idx++] = data[i];
    }
    transmit((uint8_t *) uart_dma_tx_buff, 2 * idx);
}

// Initializes receive buffer for logging data
void log_init() {
    HAL_UART_Receive_IT(&huart3, &uart_rx_cmd, 4);
}

// Set flag after uart transfer is complete
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    uart_dma_transfer_done = 1;
}

// Set flag after sync byte received
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (uart_rx_cmd == 0x54525453) {
        is_host_ready = 1;
    } else if (uart_rx_cmd == 0x504F5453) {
        is_host_ready = 0;
    }
    HAL_UART_Receive_IT(&huart3, (uint8_t *) &uart_rx_cmd, 4);
}

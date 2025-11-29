#include "main.h"
#include "led.h"
#include "stm32f7xx_hal_tim.h"
#include "utils.h"

/* STRUCTS */
// Represent a single pixel
typedef union {
  struct {
    uint8_t b;
    uint8_t r;
    uint8_t g;
  } color;
  uint32_t data;
} PixelRGB_t;

/* DEFINES */
// NEOPIXEL LED
#define NEOPIXEL_ZERO 29
#define NEOPIXEL_ONE 58
#define NEOPIXEL_COLORS 3
#define NUM_PIXELS 30
#define LED_DMA_BUFF_SIZE (NUM_PIXELS * NEOPIXEL_COLORS * 8) + 80

/* GLOBAL VARS */
extern TIM_HandleTypeDef htim1;

/* VARIABLES */
PixelRGB_t pixels[NUM_PIXELS] = {0};
uint32_t led_dma_buff[LED_DMA_BUFF_SIZE] = {0};
volatile uint8_t led_dma_done = 1;


/* FUNCTIONS */
// Refresh the LED with buffer
void led_refresh() {
    if (led_dma_done) {
        HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_3, led_dma_buff, LED_DMA_BUFF_SIZE);
    }
}

// Called after led dma transfer is complete
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
  HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_3);
  led_dma_done = 1;
}

// Sets a single pixel value
void set_one_pixel(uint8_t r, uint8_t g, uint8_t b, int idx) {
    pixels[idx].color.r = r;
    pixels[idx].color.g = g;
    pixels[idx].color.b = b;
}

// Sets all pixels to a particular value
void set_all_pixels(uint8_t r, uint8_t g, uint8_t b) {
	for (int idx = 0; idx < NUM_PIXELS; idx ++) {
		set_one_pixel(r, g, b, idx);
	}
    set_buffer();
}

// Sets all the pixels to random color of specified brightness. brightness is 0-255
void set_all_pixels_random(uint8_t brightness) {
    uint8_t r, g, b;
    random_color(brightness, &r, &g, &b);
    set_all_pixels(r, g, b);
}

// Sets the PWM DMA buffer from pixel values
void set_buffer() {
  uint32_t *p_buff = led_dma_buff;
  for (int i = 0; i < NUM_PIXELS; i++) {
    // Loopeing through each pixel's color bits
    for (int j = NEOPIXEL_COLORS * 8 - 1; j >= 0; j--) {
      *p_buff = (pixels[i].data >> j) & 0x01 ? NEOPIXEL_ONE : NEOPIXEL_ZERO; // Set duty cycle from pixel bit
      p_buff++;
    }
  }
}

#include <stdint.h>

/* FUNCTION PROTOTYPES */
void set_one_pixel(uint8_t r, uint8_t g, uint8_t b, int idx);
void set_all_pixels(uint8_t r, uint8_t g, uint8_t b);
void set_all_pixels_random(uint8_t brightness);
void set_buffer();
void led_refresh();

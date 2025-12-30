#include "led.h"
#include "main.h"
#include "mic.h"
#include "utils.h"
#include <stdint.h>

/* GLOBAL DEFINES */
#define THRESHOLD 1250

/* Main */
void main_p() {
  mic_init();
  while (1);
}

// Main function to change brightness of a LED
void set_pixels(uint16_t * buffer) {
    float rms_val = rms(buffer, MIC_BUFF_SIZE);
    if (rms_val > THRESHOLD) {
        // Really bright light if more than threshold. Assume beat here
        rms_val = 255;
    }

    // Change LED brightness according to the amplitude
    set_all_pixels_random(rms_val);
    led_refresh();
}

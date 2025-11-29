#include "main.h"
#include <stdint.h>
#include <stdlib.h>


/* FUNCTIONS */

// Generates a random r g b color of a given brightness
void random_color(uint8_t brightness, uint8_t *r, uint8_t *g, uint8_t *b) {
  uint16_t hue = rand() % 360; // Random hue

  // Convert hue to r g b with 100% saturation
  uint8_t section = hue / 60;
  hue %= 60; // Scaling to 0-60 to convert to r g b

  switch (section) {
    case 0:
        *r = brightness;
        *g = (hue * brightness) / 60;
        *b = 0;
        break;
    case 1:
        *r = brightness - ((hue * brightness) / 60);
        *g = brightness;
        *b = 0;
        break;
    case 2:
        *r = 0;
        *g = brightness;
        *b = (hue * brightness) / 60;
        break;
    case 3:
        *r = 0;
        *g = brightness - (hue * brightness) / 60;
        *b = brightness;
        break;
    case 4:
        *r = (hue * brightness) / 60;
        *g = 0;
        *b = brightness;
        break;
    case 5:
        *r = brightness;
        *g = 0;
        *b = brightness - (hue * brightness) / 60;
        break;
  }
}

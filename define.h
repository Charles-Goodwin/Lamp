#ifndef DEFINE_H
#define DEFINE_H

#include <FastLED.h> 

#define DATA_PIN    12 // pins tested so far on the Feather ESP32: 13, 12, 27, 33, 15, 32, 14, SCL
#define LED_TYPE    WS2812B
#define COLOR_ORDER RGB
#define BRIGHTNESS 128
#define NUM_LEDS_COLUMN 5
#define NUM_LEDS_ROW 30
#define NUM_LEDS (NUM_LEDS_COLUMN * NUM_LEDS_ROW)
#define MAX_POWER_MILLIAMPS 60000

#define MAX_PATTERNS 5
#define MAX_PALETTES 5

//CRGB leds[NUM_LEDS];

// FastLED with RGBW
CRGBW leds[NUM_LEDS];
CRGB *ledsRGB = (CRGB *) &leds[0];

uint8_t hues[NUM_LEDS];
static uint8_t patternIndex = 0;
static uint8_t paletteIndex = 0;
uint8_t g_brightness = BRIGHTNESS;
uint8_t g_hueTempo = 0;
uint8_t g_hueShift = 0;

#endif

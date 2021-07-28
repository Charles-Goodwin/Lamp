#ifndef DEFINE_H
#define DEFINE_H

#include <FastLED.h> 

#define DATA_PIN    12 // pins tested so far on the Feather ESP32: 13, 12, 27, 33, 15, 32, 14, SCL
#define LED_TYPE    WS2812B
#define COLOR_ORDER RGB
#define BRIGHTNESS 128
#define NUM_COLS 5
#define NUM_ROWS 30
#define NUM_LEDS (NUM_COLS * NUM_ROWS)
#define MAX_POWER_MILLIAMPS 60000

#define MAX_PATTERNS 7
#define MAX_PALETTES 7

//CRGB leds[NUM_LEDS];

// FastLED with RGBW
CRGBW leds[NUM_LEDS];
CRGB *ledsRGB = (CRGB *) &leds[0];

uint8_t hues[NUM_LEDS];
static uint8_t patternIndex = 2;
static uint8_t paletteIndex = 2;
uint8_t g_brightness = BRIGHTNESS;
uint8_t g_hueTempo = 0;
uint8_t g_hueShift = 0;

#define EEPROM_SIZE 5
#define EEPROM_BRIGHTNESS   0
#define EEPROM_GAIN         1
#define EEPROM_SQUELCH      2
#define EEPROM_PATTERN      3
#define EEPROM_DISPLAY_TIME 4

bool autoChangePatterns = false;

#endif

/// Swirl

#include "SFx.h"

// First orginal pattern
void spiralWithPalette(CRGBPalette256 pal)
{
  const int numStars = 28;
  static float shiftSlow = 0;
  static float shiftFast = 0;
  static bool firstTime = true;
  static uint8_t stars[numStars];
  float fPos;
  CRGBW col;
  
  //blank out all leds
  fill_solid(leds,NUM_LEDS, 0);
  
  if (firstTime) {
    //Seed the random star field
    for (int i=0; i<numStars; i++) {
      stars[i] = random(NUM_LEDS-2);
    }
    firstTime = false;
  }

  for (int i = 0; i<numStars; i++){
    fPos = stars[i] + shiftSlow;
    if (fPos >= NUM_LEDS) {
      fPos -= NUM_LEDS;
    }
    col = ColorFromPalette (pal, 128, 50, LINEARBLEND);
    DrawPixels(fPos, 1.2f, col);
  }

  for (int i = 0; i<numStars; i++){
    fPos = stars[i] - shiftFast;
    if (fPos < 0) {
      fPos += NUM_LEDS;
    }
    col = ColorFromPalette (pal, 0, 255, LINEARBLEND);
    DrawPixels(fPos, 0.8f, col);
  }
  
  shiftSlow += 0.006;
  if (shiftSlow >= NUM_LEDS){
    shiftSlow -= NUM_LEDS;
  }
  shiftFast += 0.009;
  if (shiftFast >= NUM_LEDS){
    shiftFast -= NUM_LEDS;
  }
  
  }

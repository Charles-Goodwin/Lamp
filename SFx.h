#ifndef SFX_H
#define SFX_H

#include "FastLED_RGBW.h"

CRGBW ColorFraction(CRGBW colorIn, float fraction){
  CRGBW col;
  fraction = min(1.0f, fraction);
  fraction = (32645 - cos16(fraction* 16300))/32645.0f;
  col = CRGBW(colorIn).nscale8(255.0f * fraction);
  return CRGBW(colorIn).nscale8(255.0f * fraction);
  
}

void DrawPixels(float fPos, float count, CRGBW color){
  float availFirstPixel = 1.0f - (fPos - (long)(fPos));
  float amtFirstPixel = min(availFirstPixel, count);
  float remaining = min(count, FastLED.size()-fPos);
  int iPos = fPos;


  //Blend (add) in the colour of the first partial pixel
  if (remaining >0.1f) {
    leds[iPos++] += ColorFraction(color, amtFirstPixel);
    remaining -= amtFirstPixel;
  }


  //Now draw any full pixel in the middle
  while (remaining > 1.0f) {
    leds[iPos++] += color;
    remaining --;
  }


  //Draw Tail pixel;
  if (remaining > 0.0f){
    leds[iPos] += ColorFraction(color, remaining);
  }
}

void DrawColumn(float fCol, float fRow, float count, CRGBW color){
  float availFirstPixel = 1.0f - (fRow - (long)(fRow));
  float amtFirstPixel = min(availFirstPixel, count);
  float remaining = min(count, FastLED.size()-fRow);
  int iPos = XY((long)fCol, (long)fRow);

  Serial.print("Remaining0:");
  Serial.println(remaining);
  //Blend (add) in the colour of the first partial pixel
  if (remaining >0.1f) {
    leds[iPos] += ColorFraction(color, amtFirstPixel);
    remaining -= amtFirstPixel;
    iPos +=5;
  }
  Serial.print("Remaining0:");
  Serial.println(remaining);
  //Now draw any full pixel in the middle
  while (remaining > 1.0f) {
    leds[iPos] += color;
    remaining --;
    iPos +=5;
  }
  Serial.print("Remaining0:");
  Serial.println(remaining);
  //Draw Tail pixel;
  if (remaining > 0.0f){
    leds[iPos] += ColorFraction(color, remaining);
  }
}

#endif

#include "audio_reactive.h"

uint8_t peak[] =         {0,0,0,0,0};
uint8_t prevFFTValue[] = {0,0,0,0,0};
uint8_t barHeights[] =   {0,0,0,0,0};

uint8_t numBands = 5;
uint8_t peakDecayRate = 13;


//////////// Patterns ////////////

void rainbowBars(uint8_t band, uint8_t barHeight) {
  int x = band;
  static uint8_t shift;
  if (barHeight > 0) {
    for (int y = 0; y <= barHeight; y++) {
      leds[XY(x,y)] = CHSV((x * 255 / numBands) + shift, 255, 255);
    }
  }
  shift++;
}

void cascade(uint8_t band, uint8_t barHeight) {
  int v = 1;
  static int shift;
  static int timer;
  timer++;
  shift++;
  if (timer==5){
    timer=0;
    ///Shift lights down
    for (int i=0; i<NUM_LEDS; i++){
      if (i>=v) {
        leds[i-v] = leds[i];
      }
      if (random(10) > 8)
        leds[i] = CRGB::Black;
    }  
    fadeToBlackBy( leds, NUM_LEDS, 5);
  }
  
  // Fire off lights if base is detected
  if (fftResult[5] > 90) {
    barHeight = map8(fftResult[0], 0, 50);  
    for (int i = 0; i < barHeight; i++){
      leds[NUM_LEDS - i] = CHSV(shift,255 ,255);
      shift++;
      }
  }

  
}

void purpleBars(int band, int barHeight) {
  int x = band;
  for (int y = 0; y < barHeight; y++) {
    leds[XY(x,y)] = ColorFromPalette(purplePal, y * (255 / barHeight));
  }
}

void changingBars(int band, int barHeight) {
  int x = band;
  for (int y = 0; y < barHeight; y++) {
    leds[XY(x,y)] = CHSV(y * (255 / NUM_ROWS) + g_hueShift, 255, 255); 
  }
}

void centerBars(int band, int barHeight) {
  int x = band;
  if (barHeight % 2 == 0) barHeight--;
  int yStart = ((NUM_ROWS - barHeight) / 2 );
  for (int y = yStart; y <= (yStart + barHeight); y++) {
    int colorIndex = constrain((y - yStart) * (255 / barHeight), 0, 255);
    leds[XY(x,y)] = ColorFromPalette(heatPal, colorIndex);
  }
}

void whitePeak(int band) {
  int x = band;
  int peakHeight = peak[band];
  if (peakHeight
  >0) leds[XY(x,peakHeight)] = 0xFFFFFF00;
}

void outrunPeak(int band) {
  int x = band;
  int y = peak[band];
  leds[XY(x,y)] = ColorFromPalette(outrunPal, y * (255 / NUM_ROWS));
}

void drawPatterns(uint8_t band, uint8_t pattern) {
  
  uint8_t barHeight = barHeights[band];
  
  //Serial.print("barHeight ");
  //Serial.print(band);
  //Serial.print(": ");
  //Serial.println(barHeight);
  
  
  // Draw bars
  switch (pattern) {
    case 0:
      rainbowBars(band, barHeight);
      break;
    case 1:
      cascade(band,barHeight);
      break;
    case 2:
      purpleBars(band, barHeight);
      break;
    case 3:
      centerBars(band, barHeight);
      break;
    case 4:
      changingBars(band, barHeight);
      EVERY_N_MILLISECONDS(10) { g_hueShift++; }
      break;
  }

  // Draw peaks
  switch (pattern) {
    case 0:
      whitePeak(band);
      break;
    case 1:
      // No peaks
      break;
    case 2:
      whitePeak(band);
      break;
    case 3:
      // No peaks
      break;
    case 4:
      // No peaks
      break;
  }
}
void VU_FFT(uint8_t pattern){
  //Serial.print("hello");
 

  if (pattern != 1) FastLED.clear(true);
  uint8_t divisor = 3;                                                    // If 16 bands, so we need to divide things by 3
                                                                          // to get 5 columns (ignore the last band)
  static uint8_t peakDecay = peakDecayRate;
  for (int i = 0; i < 15; i += divisor) {
    uint8_t fftValue;

  //  TelnetStream.print("fftResult ");
  //  TelnetStream.print(i);
  //  TelnetStream.print(": ");
  //  TelnetStream.println(fftResult[i]);
    
    fftValue = (fftResult[i] + fftResult[i+1] + fftResult[i+2]) / divisor;    // Average every three bands

    fftValue = ((prevFFTValue[i/divisor] * 3) + fftValue) / 4;            // Dirty rolling average between frames to reduce flicker
    barHeights[i/divisor] = map8(fftValue, 0, NUM_ROWS-1);                // Scale bar height
  

    if (barHeights[i/divisor] > peak[i/divisor])                          // Move peak up
      peak[i/divisor] = min(NUM_ROWS, (int)barHeights[i/divisor]);
      
    prevFFTValue[i/divisor] = fftValue;                                   // Save prevFFTValue for averaging later
    
  }

  //Serial.println("Executing Loop");
  // Draw the patterns

 
  
  for (int band = 0; band < numBands; band++) {
    drawPatterns(band, pattern);
  }

  // Decay peak
  peakDecay--;
  if (peakDecay == 0) {
    peakDecay = peakDecayRate;
    for (uint8_t band = 0; band < numBands; band++){
      if (peak[band] > 0) peak[band] -= 1 ;
      //Serial.println(peak[band]);
    }
  }
}

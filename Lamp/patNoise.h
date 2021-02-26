
#include "palette.h"
#include "xy.h"

const uint8_t kMatrixWidth  = NUM_LEDS_COLUMN;
const uint8_t kMatrixHeight = NUM_LEDS_ROW;

// This example combines two features of FastLED to produce a remarkable range of
// effects from a relatively small amount of code.  This example combines FastLED's 
// color palette lookup functions with FastLED's Perlin/simplex noise generator, and
// the combination is extremely powerful.
//
// You might want to look at the "ColorPalette" and "Noise" examples separately
// if this example code seems daunting.
//
// 
// The basic setup here is that for each frame, we generate a new array of 
// 'noise' data, and then map it onto the LED matrix through a color palette.
//
// Periodically, the color palette is changed, and new noise-generation parameters
// are chosen at the same time.  In this example, specific noise-generation
// values have been selected to match the given color palettes; some are faster, 
// or slower, or larger, or smaller than others, but there's no reason these 
// parameters can't be freely mixed-and-matched.
//
// In addition, this example includes some fast automatic 'data smoothing' at 
// lower noise speeds to help produce smoother animations in those cases.
//
// The FastLED built-in color palettes (Forest, Clouds, Lava, Ocean, Party) are
// used, as well as some 'hand-defined' ones, and some proceedurally generated
// palettes.



#define MAX_DIMENSION ((kMatrixWidth>kMatrixHeight) ? kMatrixWidth : kMatrixHeight)

// The 16 bit version of our coordinates
static uint16_t x=0;
static uint16_t y=0;
static uint16_t z=0;

// We're using the x/y dimensions to map to the x/y pixels on the matrix.  We'll
// use the z-axis for "time".  speed determines how fast time moves forward.  Try
// 1 for a very slow moving effect, or 60 for something that ends up looking like
// water.
uint16_t speed = 20; // speed is set dynamically once we've started up

// Scale determines how far apart the pixels in our noise matrix are.  Try
// changing these values around to see how it affects the motion of the display.  The
// higher the value of scale, the more "zoomed out" the noise iwll be.  A value
// of 1 will be so zoomed in, you'll mostly see solid colors.
uint16_t scale = 30; // scale is set dynamically once we've started up

// This is the array that we keep our computed noise values in
uint8_t noise[MAX_DIMENSION][MAX_DIMENSION];

CRGBPalette256 currentPalette;
uint8_t       colorLoop = 1;

// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.

// 1 = 5 sec per palette
// 2 = 10 sec per palette
// etc
#define HOLD_PALETTES_X_TIMES_AS_LONG 2

void ChangePaletteAndSettingsPeriodically(){
  //currentPalette = LavaLampPurple_pal();
  currentPalette = palettes[paletteIndex].palette();
  speed = 5; 
  scale = 20; 
  colorLoop = 1; 
}

void mapNoiseToLEDsUsingPalette()
{
  static uint8_t ihue=0;
  
  for(int i = 0; i < kMatrixWidth; i++) {
   
      for(int j = 0; j < kMatrixHeight; j++) {
        // We use the value at the (i,j) coordinate in the noise
        // array for our brightness, and the flipped value from (j,i)
        // for our pixel's index into the color palette.
  
        uint8_t index = noise[j][i];
        uint8_t bri =   noise[i][j];
  
        // if this palette is a 'loop', add a slowly-changing base value
        if( colorLoop) { 
          index += ihue;
        }
  
        // brighten up, as the color palette itself often contains the 
        // light/dark dynamic range desired
        if( bri > 127 ) {
          bri = 255;
        } else {
          bri = dim8_raw( bri * 2);
        }
  
        CRGB color = ColorFromPalette( currentPalette, index, g_brightness);
        leds[XY(i,j)] = color;
      }
    
  }
  
  ihue+=1;
}

// Fill the x/y array of 8-bit noise values using the inoise8 function.
void fillnoise8() {
  // If we're runing at a low "speed", some 8-bit artifacts become visible
  // from frame-to-frame.  In order to reduce this, we can do some fast data-smoothing.
  // The amount of data smoothing we're doing depends on "speed".
  uint8_t dataSmoothing = 0;
  if( speed < 50) {
    dataSmoothing = 200 - (speed * 4);
  }
  
  for(int i = 0; i < MAX_DIMENSION; i++) {
    int ioffset = scale * i;
    for(int j = 0; j < MAX_DIMENSION; j++) {
      int joffset = scale * j;
      
      uint8_t data = inoise8(x + ioffset,y + joffset,z);

      // The range of the inoise8 function is roughly 16-238.
      // These two operations expand those values out to roughly 0..255
      // You can comment them out if you want the raw noise data.
      data = qsub8(data,16);
      data = qadd8(data,scale8(data,39));

      if( dataSmoothing ) {
        uint8_t olddata = noise[i][j];
        uint8_t newdata = scale8( olddata, dataSmoothing) + scale8( data, 256 - dataSmoothing);
        data = newdata;
      }
      
      noise[i][j] = data;
    }
  }
  
  z += speed;
  
  // apply slow drift to X and Y, just for visual variation.
  x += speed / 8;
  y -= speed / 16;
}

void displayNoise (){
  // Serial.println("Just started Noise");
  if(x==0 && y==0 && z==0){
    // Initialize our coordinates to some random values
    x = random16();
    y = random16();
    z = random16();
  }

  // Periodically choose a new palette, speed, and scale
  ChangePaletteAndSettingsPeriodically();
  
  // generate noise data
  fillnoise8();

  // convert the noise data to colors in the LED array
  // using the current palette
  mapNoiseToLEDsUsingPalette();

}

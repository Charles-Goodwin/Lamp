#include "define.h"
#include "palette.h"
#include "patNoise.h"
#include "xy.h"
#include "FastLED_RGBW.h"

// My first stab at emulating the iconic raining code from the movie The Matrix
// The Palette parameter allows you to use an alternative to the traditional green monitor effect
void digitalRainPalette(CRGBPalette256 palette) {
  //Declare a Trail type
  // Trail comprises of x, y coords, governing throttle, life span and a palette index
  typedef struct Trail{
    uint8_t x =0;
    uint8_t y =0;
    uint8_t throttle = 0; //higher reduces speed, lower increases speed (timer reset value)
    uint8_t timer = 0;  //advance every time timer expires 
    uint8_t lifeSpan = 0; // determines if trail reaches the bottom
    uint8_t palIndex = 0;
  } ;

  const int NUM_TRAILS = 8;
  static int phase = 0;
  
  switch (phase) {
    case 0:
    //Render all the neopixels Black
    fill_solid(leds, NUM_LEDS, CRGB::Black);  
    phase =1;
    break;
    
    case 1:
    //Serial.println("codeFall");
    // Declare a list of Trails that we will track
    static Trail trailList[NUM_TRAILS];
    
    // Add entropy to random number generator; we use a lot of it.
    random16_add_entropy(random(256));
  
    // Dim every cell by 5% (10/256) each time
    fadeToBlackBy(leds, NUM_LEDS, 10);
       
    //Go through all the trails
    for (uint8_t i = 0; i < NUM_TRAILS; i++) {
      
      //Check if Trail is active
      // Check that lifespan has not expired
      if (trailList[i].lifeSpan > 0) {
        //Continue countdown until it expires
        if (trailList[i].timer > 0) {
          //coontinue with countdown of waiting
          trailList[i].timer--;
        }
        else {
          //Assign the color to the head of the trail
          leds[XY(trailList[i].x,trailList[i].y)] = ColorFromPalette(palette, trailList[i].palIndex, g_brightness, NOBLEND);
          //Set the tail of the trail 
          leds[XY(trailList[i].x, trailList[i].y + 1)] = ColorFromPalette(palette, (trailList[i].palIndex+8), g_brightness, NOBLEND);
          leds[XY(trailList[i].x, trailList[i].y + 2)] = ColorFromPalette(palette, (trailList[i].palIndex+16), g_brightness, NOBLEND);
          leds[XY(trailList[i].x, trailList[i].y + 3)] = ColorFromPalette(palette, 200, g_brightness, NOBLEND);
          // The remaining part of the tail will fade as part of the general dimming
          
          //Advance trail down one
          trailList[i].y --;
          // Deplete the life span
          trailList[i].lifeSpan --;
          
          //Advance the palette index
          trailList[i].palIndex += 8;
          if (trailList[i].palIndex > 40) {
            trailList[i].palIndex = 0;
          }
             
          //Reset the timer
          trailList[i].timer = trailList[i].throttle;
          //Trail's life ends at reaching the bottom 
          if (trailList[i].y == 0) {trailList[i].lifeSpan = 0;}
        }
      }
      else {
        //Create a new Trail
        //Pick a random column
        trailList[i].x = random8(NUM_LEDS_COLUMN);
           
        //Built in random pause by placing starting height position beyond top led)
        trailList[i].y = random8(NUM_LEDS_ROW * 1.5);
        
        trailList[i].throttle = random8(3); // Higher is slower; Lower is faster
      
        trailList[i].timer = 0;
        trailList[i].palIndex = 8* random8(5);
        //Default lifespan for Trail to reach the bottom
        trailList[i].lifeSpan = trailList[i].y;
      
        //  Once in a while shorten the lifespan so that the trail stops short
          if (!(random8(2)%2)) {trailList[i].lifeSpan += ((NUM_LEDS_COLUMN * random8(100) / 100)- NUM_LEDS_COLUMN);}
      }
    }
    break;
  }
}

void mydrawLine (uint8_t x, uint8_t y, uint8_t x1, uint8_t y1, CRGB color){   // my ugly line draw function )))
  uint8_t xsteps = abs8(x-x1)+1;  
  uint8_t ysteps = abs8(y-y1)+1;
  uint8_t steps =  xsteps >= ysteps? xsteps:ysteps;

  for (byte i = 1; i <= steps; i++) {
    uint8_t dx = lerp8by8 (x, x1, i*255/steps);
    uint8_t dy = lerp8by8 (y, y1, i*255/steps);
    leds[XY(dx, dy)] = color;                               // change to += for brightness look
  }
}

void murmurationPalette(CRGBPalette256 palette) {
  // Inspired by:
  // Yaroslaw Turbin, 27.10.2020 
  // https://vk.com/ldirko
  // https://www.reddit.com/user/ldirko/
  
  //look how it look in online emulator:
  //https://wokwi.com/arduino/projects/280541577702539789

  static uint8_t palletIndex;
  
  int x1 = beatsin8 (18, 0, (NUM_LEDS_COLUMN-1));
  int x2 = beatsin8 (23, 0, (NUM_LEDS_COLUMN-1)); 
  int y1 = beatsin8 (20, 0, (NUM_LEDS_COLUMN-1)); 
  int y2 = beatsin8 (26, 0, (NUM_LEDS_COLUMN-1)); 
  CRGB color = ColorFromPalette(palette, palletIndex++, g_brightness, LINEARBLEND );
  mydrawLine(x1, y1,  x2, y2, color);
  blur1d (leds, NUM_LEDS, 32 );
}

void digitalRain() {
  digitalRainPalette(palettes[paletteIndex].palette());
}

void murmuration() {
  murmurationPalette(palettes[paletteIndex].palette());
}
  


// We must have fire
void Fire2012WithPalette(CRGBPalette256 gPal)
{
// Array of temperature readings at each simulation cell
  const uint8_t COOLING = 80;
  const uint8_t SPARKING = 120;
  const uint8_t  NUM_SECTION = NUM_LEDS_ROW;
  static byte heat[NUM_SECTION];
  
  const boolean gReverseDirection = true;
   typedef struct flame{
    byte heat[NUM_SECTION];
  } ;

  static flame flames[NUM_LEDS_ROW];
  for( int f = 0; f < NUM_LEDS_ROW; f++) {

    // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_SECTION; i++) {
      flames[f].heat[i] = qsub8( flames[f].heat[i],  random8(0, ((COOLING * 10) / NUM_SECTION) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_SECTION - 1; k >= 2; k--) {
      flames[f].heat[k] = (flames[f].heat[k - 1] + flames[f].heat[k - 2] + flames[f].heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      flames[f].heat[y] = qadd8( flames[f].heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_SECTION; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      byte colorindex = scale8( flames[f].heat[j], 240);
      leds[XY(f,j)] = ColorFromPalette( gPal, colorindex);
    }
  }
}

void solid(CRGBPalette256 palette){
  static uint8_t brightness = 0;
  static long unsigned timeCheck;
  long unsigned timeDiff;
  timeDiff = millis() - timeCheck;
  abs(timeDiff);
  // Reset brightness to zero if more than a second has elapsed since last called
  if (timeDiff > 1000) brightness = 0;
  timeCheck = millis();
  
  if (brightness==g_brightness) {
    fill_solid(leds, NUM_LEDS, ColorFromPalette(palette, 0, g_brightness ));
  }
  else {
    if (brightness < g_brightness){ 
      fill_solid(leds, NUM_LEDS, ColorFromPalette(palette, 0, brightness++ ));
    } else{
      fill_solid(leds, NUM_LEDS, ColorFromPalette(palette, 0, brightness-- )); 
    }
  }
}

void displayPink() {
  solid(palettes[paletteIndex].palette());
}

void fire2012() {
  Fire2012WithPalette(palettes[paletteIndex].palette());
}

//Lets sort out a play list
//First lets define its structure
typedef void (*Pattern)();
typedef Pattern PatternList[];
typedef struct {
  Pattern pattern;
  String name;
} PatternAndName;
typedef PatternAndName PatternAndNameList[];

//Now lets populate it
PatternAndNameList patterns = {
 {fire2012,                       "Fire"},
 {digitalRain,                    "Matrix Digital Rain"} ,
 {murmuration,                    "Murmuration"},
 {displayNoise,                   "lava lamp"},
 {displayPink,                    "Pink" }

};


#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>

#include "FastLED_RGBW.h"
#include "define.h"
#include "OTA.h"
#include "patterns.h"
#include "web.h"
#include "blynk.h"


FASTLED_USING_NAMESPACE

void setup() {
  delay( 3000); // 3 second delay for boot recovery, and a moment of silence
  //FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS)
  //      .setCorrection( TypicalLEDStrip );
  
  //FastLED with RGBW
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(ledsRGB, getRGBWsize(NUM_LEDS));
  
  FastLED.setMaxPowerInVoltsAndMilliamps( 5, MAX_POWER_MILLIAMPS);
  FastLED.setBrightness(g_brightness);
  

  Serial.begin(115200);

  //Just need these 2 lines to enable OTA
  //ArduinoOTA.setHostname("Wall Lights");
  //setupOTA();

  //connect to WiFi
  //connectToWIFI();

  //Initialise web server
  //handleServerRequests();
  
  randomSeed(analogRead(A0));
  //Blynk.begin(auth, ssid, password);

  int hue = 0;
  int sat = 255;
  int val = 255;
  
 
/*
  // Set Individual Colors
  leds[0].r = 255;
  leds[0].g = 128;
  leds[0].b = 64;
  leds[0].w = 32; // Specific to RGBW
*/
  leds[0] = CHSV(0,255,255);
  CRGBW test;
  test = leds[0];
  Serial.println("Test 1");
  Serial.print("test.r:");
  Serial.println(test.r);
  Serial.print("test.g:");
  Serial.println(test.g);
  Serial.print("test.b:");
  Serial.println(test.b);
  Serial.print("test.w:");
  Serial.println(test.w);
  Serial.println();

  leds[0] = CRGBW::Red;
  test = leds[0];
  Serial.println("Test 2");
  Serial.print("test[0]:");
  Serial.println(test[0]);
  Serial.print("test[1]:");
  Serial.println(test[1]);
  Serial.print("test[2]:");
  Serial.println(test[2]);
  Serial.print("test[3]:");
  Serial.println(test[3]);
  Serial.println();

  leds[0] = CRGBW(100,150,200,250);
  test = leds[0];
  Serial.println("Test 3");
  Serial.print("test[0]:");
  Serial.println(test[0]);
  Serial.print("test[1]:");
  Serial.println(test[1]);
  Serial.print("test[2]:");
  Serial.println(test[2]);
  Serial.print("test[3]:");
  Serial.println(test[3]);
  Serial.println();

  leds[0] = CRGBW::Blue;

  test = leds[0];
  Serial.println("Test 4");
  Serial.print("test[0]:");
  Serial.println(test[0]);
  Serial.print("test[1]:");
  Serial.println(test[1]);
  Serial.print("test[2]:");
  Serial.println(test[2]);
  Serial.print("test[3]:");
  Serial.println(test[3]);
 


  Serial.println("step 1"); 
  leds[0] = CRGB(255, 128, 64);
  leds[0] = CRGBW(255, 128, 64, 32);
   
  // Set HSV Color
  leds[0] = CHSV(hue, sat, val);
  Serial.println("step 2"); 
}

void loop() {
  //ArduinoOTA.handle();
  //Serial.println("step 3"); 
  Serial.print("patternIndex:");
  Serial.println(patternIndex);
  patterns[patternIndex].pattern();
  FastLED.show();
  //Blynk.run();

/*
  EVERY_N_MILLISECONDS(1000) {
    ws.cleanupClients();
  }
  
  EVERY_N_MILLISECONDS(1000) {
    g_hueShift += g_hueTempo;
    if (g_hueTempo != 0) {
      notifyClients("{\"key\":\"hueShift\", \"value\":" + (String)g_hueShift + "}");
      Blynk.virtualWrite(V4, g_hueShift);
    }
  }
  */
}

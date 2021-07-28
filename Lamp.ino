 
#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>

#include "FastLED_RGBW.h"
#include "define.h"
#include "OTA.h"
#include "patterns.h"
#include "web.h"
#include "EEPROM.h"




FASTLED_USING_NAMESPACE

void setup() {
  delay( 3000); // 3 second delay for boot recovery, and a moment of silence
  //FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS)
  //      .setCorrection( TypicalLEDStrip );
  
  //FastLED with RGBW
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(ledsRGB, getRGBWsize(NUM_LEDS));
  
  FastLED.setMaxPowerInVoltsAndMilliamps( 5, MAX_POWER_MILLIAMPS);
  FastLED.setBrightness(g_brightness);
  setupAudio();
  EEPROM.begin(EEPROM_SIZE);
  //EEPROM_Init();
  //EEPROM_Read();
  
  Serial.begin(115200);

  //Just need these 2 lines to enable OTA
  ArduinoOTA.setHostname("Lamp");
  setupOTA();
  //connect to WiFi if OTA is disabled
  //connectToWIFI();

  //Initialise web server
  handleServerRequests();

}

void loop() {

  ArduinoOTA.handle();
  
  patterns[patternIndex].pattern();
  //Fire2012WithPalette(palettes[3].palette());
  //pacifica_loop();
  
  FastLED.setBrightness(g_brightness);
  FastLED.show();

  EVERY_N_SECONDS(30) {
    // Save values in EEPROM. Will only be commited if values have changed.
    //EEPROM_Save();
  }

  EVERY_N_MILLISECONDS(1000) {
    ws.cleanupClients();

    g_hueShift += g_hueTempo;
    if (g_hueTempo != 0) {
      notifyClients("{\"key\":\"hueShift\", \"value\":" + (String)g_hueShift + "}");
    }
  }
}

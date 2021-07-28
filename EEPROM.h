
#include <EEPROM.h>

void EEPROM_Init() {
  // It should not normally be possible to set the gain to 255
  // If this has happened, the EEPROM has probably never been written to
  // (new board?) so reset the values to something sane.
  if (EEPROM.read(EEPROM_GAIN) == 255) {
    EEPROM.write(EEPROM_BRIGHTNESS, 50);
    EEPROM.write(EEPROM_GAIN, 0);
    EEPROM.write(EEPROM_SQUELCH, 0);
   // EEPROM.write(EEPROM_PATTERN, 0);
   // EEPROM.write(EEPROM_DISPLAY_TIME, 10);
    EEPROM.commit();
  }
}

void EEPROM_Read() {
  // Read saved values from EEPROM
  FastLED.setBrightness( EEPROM.read(EEPROM_BRIGHTNESS));
  g_brightness = FastLED.getBrightness();
  gain = EEPROM.read(EEPROM_GAIN);
  squelch = EEPROM.read(EEPROM_SQUELCH);
  //pattern = EEPROM.read(EEPROM_PATTERN);
  //pattern = EEPROM.read(EEPROM_DISPLAY_TIME);
}

void EEPROM_Save(){
  EEPROM.write(EEPROM_BRIGHTNESS, g_brightness);
  EEPROM.write(EEPROM_GAIN, gain);
  EEPROM.write(EEPROM_SQUELCH, squelch);
  //EEPROM.write(EEPROM_PATTERN, g_brightness);
  // EEPROM.write(EEPROM_DISPLAY_TIME, g_brightness);
  EEPROM.commit();
}


class Comet {
  private:
    const byte fadeAmt = 128;
    const int cometSize = 5;
    const int deltaHue  = 4;

    byte hue = HUE_RED;
    int iDirection = 1;
    int iPos = 0;
    bool active = false;
    uint8_t dice;
    uint8_t col;
    uint8_t sat;

  public:
    Comet() {
      // example code for initiation but none required this time
      /*
      this->pinLED = pinLED;
      this->timeLedOn = timeLedOn;
      this->timeLedOff = timeLedOff;
      
      */
      //Serial.println ("Initialise");
    }

    // Checks whether it is time to turn on or off the LED.
    void Draw() {
      if (active) {
        //Serial.println("Active");
        hue += deltaHue;
        iPos += iDirection;
        //Serial.print("iPos:");
        //Serial.println(iPos);

        if (iPos == (NUM_ROWS - cometSize)) active=false;

        leds[XY(col, iPos)] = CRGBW::Black;
        for (int i = 1; i < cometSize; i++){

          sat = 255 - constrain(i*20,0,255);
          dice = random8(i);
          if (dice>0){
            if (random8(10) > 5) {
              leds[XY(col, iPos + i)] = CHSV(hue, sat, 50);
            }
            else{
              leds[XY(col, iPos + i)] = CHSV(hue, sat, 255);
            }
          }           
        }
        CRGBW headCol;
        headCol = CHSV(hue, sat, 255);
        headCol.w = 100; 
        leds[XY(col, iPos + cometSize -1)] = headCol;
        
      }
      //Serial.println("Not Active");
    }
    void Fire(){
      if (!active) {
        active = true;
        iPos = 0;
        hue = random8(255);
        col = random8(NUM_COLS);
      }
      //Serial.print("Fire:active:");
      //Serial.print(active);
    }
};

void DrawComet(){
  const uint8_t cometCount = 4;
  const uint8_t brake = 30;
  
  static Comet comets[cometCount];
  static uint8_t next = 0;
  static uint8_t pass = 0;
  
  uint8_t dice;
  
  if(brake == pass++) {
    pass = 0;
    dice = random8(100);
    if (dice > 80) {
      comets[next++].Fire();
      if (next==cometCount ) next = 0;
    }
    for (int i =0; i< cometCount; i++){
       comets[i].Draw();
    }
  }

}

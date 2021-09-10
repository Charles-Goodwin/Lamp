#define NUM_COLORS 5

//How did this dumb arse excuse for a palette get into here! 
static const CRGBW TwinkleColors [NUM_COLORS] = 
{
    CRGBW::Red,
    CRGBW::Blue,
    CRGBW::Purple,
    CRGBW::Green,
    CRGBW::Orange
};

void DrawTwinkle()
{
  static int pass = 0;
  if (pass++ > 2) {
    Serial.println ("writing");
    leds[random8(NUM_LEDS)] = TwinkleColors[random8(0, NUM_COLORS)];
    pass = 0;
  }
  fadeToBlackBy (leds, NUM_LEDS, 5);
}

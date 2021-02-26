#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  patternIndex = param.asInt();
  Serial.print("V0 Slider value is: ");
  Serial.println(pinValue);
}

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  paletteIndex = param.asInt();
  Serial.print("V1 Slider value is: ");
  Serial.println(pinValue);
}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  g_hueTempo = param.asInt();
  Serial.print("V2 Slider value is: ");
  Serial.println(pinValue);
}

BLYNK_WRITE(V3)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  g_brightness = param.asInt();
  Serial.print("V3 Slider value is: ");
  Serial.println(pinValue);
}

BLYNK_WRITE(V5)
{
  g_hueTempo = 0;
  g_hueShift = 0;
  Serial.println("V5 Button Pressed");
  
}

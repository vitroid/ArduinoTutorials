#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

extern char auth[],ssid[],pass[];

void setup()
{
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}

#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

Servo myservo;  // create servo object to control a servo

extern char auth[],ssid[],pass[];

void setup()
{
  Blynk.begin(auth, ssid, pass);
  myservo.attach(D5);  // attaches the servo on D5 to the servo object
}

void loop()
{
  Blynk.run();
}

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V1
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  myservo.write(pinValue);
}

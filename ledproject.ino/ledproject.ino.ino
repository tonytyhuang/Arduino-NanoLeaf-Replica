#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include "Controller.h"


// Auth token for Blynk App
char auth[] = "uOlz7fi1IpqMfFdIB-SipVfuRrBfbZSp";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "tcwhhome";
char pass[] = "twch1019";


std::shared_ptr<Nanoleaf> controller;

BLYNK_WRITE(V1)
{
  int R = param[0].asInt();
  int G = param[1].asInt();
  int B = param[2].asInt();
  controller->setColour(R,G,B);
}

BLYNK_WRITE(V2){
  unsigned int data = param.asInt();
  controller->setBright(data);
}

BLYNK_WRITE(V3){
  uint8_t pinValue = param.asInt();
  
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass); 
  controller = std::make_shared<Nanoleaf> ();
  controller->begin();                                                         
}

void loop()
{
  Blynk.run();
}

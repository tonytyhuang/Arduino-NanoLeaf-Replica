#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include "Controller.h"
#include <memory>


// Auth token for Blynk App
char auth[] = "uOlz7fi1IpqMfFdIB-SipVfuRrBfbZSp";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "tcwhhome";
char pass[] = "twch1019";


std::shared_ptr<Nanoleaf> controller;

// Setting colour
BLYNK_WRITE(V1)
{
  int R = param[0].asInt();
  int G = param[1].asInt();
  int B = param[2].asInt();
  controller->setColour(R,G,B);
}

// Setting brightness
BLYNK_WRITE(V2){
  unsigned int data = param.asInt();
  controller->setBright(data);
}

// Setting effect
BLYNK_WRITE(V3){
 uint8_t effect = param.asInt();
 controller->setEffect(effect);
}

// Setting theme
BLYNK_WRITE(V4){
  uint8_t theme = param.asInt();
  controller->setTheme(theme);
}

// Setting minimum fade timing
BLYNK_WRITE(V5){
  uint16_t minTime = 1000 * param.asInt();

}

// Setting maximum fade timing
BLYNK_WRITE(V6){
  uint16_t maxTime = 1000 * param.asInt();

}

// Setting randomness of hue
BLYNK_WRITE(V7){
  uint8_t hueRand = 15 * param.asInt();

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
  controller->update();
}

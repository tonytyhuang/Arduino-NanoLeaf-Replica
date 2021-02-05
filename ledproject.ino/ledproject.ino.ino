#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_NeoPixel.h>
#include <FastLED.h>
#include <SPI.h>
#include "Controller.h"
#include "Leaf.h"
#include <memory>
// Number of Nanoleaf
#define NUM_LEAF 8

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
  controller->setColour(CRGB(R,G,B));
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
  controller->setMin(minTime);
}

// Setting maximum fade timing
BLYNK_WRITE(V6){
  uint16_t maxTime = 1000 * param.asInt();
  controller->setMax(maxTime);
}

// Setting randomness of hue
BLYNK_WRITE(V7){
  uint16_t hueRand = param.asInt();
  controller->setHue(hueRand);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  // Creating controller object
  controller = std::make_shared<Nanoleaf> ();
  // Creating individual leaf objects
  for (int i = 0; i < NUM_LEAF; ++i){
    std::shared_ptr<Leaf> leaf(new Leaf(i*18, CRGB(49, 187, 217), controller));
    controller->attachLeafs(leaf);
  }
  // Starting Blynk
  Blynk.begin(auth, ssid, pass);                                                    
}

void loop()
{
  Blynk.run();
  // Calling update function of controller
  controller->update();
}

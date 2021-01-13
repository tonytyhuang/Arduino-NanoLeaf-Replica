#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Leaf.h"
#include <FastLED.h>
#include <vector>
#include <memory>

// Number of Nanoleaf
#define NUM_LEAF 8
// Pin that is connected
#define PIN 27
// Total number of LEDS
#define NUMPIXELS 150
// declare variable to control LEDS

class Nanoleaf{
  std::vector<std::shared_ptr<Leaf>> vecLeaf;
  CRGB pixels[NUMPIXELS];
  CRGB colour;
  unsigned int bright;
  uint8_t effect;
  uint8_t theme;
  uint16_t minTime;
  uint16_t maxTime;
  uint16_t hueRand;
  bool themeOn;
  bool updateNow;
  unsigned long time;
  unsigned long lastUpdate;
  public:
  // Class constructor
  Nanoleaf();
  //show colour
  void showColour();
  // setColour() sets the colour of the LEDS
  void setColour(CRGB input);
  // setBright() sets the brightness of the LEDS
  void setBright(unsigned int data);
  // setEffect() sets the effect used
  void setEffect(uint8_t eff);
  // setTheme() sets the theme of the lights
  void setTheme(uint8_t t);
  // setMin() sets the min fading time of the lights
  void setMin(uint16_t m);
  // setMax() sets the max fading time of the lights
  void setMax(uint16_t m);
  // setHue() sets the hue randomness of the lights
  void setHue(uint8_t hue);
  // update() checks the state of the lights and runs everything accordingly
  void update();
};              


#endif

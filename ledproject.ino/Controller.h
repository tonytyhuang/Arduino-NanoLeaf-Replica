#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Leaf.h"
#include <Adafruit_NeoPixel.h>

// Number of Nanoleaf
#define NUM_LEAF 8
// Pin that is connected
#define PIN 27
// Total number of LEDS
#define NUMPIXELS 150
// declare variable to control LEDS

class Nanoleaf{
  Adafruit_NeoPixel pixels;
  int colour[3];
  unsigned int bright;
  uint8_t effect;
  uint8_t theme;
  uint16_t minTime;
  uint16_t maxTime;
  uint8_t hueRand;
  bool themeOn;
  public:
  // Class constructor
  Nanoleaf();
  // begin() begin the leds
  void begin();
  //show colour
  void showColour();
  // setColour() sets the colour of the LEDS
  void setColour(int r, int g, int b);
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
};              


#endif

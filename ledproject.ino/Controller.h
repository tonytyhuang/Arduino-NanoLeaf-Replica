#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Leaf.h"
#include <Adafruit_NeoPixel.h>

// Number of LEDS in each Nanoleaf
#define LED_PER_BOX 18
// Number of Nanoleaf
#define NUM_LEAF 8
// Pin that is connected
#define PIN 27
// Total number of LEDS
#define NUMPIXELS 150
// declare variable to control LEDS

class Nanoleaf{
  Adafruit_NeoPixel pixels;

  public:
  // Class constructor
  Nanoleaf();
  //show colour
  void showColour();
  // setColour() sets the colour of the LEDS
  void setColour(int r, int g, int b);
  // setBright() sets the brightness of the LEDS
  void setBright(unsigned int data);
  // begin() begin the leds
  void begin();
};              


#endif

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Adafruit_NeoPixel.h>

// Number of LEDS in each Nanoleaf
#define LED_PER_BOX 10
// Number of Nanoleaf
#define NUM_LEAF 5
// Pin that is connected
#define PIN 27
// Total number of LEDS
#define NUMPIXELS 150
// declare variable to control LEDS

class Nanoleaf{
  Adafruit_NeoPixel pixels;
  public:
  Nanoleaf();
  //show colour
  void showColour();
  // setColour() sets the colour of the LEDS
  void setColour(int r, int g, int b);
  // brightness() sets the brightness of the LEDS
  void setBright(unsigned int data);
  void begin(){
    pixels.begin();
  }
};              


#endif

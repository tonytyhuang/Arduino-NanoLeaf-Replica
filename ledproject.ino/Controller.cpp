#include "Controller.h"

Nanoleaf::Nanoleaf(): pixels{Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800)} {}

void Nanoleaf::showColour(){
  pixels.show();
}

void Nanoleaf::setColour(int r, int g, int b){
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
  showColour();
}

void Nanoleaf::setBright(unsigned int data){
  for (int i = 0; i < NUMPIXELS; i++){
    pixels.setBrightness(data);
  }
  if (data ==  254){
    setColour(49, 187, 217);
  }
  showColour();
}

#include "Controller.h"

Nanoleaf::Nanoleaf(): pixels{Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800)}, colour{49, 187, 217} {}

void Nanoleaf::showColour(){
  pixels.show();
}

void Nanoleaf::setColour(int r, int g, int b){
  colour[0] = r;
  colour[1] = g;
  colour[2] = b;
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
  showColour();
}

void Nanoleaf::setBright(unsigned int data){
  for (int i = 0; i < NUMPIXELS; i++){
    pixels.setBrightness(data);
  }
  setColour(colour[0], colour[1], colour[2]);
  showColour();
}

void Nanoleaf::begin(){
    pixels.begin();
  }
#include "Controller.h"

Nanoleaf::Nanoleaf(): pixels{Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800)}, colour{49, 187, 217},
bright{255}, effect{1}, theme{1}, minTime{0}, maxTime{0}, hueRand{0}, themeOn{false} {}

void Nanoleaf::begin(){
    pixels.begin();
  }

void Nanoleaf::showColour(){
  pixels.show();
}

void Nanoleaf::setColour(int r, int g, int b){
  colour[0] = r;
  colour[1] = g;
  colour[2] = b;
  if (!themeOn){
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(r, g, b));
    }
    showColour();
  }
}

void Nanoleaf::setBright(unsigned int data){
  bright = data;
  for (int i = 0; i < NUMPIXELS; i++){
    pixels.setBrightness(data);
  }
  setColour(colour[0], colour[1], colour[2]);
  showColour();
}

void Nanoleaf::setEffect(uint8_t eff){
  effect = eff;
}

void Nanoleaf::setTheme(uint8_t t){
  theme = t;
  if (t == 2 && t == 3){
    themeOn = true;
  }
}

void Nanoleaf::setMin(uint16_t m){
  minTime = m;
}

void Nanoleaf::setMax(uint16_t m){
  maxTime = m;
}

void Nanoleaf::setHue(uint8_t hue){
  hueRand = hue;
}
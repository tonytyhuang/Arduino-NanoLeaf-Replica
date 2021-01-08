#include "Controller.h"

Nanoleaf::Nanoleaf(): pixels{Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800)}, colour{49, 187, 217},
bright{255}, effect{1}, theme{1}, minTime{0}, maxTime{0}, hueRand{0}, themeOn{false} {
  for (int i = 0; i < NUM_LEAF; ++i){
    if (i == 0){
      vecLeaf.push_back(std::make_shared<Leaf> (0, 49, 187, 217));
    }else if (i == 1){
      vecLeaf.push_back(std::make_shared<Leaf> (23, 49, 187, 217));
    }else{
      vecLeaf.push_back(std::make_shared<Leaf> (23 + ((i-1)*18), 49, 187, 217));
    }
  }
}

void Nanoleaf::begin(){
    pixels.begin();
  }

void Nanoleaf::showColour(){
  for(int i = 0; i < NUMPIXELS; ++i){
    pixels.setPixelColor(i, colour[0], colour[1], colour[2]);
  }
  pixels.show();
}

void Nanoleaf::setColour(int r, int g, int b){
  colour[0] = r;
  colour[1] = g;
  colour[2] = b;
  for (int i = 0; i < NUM_LEAF; ++i){
    vecLeaf[i]->setInput(r,g,b);
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

void Nanoleaf::update(){
  if (!themeOn){
    if (effect == 1){
      showColour();
    }else if (effect == 2){
      for (int i = 0; i < NUM_LEAF; ++i){
        vecLeaf[i]->changeColour(pixels, random(minTime, maxTime));
      }
      delay(minTime);
    }
  }
}

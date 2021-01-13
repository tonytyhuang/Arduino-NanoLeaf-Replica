#include "Controller.h"

Nanoleaf::Nanoleaf(): colour{CRGB(49, 187, 217)}, time{0}, lastUpdate{0},
bright{255}, effect{1}, theme{1}, minTime{3000}, maxTime{7000}, hueRand{50}, themeOn{false} {
  FastLED.addLeds<WS2812B, PIN, GRB>(pixels, NUMPIXELS);
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


void Nanoleaf::showColour(){
  for(int i = 0; i < NUMPIXELS; ++i){
    pixels[i] = colour;
  }
  FastLED.show();
}

void Nanoleaf::setColour(CRGB input){
  colour = input;
  for (int i = 0; i < NUM_LEAF; ++i){
    vecLeaf[i]->setInput(colour.red, colour.green, colour.blue);
  }
  update();
  for(int i = 0; i < NUMPIXELS; ++i){
    pixels[i] = colour;
  }
}

void Nanoleaf::setBright(unsigned int data){
  bright = data;
  FastLED.setBrightness(data);
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
  if (millis() - time > 3000){
    if (!themeOn){
      switch(effect){
        case 1:
          for (uint8_t i = 0; i < NUM_LEAF; i++){
            vecLeaf[i]->setStaticMode(pixels, colour);
          }
          break;
        case 2:
          for (uint8_t i = 0; i < NUM_LEAF; i++){
            vecLeaf[i]->setFadeTime(random(minTime, maxTime));
            vecLeaf[i]->setHueMode(pixels);
          }
      }
    }
  }
  // Update lights every 60 ms
  if (millis() - lastUpdate > 60){
    for (uint8_t i = 0; i < NUM_BOXES; i++)
      int ret = nodes[i]->draw();
      FastLED.show();
      lastUpdate = millis();
  }
}

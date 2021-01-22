#include "Controller.h"

Nanoleaf::Nanoleaf(): colour{CRGB(49, 187, 217)}, time{0}, lastUpdate{0}, updateNow{false},
bright{255}, effect{1}, theme{1}, minTime{3000}, maxTime{7000}, hueRand{50}, themeOn{false} {
  FastLED.addLeds<WS2812B, PIN, GRB>(pixels, NUMPIXELS);
  for(int i = 0; i < NUMPIXELS; ++i){
    setPixels(i, colour);
    }
}

void Nanoleaf::attachLeafs(std::shared_ptr<Leaf> leaf){
  vecLeaf.emplace_back(leaf);
}


void Nanoleaf::showColour(){
}

void Nanoleaf::setPixels(unsigned int i, CRGB colour){
  pixels[i] = colour;
}

void Nanoleaf::setColour(CRGB input){
  colour = input;
  for (int i = 0; i < NUM_LEAF; ++i){
    vecLeaf[i]->setInput(input);
  }
  updateNow = true;
  lastUpdate = 0;
}

void Nanoleaf::setBright(unsigned int data){
  bright = data;
  if (effect == 1){
    FastLED.setBrightness(data);
    FastLED.show();
  }
}

void Nanoleaf::setEffect(uint8_t eff){
  effect = eff;
  updateNow = true;
  lastUpdate = 0;
}

void Nanoleaf::setTheme(uint8_t t){
  theme = t;
  if (t == 2 && t == 3){
    themeOn = true;
  }
  updateNow = true;
  lastUpdate = 0;
}

void Nanoleaf::setMin(uint16_t m){
  minTime = m;
  updateNow = true;
  lastUpdate = 0;
}

void Nanoleaf::setMax(uint16_t m){
  maxTime = m;
  updateNow = true;
  lastUpdate = 0;
}

void Nanoleaf::setHue(uint8_t hue){
  hueRand = hue;
  updateNow = true;
  lastUpdate = 0;
}

void Nanoleaf::update(){
  if (updateNow){
    if (!themeOn){
      switch(effect){
        case 1:
          for (uint8_t i = 0; i < NUM_LEAF; i++){
            vecLeaf[i]->setStaticMode(colour);
          }
          updateNow = false;
          break;
        case 2:
          for (uint8_t i = 0; i < NUM_LEAF; i++){
            vecLeaf[i]->setHue(hueRand);
            vecLeaf[i]->setColourTime(minTime, maxTime); 
            vecLeaf[i]->setHueMode(millis());
          }
          updateNow = false;
          break;
        case 3:
          for (uint8_t i = 0; i < NUM_LEAF; i++){
            vecLeaf[i]->setColourGradientMode();
          }
          updateNow = false;
          break;
        default:
          for (uint8_t i = 0; i < NUM_LEAF; i++){
            vecLeaf[i]->setStaticMode(colour);
          } 
          updateNow = false;
          break;
      }
    }
    time = millis();
  }
  // Update lights every 100 ms
  if (millis() - lastUpdate > 50){
    for (uint8_t i = 0; i < NUM_LEAF; i++){
       vecLeaf[i]->update(millis());
    }
    FastLED.show();
    lastUpdate = millis();
  }
}

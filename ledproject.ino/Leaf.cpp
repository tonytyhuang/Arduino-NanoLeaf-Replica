#include "Leaf.h"

Leaf::Leaf(int pix, CRGB colour, std::shared_ptr<Nanoleaf> &nano): pixelNum{pix}, hueRand{100}, inputColour{colour},
colorFrom{rgb2hsv_approximate(colour)}, colorTo{rgb2hsv_approximate(colour)},
fadeMin{3000}, fadeMax{7000}, fadeTime{5000}, hue{false}, gradient{false}, gradFade{false}, hueStartTime{0} {
    nanoleaf = nano;
}

void Leaf::hueGenerate(){
    CHSV hsv = rgb2hsv_approximate(inputColour);
    CHSV colour = CHSV(hsv.hue + random(-hueRand / 2, hueRand / 2), hsv.sat, hsv.val);
    colorTo = colour;
    CRGB light = colour;
    for (int i = pixelNum; i < pixelNum + LED_PER_BOX; ++i){
        nanoleaf->setPixels(i, light);
    }
}

void Leaf::fadeOut(){
    for (int i = colorFrom.val; i >= 1; --i){
        for (int j = pixelNum; j < pixelNum + LED_PER_BOX; ++j){
            CRGB light = CHSV(colorFrom.hue, colorFrom.sat, i);
            nanoleaf->setPixels(i, light);
        }
        FastLED.show();
        delay(10);
    }
}

void Leaf::fadeIn(){
    for (int i = 1; i < colorTo.val; ++i){
        for (int j = pixelNum; j < pixelNum + LED_PER_BOX; ++j){
            CRGB light = CHSV(colorFrom.hue, colorFrom.sat, i);
            nanoleaf->setPixels(i, light);
        }
        FastLED.show();
        delay(10);
    }
}

void Leaf::setFadeTime(uint16_t min, uint16_t max){
    fadeMin = min;
    fadeMax = max;
}

void Leaf::setInput(CRGB colour){
    inputColour = colour;
    colorFrom = rgb2hsv_approximate(colour);
}

void Leaf::setHue(uint8_t hue){
  hueRand = hue;
  hue = true;
}

void Leaf::setStaticMode(CRGB colour){
    setInput(colour);
    hue = false;
    gradient = false;
    gradFade = false;
    CHSV hsv = rgb2hsv_approximate(inputColour);
    CRGB light = hsv;
    for(int i = pixelNum; i < pixelNum + LED_PER_BOX; ++i){
        nanoleaf->setPixels(i, light);
    }
}

void Leaf::setHueMode(unsigned long time){
    hue = true;
    if (time - hueStartTime >= fadeTime){
        //fadeOut();
        hueGenerate();
        //fadeIn();
        colorFrom = colorTo;
        fadeTime = random(fadeMin, fadeMax);
        hueStartTime = time;
    }
}

void Leaf::update(unsigned long time){
    if (hue){
        setHueMode(time);
    }
}

#include "Leaf.h"

Leaf::Leaf(int pix, CRGB colour, std::shared_ptr<Nanoleaf> &nano): pixelNum{pix}, hueRand{50}, inputColour{colour},
colorFrom{rgb2hsv_approximate(colour)}, colorTo{rgb2hsv_approximate(colour)},
fadeTime{0}, hue{false}, gradient{false}, gradFade{false}, hueStartTime{0} {
    nanoleaf = nano;
}

void Leaf::hueGenerate(){
    CHSV hsv = rgb2hsv_approximate(inputColour);
    hsv.hue += random(-hueRand / 2, hueRand / 2);
    colorTo = hsv;
    for (int i = pixelNum; i < pixelNum + LED_PER_BOX; ++i){
        CRGB light = hsv;
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

void Leaf::setFadeTime(uint16_t time){
    fadeTime = time;
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
    for(int i = pixelNum; i < pixelNum + LED_PER_BOX; ++i){
        nanoleaf->setPixels(i, colour);
    }
}

void Leaf::setHueMode(){
    if (millis() - hueStartTime >= fadeTime){
        fadeOut();
        hueGenerate();
        fadeIn();
        colorFrom = colorTo;
        hueStartTime = millis();
    }
}

void Leaf::update(){
    if (hue){
        setHueMode();
    }
}

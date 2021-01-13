#include "Leaf.h"

Leaf::Leaf(int pix, CRGB colour): pixelNum{pix}, hueRand{50}, inputColour{colour},
colorFrom{rgb2hsv_approximate(colour)}, colorTo{rgb2hsv_approximate(colour)},
fadeTime{0}, hue{false}, gradient{false}, gradFade{false} {}

void Leaf::hueGenerate(){
    CHSV hsv = rgb2hsv_approximate(inputColour);
    hsv.hue += random(-hueRand / 2, hueRand / 2);
    colorTo = hsv;
    for (int i = pixelNum; i < pixelNum + LED_PER_BOX; ++i){
        CRGB light = hsv;
        pixels[i] = light;
    }
}

void Leaf::fadeOut(){
    for (int i = colorFrom.val; i >= 1; --i){
        for (int j = pixelNum; j < pixelNum + LED_PER_BOX; ++j){
            CRGB light = CHSV(colorFrom.hue, colorFrom.sat, i);
            pixels[j] = light;
        }
        FastLED.show();
    }
}

void Leaf::fadeIn(){
    for (int i = 1; i < colorTo.val; ++i){
        for (int j = pixelNum; j < pixelNum + LED_PER_BOX; ++j){
            CRGB light = CHSV(colorFrom.hue, colorFrom.sat, i);
            pixels[j] = light;
        }
        FastLED.show();
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
}

void Leaf::setStaticMode(CRGB colour){
    setInput(colour);
    hue = false;
    gradient = false;
    gradFade = false;
}

void Leaf::setHueMode(){
    hue = true;
    unsigned long time = millis();
    if (millis() - time >= fadeTime){
        fadeOut();
        hueGenerate();
        fadeIn();
        colorFrom = colorTo;
    }
}

void Leaf::update(){
    if (hue){
        setHueMode();
    }
}

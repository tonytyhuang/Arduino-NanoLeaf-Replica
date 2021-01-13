#include "Leaf.h"

Leaf::Leaf(int pix, CRGB colour): pixelNum{pix}, hueRand{50}, inputColour{colour},
colorFrom{rgb2hsv_approximate(colour)} {}

void Leaf::hueGenerate(CRGB leds){
    CHSV hsv = inputColour;
    hsv.hue += random(-hueRand / 2, hueRand / 2);
    for (int i = pixelNum; i < pixelNum + LED_PER_BOX; ++i){
        pixels.setPixelColor(i, pixels.ColorHSV(hsv.hue, hsv.sat, hsv.val));
    }
}

void Leaf::fadeOut(CRGB leds){
    for (int i = 255; i >= 1; --i){
        for (int j = pixelNum; j < pixelNum + LED_PER_BOX; ++j){
            pixels.setBrightness(i);
        }
        pixels.show();
    }
}

void Leaf::fadeIn(CRGB leds){
    for (int i = 1; i < 256; ++i){
        for (int j = pixelNum; j < pixelNum + LED_PER_BOX; ++j){
            pixels.setBrightness(i);
        }
        pixels.show();
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

void Leaf::setStaticMode(CRGB leds, CRGB colour){
    setInput(colour);
    hue = false;
    gradient = false;
    gradFade = false;
}

void Leaf::setHueMode(CRGB leds, bool set){
    if (set){
        fadeTime = time;
    }
    unsigned long beginTime = millis();
    if (millis() - beginTime > fadeTime){
        fadeOut(leds);
        hueGenerate(leds);
        fadeIn(leds);
    }
}
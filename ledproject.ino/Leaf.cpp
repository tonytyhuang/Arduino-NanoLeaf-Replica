#include "Leaf.h"

Leaf::Leaf(int pix, CRGB colour): pixelNum{pix}, hueRand{50}, inputColour{colour},
colorFrom{rgb2hsv_approximate(colour)}, colorTo{rgb2hsv_approximate(colour)},
fadeTime{0}, hue{false}, gradient{false}, gradFade{false} {}

void Leaf::hueGenerate(CRGB leds){
    CHSV hsv = rgb2hsv_approximate(inputColour);
    hsv.hue += random(-hueRand / 2, hueRand / 2);
    colorTo = hsv;
    for (int i = pixelNum; i < pixelNum + LED_PER_BOX; ++i){
        leds[i] = hsv;
    }
}

void Leaf::fadeOut(CRGB leds){
    for (int i = colorFrom.val; i >= 1; --i){
        for (int j = pixelNum; j < pixelNum + LED_PER_BOX; ++j){
            leds[j] = (CHSV(colorFrom.hue, colorFrom.sat, i));
        }
        FastLED.show();
    }
}

void Leaf::fadeIn(CRGB leds){
    for (int i = 1; i < colorTo.val; ++i){
        for (int j = pixelNum; j < pixelNum + LED_PER_BOX; ++j){
            leds[j] = (CHSV(colorFrom.hue, colorFrom.sat, i));
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

void Leaf::setStaticMode(CRGB leds, CRGB colour){
    setInput(colour);
    hue = false;
    gradient = false;
    gradFade = false;
}

void Leaf::setHueMode(CRGB leds){
    hue = true;
    unsigned long time = millis();
    if (millis() - time >= fadeTime){
        fadeOut(leds);
        hueGenerate(leds);
        fadeIn(leds);
        colorFrom = colorTo;
    }
}

void Leaf::update(CRGB leds){
    if (hue){
        setHueMode(leds)
    }
}
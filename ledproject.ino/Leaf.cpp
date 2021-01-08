#include "Leaf.h"

Leaf::Leaf(int pix, int r, int g, int b): pixelNum{pix}, hueRand{0} {
    CRGB rgb;
    rgb.red = r;
    rgb.green = g;
    rgb.blue = b;
    inputColour = rgb2hsv_approximate(rgb);
}

void Leaf::hueGenerate(Adafruit_NeoPixel pixels){
    CHSV hsv = inputColour;
    hsv.hue += random(-hueRand / 2, hueRand / 2);
    for (int i = pixelNum; i < pixelNum + LED_PER_BOX; ++i){
        pixels.setPixelColor(i, pixels.ColorHSV(hsv.hue, hsv.sat, hsv.val));
    }
}

void Leaf::fadeOut(Adafruit_NeoPixel pixels){
    for (int i = 255; i >= 1; --i){
        for (int j = pixelNum; j < pixelNum + LED_PER_BOX; ++j){
            pixels.setBrightness(i);
        }
        pixels.show();
    }
}

void Leaf::fadeIn(Adafruit_NeoPixel pixels){
    for (int i = 1; i < 256; ++i){
        for (int j = pixelNum; j < pixelNum + LED_PER_BOX; ++j){
            pixels.setBrightness(i);
        }
        pixels.show();
    }
}


void Leaf::changeColour(Adafruit_NeoPixel pixels, uint16_t time){
    unsigned long beginTime = millis();
    if (millis() - beginTime > time){
        fadeOut(pixels);
        hueGenerate(pixels);
        fadeIn(pixels);
    }

}

void Leaf::setInput(int r, int g, int b){
    CRGB rgb;
    rgb.red = r;
    rgb.green = g;
    rgb.blue = b;
    inputColour = rgb2hsv_approximate(rgb);
}

void Leaf::setHue(uint8_t hue){
  hueRand = hue;
}

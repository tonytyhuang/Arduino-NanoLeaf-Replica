#include "Leaf.h"

Leaf::Leaf(int pix): pixelNum{pix} {}

void Leaf::hueGenerate(int r, int g, int b, uint8_t hueRand, Adafruit_NeoPixel pixels){
    CRGB rgb;
    rgb.red = r;
    rgb.green = g;
    rbg.blue = b;
    CHSV hsv = rgb2hsv_approximate(rgb);
    hsv.hue += random(-hueRandomness / 2, hueRandomness / 2);
    for (int i = pixelNum; i < pixelNum + LED_PER_BOX; ++i){
        pixels.setPixelColor(i, pixels.ColorHSV(hsv.hue, hsv.sat, hsv.val));
    }
}


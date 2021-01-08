#ifndef LEAF_H
#define LEAF_H

#define FASTLED_INTERNAL
#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

// Number of LEDS in each Nanoleaf
#define LED_PER_BOX 18

struct hsv{
        int h;
        int s;
        int v;
    };

class Leaf{
    int pixelNum;
    CHSV colorFrom;
    CHSV colorTo;
    CHSV inputColour;
    uint8_t hueRand;
    public:
    Leaf(int pix, int r, int g, int b);
    void hueGenerate(Adafruit_NeoPixel pixels);
    void changeColour(Adafruit_NeoPixel pixels, uint16_t time);
    void fadeIn(Adafruit_NeoPixel pixels);
    void fadeOut(Adafruit_NeoPixel pixels);
    void setInput(int r, int g, int b);
    void setHue(uint8_t hue);
};

#endif

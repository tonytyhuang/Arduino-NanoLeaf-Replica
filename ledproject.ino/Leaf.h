#ifndef LEAF_H
#define LEAF_H

#define FASTLED_INTERNAL
#include <Adafruit_NeoPixel.h>
#include <FastLED.h>
#include <vector>
#include <memory>
#include "Controller.h"

class Nanoleaf;

// Number of LEDS in each Nanoleaf
#define LED_PER_BOX 18
// Number of Nanoleaf
#define NUM_LEAF 8
// Pin that is connected
#define PIN 27
// Total number of LEDS
#define NUMPIXELS 150
// declare variable to control LEDS

struct hsv{
        int h;
        int s;
        int v;
    };

class Leaf{
    int pixelNum;
    std::shared_ptr<Nanoleaf> nanoleaf;
    CHSV colorFrom;
    CHSV colorTo;
    CRGB inputColour;
    uint16_t hueRand;
    uint16_t fadeTime;
    uint16_t fadeMin;
    uint16_t fadeMax;
    bool hue;
    bool gradient;
    bool gradFade;
    unsigned long hueStartTime;
    public:
    Leaf(int pix, CRGB colour, std::shared_ptr<Nanoleaf> &nano);
    void hueGenerate();
    void fadeIn();
    void fadeOut();
    void setFadeTime(uint16_t min, uint16_t max);
    void setInput(CRGB colour);
    void setHue(uint8_t hue);
    void setStaticMode(CRGB colour);
    void setHueMode(unsigned long time);
    void update(unsigned long time);
};

#endif

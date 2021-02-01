#ifndef LEAF_H
#define LEAF_H

#define FASTLED_INTERNAL
#include <Adafruit_NeoPixel.h>
#include <FastLED.h>
#include <vector>
#include <memory>
#include <iostream>
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
    CRGB colorFrom;
    CRGB colorTo;
    CRGB inputColour;
    int fadeInterval;
    int gradFadeInt;
    int themeNum;
    uint16_t hueRand;
    uint16_t colourTime;
    uint16_t colourMin;
    uint16_t colourMax;
    bool fade;
    bool hue;
    bool colourGrad;
    bool hueGrad;
    bool theme;
    unsigned long hueStartTime;
    unsigned long fadeTimer;
    unsigned long gradTimer;
    const CRGB winterArr[6] = {CRGB(194, 194, 194), CRGB(223, 223, 223), CRGB(248, 248, 248), CRGB(121, 192, 215), CRGB(80, 163, 198), CRGB(30, 119, 164)};
    const CRGB beachArr[6] = {CRGB(254, 233, 100), CRGB(30, 70, 70), CRGB(255, 166, 0), CRGB(255, 156, 223), CRGB(30, 87, 91), CRGB(255, 20, 22)};
    public:
    Leaf(int pix, CRGB colour, std::shared_ptr<Nanoleaf> &nano);
    void hueGenerate();
    void fadeIn();
    void fadeOut();
    void gradFadeIn();
    void gradFadeOut();
    void setColourTime(uint16_t min, uint16_t max);
    void setInput(CRGB colour);
    void setHue(uint8_t hueInp);
    void setThemeNum(uint8_t effect);
    void setColourGradientMode();
    void setHueGradientMode();
    void setStaticMode(CRGB colour);
    void setHueMode(unsigned long time);
    void setThemeColour(unsigned long time);
    void update(unsigned long time);
};

#endif

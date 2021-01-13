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
    CRGB pixels[150];
    CHSV colorFrom;
    CHSV colorTo;
    CRGB inputColour;
    uint16_t hueRand;
    uint16_t fadeTime;
    bool hue;
    bool gradient;
    bool gradFade;
    public:
    Leaf(int pix, CRGB colour);
    void hueGenerate();
    void fadeIn();
    void fadeOut();
    void setFadeTime(uint16_t time);
    void setInput(CRGB colour);
    void setHue(uint8_t hue);
    void setStaticMode(CRGB colour);
    void setHueMode();
    void update();
};

#endif

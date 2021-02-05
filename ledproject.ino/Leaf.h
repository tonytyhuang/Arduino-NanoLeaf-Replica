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
    const CRGB winterArr[6] = 
    {CRGB(194, 194, 194), 
    CRGB(223, 223, 223), 
    CRGB(248, 248, 248), 
    CRGB(121, 192, 215), 
    CRGB(80, 163, 198), 
    CRGB(30, 119, 164)};
    const CRGB beachArr[6] = 
    {CRGB(254, 233, 100), 
    CRGB(30, 70, 70), 
    CRGB(255, 166, 0), 
    CRGB(255, 156, 223), 
    CRGB(30, 87, 91), 
    CRGB(255, 20, 22)};
    public:
    // Constructor for the leaf
    Leaf(int pix, CRGB colour, std::shared_ptr<Nanoleaf> &nano);
    // hueGenerate() generates a new colour with random hue
    void hueGenerate();
    // setNew() sets the colour to the generated one 
    void setNew();
    // fadeColour() fades the colour from the past one to the new colour
    void fadeColour();
    // gradFadeIn() fades the gradients in
    void gradFadeIn();
    // gradFadeOut() fades the gradients out
    void gradFadeOut();
    // setColourTime(min, max) sets the min colour time to min, and the max colour time to max,
    void setColourTime(uint16_t min, uint16_t max);
    // setInput(colour) sets the input colour to colour
    void setInput(CRGB colour);
    // setHue(hueInp) sets the hue randomness to hueInp
    void setHue(uint8_t hueInp);
    // setThemeNum(effect) sets the theme to the given integer effect
    void setThemeNum(uint8_t effect);
    // setColourGradientMode() sets the mode to the colour gradient mode and creates
    //    the specific colours needed for the lights
    void setColourGradientMode();
    // setHueGradientMode() sets the mode to the hue gradient mode and creates
    //    the specific colours needed for the lights
    void setHueGradientMode();
    // setStaticMode(colour) sets the mode to static mode and creates
    //    the specific colours needed for the lights
    void setStaticMode(CRGB colour);
    // setHueMode(time) sets the mode to hue mode and creates
    //     the specific colours needed for the lights
    void setHueMode(unsigned long time);
    // setThemeColour(time) sets the theme colour while changing it based on
    //     the variable time given
    void setThemeColour(unsigned long time);
    // update(time) is a function run all the time and changes the lights colours
    //     based on the current settings received from blynk
    void update(unsigned long time);
};

#endif

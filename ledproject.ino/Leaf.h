#ifndef LEAF_H
#define LEAF_H
#include <Adafruit_NeoPixel.h>
#include <FASTLED.h>

// Number of LEDS in each Nanoleaf
#define LED_PER_BOX 18

struct hsv{
        int h;
        int s;
        int v;
    }

class Leaf{
    int pixelNum;
    hsv color;
    public:
    Leaf(int pix);
    uint8_t hueGenerate(int r, int g, int b);
};

#endif

#include "Leaf.h"

Leaf::Leaf(int pix, CRGB colour, std::shared_ptr<Nanoleaf> &nano): 
pixelNum{pix},
inputColour{colour}, colorFrom{colour}, colorTo{colour},
hueRand{100}, fade{false}, colourMin{3000}, colourMax{7000}, colourTime{0}, hueStartTime{0}, fadeTimer{0}, fadeInterval{1},
hue{false}, gradient{false}, gradFade{false} {
    nanoleaf = nano;
}

void Leaf::hueGenerate(){
    CHSV hsv = rgb2hsv_approximate(inputColour);
    CHSV colour = CHSV(hsv.hue + random(-hueRand / 2, hueRand / 2), hsv.sat, hsv.val);
    colorTo = colour;
    //CRGB light = colorTo;
//     for (int i = pixelNum; i < pixelNum + LED_PER_BOX; ++i){
//          nanoleaf->setPixels(i, colorTo);
//     }
}

void Leaf::fadeOut(){
    // int16_t r = colorFrom.r + (((float)(colorTo.r - colorFrom.r)/(15)) * fadeInterval);
    // int16_t g = colorFrom.g + (((float)(colorTo.g - colorFrom.g)/(15)) * fadeInterval);
    // int16_t b = colorFrom.b + (((float)(colorTo.b - colorFrom.b)/(15)) * fadeInterval);
    float red = ((colorTo.r - colorFrom.r)/(15)) * fadeInterval;
    float green = ((colorTo.g - colorFrom.g)/(15)) * fadeInterval;
    float blue = ((colorTo.b - colorFrom.b)/(15)) * fadeInterval;

    int16_t r = colorFrom.r + (int)red;
    int16_t g = colorFrom.g + (int)green;
    int16_t b = colorFrom.b + (int)blue;
    CRGB light = CRGB(r, g, b);
    for (int i = pixelNum; i < pixelNum + LED_PER_BOX; ++i){
       nanoleaf->setPixels(i, light);
    }
    fadeInterval += 1;
}

void Leaf::fadeIn(){
    for (int i = pixelNum; i < pixelNum + LED_PER_BOX; ++i){
        nanoleaf->setPixels(i, colorTo);
    }
    colorFrom = colorTo;
    fade = false;
    fadeInterval = 1;
}

void Leaf::setColourTime(uint16_t min, uint16_t max){
    colourMin = min;
    colourMax = max;
}

void Leaf::setInput(CRGB colour){
    inputColour = colour;
    colorFrom = colour;
}

void Leaf::setHue(uint8_t hueInp){
  hueRand = hueInp;
  hue = true;
  gradient = false;
  gradFade = false;
}

void Leaf::setStaticMode(CRGB colour){
    setInput(colour);
    hue = false;
    gradient = false;
    gradFade = false;
    CHSV hsv = rgb2hsv_approximate(inputColour);
    CRGB light = hsv;
    for(int i = pixelNum; i < pixelNum + LED_PER_BOX; ++i){
        nanoleaf->setPixels(i, light);
    }
}

void Leaf::setHueMode(unsigned long time){
    if (time - hueStartTime >= colourTime){
        //fadeOut();
        hueGenerate();
        //fadeIn();
        //colorFrom = colorTo;
        fade = true;
        colourTime = random(colourMin, colourMax);
        hueStartTime = time;
        fadeTimer = time;
    }
}

void Leaf::update(unsigned long time){
    if (hue){
        setHueMode(time);
        if (fade){
            if (time - fadeTimer >= 1500){
                fadeIn();
            }else{
                //fadeIn();
                fadeOut();
            }
        }
    }
}

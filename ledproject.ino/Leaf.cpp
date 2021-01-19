#include "Leaf.h"

Leaf::Leaf(int pix, CRGB colour, std::shared_ptr<Nanoleaf> &nano): 
pixelNum{pix},
inputColour{colour}, colorFrom{rgb2hsv_approximate(colour)}, colorTo{rgb2hsv_approximate(colour)},
hueRand{100}, fade{false}, colourMin{3000}, colourMax{7000}, colourTime{0}, hueStartTime{0}, fadeTimer{0}, fadeInterval{1},
hue{false}, gradient{false}, gradFade{false} {
    nanoleaf = nano;
}

void Leaf::hueGenerate(){
    CHSV hsv = rgb2hsv_approximate(inputColour);
    CHSV colour = CHSV(hsv.hue + random(-hueRand / 2, hueRand / 2), hsv.sat, hsv.val);
    colorTo = colour;
    CRGB light = colorTo;
    for (int i = pixelNum; i < pixelNum + LED_PER_BOX; ++i){
         nanoleaf->setPixels(i, colorTo);
    }
}

void Leaf::fadeOut(){
    // for (int i = colorFrom.val; i >= 1; --i){
    //     for (int j = pixelNum; j < pixelNum + LED_PER_BOX; ++j){
    //         CRGB light = CHSV(colorFrom.hue, colorFrom.sat, i);
    //         nanoleaf->setPixels(i, light);
    //     }
    //     FastLED.show();
    //     delay(10);
    // }
   // int16_t r = colorFrom.r + ((float)(colorTo.r - colorFrom.r)/(10) * fadeInterval);
    //int16_t g = colorFrom.g + ((float)(colorTo.g - colorFrom.g)/(10) * fadeInterval);
    //int16_t b = colorFrom.b + ((float)(colorTo.b - colorFrom.b)/(10) * fadeInterval);
    //CRGB light = CRGB(r, g, b);
    //for (int i = pixelNum; i < pixelNum + LED_PER_BOX; ++i){
      //  nanoleaf->setPixels(i, light);
    //}
    //fadeInterval += 1;
}

void Leaf::fadeIn(){
//    for (int i = 1; i < colorTo.val; ++i){
//        for (int j = pixelNum; j < pixelNum + LED_PER_BOX; ++j){
//            CRGB light = CHSV(colorFrom.hue, colorFrom.sat, i);
//            nanoleaf->setPixels(i, light);
//        }
//        FastLED.show();
//        delay(10);
//    }

    for (int i = pixelNum; i < pixelNum + LED_PER_BOX; ++i){
        nanoleaf->setPixels(i, colorTo);
    }
}

void Leaf::setColourTime(uint16_t min, uint16_t max){
    colourMin = min;
    colourMax = max;
}

void Leaf::setInput(CRGB colour){
    inputColour = colour;
    colorFrom = rgb2hsv_approximate(colour);
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
        colorFrom = colorTo;
        colourTime = random(colourMin, colourMax);
        hueStartTime = time;
        fadeTimer = time;
    }
}

void Leaf::update(unsigned long time){
    if (hue){
        setHueMode(time);
        // if (fade){
        //     if (time - fadeTimer >= 1000){
        //         colorFrom = colorTo;
        //         fade = false;
        //     }else{
        //         fadeIn();
        //         //fadeOut();
        //     }
        // }
    }
}

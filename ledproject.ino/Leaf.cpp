#include "Leaf.h"

Leaf::Leaf(int pix, CRGB colour, std::shared_ptr<Nanoleaf> &nano): 
pixelNum{pix},
inputColour{colour}, colorFrom{colour}, colorTo{colour}, gradFadeInt{1},
hueRand{100}, fade{false}, colourMin{3000}, colourMax{7000}, colourTime{0}, hueStartTime{0}, fadeTimer{0}, fadeInterval{1},
hue{false}, colourGrad{false}, hueGrad{false}, theme{false}, gradTimer{0} {
    nanoleaf = nano;
}

void Leaf::hueGenerate(){
    CHSV hsv = rgb2hsv_approximate(inputColour);
    CHSV colour = CHSV(hsv.hue + random(-hueRand / 2, hueRand / 2), hsv.sat, hsv.val);
    colorTo = colour;
}

void Leaf::fadeOut(){
    float red = ((colorTo.r - colorFrom.r)/(30)) * fadeInterval;
    float green = ((colorTo.g - colorFrom.g)/(30)) * fadeInterval;
    float blue = ((colorTo.b - colorFrom.b)/(30)) * fadeInterval;

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
}

void Leaf::setHue(uint8_t hueInp){
  hueRand = hueInp;
  hue = true;
  colourGrad = false;
  hueGrad = false;
  theme = false;
}

void Leaf::setThemeNum(uint8_t effect){
  themeNum = effect;
}

void Leaf::setThemeColour(unsigned long time){
    hue = false;
    colourGrad = false;
    hueGrad = false;
    theme = true;
    if (time - hueStartTime >= colourTime){
        if (themeNum == 2){
            colorTo = winterArr[rand()%6];
        }else if (themeNum == 3){
            colorTo = beachArr[rand()%6];
            //colorFrom = beachArr[0];
        }
        colourTime = random(colourMin, colourMax);
        hueStartTime = time;
        fade = true;
        fadeTimer = time;
    }
}

void Leaf::setStaticMode(CRGB colour){
    setInput(colour);
    hue = false;
    colourGrad = false;
    colorFrom = colour;
    hueGrad = false;
    theme = false;
    for(int i = pixelNum; i < pixelNum + LED_PER_BOX; ++i){
        nanoleaf->setPixels(i, inputColour);
    }
}

void Leaf::setHueMode(unsigned long time){
    if (time - hueStartTime >= colourTime){
        hueGenerate();
        fade = true;
        colourTime = random(colourMin, colourMax);
        hueStartTime = time;
        fadeTimer = time;
    }
}

void Leaf::setColourGradientMode(){
    hue = false;
    colourGrad = true;
    hueGrad = false;
    theme = false;
    CHSV hsv = rgb2hsv_approximate(inputColour);
    uint16_t leafNum;
    if (pixelNum == 0 || pixelNum == 18){
        leafNum = 0;
    }else if (pixelNum == 36 || pixelNum == 54){
        leafNum = 1;
    }else if (pixelNum == 72 || pixelNum == 90){
        leafNum = 2;
    }else if (pixelNum == 108 || pixelNum == 126){
        leafNum = 3;
    }
    hsv.sat = 75 + (45*leafNum);
    CHSV colour = CHSV(hsv.hue, hsv.sat, hsv.val);
    colorFrom = colour; 
    for (int i = pixelNum; i < pixelNum + LED_PER_BOX; ++i){
        nanoleaf->setPixels(i, colorFrom);
    }
}

void Leaf::setHueGradientMode(){
    hue = false;
    colourGrad = false;
    hueGrad = true;
    theme = false;
    uint16_t leafNum;
    if (pixelNum == 0 || pixelNum == 18){
        leafNum = 0;
    }else if (pixelNum == 36 || pixelNum == 54){
        leafNum = 1;
    }else if (pixelNum == 72 || pixelNum == 90){
        leafNum = 2;
    }else if (pixelNum == 108 || pixelNum == 126){
        leafNum = 3;
    }
    CHSV hsv = rgb2hsv_approximate(inputColour);
    if (hsv.hue > 235){
        hsv.hue += -60 + (leafNum * 20);
    }else if (hsv.hue > 215){
        hsv.hue += -40 + (leafNum * 20);
    }else if (hsv.hue < 20){
        hsv.hue += (leafNum * 20);
    }else{
        hsv.hue += -20 + (leafNum * 20);
    }
    CHSV colour = CHSV(hsv.hue, hsv.sat, hsv.val);
    colorFrom = colour;
    for (int i = pixelNum; i < pixelNum + LED_PER_BOX; ++i){
        nanoleaf->setPixels(i, colorFrom);
    }
}

void Leaf::gradFadeIn(){
  CHSV hsv = rgb2hsv_approximate(colorFrom);
  hsv.val = 255 - (5 * gradFadeInt);
  CRGB colour = CHSV(hsv.hue, hsv.sat, hsv.val);
  for (int i = pixelNum; i < pixelNum + LED_PER_BOX; ++i){
        nanoleaf->setPixels(i, colour);
   }
   gradFadeInt += 1;
}

void Leaf::gradFadeOut(){
  CHSV hsv = rgb2hsv_approximate(colorFrom);
  hsv.val = 55 + (5 * (gradFadeInt - 40));
  CRGB colour = CHSV(hsv.hue, hsv.sat, hsv.val);
  for (int i = pixelNum; i < pixelNum + LED_PER_BOX; ++i){
        nanoleaf->setPixels(i, colour);
   }
   gradFadeInt += 1;
}

void Leaf::update(unsigned long time){
    if (hue){
        setHueMode(time);
        if (fade){
            if (time - fadeTimer >= 1500){
                fadeIn();
            }else{
                fadeOut();
            }
        }
    }else if (colourGrad || hueGrad){
      if (time - gradTimer >= 10000){
        if (gradFadeInt <= 40){
          gradFadeIn();
        }else if (gradFadeInt <= 80){
          gradFadeOut();
        }else {
          gradTimer = time;
          gradFadeInt = 1;
        }
      }
    }else if (theme){
        setThemeColour(time);
        if (fade){
            if (time - fadeTimer >= 1500){
                fadeIn();
            }else{
                fadeOut();
            }
        }
    }
}

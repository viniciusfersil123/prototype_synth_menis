#ifndef MENUS_H
#define MENUS_H
#include "daisy_seed.h"
#include "dev/oled_ssd130x.h"

class Menus
{
  public:
    float splashScreenRectY = 0;
    void  SplashScreen(
         daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen);
};
#endif
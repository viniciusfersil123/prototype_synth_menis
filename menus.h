#ifndef MENUS_H
#define MENUS_H
#include "daisy_seed.h"
#include "dev/oled_ssd130x.h"

class Menus
{
  public:
    float         splashScreenRectY = 0;
    const uint8_t marginLeft        = 10;
    const uint8_t marginRight       = 10;
    const uint8_t marginUp          = 10;
    const uint8_t marginBottom      = 10;

    struct graphicsArea
    {
        //bottom-left x1,y1 __ top-right x2,y2
        uint8_t x1;
        uint8_t y1;
        uint8_t x2;
        uint8_t y2;
    };
    graphicsArea canvas;

    Menus(daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen);

    void splashScreen(
        daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen);
    void
    drawMenis(daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen);
    void drawSawGraphics(
        daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen,
        uint8_t                                                 xinit,
        uint8_t                                                 yinit,
        uint8_t                                                 xfinal,
        uint8_t                                                 yfinal,
        uint8_t                                                 iterations);
    void drawWaveGraphics(
        daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen);
    void Menu1(daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen);
};
#endif
#ifndef MENUS_H
#define MENUS_H
#include "daisy_seed.h"
#include "dev/oled_ssd130x.h"
#include "globalFunc.h"
//TODO: Organizar declarações
//TODO: Adicionar public e private

class Menus
{
  public:
    float         splashScreenRectY = 0;
    const uint8_t marginLeft        = 15;
    const uint8_t marginRight       = 10;
    const uint8_t marginUp          = 10;
    const uint8_t marginBottom      = 15;
    uint8_t*      iterations;
    int           arcAngle          = 0;
    uint8_t       cursorPos         = 0;
    uint8_t       headerGridWidth   = 20;
    char          oscIdString[6]    = "OSC I";
    char          gainLabel[6]      = "0.0db";
    bool          isOn              = true;
    float         gain              = 1;
    int           waveSelectorIndex = 0;
    struct graphicsArea
    {
        //bottom-left x1,y1 __ top-right x2,y2
        uint8_t x1;
        uint8_t y1;
        uint8_t x2;
        uint8_t y2;
    };
    graphicsArea waveCanvas;
    graphicsArea parametersCanvas;
    graphicsArea infoCanvas;


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
    void Menu1(hardwareToInit* hw, VoiceManager* VoiceMng);
    void
    drawCursor(daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen,
               uint8_t                                                 x,
               uint8_t                                                 y,
               uint8_t                                                 radius,
               int                                                     sweep);
    void
    drawInfo(daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen);
    void
    drawIcons(daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen,
              uint8_t                                                 x,
              uint8_t                                                 y,
              uint8_t waveFormSelector);

    void
    drawIOIcon(daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen);
    void onOffHandler(hardwareToInit* hw, VoiceManager* VoiceMng);
    void drawHorizontalToggle(
        daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen,
        uint8_t                                                 x,
        uint8_t                                                 y,
        uint8_t                                                 radius,
        bool                                                    on,
        bool                                                    state,
        const char*                                             label);
    void drawSilenceGraphics(
        daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen);
    void gainHandler(hardwareToInit* hw, VoiceManager* VoiceMng);
    void drawGainIcon(
        daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen);
    void
    drawSlider(daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen,
               float                                                   x,
               float                                                   y,
               float                                                   width,
               float                                                   height,
               float                                                   on,
               float                                                   amount);
    void drawWaveFormIcon(
        daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen,
        uint8_t waveFormSelector);
    void
    drawSawIcon(daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen);
    void drawSquareIcon(
        daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen);
    void drawTriangleIcon(
        daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen);
    void drawSineIcon(
        daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen);
};


#endif
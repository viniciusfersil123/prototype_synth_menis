#include "menus.h"
//TODO:Global ColorTemplate
//TODO:Global Screen
Menus::Menus(daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen)
{
    //bottom-left x1,y1 __ top-right x2,y2
    this->canvas.x1 = marginLeft;
    this->canvas.y1 = screen->Height() - marginBottom;
    this->canvas.x2 = screen->Width() - (marginLeft+marginRight) ;
    this->canvas.y2 = marginUp + 20;
}


void Menus::drawMenis(
    daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen)
{
    bool colorTemplate = false;
    screen->Fill(colorTemplate);
    //RECTANGLE
    screen->DrawRect(screen->Width() / 2 - 10,
                     6,
                     screen->Width() / 2 + 12,
                     33,
                     !colorTemplate,
                     true);
    //M
    screen->DrawLine(screen->Width() / 2 - 10,
                     37,
                     screen->Width() / 2 - 10,
                     52,
                     !colorTemplate);
    screen->DrawLine(screen->Width() / 2 - 10,
                     37,
                     screen->Width() / 2 - 10 + 3,
                     52,
                     !colorTemplate);
    screen->DrawLine(screen->Width() / 2 - 10 + 3,
                     52,
                     screen->Width() / 2 - 10 + 6,
                     37,
                     !colorTemplate);
    screen->DrawLine(screen->Width() / 2 - 10 + 6,
                     37,
                     screen->Width() / 2 - 10 + 6,
                     52,
                     !colorTemplate);
    //H
    screen->DrawLine(screen->Width() / 2 - 10 + 8,
                     52,
                     screen->Width() / 2 - 10 + 8,
                     37,
                     !colorTemplate);
    screen->DrawLine(screen->Width() / 2 - 10 + 8,
                     45,
                     screen->Width() / 2 - 10 + 11,
                     45,
                     !colorTemplate);
    screen->DrawLine(screen->Width() / 2 - 10 + 11,
                     52,
                     screen->Width() / 2 - 10 + 11,
                     37,
                     !colorTemplate);
    //N
    screen->DrawLine(screen->Width() / 2 - 10 + 13,
                     37,
                     screen->Width() / 2 - 10 + 13,
                     52,
                     !colorTemplate);
    screen->DrawLine(screen->Width() / 2 - 10 + 13,
                     37,
                     screen->Width() / 2 - 10 + 16,
                     52,
                     !colorTemplate);
    screen->DrawLine(screen->Width() / 2 - 10 + 16,
                     52,
                     screen->Width() / 2 - 10 + 16,
                     37,
                     !colorTemplate);
    //I
    screen->DrawLine(screen->Width() / 2 - 10 + 18,
                     52,
                     screen->Width() / 2 - 10 + 18,
                     37,
                     !colorTemplate);

    //S
    screen->DrawLine(screen->Width() / 2 - 10 + 20,
                     37,
                     screen->Width() / 2 - 10 + 22,
                     37,
                     !colorTemplate);
    screen->DrawLine(screen->Width() / 2 - 10 + 20,
                     37,
                     screen->Width() / 2 - 10 + 22,
                     44,
                     !colorTemplate);
    screen->DrawLine(screen->Width() / 2 - 10 + 22,
                     44,
                     screen->Width() / 2 - 10 + 20,
                     52,
                     !colorTemplate);
    screen->DrawLine(screen->Width() / 2 - 10 + 20,
                     52,
                     screen->Width() / 2 - 10 + 22,
                     52,
                     !colorTemplate);
    //Animation Overlay
    screen->DrawRect(0,
                     this->splashScreenRectY + 2,
                     screen->Width(),
                     (screen->Height() / 2 + this->splashScreenRectY) + 2,
                     colorTemplate,
                     true);

    screen->DrawRect(0,
                     screen->Height() / 2 - (this->splashScreenRectY + 2),
                     screen->Width(),
                     (screen->Height() - this->splashScreenRectY) + 2,
                     colorTemplate,
                     true);
    this->splashScreenRectY = this->splashScreenRectY - 0.1;
    screen->Update();
}

void Menus::drawSawGraphics(
    daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen,
    uint8_t                                                 x,
    uint8_t                                                 y,
    uint8_t                                                 width,
    uint8_t                                                 height,
    uint8_t                                                 iterations)
{
    for(size_t i = 0; i < iterations; i++)
    {
        int ratio = width / iterations;
        screen->DrawLine(
            x + ratio * i, y, x + ratio * (i + 1), y - height, true);
        screen->DrawLine(
            x + ratio * (i + 1), y - height, x + ratio * (i + 1), y, true);
    }
}

void Menus::drawWaveGraphics(
    daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen)
{
    drawSawGraphics(screen,
                    this->canvas.x1,
                    this->canvas.y1,
                    this->canvas.x2,
                    (screen->Height())-(this->canvas.y2),
                    7);
}

void Menus::splashScreen(
    daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen)
{
    drawMenis(screen);
}

void Menus::Menu1(
    daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen)
{
    screen->Fill(false);
    drawWaveGraphics(screen);
    screen->Update();
}
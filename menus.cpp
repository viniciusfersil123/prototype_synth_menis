#include "menus.h"
#include <math.h>
//TODO:Global ColorTemplate
//TODO:Global Screen
//TODO:Interpolação Linear entre a mudança de iterations
//TODO:Refatorar Cursor
Menus::Menus(daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen)
{
    //bottom-left x1,y1 __ top-right x2,y2
    this->waveCanvas.x1 = screen->Width() / 2 + 7;
    this->waveCanvas.y1 = screen->Height() - marginBottom / 2;
    this->waveCanvas.x2 = screen->Width() / 2 - marginRight;
    this->waveCanvas.y2 = marginUp * 3.75;

    this->parametersCanvas.x1 = marginLeft / 3;
    this->parametersCanvas.y1 = 0;
    this->parametersCanvas.x2 = screen->Width() - marginRight / 3;
    this->parametersCanvas.y2 = marginUp * 2;

    this->infoCanvas.x1  = this->parametersCanvas.x1;
    this->infoCanvas.y1  = this->parametersCanvas.y2;
    this->infoCanvas.x2 = this->waveCanvas.x1;
    this->infoCanvas.y2  = this->waveCanvas.y1;
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

void Menus::drawCursor(
    daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen,
    uint8_t                                                 x,
    uint8_t                                                 y,
    uint8_t                                                 radius,
    int                                                     sweep)
{
    screen->DrawArc(x, y, radius, arcAngle, 45 + sweep, true);
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
                    this->waveCanvas.x1,
                    this->waveCanvas.y1,
                    this->waveCanvas.x2,
                    (screen->Height()) - (this->waveCanvas.y2),
                    *iterations);
}

void Menus::splashScreen(
    daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen)
{
    drawMenis(screen);
}

void Menus::drawInfo(
    daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen)
{
    // sprintf(this->oscIdString, "Semi_st");
    int cursorX;
    int cursorY;
    cursorX = (this->infoCanvas.x2/2-(sizeof(this->oscIdString)))-9;
    cursorY = this->infoCanvas.y1 + 7;
    screen->SetCursor(cursorX, cursorY);
    screen->WriteString(this->oscIdString, Font_6x8, true);
}

void Menus::Menu1(hardwareToInit* hw)
{
    hw->oledScreen.Fill(false);
    if(hw->buttonRight.RisingEdge())
    {
        this->cursorPos < 5 ? this->cursorPos++ : this->cursorPos = 5;
    }
    if(hw->buttonLeft.RisingEdge())
    {
        this->cursorPos > 0 ? this->cursorPos-- : this->cursorPos = 0;
    }
    drawCursor(&hw->oledScreen,
               uint8_t(marginLeft + (this->cursorPos) * this->headerGridWidth),
               marginUp - 3,
               7,
               ((sin(arcAngle * M_PI / 180) + 1) * 0.5) * 90);
    arcAngle = int((arcAngle - (sin(arcAngle * M_PI / 180) + 2))) % 360;
    // hw->oledScreen.DrawRect(this->parametersCanvas.x1,
    //                         this->parametersCanvas.y1,
    //                         this->parametersCanvas.x2,
    //                         this->parametersCanvas.y2,
    //                         true,
    //                         false);
    hw->oledScreen.DrawLine(hw->oledScreen.Width()/4,this->infoCanvas.y1,((hw->oledScreen.Width() - hw->oledScreen.Width()/4))+3,this->infoCanvas.y1,true);
    hw->oledScreen.DrawLine(hw->oledScreen.Width()/2, this->infoCanvas.y1 + 4,hw->oledScreen.Width()/2, hw->oledScreen.Height()-marginBottom,true);
    // hw->oledScreen.DrawRect(this->infoCanvas.x1,
    //                         this->infoCanvas.y1,
    //                         this->infoCanvas.x2,
    //                         this->infoCanvas.y2,true,false);
    drawInfo(&hw->oledScreen);
    drawWaveGraphics(&hw->oledScreen);
    hw->oledScreen.Update();
}
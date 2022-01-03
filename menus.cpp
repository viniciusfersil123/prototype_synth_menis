#include "menus.h"
#include <math.h>
//TODO:Global ColorTemplate
//TODO:Global Screen
//TODO:Interpolação Linear entre a mudança de iterations e movimento cursor

//TODO:Resolver Strings


//TODO:Implementar DSP Ganho
//TODO: passar amplitude para drawWave
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

    this->infoCanvas.x1 = this->parametersCanvas.x1;
    this->infoCanvas.y1 = this->parametersCanvas.y2;
    this->infoCanvas.x2 = this->waveCanvas.x1;
    this->infoCanvas.y2 = this->waveCanvas.y1;
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

void Menus::drawIcons(
    daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen,
    uint8_t                                                 x,
    uint8_t                                                 y)
{
    drawIOIcon(screen);
    drawGainIcon(screen);
}

void Menus::drawIOIcon(
    daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen)
{
    screen->DrawArc(marginLeft, marginUp - 3,4,135,275,true);
    screen->DrawLine(marginLeft, marginUp - 8, marginLeft, marginUp - 4, true);
}

void Menus::drawGainIcon(
    daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen)
{
    for(uint8_t i = 0; i < 5; i++)
    {
        screen->DrawLine(((marginLeft + this->headerGridWidth) - 4) + i * 2,
                         (marginUp - 1),
                         ((marginLeft + this->headerGridWidth) - 4) + i * 2,
                         (marginUp - 1) - i,
                         true);
    }
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
        screen->DrawLine(x + ratio * i,
                         y,
                         x + ratio * (i + 1),
                         (y - (height * this->gain)),
                         true);
        screen->DrawLine(x + ratio * (i + 1),
                         (y - (height * this->gain)),
                         x + ratio * (i + 1),
                         y,
                         true);
    }
}

void Menus::drawHorizontalToggle(
    daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen,
    uint8_t                                                 x,
    uint8_t                                                 y,
    uint8_t                                                 radius,
    bool                                                    on,
    bool                                                    state,
    const char*                                             label)
{
    screen->DrawArc(x, y, radius, 270, 180, on);
    screen->DrawArc(x - radius, y, radius, 270, -180, on);
    screen->DrawLine(x, y - radius, x - radius, y - radius, on);
    screen->DrawLine(x, y + radius, x - radius, y + radius, on);
    screen->SetCursor(x - (radius * 1.75), y - (radius * 2.5));
    screen->WriteString(label, Font_7x10, on);

    if(state == true)
    {
        for(int i = 1; i <= radius; i++)
        {
            screen->DrawCircle(x, y, (radius / 2) - i, on);
            screen->DrawCircle(x, y, (radius / 2) - i, on);
            screen->SetCursor(x - radius * 1.35, y - radius / 3);
            screen->WriteString("I", Font_6x8, on);
        }
    }
    else
    {
        for(int i = 1; i <= radius; i++)
        {
            screen->DrawCircle(x - radius, y, (radius / 2) - i, on);
            screen->DrawCircle(x - radius, y, (radius / 2) - i, on);
            screen->SetCursor(x - radius * 0.15, y - radius / 3);
            screen->WriteString("0", Font_6x8, on);
        }
    }
}

void Menus::drawSilenceGraphics(
    daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen)
{
    for(uint8_t i = 0; i < screen->Width() - 15; i++)
    {
        screen->DrawPixel(
            (screen->Width() / 2) + 15 + (i * 4), screen->Height() / 1.5, true);
    }
}

void Menus::drawWaveGraphics(
    daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen)
{
    // drawSawGraphics(screen,
    //                 this->waveCanvas.x1,
    //                 this->waveCanvas.y1,
    //                 this->waveCanvas.x2,
    //                 (screen->Height()) - (this->waveCanvas.y2),
    //                 *iterations);
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
    cursorX = (this->infoCanvas.x2 / 2 - (sizeof(this->oscIdString))) - 9;
    cursorY = this->infoCanvas.y1 + 7;
    screen->SetCursor(cursorX, cursorY);
    screen->WriteString(this->oscIdString, Font_6x8, true);


    if(this->cursorPos == 1)
    {
        cursorX = (this->infoCanvas.x2 / 2 - (sizeof(this->oscIdString))) - 9;
        cursorY = screen->Height() - (marginBottom - 3);
        screen->SetCursor(cursorX, cursorY);
        screen->WriteString(this->gainLabel, Font_6x8, true);
    }
}

void Menus::onOffHandler(hardwareToInit* hw, VoiceManager* VoiceMng)
{
    if(hw->encoderRight.Increment() != 0)
    {
        hw->encoderRight.Increment() == 1 ? this->isOn = true
                                          : this->isOn = false;
    }
    if(!this->isOn)
    {
        for(uint8_t i = 0; i < VoiceMng->NumberOfVoices; i++)
        {
            VoiceMng->voices[i].osc.SetAmp(0);
        }
    }
}

void Menus::gainHandler(hardwareToInit* hw, VoiceManager* VoiceMng) {}


void Menus::drawSlider(
    daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* screen,
    float                                                   x,
    float                                                   y,
    float                                                   width,
    float                                                   height,
    float                                                   on,
    float                                                   amount)
{
    uint8_t padding = 3;
    screen->DrawRect(x - padding,
                     y - padding,
                     x + width + padding,
                     (y + height) + padding,
                     on,
                     false);
    screen->DrawRect(x, y, x + width * amount, y + height, on, true);
}


void Menus::Menu1(hardwareToInit* hw, VoiceManager* VoiceMng)
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
    drawIcons(&hw->oledScreen, 0, 0);
    hw->oledScreen.DrawLine(
        hw->oledScreen.Width() / 4,
        this->infoCanvas.y1,
        ((hw->oledScreen.Width() - hw->oledScreen.Width() / 4)) + 3,
        this->infoCanvas.y1,
        true);
    hw->oledScreen.DrawLine(hw->oledScreen.Width() / 2,
                            this->infoCanvas.y1 + 4,
                            hw->oledScreen.Width() / 2,
                            hw->oledScreen.Height() - marginBottom,
                            true);
    // hw->oledScreen.DrawRect(this->infoCanvas.x1,
    //                         this->infoCanvas.y1,
    //                         this->infoCanvas.x2,
    //                         this->infoCanvas.y2,true,false);
    drawInfo(&hw->oledScreen);
    isOn ? drawWaveGraphics(&hw->oledScreen)
         : drawSilenceGraphics(&hw->oledScreen);
    switch(this->cursorPos)
    {
        case 0:
            drawHorizontalToggle(&hw->oledScreen,
                                 marginLeft + 23,
                                 hw->oledScreen.Height() - (marginBottom + 1),
                                 8,
                                 true,
                                 isOn,
                                 "");
            onOffHandler(hw, VoiceMng);
            break;
        case 1:
            drawSlider(&hw->oledScreen,
                       marginLeft - 5,
                       hw->oledScreen.Height() - (marginBottom + 7),
                       45,
                       1,
                       true,
                       this->gain);

            if(this->gain > 1)
            {
                this->gain = 1;
            }
            else if(this->gain < 0)
            {
                this->gain = 0;
            }
            else
            {
                this->gain += (float(hw->encoderRight.Increment())) / 45;
            }
            gainHandler(hw, VoiceMng);
            break;
        default: break;
    }

    hw->oledScreen.Update();
}
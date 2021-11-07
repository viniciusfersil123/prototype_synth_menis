#include "menus.h"

void Menus::SplashScreen(
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
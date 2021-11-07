#ifndef GLOBALFUNC_H
#define GLOBALFUNC_H
#include "daisy_seed.h"
#include "dev/oled_ssd130x.h"

void hardwareInit(daisy::DaisySeed* seed, daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* oledScreen);


#endif
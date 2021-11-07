#ifndef GLOBALFUNC_H
#define GLOBALFUNC_H
#include "daisy_seed.h"
#include "daisysp.h"
#include "dev/oled_ssd130x.h"


void SynthInit(
    daisy::DaisySeed*                                       seed,
    daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* oledScreen,
    daisysp::Oscillator*                                      osc);


#endif
#ifndef GLOBALFUNC_H
#define GLOBALFUNC_H
#include "daisy_seed.h"
#include "daisysp.h"
#include "dev/oled_ssd130x.h"
using namespace daisy;
using namespace daisysp;

void SynthInit(
    DaisySeed*                                       seed,
    OledDisplay<SSD130x4WireSpi128x64Driver>* oledScreen,
    Oscillator*                                      osc, MidiHandler<MidiUartTransport>* midi);

void HandleMidiMessage(MidiEvent m, daisysp::Oscillator* osc);

#endif
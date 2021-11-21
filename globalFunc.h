#ifndef GLOBALFUNC_H
#define GLOBALFUNC_H
#include "daisy_seed.h"
#include "daisysp.h"
#include "dev/oled_ssd130x.h"
#include "Voice.h"
#include "VoiceManager.h"
using namespace daisy;
using namespace daisysp;

struct hardwareToInit
{
    public:
    DaisySeed                                seed;
    OledDisplay<SSD130x4WireSpi128x64Driver> oledScreen;
    MidiHandler<MidiUartTransport>           midi;
    Encoder                                  encoderRight;
    
};

void SynthInit(hardwareToInit* hw, VoiceManager* vMng);

void HandleMidiMessage(MidiEvent m, VoiceManager* voiceMng);

#endif
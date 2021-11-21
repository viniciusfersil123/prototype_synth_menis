#ifndef GLOBALFUNC_H
#define GLOBALFUNC_H
#include "daisy_seed.h"
#include "daisysp.h"
#include "dev/oled_ssd130x.h"
#include "Voice.h"
#include "VoiceManager.h"
using namespace daisy;
using namespace daisysp;

void SynthInit(DaisySeed*                                seed,
               OledDisplay<SSD130x4WireSpi128x64Driver>* oledScreen,
               Voice*                                    osc,
               MidiHandler<MidiUartTransport>*           midi,
               int                                       numVoices,
               Encoder*                                  encoderRight);

void HandleMidiMessage(MidiEvent m, VoiceManager* voiceMng);

#endif
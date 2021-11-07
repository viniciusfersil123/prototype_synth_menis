//INCLUDES
#include <stdio.h>
#include <string.h>
#include "daisy_seed.h"
#include "daisysp.h"
#include "dev/oled_ssd130x.h"
#include "globalFunc.h"
#include "menus.h"
//USING
using namespace daisy;
using namespace daisysp;
using SynthOled = OledDisplay<SSD130x4WireSpi128x64Driver>;
//VARIABLES
DaisySeed                              hw;
SynthOled                              display;
Menus                                  synthMenus;
Oscillator                             osc;
MidiHandler<MidiUartTransport>         midi;
MidiHandler<MidiUartTransport>::Config midi_cfg;

void HandleMidiMessage(MidiEvent m)
{
    switch(m.type)
    {
        case NoteOn:

        {
            NoteOnEvent p = m.AsNoteOn();
            if(m.data[1] != 0)
            {
                osc.SetFreq(mtof(p.note));
                osc.SetAmp(0.7);
            }
        }
        break;

        case NoteOff:
        {
            if(m.data[1] != 0) {
                osc.SetAmp(0);
            }
        }
        break;
        default: break;
    }
}


void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
    float osc_out;
    for(size_t i = 0; i < size; i++)
    {
        osc_out   = osc.Process();
        out[0][i] = osc_out;
        out[1][i] = osc_out;
    }
}

int main(void)
{
    SynthInit(&hw, &display, &osc);
    hw.usb_handle.Init(UsbHandle::FS_INTERNAL);
    midi.Init(midi_cfg);
    midi.StartReceive();
    hw.StartAudio(AudioCallback);
    while(1)
    {
        midi.Listen();
        synthMenus.SplashScreen(&display);
        if(midi.HasEvents())
        {
            HandleMidiMessage(midi.PopEvent());
        }
    }
}

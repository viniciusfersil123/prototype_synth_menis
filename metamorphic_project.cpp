#include "daisy_seed.h"
#include "daisysp.h"
#include "dev/oled_ssd130x.h"
#include "menus.h"
#include "Voice.h"
#include "VoiceManager.h"
#include "globalFunc.h"
//USING
using SynthOled = OledDisplay<SSD130x4WireSpi128x64Driver>;
//VARIABLES
DaisySeed                      hw;
SynthOled                      display;
Menus                          synthMenus;
VoiceManager                   voiceMng;
MidiHandler<MidiUartTransport> midi;


void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
    float osc_out;
    for(size_t i = 0; i < size; i++)
    {
        for(size_t i = 0; i < voiceMng.NumberOfVoices; i++)
        {
            if(i == 0)
            {
                osc_out = voiceMng.voices[i].osc.Process();
            }
            else
            {
                osc_out += voiceMng.voices[i].osc.Process();
            }
        }
        out[0][i] = osc_out / voiceMng.NumberOfVoices;
        out[1][i] = osc_out / voiceMng.NumberOfVoices;
    }
}

int main(void)
{
    SynthInit(&hw, &display, voiceMng.voices, &midi, voiceMng.NumberOfVoices);
    hw.usb_handle.Init(UsbHandle::FS_INTERNAL);
    hw.StartAudio(AudioCallback);
    while(1)
    {
        midi.Listen();
        synthMenus.splashScreen(&display);
        if(midi.HasEvents())
        {
            HandleMidiMessage(midi.PopEvent(), &voiceMng);
        }
    }
}

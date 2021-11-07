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
DaisySeed  hw;
SynthOled  display;
Menus      synthMenus;
Oscillator osc;


void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
    float osc_out;
    for(size_t i = 0; i < size; i++)
    {
        osc_out = osc.Process();
        out[0][i] = osc_out;
        out[1][i] = osc_out ;
    }
}

int main(void)
{
    SynthInit(&hw, &display, &osc);
    hw.StartAudio(AudioCallback);
    while(1)
    {
        synthMenus.SplashScreen(&display);
    }
}

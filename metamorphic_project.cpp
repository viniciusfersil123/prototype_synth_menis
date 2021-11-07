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
DaisySeed hw;
SynthOled display;
Menus     synthMenus;

void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
    for(size_t i = 0; i < size; i++)
    {
        out[0][i] = in[0][i];
        out[1][i] = in[1][i];
    }
}

int main(void)
{
    hardwareInit(&hw, &display);
    while(1)
    {
        synthMenus.SplashScreen(&display);
    }
}

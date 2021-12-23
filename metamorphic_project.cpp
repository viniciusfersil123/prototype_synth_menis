#include "daisy_seed.h"
#include "daisysp.h"
#include "dev/oled_ssd130x.h"
#include "globalFunc.h"
#include "menus.h"
#include "Voice.h"
#include "VoiceManager.h"

//USING
using SynthOled = OledDisplay<SSD130x4WireSpi128x64Driver>;
//TODO:Rever tipos
//TODO: Refatorar polifonia para seleção otimizada de voz, ou lidar com outra forma com o voice stealing
//VARIABLES
bool           splashScreenRunning  = true;
int            splashScreenDuration = 0;
uint8_t        iterations           = 3;
hardwareToInit hwToInit;
VoiceManager   voiceMng;
Menus          synthMenus(&hwToInit.oledScreen);


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
                osc_out = voiceMng.voices[i].osc.Process()*synthMenus.gain;
            }
            else
            {
                osc_out += voiceMng.voices[i].osc.Process()*synthMenus.gain;
            }
        }
        out[0][i] = osc_out / voiceMng.NumberOfVoices;
        out[1][i] = osc_out / voiceMng.NumberOfVoices;
    }
}

int main(void)
{
    SynthInit(&hwToInit, &voiceMng);
    hwToInit.seed.usb_handle.Init(UsbHandle::FS_INTERNAL);
    hwToInit.seed.StartAudio(AudioCallback);
    while(1)
    {
        hwToInit.encoderRight.Debounce();
        hwToInit.buttonLeft.Debounce();
        hwToInit.buttonRight.Debounce();
        //TODO: Refatorar nome de variáveies iterations
        // iterations += hwToInit.encoderRight.Increment();
        synthMenus.iterations = &iterations;
        hwToInit.midi.Listen();
        if(splashScreenRunning)
        {
            synthMenus.splashScreen(&hwToInit.oledScreen);
            splashScreenDuration++;
            splashScreenRunning = splashScreenDuration < 1024;
        }
        else
        {
            synthMenus.Menu1(&hwToInit,&voiceMng);
        }
        if(hwToInit.midi.HasEvents())
        {
            HandleMidiMessage(hwToInit.midi.PopEvent(), &voiceMng);
        }
    }
}

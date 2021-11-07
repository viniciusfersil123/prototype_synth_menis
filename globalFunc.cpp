#include "globalFunc.h"

void SynthInit(
    daisy::DaisySeed*                                       seed,
    daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* oledScreen,
    daisysp::Oscillator*                                      osc)
{
    seed->Configure();
    seed->Init();
    /** Configure the Display */
    daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>::Config disp_cfg;
    disp_cfg.driver_config.transport_config.pin_config.dc    = seed->GetPin(9);
    disp_cfg.driver_config.transport_config.pin_config.reset = seed->GetPin(30);
    /** And Initialize */
    oledScreen->Init(disp_cfg);
    osc->Init(seed->AudioSampleRate());
    osc->SetWaveform(osc->WAVE_SAW);
    osc->SetAmp(0.5);
    osc->SetFreq(440);
}

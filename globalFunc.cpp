#include "globalFunc.h"

void SynthInit(
    DaisySeed*                                       seed,
    OledDisplay<SSD130x4WireSpi128x64Driver>* oledScreen,
    Oscillator*                                    osc,
    MidiHandler<MidiUartTransport>*                         midi)
{
    MidiHandler<MidiUartTransport>::Config midi_cfg;
    seed->Configure();
    seed->Init();
    /** Configure the Display */
    OledDisplay<SSD130x4WireSpi128x64Driver>::Config disp_cfg;
    disp_cfg.driver_config.transport_config.pin_config.dc    = seed->GetPin(9);
    disp_cfg.driver_config.transport_config.pin_config.reset = seed->GetPin(30);
    /** And Initialize */
    oledScreen->Init(disp_cfg);
    osc->Init(seed->AudioSampleRate());
    osc->SetWaveform(osc->WAVE_SAW);
    osc->SetAmp(0.5);
    osc->SetFreq(440);
    midi->Init(midi_cfg);
    midi->StartReceive();
}

void HandleMidiMessage(MidiEvent m, Oscillator* osc)
{
    switch(m.type)
    {
        case NoteOn:

        {
            NoteOnEvent p = m.AsNoteOn();
            if(m.data[1] != 0)
            {
                osc->SetFreq(mtof(p.note));
                osc->SetAmp(0.7);
            }
        }
        break;

        case NoteOff:
        {
            if(m.data[1] != 0)
            {
                osc->SetAmp(0);
            }
        }
        break;
        default: break;
    }
}
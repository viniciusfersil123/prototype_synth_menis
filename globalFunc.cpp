#include "globalFunc.h"
unsigned int polyIndexOn  = 0;
unsigned int polyIndexOff = 0;

void         SynthInit(DaisySeed*                                seed,
                       OledDisplay<SSD130x4WireSpi128x64Driver>* oledScreen,
                       Voice*                                    voice,
                       MidiHandler<MidiUartTransport>*           midi,
                       int                                       numVoices,
                       Encoder*                                  encoderRight)
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
    for(int i = 0; i < numVoices; i++)
    {
        voice[i].osc.Init(seed->AudioSampleRate());
        voice[i].osc.SetWaveform(voice[i].osc.WAVE_SAW);
        voice[i].osc.SetAmp(0.5);
        voice[i].osc.SetFreq(0);
    }
    midi->Init(midi_cfg);
    midi->StartReceive();
    encoderRight->Init(seed->GetPin(16),
                       seed->GetPin(17),
                       seed->GetPin(15),
                       seed->AudioSampleRate());
}

void HandleMidiMessage(MidiEvent m, VoiceManager* voiceMng)
{
    switch(m.type)
    {
        case NoteOn:

        {
            NoteOnEvent p = m.AsNoteOn();
            if(m.data[1] != 0)
            {
                if(polyIndexOn <= voiceMng->NumberOfVoices - 1)
                {
                    voiceMng->voices[polyIndexOn].osc.SetFreq(mtof(p.note));
                    voiceMng->voices[polyIndexOn].osc.SetAmp(0.7);
                    polyIndexOn++;
                }
                else
                {
                    polyIndexOn = 0;
                    voiceMng->voices[polyIndexOn].osc.SetFreq(mtof(p.note));
                    voiceMng->voices[polyIndexOn].osc.SetAmp(0.7);
                }
            }
        }
        break;

        case NoteOff:
        {
            if(m.data[1] != 0)
            {
                if(polyIndexOff <= voiceMng->NumberOfVoices - 1)
                {
                    voiceMng->voices[polyIndexOff].osc.SetAmp(0);
                    polyIndexOff++;
                }
                else
                {
                    polyIndexOff = 0;
                    voiceMng->voices[polyIndexOff].osc.SetAmp(0);
                }
            }
        }
        break;
        default: break;
    }
}
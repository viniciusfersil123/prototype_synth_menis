#include "globalFunc.h"
unsigned int polyIndexOn  = 0;
unsigned int polyIndexOff = 0;


void SynthInit(hardwareToInit* hw, VoiceManager* vMng)
{
    MidiHandler<MidiUartTransport>::Config midi_cfg;
    hw->seed.Configure();
    hw->seed.Init();
    OledDisplay<SSD130x4WireSpi128x64Driver>::Config disp_cfg;
    disp_cfg.driver_config.transport_config.pin_config.dc = hw->seed.GetPin(9);
    disp_cfg.driver_config.transport_config.pin_config.reset
        = hw->seed.GetPin(30);
    hw->oledScreen.Init(disp_cfg);
    hw->buttonLeft.Init(hw->seed.GetPin(27), hw->seed.AudioSampleRate());
    hw->buttonRight.Init(hw->seed.GetPin(26), hw->seed.AudioSampleRate());
    for(int i = 0; i < vMng->NumberOfVoices; i++)
    {
        vMng->voices[i].osc.Init(hw->seed.AudioSampleRate());
        vMng->voices[i].osc.SetWaveform(vMng->voices[i].osc.WAVE_SAW);
        vMng->voices[i].osc.SetAmp(0.5);
        vMng->voices[i].osc.SetFreq(0);
    }
    hw->midi.Init(midi_cfg);
    hw->midi.StartReceive();
    hw->encoderRight.Init(hw->seed.GetPin(16),
                          hw->seed.GetPin(17),
                          hw->seed.GetPin(15),
                          hw->seed.AudioSampleRate());
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
#ifndef VOICE_MANAGER_H
#define VOICE_MANAGER_H
#include "Voice.h"

class VoiceManager
{
  public:
    static const uint8_t NumberOfVoices = 12;
    Voice                voices[NumberOfVoices];
    Voice*               findFreeVoice();
    void                 onNoteOn(int noteNumber);
    void                 onNoteOff(int noteNumber);
    
};

#endif
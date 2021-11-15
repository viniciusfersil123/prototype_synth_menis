#include "VoiceManager.h"


Voice* VoiceManager::findFreeVoice() {
    Voice* freeVoice = NULL;
    for (int i = 0; i < NumberOfVoices; i++) {
        if (!voices[i].isActive) {
            freeVoice = &(voices[i]);
            break;
        }
    }
     return freeVoice;
}
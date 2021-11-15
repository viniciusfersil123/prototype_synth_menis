#ifndef VOICE_H
#define VOICE_H
#include "daisy_seed.h"
#include "daisysp.h"
using namespace daisy;
using namespace daisysp;

struct Voice
{
  public:
    Oscillator osc;
    bool       isActive;
};

#endif
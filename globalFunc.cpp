#include "globalFunc.h"

void hardwareInit(daisy::DaisySeed* seed, daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>* oledScreen){
    seed->Configure();
    seed->Init();
    /** Configure the Display */
    daisy::OledDisplay<daisy::SSD130x4WireSpi128x64Driver>::Config disp_cfg;
    disp_cfg.driver_config.transport_config.pin_config.dc    = seed->GetPin(9);
    disp_cfg.driver_config.transport_config.pin_config.reset = seed->GetPin(30);
    /** And Initialize */
   oledScreen->Init(disp_cfg);
}


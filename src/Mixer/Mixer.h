#pragma once

#include <Arduino.h>
#include "Axis/Axis.h"
#include "Button/Mode.h"
#include "Button/Switch.h"
#include "RC/ChannelInfo.h"

enum Axies {
    A = 0,
    E,
    T,
    R,
    AXIES_MAX,
};

class Mixer
{
public:
    Mixer();

    void update(uint32_t time);
    ChanellInfo getRCChanellInfo();

private:
    Axis* _axises[AXIES_MAX];
    Mode* _mode;
    Switch* _arm;
};

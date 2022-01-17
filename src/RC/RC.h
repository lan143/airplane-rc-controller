#pragma once

#include "Arduino.h"
#include "ChannelInfo.h"
#include "Crossfire.h"

#define SEND_PERIOD 16

class RC
{
public:
    RC(HardwareSerial* serial)
    {
        _serial = serial;
        _crossfire = new Crossfire(_serial);
    }

    void setChanellInfo(ChanellInfo info)
    {
        _currentChanellInfo = info;
    }

    void update(uint32_t currentTime);

private:
    void sendToRCModule();

private:
    HardwareSerial* _serial;
    ChanellInfo _currentChanellInfo;
    Crossfire* _crossfire;

    uint32_t _lastUpdateTime = 0;
};

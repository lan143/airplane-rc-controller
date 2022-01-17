#include "RC.h"

void RC::sendToRCModule()
{
    int16_t aux[16];
    for (uint8_t i = 0; i < 16; i++) {
        aux[i] = map(_currentChanellInfo.aux[i], 1000, 2000, -1024, 1024);
    }

    _crossfire->sendCrossfireChannelsFrame(aux);
}

void RC::update(uint32_t currentTime)
{
    if ((currentTime - _lastUpdateTime) > (1000 / SEND_PERIOD)) {
        sendToRCModule();
        _lastUpdateTime = currentTime;
    }
}

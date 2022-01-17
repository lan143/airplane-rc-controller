#include "Mixer.h"
#include "target.h"

Mixer::Mixer()
{
    _axises[A] = new Axis(PIN_Y, "pitch", 162, 782, 472, 30, true);
    _axises[E] = new Axis(PIN_X, "roll", 194, 813, 463, 50, true);
    _axises[T] = new Axis(PIN_Z, "throttle", 26, 1015, 520, 0, true);
    _axises[R] = new Axis(PIN_RY, "yaw", 0, 1023, 512, 30, false);

    _mode = new Mode;
    _mode->addButton(new Button(PIN_7, "Button 7"), 1000);
    _mode->addButton(new Button(PIN_8, "Button 8"), 1200);
    _mode->addButton(new Button(PIN_9, "Button 9"), 1400);
    _mode->addButton(new Button(PIN_10, "Button 10"), 1600);
    _mode->addButton(new Button(PIN_11, "Button 11"), 1800);
    _mode->addButton(new Button(PIN_12, "Button 12"), 2000);

    _arm = new Switch(PIN_ARM, "arm");
}

void Mixer::update(uint32_t time)
{
    for (uint8_t i = A; i < AXIES_MAX; i++) {
        _axises[i]->update(time);
    }

    _arm->update(time);
}

ChanellInfo Mixer::getRCChanellInfo()
{
    ChanellInfo info;
    memset(info.aux, 1000, 16);

    for (uint8_t i = A; i < AXIES_MAX; i++) {
        info.aux[i] = _axises[i]->getRadioValue();
    }

    info.aux[4] = _arm->getState() == SWITCH_STATE_DISABLED ? 1000 : 2000;
    info.aux[5] = _mode->getRadioValue();

    return info;
}

#include "Switch.h"

Switch::Switch(uint32_t pin, String name)
{
    _pin = pin;
    _name = name;

    pinMode(_pin, INPUT_PULLUP);
    attachInterrupt(_pin, [this]() {
        this->changeState();
    }, CHANGE);
}

void Switch::update(uint32_t time)
{
    _time = time;
}

void Switch::changeState()
{
    if (_time - _lastChangeStateTime > 300) {
        if (digitalRead(_pin)) {
            _state = SWITCH_STATE_ENABLED;
        } else {
            _state = SWITCH_STATE_DISABLED;
        }

        _lastChangeStateTime = _time;
    }
}

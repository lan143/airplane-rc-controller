#include "Axis.h"

Axis::Axis(int pin, String name, uint32_t min, uint32_t max, uint32_t center, uint32_t deadband, bool reverse)
{
    _pin = pin;
    _name = name;
    _min = min;
    _max = max;
    _center = center;
    _deadband = deadband;
    _reverse = reverse;

    pinMode(_pin, INPUT_ANALOG);

    _filter = new Kalman(30, 30, 0.1);
}

void Axis::update(uint32_t dt)
{
    uint32_t rawValue = analogRead(_pin);
    _value = _filter->filtered(rawValue);

    if (rawValue < _noise_min) {
        _noise_min = rawValue;
    }

    if (rawValue > _noise_max) {
        _noise_max = rawValue;
    }
}

uint32_t Axis::getRadioValue()
{
    uint32_t value = getValue();
    uint32_t radioValue = 0;

    if (((_center + _deadband) < value) || ((_center - _deadband) > value)) {
        if (value <= _center) {
            radioValue = map(getValue(), _min, _center, 1000, 1500);
        } else {
            radioValue = map(getValue(), _center, _max, 1500, 2000);
        }
    } else {
        radioValue = 1500;
    }

    if (radioValue < 1000) {
        radioValue = 1000;
    }

    if (radioValue > 2000) {
        radioValue = 2000;
    }

    if (_reverse) {
        radioValue = map(radioValue, 1000, 2000, 2000, 1000);
    }

    return radioValue;
}

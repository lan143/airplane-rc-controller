#pragma once

#include "Arduino.h"
#include "Filters/Kalman.h"

class Axis {
public:
    Axis(int pin, String name, uint32_t min, uint32_t max, uint32_t center, uint32_t deadband, bool reverse);

    void update(uint32_t dt);
    uint32_t getValue() { return _value; }
    uint32_t getRadioValue();
    String getName() { return _name; }

    uint32_t getMin() { return _noise_min; }
    uint32_t getMax() { return _noise_max; }

private:
    int _pin;
    String _name;
    Kalman* _filter;
    uint32_t _value = 0;

    // calibration data
    uint32_t _min;
    uint32_t _max;
    uint32_t _center;
    uint32_t _deadband;
    bool _reverse;

    uint32_t _noise_min = 1024;
    uint32_t _noise_max = 0;
};

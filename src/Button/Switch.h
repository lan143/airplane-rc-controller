#pragma once

#include <Arduino.h>

enum SwitchState {
    SWITCH_STATE_DISABLED,
    SWITCH_STATE_ENABLED
};

class Switch
{
public:
    Switch(uint32_t pin, String name);

    String getName() { return _name; }
    void update(uint32_t time);
    uint8_t getState() { return _state; }

private:
    void changeState();

private:
    uint32_t _pin;
    String _name;
    uint8_t _state;
    uint32_t _time;
    uint32_t _lastChangeStateTime;
};

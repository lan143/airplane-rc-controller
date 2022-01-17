#pragma once

#include <Arduino.h>
#include <list>
#include "Button.h"

struct ModeButton
{
    Button* button;
    uint16_t rcValue;
    bool active = false;
};

class Mode 
{
public:
    void addButton(Button* button, uint16_t value);
    uint16_t getRadioValue();

private:
    void pressButton(Button* button);

private:
    std::list<ModeButton> _buttons;
};

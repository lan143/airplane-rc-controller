#include "Mode.h"

void Mode::addButton(Button* button, uint16_t rcValue)
{
    ModeButton modeButton;
    modeButton.button = button;
    modeButton.rcValue = rcValue;

    if (_buttons.size() == 0) {
        modeButton.active = true;
    }

    button->addCallback([this](Button* button) {
        pressButton(button);
    });

    _buttons.push_back(modeButton);
}

void Mode::pressButton(Button* button)
{
    for (auto i = _buttons.begin(); i != _buttons.end(); i++) {
        if ((*i).button == button) {
            (*i).active = true;
        } else {
            (*i).active = false;
        }
    }
}

uint16_t Mode::getRadioValue()
{
    for (auto i = _buttons.begin(); i != _buttons.end(); i++) {
        if ((*i).active) {
            return (*i).rcValue;
        }
    }

    return 1000;
}

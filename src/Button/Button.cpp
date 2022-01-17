#include "Button.h"

Button::Button(uint32_t pin, String name)
{
    _pin = pin;
    _name = name;

    pinMode(_pin, INPUT_PULLUP);
    attachInterrupt(_pin, [this]() {
        this->pressButton();
    }, FALLING);
}

void Button::update(uint32_t time)
{
    _time = time;
}

void Button::pressButton()
{
    if (_time - _lastPressTime > 300) {
        for (auto i = _callbacks.begin(); i != _callbacks.end(); i++) {
            (*i)(this);
        }

        _lastPressTime = _time;
    }
}

void Button::addCallback(std::function<void(Button*)> callback)
{
    _callbacks.push_back(callback);
}

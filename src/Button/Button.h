#pragma once

#include <Arduino.h>
#include <list>

class Button
{
public:
    Button(uint32_t pin, String name);

    String getName() { return _name; }
    void update(uint32_t time);
    void addCallback(std::function<void(Button*)> callback);

private:
    void pressButton();

private:
    uint32_t _pin;
    String _name;
    uint32_t _time;
    uint32_t _lastPressTime;
    std::list<std::function<void(Button*)>> _callbacks;
};

#include <Arduino.h>
#include "Mixer/Mixer.h"
#include "RC/RC.h"

HardwareSerial serial(USART3);
HardwareSerial crossfire(USART1);

RC* rc;
Mixer* mixer;
uint32_t time;

void setup()
{
    serial.begin(115200);

    rc = new RC(&crossfire);
    mixer = new Mixer();
}

void loop()
{
    time = millis();

    mixer->update(time);
    rc->setChanellInfo(mixer->getRCChanellInfo());
    rc->update(time);
}

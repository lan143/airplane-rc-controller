#include "Crossfire.h"

void Crossfire::sendCrossfireChannelsFrame(int16_t channels[])
{
    CrossfirePulsesData data;
    memset(data.pulses, 0, CROSSFIRE_FRAME_MAXLEN);

    uint8_t * buf = data.pulses;
    *buf++ = MODULE_ADDRESS;
    *buf++ = 24; // 1(ID) + 22 + 1(CRC)
    uint8_t * crc_start = buf;
    *buf++ = CHANNELS_ID;
    uint32_t bits = 0;
    uint8_t bitsavailable = 0;

    for (int i = 0; i < CROSSFIRE_CHANNELS_COUNT; i++) { 
        int16_t std_value = i < CROSSFIRE_CHANNELS_COUNT ? channels[i] : 0;
        uint32_t val0 =  CROSSFIRE_CH_CENTER + ((std_value * 4) / 5);
        uint32_t val = constrain(val0, 0, 2 * CROSSFIRE_CH_CENTER);

        bits |= val << bitsavailable;
        bitsavailable += CROSSFIRE_CH_BITS;

        while (bitsavailable >= 8) {
            *buf++ = bits;
            bits >>= 8;
            bitsavailable -= 8;
        }
    }

    *buf++ = crc8(crc_start, 23);
    data.len = buf - data.pulses;

    // CrossFire - 3.36ms between frames; 0.64ms - frame length;
    // Gaps is LOW; Signal - High;
    // Each frame starts with 0xEE; 0x18;
    _serial->write(data.pulses, data.len);
}

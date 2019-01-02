#ifndef WIZBATTERY_H
#define WIZBATTERY_H

#include "SDL.h"
#include "SDL_wiz_dev.h"

class wizBattery
{
    public:

    static const Uint16 BATTERY_STATUS_HIGH  = 1;
    static const Uint16 BATTERY_STATUS_MID   = 2;
    static const Uint16 BATTERY_STATUS_LOW   = 3;
    static const Uint16 BATTERY_STATUS_EMPTY = 4;

    static Uint16 getBatteryStatus();
};

#endif // WIZBATTERY_H

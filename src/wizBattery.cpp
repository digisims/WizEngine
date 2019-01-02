#include "wizBattery.h"

Uint16 wizBattery::getBatteryStatus()
{
    Uint16 status;
    return SDL_GetBattryCheck(&status);
}

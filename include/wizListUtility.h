#ifndef WIZLISTUTILITY_H
#define WIZLISTUTILITY_H

#include "wizGameEntity.h"

#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>

class wizListUtility
{
    public:

    static std::vector<wizGameEntity*> difference(std::vector<wizGameEntity*>& _a, std::vector<wizGameEntity*>& _b);
    static std::vector<wizGameEntity*> combine(std::vector<wizGameEntity*>& _a, std::vector<wizGameEntity*>& _b);
};

#endif // WIZLISTUTILITY_H

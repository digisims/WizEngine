#ifndef WIZLIGHTMANAGER_H
#define WIZLIGHTMANAGER_H

#include "wizLight.h"
#include "wizUtility.h"

#include <vector>
#include <string>

class wizLightManager
{
    public:

    static const int MAX_LIGHTS = 4;

    static void initialize();
    static void destroy();

    static void applyGlobalSettings();
    static void undoGlobalSettings();
    static std::string applySettings(wizVector3 _position);
    static void undoSettings();

    static void addLight(wizLight* _light);
    static wizLight* getLight(unsigned int _idx);
    static void removeLight(unsigned int _idx);

    static unsigned int getLights();

    protected:

    static std::vector<wizLight*> lightList;
    static std::vector<unsigned int> order;
};

#endif // WIZLIGHTMANAGER_H

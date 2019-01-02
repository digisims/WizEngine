#ifndef WIZSOUNDCONTROLLER2D_H
#define WIZSOUNDCONTROLLER2D_H

#include "wizSoundController.h"
#include "wizSoundManager.h"
#include "wizVector2.h"

#include <string>
#include <map>

class wizSoundController2D : wizSoundController
{
    public:

    wizSoundController2D();
    virtual ~wizSoundController2D();

    void setPosition(wizVector2 _position);
    void setRadius(float _radius);
    wizVector2 getPosition();
    float getRadius();

    void playSound(std::string _filename, int _volume, wizVector2 _position);

    void update(float _dt);

    protected:

    void updateVolume(std::string _filename);

    wizVector2 position;
    float radius;
    std::map<std::string, wizVector2> positionMap;
    std::map<std::string, int> volumeMap;
};

#endif // WIZSOUNDCONTROLLER2D_H

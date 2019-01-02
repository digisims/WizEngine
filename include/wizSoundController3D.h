#ifndef WIZSOUNDCONTROLLER3D_H
#define WIZSOUNDCONTROLLER3D_H

#include "wizSoundController.h"
#include "wizSoundManager.h"
#include "wizVector3.h"

#include <string>
#include <map>

class wizSoundController3D : wizSoundController
{
    public:

    wizSoundController3D();
    virtual ~wizSoundController3D();

    void setPosition(wizVector3 _position);
    void setRadius(float _radius);
    wizVector3 getPosition();
    float getRadius();

    void playSound(std::string _filename, int _volume, wizVector3 _position);

    void update(float _dt);

    protected:

    void updateVolume(std::string _filename);

    wizVector3 position;
    float radius;
    std::map<std::string, wizVector3> positionMap;
    std::map<std::string, int> volumeMap;
};

#endif // WIZSOUNDCONTROLLER3D_H

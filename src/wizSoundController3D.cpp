#include "wizSoundController3D.h"

wizSoundController3D::wizSoundController3D()
{
}

wizSoundController3D::~wizSoundController3D()
{
}

void wizSoundController3D::setPosition(wizVector3 _position)
{
    position = _position;
}

void wizSoundController3D::setRadius(float _radius)
{
    radius = _radius;
}

wizVector3 wizSoundController3D::getPosition()
{
    return position;
}

float wizSoundController3D::getRadius()
{
    return radius;
}

void wizSoundController3D::playSound(std::string _filename, int _volume, wizVector3 _position)
{
    if (positionMap.find(_filename)==positionMap.end())
    {
        wizSoundManager::loadSample(_filename);
    }

    positionMap[_filename] = _position;
    volumeMap[_filename] = _volume;

    wizSoundManager::playSample(_filename);
}

void wizSoundController3D::updateVolume(std::string _filename)
{
    if (positionMap.find(_filename)!=positionMap.end() && wizSoundManager::isSamplePlaying(_filename))
    {
        float distance = positionMap[_filename].sub(position).length();
        float ratio = 1 - distance / radius;
        if (ratio < 0) ratio = 0;

        wizSoundManager::setSampleVolume(_filename, (int)(ratio * volumeMap[_filename]));
    }
}

void wizSoundController3D::update(float _dt)
{
    std::map<std::string, wizVector3>::iterator i;

    for (i = positionMap.begin(); i!=positionMap.end(); i++)
    {
        updateVolume(i->first);
    }
}

#include "wizSoundController2D.h"

wizSoundController2D::wizSoundController2D()
{
}

wizSoundController2D::~wizSoundController2D()
{
}

void wizSoundController2D::setPosition(wizVector2 _position)
{
    position = _position;
}

void wizSoundController2D::setRadius(float _radius)
{
    radius = _radius;
}

wizVector2 wizSoundController2D::getPosition()
{
    return position;
}

float wizSoundController2D::getRadius()
{
    return radius;
}

void wizSoundController2D::playSound(std::string _filename, int _volume, wizVector2 _position)
{
    if (positionMap.find(_filename)==positionMap.end())
    {
        wizSoundManager::loadSample(_filename);
    }

    positionMap[_filename] = _position;
    volumeMap[_filename] = _volume;

    wizSoundManager::playSample(_filename);
}

void wizSoundController2D::updateVolume(std::string _filename)
{
    if (positionMap.find(_filename)!=positionMap.end() && wizSoundManager::isSamplePlaying(_filename))
    {
        float distance = positionMap[_filename].sub(position).length();
        float ratio = 1 - distance / radius;
        if (ratio < 0) ratio = 0;

        wizSoundManager::setSampleVolume(_filename, (int)(ratio * volumeMap[_filename]));
    }
}

void wizSoundController2D::update(float _dt)
{
    std::map<std::string, wizVector2>::iterator i;

    for (i = positionMap.begin(); i!=positionMap.end(); i++)
    {
        updateVolume(i->first);
    }
}

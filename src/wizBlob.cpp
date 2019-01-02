#include "wizBlob.h"

wizBlob::wizBlob(std::string _texture, wizVector3 _minimum, wizVector3 _maximum, float _minimumDistance, float _maximumDistance)
{
    texture = _texture;
    minimum = _minimum;
    maximum = _maximum;
    minimumDistance = _minimumDistance;
    maximumDistance = _maximumDistance;

    wizTextureManager::loadTexture(texture);
}

wizBlob::~wizBlob()
{
}

std::string wizBlob::getTexture()
{
    return texture;
}

wizVector3 wizBlob::getMinimum()
{
    return minimum;
}

wizVector3 wizBlob::getMaximum()
{
    return maximum;
}

float wizBlob::getMinimumDistance()
{
    return minimumDistance;
}

float wizBlob::getMaximumDistance()
{
    return maximumDistance;
}

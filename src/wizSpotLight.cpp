#include "wizSpotLight.h"

wizSpotLight::wizSpotLight()
{
    ambient = NULL;
    diffuse = NULL;
    specular = NULL;
    position = NULL;
    direction = NULL;
}

wizSpotLight::wizSpotLight(wizColour* _ambient, wizColour* _diffuse, wizColour* _specular, wizVector3* _position, wizVector3* _direction, float _cutOff, float _exponent)
{
    ambient = _ambient;
    diffuse = _diffuse;
    specular = _specular;
    position = _position;
    direction = _direction;
    cutOff = _cutOff;
    exponent = _exponent;
}

wizSpotLight::~wizSpotLight()
{
    if (ambient!=NULL) delete ambient;
    if (diffuse!=NULL) delete diffuse;
    if (specular!=NULL) delete specular;
    if (position!=NULL) delete position;
    if (direction!=NULL) delete direction;
}

void wizSpotLight::applySettings()
{
    glEnable(GL_LIGHT0 + idx);
    glLightfv(GL_LIGHT0 + idx, GL_AMBIENT, ambient->getArray());
    glLightfv(GL_LIGHT0 + idx, GL_DIFFUSE, diffuse->getArray());
    glLightfv(GL_LIGHT0 + idx, GL_SPECULAR, specular->getArray());
    glLightfv(GL_LIGHT0 + idx, GL_POSITION, position->getArray(1));
    glLightfv(GL_LIGHT0 + idx, GL_SPOT_DIRECTION, direction->getArray());
    glLightf(GL_LIGHT0 + idx, GL_SPOT_CUTOFF, cutOff);
    glLightf(GL_LIGHT0 + idx, GL_SPOT_EXPONENT, exponent);
}

void wizSpotLight::setDirection(wizVector3* _direction)
{
    direction = _direction;
}

void wizSpotLight::setCutOff(float _cutOff)
{
    cutOff = _cutOff;
}

void wizSpotLight::setExponent(float _exponent)
{
    exponent = _exponent;
}

wizVector3* wizSpotLight::getDirection()
{
    return direction;
}

float wizSpotLight::getCutOff()
{
    return cutOff;
}

float wizSpotLight::getExponent()
{
    return exponent;
}

#include "wizLight.h"

wizLight::wizLight()
{
    ambient = NULL;
    diffuse = NULL;
    specular = NULL;
    position = NULL;
}

wizLight::~wizLight()
{
    if (ambient!=NULL) delete ambient;
    if (diffuse!=NULL) delete diffuse;
    if (specular!=NULL) delete specular;
    if (position!=NULL) delete position;
}

void wizLight::undoSettings()
{
    glDisable(GL_LIGHT0 + idx);
}

void wizLight::setIndex(unsigned int _idx)
{
    idx = _idx;
}

unsigned int wizLight::getIndex()
{
    return idx;
}

void wizLight::setAmbient(wizColour* _ambient)
{
    ambient = _ambient;
}

void wizLight::setDiffuse(wizColour* _diffuse)
{
    diffuse = _diffuse;
}

void wizLight::setSpecular(wizColour* _specular)
{
    specular = _specular;
}

void wizLight::setPosition(wizVector3* _position)
{
    position = _position;
}

wizColour* wizLight::getAmbient()
{
    return ambient;
}

wizColour* wizLight::getDiffuse()
{
    return diffuse;
}

wizColour* wizLight::getSpecular()
{
    return specular;
}

wizVector3* wizLight::getPosition()
{
    return position;
}

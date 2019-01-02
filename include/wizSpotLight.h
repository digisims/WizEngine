#ifndef WIZSPOTLIGHT_H
#define WIZSPOTLIGHT_H

#include "wizLight.h"

class wizSpotLight : public wizLight
{
    public:

    wizSpotLight();
    wizSpotLight(wizColour* _ambient, wizColour* _diffuse, wizColour* _specular, wizVector3* _position, wizVector3* _direction, float _cutOff, float _exponent);
    ~wizSpotLight();

    void applySettings();

    void setDirection(wizVector3* _direction);
    void setCutOff(float _cutOff);
    void setExponent(float _exponent);
    wizVector3* getDirection();
    float getCutOff();
    float getExponent();

    protected:

    wizVector3* direction;
    float cutOff;
    float exponent;
};

#endif // WIZSPOTLIGHT_H

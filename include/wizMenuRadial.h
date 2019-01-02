#ifndef WIZMENURADIAL_H
#define WIZMENURADIAL_H

#include "wizMenu.h"
#include "wizMenuItem.h"
#include "wizRenderer.h"
#include "wizSpriteRenderer.h"
#include "wizVector2.h"

#include <math.h>
#include <vector>

class wizMenuRadial : public wizMenu
{
    public:

    wizMenuRadial(wizRenderer* _renderer);
    virtual ~wizMenuRadial();

    void setPosition(wizVector2 _position);
    void setRadius(float _radiusW, float _radiusH);
    void setSpeed(float _speed);
    void setAcceleration(float _acceleration);
    void setDamping(float _damping);
    wizVector2 getPosition();
    float getRadiusW();
    float getRadiusH();
    float getSpeed();
    float getAcceleration();
    float getDamping();

    void addItem(wizMenuItem* _item);
    void nextItem();
    void previousItem();

    void update(float _dt);
    bool isAnimating();

    protected:

    float radiusW;
    float radiusH;
    float speed;
    float time;
    float endTime;
    float initialAcceleration;
    float damping;
    float acceleration;
    wizVector2 position;
    wizMenuItem* toSelect;
    std::vector<float> angleList;
    std::vector<float> endAngleList;
};

#endif // WIZMENURADIAL_H

#ifndef WIZMENUSLIDE_H
#define WIZMENUSLIDE_H

#include "wizMenu.h"
#include "wizMenuItem.h"
#include "wizRenderer.h"
#include "wizSpriteRenderer.h"
#include "wizVector2.h"

#include <math.h>
#include <vector>

#define MENU_ORIENTATION_HORIZONTAL 0
#define MENU_ORIENTATION_VERTICAL   1

class wizMenuSlide : public wizMenu
{
    public:

    wizMenuSlide(wizRenderer* _renderer);
    virtual ~wizMenuSlide();

    void setOrientation(unsigned int _orientation);
    void setPosition(wizVector2 _position);
    void setSpeed(float _speed);
    void setAcceleration(float _acceleration);
    void setDamping(float _damping);
    wizVector2 getPosition();
    unsigned int getOrientation();
    float getSpeed();
    float getAcceleration();
    float getDamping();

    void addItem(wizMenuItem* _item);
    void nextItem();
    void previousItem();

    void update(float _dt);
    bool isAnimating();

    protected:

    unsigned int orientation;
    float speed;
    float time;
    float endTime;
    float initialAcceleration;
    float damping;
    float acceleration;
    wizVector2 position;
    wizMenuItem* toSelect;
    std::vector<wizVector2> coord;
    std::vector<wizVector2> endCoord;
};

#endif // WIZMENUSLIDE_H

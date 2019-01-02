#include "wizMenuRadial.h"

wizMenuRadial::wizMenuRadial(wizRenderer* _renderer) : wizMenu(_renderer)
{
    damping = 1;
    initialAcceleration = 1;
    radiusW = 0;
    radiusH = 0;
    speed = 1;
    endTime = -1;
    toSelect = NULL;
    position = wizVector2(160, 120);
    renderer = _renderer;
}

wizMenuRadial::~wizMenuRadial()
{
}

void wizMenuRadial::setPosition(wizVector2 _position)
{
    position = _position;
}

void wizMenuRadial::setRadius(float _radiusW, float _radiusH)
{
    radiusW = _radiusW;
    radiusH = _radiusH;
}

void wizMenuRadial::setSpeed(float _speed)
{
    speed = _speed;
}

void wizMenuRadial::setAcceleration(float _acceleration)
{
    initialAcceleration = _acceleration;
}

void wizMenuRadial::setDamping(float _damping)
{
    damping = _damping;
}

wizVector2 wizMenuRadial::getPosition()
{
    return position;
}

float wizMenuRadial::getRadiusW()
{
    return radiusW;
}

float wizMenuRadial::getRadiusH()
{
    return radiusH;
}

float wizMenuRadial::getSpeed()
{
    return speed;
}

float wizMenuRadial::getAcceleration()
{
    return initialAcceleration;
}

float wizMenuRadial::getDamping()
{
    return damping;
}

void wizMenuRadial::addItem(wizMenuItem* _item)
{
    itemList.push_back(_item);
    angleList.push_back(0);
    endAngleList.push_back(0);

    itemList[itemList.size()-1]->setRenderer(renderer);

    float angle = 0;
    float angleInc = 360.0f / itemList.size();

    for (unsigned int i=0; i<itemList.size(); i++)
    {
        itemList[i]->setX(position.getX() + cos(angle*3.1415926f/180.0f)*radiusW - itemList[i]->getWidth()/2);
        itemList[i]->setY(position.getY() + sin(angle*3.1415926f/180.0f)*radiusH - itemList[i]->getHeight()/2);
        angleList[i] = angle;
        angle += angleInc;
    }

    setSelected(itemList[0]);
}

void wizMenuRadial::nextItem()
{
    time = 0;
    acceleration = initialAcceleration;
    endTime = speed;
    toSelect = getNextItem();

    for (unsigned int i=0; i<itemList.size(); i++)
    {
        endAngleList[i] = angleList[i] + 360.0f / itemList.size();
    }

    setSelected(NULL);
}

void wizMenuRadial::previousItem()
{
    time = 0;
    acceleration = initialAcceleration;
    endTime = speed;
    toSelect = getPreviousItem();

    for (unsigned int i=0; i<itemList.size(); i++)
    {
        endAngleList[i] = angleList[i] - 360.0f / itemList.size();
    }

    setSelected(NULL);
}

bool wizMenuRadial::isAnimating()
{
    return endTime >= 0;
}

void wizMenuRadial::update(float _dt)
{
    acceleration *= damping;

    if (acceleration < 1) acceleration = 1;

    if (endTime>0)
    {
        time += speed * acceleration * _dt;

        if (time>=endTime)
        {
            time = endTime;
            endTime = -1;

            for (unsigned int i=0; i<itemList.size(); i++)
            {
                angleList[i] = endAngleList[i];
                itemList[i]->setX(position.getX() + cos(angleList[i]/180.0f*3.1415926f)*radiusW - itemList[i]->getWidth()/2);
                itemList[i]->setY(position.getY() + sin(angleList[i]/180.0f*3.1415926f)*radiusH - itemList[i]->getHeight()/2);
            }

            setSelected(toSelect);
        }
        else
        {
            float ratio = time/endTime;

            for (unsigned int i=0; i<itemList.size(); i++)
            {
                itemList[i]->setX(position.getX() + cos((angleList[i]*(1-ratio)+endAngleList[i]*ratio)/180.0f*3.1415926f)*radiusW - itemList[i]->getWidth()/2);
                itemList[i]->setY(position.getY() + sin((angleList[i]*(1-ratio)+endAngleList[i]*ratio)/180.0f*3.1415926f)*radiusH - itemList[i]->getHeight()/2);
            }
        }
    }
}

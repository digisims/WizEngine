#ifndef WIZSPRITEFRAME_H
#define WIZSPRITEFRAME_H

#include "wizUtility.h"
#include "wizVector2.h"

#include <cstdlib>
#include <string>
#include <fstream>

class wizSpriteFrame
{
    public:

    wizSpriteFrame();
    wizSpriteFrame(std::ifstream& _ssh);
    virtual ~wizSpriteFrame();

    void setPosition(wizVector2 _position);
    void setActualSize(wizVector2 _size);
    void setSize(wizVector2 _size);
    void setTime(float _time);
    wizVector2 getPosition();
    wizVector2 getSize();
    wizVector2 getActualSize();
    float getTime();

    protected:

    wizVector2 position;
    wizVector2 actualSize;
    wizVector2 size;
    float time;
};

#endif // WIZSPRITEFRAME_H

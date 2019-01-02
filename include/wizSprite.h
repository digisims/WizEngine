#ifndef WIZSPRITE_H
#define WIZSPRITE_H

#include "wizUtility.h"
#include "wizSpriteAnimation.h"

#include <map>
#include <string>
#include <fstream>

class wizSprite
{
    public:

    wizSprite();
    wizSprite(std::ifstream& _ssh);
    virtual ~wizSprite();

    void addAnimation(std::string _id, wizSpriteAnimation* _animation);
    void removeAnimation(std::string _id);
    wizSpriteAnimation* getAnimation(std::string _id);

    protected:

    std::map<std::string, wizSpriteAnimation*> animationMap;
};

#endif // WIZSPRITE_H

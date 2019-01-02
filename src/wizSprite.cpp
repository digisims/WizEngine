#include "wizSprite.h"

wizSprite::wizSprite()
{
}

wizSprite::wizSprite(std::ifstream& _ssh)
{
    std::string data;

    do
    {
        _ssh >> data;

        std::vector<std::string> tokens = wizUtility::splitString(data, '=');

        if (tokens.size()>0)
        {
            if (tokens[0].compare("ANIMATION")==0)
            {
                std::string name = tokens[1];

                wizSpriteAnimation* animation = new wizSpriteAnimation(_ssh);

                addAnimation(name, animation);
            }
        }
    }
    while (data.compare("END")!=0);
}

wizSprite::~wizSprite()
{
    std::map<std::string, wizSpriteAnimation*>::iterator i;

    for (i = animationMap.begin(); i != animationMap.end(); i++)
    {
        delete i->second;
    }
}

void wizSprite::addAnimation(std::string _id, wizSpriteAnimation* _animation)
{
    if (getAnimation(_id)==NULL)
    {
        animationMap[_id] = _animation;
    }
}

void wizSprite::removeAnimation(std::string _id)
{
    if (getAnimation(_id)!=NULL)
    {
        animationMap.erase(animationMap.find(_id));
    }
}

wizSpriteAnimation* wizSprite::getAnimation(std::string _id)
{
    if (animationMap.find(_id) != animationMap.end())
    {
        return animationMap[_id];
    }

    return NULL;
}

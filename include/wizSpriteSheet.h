#ifndef WIZSPRITESHEET_H
#define WIZSPRITESHEET_H

#include "wizSprite.h"
#include "wizTextureManager.h"

#include <map>

class wizSpriteSheet
{
    public:

    wizSpriteSheet();
    wizSpriteSheet(std::string _filename);
    ~wizSpriteSheet();

    void setTexture(std::string _texture);
    std::string getTexture();

    void addSprite(std::string _id, wizSprite* _sprite);
    wizSprite* getSprite(std::string _id);
    void removeSprite(std::string _id);

    protected:

    std::map<std::string, wizSprite*> spriteMap;
    std::string texture;
};

#endif // WIZSPRITESHEET_H

#include "wizSpritesheet.h"

wizSpriteSheet::wizSpriteSheet()
{
}

wizSpriteSheet::wizSpriteSheet(std::string _filename)
{
    std::ifstream ssh(_filename.c_str());

    while (!ssh.eof())
    {
        std::string data;

        ssh >> data;

        std::vector<std::string> tokens = wizUtility::splitString(data, '=');

        if (tokens.size()>0)
        {
            if (tokens[0].compare("SPRITE")==0)
            {
                std::string name = tokens[1];

                wizSprite* sprite = new wizSprite(ssh);

                addSprite(name, sprite);
            }
            else if (tokens[0].compare("TEXTURE")==0)
            {
                std::string texture = tokens[1];

                setTexture(texture);
            }
        }
    }

    ssh.close();

    wizTextureManager::loadTexture(texture);
}

wizSpriteSheet::~wizSpriteSheet()
{
    std::map<std::string, wizSprite*>::iterator i;

    for (i=spriteMap.begin(); i!=spriteMap.end(); i++)
    {
        delete i->second;
    }
}

void wizSpriteSheet::setTexture(std::string _texture)
{
    texture = _texture;
}

std::string wizSpriteSheet::getTexture()
{
    return texture;
}

void wizSpriteSheet::addSprite(std::string _id, wizSprite* _sprite)
{
    if (getSprite(_id)==NULL)
    {
        spriteMap[_id] = _sprite;
    }
}

wizSprite* wizSpriteSheet::getSprite(std::string _id)
{
    if (spriteMap.find(_id)!=spriteMap.end())
    {
        return spriteMap[_id];
    }

    return NULL;
}

void wizSpriteSheet::removeSprite(std::string _id)
{
    if (getSprite(_id)!=NULL)
    {
        spriteMap.erase(spriteMap.find(_id));
    }
}

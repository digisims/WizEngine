#include "wizSpritesheetManager.h"

std::map<std::string, wizSpriteSheet*> wizSpriteSheetManager::sheetMap;

void wizSpriteSheetManager::initialize()
{
}

void wizSpriteSheetManager::destroy()
{
    std::map<std::string, wizSpriteSheet*>::iterator i;

    for (i=sheetMap.begin(); i!=sheetMap.end(); i++)
    {
        delete i->second;
    }
}

void wizSpriteSheetManager::addSpriteSheet(std::string _id, wizSpriteSheet* _sheet)
{
    if (getSpriteSheet(_id)==NULL)
    {
        sheetMap[_id] = _sheet;
    }
}

wizSpriteSheet* wizSpriteSheetManager::getSpriteSheet(std::string _id)
{
    if (sheetMap.find(_id)!=sheetMap.end())
    {
        return sheetMap[_id];
    }

    return NULL;
}

void wizSpriteSheetManager::removeSpriteSheet(std::string _id)
{
    if (getSpriteSheet(_id)!=NULL)
    {
        sheetMap.erase(sheetMap.find(_id));
    }
}

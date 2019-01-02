#include "wizFontManager.h"

std::map<std::string, wizFont*> wizFontManager::fontMap;

void wizFontManager::initialize()
{
}

void wizFontManager::destroy()
{
    std::map<std::string, wizFont*>::iterator i;

    for (i=fontMap.begin(); i!=fontMap.end(); i++)
    {
        delete i->second;
    }
}

void wizFontManager::addFont(std::string _id, wizFont* _font)
{
    if (getFont(_id)==NULL)
    {
        fontMap[_id] = _font;
    }
}

wizFont* wizFontManager::getFont(std::string _id)
{
    if (fontMap.find(_id)!=fontMap.end())
    {
        return fontMap[_id];
    }

    return NULL;
}

void wizFontManager::removeFont(std::string _id)
{
    if (getFont(_id)!=NULL)
    {
        fontMap.erase(fontMap.find(_id));
    }
}

#ifndef WIZSPRITESHEETMANAGER_H
#define WIZSPRITESHEETMANAGER_H

#include "wizSpriteSheet.h"

#include <map>

class wizSpriteSheetManager
{
    public:

    static void initialize();
    static void destroy();

    static void addSpriteSheet(std::string _id, wizSpriteSheet* _sheet);
    static wizSpriteSheet* getSpriteSheet(std::string _id);
    static void removeSpriteSheet(std::string _id);

    protected:

    static std::map<std::string, wizSpriteSheet*> sheetMap;
};

#endif // WIZSPRITESHEETMANAGER_H

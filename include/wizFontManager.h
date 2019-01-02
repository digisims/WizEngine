#ifndef WIZFONTMANAGER_H
#define WIZFONTMANAGER_H

#include "wizFont.h"

#include <string>
#include <map>

class wizFontManager
{
    public:

    static void initialize();
    static void destroy();

    static void addFont(std::string _id, wizFont* _font);
    static wizFont* getFont(std::string _id);
    static void removeFont(std::string _id);

    protected:

    static std::map<std::string, wizFont*> fontMap;
};

#endif // WIZFONTMANAGER_H

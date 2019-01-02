#ifndef WIZGESTUREOBJECT_H
#define WIZGESTUREOBJECT_H

#include "wizUtility.h"

#include <string>

class wizGestureObject
{
    public:

    wizGestureObject(std::string _pattern);

    void setPattern(std::string _pattern);
    std::string getPattern();
    int calculateScore(std::string _pattern);

    protected:

    std::string pattern;
};

#endif // WIZGESTUREOBJECT_H

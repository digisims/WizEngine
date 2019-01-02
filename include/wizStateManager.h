#ifndef WIZSTATEMANAGER_H
#define WIZSTATEMANAGER_H

#include "wizStateGroup.h"

#include <map>
#include <string>

class wizStateManager
{
    public:

    void initialize();
    void destroy();

    static void addStateGroup(std::string _id, wizStateGroup* _group);
    static wizStateGroup* getStateGroup(std::string _id);
    static void removeStateGroup(std::string _id);
    static void activateStateGroup(std::string _id);

    static void update(float _dt);

    protected:

    static std::string active;
    static std::map<std::string, wizStateGroup*> groupMap;
};

#endif // WIZSTATEMANAGER_H

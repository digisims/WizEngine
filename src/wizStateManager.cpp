#include "wizStateManager.h"

std::map<std::string, wizStateGroup*> wizStateManager::groupMap;
std::string wizStateManager::active;

void wizStateManager::initialize()
{
    active = "";
}

void wizStateManager::destroy()
{
    std::map<std::string, wizStateGroup*>::iterator i;

    for (i=groupMap.begin(); i!=groupMap.end(); i++)
    {
        delete i->second;
    }
}

void wizStateManager::activateStateGroup(std::string _id)
{
    if (groupMap.find(active)!=groupMap.end())
    {
        groupMap[active]->stopAll();
    }
    active = _id;
    groupMap[active]->startAll();
}

void wizStateManager::addStateGroup(std::string _id, wizStateGroup* _group)
{
    _group->loadAll();
    groupMap[_id] = _group;
    activateStateGroup(_id);
}

wizStateGroup* wizStateManager::getStateGroup(std::string _id)
{
    return groupMap[_id];
}

void wizStateManager::removeStateGroup(std::string _id)
{
    if (groupMap.find(_id)!=groupMap.end())
    {
        groupMap.erase(_id);
    }
}

void wizStateManager::update(float _dt)
{
    if (groupMap.find(active)!=groupMap.end())
    {
        groupMap[active]->update(_dt);
    }
}

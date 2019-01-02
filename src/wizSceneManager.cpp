#include "wizSceneManager.h"

wizSceneManager::wizSceneManager()
{
}

wizSceneManager::~wizSceneManager()
{
}

void wizSceneManager::addEntity(wizGameEntity* _entity)
{
    objectList.push_back(_entity);
}

void wizSceneManager::removeEntity(unsigned int _idx)
{
    objectList.erase(objectList.begin()+_idx);
}

void wizSceneManager::clear()
{
    objectList.clear();
}

std::vector<wizGameEntity*> wizSceneManager::mergeLists(std::vector<wizGameEntity*> _l1, std::vector<wizGameEntity*> _l2)
{
    std::vector<wizGameEntity*> list;

    for (unsigned int i=0; i<_l1.size(); i++)
    {
        list.push_back(_l1[i]);
    }

    for (unsigned int i=0; i<_l2.size(); i++)
    {
        #ifndef WIN32
        if (std::find(list.begin(), list.end(), _l2[i])==list.end())
        #endif
        {
            list.push_back(_l2[i]);
        }
    }

    return list;
}

std::vector<wizGameEntity*> wizSceneManager::queryAll()
{
    return objectList;
}

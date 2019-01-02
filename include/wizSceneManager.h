#ifndef WIZSCENEMANAGER_H
#define WIZSCENEMANAGER_H

#include "wizGameEntity.h"
#include "wizCamera.h"

#include <vector>

class wizSceneManager
{
    public:

    wizSceneManager();
    virtual ~wizSceneManager();

    void addEntity(wizGameEntity* _entity);
    void removeEntity(unsigned int _idx);
    void clear();

    std::vector<wizGameEntity*> mergeLists(std::vector<wizGameEntity*> _l1, std::vector<wizGameEntity*> _l2);

    virtual void construct() = 0;
    virtual std::vector<wizGameEntity*> queryAll();
    virtual std::vector<wizGameEntity*> queryVisible(wizCamera* _camera) = 0;
    virtual std::vector<wizGameEntity*> queryVisibleStatic(wizCamera* _camera) = 0;
    virtual std::vector<wizGameEntity*> queryVisibleDynamic(wizCamera* _camera) = 0;

    protected:

    std::vector<wizGameEntity*> objectList;
};

#endif // WIZSCENEMANAGER_H

#ifndef WIZSCENEMANAGERLAYERED_H
#define WIZSCENEMANAGERLAYERED_H

#include "wizSceneManager.h"
#include "wizGameEntity.h"
#include "wizSpriteEntity.h"

#include <vector>

class wizSceneManagerLayered : wizSceneManager
{
    public:

    wizSceneManagerLayered();
    virtual ~wizSceneManagerLayered();

    void addEntity(wizGameEntity* _entity);
    void removeEntity(unsigned int _idx);
    void clear();

    void addEntity(unsigned int _layer, wizGameEntity* _entity);
    void removeEntity(unsigned int _layer, unsigned int _idx);
    void clear(unsigned int _layer);

    void construct();
    std::vector<wizGameEntity*> queryAll();
    std::vector<wizGameEntity*> queryVisible(wizCamera* _camera);
    std::vector<wizGameEntity*> queryVisibleStatic(wizCamera* _camera);
    std::vector<wizGameEntity*> queryVisibleDynamic(wizCamera* _camera);

    protected:

    std::vector<std::vector<wizGameEntity*> > layerList;
};

#endif // WIZSCENEMANAGERLAYERED_H

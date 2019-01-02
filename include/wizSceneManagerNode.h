#ifndef WIZSCENEMANAGERNODE_H
#define WIZSCENEMANAGERNODE_H

#include "wizSceneManager.h"
#include "wizBoundingBox.h"
#include "wizCamera3D.h"
#include "wizGameEntity.h"
#include "wizMeshEntity.h"

#include <vector>

class wizSceneManagerNode : public wizSceneManager
{
    public:

    wizSceneManagerNode();
    virtual ~wizSceneManagerNode();

    void clear();
    void construct();

    std::vector<wizGameEntity*> queryVisible(wizCamera* _camera);
    std::vector<wizGameEntity*> queryVisibleStatic(wizCamera* _camera);
    std::vector<wizGameEntity*> queryVisibleDynamic(wizCamera* _camera);
    std::vector<wizGameEntity*> queryVisible(wizBoundingBox _bbox);
    std::vector<wizGameEntity*> queryVisibleStatic(wizBoundingBox _bbox);
    std::vector<wizGameEntity*> queryVisibleDynamic(wizBoundingBox _bbox);

    void setParent(wizSceneManagerNode* _parent);
    wizSceneManagerNode* getParent();
    void addChild(wizSceneManagerNode* _child);

    void setBoundingBox(wizBoundingBox _bbox);
    wizBoundingBox getBoundingBox();

    protected:

    wizSceneManagerNode* parent;
    std::vector<wizSceneManagerNode*> children;
    wizBoundingBox bbox;
};

#endif // WIZSCENEMANAGERNODE_H

#ifndef WIZSCENEMANAGERBVH_H
#define WIZSCENEMANAGERBVH_H

#include "wizSceneManager.h"
#include "wizSceneManagerNode.h"

class wizSceneManagerBVH : public wizSceneManager
{
    public:

    wizSceneManagerBVH();
    virtual ~wizSceneManagerBVH();

    std::vector<wizGameEntity*> queryVisible(wizCamera* _camera);
    std::vector<wizGameEntity*> queryVisibleStatic(wizCamera* _camera);
    std::vector<wizGameEntity*> queryVisibleDynamic(wizCamera* _camera);

    virtual void construct() = 0;
    virtual void construct(int _minimumObjectsPerNode, int _maximumDepth) = 0;

    wizSceneManagerNode* getRoot();

    protected:

    wizSceneManagerNode* root;
};

#endif // WIZSCENEMANAGERBVH_H

#include "wizSceneManagerBVH.h"

wizSceneManagerBVH::wizSceneManagerBVH()
{
}

wizSceneManagerBVH::~wizSceneManagerBVH()
{
    if (root!=NULL) delete root;
}

wizSceneManagerNode* wizSceneManagerBVH::getRoot()
{
    return root;
}

std::vector<wizGameEntity*> wizSceneManagerBVH::queryVisible(wizCamera* _camera)
{
    return root->queryVisible(_camera);
}

std::vector<wizGameEntity*> wizSceneManagerBVH::queryVisibleStatic(wizCamera* _camera)
{
    return root->queryVisibleStatic(_camera);
}

std::vector<wizGameEntity*> wizSceneManagerBVH::queryVisibleDynamic(wizCamera* _camera)
{
    return root->queryVisibleDynamic(_camera);
}

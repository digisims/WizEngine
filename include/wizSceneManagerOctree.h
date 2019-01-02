#ifndef WIZSCENEMANAGEROCTREE_H
#define WIZSCENEMANAGEROCTREE_H

#include "wizSceneManagerBVH.h"
#include "wizSceneManagerNode.h"
#include "wizBoundingBox.h"
#include "wizVector3.h"

class wizSceneManagerOctree : public wizSceneManagerBVH
{
    public:

    wizSceneManagerOctree();
    virtual ~wizSceneManagerOctree();

    void construct();
    void construct(int _minimumObjectsPerNode, int _maximumDepth);

    protected:

    void constructNode(std::vector<wizGameEntity*> _objectList, wizVector3 _minimum, wizVector3 _maximum, wizSceneManagerNode* _node, unsigned int _minimumObjects, unsigned int _maximumDepth, unsigned _depth);
};

#endif // WIZSCENEMANAGEROCTREE_H

#include "wizSceneManagerOctree.h"
#include <fstream>

wizSceneManagerOctree::wizSceneManagerOctree()
{
    root = new wizSceneManagerNode();
}

wizSceneManagerOctree::~wizSceneManagerOctree()
{
    if (root!=NULL) delete root;
}

void wizSceneManagerOctree::construct()
{
    construct(8, 4);
}

void wizSceneManagerOctree::construct(int _minimumObjectsPerNode, int _maximumDepth)
{
    wizBoundingBox bbox(wizVector3(1000000, 1000000, 1000000), wizVector3(-1000000, -1000000, -1000000));

    for (unsigned int i=0; i<objectList.size(); i++)
    {
        wizMeshEntity* entity = (wizMeshEntity*)objectList[i];
        bbox.merge(entity->getBoundingBox());
    }

    root = new wizSceneManagerNode();
    constructNode(objectList, bbox.getMinimum(), bbox.getMaximum(), root, _minimumObjectsPerNode, _maximumDepth, 0);
}

void wizSceneManagerOctree::constructNode(std::vector<wizGameEntity*> _objectList, wizVector3 _minimum, wizVector3 _maximum, wizSceneManagerNode* _node, unsigned int _minimumObjects, unsigned int _maximumDepth, unsigned int _depth)
{
    _node->setBoundingBox(wizBoundingBox(_minimum, _maximum));

    for (unsigned int i = 0; i < _objectList.size(); i++)
    {
        wizMeshEntity* entity = (wizMeshEntity*)_objectList[i];

        if (wizBoundingBox::doesIntersectAABB(_node->getBoundingBox(), entity->getBoundingBox()))
        {
            _node->addEntity(entity);
        }
    }

    if (_node->getParent() != NULL && _node->queryAll().size() == _node->getParent()->queryAll().size())
    {
        _node->clear();
        _node = NULL;
        return;
    }

    if (_node->queryAll().size() > _minimumObjects && _depth < _maximumDepth)
    {
        wizVector3 dim = _maximum.sub(_minimum).mul(0.5f);
        float sx = _minimum.getX();
        float sy = _minimum.getY();
        float sz = _minimum.getZ();

        for (int i = 0; i < 2; i++)
        {
            sy = _minimum.getY();

            for (int j = 0; j < 2; j++)
            {
                sz = _minimum.getZ();

                for (int k = 0; k < 2; k++)
                {
                    wizVector3 bmin(sx, sy, sz);
                    wizVector3 bmax(sx + dim.getX(), sy + dim.getY(), sz + dim.getZ());

                    wizSceneManagerNode* c = new wizSceneManagerNode();
                    c->setParent(_node);

                    constructNode(_objectList, bmin, bmax, c, _minimumObjects, _maximumDepth, _depth+1);

                    if (c->queryAll().size() == 0) c = NULL;

                    if (c != NULL)
                    {
                        _node->addChild(c);
                    }

                    sz += dim.getZ();
                }

                sy += dim.getY();
            }

            sx += dim.getX();
        }
    }
}

#include "wizSceneManagerKDTree.h"

wizSceneManagerKDTree::wizSceneManagerKDTree()
{
    root = new wizSceneManagerNode();
}

wizSceneManagerKDTree::~wizSceneManagerKDTree()
{
    if (root!=NULL) delete root;
}

void wizSceneManagerKDTree::construct()
{
    construct(8, 4);
}

void wizSceneManagerKDTree::construct(int _minimumObjectsPerNode, int _maximumDepth)
{
    std::vector<wizGameEntity*> staticObjects;
    wizBoundingBox bbox(new wizVector3(1000000, 1000000, 1000000), new wizVector3(-1000000, -1000000, -1000000));

    for (unsigned int i=0; i<objectList.size(); i++)
    {
        wizMeshEntity* entity = (wizMeshEntity*)objectList[i];

        if (entity->getStatic())
        {
            staticObjects.push_back(entity);
            bbox.merge(entity->getBoundingBox());
        }
    }

    root = new wizSceneManagerNode();
    constructNode(staticObjects, *(bbox.getMinimum()), *(bbox.getMaximum()), root, _minimumObjectsPerNode, _maximumDepth, 0);
}

void wizSceneManagerKDTree::constructNode(std::vector<wizGameEntity*> _objectList, wizVector3 _minimum, wizVector3 _maximum, wizSceneManagerNode* _node, unsigned int _minimumObjects, unsigned int _maximumDepth, unsigned _depth)
{
    _node->setBoundingBox(new wizBoundingBox(_minimum, _maximum));

    for (unsigned int i = 0; i < _objectList.size(); i++)
    {
        wizMeshEntity* entity = (wizMeshEntity*)_objectList[i];

        if (_node->getBoundingBox()->doesIntersectBox(entity->getBoundingBox()))
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
        wizVector3 dim = _maximum.sub(_minimum);
        unsigned int axis = 0;

        if (dim.getY()>dim.getX() && dim.getY()>dim.getZ())
            axis = 1;
        else if (dim.getZ()>dim.getX() && dim.getZ()>dim.getY())
            axis = 2;

        wizBoundingBox** b = _node->getBoundingBox()->split(axis);

        wizSceneManagerNode* c1 = new wizSceneManagerNode();
        wizSceneManagerNode* c2 = new wizSceneManagerNode();

        c1->setParent(_node);
        c2->setParent(_node);

        constructNode(_objectList, *b[0]->getMinimum(), *b[0]->getMaximum(), c1, _minimumObjects, _maximumDepth, _depth+1);
        constructNode(_objectList, *b[1]->getMinimum(), *b[1]->getMaximum(), c2, _minimumObjects, _maximumDepth, _depth+1);

        if (c1->queryAll().size() == 0) c1 = NULL;
        if (c2->queryAll().size() == 0) c2 = NULL;

        if (c1!=NULL) _node->addChild(c1);
        if (c2!=NULL) _node->addChild(c2);
    }
}

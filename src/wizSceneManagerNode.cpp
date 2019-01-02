#include "wizSceneManagerNode.h"

wizSceneManagerNode::wizSceneManagerNode()
{
    parent = NULL;
}

wizSceneManagerNode::~wizSceneManagerNode()
{
}

void wizSceneManagerNode::construct()
{

}

void wizSceneManagerNode::clear()
{
    objectList.clear();
}

void wizSceneManagerNode::setParent(wizSceneManagerNode* _parent)
{
    parent = _parent;
}

wizSceneManagerNode* wizSceneManagerNode::getParent()
{
    return parent;
}

void wizSceneManagerNode::addChild(wizSceneManagerNode* _child)
{
    children.push_back(_child);
}

void wizSceneManagerNode::setBoundingBox(wizBoundingBox _bbox)
{
    bbox = _bbox;
}

wizBoundingBox wizSceneManagerNode::getBoundingBox()
{
    return bbox;
}

std::vector<wizGameEntity*> wizSceneManagerNode::queryVisible(wizCamera* _camera)
{
    wizCamera3D* camera3D = (wizCamera3D*)_camera;
    unsigned int result = camera3D->getFrustum()->isBoxInside(bbox);

    if (result == wizFrustum::DEF_INSIDE)
    {
        return queryAll();
    }
    else if (result == wizFrustum::DEF_OUTSIDE)
    {
        std::vector<wizGameEntity*> visible;
        return visible;
    }
    else
    {
        std::vector<wizGameEntity*> visible;
        int valid = 0;

        for (unsigned int i=0; i<children.size(); i++)
        {
            if (children[i] != NULL)
            {
                visible = mergeLists(visible, children[i]->queryVisible(_camera));
                valid++;
            }
        }

        if (children.size()==0 || valid == 0)
        {
            visible = mergeLists(visible, queryAll());
        }

        return visible;
    }
}

std::vector<wizGameEntity*> wizSceneManagerNode::queryVisibleStatic(wizCamera* _camera)
{
    wizCamera3D* camera3D = (wizCamera3D*)_camera;
    unsigned int result = camera3D->getFrustum()->isBoxInside(bbox);

    if (result == wizFrustum::DEF_INSIDE)
    {
        std::vector<wizGameEntity*> visible;

        for (unsigned int i=0; i<objectList.size(); i++)
        {
            wizMeshEntity* entity = (wizMeshEntity*)objectList[i];

            if (entity->getStatic())
            {
                visible.push_back(entity);
            }
        }

        return visible;
    }
    else if (result == wizFrustum::DEF_OUTSIDE)
    {
        std::vector<wizGameEntity*> visible;
        return visible;
    }
    else
    {
        std::vector<wizGameEntity*> visible;
        int valid = 0;

        for (unsigned int i=0; i<children.size(); i++)
        {
            if (children[i]!=NULL)
            {
                visible = mergeLists(visible, children[i]->queryVisibleStatic(_camera));
                valid++;
            }
        }

        if (children.size()==0 || valid == 0)
        {
            for (unsigned int i=0; i<objectList.size(); i++)
            {
                wizMeshEntity* entity = (wizMeshEntity*)objectList[i];

                #ifndef WIN32
                if (entity->getStatic() && std::find(visible.begin(), visible.end(), entity)!=visible.end())
                #endif
                {
                    visible.push_back(entity);
                }
            }
        }

        return visible;
    }
}

std::vector<wizGameEntity*> wizSceneManagerNode::queryVisibleDynamic(wizCamera* _camera)
{
    wizCamera3D* camera3D = (wizCamera3D*)_camera;
    unsigned int result = camera3D->getFrustum()->isBoxInside(bbox);

    if (result == wizFrustum::DEF_INSIDE)
    {
        std::vector<wizGameEntity*> visible;

        for (unsigned int i=0; i<objectList.size(); i++)
        {
            wizMeshEntity* entity = (wizMeshEntity*)objectList[i];

            if (!entity->getStatic())
            {
                visible.push_back(entity);
            }
        }

        return visible;
    }
    else if (result == wizFrustum::DEF_OUTSIDE)
    {
        std::vector<wizGameEntity*> visible;
        return visible;
    }
    else
    {
        std::vector<wizGameEntity*> visible;
        int valid = 0;

        for (unsigned int i=0; i<children.size(); i++)
        {
            if (children[i]!=NULL)
            {
                visible = mergeLists(visible, children[i]->queryVisibleDynamic(_camera));
                valid++;
            }
        }

        if (children.size()==0 || valid==0)
        {
            for (unsigned int i=0; i<objectList.size(); i++)
            {
                wizMeshEntity* entity = (wizMeshEntity*)objectList[i];

                #ifndef WIN32
                if (!entity->getStatic() && std::find(visible.begin(), visible.end(), entity)!=visible.end())
                #endif
                {
                    visible.push_back(entity);
                }
            }
        }

        return visible;
    }
}

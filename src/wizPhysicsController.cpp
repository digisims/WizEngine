#include "wizPhysicsController.h"
#include "wizGame.h"

wizPhysicsController::wizPhysicsController()
{
    gravity = wizVector3(0, -9.8f, 0);
    reportDynamicStaticCollision = NULL;
    reportDynamicDynamicCollision = NULL;
    iterations = 10;
    scale = 0.01f;
}

wizPhysicsController::~wizPhysicsController()
{
}

void wizPhysicsController::setGravity(wizVector3 _gravity)
{
    gravity = _gravity;
}

void wizPhysicsController::setScale(float _scale)
{
    scale = _scale;
}

void wizPhysicsController::setIterations(unsigned int _iterations)
{
    iterations = _iterations;
}

void wizPhysicsController::setEarlyOut(bool _earlyOut)
{
    earlyOut = _earlyOut;
}

wizVector3 wizPhysicsController::getGravity()
{
    return gravity;
}

float wizPhysicsController::getScale()
{
    return scale;
}

unsigned int wizPhysicsController::getIterations()
{
    return iterations;
}

bool wizPhysicsController::getEarlyOut()
{
    return earlyOut;
}

std::vector<wizGameEntity*> wizPhysicsController::sort(std::vector<wizGameEntity*>& colliders)
{
    std::vector<wizGameEntity*> list;

    for (unsigned int i=0; i<colliders.size(); i++)
    {
        if (!colliders[i]->getStatic())
        {
            list.push_back(colliders[i]);
        }
    }

    for (unsigned int i=0; i<colliders.size(); i++)
    {
        if (colliders[i]->getStatic())
        {
            list.push_back(colliders[i]);
        }
    }

    return list;
}

void wizPhysicsController::update(std::vector<wizGameEntity*>& colliders, float _dt)
{
    std::vector<wizMeshEntity*> pair;
    std::vector<wizIntersectionPoint> points;
    std::vector<bool> type;

    unsigned int minIterations = wizUtility::max(2, iterations);

    for (unsigned int i=0; i<colliders.size(); i++)
    {
        wizMeshEntity* src = (wizMeshEntity*)colliders[i];

        if (!src->getStatic())
        {
            src->getPhysicsBody()->applyForce(gravity.mul(src->getPhysicsBody()->getMass()));

            for (unsigned int j=0; j<minIterations; j++)
            {
                src->getPhysicsBody()->update(_dt);

                unsigned int joints = src->getPhysicsJoints().size();

                for (unsigned int k=0; k<joints; k++)
                {
                    src->getPhysicsJoints()[k]->update(_dt);
                }

                src->update();

                pair.clear();
                points.clear();
                type.clear();

                bool collided = false;

                for (unsigned int k=0; k<colliders.size(); k++)
                {
                    if (i!=k)
                    {
                        wizMeshEntity* dst = (wizMeshEntity*)colliders[k];

                        if (wizBoundingBox::doesIntersectAABB(src->getBoundingBox(), dst->getBoundingBox()))
                        {
                            if (dst->getStatic())
                            {
                                wizIntersectionPoint ip = src->getIntersectMesh(dst);

                                wizMaterial* material = wizMaterialManager::getMaterial(dst->getMaterial());

                                if (material->getCullSide()==GL_FRONT)
                                {
                                    ip.setNormal(ip.getNormal().mul(-1));
                                }

                                if (ip.getType()!=wizIntersectionPoint::POINT_MISS && ip.getNormal().dot(src->getPhysicsBody()->getLinearVelocity().normalize()) <= 0)
                                {
                                    collided = true;

                                    pair.push_back(dst);
                                    points.push_back(ip);
                                    type.push_back(false);
                                }
                            }
                            else
                            {
                                wizIntersectionPoint ip;

                                if (src->getPhysicsBody()->getShape() == PHYSICS_SHAPE_SPHERE && dst->getPhysicsBody()->getShape() == PHYSICS_SHAPE_SPHERE)
                                {
                                    ip = wizBoundingBox::getSphereIntersectSphere(src->getBoundingBox(), dst->getBoundingBox());
                                }
                                else if (src->getPhysicsBody()->getShape() == PHYSICS_SHAPE_SPHERE)
                                {
                                    if (dst->getPhysicsBody()->getShape() == PHYSICS_SHAPE_AABB)
                                    {
                                        ip = wizBoundingBox::getSphereIntersectAABB(src->getBoundingBox(), dst->getBoundingBox());
                                    }
                                    else if (dst->getPhysicsBody()->getShape() == PHYSICS_SHAPE_OBB)
                                    {
                                        ip = wizBoundingBox::getSphereIntersectOBB(src->getBoundingBox(), dst->getBoundingBox(), dst->getTransformation());
                                    }
                                }
                                else if (dst->getPhysicsBody()->getShape() == PHYSICS_SHAPE_SPHERE)
                                {
                                    if (src->getPhysicsBody()->getShape() == PHYSICS_SHAPE_AABB)
                                    {
                                        ip = wizBoundingBox::getSphereIntersectAABB(dst->getBoundingBox(), src->getBoundingBox());
                                    }
                                    else if (src->getPhysicsBody()->getShape() == PHYSICS_SHAPE_OBB)
                                    {
                                        ip = wizBoundingBox::getSphereIntersectOBB(dst->getBoundingBox(), src->getBoundingBox(), src->getTransformation());
                                    }
                                }
                                else
                                {
                                    // treat AABB and OBB the same

                                    ip = src->getIntersectOBB(dst);
                                }

                                if (ip.getType()!=wizIntersectionPoint::POINT_MISS && ip.getNormal().dot(src->getPhysicsBody()->getLinearVelocity().normalize()) <= 0)
                                {
                                    collided = true;

                                    pair.push_back(dst);
                                    points.push_back(ip);
                                    type.push_back(true);
                                }
                            }
                        }
                    }

                    // early out?

                    if (earlyOut && collided && pair[pair.size()-1]->getPhysicsBody()->getTangible()) break;
                }

                if (!collided)
                {
                    break;
                }

                // find closest intersection

                std::vector<int> order;

                for (unsigned int k=0; k<pair.size(); k++)
                {
                    order.push_back(k);
                }

                for (unsigned int k=0; k<pair.size(); k++)
                {
                    for (unsigned int l=k+1; l<pair.size(); l++)
                    {
                        if (points[order[l]].getDistance() < points[order[k]].getDistance())
                        {
                            int tmp = order[l];
                            order[l] = order[k];
                            order[k] = tmp;
                        }
                    }
                }

                for (unsigned int k=0; k<pair.size(); k++)
                {
                    if (pair[order[k]]->getPhysicsBody()->getTangible())
                    {
                        src->getPhysicsBody()->rewind();
                        collisionResponse(src->getPhysicsBody(), src->getBoundingBox(), pair[order[k]]->getPhysicsBody(), pair[order[k]]->getBoundingBox(), points[order[k]], scale);
                    }

                    if (type[order[k]])
                    {
                        if (reportDynamicDynamicCollision != NULL)
                        {
                            reportDynamicDynamicCollision(src, pair[order[k]], points[order[k]]);
                        }
                    }
                    else
                    {
                        if (reportDynamicStaticCollision != NULL)
                        {
                            reportDynamicStaticCollision(src, pair[order[k]], points[order[k]]);
                        }
                    }
                }

                if (collided)
                {
                    src->update();
                }
            }
        }
    }
}

void wizPhysicsController::registerStaticReport(void (*fp)(wizGameEntity*, wizGameEntity*, wizIntersectionPoint))
{
    reportDynamicStaticCollision = fp;
}

void wizPhysicsController::registerDynamicReport(void (*fp)(wizGameEntity*, wizGameEntity*, wizIntersectionPoint))
{
    reportDynamicDynamicCollision = fp;
}

void wizPhysicsController::registerCollisionHandler(std::string _src, std::string _dst, void (*fp)(wizPhysicsBody*, wizBoundingBox, wizPhysicsBody*, wizBoundingBox, wizIntersectionPoint, float))
{
    handlers[_src][_dst] = fp;
}

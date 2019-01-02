#ifndef WIZPHYSICSCONTROLLER_H
#define WIZPHYSICSCONTROLLER_H

#include "wizVector3.h"
#include "wizMeshEntity.h"
#include "wizMaterial.h"
#include "wizMaterialManager.h"

#include <vector>
#include <string>
#include <map>

class wizPhysicsController
{
    public:

    wizPhysicsController();
    ~wizPhysicsController();

    void setGravity(wizVector3 _gravity);
    void setScale(float _scale);
    void setIterations(unsigned int _iterations);
    void setEarlyOut(bool _earlyOut);
    wizVector3 getGravity();
    float getScale();
    unsigned int getIterations();
    bool getEarlyOut();

    std::vector<wizGameEntity*> sort(std::vector<wizGameEntity*>& colliders);
    void update(std::vector<wizGameEntity*>& colliders, float _dt);
    void registerStaticReport(void (*fp)(wizGameEntity*, wizGameEntity*, wizIntersectionPoint));
    void registerDynamicReport(void (*fp)(wizGameEntity*, wizGameEntity*, wizIntersectionPoint));
    void registerCollisionHandler(std::string _src, std::string _dst, void (*fp)(wizPhysicsBody*, wizBoundingBox, wizPhysicsBody*, wizBoundingBox, wizIntersectionPoint, float _scale));

    protected:

    wizVector3 gravity;
    float scale;
    unsigned int iterations;
    bool earlyOut;

    void (*reportDynamicStaticCollision)(wizGameEntity*, wizGameEntity*, wizIntersectionPoint);
    void (*reportDynamicDynamicCollision)(wizGameEntity*, wizGameEntity*, wizIntersectionPoint);
    std::map<std::string, std::map<std::string, void (*)(wizPhysicsBody*, wizBoundingBox, wizPhysicsBody*, wizBoundingBox, wizIntersectionPoint, float)> > handlers;
};

#endif // WIZPHYSICSCONTROLLER_H

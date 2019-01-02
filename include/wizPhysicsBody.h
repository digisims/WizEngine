#ifndef WIZPHYSICSBODY_H
#define WIZPHYSICSBODY_H

#include "wizVector3.h"
#include "wizBoundingBox.h"
#include "wizMatrix.h"
#include "wizUtility.h"

#include <string>

#define PHYSICS_SHAPE_AABB   0
#define PHYSICS_SHAPE_OBB    1
#define PHYSICS_SHAPE_SPHERE 2

class wizPhysicsBody
{
    public:

    wizPhysicsBody(std::string _type, wizBoundingBox* _box, wizVector3* _translation, wizVector3* _rotation, float _mass, float _elasticity, float _friction, bool _tangible);
    virtual ~wizPhysicsBody();

    void update(float _dt);
    void applyForce(wizVector3 _force);
    void applyImpulse(wizVector3 _force);
    void applyImpulse(wizVector3 _force, wizVector3 _point);
    void rewind();
    void stop();

    std::string getType();
    float getMass();
    float getFriction();
    float getElasticity();
    wizVector3 getLinearVelocity();
    wizVector3 getAngularVelocity();
    float* getInverseInertiaTensor();
    float getLinearDamping();
    float getAngularDamping();
    float getAngularScale();
    bool getTangible();
    bool getPlatformControls();
    unsigned int getShape();
    wizVector3* getTranslation();
    wizVector3* getRotation();
    bool isXFree();
    bool isYFree();
    bool isZFree();
    bool canRotate();
    void setTangible(bool _tangible);
    void setLinearVelocity(wizVector3 _linear);
    void setAngularVelocity(wizVector3 _angular);
    void setTranslation(wizVector3 _translation);
    void setRotation(wizVector3 _rotation);
    void setPlatformControls(bool _platformer);
    void setShape(unsigned int _shape);
    void setLinearDamping(float _damping);
    void setAngularDamping(float _damping);
    void setAngularScale(float _scale);
    void setAxis(bool _x, bool _y, bool _z);
    void orient(wizVector3 _n);

    static wizVector3 unitRays[6];

    protected:

    wizVector3 freeAxis;
    wizVector3 oldLinearVelocity;
    wizVector3 oldAngularVelocity;
    wizVector3 oldTranslation;
    wizVector3 oldRotation;
    wizVector3 acceleration;
    wizVector3* translation;
    wizVector3* rotation;
    wizVector3 angularVelocity;
    wizVector3 linearVelocity;
    wizBoundingBox* box;
    float* invInertiaTensor;
    float linearDamping;
    float angularDamping;
    float angularScale;
    float elasticity;
    float mass;
    float friction;
    bool tangible;
    bool platformer;
    std::string type;
    unsigned int shape;
};

void collisionResponse(wizPhysicsBody* _b1, wizBoundingBox _bb1, wizPhysicsBody* _b2, wizBoundingBox _bb2, wizIntersectionPoint _point, float _scale);

#endif // WIZPHYSICSBODY_H

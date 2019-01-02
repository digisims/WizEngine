#ifndef WIZPARTICLE3D_H
#define WIZPARTICLE3D_H

#include "wizVector3.h"
#include "wizParticle.h"
#include "wizCamera3D.h"
#include "wizUtility.h"

class wizParticle3D : public wizParticle
{
    public:

    wizParticle3D();
    ~wizParticle3D();

    void setPosition(wizVector3* _position);
    void setVelocity(wizVector3* _velocity);
    void setMinSize(float _minSize);
    void setMaxSize(float _maxSize);
    void setMaxDistance(float _maxDistance);
    void setCamera(wizCamera3D* _camera);
    wizVector3* getPosition();
    wizVector3* getVelocity();
    GLubyte* getColourBuffer();
    float getMinSize();
    float getMaxSize();
    float getMaxDistance();
    float getSize();
    wizCamera3D* getCamera();

    void update(float _dt);

    protected:

    float size;
    float minSize;
    float maxSize;
    float maxDistance;
    wizVector3* position;
    wizVector3* velocity;
    GLubyte* colourBuffer;
    wizCamera3D* camera;
};

#endif // WIZPARTICLE3D_H

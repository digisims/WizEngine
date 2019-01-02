#include "wizParticle3D.h"

wizParticle3D::wizParticle3D()
{
    position = NULL;
    velocity = NULL;
    colourBuffer = NULL;
    camera = NULL;
}

wizParticle3D::~wizParticle3D()
{
    if (position!=NULL) delete position;
    if (velocity!=NULL) delete velocity;
}

void wizParticle3D::setVelocity(wizVector3* _velocity)
{
    velocity = _velocity;
}

void wizParticle3D::setPosition(wizVector3* _position)
{
    position = _position;
}

void wizParticle3D::setMinSize(float _minSize)
{
    minSize = _minSize;
}

void wizParticle3D::setMaxSize(float _maxSize)
{
    maxSize = _maxSize;
}

void wizParticle3D::setMaxDistance(float _maxDistance)
{
    maxDistance = _maxDistance;
}

void wizParticle3D::setCamera(wizCamera3D* _camera)
{
    camera = _camera;
}

wizVector3* wizParticle3D::getVelocity()
{
    return velocity;
}

wizVector3* wizParticle3D::getPosition()
{
    return position;
}

GLubyte* wizParticle3D::getColourBuffer()
{
    return colourBuffer;
}

float wizParticle3D::getMinSize()
{
    return minSize;
}

float wizParticle3D::getMaxSize()
{
    return maxSize;
}

float wizParticle3D::getMaxDistance()
{
    return maxDistance;
}

float wizParticle3D::getSize()
{
    return size;
}

wizCamera3D* wizParticle3D::getCamera()
{
    return camera;
}

void wizParticle3D::update(float _dt)
{
    if (colourBuffer==NULL)
    {
        colourBuffer = new GLubyte[4 * 1];

        for (unsigned int i=0; i<4*1; i++)
        {
            colourBuffer[i] = 255;
        }
    }

    life -= decayRate * _dt;

    for (unsigned int i=0; i<4*1; i++)
    {
        colourBuffer[i] = (GLubyte)(life*255);
    }

    position->setX(position->getX() + velocity->getX() * _dt);
    position->setY(position->getY() + velocity->getY() * _dt);
    position->setZ(position->getZ() + velocity->getZ() * _dt);

    float dx = camera->getPosition().getX() - position->getX();
    float dy = camera->getPosition().getY() - position->getY();
    float dz = camera->getPosition().getZ() - position->getZ();
    float distance = sqrt(dx*dx+dy*dy+dz*dz);

    size = minSize + (maxSize - minSize) * wizUtility::min(1.0f, distance / maxDistance);
}

#include "wizParticle2D.h"

wizParticle2D::wizParticle2D()
{
    velocity = NULL;
}

wizParticle2D::~wizParticle2D()
{
    if (velocity!=NULL) delete velocity;
}

void wizParticle2D::setVelocity(wizVector2* _velocity)
{
    velocity = _velocity;
}

void wizParticle2D::setRotationVelocity(float _rotationVelocity)
{
    rotationVelocity = _rotationVelocity;
}

wizVector2* wizParticle2D::getVelocity()
{
    return velocity;
}

float wizParticle2D::getRotationVelocity()
{
    return rotationVelocity;
}

void wizParticle2D::update(float _dt)
{
    wizSpriteEntity::update(_dt);

    angle += rotationVelocity * _dt;

    if (colourBuffer==NULL)
    {
        colourBuffer = new GLubyte[6 * 4];

        for (unsigned int i=0; i<6*4; i++)
        {
            colourBuffer[i] = 255;
        }
    }

    life -= decayRate * _dt;

    for (unsigned int i=0; i<6*4; i++)
    {
        colourBuffer[i] = (GLubyte)(life*255);
    }

    position.setX(position.getX() + velocity->getX() * _dt);
    position.setY(position.getY() + velocity->getY() * _dt);
}

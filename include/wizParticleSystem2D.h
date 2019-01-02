#ifndef WIZPARTICLESYSTEM2D_H
#define WIZPARTICLESYSTEM2D_H

#include "wizParticleSystem.h"
#include "wizParticle2D.h"

class wizParticleSystem2D : public wizParticleSystem
{
    public:

    wizParticleSystem2D();

    void setSheet(std::string _sheet);
    void setSprite(std::string _sprite);
    void setAnimation(std::string _animation);
    std::string getSheet();
    std::string getSprite();
    std::string getAnimation();

    virtual void render() = 0;

    protected:

    void addParticle(wizParticle* _particle);

    std::string sheet;
    std::string sprite;
    std::string animation;
};

#endif // WIZPARTICLESYSTEM2D_H

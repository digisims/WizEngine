#ifndef WIZPARTICLEEMITTER_H
#define WIZPARTICLEEMITTER_H

#include "wizParticle.h"

class wizParticleEmitter
{
    public:

    wizParticleEmitter();
    virtual ~wizParticleEmitter();

    virtual wizParticle* spawnParticle() = 0;

    protected:
};

#endif // WIZPARTICLEEMITTER_H

#ifndef WIZPARTICLESYSTEM_H
#define WIZPARTICLESYSTEM_H

#include "wizParticleEmitter.h"
#include "wizSpriteRenderer.h"

#include <string>
#include <vector>
#include <cstdlib>

class wizParticleSystem
{
    public:

    wizParticleSystem();
    virtual ~wizParticleSystem();

    void setRenderer(wizRenderer* _renderer);
    wizRenderer* getRenderer();

    void setEmitter(wizParticleEmitter* _emitter);
    void setLoop(bool _loop);
    wizParticleEmitter* getEmitter();
    bool getLoop();

    std::vector<wizParticle*> getParticles();
    void setMaximumParticles(unsigned int _maximumParticles);
    unsigned int getMaximumParticles();

    virtual void render() = 0;
    virtual void update(float _dt);

    protected:

    virtual void addParticle(wizParticle* _particle) = 0;

    bool loop;
    unsigned int maximumParticles;
    wizParticleEmitter* emitter;
    wizRenderer* renderer;
    std::vector<wizParticle*> particles;
};

#endif // WIZPARTICLESYSTEM_H

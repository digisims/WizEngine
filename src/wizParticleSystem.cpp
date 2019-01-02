#include "wizParticleSystem.h"

wizParticleSystem::wizParticleSystem()
{
    emitter = NULL;
    renderer = NULL;
}

wizParticleSystem::~wizParticleSystem()
{
    for (unsigned int i=0; i<particles.size(); i++)
    {
        if (particles[i]!=NULL) delete particles[i];
    }
}

void wizParticleSystem::setRenderer(wizRenderer* _renderer)
{
    renderer = _renderer;
}

wizRenderer* wizParticleSystem::getRenderer()
{
    return renderer;
}

void wizParticleSystem::setEmitter(wizParticleEmitter* _emitter)
{
    emitter = _emitter;
}

void wizParticleSystem::setLoop(bool _loop)
{
    loop = _loop;
}

wizParticleEmitter* wizParticleSystem::getEmitter()
{
    return emitter;
}

bool wizParticleSystem::getLoop()
{
    return loop;
}

std::vector<wizParticle*> wizParticleSystem::getParticles()
{
    return particles;
}

void wizParticleSystem::setMaximumParticles(unsigned int _maximumParticles)
{
    maximumParticles = _maximumParticles;
}

unsigned int wizParticleSystem::getMaximumParticles()
{
    return maximumParticles;
}

void wizParticleSystem::update(float _dt)
{
    for (unsigned int i=particles.size()-1; i>=0; i--)
    {
        particles[i]->update(_dt);

        if (particles[i]->isDead())
        {
            delete particles[i];
            particles.erase(particles.begin()+i);
        }
    }

    if (loop)
    {
        while (particles.size() < maximumParticles)
        {
            addParticle(emitter->spawnParticle());
        }
    }
}

#include "wizParticleSystem2D.h"

wizParticleSystem2D::wizParticleSystem2D()
{
    emitter = NULL;
    renderer = NULL;
}

void wizParticleSystem2D::setSheet(std::string _sheet)
{
    sheet = _sheet;
}

void wizParticleSystem2D::setSprite(std::string _sprite)
{
    sprite = _sprite;
}

void wizParticleSystem2D::setAnimation(std::string _animation)
{
    animation = _animation;
}

std::string wizParticleSystem2D::getSheet()
{
    return sheet;
}

std::string wizParticleSystem2D::getSprite()
{
    return sprite;
}

std::string wizParticleSystem2D::getAnimation()
{
    return animation;
}

void wizParticleSystem2D::render()
{
    wizSpriteRenderer* _renderer = (wizSpriteRenderer*)renderer;

    _renderer->applyGlobalSettings();
    _renderer->applyLocalSettings((wizSpriteEntity*)particles[0]);

    std::vector<wizSpriteEntity*> tmp;

    for (unsigned int i=0; i<particles.size(); i++)
    {
        tmp.push_back((wizSpriteEntity*)particles[i]);
    }

    _renderer->renderSpriteList(tmp);

    _renderer->undoLocalSettings((wizSpriteEntity*)particles[0]);
    _renderer->undoGlobalSettings();
}

void wizParticleSystem2D::addParticle(wizParticle* _particle)
{
    if (particles.size() >= maximumParticles)
    {
        particles.erase(particles.begin()+0);
    }

    ((wizParticle2D*)_particle)->setSheet(sheet);
    ((wizParticle2D*)_particle)->setSprite(sprite);
    ((wizParticle2D*)_particle)->setAnimation(animation);
    particles.push_back(_particle);
}

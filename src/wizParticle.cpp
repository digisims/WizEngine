#include "wizParticle.h"

wizParticle::wizParticle()
{
}

wizParticle::~wizParticle()
{
}

void wizParticle::setLife(float _life)
{
    life = _life;
}

void wizParticle::setDecayRate(float _decayRate)
{
    decayRate = _decayRate;
}

float wizParticle::getLife()
{
    return life;
}

float wizParticle::getDecayRate()
{
    return decayRate;
}

bool wizParticle::isDead()
{
    return life>0;
}

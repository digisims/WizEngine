#ifndef WIZPARTICLESYSTEM3D_H
#define WIZPARTICLESYSTEM3D_H

#include "wizParticleSystem.h"
#include "wizParticle3D.h"

#include <vector>

class wizParticleSystem3D : public wizParticleSystem
{
    public:

    static const unsigned int POINT_CACHE = 32;

    wizParticleSystem3D();

    void setTexture(std::string _texture);
    std::string getTexture();

    virtual void render() = 0;

    protected:

    void addParticle(wizParticle* _particle);

    std::string texture;
    GLfloat* vertexBuffer;
    std::vector<unsigned int> order;
};

#endif // WIZPARTICLESYSTEM3D_H

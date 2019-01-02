#include "wizParticleSystem3D.h"

wizParticleSystem3D::wizParticleSystem3D()
{
    vertexBuffer = new float[POINT_CACHE * 3];
    emitter = NULL;
    renderer = NULL;
}

void wizParticleSystem3D::setTexture(std::string _texture)
{
    texture = _texture;
}

std::string wizParticleSystem3D::getTexture()
{
    return texture;
}

void wizParticleSystem3D::render()
{
    #ifndef WIN32
    glActiveTexture(GL_TEXTURE0);
    #endif
    glEnable(GL_TEXTURE_2D);
    int id = wizTextureManager::getTexture(texture);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    #ifndef WIN32
    glEnable(GL_POINT_SPRITE_OES);
    glTexEnvf(GL_POINT_SPRITE_OES, GL_COORD_REPLACE_OES, GL_TRUE);
    #endif

    while (order.size() < particles.size())
    {
        order.push_back(0);
    }

    for (unsigned int i=0; i<particles.size(); i++)
    {
        order[i] = i;
    }

    for (unsigned int i=0; i<particles.size(); i++)
    {
        for (unsigned int j=i+1; j<particles.size(); j++)
        {
            if (((wizParticle3D*)particles[order[j]])->getSize() < ((wizParticle3D*)particles[order[i]])->getSize())
            {
                unsigned int tmp = order[i];
                order[i] = order[j];
                order[j] = tmp;
            }
        }
    }

    for (unsigned int i=0; i<particles.size(); i+=POINT_CACHE)
    {
        unsigned int k = 1;

        while (k < POINT_CACHE && i+k < particles.size())
        {
            if ((int)((wizParticle3D*)particles[order[i+k]])->getSize() != (int)((wizParticle3D*)particles[order[i+k-1]])->getSize())
            {
                break;
            }
            k++;
        }

        for (unsigned int j=0; j<k; j++)
        {
            vertexBuffer[j*3] = ((wizParticle3D*)particles[order[i+j]])->getPosition()->getX();
            vertexBuffer[j*3+1] = ((wizParticle3D*)particles[order[i+j]])->getPosition()->getY();
            vertexBuffer[j*3+2] = ((wizParticle3D*)particles[order[i+j]])->getPosition()->getZ();
        }

        glPointSize(((wizParticle3D*)particles[order[i]])->getSize());
        glVertexPointer(3, GL_FLOAT, 0, vertexBuffer);
        glDrawArrays(GL_POINTS, 0, k);
    }

    #ifndef WIN32
    glDisable(GL_POINT_SPRITE_OES);
    glTexEnvf(GL_POINT_SPRITE_OES, GL_COORD_REPLACE_OES, GL_FALSE);
    #endif
    glDisable(GL_TEXTURE_2D);
}

void wizParticleSystem3D::addParticle(wizParticle* _particle)
{
    if (particles.size() >= maximumParticles)
    {
        particles.erase(particles.begin()+0);
    }

    particles.push_back(_particle);
}

#ifndef WIZPROJECTIVESHADOWRENDERER_H
#define WIZPROJECTIVESHADOWRENDERER_H

#include "wizMatrix.h"

class wizProjectiveShadowRenderer
{
    public:

    wizProjectiveShadowRenderer();
    virtual ~wizProjectiveShadowRenderer();

    protected:

    float* biasMatrix;
};

#endif // WIZPROJECTIVESHADOWRENDERER_H

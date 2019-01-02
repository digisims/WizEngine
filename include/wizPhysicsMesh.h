#ifndef WIZPHYSICSMESH_H
#define WIZPHYSICSMESH_H

#include "wizVector3.h"
#include "wizBoundingBox.h"

class wizPhysicsMesh
{
    public:

    wizPhysicsMesh();
    wizPhysicsMesh(wizBoundingBox _bbox, float* _matrix, float* _invMatrix);
    virtual ~wizPhysicsMesh();

    wizVector3 getVertex(unsigned int _idx);
    wizVector3 getTransformedVertex(unsigned int _idx);
    wizVector3 getCenter();
    wizBoundingBox getBoundingBox();

    protected:

    wizBoundingBox bbox;
    float* transformationMatrix;
    float* invTransformationMatrix;
};

#endif // WIZPHYSICSMESH_H

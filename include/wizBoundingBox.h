#ifndef WIZBOUNDINGBOX_H
#define WIZBOUNDINGBOX_H

#include "wizBoundingVolume.h"
#include "wizVector3.h"
#include "SDL.h"
#include "DGE_Frame.h"
#include "DGE_Display.h"

#include <cstdlib>
#include <limits>

class wizBoundingBox : wizBoundingVolume
{
    public:

    static int BOX_EDGE[12][2];

    wizBoundingBox();
    wizBoundingBox(wizVector3 _minimum, wizVector3 _maximum);
    virtual ~wizBoundingBox();

    wizVector3 getCenter();

    wizBoundingBox mul(float* matrix);

    static bool doesRayIntersect(wizBoundingBox b1, wizRay ray);
    static wizIntersectionPoint getIntersectionPoint(wizBoundingBox b1, wizRay ray);
    static bool doesIntersectAABB(wizBoundingBox b1, wizBoundingBox b2);
    static wizIntersectionPoint getIntersectOBB(wizBoundingBox b1, float* m1, wizBoundingBox b2, float* m2);
    static bool doesIntersectOBB(wizBoundingBox b1, float* m1, wizBoundingBox b2, float* m2);
    static bool doesIntersectTriangle(wizBoundingBox b1, float* m1, GLfloat* vertexBuffer, GLushort* indexBuffer, unsigned int idx);
    static wizIntersectionPoint getIntersectTriangle(wizBoundingBox b1, float* m1, GLfloat* vertexBuffer, GLushort* indexBuffer, unsigned int idx);
    static wizIntersectionPoint getIntersectTriangle(wizBoundingBox b1, wizVector3 center, GLfloat* vertexBuffer, GLushort* indexBuffer, unsigned int idx);
    static wizIntersectionPoint getSphereIntersectTriangle(wizBoundingBox b1, wizVector3 center, GLfloat* vertexBuffer, GLushort* indexBuffer, unsigned int idx);
    static wizIntersectionPoint getSphereIntersectAABB(wizBoundingBox b1, wizBoundingBox b2);
    static wizIntersectionPoint getSphereIntersectOBB(wizBoundingBox b1, wizBoundingBox b2, float* m1);
    static wizIntersectionPoint getSphereIntersectSphere(wizBoundingBox b1, wizBoundingBox b2);

    wizVector3 getVertex(unsigned int _idx);

    void setMinimum(wizVector3 _minimum);
    void setMaximum(wizVector3 _maximum);
    wizVector3 getMinimum();
    wizVector3 getMaximum();

    void merge(wizBoundingBox _bbox);

    protected:

    static bool overlap(float min0, float max0, float min1, float max1);
    static bool spanOverlap(float min0, float max0, float min1, float max1);
    static void computeSpan(wizVector3 axis, wizVector3 p, wizVector3 e, wizVector3 x, wizVector3 y, wizVector3 z, float& min, float& max);
    static void computeSpan(wizVector3 axis, wizVector3 v0, wizVector3 v1, wizVector3 v2, float& min, float& max);
    static bool axisOverlap(wizVector3 axis, wizVector3 p1, wizVector3 e1, wizVector3 x1, wizVector3 y1, wizVector3 z1, wizVector3 p2, wizVector3 e2, wizVector3 x2, wizVector3 y2, wizVector3 z2);
    static bool axisOverlap(wizVector3 axis, wizVector3 p1, wizVector3 e1, wizVector3 x1, wizVector3 y1, wizVector3 z1, wizVector3 p2, wizVector3 e2, wizVector3 x2, wizVector3 y2, wizVector3 z2, float& min0, float& max0, float& min1, float& max1);
    static bool axisOverlap(wizVector3 axis, wizVector3 p1, wizVector3 e1, wizVector3 x1, wizVector3 y1, wizVector3 z1, wizVector3 v0, wizVector3 v1, wizVector3 v2);
    static bool axisOverlap(wizVector3 axis, wizVector3 p1, wizVector3 e1, wizVector3 x1, wizVector3 y1, wizVector3 z1, wizVector3 v0, wizVector3 v1, wizVector3 v2, float& min0, float& max0, float& min1, float& max1);

    wizVector3 minimum;
    wizVector3 maximum;
    wizVector3** cache;
};

#endif // WIZBOUNDINGBOX_H

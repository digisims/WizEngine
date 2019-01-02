#include "wizBoundingBox.h"

int wizBoundingBox::BOX_EDGE[12][2] = { { 0, 1 }, { 4, 5 }, { 0, 4 },
                                        { 1, 5 }, { 2, 3 }, { 6, 7 },
                                        { 2, 6 }, { 3, 7 }, { 0, 3 },
                                        { 1, 2 }, { 4, 7 }, { 5, 6 } };

wizBoundingBox::wizBoundingBox()
{
    cache = NULL;
}

wizBoundingBox::wizBoundingBox(wizVector3 _minimum, wizVector3 _maximum)
{
    cache = NULL;
    minimum = _minimum;
    maximum = _maximum;
}

wizBoundingBox::~wizBoundingBox()
{
    if (cache!=NULL)
    {
        delete[] cache;
    }
}

wizVector3 wizBoundingBox::getCenter()
{
    return minimum.add(maximum).mul(0.5f);
}

void wizBoundingBox::setMinimum(wizVector3 _minimum)
{
    minimum = _minimum;
}

void wizBoundingBox::setMaximum(wizVector3 _maximum)
{
    maximum = _maximum;
}

wizVector3 wizBoundingBox::getMinimum()
{
    return minimum;
}

wizVector3 wizBoundingBox::getMaximum()
{
    return maximum;
}

wizBoundingBox wizBoundingBox::mul(float* matrix)
{
    if (matrix!=NULL)
    {
        float minX = 1000000;
        float minY = 1000000;
        float minZ = 1000000;
        float maxX = -1000000;
        float maxY = -1000000;
        float maxZ = -1000000;

        for (unsigned int i=0; i<8; i++)
        {
            wizVector3 tmp = getVertex(i).mul(matrix);

            if (tmp.getX() < minX) minX = tmp.getX();
            if (tmp.getY() < minY) minY = tmp.getY();
            if (tmp.getZ() < minZ) minZ = tmp.getZ();

            if (tmp.getX() > maxX) maxX = tmp.getX();
            if (tmp.getY() > maxY) maxY = tmp.getY();
            if (tmp.getZ() > maxZ) maxZ = tmp.getZ();
        }

        return wizBoundingBox(wizVector3(minX, minY, minZ), wizVector3(maxX, maxY, maxZ));
    }
    else
    {
        return wizBoundingBox(minimum, maximum);
    }
}

wizVector3 wizBoundingBox::getVertex(unsigned int _idx)
{
    if (cache==NULL)
    {
        cache = new wizVector3*[8];

        for (unsigned int i=0; i<8; i++)
        {
            cache[i] = NULL;
        }
    }

    if (cache[_idx]!=NULL)
    {
        return *cache[_idx];
    }

    wizVector3 dimension = maximum.sub(minimum);

    // 0,1
    // 4,5
    // 0,4
    // 1,5
    // 2,3
    // 6,7
    // 2,6
    // 3,7
    // 0,3
    // 1,2
    // 4,7
    // 5,6

    switch (_idx)
    {
        case 0:
            cache[_idx] = new wizVector3(minimum);
            break;

        case 1:
            cache[_idx] = new wizVector3(minimum);
            cache[_idx]->setX(cache[_idx]->getX()+dimension.getX());
            break;

        case 2:
            cache[_idx] = new wizVector3(minimum);
            cache[_idx]->setX(cache[_idx]->getX()+dimension.getX());
            cache[_idx]->setZ(cache[_idx]->getZ()+dimension.getZ());
            break;

        case 3:
            cache[_idx] = new wizVector3(minimum);
            cache[_idx]->setZ(cache[_idx]->getZ()+dimension.getZ());
            break;

        case 4:
            cache[_idx] = new wizVector3(minimum);
            cache[_idx]->setY(cache[_idx]->getY()+dimension.getY());
            break;

        case 5:
            cache[_idx] = new wizVector3(minimum);
            cache[_idx]->setX(cache[_idx]->getX()+dimension.getX());
            cache[_idx]->setY(cache[_idx]->getY()+dimension.getY());
            break;

        case 6:
            cache[_idx] = new wizVector3(minimum);
            cache[_idx]->setX(cache[_idx]->getX()+dimension.getX());
            cache[_idx]->setY(cache[_idx]->getY()+dimension.getY());
            cache[_idx]->setZ(cache[_idx]->getZ()+dimension.getZ());
            break;

        case 7:
            cache[_idx] = new wizVector3(minimum);
            cache[_idx]->setY(cache[_idx]->getY()+dimension.getY());
            cache[_idx]->setZ(cache[_idx]->getZ()+dimension.getZ());
            break;
    }

    return *cache[_idx];
}

bool wizBoundingBox::doesRayIntersect(wizBoundingBox b1, wizRay ray)
{
    float tNear = -1000000;
    float tFar = 1000000;

    float xLow=b1.getMinimum().getX();
    float xHi=b1.getMaximum().getX();

    if (ray.getDirection().getX() == 0)
    {
        if (ray.getOrigin().getX() < xLow || ray.getOrigin().getX() > xHi)
        {
            return false;
        }
    }
    else
    {
        float t1 = (xLow - ray.getOrigin().getX()) / ray.getDirection().getX();
        float t2 = (xHi - ray.getOrigin().getX()) / ray.getDirection().getX();

        if (t1 > t2)
        {
            float temp = t1;
            t1 = t2;
            t2 = temp;
        }

        if (t1 > tNear) tNear = t1;
        if (t2 < tFar) tFar = t2;

        if (tNear>tFar || tFar<0)
        {
            return false;
        }
    }

    float yLow = b1.getMinimum().getY();
    float yHi = b1.getMaximum().getY();

    if (ray.getDirection().getY() == 0)
    {
        if (ray.getOrigin().getY() < yLow || ray.getOrigin().getY() > yHi)
        {
            return false;
        }
    }
    else
    {
        float t1 = (yLow - ray.getOrigin().getY()) / ray.getDirection().getY();
        float t2 = (yHi - ray.getOrigin().getY()) / ray.getDirection().getY();

        if (t1 > t2)
        {
            float temp = t1;
            t1 = t2;
            t2 = temp;
        }

        if (t1 > tNear) tNear = t1;
        if (t2 < tFar) tFar = t2;

        if (tNear > tFar || tFar < 0)
        {
            return false;
        }
    }

    float zLow = b1.getMinimum().getZ();
    float zHi = b1.getMaximum().getZ();

    if (ray.getDirection().getZ() == 0)
    {
        if (ray.getOrigin().getZ() < zLow || ray.getOrigin().getZ() > zHi)
        {
            return false;
        }
    }
    else
    {
        float t1 = (zLow - ray.getOrigin().getZ()) / ray.getDirection().getZ();
        float t2 = (zHi - ray.getOrigin().getZ()) / ray.getDirection().getZ();

        if (t1 > t2)
        {
            float temp = t1;
            t1 = t2;
            t2 = temp;
        }

        if (t1 > tNear) tNear = t1;
        if (t2 < tFar) tFar = t2;

        if (tNear > tFar || tFar < 0)
        {
            return false;
        }
    }

    return true;
}

wizIntersectionPoint wizBoundingBox::getIntersectionPoint(wizBoundingBox b1, wizRay ray)
{
    float tNear = -1000000;
    float tFar = 1000000;
    wizIntersectionPoint ip;
    ip.setType(wizIntersectionPoint::POINT_MISS);

    float xLow=b1.getMinimum().getX();
    float xHi=b1.getMaximum().getX();

    if (ray.getDirection().getX() == 0)
    {
        if (ray.getOrigin().getX() < xLow || ray.getOrigin().getX() > xHi)
        {
            return ip;
        }
    }
    else
    {
        float t1 = (xLow - ray.getOrigin().getX()) / ray.getDirection().getX();
        float t2 = (xHi - ray.getOrigin().getX()) / ray.getDirection().getX();

        if (t1 > t2)
        {
            float temp = t1;
            t1 = t2;
            t2 = temp;
        }

        if (t1 > tNear) tNear = t1;
        if (t2 < tFar) tFar = t2;

        if (tNear>tFar || tFar<0)
        {
            return ip;
        }
    }

    float yLow = b1.getMinimum().getY();
    float yHi = b1.getMaximum().getY();

    if (ray.getDirection().getY() == 0)
    {
        if (ray.getOrigin().getY() < yLow || ray.getOrigin().getY() > yHi)
        {
            return ip;
        }
    }
    else
    {
        float t1 = (yLow - ray.getOrigin().getY()) / ray.getDirection().getY();
        float t2 = (yHi - ray.getOrigin().getY()) / ray.getDirection().getY();

        if (t1 > t2)
        {
            float temp = t1;
            t1 = t2;
            t2 = temp;
        }

        if (t1 > tNear) tNear = t1;
        if (t2 < tFar) tFar = t2;

        if (tNear > tFar || tFar < 0)
        {
            return ip;
        }
    }

    float zLow = b1.getMinimum().getZ();
    float zHi = b1.getMaximum().getZ();

    if (ray.getDirection().getZ() == 0)
    {
        if (ray.getOrigin().getZ() < zLow || ray.getOrigin().getZ() > zHi)
        {
            return ip;
        }
    }
    else
    {
        float t1 = (zLow - ray.getOrigin().getZ()) / ray.getDirection().getZ();
        float t2 = (zHi - ray.getOrigin().getZ()) / ray.getDirection().getZ();

        if (t1 > t2)
        {
            float temp = t1;
            t1 = t2;
            t2 = temp;
        }

        if (t1 > tNear) tNear = t1;
        if (t2 < tFar) tFar = t2;

        if (tNear > tFar || tFar < 0)
        {
            return ip;
        }
    }

    ip.setType(wizIntersectionPoint::POINT_INTERSECTION);
    ip.setDistance(tNear);
    ip.setPoint(ray.getOrigin().add(ray.getDirection().mul(tNear)));

    return ip;
}

void wizBoundingBox::merge(wizBoundingBox _bbox)
{
    wizVector3 min = _bbox.getMinimum();
    wizVector3 max = _bbox.getMaximum();

    if (min.getX()<minimum.getX()) minimum.setX(min.getX());
    if (min.getY()<minimum.getY()) minimum.setY(min.getY());
    if (min.getZ()<minimum.getZ()) minimum.setZ(min.getZ());
    if (max.getX()>maximum.getX()) maximum.setX(max.getX());
    if (max.getY()>maximum.getY()) maximum.setY(max.getY());
    if (max.getZ()>maximum.getZ()) maximum.setZ(max.getZ());

    if (cache!=NULL)
    {
        delete[] cache;

        cache = NULL;
    }
}

bool wizBoundingBox::overlap(float min0, float max0, float min1, float max1)
{
    return (min0 > max1 || max0 < min1);
}

bool wizBoundingBox::spanOverlap(float min0, float max0, float min1, float max1)
{
    return !(min0 > max1 || max0 < min1);
}

void wizBoundingBox::computeSpan(wizVector3 axis, wizVector3 p, wizVector3 e, wizVector3 x, wizVector3 y, wizVector3 z, float& min, float& max)
{
    float p0 = axis.dot(p);
    float r0 = fabs(axis.dot(x)) * e.getX() + fabs(axis.dot(y)) * e.getY() + fabs(axis.dot(z)) * e.getZ();

    min = p0-r0;
    max = p0+r0;
}

bool wizBoundingBox::axisOverlap(wizVector3 axis, wizVector3 p1, wizVector3 e1, wizVector3 x1, wizVector3 y1, wizVector3 z1, wizVector3 p2, wizVector3 e2, wizVector3 x2, wizVector3 y2, wizVector3 z2)
{
    float min0;
    float max0;
    float min1;
    float max1;

    computeSpan(axis, p1, e1, x1, y1, z1, min0, max0);
    computeSpan(axis, p2, e2, x2, y2, z2, min1, max1);

    return spanOverlap(min0, max0, min1, max1);
}

bool wizBoundingBox::axisOverlap(wizVector3 axis, wizVector3 p1, wizVector3 e1, wizVector3 x1, wizVector3 y1, wizVector3 z1, wizVector3 p2, wizVector3 e2, wizVector3 x2, wizVector3 y2, wizVector3 z2, float& min0, float& max0, float& min1, float& max1)
{
    computeSpan(axis, p1, e1, x1, y1, z1, min0, max0);
    computeSpan(axis, p2, e2, x2, y2, z2, min1, max1);

    return spanOverlap(min0, max0, min1, max1);
}

bool wizBoundingBox::doesIntersectAABB(wizBoundingBox b1, wizBoundingBox b2)
{
    wizVector3 b1min = b1.getMinimum();
    wizVector3 b1max = b1.getMaximum();
    wizVector3 b2min = b2.getMinimum();
    wizVector3 b2max = b2.getMaximum();

    if (b1min.getX() >= b2min.getX() && b1min.getY() >= b2min.getY() && b1min.getZ() >= b2min.getZ() &&
        b1max.getX() <= b2max.getX() && b1max.getY() <= b2max.getY() && b1max.getZ() <= b2max.getZ())
    return true;

    if (b2min.getX() >= b1min.getX() && b2min.getY() >= b1min.getY() && b2min.getZ() >= b1min.getZ() &&
        b2max.getX() <= b1max.getX() && b2max.getY() <= b1max.getY() && b2max.getZ() <= b1max.getZ())
    return true;

    return !(b2min.getX() > b1max.getX() || b1min.getX() > b2max.getX() ||
             b2min.getY() > b1max.getY() || b1min.getY() > b2max.getY() ||
             b2min.getZ() > b1max.getZ() || b1min.getZ() > b2max.getZ());
}

bool wizBoundingBox::doesIntersectOBB(wizBoundingBox b1, float* m1, wizBoundingBox b2, float* m2)
{
    wizVector3 p1 = b1.getCenter().mul(m1);
    wizVector3 e1 = (b1.getMaximum().sub(b1.getMinimum())).mul(0.5f);
    wizVector3 x1(m1[0], m1[1], m1[2]);
    wizVector3 y1(m1[4], m1[5], m1[6]);
    wizVector3 z1(m1[8], m1[9], m1[10]);
    wizVector3 p2 = b2.getCenter().mul(m2);
    wizVector3 e2 = (b2.getMaximum().sub(b2.getMinimum())).mul(0.5f);
    wizVector3 x2(m2[0], m2[1], m2[2]);
    wizVector3 y2(m2[4], m2[5], m2[6]);
    wizVector3 z2(m2[8], m2[9], m2[10]);

    if (!axisOverlap(x1, p1, e1, x1, y1, z1, p2, e2, x2, y2, z2)) return false;
    if (!axisOverlap(y1, p1, e1, x1, y1, z1, p2, e2, x2, y2, z2)) return false;
    if (!axisOverlap(z1, p1, e1, x1, y1, z1, p2, e2, x2, y2, z2)) return false;

    if (!axisOverlap(x2, p1, e1, x1, y1, z1, p2, e2, x2, y2, z2)) return false;
    if (!axisOverlap(y2, p1, e1, x1, y1, z1, p2, e2, x2, y2, z2)) return false;
    if (!axisOverlap(z2, p1, e1, x1, y1, z1, p2, e2, x2, y2, z2)) return false;

    if (!axisOverlap(x1.cross(x2), p1, e1, x1, y1, z1, p2, e2, x2, y2, z2)) return false;
    if (!axisOverlap(x1.cross(y2), p1, e1, x1, y1, z1, p2, e2, x2, y2, z2)) return false;
    if (!axisOverlap(x1.cross(z2), p1, e1, x1, y1, z1, p2, e2, x2, y2, z2)) return false;

    if (!axisOverlap(y1.cross(x2), p1, e1, x1, y1, z1, p2, e2, x2, y2, z2)) return false;
    if (!axisOverlap(y1.cross(y2), p1, e1, x1, y1, z1, p2, e2, x2, y2, z2)) return false;
    if (!axisOverlap(y1.cross(z2), p1, e1, x1, y1, z1, p2, e2, x2, y2, z2)) return false;

    if (!axisOverlap(z1.cross(x2), p1, e1, x1, y1, z1, p2, e2, x2, y2, z2)) return false;
    if (!axisOverlap(z1.cross(y2), p1, e1, x1, y1, z1, p2, e2, x2, y2, z2)) return false;
    if (!axisOverlap(z1.cross(z2), p1, e1, x1, y1, z1, p2, e2, x2, y2, z2)) return false;

    return true;
}

wizIntersectionPoint wizBoundingBox::getIntersectOBB(wizBoundingBox b1, float* m1, wizBoundingBox b2, float* m2)
{
    wizVector3 p1 = b1.getCenter().mul(m1);
    wizVector3 e1 = (b1.getMaximum().sub(b1.getMinimum())).mul(0.5f);
    wizVector3 x1(m1[0], m1[1], m1[2]);
    wizVector3 y1(m1[4], m1[5], m1[6]);
    wizVector3 z1(m1[8], m1[9], m1[10]);
    wizVector3 p2 = b2.getCenter().mul(m2);
    wizVector3 e2 = (b2.getMaximum().sub(b2.getMinimum())).mul(0.5f);
    wizVector3 x2(m2[0], m2[1], m2[2]);
    wizVector3 y2(m2[4], m2[5], m2[6]);
    wizVector3 z2(m2[8], m2[9], m2[10]);

    wizVector3 axis[15];
    float min0[15];
    float max0[15];
    float min1[15];
    float max1[15];

    wizIntersectionPoint ip;
    ip.setType(wizIntersectionPoint::POINT_MISS);

    axis[0] = x1;
    if (!axisOverlap(x1, p1, e1, x1, y1, z1, p2, e2, x2, y2, z2, min0[0], max0[0], min1[0], max1[0])) return ip;
    axis[1] = y1;
    if (!axisOverlap(y1, p1, e1, x1, y1, z1, p2, e2, x2, y2, z2, min0[1], max0[1], min1[1], max1[1])) return ip;
    axis[2] = z1;
    if (!axisOverlap(z1, p1, e1, x1, y1, z1, p2, e2, x2, y2, z2, min0[2], max0[2], min1[2], max1[2])) return ip;

    axis[3] = x2;
    if (!axisOverlap(x2, p1, e1, x1, y1, z1, p2, e2, x2, y2, z2, min0[3], max0[3], min1[3], max1[3])) return ip;
    axis[4] = y2;
    if (!axisOverlap(y2, p1, e1, x1, y1, z1, p2, e2, x2, y2, z2, min0[4], max0[4], min1[4], max1[4])) return ip;
    axis[5] = z2;
    if (!axisOverlap(z2, p1, e1, x1, y1, z1, p2, e2, x2, y2, z2, min0[5], max0[5], min1[5], max1[5])) return ip;

    axis[6] = x1.cross(x2);
    if (!axisOverlap(axis[6], p1, e1, x1, y1, z1, p2, e2, x2, y2, z2, min0[6], max0[6], min1[6], max1[6])) return ip;
    axis[7] = x1.cross(y2);
    if (!axisOverlap(axis[7], p1, e1, x1, y1, z1, p2, e2, x2, y2, z2, min0[7], max0[7], min1[7], max1[7])) return ip;
    axis[8] = x1.cross(z2);
    if (!axisOverlap(axis[8], p1, e1, x1, y1, z1, p2, e2, x2, y2, z2, min0[8], max0[8], min1[8], max1[8])) return ip;

    axis[9] = y1.cross(x2);
    if (!axisOverlap(axis[9], p1, e1, x1, y1, z1, p2, e2, x2, y2, z2, min0[9], max0[9], min1[9], max1[9])) return ip;
    axis[10] = y1.cross(y2);
    if (!axisOverlap(axis[10], p1, e1, x1, y1, z1, p2, e2, x2, y2, z2, min0[10], max0[10], min1[10], max1[10])) return ip;
    axis[11] = y1.cross(z2);
    if (!axisOverlap(axis[11], p1, e1, x1, y1, z1, p2, e2, x2, y2, z2, min0[11], max0[11], min1[11], max1[11])) return ip;

    axis[12] = z1.cross(x2);
    if (!axisOverlap(axis[12], p1, e1, x1, y1, z1, p2, e2, x2, y2, z2, min0[12], max0[12], min1[12], max1[12])) return ip;
    axis[13] = z1.cross(y2);
    if (!axisOverlap(axis[13], p1, e1, x1, y1, z1, p2, e2, x2, y2, z2, min0[13], max0[13], min1[13], max1[13])) return ip;
    axis[14] = z1.cross(z2);
    if (!axisOverlap(axis[14], p1, e1, x1, y1, z1, p2, e2, x2, y2, z2, min0[14], max0[14], min1[14], max1[14])) return ip;

    float depth = 1000000;

    for (unsigned int i=0; i<15; i++)
    {
        float min = min1[i] > min0[i] ? min1[i] : min0[i];
        float max = max1[i] < max0[i] ? max1[i] : max0[i];

        float d = max-min;
        float l = axis[i].length();

        if (l < 0.000001f)
        {
            continue;
        }

        d /= l;

        if (d < depth)
        {
            depth = d;
            ip.setNormal(axis[i].mul(1/l));
        }
    }

    wizVector3 diff = p2.sub(p1);

    if (diff.dot(ip.getNormal())>0)
    {
        ip.setNormal(ip.getNormal().mul(-1));
    }

    ip.setType(wizIntersectionPoint::POINT_INTERSECTION);
    ip.setDistance(depth);
    ip.setPoint(p1.add(ip.getNormal().mul(depth)));

    return ip;
}

void wizBoundingBox::computeSpan(wizVector3 axis, wizVector3 v0, wizVector3 v1, wizVector3 v2, float& min, float& max)
{
    float d;

    d = v0.dot(axis);
    min = d;
    max = d;

    d = v1.dot(axis);
    if (d < min)
    {
        min = d;
    }
    else if (d > max)
    {
        max = d;
    }

    d = v2.dot(axis);
    if (d < min)
    {
        min = d;
    }
    else if (d > max)
    {
        max = d;
    }
}

bool wizBoundingBox::axisOverlap(wizVector3 axis, wizVector3 p1, wizVector3 e1, wizVector3 x1, wizVector3 y1, wizVector3 z1, wizVector3 v0, wizVector3 v1, wizVector3 v2, float& min0, float& max0, float& min1, float& max1)
{
    computeSpan(axis, p1, e1, x1, y1, z1, min0, max0);
    computeSpan(axis, v0, v1, v2, min1, max1);

    return spanOverlap(min0, max0, min1, max1);
}

bool wizBoundingBox::axisOverlap(wizVector3 axis, wizVector3 p1, wizVector3 e1, wizVector3 x1, wizVector3 y1, wizVector3 z1, wizVector3 v0, wizVector3 v1, wizVector3 v2)
{
    float min0;
    float max0;
    float min1;
    float max1;

    computeSpan(axis, p1, e1, x1, y1, z1, min0, max0);
    computeSpan(axis, v0, v1, v2, min1, max1);

    return spanOverlap(min0, max0, min1, max1);
}

bool wizBoundingBox::doesIntersectTriangle(wizBoundingBox b1, float* m1, GLfloat* vertexBuffer, GLushort* indexBuffer, unsigned int idx)
{
    wizVector3 p1 = b1.getCenter().mul(m1);
    wizVector3 e1 = (b1.getMaximum().sub(b1.getMinimum())).mul(0.5f);
    wizVector3 x1(m1[0], m1[1], m1[2]);
    wizVector3 y1(m1[4], m1[5], m1[6]);
    wizVector3 z1(m1[8], m1[9], m1[10]);

    unsigned short a = indexBuffer[idx*3];
    unsigned short b = indexBuffer[idx*3+1];
    unsigned short c = indexBuffer[idx*3+2];

    wizVector3 v0(vertexBuffer[a*3]-p1.getX(), vertexBuffer[a*3+1]-p1.getY(), vertexBuffer[a*3+2]-p1.getZ());
    wizVector3 v1(vertexBuffer[b*3]-p1.getX(), vertexBuffer[b*3+1]-p1.getY(), vertexBuffer[b*3+2]-p1.getZ());
    wizVector3 v2(vertexBuffer[c*3]-p1.getX(), vertexBuffer[c*3+1]-p1.getY(), vertexBuffer[c*3+2]-p1.getZ());

    p1 = wizVector3(0, 0, 0);

    wizVector3 te0 = v1.sub(v0);
    wizVector3 te1 = v2.sub(v1);
    wizVector3 te2 = v0.sub(v2);
    wizVector3 n = te0.cross(te1).normalize();

    if (!axisOverlap(n, p1, e1, x1, y1, z1, v0, v1, v2)) return false;

    if (!axisOverlap(x1, p1, e1, x1, y1, z1, v0, v1, v2)) return false;
    if (!axisOverlap(y1, p1, e1, x1, y1, z1, v0, v1, v2)) return false;
    if (!axisOverlap(z1, p1, e1, x1, y1, z1, v0, v1, v2)) return false;

    if (!axisOverlap(x1.cross(te0), p1, e1, x1, y1, z1, v0, v1, v2)) return false;
    if (!axisOverlap(x1.cross(te1), p1, e1, x1, y1, z1, v0, v1, v2)) return false;
    if (!axisOverlap(x1.cross(te2), p1, e1, x1, y1, z1, v0, v1, v2)) return false;

    if (!axisOverlap(y1.cross(te0), p1, e1, x1, y1, z1, v0, v1, v2)) return false;
    if (!axisOverlap(y1.cross(te1), p1, e1, x1, y1, z1, v0, v1, v2)) return false;
    if (!axisOverlap(y1.cross(te2), p1, e1, x1, y1, z1, v0, v1, v2)) return false;

    if (!axisOverlap(z1.cross(te0), p1, e1, x1, y1, z1, v0, v1, v2)) return false;
    if (!axisOverlap(z1.cross(te1), p1, e1, x1, y1, z1, v0, v1, v2)) return false;
    if (!axisOverlap(z1.cross(te2), p1, e1, x1, y1, z1, v0, v1, v2)) return false;

    return true;
}

wizIntersectionPoint wizBoundingBox::getIntersectTriangle(wizBoundingBox b1, float* m1, GLfloat* vertexBuffer, GLushort* indexBuffer, unsigned int idx)
{
    wizVector3 p1 = b1.getCenter().mul(m1);
    wizVector3 e1 = (b1.getMaximum().sub(b1.getMinimum())).mul(0.5f);
    wizVector3 x1(m1[0], m1[1], m1[2]);
    wizVector3 y1(m1[4], m1[5], m1[6]);
    wizVector3 z1(m1[8], m1[9], m1[10]);

    unsigned short a = indexBuffer[idx*3];
    unsigned short b = indexBuffer[idx*3+1];
    unsigned short c = indexBuffer[idx*3+2];

    wizVector3 v0(vertexBuffer[a*3]-p1.getX(), vertexBuffer[a*3+1]-p1.getY(), vertexBuffer[a*3+2]-p1.getZ());
    wizVector3 v1(vertexBuffer[b*3]-p1.getX(), vertexBuffer[b*3+1]-p1.getY(), vertexBuffer[b*3+2]-p1.getZ());
    wizVector3 v2(vertexBuffer[c*3]-p1.getX(), vertexBuffer[c*3+1]-p1.getY(), vertexBuffer[c*3+2]-p1.getZ());

    p1 = wizVector3(0, 0, 0);

    wizVector3 te0 = v1.sub(v0);
    wizVector3 te1 = v2.sub(v1);
    wizVector3 te2 = v0.sub(v2);
    wizVector3 n = te0.cross(te1).normalize();

    wizVector3 axis[13];
    float min0[13];
    float max0[13];
    float min1[13];
    float max1[13];

    wizIntersectionPoint ip;
    ip.setType(wizIntersectionPoint::POINT_MISS);

    axis[0] = n;
    if (!axisOverlap(axis[0], p1, e1, x1, y1, z1, v0, v1, v2, min0[0], max0[0], min1[0], max1[0])) return ip;

    axis[1] = x1;
    if (!axisOverlap(axis[1], p1, e1, x1, y1, z1, v0, v1, v2, min0[1], max0[1], min1[1], max1[1])) return ip;
    axis[2] = y1;
    if (!axisOverlap(axis[2], p1, e1, x1, y1, z1, v0, v1, v2, min0[2], max0[2], min1[2], max1[2])) return ip;
    axis[3] = z1;
    if (!axisOverlap(axis[3], p1, e1, x1, y1, z1, v0, v1, v2, min0[3], max0[3], min1[3], max1[3])) return ip;

    axis[4] = x1.cross(te0);
    if (!axisOverlap(axis[4], p1, e1, x1, y1, z1, v0, v1, v2, min0[4], max0[4], min1[4], max1[4])) return ip;
    axis[5] = x1.cross(te1);
    if (!axisOverlap(axis[5], p1, e1, x1, y1, z1, v0, v1, v2, min0[5], max0[5], min1[5], max1[5])) return ip;
    axis[6] = x1.cross(te2);
    if (!axisOverlap(axis[6], p1, e1, x1, y1, z1, v0, v1, v2, min0[6], max0[6], min1[6], max1[6])) return ip;

    axis[7] = y1.cross(te0);
    if (!axisOverlap(axis[7], p1, e1, x1, y1, z1, v0, v1, v2, min0[7], max0[7], min1[7], max1[7])) return ip;
    axis[8] = y1.cross(te1);
    if (!axisOverlap(axis[8], p1, e1, x1, y1, z1, v0, v1, v2, min0[8], max0[8], min1[8], max1[8])) return ip;
    axis[9] = y1.cross(te2);
    if (!axisOverlap(axis[9], p1, e1, x1, y1, z1, v0, v1, v2, min0[9], max0[9], min1[9], max1[9])) return ip;

    axis[10] = z1.cross(te0);
    if (!axisOverlap(axis[10], p1, e1, x1, y1, z1, v0, v1, v2, min0[10], max0[10], min1[10], max1[10])) return ip;
    axis[11] = z1.cross(te1);
    if (!axisOverlap(axis[11], p1, e1, x1, y1, z1, v0, v1, v2, min0[11], max0[11], min1[11], max1[11])) return ip;
    axis[12] = z1.cross(te2);
    if (!axisOverlap(axis[12], p1, e1, x1, y1, z1, v0, v1, v2, min0[12], max0[12], min1[12], max1[12])) return ip;

    float depth = 1000000;

    for (unsigned int i=0; i<13; i++)
    {
        float min = min1[i] > min0[i] ? min1[i] : min0[i];
        float max = max1[i] < max0[i] ? max1[i] : max0[i];

        float d = max-min;
        float l = axis[i].length();

        if (l < 0.000001f)
        {
            continue;
        }

        d /= l;

        if (d < depth)
        {
            depth = d;
        }
    }

    ip.setType(wizIntersectionPoint::POINT_INTERSECTION);
    ip.setDistance(depth);
    ip.setPoint(p1.add(ip.getNormal().mul(depth)));
    ip.setNormal(n);

    /*wizVector3 diff = (v0.add(v1).add(v2)).mul(1/3.0f);

    if (diff.dot(ip.getNormal())>0)
    {
        ip.setNormal(ip.getNormal().mul(-1));
    }*/

    return ip;
}

wizIntersectionPoint wizBoundingBox::getIntersectTriangle(wizBoundingBox b1, wizVector3 center, GLfloat* vertexBuffer, GLushort* indexBuffer, unsigned int idx)
{
    wizVector3 p1 = b1.getCenter().add(center);
    wizVector3 e1 = (b1.getMaximum().sub(b1.getMinimum())).mul(0.5f);
    wizVector3 x1(1, 0, 0);
    wizVector3 y1(0, 1, 0);
    wizVector3 z1(0, 0, 1);

    unsigned short a = indexBuffer[idx*3];
    unsigned short b = indexBuffer[idx*3+1];
    unsigned short c = indexBuffer[idx*3+2];

    wizVector3 v0(vertexBuffer[a*3]-p1.getX(), vertexBuffer[a*3+1]-p1.getY(), vertexBuffer[a*3+2]-p1.getZ());
    wizVector3 v1(vertexBuffer[b*3]-p1.getX(), vertexBuffer[b*3+1]-p1.getY(), vertexBuffer[b*3+2]-p1.getZ());
    wizVector3 v2(vertexBuffer[c*3]-p1.getX(), vertexBuffer[c*3+1]-p1.getY(), vertexBuffer[c*3+2]-p1.getZ());

    p1 = wizVector3(0, 0, 0);

    wizVector3 te0 = v1.sub(v0);
    wizVector3 te1 = v2.sub(v1);
    wizVector3 te2 = v0.sub(v2);
    wizVector3 n = te0.cross(te1).normalize();

    wizVector3 axis[13];
    float min0[13];
    float max0[13];
    float min1[13];
    float max1[13];

    wizIntersectionPoint ip;
    ip.setType(wizIntersectionPoint::POINT_MISS);

    axis[0] = n;
    if (!axisOverlap(axis[0], p1, e1, x1, y1, z1, v0, v1, v2, min0[0], max0[0], min1[0], max1[0])) return ip;

    axis[1] = x1;
    if (!axisOverlap(axis[1], p1, e1, x1, y1, z1, v0, v1, v2, min0[1], max0[1], min1[1], max1[1])) return ip;
    axis[2] = y1;
    if (!axisOverlap(axis[2], p1, e1, x1, y1, z1, v0, v1, v2, min0[2], max0[2], min1[2], max1[2])) return ip;
    axis[3] = z1;
    if (!axisOverlap(axis[3], p1, e1, x1, y1, z1, v0, v1, v2, min0[3], max0[3], min1[3], max1[3])) return ip;

    axis[4] = x1.cross(te0);
    if (!axisOverlap(axis[4], p1, e1, x1, y1, z1, v0, v1, v2, min0[4], max0[4], min1[4], max1[4])) return ip;
    axis[5] = x1.cross(te1);
    if (!axisOverlap(axis[5], p1, e1, x1, y1, z1, v0, v1, v2, min0[5], max0[5], min1[5], max1[5])) return ip;
    axis[6] = x1.cross(te2);
    if (!axisOverlap(axis[6], p1, e1, x1, y1, z1, v0, v1, v2, min0[6], max0[6], min1[6], max1[6])) return ip;

    axis[7] = y1.cross(te0);
    if (!axisOverlap(axis[7], p1, e1, x1, y1, z1, v0, v1, v2, min0[7], max0[7], min1[7], max1[7])) return ip;
    axis[8] = y1.cross(te1);
    if (!axisOverlap(axis[8], p1, e1, x1, y1, z1, v0, v1, v2, min0[8], max0[8], min1[8], max1[8])) return ip;
    axis[9] = y1.cross(te2);
    if (!axisOverlap(axis[9], p1, e1, x1, y1, z1, v0, v1, v2, min0[9], max0[9], min1[9], max1[9])) return ip;

    axis[10] = z1.cross(te0);
    if (!axisOverlap(axis[10], p1, e1, x1, y1, z1, v0, v1, v2, min0[10], max0[10], min1[10], max1[10])) return ip;
    axis[11] = z1.cross(te1);
    if (!axisOverlap(axis[11], p1, e1, x1, y1, z1, v0, v1, v2, min0[11], max0[11], min1[11], max1[11])) return ip;
    axis[12] = z1.cross(te2);
    if (!axisOverlap(axis[12], p1, e1, x1, y1, z1, v0, v1, v2, min0[12], max0[12], min1[12], max1[12])) return ip;

    float depth = 1000000;

    for (unsigned int i=0; i<13; i++)
    {
        float min = min1[i] > min0[i] ? min1[i] : min0[i];
        float max = max1[i] < max0[i] ? max1[i] : max0[i];

        float d = max-min;
        float l = axis[i].length();

        if (l < 0.000001f)
        {
            continue;
        }

        d /= l;

        if (d < depth)
        {
            depth = d;
        }
    }

    ip.setType(wizIntersectionPoint::POINT_INTERSECTION);
    ip.setDistance(depth);
    ip.setPoint(p1.add(ip.getNormal().mul(depth)));
    ip.setNormal(n);

    /*wizVector3 diff = (v0.add(v1).add(v2)).mul(1/3.0f);

    if (diff.dot(ip.getNormal())>0)
    {
        ip.setNormal(ip.getNormal().mul(-1));
    }*/

    return ip;
}

wizVector3 getClosestPointTriangle(wizVector3 p, wizVector3 a, wizVector3 b, wizVector3 c)
{
    wizVector3 ab = b.sub(a);
    wizVector3 ac = c.sub(a);
    wizVector3 bc = c.sub(b);

    float snom = (p.sub(a)).dot(ab);
    float sdenom = (p.sub(b)).dot(a.sub(b));
    float tnom = (p.sub(a)).dot(ac);
    float tdenom = (p.sub(c)).dot(a.sub(c));

    if (snom<=0.0f && tnom<=0.0f) return a;

    float unom = (p.sub(b)).dot(bc);
    float udenom = (p.sub(c)).dot(b.sub(c));

    if (sdenom <= 0.0f && unom <= 0.0f) return b;
    if (tdenom <= 0.0f && udenom <= 0.0f) return c;

    wizVector3 n = b.sub(a).cross(c.sub(a));
    float vc = n.dot((a.sub(p).cross(b.sub(p))));

    if (vc <= 0.0f && snom >= 0.0f && sdenom >= 0.0f)
    {
        return a.add(ab.mul(snom/(snom+sdenom)));
    }

    float va = n.dot(b.sub(p).cross(c.sub(p)));

    if (va<=0.0f && unom>=0.0f && udenom>=0.0f)
    {
        return b.add(bc.mul(unom/(unom+udenom)));
    }

    float vb = n.dot(c.sub(p).cross(a.sub(p)));

    if (vb <= 0.0f && tnom >= 0.0f && tdenom >= 0.0f)
    {
        return a.add(ac.mul(tnom/(tnom+tdenom)));
    }

    float u = va/(va+vb+vc);
    float v = vb/(va+vb+vc);
    float w = 1 - u - v;
    return a.mul(u).add(b.mul(v)).add(c.mul(w));
}

wizIntersectionPoint wizBoundingBox::getSphereIntersectTriangle(wizBoundingBox b1, wizVector3 center, GLfloat* vertexBuffer, GLushort* indexBuffer, unsigned int idx)
{
    wizIntersectionPoint ip;
    ip.setType(wizIntersectionPoint::POINT_MISS);

    unsigned short a = indexBuffer[idx*3];
    unsigned short b = indexBuffer[idx*3+1];
    unsigned short c = indexBuffer[idx*3+2];

    wizVector3 v0(vertexBuffer[a*3], vertexBuffer[a*3+1], vertexBuffer[a*3+2]);
    wizVector3 v1(vertexBuffer[b*3], vertexBuffer[b*3+1], vertexBuffer[b*3+2]);
    wizVector3 v2(vertexBuffer[c*3], vertexBuffer[c*3+1], vertexBuffer[c*3+2]);

    wizVector3 bc = b1.getCenter().add(center);
    wizVector3 p = getClosestPointTriangle(bc, v0, v1, v2);
    wizVector3 v = p.sub(bc);

    float d2 = v.dot(v);
    float r = fabs(b1.getMaximum().getX() - b1.getCenter().getX());

    if (d2 <=  r * r)
    {
        ip.setType(wizIntersectionPoint::POINT_INTERSECTION);
        ip.setDistance(sqrt(d2));
        ip.setPoint(p);

        wizVector3 te0 = v1.sub(v0);
        wizVector3 te1 = v2.sub(v1);
        wizVector3 te2 = v0.sub(v2);
        wizVector3 n = te0.cross(te1).normalize();

        ip.setNormal(n);
    }

    return ip;
}

wizVector3 getClosestPointAABB(wizVector3 p, wizBoundingBox b)
{
    wizVector3 q = p;
    wizVector3 min = b.getMinimum();
    wizVector3 max = b.getMaximum();

    if (q.getX()<min.getX()) q.setX(min.getX());
    if (q.getX()>max.getX()) q.setX(max.getX());

    if (q.getY()<min.getY()) q.setY(min.getY());
    if (q.getY()>max.getY()) q.setY(max.getY());

    if (q.getZ()<min.getZ()) q.setZ(min.getZ());
    if (q.getZ()>max.getZ()) q.setZ(max.getZ());

    return q;
}

wizIntersectionPoint wizBoundingBox::getSphereIntersectAABB(wizBoundingBox b1, wizBoundingBox b2)
{
    wizIntersectionPoint ip;
    ip.setType(wizIntersectionPoint::POINT_MISS);

    wizVector3 q = getClosestPointAABB(b1.getCenter(), b2);

    wizVector3 v = q.sub(b1.getCenter());
    float v2 = v.dot(v);
    float r = fabs(b1.getMaximum().getX() - b1.getCenter().getX());

    if (v2 <= r * r)
    {
        ip.setType(wizIntersectionPoint::POINT_INTERSECTION);
        ip.setDistance(sqrt(v2));
        ip.setPoint(q);
        ip.setNormal(q.sub(b1.getCenter()).normalize());
    }

    return ip;
}

wizVector3 getClosestPointOBB(wizVector3 p, wizBoundingBox b, float* m1)
{
    wizVector3 e = (b.getMaximum().sub(b.getMinimum())).mul(0.5f);
    wizVector3 u1(m1[0], m1[1], m1[2]);
    wizVector3 u2(m1[4], m1[5], m1[6]);
    wizVector3 u3(m1[8], m1[9], m1[10]);

    wizVector3 d = p.sub(b.getCenter());
    wizVector3 q = b.getCenter();

    float dist = d.dot(u1);
    if (dist > e.getX()) dist = e.getX();
    if (dist < -e.getX()) dist = -e.getX();
    q = q.add(u1.mul(dist));

    dist = d.dot(u2);
    if (dist > e.getY()) dist = e.getY();
    if (dist < -e.getY()) dist = -e.getY();
    q = q.add(u2.mul(dist));

    dist = d.dot(u3);
    if (dist > e.getZ()) dist = e.getZ();
    if (dist < -e.getZ()) dist = -e.getZ();
    q = q.add(u3.mul(dist));

    return q;
}

wizIntersectionPoint wizBoundingBox::getSphereIntersectOBB(wizBoundingBox b1, wizBoundingBox b2, float* m1)
{
    wizIntersectionPoint ip;
    ip.setType(wizIntersectionPoint::POINT_MISS);

    wizVector3 q = getClosestPointAABB(b1.getCenter(), b2);

    wizVector3 v = q.sub(b1.getCenter());
    float v2 = v.dot(v);
    float r = fabs(b1.getMaximum().getX() - b1.getCenter().getX());

    if (v2 <= r * r)
    {
        ip.setType(wizIntersectionPoint::POINT_INTERSECTION);
        ip.setDistance(sqrt(v2));
        ip.setPoint(q);
        ip.setNormal(q.sub(b1.getCenter()).normalize());
    }

    return ip;
}

wizIntersectionPoint wizBoundingBox::getSphereIntersectSphere(wizBoundingBox b1, wizBoundingBox b2)
{
    wizIntersectionPoint ip;
    ip.setType(wizIntersectionPoint::POINT_MISS);


    return ip;
}

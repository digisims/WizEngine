#include "wizTriangle.h"

wizIntersectionPoint wizTriangle::getIntersectionPoint(GLfloat* _vertexBuffer, GLushort* _indexBuffer, unsigned int _idx, wizRay _ray, bool _flip)
{
    wizIntersectionPoint ip;
    ip.setType(wizIntersectionPoint::POINT_MISS);

    unsigned int a = _indexBuffer[_idx*3] * 3;
    unsigned int b = _indexBuffer[_idx*3+1] * 3;
    unsigned int c = _indexBuffer[_idx*3+2] * 3;

    if (_flip)
    {
        unsigned int tmp = a;
        a = c;
        c = tmp;
    }

    float e1x = _vertexBuffer[b] - _vertexBuffer[a];
    float e1y = _vertexBuffer[b+1] - _vertexBuffer[a+1];
    float e1z = _vertexBuffer[b+2] - _vertexBuffer[a+2];

    float e2x = _vertexBuffer[c] - _vertexBuffer[a];
    float e2y = _vertexBuffer[c+1] - _vertexBuffer[a+1];
    float e2z = _vertexBuffer[c+2] - _vertexBuffer[a+2];

    float nx = e1x * e2z - e1z * e2y;
    float ny = e1z * e2x - e1x * e2z;
    float nz = e1x * e2y - e1y * e2x;

    float g = -(_ray.getDirection().getX() * nx + _ray.getDirection().getY() * ny + _ray.getDirection().getZ() * nz);

    if (g<0.001f) return ip;

    float bx = _ray.getOrigin().getX() - _vertexBuffer[a];
    float by = _ray.getOrigin().getY() - _vertexBuffer[a+1];
    float bz = _ray.getOrigin().getZ() - _vertexBuffer[a+2];

    float l = (bx * nx + by * ny + bz * nz) / g;

    if (l >= 0.0f && l <= 1.0f)
    {
        float ux = bx * _ray.getDirection().getZ() - bz * _ray.getDirection().getY();
        float uy = bz * _ray.getDirection().getX() - bx * _ray.getDirection().getZ();
        float uz = bx * _ray.getDirection().getY() - by * _ray.getDirection().getX();

        float u1 = (e2x * ux + e2y * uy + e2z * uz) / g;
        float u2 = (-(e1x * ux + e1y * uy + e1z * uz)) / g;

        if (u1 + u2 <= 1.0f && u1 >= 0.0f && u2 >= 0.0f)
        {
            ip.setType(wizIntersectionPoint::POINT_INTERSECTION);
            ip.setPoint(_ray.getOrigin().add(_ray.getDirection().mul(l)));
            ip.setNormal(wizVector3(nx, ny, nz));
            ip.setRay(_ray);
            ip.setDistance(l);
        }
    }

    return ip;
}

wizIntersectionPoint wizTriangle::getIntersectionPoint(GLfloat* _vertexBuffer, GLushort* _indexBuffer, unsigned int _idx, wizVector3 _src, wizVector3 _dst, bool _flip)
{
    wizIntersectionPoint ip;
    ip.setType(wizIntersectionPoint::POINT_MISS);

    unsigned int _a = _indexBuffer[_idx*3] * 3;
    unsigned int _b = _indexBuffer[_idx*3+1] * 3;
    unsigned int _c = _indexBuffer[_idx*3+2] * 3;

    if (_flip)
    {
        unsigned int tmp = _a;
        _a = _c;
        _c = tmp;
    }

    wizVector3 a(_vertexBuffer[_a], _vertexBuffer[_a+1], _vertexBuffer[_a+2]);
    wizVector3 b(_vertexBuffer[_b], _vertexBuffer[_b+1], _vertexBuffer[_b+2]);
    wizVector3 c(_vertexBuffer[_c], _vertexBuffer[_c+1], _vertexBuffer[_c+2]);

    wizVector3 ab = b.sub(a);
    wizVector3 ac = c.sub(a);
    wizVector3 qp = _src.sub(_dst);

    wizVector3 n = ab.cross(ac);

    float d = qp.dot(n);
    if (d<=0.0f) return ip;

    wizVector3 ap = _src.sub(a);
    float t = ap.dot(n);
    if (t<0 || t>d) return ip;

    wizVector3 e = qp.cross(ap);
    float v = ac.dot(e);
    if (v<0 || v>d) return ip;
    float w = -ab.dot(e);
    if (w<0 || v+w > d) return ip;

    ip.setType(wizIntersectionPoint::POINT_INTERSECTION);
    ip.setNormal(n);

    float ood = 1.0f/d;
    t*=ood;
    v*=ood;
    w*=ood;
    float u = 1 - v - w;
    ip.setPoint(a.mul(u).add(b.mul(v).add(c.mul(w))));
    ip.setDistance(ip.getPoint().sub(_src).length());

    return ip;
}

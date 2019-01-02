#include "wizPhysicsBody.h"

wizVector3 wizPhysicsBody::unitRays[6] = { wizVector3(-1, 0, 0), wizVector3(1, 0, 0),
                                           wizVector3(0, -1, 0), wizVector3(0, 1, 0),
                                           wizVector3(0, 0, -1), wizVector3(0, 0, 1) };

wizPhysicsBody::wizPhysicsBody(std::string _type, wizBoundingBox* _box, wizVector3* _translation, wizVector3* _rotation, float _mass, float _elasticity, float _friction, bool _tangible)
{
    type = _type;
    translation = _translation;
    rotation = _rotation;
    angularVelocity = wizVector3();
    linearVelocity = wizVector3();
    elasticity = _elasticity;
    mass = _mass;
    friction = _friction;
    tangible = _tangible;
    platformer = false;
    shape = PHYSICS_SHAPE_OBB;
    setAxis(false, false, false);
    invInertiaTensor = new float[16];
    box = _box;
    linearDamping = 1.0f;
    angularDamping = 1.0f;
    angularScale = 36;
}

wizPhysicsBody::~wizPhysicsBody()
{
}

void wizPhysicsBody::update(float _dt)
{
    oldAngularVelocity = angularVelocity;
    oldLinearVelocity = linearVelocity;
    oldTranslation = *translation;
    oldRotation = *rotation;

    linearVelocity = linearVelocity.add(acceleration.mul(_dt));
    acceleration = wizVector3();

    linearVelocity = linearVelocity.mul(linearDamping);
    angularVelocity = angularVelocity.mul(angularDamping);

    translation->setX(translation->getX() + linearVelocity.getX() * _dt);
    translation->setY(translation->getY() + linearVelocity.getY() * _dt);
    translation->setZ(translation->getZ() + linearVelocity.getZ() * _dt);

    rotation->setX(rotation->getX() + angularVelocity.getX() * _dt);
    rotation->setY(rotation->getY() + angularVelocity.getY() * _dt);
    rotation->setZ(rotation->getZ() + angularVelocity.getZ() * _dt);
}

void wizPhysicsBody::applyForce(wizVector3 _force)
{
    if (mass > 1000)
    {
        stop();
        return;
    }

    acceleration = acceleration.add(_force.mul(1.0f/mass));
}

void wizPhysicsBody::applyImpulse(wizVector3 _force, wizVector3 _point)
{
    if (mass > 1000)
    {
        stop();
        return;
    }

    linearVelocity = linearVelocity.add(_force.mul(1.0f/mass));
    angularVelocity = angularVelocity.add(_point.sub(box->getCenter()).cross(_force).mul(invInertiaTensor).mul(angularScale));

    if (!isXFree()) angularVelocity.setX(0);
    if (!isYFree()) angularVelocity.setY(0);
    if (!isZFree()) angularVelocity.setZ(0);
}

void wizPhysicsBody::applyImpulse(wizVector3 _force)
{
    if (mass > 1000)
    {
        stop();
        return;
    }

    linearVelocity = linearVelocity.add(_force.mul(1.0f/mass));

    if (canRotate())
    {
        angularVelocity = angularVelocity.add(linearVelocity.normalize().cross(_force).mul(invInertiaTensor).mul(angularScale));

        if (!isXFree()) angularVelocity.setX(0);
        if (!isYFree()) angularVelocity.setY(0);
        if (!isZFree()) angularVelocity.setZ(0);
    }
}

std::string wizPhysicsBody::getType()
{
    return type;
}

float wizPhysicsBody::getMass()
{
    return mass;
}

float wizPhysicsBody::getFriction()
{
    return friction;
}

wizVector3* wizPhysicsBody::getTranslation()
{
    return translation;
}

wizVector3* wizPhysicsBody::getRotation()
{
    return rotation;
}

wizVector3 wizPhysicsBody::getLinearVelocity()
{
    return linearVelocity;
}

wizVector3 wizPhysicsBody::getAngularVelocity()
{
    return angularVelocity;
}

float wizPhysicsBody::getElasticity()
{
    return elasticity;
}

bool wizPhysicsBody::getTangible()
{
    return tangible;
}

void wizPhysicsBody::setLinearVelocity(wizVector3 _linear)
{
    linearVelocity = _linear;
}

void wizPhysicsBody::setAngularVelocity(wizVector3 _angular)
{
    angularVelocity = _angular;
}

void wizPhysicsBody::setTranslation(wizVector3 _translation)
{
    oldTranslation = *translation;
    translation->setX(_translation.getX());
    translation->setY(_translation.getY());
    translation->setZ(_translation.getZ());
}

void wizPhysicsBody::setRotation(wizVector3 _rotation)
{
    oldRotation = *rotation;
    rotation->setX(_rotation.getX());
    rotation->setY(_rotation.getY());
    rotation->setZ(_rotation.getZ());
}

void wizPhysicsBody::setTangible(bool _tangible)
{
    tangible = _tangible;
}

void wizPhysicsBody::rewind()
 {
    rotation->setX(oldRotation.getX());
    rotation->setY(oldRotation.getY());
    rotation->setZ(oldRotation.getZ());
    translation->setX(oldTranslation.getX());
    translation->setY(oldTranslation.getY());
    translation->setZ(oldTranslation.getZ());
}

void wizPhysicsBody::stop()
{
    linearVelocity = wizVector3();
    angularVelocity = wizVector3();
    oldLinearVelocity = wizVector3();
    oldAngularVelocity = wizVector3();
    acceleration = wizVector3();
}

void wizPhysicsBody::setPlatformControls(bool _platformer)
{
    platformer = _platformer;
}

bool wizPhysicsBody::getPlatformControls()
{
    return platformer;
}

unsigned int wizPhysicsBody::getShape()
{
    return shape;
}

void wizPhysicsBody::setShape(unsigned int _shape)
{
    shape = _shape;

    if (shape == PHYSICS_SHAPE_SPHERE)
    {
        float* tmp = new float[16];
        float r = fabs(box->getMaximum().getX() - box->getCenter().getX());

        for (unsigned int i=0; i<16; i++) tmp[i] = 0;

        tmp[0] = tmp[5] = tmp[10] = 0.4f * mass * r * r;

        for (unsigned int i=0; i<16; i++)
        {
            if (fabs(tmp[i])>0.0001f)
            {
                invInertiaTensor[i] = 1;//tmp[i]; //1 / tmp[i];
            }
            else
            {
                invInertiaTensor[i] = 0;
            }
        }

        delete[] tmp;
    }
    else
    {
        float* tmp = new float[16];
        wizVector3 dim = box->getMaximum().sub(box->getMinimum());

        for (unsigned int i=0; i<16; i++) tmp[i] = 0;

        tmp[0] = 1.0f/12.0f * mass * (dim.getY()*dim.getY()+dim.getZ()*dim.getZ());
        tmp[5] = 1.0f/12.0f * mass * (dim.getX()*dim.getX()+dim.getZ()*dim.getZ());
        tmp[10] = 1.0f/12.0f * mass * (dim.getY()*dim.getY()+dim.getX()*dim.getX());

        for (unsigned int i=0; i<16; i++)
        {
            if (fabs(tmp[i])>0.0001f)
            {
                invInertiaTensor[i] = 1;//tmp[i];// 1 / tmp[i];
            }
            else
            {
                invInertiaTensor[i] = 0;
            }
        }

        delete[] tmp;
    }
}

void collisionResponse(wizPhysicsBody* _b1, wizBoundingBox _bb1, wizPhysicsBody* _b2, wizBoundingBox _bb2, wizIntersectionPoint _point, float _scale)
{
    float ma = _b1->getMass();
    float mb = _b2->getMass();
    float cor = wizUtility::min(_b1->getElasticity(), _b2->getElasticity());
    float cof = wizUtility::min(_b1->getFriction(), _b2->getFriction());

    // assume ray-AABB intersection is sufficient approximation

    bool f1 = _b1->canRotate();
    bool f2 = _b2->canRotate();
    wizVector3 ra;
    wizVector3 rb;

    if (f1 || f2)
    {
        if (_b1->getLinearVelocity().length()>_b2->getLinearVelocity().length())
        {
            float dist = 1000000;
            wizVector3 c1 = _bb1.getCenter();

            for (unsigned int i=0; i<6; i++)
            {
                wizRay ray(c1, wizPhysicsBody::unitRays[i]);
                wizIntersectionPoint ip = wizBoundingBox::getIntersectionPoint(_bb2, ray);
                if (ip.getType()!=wizIntersectionPoint::POINT_MISS && ip.getDistance()<dist)
                {
                    dist = ip.getDistance();
                    ra = wizPhysicsBody::unitRays[i].mul(-1);
                    rb = wizPhysicsBody::unitRays[i];
                }
            }

            wizRay ray(c1, _b1->getLinearVelocity().normalize());
            wizIntersectionPoint ip = wizBoundingBox::getIntersectionPoint(_bb2, ray);
            if (ip.getType()!=wizIntersectionPoint::POINT_MISS && ip.getDistance()<dist)
            {
                dist = ip.getDistance();
                ra = ray.getDirection().mul(-1);
                rb = ray.getDirection();
            }
        }
        else
        {
            float dist = 1000000;
            wizVector3 c2 = _bb2.getCenter();

            for (unsigned int i=0; i<6; i++)
            {
                wizRay ray(c2, wizPhysicsBody::unitRays[i]);
                wizIntersectionPoint ip = wizBoundingBox::getIntersectionPoint(_bb1, ray);
                if (ip.getType()!=wizIntersectionPoint::POINT_MISS && ip.getDistance()<dist)
                {
                    dist = ip.getDistance();
                    ra = wizPhysicsBody::unitRays[i];
                    rb = wizPhysicsBody::unitRays[i].mul(-1);
                }
            }

            wizRay ray(c2, _b2->getLinearVelocity().normalize());
            wizIntersectionPoint ip = wizBoundingBox::getIntersectionPoint(_bb1, ray);
            if (ip.getType()!=wizIntersectionPoint::POINT_MISS && ip.getDistance()<dist)
            {
                dist = ip.getDistance();
                ra = ray.getDirection();
                rb = ray.getDirection().mul(-1);
            }
        }
    }

    wizVector3 n = _point.getNormal();

    wizVector3 tv1 = _b1->getLinearVelocity().add(_b1->getAngularVelocity().cross(ra));
    wizVector3 tv2 = _b2->getLinearVelocity().add(_b2->getAngularVelocity().cross(rb));

    wizVector3 relativeVelocity = tv1.sub(tv2);

    float k = 1.0f/ma + 1.0f/mb + (ra.cross(n).mul(_b1->getInverseInertiaTensor()).cross(ra).add(rb.cross(n).mul(_b2->getInverseInertiaTensor()).cross(rb))).dot(n);
    float j = -(1+cor)*relativeVelocity.dot(n) / k;

    if (ma<1000 && mb<1000)
    {
        wizVector3 p = *_b1->getTranslation();
        wizVector3 v = n;

        _b1->getTranslation()->setX(p.getX() + v.getX() * _scale);
        _b1->getTranslation()->setY(p.getY() + v.getY() * _scale);
        _b1->getTranslation()->setZ(p.getZ() + v.getZ() * _scale);

        p = *_b2->getTranslation();
        v = n;

        _b2->getTranslation()->setX(p.getX() - v.getX() * _scale);
        _b2->getTranslation()->setY(p.getY() - v.getY() * _scale);
        _b2->getTranslation()->setZ(p.getZ() - v.getZ() * _scale);
    }
    else if (ma<1000)
    {
        wizVector3 p = *_b1->getTranslation();
        wizVector3 v = n;

        _b1->getTranslation()->setX(p.getX() + v.getX() * _scale);
        _b1->getTranslation()->setY(p.getY() + v.getY() * _scale);
        _b1->getTranslation()->setZ(p.getZ() + v.getZ() * _scale);
    }
    else if (mb<1000)
    {
        wizVector3 p = *_b2->getTranslation();
        wizVector3 v = n;

        _b2->getTranslation()->setX(p.getX() - v.getX() * _scale);
        _b2->getTranslation()->setY(p.getY() - v.getY() * _scale);
        _b2->getTranslation()->setZ(p.getZ() - v.getZ() * _scale);
    }

    if ((_b1->getPlatformControls() || _b2->getPlatformControls()) && n.getY()>0 && fabs(n.getY())>fabs(n.getX()) && fabs(n.getY())>fabs(n.getZ()))
    {
        float l1 = _b1->getLinearVelocity().length();
        float l2 = _b2->getLinearVelocity().length();

        if (l1>l2)
        {
            mb = 10000;
        }
        else
        {
            ma = 10000;
        }
    }

    if (ma<1000 && mb<1000)
    {
        if (f1)
            _b1->applyImpulse(n.mul(j), _point.getPoint());
        else
            _b1->applyImpulse(n.mul(j));

        if (f2)
            _b2->applyImpulse(n.mul(-j), _point.getPoint());
        else
            _b2->applyImpulse(n.mul(-j));
    }
    else if (ma<1000)
    {
        cof = _b2->getFriction();
        wizVector3 lv = _b1->getLinearVelocity();
        float nl = n.dot(lv);
        wizVector3 vn = n.mul(nl);
        wizVector3 vt = lv.sub(vn);
        wizVector3 v = vt.sub(vn.mul(cor));
        _b1->setLinearVelocity(v.mul(cof));
        if (f1)
        {
            wizVector3 av = v.mul(-cof*_b1->getAngularScale());
            //wizVector3 av = v.normalize().cross(n).mul(_b1->getInverseInertiaTensor()).mul(-v.length()*cof*_b1->getAngularScale());

            if (!_b1->isXFree()) av.setX(0);
            if (!_b1->isYFree()) av.setY(0);
            if (!_b1->isZFree()) av.setZ(0);

            _b1->setAngularVelocity(av);
        }
    }
    else if (mb<1000)
    {
        cof = _b1->getFriction();
        wizVector3 lv = _b2->getLinearVelocity();
        float nl = n.dot(lv);
        wizVector3 vn = n.mul(nl);
        wizVector3 vt = lv.sub(vn);
        wizVector3 v = vt.sub(vn.mul(cor));
        _b2->setLinearVelocity(v.mul(cof));
        if (f2)
        {
            wizVector3 av = v.mul(-cof*_b2->getAngularScale());
            //wizVector3 av = v.normalize().cross(n).mul(_b2->getInverseInertiaTensor()).mul(-v.length()*cof*_b2->getAngularScale());

            if (!_b2->isXFree()) av.setX(0);
            if (!_b2->isYFree()) av.setY(0);
            if (!_b2->isZFree()) av.setZ(0);

            _b2->setAngularVelocity(av);
        }
    }
}

bool wizPhysicsBody::isXFree()
{
    return freeAxis.getX() > 0;
}

bool wizPhysicsBody::isYFree()
{
    return freeAxis.getY() > 0;
}

bool wizPhysicsBody::isZFree()
{
    return freeAxis.getZ() > 0;
}

void wizPhysicsBody::setAxis(bool _x, bool _y, bool _z)
{
    freeAxis.setX(_x ? 1 : -1);
    freeAxis.setY(_y ? 1 : -1);
    freeAxis.setZ(_z ? 1 : -1);
}

bool wizPhysicsBody::canRotate()
{
    return freeAxis.getX()>0 || freeAxis.getY()>0 || freeAxis.getZ()>0;
}

float* wizPhysicsBody::getInverseInertiaTensor()
{
    return invInertiaTensor;
}

float wizPhysicsBody::getLinearDamping()
{
    return linearDamping;
}

float wizPhysicsBody::getAngularDamping()
{
    return angularDamping;
}

float wizPhysicsBody::getAngularScale()
{
    return angularScale;
}

void wizPhysicsBody::setLinearDamping(float _damping)
{
    linearDamping = _damping;
}

void wizPhysicsBody::setAngularDamping(float _damping)
{
    angularDamping = _damping;
}

void wizPhysicsBody::setAngularScale(float _scale)
{
    angularScale = _scale;
}

void wizPhysicsBody::orient(wizVector3 _n)
{

}

#include "wizMeshEntity.h"

wizMeshEntity::wizMeshEntity()
{
    frame = 0;
    transformed = false;
    visible = true;
    precalcTransformation = false;
    rotation = wizVector3(0, 0, 0);
    scale = wizVector3(1, 1, 1);
    translation = wizVector3(0, 0, 0);
    tmpMatrix = new float[16];
    transformationMatrix = new float[16];
    invTransformationMatrix = new float[16];

    for (unsigned int i=0; i<16; i++)
    {
        transformationMatrix[i] = 0;
        invTransformationMatrix[i] = 0;
    }

    transformationMatrix[0] = invTransformationMatrix[0] = transformationMatrix[5] = invTransformationMatrix[5] = transformationMatrix[10] = invTransformationMatrix[10] = 1;
}

wizMeshEntity::~wizMeshEntity()
{
    if (tmpMatrix!=NULL) delete[] tmpMatrix;
    if (transformationMatrix!=NULL) delete[] transformationMatrix;
    if (invTransformationMatrix!=NULL) delete[] invTransformationMatrix;
}

std::string wizMeshEntity::getID()
{
    return mesh + "_" + animation + "_" + wizUtility::intToString(frame) + "" + wizUtility::intToString((int)(time*1000));
}

void wizMeshEntity::setRotation(wizVector3 _rotation)
{
    precalcTransformation = false;
    transformed = true;
    rotation = _rotation;
    update();
}

void wizMeshEntity::setScale(wizVector3 _scale)
{
    precalcTransformation = false;
    transformed = true;
    scale = _scale;
    update();
}

void wizMeshEntity::setTranslation(wizVector3 _translation)
{
    precalcTransformation = false;
    transformed = true;
    translation = _translation;
    update();
}

void wizMeshEntity::setTransformation(float* _matrix)
{
    precalcTransformation = true;
    transformationMatrix = _matrix;
    wizMatrix::invert(transformationMatrix, invTransformationMatrix);
}

void wizMeshEntity::setVisible(bool _visible)
{
    visible = _visible;
}

bool wizMeshEntity::getTransformed()
{
    return transformed;
}

wizVector3 wizMeshEntity::getRotation()
{
    return rotation;
}

wizVector3 wizMeshEntity::getScale()
{
    return scale;
}

wizVector3 wizMeshEntity::getTranslation()
{
    return translation;
}

bool wizMeshEntity::getVisible()
{
    return visible;
}

void wizMeshEntity::update(float _dt)
{
    time += _dt;
    wizMeshFrame* frameObject = getFrameObject();

    if (time >= frameObject->getTime())
    {
        time -= frameObject->getTime();
        frame++;
        wizMeshAnimation* animationObject = wizMeshManager::getMesh(mesh)->getAnimation(animation);
        if (frame > animationObject->getFrameCount()-1)
        {
            frame = animationObject->getLoopable() ? 0 : animationObject->getFrameCount()-1;
        }

        updateBoundingBox();
    }
}

void wizMeshEntity::update()
{
    glMatrixMode(GL_MODELVIEW_MATRIX);
    glLoadIdentity();
    applyTransformations();
    glGetFloatv(GL_MODELVIEW_MATRIX, transformationMatrix);
    undoTransformations();

    wizMatrix::invert(transformationMatrix, invTransformationMatrix);

    updateBoundingBox();
}

void wizMeshEntity::updateBoundingBox()
{
    wizMeshFrame* frame = getFrameObject();

    if (frame!=NULL)
    {
        bbox = frame->getBoundingBox().mul(transformationMatrix);
    }
}

wizVector3 wizMeshEntity::calculateDirection()
{
    glPushMatrix();
    glLoadIdentity();
    glRotatef(rotation.getZ(), 0, 0, 1);
    glRotatef(rotation.getY(), 0, 1, 0);
    glRotatef(rotation.getX(), 1, 0, 0);
    glGetFloatv(GL_MODELVIEW_MATRIX, tmpMatrix);
    glPopMatrix();

    return wizVector3(tmpMatrix[2], tmpMatrix[6], tmpMatrix[10]);
}

void wizMeshEntity::applyTransformations()
{
    glPushMatrix();
    if (precalcTransformation)
    {
        glMultMatrixf(transformationMatrix);
    }
    else
    {
        glTranslatef(translation.getX(), translation.getY(), translation.getZ());
        glRotatef(rotation.getZ(), 0, 0, 1);
        glRotatef(rotation.getY(), 0, 1, 0);
        glRotatef(rotation.getX(), 1, 0, 0);
        glScalef(scale.getX(), scale.getY(), scale.getZ());
    }
}

void wizMeshEntity::undoTransformations()
{
    glPopMatrix();
}

void wizMeshEntity::prepareVertexBuffer()
{
    wizMeshFrame* frame = getFrameObject();
    wizMeshFrame* nextFrame = getNextFrameObject();

    if (nextFrame!=NULL)
    {
        glVertexPointer(3, GL_FLOAT, 0, frame->getAnimatedVertexBuffer(nextFrame->getVertexBuffer(), time));
    }
    else
    {
        glVertexPointer(3, GL_FLOAT, 0, frame->getVertexBuffer());
    }
}

bool wizMeshEntity::isAnimating()
{
    wizMeshAnimation* animationObject = wizMeshManager::getMesh(mesh)->getAnimation(animation);

    return animationObject->getLoopable() || frame < animationObject->getFrameCount() - 1;
}

GLfloat* wizMeshEntity::getVertexBuffer()
{
    wizMeshFrame* frame = getFrameObject();
    wizMeshFrame* nextFrame = getNextFrameObject();

    if (nextFrame!=NULL)
    {
        return frame->getAnimatedVertexBuffer(nextFrame->getVertexBuffer(), time);
    }
    else
    {
        return frame->getVertexBuffer();
    }
}

void wizMeshEntity::prepareColourBuffer()
{
    wizMesh* meshObject = wizMeshManager::getMesh(mesh);

    glColorPointer(4, GL_UNSIGNED_BYTE, 0, meshObject->getColourBuffer());
}

void wizMeshEntity::prepareTextureBuffer(int _textures)
{
    wizMesh* meshObject = wizMeshManager::getMesh(mesh);

    int maxTextures = meshObject->getTextures();
    if (_textures == -1) _textures = maxTextures;

    _textures = 1;

    for (int i=0; i<_textures; i++)
    {
        #ifndef WIN32
        int j = i%maxTextures;
        glActiveTexture(GL_TEXTURE0+j);
        glClientActiveTexture(GL_TEXTURE0 + j);
        #endif
        glTexCoordPointer(2, GL_FLOAT, 0, meshObject->getTextureBuffer()[j]);
    }
}

void wizMeshEntity::render()
{
    applyTransformations();

    wizMesh* meshObject = wizMeshManager::getMesh(mesh);

	glDrawElements(GL_TRIANGLES, meshObject->getTriangles()*3, GL_UNSIGNED_SHORT, meshObject->getIndexBuffer());

	undoTransformations();
}

void wizMeshEntity::setMaterial(std::string _material)
{
    material = _material;
}

void wizMeshEntity::setMesh(std::string _mesh)
{
    mesh = _mesh;
}

void wizMeshEntity::setAnimation(std::string _animation)
{
    animation = _animation;
    updateBoundingBox();
}

void wizMeshEntity::setFrame(int _frame)
{
    frame = _frame;
    updateBoundingBox();
}

std::string wizMeshEntity::getMaterial()
{
    return material;
}

std::string wizMeshEntity::getMesh()
{
    return mesh;
}

std::string wizMeshEntity::getAnimation()
{
    return animation;
}

int wizMeshEntity::getFrame()
{
    return frame;
}

float* wizMeshEntity::getTransformation()
{
    return transformationMatrix;
}

float* wizMeshEntity::getInverseTransformation()
{
    return invTransformationMatrix;
}

void wizMeshEntity::initialize()
{

}

wizMesh* wizMeshEntity::getMeshObject()
{
    return wizMeshManager::getMesh(mesh);
}

wizMeshFrame* wizMeshEntity::getFrameObject()
{
    return wizMeshManager::getMesh(mesh)->getAnimation(animation)->getFrame(frame);
}

wizMeshFrame* wizMeshEntity::getNextFrameObject()
{
    wizMeshAnimation* animationObject = wizMeshManager::getMesh(mesh)->getAnimation(animation);

    if (animationObject->getFrameCount()<2 || (!animationObject->getLoopable() && frame >= animationObject->getFrameCount() - 1))
    {
        return NULL;
    }
    else
    {
        int nextFrame = (frame+1)%animationObject->getFrameCount();
        return animationObject->getFrame(nextFrame);
    }
}

wizVector3 wizMeshEntity::getUp()
{
    return wizVector3(transformationMatrix[1], transformationMatrix[5], transformationMatrix[9]);
}

wizVector3 wizMeshEntity::getDirection()
{
    return wizVector3(transformationMatrix[2], transformationMatrix[6], transformationMatrix[10]);
}

wizVector3 wizMeshEntity::getRight()
{
    return wizVector3(transformationMatrix[0], transformationMatrix[4], transformationMatrix[8]);
}

void wizMeshEntity::setLocation(wizVector3 _location)
{
    transformationMatrix[12] = _location.getX();
    transformationMatrix[13] = _location.getY();
    transformationMatrix[14] = _location.getZ();
}

void wizMeshEntity::setUp(wizVector3 _up)
{
    transformationMatrix[1] = _up.getX();
    transformationMatrix[5] = _up.getY();
    transformationMatrix[9] = _up.getZ();
}

void wizMeshEntity::setDirection(wizVector3 _direction)
{
    transformationMatrix[2] = _direction.getX();
    transformationMatrix[6] = _direction.getY();
    transformationMatrix[10] = _direction.getZ();
}

void wizMeshEntity::setRight(wizVector3 _right)
{
    transformationMatrix[0] = _right.getX();
    transformationMatrix[4] = _right.getY();
    transformationMatrix[8] = _right.getZ();
}

wizBoundingBox wizMeshEntity::getBoundingBox()
{
    return bbox;
}

wizPhysicsBody* wizMeshEntity::getPhysicsBody()
{
    return physicsBody;
}

void wizMeshEntity::createPhysicsBody(std::string _type, float _mass, float _elasticity, float _friction, bool _tangible)
{
    physicsBody = new wizPhysicsBody(_type, &bbox, &translation, &rotation, _mass, _elasticity, _friction, _tangible);
}

bool wizMeshEntity::doesOBBIntersect(wizMeshEntity* _entity)
{
    return wizBoundingBox::doesIntersectOBB(getFrameObject()->getBoundingBox(), transformationMatrix, _entity->getFrameObject()->getBoundingBox(), _entity->getTransformation());
}

wizIntersectionPoint wizMeshEntity::getIntersectOBB(wizMeshEntity* _entity)
{
    return wizBoundingBox::getIntersectOBB(getFrameObject()->getBoundingBox(), transformationMatrix, _entity->getFrameObject()->getBoundingBox(), _entity->getTransformation());
}

bool wizMeshEntity::doesMeshIntersect(wizMeshEntity* _entity)
{
    wizMesh* mesh = _entity->getMeshObject();
    wizMeshFrame* frame = _entity->getFrameObject();
    unsigned int triangles = mesh->getTriangles();
    wizBoundingBox box = getFrameObject()->getBoundingBox();

    for (unsigned int i=0; i<triangles; i++)
    {
        if (wizBoundingBox::doesIntersectTriangle(box, transformationMatrix, frame->getVertexBuffer(), mesh->getIndexBuffer(), i))
        {
            return true;
        }
    }

    return false;
}

wizIntersectionPoint wizMeshEntity::getIntersectMesh(wizMeshEntity* _entity)
{
    wizIntersectionPoint ip;
    ip.setType(wizIntersectionPoint::POINT_MISS);
    ip.setDistance(1000000);

    wizMesh* mesh = _entity->getMeshObject();
    wizMeshFrame* frame = _entity->getFrameObject();
    unsigned int triangles = mesh->getTriangles();

    wizBoundingBox box = getFrameObject()->getBoundingBox();

    if (getPhysicsBody()->getShape() == PHYSICS_SHAPE_OBB)
    {
        for (unsigned int i=0; i<triangles; i++)
        {
            wizIntersectionPoint tmp;
            tmp.setType(wizIntersectionPoint::POINT_MISS);
            tmp = wizBoundingBox::getIntersectTriangle(box, transformationMatrix, frame->getVertexBuffer(), mesh->getIndexBuffer(), i);

            if (tmp.getType()!=wizIntersectionPoint::POINT_MISS && tmp.getDistance() < ip.getDistance())
            {
                ip = tmp;
            }
        }
    }
    else if (getPhysicsBody()->getShape() == PHYSICS_SHAPE_AABB)
    {
        for (unsigned int i=0; i<triangles; i++)
        {
            wizIntersectionPoint tmp;
            tmp.setType(wizIntersectionPoint::POINT_MISS);
            tmp = wizBoundingBox::getIntersectTriangle(box, getTranslation(), frame->getVertexBuffer(), mesh->getIndexBuffer(), i);

            if (tmp.getType()!=wizIntersectionPoint::POINT_MISS && tmp.getDistance() < ip.getDistance())
            {
                ip = tmp;
            }
        }
    }
    else if (getPhysicsBody()->getShape() == PHYSICS_SHAPE_SPHERE)
    {
        for (unsigned int i=0; i<triangles; i++)
        {
            wizIntersectionPoint tmp;
            tmp.setType(wizIntersectionPoint::POINT_MISS);
            tmp = wizBoundingBox::getSphereIntersectTriangle(box, getTranslation(), frame->getVertexBuffer(), mesh->getIndexBuffer(), i);

            if (tmp.getType()!=wizIntersectionPoint::POINT_MISS && tmp.getDistance() < ip.getDistance())
            {
                ip = tmp;
            }
        }
    }

    return ip;
}

void wizMeshEntity::addPhysicsJoint(wizPhysicsJoint* _joint)
{
    physicsJoints.push_back(_joint);
}

std::vector<wizPhysicsJoint*> wizMeshEntity::getPhysicsJoints()
{
    return physicsJoints;
}

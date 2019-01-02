#ifndef WIZMESHENTITY_H
#define WIZMESHENTITY_H

#include "wizGameEntity.h"
#include "wizBoundingBox.h"
#include "wizVector3.h"
#include "wizGame.h"
#include "wizRay.h"
#include "wizMeshFrame.h"
#include "wizMeshManager.h"
#include "wizIntersectionPoint.h"
#include "wizTriangle.h"
#include "wizMatrix.h"
#include "wizPhysicsBody.h"
#include "wizPhysicsJoint.h"
#include "SDL.h"
#include "DGE_Frame.h"
#include "DGE_Display.h"

#include <cstdlib>
#include <string>
#include <fstream>

class wizMeshEntity : public wizGameEntity
{
    public:

    wizMeshEntity();
    virtual ~wizMeshEntity();

    std::string getID();

    void setRotation(wizVector3 _rotation);
    void setScale(wizVector3 _scale);
    void setTranslation(wizVector3 _translation);
    void setTransformation(float* _matrix);
    wizVector3 getRotation();
    wizVector3 getScale();
    wizVector3 getTranslation();
    float* getTransformation();
    float* getInverseTransformation();

    void applyTransformations();
    void undoTransformations();

    void prepareVertexBuffer();
    void prepareColourBuffer();
    void prepareTextureBuffer(int _textures);
    void render();

    void setMaterial(std::string _material);
    void setMesh(std::string _mesh);
    void setAnimation(std::string _animation);
    void setFrame(int _frame);
    void setVisible(bool _visible);
    std::string getMaterial();
    std::string getMesh();
    std::string getAnimation();
    int getFrame();
    bool getTransformed();
    bool getVisible();

    bool isAnimating();

    void createPhysicsBody(std::string _type, float _mass, float _elasticity, float _friction, bool _tangible);
    wizPhysicsBody* getPhysicsBody();

    void addPhysicsJoint(wizPhysicsJoint* _joint);
    std::vector<wizPhysicsJoint*> getPhysicsJoints();

    wizMesh* getMeshObject();
    wizMeshFrame* getFrameObject();
    wizMeshFrame* getNextFrameObject();
    wizBoundingBox getBoundingBox();
    GLfloat* getVertexBuffer();

    void update();
    void update(float _dt);
    void updateBoundingBox();

    wizVector3 calculateDirection();

    wizVector3 getUp();
    wizVector3 getDirection();
    wizVector3 getRight();
    void setUp(wizVector3 _up);
    void setDirection(wizVector3 _direction);
    void setRight(wizVector3 _right);
    void setLocation(wizVector3 _location);

    bool doesOBBIntersect(wizMeshEntity* _entity);
    wizIntersectionPoint getIntersectOBB(wizMeshEntity* _entity);
    bool doesMeshIntersect(wizMeshEntity* _entity);
    wizIntersectionPoint getIntersectMesh(wizMeshEntity* _entity);

    protected:

    void initialize();

    std::string material;
    std::string mesh;
    std::string animation;
    int frame;
    bool precalcTransformation;
    bool visible;
    wizVector3 scale;
    wizVector3 translation;
    wizVector3 rotation;
    wizBoundingBox bbox;
    wizPhysicsBody* physicsBody;
    std::vector<wizPhysicsJoint*> physicsJoints;
    bool transformed;
    float* transformationMatrix;
    float* invTransformationMatrix;
    float* tmpMatrix;
    float time;
};

#endif // WIZMESHENTITY_H


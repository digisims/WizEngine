#ifndef WIZSPRITEENTITY_H
#define WIZSPRITEENTITY_H

#include "wizGameEntity.h"
#include "wizVector2.h"
#include "wizGame.h"
#include "wizSpriteFrame.h"
#include "wizSpriteSheetManager.h"
#include "SDL.h"
#include "DGE_Frame.h"
#include "DGE_Display.h"

#include <cstdlib>
#include <string>
#include <fstream>

class wizSpriteEntity : public wizGameEntity
{
    public:

    wizSpriteEntity();
    virtual ~wizSpriteEntity();

    std::string getID();

    void setAngle(float _angle);
    void setSize(wizVector2 _size);
    void setPosition(wizVector2 _position);
    float getAngle();
    wizVector2 getSize();
    wizVector2 getPosition();

    void update(float _dt);

    void render();

    void setSheet(std::string _sheet);
    void setSprite(std::string _sprite);
    void setAnimation(std::string _animation);
    void setFrame(int _frame);
    std::string getSheet();
    std::string getSprite();
    std::string getAnimation();
    int getFrame();

    void setVertexBuffer(GLshort* _vertexBuffer);
    void setTextureBuffer(GLfloat* _textureBuffer);
    void setColourBuffer(GLubyte* _colourBuffer);
    int getVertices();
    GLshort* getTransformedVertexBuffer();
    GLshort* getVertexBuffer();
    GLfloat* getTextureBuffer();
    GLubyte* getColourBuffer();

    bool needsUpdate();
    void transform(bool _copy = false);
    void initialize();
    void extract();
    wizSpriteFrame* getFrameObject();

    void setAlpha(float _a);

    protected:

    bool extracted;
    bool needUpdate;
    std::string sheet;
    std::string sprite;
    std::string animation;
    int frame;
    wizVector2 size;
    wizVector2 position;
    float angle;
    GLshort* transformedVertexBuffer;
    GLshort* vertexBuffer;
    GLubyte* colourBuffer;
    GLfloat* textureBuffer;
    float time;
};

#endif // WIZSPRITE_H

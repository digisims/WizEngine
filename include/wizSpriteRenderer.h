#ifndef WIZSPRITERENDERER_H
#define WIZSPRITERENDERER_H

#include "wizRenderer.h"
#include "wizTextureManager.h"
#include "wizSpriteEntity.h"
#include "wizParticle.h"

#include <vector>
#include <map>

class wizSpriteRenderer : public wizRenderer
{
    public:

    wizSpriteRenderer();
    wizSpriteRenderer(unsigned int _cache);
    ~wizSpriteRenderer();

    void applyGlobalSettings();
    void undoGlobalSettings();
    void applyLocalSettings(wizSpriteEntity* _entity);
    void undoLocalSettings(wizSpriteEntity* _entity);

    void lock();
    void unlock();

    void renderSpriteEntity(wizSpriteEntity* _entity);
    void renderSpriteList(std::vector<wizSpriteEntity*>& _list);

    void resetBatch(std::string _texture);
    void resetAll();

    void enableBlending(int _src, int _dst);
    void disableBlending();
    void enableColourKey(float _alpha = 0);
    void disableColourKey();

    protected:

    void batchSprite(std::string _texture, wizSpriteEntity* _entity);
    void compileBatch(std::string _texture);

    unsigned int cache;
    std::map<std::string, GLshort*> batchVertex;
    std::map<std::string, GLubyte*> batchColour;
    std::map<std::string, GLfloat*> batchTexture;
    std::map<std::string, GLuint> vboVertex;
    std::map<std::string, GLuint> vboColour;
    std::map<std::string, GLuint> vboTexture;
    std::map<std::string, bool> vboCompiled;
    std::map<std::string, unsigned int> batchVertices;
    std::map<std::string, unsigned int> batchColours;
    std::vector<wizSpriteEntity*> lastList;
    std::map<std::string, std::vector<wizSpriteEntity*> >::iterator j;
    bool locked;

    std::map<std::string, std::vector<wizSpriteEntity*> > batch;
};

#endif // WIZSPRITERENDERER_H

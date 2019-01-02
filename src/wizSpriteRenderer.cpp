#include "wizSpriteRenderer.h"

wizSpriteRenderer::wizSpriteRenderer()
{
    cache = 65535;
}

wizSpriteRenderer::wizSpriteRenderer(unsigned int _cache)
{
    cache = _cache;
}

wizSpriteRenderer::~wizSpriteRenderer()
{
    std::map<std::string, GLshort*>::iterator i;

    for (i=batchVertex.begin(); i!=batchVertex.end(); i++)
    {
        delete i->second;
    }

    std::map<std::string, GLubyte*>::iterator j;

    for (j=batchColour.begin(); j!=batchColour.end(); j++)
    {
        delete j->second;
    }

    std::map<std::string, GLfloat*>::iterator k;

    for (k=batchTexture.begin(); k!=batchTexture.end(); k++)
    {
        delete k->second;
    }

    std::map<std::string, GLuint>::iterator l;

    for (l=vboVertex.begin(); l!=vboVertex.end(); l++)
    {
        glDeleteBuffers(1, &l->second);
    }

    for (l=vboColour.begin(); l!=vboColour.end(); l++)
    {
        glDeleteBuffers(1, &l->second);
    }

    for (l=vboTexture.begin(); l!=vboTexture.end(); l++)
    {
        glDeleteBuffers(1, &l->second);
    }
}

void wizSpriteRenderer::applyGlobalSettings()
{
	glEnableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    #ifndef WIN32
    glActiveTexture(GL_TEXTURE0);
    glClientActiveTexture(GL_TEXTURE0);
    #endif
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//GL_CLAMP_TO_EDGE);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void wizSpriteRenderer::undoGlobalSettings()
{
	glDisableClientState(GL_VERTEX_ARRAY);

    #ifndef WIN32
    glActiveTexture(GL_TEXTURE0);
    glClientActiveTexture(GL_TEXTURE0);
    #endif
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

void wizSpriteRenderer::applyLocalSettings(wizSpriteEntity* _entity)
{
    glBindTexture(GL_TEXTURE_2D, wizTextureManager::getTexture(wizSpriteSheetManager::getSpriteSheet(_entity->getSheet())->getTexture()));

    if (_entity->getColourBuffer() != NULL)
    {
        glEnableClientState(GL_COLOR_ARRAY);
    }
}

void wizSpriteRenderer::undoLocalSettings(wizSpriteEntity* _entity)
{
    if (_entity->getColourBuffer() != NULL)
    {
        glDisableClientState(GL_COLOR_ARRAY);
    }
}

void wizSpriteRenderer::renderSpriteEntity(wizSpriteEntity* _entity)
{
    applyLocalSettings(_entity);
    _entity->render();
    undoLocalSettings(_entity);
}

void wizSpriteRenderer::resetBatch(std::string _texture)
{
    batchVertices[_texture] = 0;
    batchColours[_texture] = 0;
}

void wizSpriteRenderer::compileBatch(std::string _texture)
{
    if (vboCompiled.find(_texture)!=vboCompiled.end() && vboCompiled[_texture])
    {
        return;
    }

    vboCompiled[_texture] = true;

    vboVertex[_texture] = 0;
    vboColour[_texture] = 0;
    vboTexture[_texture] = 0;

    glGenBuffers(1, &vboVertex[_texture]);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertex[_texture]);
    glBufferData(GL_ARRAY_BUFFER, batchVertices[_texture] * 2 * sizeof(GLshort), batchVertex[_texture], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (batchColours[_texture]>0)
    {
        glGenBuffers(1, &vboColour[_texture]);
        glBindBuffer(GL_ARRAY_BUFFER, vboColour[_texture]);
        glBufferData(GL_ARRAY_BUFFER, batchColours[_texture] * 4 * sizeof(GLubyte), batchColour[_texture], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    glGenBuffers(1, &vboTexture[_texture]);
    glBindBuffer(GL_ARRAY_BUFFER, vboTexture[_texture]);
    glBufferData(GL_ARRAY_BUFFER, batchVertices[_texture] * 2 * sizeof(GLfloat), batchTexture[_texture], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void wizSpriteRenderer::batchSprite(std::string _texture, wizSpriteEntity* _entity)
{
    if (batchVertex.find(_texture)==batchVertex.end())
    {
        batchVertex[_texture] = new GLshort[cache];
        batchColour[_texture] = new GLubyte[cache];
        batchTexture[_texture] = new GLfloat[cache];

        batchVertices[_texture] = 0;
        batchColours[_texture] = 0;
    }

    memcpy((char*)&batchVertex[_texture][batchVertices[_texture]], _entity->getTransformedVertexBuffer(), 6 * 2 *sizeof(GLushort));
    memcpy((char*)&batchTexture[_texture][batchVertices[_texture]], _entity->getTextureBuffer(), 6 * 2 *sizeof(GLfloat));

    if (_entity->getColourBuffer()!=NULL)
    {
        memcpy((char*)&batchColour[_texture][batchColours[_texture]], _entity->getColourBuffer(), 6 * 4 *sizeof(GLubyte));
        batchColours[_texture] += 6 * 4;
    }

    batchVertices[_texture] += 6 * 2;
}

void wizSpriteRenderer::renderSpriteList(std::vector<wizSpriteEntity*>& _list)
{
    bool same = _list.size() == lastList.size();

    if (!locked && same)
    {
        for (unsigned int i=0; i<_list.size(); i++)
        {
            if (find(lastList.begin(), lastList.end(), _list[i])==lastList.end())
            {
                same = false;
                break;
            }
        }
    }

    if (!same)
    {
        batch.clear();

        for (unsigned int i=0; i<_list.size(); i++)
        {
            std::string texture = wizSpriteSheetManager::getSpriteSheet(_list[i]->getSheet())->getTexture();
            batch[texture].push_back(_list[i]);
        }
    }

    if (same)
    {
        for (j = batch.begin(); j!= batch.end(); j++)
        {
            std::string material = j->first;

            if (locked)
            {
                compileBatch(material);
            }

            applyLocalSettings(j->second[0]);

            for (unsigned int i=0; i<j->second.size(); i++)
            {
                if (j->second[i]->needsUpdate())
                {
                    j->second[i]->render();
                }
            }

            if (batchVertices[material]>0)
            {
                if (locked)
                {
                    glBindBuffer(GL_ARRAY_BUFFER, vboVertex[material]);
                    glVertexPointer(2, GL_SHORT, 0, NULL);

                    if (batchColours[material] > 0)
                    {
                        glBindBuffer(GL_ARRAY_BUFFER, vboColour[material]);
                        glColorPointer(4, GL_UNSIGNED_BYTE, 0, NULL);
                        glEnable(GL_BLEND);
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    }

                    glBindBuffer(GL_ARRAY_BUFFER, vboTexture[material]);
                    glTexCoordPointer(2, GL_FLOAT, 0, NULL);

                    glDrawArrays(GL_TRIANGLES, 0, batchVertices[material]/2);

                    if (batchColours[material] > 0)
                    {
                        glDisable(GL_BLEND);
                    }

                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                    glBindBuffer(GL_ARRAY_BUFFER, 0);
                }
                else
                {
                    glVertexPointer(2, GL_SHORT, 0, batchVertex[material]);

                    if (batchColours[material] > 0)
                    {
                        glColorPointer(4, GL_UNSIGNED_BYTE, 0, batchColour[material]);
                        glEnable(GL_BLEND);
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    }

                    glTexCoordPointer(2, GL_FLOAT, 0, batchTexture[material]);

                    glDrawArrays(GL_TRIANGLES, 0, batchVertices[material]/2);

                    if (batchColours[material] > 0)
                    {
                        glDisable(GL_BLEND);
                    }
                }
            }

            undoLocalSettings(j->second[0]);
        }
    }
    else
    {
        for (j = batch.begin(); j!= batch.end(); j++)
        {
            std::string material = j->first;

            resetBatch(material);

            applyLocalSettings(j->second[0]);

            for (unsigned int i=0; i<j->second.size(); i++)
            {
                if (j->second[i]->needsUpdate())
                {
                    j->second[i]->render();
                }
                else
                {
                    batchSprite(material, j->second[i]);
                }
            }

            if (batchVertices[material]>0)
            {
                glVertexPointer(2, GL_SHORT, 0, batchVertex[material]);

                if (batchColours[material] > 0)
                {
                    glColorPointer(4, GL_UNSIGNED_BYTE, 0, batchColour[material]);
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                }

                glTexCoordPointer(2, GL_FLOAT, 0, batchTexture[material]);

                glDrawArrays(GL_TRIANGLES, 0, batchVertices[material]/2);

                if (batchColours[material] > 0)
                {
                    glDisable(GL_BLEND);
                }
            }

            undoLocalSettings(j->second[0]);
        }
    }

    lastList = _list;
}

void wizSpriteRenderer::lock()
{
    locked = true;
}

void wizSpriteRenderer::unlock()
{
    locked = false;
}

void wizSpriteRenderer::enableBlending(int _src, int _dst)
{
    glEnable(GL_BLEND);
    glBlendFunc(_src, _dst);
}

void wizSpriteRenderer::disableBlending()
{
    glDisable(GL_BLEND);
}

void wizSpriteRenderer::enableColourKey(float _alpha)
{
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, _alpha);
}

void wizSpriteRenderer::disableColourKey()
{
    glDisable(GL_ALPHA_TEST);
}

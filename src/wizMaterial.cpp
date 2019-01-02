#include "wizMaterial.h"

const std::string wizMaterial::CULL_FACE_IDS[3] = { "FRONT", "BACK", "NONE" };
const int wizMaterial::CULL_FACE_VALUES[3] = { GL_FRONT, GL_BACK, 0 };

const std::string wizMaterial::CULL_DIRECTION_IDS[2] = { "CCW", "CW" };
const int wizMaterial::CULL_DIRECTION_VALUES[2] = { GL_CCW, GL_CW };

wizMaterial::wizMaterial()
{
    cullSide = GL_BACK;
    cullDirection = GL_CCW;
    polygonOffset = false;
    colourMaterial = false;
    sortOrder = 1;
    ambient = NULL;
    diffuse = NULL;
    specular = NULL;
}

wizMaterial::wizMaterial(std::string _filename)
{
    cullSide = GL_BACK;
    cullDirection = GL_CCW;
    polygonOffset = false;
    colourMaterial = false;
    sortOrder = 1;
    ambient = NULL;
    diffuse = NULL;
    specular = NULL;

    std::ifstream mat(_filename.c_str());

    while (!mat.eof())
    {
        std::string data;

        mat >> data;

        std::vector<std::string> tokens = wizUtility::splitString(data, '=');

        if (tokens.size()>0)
        {
            if (tokens[0].compare("CULL_SIDE")==0)
            {
                cullSide = wizUtility::decode(CULL_FACE_IDS, CULL_FACE_VALUES, CULL_FACE_COUNT, tokens[1]);
            }
            else if (tokens[0].compare("CULL_DIRECTION")==0)
            {
                cullDirection = wizUtility::decode(CULL_DIRECTION_IDS, CULL_DIRECTION_VALUES, CULL_DIRECTION_COUNT, tokens[1]);
            }
            else if (tokens[0].compare("POLYGON_OFFSET")==0)
            {
                std::vector<std::string> tokens2 = wizUtility::splitString(tokens[1], ',');
                polygonOffset = true;
                polygonFactor = atof(tokens2[0].c_str());
                polygonUnits = atof(tokens2[1].c_str());
            }
            else if (tokens[0].compare("AMBIENT")==0)
            {
                colourMaterial = true;
                std::vector<std::string> tokens2 = wizUtility::splitString(tokens[1], ',');
                ambient = new wizColour();
                ambient->setRed(atof(tokens2[0].c_str()));
                ambient->setGreen(atof(tokens2[1].c_str()));
                ambient->setBlue(atof(tokens2[2].c_str()));
                ambient->setAlpha(atof(tokens2[3].c_str()));
            }
            else if (tokens[0].compare("DIFFUSE")==0)
            {
                colourMaterial = true;
                std::vector<std::string> tokens2 = wizUtility::splitString(tokens[1], ',');
                diffuse = new wizColour();
                diffuse->setRed(atof(tokens2[0].c_str()));
                diffuse->setGreen(atof(tokens2[1].c_str()));
                diffuse->setBlue(atof(tokens2[2].c_str()));
                diffuse->setAlpha(atof(tokens2[3].c_str()));
            }
            else if (tokens[0].compare("SPECULAR")==0)
            {
                colourMaterial = true;
                std::vector<std::string> tokens2 = wizUtility::splitString(tokens[1], ',');
                specular = new wizColour();
                specular->setRed(atof(tokens2[0].c_str()));
                specular->setGreen(atof(tokens2[1].c_str()));
                specular->setBlue(atof(tokens2[2].c_str()));
                specular->setAlpha(atof(tokens2[3].c_str()));
            }
            else if (tokens[0].compare("SPECULARITY")==0)
            {
                specularity = atof(tokens[1].c_str());
            }
            else if (tokens[0].compare("ORDER")==0)
            {
                sortOrder = atoi(tokens[1].c_str());
            }
            else if (tokens[0].compare("STAGE")==0)
            {
                wizMaterialStage* stage = new wizMaterialStage(mat);
                addStage(stage);
            }
        }
    }

    mat.close();
}

wizMaterial::~wizMaterial()
{
    if (ambient!=NULL) delete ambient;
    if (diffuse!=NULL) delete diffuse;
    if (specular!=NULL) delete specular;

    for (unsigned int i=0; i<stageList.size(); i++)
    {
        if (stageList[i]!=NULL) delete stageList[i];
    }
}

void wizMaterial::applySettings()
{
    if (cullSide != 0)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(cullSide);
        glFrontFace(cullDirection);
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }

    glEnable(GL_DEPTH_TEST);

    if (polygonOffset)
    {
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(polygonFactor, polygonUnits);
    }

    if (colourMaterial)
    {
        glEnable(GL_COLOR_MATERIAL);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient->getArray());
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse->getArray());
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular->getArray());
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, specularity);
    }
}

void wizMaterial::undoSettings()
{
    if (polygonOffset)
    {
        glDisable(GL_POLYGON_OFFSET_FILL);
    }

    if (colourMaterial)
    {
        glDisable(GL_COLOR_MATERIAL);
    }

    glDisable(GL_DEPTH_TEST);
}

void wizMaterial::addStage(wizMaterialStage* stage)
{
    stageList.push_back(stage);
}

void wizMaterial::removeStage(int _idx)
{
    stageList.erase(stageList.begin() + _idx);
}

wizMaterialStage* wizMaterial::getStage(int _idx)
{
    return stageList[_idx];
}

std::vector<wizMaterialStage*> wizMaterial::getStages()
{
    return stageList;
}

void wizMaterial::setCullSide(unsigned int _cullSide)
{
    cullSide = _cullSide;
}

void wizMaterial::setCullDirection(unsigned int _cullDirection)
{
    cullDirection = _cullDirection;
}

void wizMaterial::setPolygonOffset(bool _polygonOffset)
{
    polygonOffset = _polygonOffset;
}

void wizMaterial::setPolygonFactor(unsigned int _polygonFactor)
{
    polygonFactor = _polygonFactor;
}

void wizMaterial::setPolygonUnits(unsigned int _polygonUnits)
{
    polygonFactor = _polygonUnits;
}

void wizMaterial::setColourMaterial(bool _colourMaterial)
{
    colourMaterial = _colourMaterial;
}

void wizMaterial::setAmbient(wizColour* _ambient)
{
    ambient = _ambient;
}

void wizMaterial::setDiffuse(wizColour* _diffuse)
{
    diffuse = _diffuse;
}

void wizMaterial::setSpecular(wizColour* _specular)
{
    specular = _specular;
}

void wizMaterial::setSpecularity(float _specularity)
{
    specularity = _specularity;
}

void wizMaterial::setSortOrder(unsigned int _sortOrder)
{
    sortOrder = _sortOrder;
}

unsigned int wizMaterial::getCullSide()
{
    return cullSide;
}

unsigned int wizMaterial::getCullDirection()
{
    return cullDirection;
}

bool wizMaterial::getPolygonOffset()
{
    return polygonOffset;
}

float wizMaterial::getPolygonFactor()
{
    return polygonFactor;
}

float wizMaterial::getPolygonUnits()
{
    return polygonUnits;
}

bool wizMaterial::getColourMaterial()
{
    return colourMaterial;
}

wizColour* wizMaterial::getAmbient()
{
    return ambient;
}

wizColour* wizMaterial::getDiffuse()
{
    return diffuse;
}

wizColour* wizMaterial::getSpecular()
{
    return specular;
}

float wizMaterial::getSpecularity()
{
    return specularity;
}

unsigned int wizMaterial::getSortOrder()
{
    return sortOrder;
}

unsigned int wizMaterial::getTextures()
{
    unsigned int textures = 0;

    for (unsigned int i=0; i<stageList.size(); i++)
    {
        if (stageList[i]->getTextures() > textures)
        {
            textures = stageList[i]->getTextures();
        }
    }

    return textures;
}

bool wizMaterial::hasColourBuffer()
{
    for (unsigned int i=0; i<stageList.size(); i++)
    {
        if (stageList[i]->getColourBuffer())
        {
            return true;
        }
    }

    return false;
}

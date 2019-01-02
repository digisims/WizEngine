#ifndef WIZMATERIAL_H
#define WIZMATERIAL_H

#include "wizMaterialStage.h"
#include "wizColour.h"
#include "wizUtility.h"
#include "SDL.h"
#include "DGE_Frame.h"
#include "DGE_Display.h"

#include <vector>
#include <fstream>

class wizMaterial
{
    public:

    static const std::string CULL_FACE_IDS[3];
    static const int CULL_FACE_VALUES[3];
    static const unsigned int CULL_FACE_COUNT = 3;

    static const std::string CULL_DIRECTION_IDS[2];
    static const int CULL_DIRECTION_VALUES[2];
    static const unsigned int CULL_DIRECTION_COUNT = 2;

    wizMaterial();
    wizMaterial(std::string _filename);
    virtual ~wizMaterial();

    void load(std::string _filename);

    void applySettings();
    void undoSettings();

    void addStage(wizMaterialStage* stage);
    void removeStage(int _idx);
    wizMaterialStage* getStage(int _idx);
    std::vector<wizMaterialStage*> getStages();

    void setCullSide(unsigned int _cullSide);
    void setCullDirection(unsigned int _cullDirection);
    void setPolygonOffset(bool _polygonOffset);
    void setPolygonFactor(unsigned int _polygonFactor);
    void setPolygonUnits(unsigned int _polygonUnits);
    void setColourMaterial(bool _colourMaterial);
    void setAmbient(wizColour* _ambient);
    void setDiffuse(wizColour* _diffuse);
    void setSpecular(wizColour* _specular);
    void setSpecularity(float _specularity);
    void setSortOrder(unsigned int _sortOrder);
    unsigned int getCullSide();
    unsigned int getCullDirection();
    bool getPolygonOffset();
    float getPolygonFactor();
    float getPolygonUnits();
    bool getColourMaterial();
    wizColour* getAmbient();
    wizColour* getDiffuse();
    wizColour* getSpecular();
    float getSpecularity();
    unsigned int getSortOrder();
    unsigned int getTextures();
    bool hasColourBuffer();

    protected:

    unsigned int cullSide;
    unsigned int cullDirection;
    bool polygonOffset;
    float polygonFactor;
    float polygonUnits;
    bool colourMaterial;
    wizColour* ambient;
    wizColour* diffuse;
    wizColour* specular;
    float specularity;
    unsigned int sortOrder;
    std::vector<wizMaterialStage*> stageList;
};

#endif // WIZMATERIAL_H

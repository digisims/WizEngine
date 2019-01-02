#ifndef WIZMATERIALSTAGE_H
#define WIZMATERIALSTAGE_H

#include "wizUtility.h"
#include "wizTextureManager.h"
#include "SDL.h"
#include "DGE_Frame.h"
#include "DGE_Display.h"

#include <vector>
#include <string>
#include <fstream>

class wizMaterialStage
{
    public:

    static const std::string CLAMPMODE_IDS[2];
    static const int CLAMPMODE_VALUES[2];
    static const unsigned int CLAMPMODE_COUNT = 2;

    static const std::string BLENDFUNC_IDS[11];
    static const int BLENDFUNC_VALUES[11];
    static const unsigned int BLENDFUNC_COUNT = 11;

    static const std::string DEPTHFUNC_IDS[8];
    static const int DEPTHFUNC_VALUES[8];
    static const unsigned int DEPTHFUNC_COUNT = 8;

    static const std::string ENVMODE_IDS[6];
    static const int ENVMODE_VALUES[6];
    static const unsigned int ENVMODE_COUNT = 6;

    static const std::string SOURCE_IDS[8];
    static const int SOURCE_VALUES[8];
    static const unsigned int SOURCE_COUNT = 8;

    static const std::string OPERATION_IDS[7];
    static const int OPERATION_VALUES[7];
    static const unsigned int OPERATION_COUNT = 7;

    static const std::string OPERAND_IDS[4];
    static const int OPERAND_VALUES[4];
    static const unsigned int OPERAND_COUNT = 4;

    wizMaterialStage();
    wizMaterialStage(std::ifstream& _mat);
    virtual ~wizMaterialStage();

    void applySettings();
    void undoSettings();

    unsigned int getTextures();
    void addTexture(std::string _texture);
    void removeTexture(unsigned int _idx);
    std::string getTexture(unsigned int _idx);
    void addTextureClampModeS(unsigned int _mode);
    void removeTextureClampModeS(unsigned int _idx);
    unsigned int getTextureClampModeS(unsigned int _idx);
    void addTextureClampModeT(unsigned int _mode);
    void removeTextureClampModeT(unsigned int _idx);
    unsigned int getTextureClampModeT(unsigned int _idx);
    void addTextureEnvMode(unsigned int _mode);
    void removeTextureEnvMode(unsigned int _idx);
    unsigned int getTextureEnvMode(unsigned int _idx);
    void addCombineMode(bool _mode);
    void addCombineOperation(unsigned int _operation);
    void addCombineSource0(unsigned int _source);
    void addCombineSource1(unsigned int _source);
    void addCombineOperand0(unsigned int _operand);
    void addCombineOperand1(unsigned int _operand);
    bool getCombineMode(unsigned int _idx);
    unsigned int getCombineOperation(unsigned int _idx);
    unsigned int getCombineSource0(unsigned int _idx);
    unsigned int getCombineSource1(unsigned int _idx);
    unsigned int getCombineOperand0(unsigned int _idx);
    unsigned int getCombineOperand1(unsigned int _idx);
    void removeCombineMode(unsigned int _idx);
    void removeCombineOperation(unsigned int _idx);
    void removeCombineSource0(unsigned int _idx);
    void removeCombineSource1(unsigned int _idx);
    void removeCombineOperand0(unsigned int _idx);
    void removeCombineOperand1(unsigned int _idx);
    void setAlphaBlend(bool _alphaBlend);
    void setBlendSrcFunction(unsigned int _srcFunction);
    void setBlendDstFunction(unsigned int _dstFunction);
    void setDepthFunction(unsigned int _depthFunction);
    void setDepthWrite(bool _depthWrite);
    void setAlphaTest(bool _alphaTest);
    void setAlphaFunction(unsigned int _alphaFunction);
    void setAlphaConstant(float _alphaConstant);
    void setColourBuffer(bool _colourBuffer);
    bool getAlphaBlend();
    unsigned int getBlendSrcFunction();
    unsigned int getBlendDstFunction();
    unsigned int getDepthFunction();
    bool getAlphaTest();
    unsigned int getAlphaFunction();
    float getAlphaConstant();
    bool getColourBuffer();

    protected:

    std::vector<std::string> textureList;
    std::vector<unsigned int> textureClampModeS;
    std::vector<unsigned int> textureClampModeT;
    std::vector<unsigned int> textureEnvMode;
    std::vector<unsigned int> combineOperation;
    std::vector<bool> combineMode;
    std::vector<unsigned int> combineSource0;
    std::vector<unsigned int> combineOperand0;
    std::vector<unsigned int> combineSource1;
    std::vector<unsigned int> combineOperand1;
    bool alphaBlend;
    unsigned int blendSrcFunction;
    unsigned int blendDstFunction;
    unsigned int depthFunction;
    bool depthWrite;
    bool alphaTest;
    unsigned int alphaFunction;
    float alphaConstant;
    bool colourBuffer;
};

#endif // WIZMATERIALSTAGE_H

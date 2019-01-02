#include "wizMaterialStage.h"

const std::string wizMaterialStage::CLAMPMODE_IDS[2] = { "CLAMP", "REPEAT" };
const int wizMaterialStage::CLAMPMODE_VALUES[2] = { GL_CLAMP_TO_EDGE, GL_REPEAT };

const std::string wizMaterialStage::BLENDFUNC_IDS[11] = { "ZERO", "ONE", "SRC_COLOUR", "1-SRC_COLOUR", "DST_COLOUR", "1-DST_COLOUR", "SRC_ALPHA", "1-SRC_ALPHA", "DST_ALPHA", "1-DST_ALPHA", "SRC_ALPHA_SATURATE" };
const int wizMaterialStage::BLENDFUNC_VALUES[11] = { GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_SRC_ALPHA_SATURATE };

const std::string wizMaterialStage::DEPTHFUNC_IDS[8] = { "LESS", "LESS_OR_EQUAL", "EQUAL", "GREATER_OR_EQUAL", "GREATER", "NOT_EQUAL", "ALWAYS", "NEVER" };
const int wizMaterialStage::DEPTHFUNC_VALUES[8] = { GL_LESS, GL_LEQUAL, GL_EQUAL, GL_GEQUAL, GL_GREATER, GL_NOTEQUAL, GL_ALWAYS, GL_NEVER };

const std::string wizMaterialStage::ENVMODE_IDS[6] = { "REPLACE", "MODULATE", "DECAL", "BLEND", "ADD", "COMBINE" };
const int wizMaterialStage::ENVMODE_VALUES[6] = { GL_REPLACE, GL_MODULATE, GL_DECAL, GL_BLEND, GL_ADD, GL_COMBINE };

const std::string wizMaterialStage::SOURCE_IDS[8] = { "TEXTURE", "CONSTANT", "PRIMARY_COLOUR", "PREVIOUS", "SRC_COLOUR", "1-SRC_COLOUR", "SRC_ALPHA", "1-SRC_ALPHA" };
const int wizMaterialStage::SOURCE_VALUES[8] = { GL_TEXTURE, GL_CONSTANT, GL_PRIMARY_COLOR, GL_PREVIOUS, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA };

const std::string wizMaterialStage::OPERATION_IDS[7] = { "REPLACE", "MODULATE", "ADD", "ADD_SIGNED", "SUBTRACT", "DOT3_RGB", "DOT3_RGBA" };
const int wizMaterialStage::OPERATION_VALUES[7] = { GL_REPLACE, GL_MODULATE, GL_ADD, GL_ADD_SIGNED, GL_SUBTRACT, GL_DOT3_RGB, GL_DOT3_RGBA };

const std::string wizMaterialStage::OPERAND_IDS[4] = { "SRC_COLOUR", "1-SRC_COLOUR", "SRC_ALPHA", "1-SRC_ALPHA" };
const int wizMaterialStage::OPERAND_VALUES[4] = { GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA };

wizMaterialStage::wizMaterialStage()
{
    setAlphaBlend(false);
    setDepthWrite(true);
    setAlphaTest(false);
    setDepthFunction(GL_LEQUAL);
    setColourBuffer(false);
}

wizMaterialStage::wizMaterialStage(std::ifstream& _mat)
{
    setAlphaBlend(false);
    setDepthWrite(true);
    setAlphaTest(false);
    setDepthFunction(GL_LEQUAL);
    setColourBuffer(false);

    std::string data;
    std::vector<std::string> tokens;

    do
    {
        _mat >> data;

        tokens = wizUtility::splitString(data, '=');

        if (tokens.size()>0)
        {
            if (tokens[0].compare("TEXTURE")==0)
            {
                addTexture(tokens[1]);

                wizTextureManager::loadTexture(tokens[1]);
            }
            else if (tokens[0].compare("CLAMP_S")==0)
            {
                addTextureClampModeS(wizUtility::decode(CLAMPMODE_IDS, CLAMPMODE_VALUES, CLAMPMODE_COUNT, tokens[1]));
            }
            else if (tokens[0].compare("CLAMP_T")==0)
            {
                addTextureClampModeT(wizUtility::decode(CLAMPMODE_IDS, CLAMPMODE_VALUES, CLAMPMODE_COUNT, tokens[1]));
            }
            else if (tokens[0].compare("OPERATION")==0)
            {
                addCombineOperation(wizUtility::decode(OPERATION_IDS, OPERATION_VALUES, OPERATION_COUNT, tokens[1]));
            }
            else if (tokens[0].compare("MODE")==0)
            {
                addCombineMode(tokens[1].compare("RGB")==0 ? false : true);
            }
            else if (tokens[0].compare("ENVMODE")==0)
            {
                addTextureEnvMode(wizUtility::decode(ENVMODE_IDS, ENVMODE_VALUES, ENVMODE_COUNT, tokens[1]));
            }
            else if (tokens[0].compare("SOURCE0")==0)
            {
                addCombineSource0(wizUtility::decode(SOURCE_IDS, SOURCE_VALUES, SOURCE_COUNT, tokens[1]));
            }
            else if (tokens[0].compare("SOURCE1")==0)
            {
                addCombineSource1(wizUtility::decode(SOURCE_IDS, SOURCE_VALUES, SOURCE_COUNT, tokens[1]));
            }
            else if (tokens[0].compare("OPERAND0")==0)
            {
                addCombineOperand0(wizUtility::decode(OPERAND_IDS, OPERAND_VALUES, OPERAND_COUNT, tokens[1]));
            }
            else if (tokens[0].compare("OPERAND1")==0)
            {
                addCombineOperand1(wizUtility::decode(OPERAND_IDS, OPERAND_VALUES, OPERAND_COUNT, tokens[1]));
            }
            else if (tokens[0].compare("BLEND")==0)
            {
                setAlphaBlend(true);
                std::vector<std::string> tokens2 = wizUtility::splitString(tokens[1], ',');
                setBlendSrcFunction(wizUtility::decode(BLENDFUNC_IDS, BLENDFUNC_VALUES, BLENDFUNC_COUNT, tokens2[0]));
                setBlendDstFunction(wizUtility::decode(BLENDFUNC_IDS, BLENDFUNC_VALUES, BLENDFUNC_COUNT, tokens2[1]));
            }
            else if (tokens[0].compare("DEPTH")==0)
            {
                setDepthFunction(wizUtility::decode(DEPTHFUNC_IDS, DEPTHFUNC_VALUES, DEPTHFUNC_COUNT, tokens[1]));
            }
            else if (tokens[0].compare("DEPTH_WRITE")==0)
            {
                setDepthWrite(tokens[1].compare("ON")==0 ? true : false);
            }
            else if (tokens[0].compare("ALPHA_TEST")==0)
            {
                setAlphaTest(true);
                std::vector<std::string> tokens2 = wizUtility::splitString(tokens[1], ',');
                setAlphaFunction(wizUtility::decode(DEPTHFUNC_IDS, DEPTHFUNC_VALUES, DEPTHFUNC_COUNT, tokens2[0]));
                setAlphaConstant(atof(tokens2[1].c_str()));
            }
            else if (tokens[0].compare("COLOUR_BUFFER")==0)
            {
                setColourBuffer(tokens[1].compare("ON")==0 ? true : false);
            }
        }
    }
    while (tokens[0].compare("END")!=0);
}

wizMaterialStage::~wizMaterialStage()
{
}

void wizMaterialStage::applySettings()
{
    if (alphaBlend)
    {
        glEnable(GL_BLEND);
        glBlendFunc(blendSrcFunction, blendDstFunction);
    }
    else
    {
        glDisable(GL_BLEND);
    }

    glDepthFunc(depthFunction);
    glDepthMask(depthWrite ? GL_TRUE : GL_FALSE);

    if (alphaTest)
    {
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(alphaFunction, alphaConstant);
    }

    for (unsigned int i=0; i<textureList.size(); i++)
    {
        #ifndef WIN32
        glActiveTexture(GL_TEXTURE0+i);
        glClientActiveTexture(GL_TEXTURE0+i);
        #endif
        glEnable(GL_TEXTURE_2D);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        std::string texture = getTexture(i);
        int id = wizTextureManager::getTexture(texture);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, getTextureClampModeS(i));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, getTextureClampModeT(i));

        if (i < textureEnvMode.size())
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, getTextureEnvMode(i));

            if (getTextureEnvMode(i)==GL_COMBINE)
            {
                if (getCombineMode(i))
                {
                    glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB, getCombineOperation(i));
                    glTexEnvf(GL_TEXTURE_ENV, GL_SRC0_RGB, getCombineSource0(i));
                    glTexEnvf(GL_TEXTURE_ENV, GL_OPERAND0_RGB, getCombineOperand0(i));
                    glTexEnvf(GL_TEXTURE_ENV, GL_SRC1_RGB, getCombineSource1(i));
                    glTexEnvf(GL_TEXTURE_ENV, GL_OPERAND1_RGB, getCombineOperand1(i));
                }
                else
                {
                    glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, getCombineOperation(i));
                    glTexEnvf(GL_TEXTURE_ENV, GL_SRC0_ALPHA, getCombineSource0(i));
                    glTexEnvf(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA, getCombineOperand0(i));
                    glTexEnvf(GL_TEXTURE_ENV, GL_SRC1_ALPHA, getCombineSource1(i));
                    glTexEnvf(GL_TEXTURE_ENV, GL_OPERAND1_ALPHA, getCombineOperand1(i));
                }
            }
        }
    }

    if (colourBuffer)
    {
        glEnableClientState(GL_COLOR_ARRAY);
    }
}

void wizMaterialStage::undoSettings()
{
    if (alphaBlend)
    {
        glDisable(GL_BLEND);
    }

    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);

    if (alphaTest)
    {
        glDisable(GL_ALPHA_TEST);
    }

    for (unsigned int i=0; i<textureList.size(); i++)
    {
        #ifndef WIN32
        glActiveTexture(GL_TEXTURE0+i);
        glClientActiveTexture(GL_TEXTURE0+i);
        #endif
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glDisable(GL_TEXTURE_2D);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }

    if (colourBuffer)
    {
        glDisableClientState(GL_COLOR_ARRAY);
    }
}

unsigned int wizMaterialStage::getTextures()
{
    return textureList.size();
}

void wizMaterialStage::addTexture(std::string _texture)
{
    textureList.push_back(_texture);
}

void wizMaterialStage::removeTexture(unsigned int _idx)
{
    textureList.erase(textureList.begin() + _idx);
}

std::string wizMaterialStage::getTexture(unsigned int _idx)
{
    return textureList[_idx];
}

void wizMaterialStage::addTextureClampModeS(unsigned int _mode)
{
    textureClampModeS.push_back(_mode);
}

void wizMaterialStage::removeTextureClampModeS(unsigned int _idx)
{
    textureClampModeS.erase(textureClampModeS.begin() + _idx);
}

unsigned int wizMaterialStage::getTextureClampModeS(unsigned int _idx)
{
    return textureClampModeS[_idx];
}

void wizMaterialStage::addTextureClampModeT(unsigned int _mode)
{
    textureClampModeT.push_back(_mode);
}

void wizMaterialStage::removeTextureClampModeT(unsigned int _idx)
{
    textureClampModeT.erase(textureClampModeT.begin() + _idx);
}

unsigned int wizMaterialStage::getTextureClampModeT(unsigned int _idx)
{
    return textureClampModeT[_idx];
}

void wizMaterialStage::addTextureEnvMode(unsigned int _mode)
{
    textureEnvMode.push_back(_mode);
}

void wizMaterialStage::removeTextureEnvMode(unsigned int _idx)
{
    textureEnvMode.erase(textureEnvMode.begin()+_idx);
}

unsigned int wizMaterialStage::getTextureEnvMode(unsigned int _idx)
{
    return textureEnvMode[_idx];
}

void wizMaterialStage::addCombineMode(bool _mode)
{
   combineMode.push_back(_mode);
}

void wizMaterialStage::addCombineOperation(unsigned int _operation)
{
   combineOperation.push_back(_operation);
}

void wizMaterialStage::addCombineSource0(unsigned int _source)
{
   combineSource0.push_back(_source);
}

void wizMaterialStage::addCombineSource1(unsigned int _source)
{
   combineSource1.push_back(_source);
}

void wizMaterialStage::addCombineOperand0(unsigned int _operand)
{
    combineOperand0.push_back(_operand);
}

void wizMaterialStage::addCombineOperand1(unsigned int _operand)
{
    combineOperand1.push_back(_operand);
}

bool wizMaterialStage::getCombineMode(unsigned int _idx)
{
    return combineMode[_idx];
}

unsigned int wizMaterialStage::getCombineOperation(unsigned int _idx)
{
    return combineOperation[_idx];
}

unsigned int wizMaterialStage::getCombineSource0(unsigned int _idx)
{
    return combineSource0[_idx];
}

unsigned int wizMaterialStage::getCombineSource1(unsigned int _idx)
{
    return combineSource1[_idx];
}

unsigned int wizMaterialStage::getCombineOperand0(unsigned int _idx)
{
    return combineOperand0[_idx];
}

unsigned int wizMaterialStage::getCombineOperand1(unsigned int _idx)
{
    return combineOperand1[_idx];
}

void wizMaterialStage::removeCombineMode(unsigned int _idx)
{
   combineMode.erase(combineMode.begin()+_idx);
}

void wizMaterialStage::removeCombineSource0(unsigned int _idx)
{
   combineSource0.erase(combineSource0.begin()+_idx);
}

void wizMaterialStage::removeCombineSource1(unsigned int _idx)
{
   combineSource1.erase(combineSource1.begin()+_idx);
}

void wizMaterialStage::removeCombineOperand0(unsigned int _idx)
{
   combineOperand0.erase(combineOperand0.begin()+_idx);
}

void wizMaterialStage::removeCombineOperand1(unsigned int _idx)
{
   combineOperand1.erase(combineOperand1.begin()+_idx);
}

void wizMaterialStage::setAlphaBlend(bool _alphaBlend)
{
    alphaBlend = _alphaBlend;
}

void wizMaterialStage::setBlendSrcFunction(unsigned int _srcFunction)
{
    blendSrcFunction = _srcFunction;
}

void wizMaterialStage::setBlendDstFunction(unsigned int _dstFunction)
{
    blendDstFunction = _dstFunction;
}

void wizMaterialStage::setDepthFunction(unsigned int _depthFunction)
{
    depthFunction = _depthFunction;
}

void wizMaterialStage::setDepthWrite(bool _depthWrite)
{
    depthWrite = _depthWrite;
}

void wizMaterialStage::setAlphaTest(bool _alphaTest)
{
    alphaTest = _alphaTest;
}

void wizMaterialStage::setAlphaFunction(unsigned int _alphaFunction)
{
    alphaFunction = _alphaFunction;
}

void wizMaterialStage::setAlphaConstant(float _alphaConstant)
{
    alphaConstant = _alphaConstant;
}

void wizMaterialStage::setColourBuffer(bool _colourBuffer)
{
    colourBuffer = _colourBuffer;
}

bool wizMaterialStage::getAlphaBlend()
{
    return alphaBlend;
}

unsigned int wizMaterialStage::getBlendSrcFunction()
{
    return blendSrcFunction;
}

unsigned int wizMaterialStage::getBlendDstFunction()
{
    return blendDstFunction;
}

unsigned int wizMaterialStage::getDepthFunction()
{
    return depthFunction;
}

bool wizMaterialStage::getAlphaTest()
{
    return alphaTest;
}

unsigned int wizMaterialStage::getAlphaFunction()
{
    return alphaFunction;
}

float wizMaterialStage::getAlphaConstant()
{
    return alphaConstant;
}

bool wizMaterialStage::getColourBuffer()
{
    return colourBuffer;
}

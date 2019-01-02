#include "wizProjectiveShadowRenderer.h"

wizProjectiveShadowRenderer::wizProjectiveShadowRenderer()
{
    biasMatrix = new float[16];

    biasMatrix = {
                    0.5f, 0.0f, 0.0f, 0.0f,
                    0.0f, 0.5f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.5f, 0.0f,
                    0.5f, 0.5f, 0.5f, 1.0f
                 }
}

wizProjectiveShadowRenderer::~wizProjectiveShadowRenderer()
{
}

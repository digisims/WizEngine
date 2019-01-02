#ifndef WIZTEXTUREMANAGER_H
#define WIZTEXTUREMANAGER_H

#include "SDL.h"
#include "SDL_Image.h"
#include "DGE_Frame.h"
#include "DGE_Display.h"
#include "DGE_Render.h"
#include "DGE_SurfaceManager.h"

#include <string>
#include <map>
#include <fstream>

class wizTextureManager
{
    public:

    static void initialize();
    static void destroy();

    static int loadTexture(std::string _filename);
    static int getTexture(std::string _filename);
    static int getTextureWidth(std::string _filename);
    static int getTextureHeight(std::string _filename);
    static int createTexture(std::string _filename, unsigned int _internalFormat, unsigned int _format, unsigned int _width, unsigned int _height);
    static int updateTexture(std::string _filename, unsigned int _format, unsigned int _x, unsigned int _y, unsigned int _width, unsigned int _height);

    protected:

    static std::map<std::string, GLuint> glMap;
};

#endif // WIZTEXTUREMANAGER_H

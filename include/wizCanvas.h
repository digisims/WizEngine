#ifndef WIZCANVAS_H
#define WIZCANVAS_H

#include "SDL.h"
#include "SDL_mixer.h"
#include "DGE_Frame.h"
#include "DGE_Display.h"
#include "DGE_Render.h"
#include "DGE_SurfaceManager.h"

#include <map>
#include <string>

class wizCanvas
{
    public:

    static const int DEFAULT_FPS = 60;

    static void initialize();
    static void initialize(int _fps);
    static void destroy();

    static void update();

    protected:

    static void create(int _fps);
};

#endif // WIZCANVAS_H

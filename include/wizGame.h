#ifndef WIZCANVAS_H
#define WIZCANVAS_H

#include "SDL.h"
#include "SDL_mixer.h"
#include "DGE_Frame.h"
#include "DGE_Display.h"
#include "DGE_Render.h"
#include "DGE_SurfaceManager.h"
#include "wizInputManager.h"
#include "wizStateManager.h"
#include "wizUtility.h"
#include "wizRecording.h"
#include "wizProgress.h"

#include <map>
#include <string>
#include <fstream>
#include <vector>

class wizGame
{
    public:

    static const int DEFAULT_FPS = 60;

    static void initialize();
    static void initialize(int _fps, int _bpp);
    static void destroy();

    static void run();
    static void quit();

    static float getDelta();
    static unsigned int getTime();
    static unsigned int getFPS();
    static void setTimeout(unsigned int _timeout);
    static unsigned int getTimeout();

    protected:

    static void create(int _fps, int _bpp);

    static bool running;
    static float delta;
    static unsigned int time;
    static unsigned int targetFps;
    static unsigned int fps;
    static unsigned int lastFPS;
    static unsigned int timeout;
};

#endif // WIZCANVAS_H

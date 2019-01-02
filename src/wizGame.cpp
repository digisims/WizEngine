#include "wizGame.h"

bool wizGame::running;
float wizGame::delta;
unsigned int wizGame::targetFps;
unsigned int wizGame::fps;
unsigned int wizGame::lastFPS;
unsigned int wizGame::time = 0;
unsigned int wizGame::timeout = 0;

void wizGame::initialize()
{
    create(wizGame::DEFAULT_FPS, DGE_DISPLAY_DEFAULT_BPP);
    setTimeout(0);
}

void wizGame::initialize(int _fps, int _bpp)
{
    create(_fps, _bpp);
}

void wizGame::create(int _fps, int _bpp)
{
    g_cFrame.CreateFrame(DGE_FRAME_USE_ON, DGE_FRAME_USE_ON, DGE_FRAME_USE_ON);

    g_cFrame.SetFPS(_fps);
    targetFps = _fps;

    g_cDisplay.SetDisplay(320, 240, _bpp);
    g_cDisplay.CreateDisplay();

    g_cSurface.AttachDisplay(&g_cDisplay);

    g_cRender.AttachSurfaceManager(&g_cSurface);

    running = true;
    setTimeout(0);
}

void wizGame::destroy()
{
    wizRecording::flushRecording();

    g_cSurface.DestroySurfaceMgr();
    g_cDisplay.DestroyDisplay();
    g_cRender.DestroyRender();

    g_cFrame.CallGP2XMenu();
}

unsigned int wizGame::getTime()
{
    return time;
}

void wizGame::setTimeout(unsigned int _timeout)
{
    timeout = _timeout;
}

unsigned int wizGame::getTimeout()
{
    return timeout;
}

void wizGame::run()
{
    unsigned int total = 0;
    fps = 0;
    lastFPS = 0;
    float runningTotal = 0;
    float expected = 1000 / targetFps;
    int start = SDL_GetTicks();
    bool wasTimedout = false;

    while (running)
    {
        int current = SDL_GetTicks();

        if (timeout>0 && (current - wizInputManager::getLastUpdate())/1000>timeout)
        {
            // blank

            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            g_cDisplay.Flip();

            wasTimedout = true;

            wizInputManager::update();
        }
        else
        {
            if (wasTimedout)
            {
                wizInputManager::flush();
            }

            wasTimedout = false;

            int tmpDelta = current - start;
            runningTotal += tmpDelta;
            total += tmpDelta;
            start = current;

            wizRecording::updateTime(tmpDelta);

            if (runningTotal > expected)
            {
                wizRecording::updateFrames();

                fps++;
                runningTotal -= expected;
                delta = expected / 1000.0f;

                wizInputManager::update();
                wizStateManager::update(delta);

                g_cDisplay.Flip();

                wizRecording::update();
            }

            if (total>=1000)
            {
                total = 0;
                lastFPS = fps;
                fps=0;
            }
        }
    }
}

void wizGame::quit()
{
    running = false;
}

float wizGame::getDelta()
{
    return delta;
}

unsigned int wizGame::getFPS()
{
    return lastFPS;
}

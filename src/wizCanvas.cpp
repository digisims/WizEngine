#include "wizCanvas.h"

void wizCanvas::initialize()
{
    create(wizCanvas::DEFAULT_FPS);
}

void wizCanvas::initialize(int _fps)
{
    create(_fps);
}

void wizCanvas::create(int _fps)
{
    g_cFrame.CreateFrame(DGE_FRAME_USE_ON, DGE_FRAME_USE_ON, DGE_FRAME_USE_ON);

    g_cFrame.SetFPS(_fps);

    g_cDisplay.SetDisplay(DGE_DISPLAY_DEFAULT_WIDTH, DGE_DISPLAY_DEFAULT_HEIGHT, DGE_DISPLAY_DEFAULT_BPP);
    g_cDisplay.CreateDisplay();

    g_cSurface.AttachDisplay(&g_cDisplay);

    g_cRender.AttachSurfaceManager(&g_cSurface);
}

void wizCanvas::destroy()
{
    g_cSurface.DestroySurfaceMgr();
    g_cDisplay.DestroyDisplay();
    g_cRender.DestroyRender();
}

void wizCanvas::update()
{
    g_cDisplay.Flip();
}

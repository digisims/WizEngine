#ifndef WIZRECORDING_H
#define WIZRECORDING_H

#include "SDL.h"
#include "SDL_mixer.h"
#include "DGE_Frame.h"
#include "DGE_Display.h"
#include "DGE_Render.h"
#include "DGE_SurfaceManager.h"
#include "wizInputManager.h"
#include "wizStateManager.h"
#include "wizUtility.h"
#include "wizProgress.h"

#include <map>
#include <string>
#include <fstream>
#include <vector>

class wizRecording
{
    public:

    static char* grabScreenshot();
    static void cacheScreenshot(std::string _filename);
    static void saveScreenshot(std::string _filename);
    static void startRecording(int _skipFrames, int _maxFrames, int _maxTime);
    static void stopRecording();
    static void setRecordingFolder(std::string _folder);
    static void flushRecording();
    static void setDownsample(int _ratio);
    static void setRecordingCacheSize(int _size);
    static bool getRecording();
    static void updateTime(unsigned int _ticks);
    static void updateFrames();
    static void update();

    protected:

    static void dumpScreenshot(char* _image, std::string _filename);

    static unsigned int totalFrames;
    static unsigned int totalTime;
    static unsigned int skipFrames;
    static unsigned int recordCache;
    static int maxFrames;
    static int maxTime;
    static unsigned int recordFrames;
    static unsigned int stepRatio;
    static std::string recordFolder;
    static bool recording;
    static std::vector<char*> recordedFrames;
    static std::vector<std::string> recordedNames;
};

#endif // WIZRECORDING_H

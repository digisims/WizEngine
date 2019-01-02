#include "wizRecording.h"

unsigned int wizRecording::totalFrames = 0;
unsigned int wizRecording::skipFrames = 1;
unsigned int wizRecording::totalTime = 0;
int wizRecording::maxFrames = 0;
int wizRecording::maxTime = 0;
unsigned int wizRecording::recordFrames = 0;
std::string wizRecording::recordFolder = "./";
bool wizRecording::recording = false;
std::vector<char*> wizRecording::recordedFrames;
std::vector<std::string> wizRecording::recordedNames;
unsigned int wizRecording::stepRatio = 1;
unsigned int wizRecording::recordCache = 120;

void wizRecording::updateTime(unsigned int _ticks)
{
    totalTime += _ticks;
}

void wizRecording::updateFrames()
{
    totalFrames++;
}

void wizRecording::update()
{
    if (recording)
    {
        if (totalFrames%skipFrames==0)
        {
            cacheScreenshot("screenshot-"+wizUtility::intToString(totalFrames/skipFrames)+".raw");
            recordFrames++;
        }

        if (maxTime!=-1 && (int)totalTime > maxTime || maxFrames!=-1 && (int)recordFrames > maxFrames)
        {
            stopRecording();
        }
    }
}

char* wizRecording::grabScreenshot()
{
    glFlush();

    char* data = new char[320*240*4];
    glReadPixels(0, 0, 320, 240, GL_RGBA, GL_UNSIGNED_BYTE, data);

    if (stepRatio!=1)
    {
        char* tmp = new char[320/stepRatio*240/stepRatio*4];
        int offs = 0;

        for (unsigned int i=0; i<240; i+=stepRatio)
        {
            for (unsigned int j=0; j<320; j+=stepRatio)
            {
                int offs2 = j*4+i*320*4;
                tmp[offs++] = data[offs2++];
                tmp[offs++] = data[offs2++];
                tmp[offs++] = data[offs2++];
                tmp[offs++] = data[offs2++];
            }
        }

        delete[] data;
        data = tmp;
    }

    return data;
}

void wizRecording::cacheScreenshot(std::string _filename)
{
    recordedFrames.push_back(grabScreenshot());
    recordedNames.push_back(_filename);

    if (recordedFrames.size() > recordCache)
    {
        dumpScreenshot(recordedFrames[0], recordedNames[0]);
        recordedFrames.erase(recordedFrames.begin());
        recordedNames.erase(recordedNames.begin());
    }
}

void wizRecording::saveScreenshot(std::string _filename)
{
    char* data = wizRecording::grabScreenshot();

    dumpScreenshot(data, _filename);

    delete[] data;
}

void wizRecording::dumpScreenshot(char* _image, std::string _filename)
{
    std::fstream raw((recordFolder + _filename).c_str(), std::ios::out | std::ios::binary);
    raw.write(_image, 320/stepRatio*240/stepRatio*4);
    raw.close();
}

void wizRecording::flushRecording()
{
    wizProgress::setProgress("Saving recorded frames", 0, 1);

    for (unsigned int i=0; i<recordedFrames.size(); i++)
    {
        dumpScreenshot(recordedFrames[i], recordedNames[i]);
        wizProgress::updateProgress(i/(float)recordedFrames.size());
    }

    recordedFrames.clear();
    recordedNames.clear();
}

void wizRecording::startRecording(int _skipFrames, int _maxFrames, int _maxTime)
{
    recording = true;
    skipFrames = _skipFrames;
    totalFrames = 0;
    recordFrames = 0;
    maxFrames = _maxFrames;
    maxTime = _maxTime;
    totalTime = 0;
}

bool wizRecording::getRecording()
{
    return recording;
}

void wizRecording::stopRecording()
{
    recording = false;
}

void wizRecording::setRecordingFolder(std::string _folder)
{
    recordFolder = _folder;
}

void wizRecording::setDownsample(int _ratio)
{
    stepRatio = _ratio;
}

void wizRecording::setRecordingCacheSize(int _size)
{
    wizRecording::recordCache = _size;
}

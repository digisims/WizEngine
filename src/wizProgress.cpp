#include "wizProgress.h"

void (*wizProgress::updateProgressCallback)(std::string, float, float) = NULL;
std::string wizProgress::lastProgressMessage = "";
float wizProgress::lastProgressStart = 0;
float wizProgress::lastProgressStop = 0;
float wizProgress::progressLimit = 0;
float wizProgress::lastValue = 0;

void wizProgress::setProgressCallBack(void (*callback)(std::string, float, float))
{
    updateProgressCallback = callback;
}

void wizProgress::setProgress(std::string _message, float _progressStart, float _progressStop)
{
    wizProgress::lastProgressMessage = _message;
    wizProgress::lastProgressStart = _progressStart;
    wizProgress::lastProgressStop = _progressStop;
}

void wizProgress::updateProgress(float _ratio)
{
    if (updateProgressCallback != NULL)
    {
        lastValue = lastProgressStart + _ratio * (lastProgressStop - lastProgressStart);
        updateProgressCallback(lastProgressMessage, lastValue, progressLimit);
    }
}

void wizProgress::refreshProgress()
{
    if (updateProgressCallback != NULL)
    {
        updateProgressCallback(lastProgressMessage, lastValue, progressLimit);
    }
}

void wizProgress::setProgressLimit(float _limit)
{
    wizProgress::progressLimit = _limit;
}

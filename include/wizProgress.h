#ifndef WIZPROGRESS_H
#define WIZPROGRESS_H

#include <string>

class wizProgress
{
    public:

    static void setProgressCallBack(void (*callback)(std::string, float, float));
    static void setProgressLimit(float _progressLimit);
    static void setProgress(std::string _message, float _progressStart, float _progressStop);
    static void updateProgress(float _ratio);
    static void refreshProgress();

    protected:

    static std::string lastProgressMessage;
    static float lastProgressStart;
    static float lastProgressStop;
    static float progressLimit;
    static float lastValue;

    static void (*updateProgressCallback)(std::string, float, float);
};

#endif // WIZPROGRESS_H

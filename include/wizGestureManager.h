#ifndef WIZGESTURE_H
#define WIZGESTURE_H

#include "wizVector2.h"
#include "wizInputManager.h"
#include "wizGestureObject.h"

#include <vector>
#include <map>
#include <math.h>
#include <string>

class wizGestureManager
{
    public:

    static void initialize();
    static void destroy();

    static void update();
    static bool wasMatched();
    wizGestureObject* getMatchedGesture();

    static void addGesture(std::string _id, wizGestureObject* _gesture);
    static wizGestureObject* getGesture(std::string _id);
    static void removeGesture(std::string _id);

    protected:

    static void startCapture();
    static void stopCapture();
    static void match();

    static wizVector2 start;
    static wizVector2 stop;
    static bool capturing;
    static bool matched;
    static wizGestureObject* matchedGesture;
    static std::vector<wizVector2> history;
    static std::map<std::string, wizGestureObject*> gestureMap;
};

#endif // WIZGESTURE_H

#ifndef WIZFOLDER_H
#define WIZFOLDER_H

#include <unistd.h>
#include <vector>
#include <string>

class wizFolder
{
    public:

    static void push(std::string _folder);
    static void pop();
    static char* getFolder();

    protected:

    static std::vector<std::string> folderList;
};

#endif // WIZFOLDER_H

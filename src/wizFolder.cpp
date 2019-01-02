#include "wizFolder.h"

std::vector<std::string> wizFolder::folderList;

void wizFolder::push(std::string _folder)
{
    char *oldPath = getFolder();

    folderList.push_back(oldPath);
    chdir(_folder.c_str());

    delete[] oldPath;
}

void wizFolder::pop()
{
    std::string previous = folderList[folderList.size()-1];
    chdir(previous.c_str());
    folderList.erase(folderList.begin()+(folderList.size()-1));
}

char* wizFolder::getFolder()
{
    char *oldPath = new char[256];
    int maxLength = 256;
    oldPath = getcwd(oldPath, maxLength);

    return oldPath;
}

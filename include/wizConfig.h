#ifndef WIZCONFIG_H
#define WIZCONFIG_H

#include "wizUtility.h"

#include <map>
#include <vector>
#include <string>
#include <fstream>

class wizConfig
{
    public:

    wizConfig();
    virtual ~wizConfig();

    void registerVariable(std::string _id, std::string* _ptr);
    std::string* getVariable(std::string _id);

    void load(std::string _filename);
    void save(std::string _filename);

    protected:

    std::map<std::string, std::string*> varMap;
};

#endif // WIZCONFIG_H

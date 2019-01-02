#include "wizConfig.h"

wizConfig::wizConfig()
{
}

wizConfig::~wizConfig()
{
}

void wizConfig::registerVariable(std::string _id, std::string* _ptr)
{
    varMap[_id] = _ptr;
}

std::string* wizConfig::getVariable(std::string _id)
{
    if (varMap.find(_id)!=varMap.end())
    {
        return varMap[_id];
    }

    return NULL;
}

void wizConfig::load(std::string _filename)
{
    std::ifstream cfg(_filename.c_str());
    std::string data;
    std::vector<std::string> tokens;

    while (!cfg.eof())
    {
        cfg >> data;
        tokens = wizUtility::splitString(data, '=');

        if (tokens.size()>1)
        {
            *getVariable(tokens[0]) = tokens[1];
        }
    }

    cfg.close();
}

void wizConfig::save(std::string _filename)
{
    std::ofstream cfg(_filename.c_str());

    for (std::map<std::string, std::string*>::iterator i = varMap.begin(); i!=varMap.end(); i++)
    {
        cfg << i->first << "=" << &i->second << "\r\n";
    }

    cfg.close();
}

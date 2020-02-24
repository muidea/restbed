#ifndef __TAG_HPP_1025__
#define __TAG_HPP_1025__
#include <cstdlib>
#include <list>
#include "json/json.h"

using namespace std;

class tagInfo 
{
public:
    tagInfo(string const &name, string const& desc, string const& unit, int type);
    tagInfo(tagInfo const& right);
    ~tagInfo();

    void jsonVal(Json::Value& val);
    tagInfo& operator=(tagInfo const& right);

protected:
    string _name;
    string _desc;
    string _unit;
    int _type;

private:
    tagInfo();

};

typedef list<tagInfo> tagInfoList;

#endif
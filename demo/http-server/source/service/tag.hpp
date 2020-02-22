#ifndef __TAG_HPP_1025__
#define __TAG_HPP_1025__
#include <cstdlib>
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
    string name;
    string desc;
    string unit;
    int type;
    Json::Value tag;

private:
    tagInfo();

};

#endif
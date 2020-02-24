#ifndef __VALUE_HPP_1025__
#define __VALUE_HPP_1025__
#include <cstdlib>
#include <list>
#include <map>

#include "json/json.h"

using namespace std;

class tagValue 
{
public:
    tagValue(string const &name, Json::Value const& val, int quality, string timeStamp);
    tagValue(tagValue const& right);
    ~tagValue();

    string const& name();

    void jsonVal(Json::Value& val);
    tagValue& operator=(tagValue const& right);

protected:
    string _name;
    Json::Value _value;
    int _quality;
    string _timeStamp;

private:
    tagValue();

};

typedef list<tagValue> tagValueList;
typedef map<string, tagValueList> tagValuesMap;

#endif
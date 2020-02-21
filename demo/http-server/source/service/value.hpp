#ifndef __VALUE_HPP_1025__
#define __VALUE_HPP_1025__
#include <cstdlib>
#include "json/json.h"

using namespace std;

class tagValue 
{
public:
    tagValue(string const &name, Json::Value const& val, int quality, string timeStamp);
    tagValue(tagValue const& right);
    ~tagValue();

    void jsonVal(Json::Value& val);
    tagValue& operator=(tagValue const& right);

protected:
    string name;
    Json::Value value;
    int quality;
    string timeStamp;

private:
    tagValue();

};

#endif
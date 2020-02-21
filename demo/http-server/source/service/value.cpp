#include "value.hpp"

tagValue::tagValue(string const &name, Json::Value const& val, int quality, string timeStamp)
    : name(name)
    , value(val)
    , quality(quality)
    , timeStamp(timeStamp)
{
}

tagValue::tagValue(tagValue const& right)
    : name(right.name)
    , value(right.value)
    , quality(right.quality)
    , timeStamp(right.timeStamp)
{
}

tagValue::~tagValue()
{
}

void tagValue::jsonVal(Json::Value& val)
{
    val["name"] = this->name;
    val["value"] = this->value;
    val["quality"] = this->quality;
    val["timeStamp"] = this->timeStamp;

}

tagValue& tagValue::operator=(tagValue const& right)
{
    if (this == &right){
        return *this;
    }

    this->name = right.name;
    this->value = right.value;
    this->quality = right.quality;
    this->timeStamp = right.timeStamp;
    
    return *this;
}
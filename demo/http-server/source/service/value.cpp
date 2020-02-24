#include "value.hpp"

tagValue::tagValue(string const &name, Json::Value const& val, int quality, string timeStamp)
    : _name(name)
    , _value(val)
    , _quality(quality)
    , _timeStamp(timeStamp)
{
}

tagValue::tagValue(tagValue const& right)
    : _name(right._name)
    , _value(right._value)
    , _quality(right._quality)
    , _timeStamp(right._timeStamp)
{
}

tagValue::~tagValue()
{
}

string const& tagValue::name() 
{
    return _name;
}

void tagValue::jsonVal(Json::Value& val)
{
    val["name"] = this->_name;
    val["value"] = this->_value;
    val["quality"] = this->_quality;
    val["timeStamp"] = this->_timeStamp;

}

tagValue& tagValue::operator=(tagValue const& right)
{
    if (this == &right){
        return *this;
    }

    this->_name = right._name;
    this->_value = right._value;
    this->_quality = right._quality;
    this->_timeStamp = right._timeStamp;
    
    return *this;
}
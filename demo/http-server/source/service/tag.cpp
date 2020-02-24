#include "tag.hpp"

tagInfo::tagInfo(string const &name, string const& desc, string const& unit, int type)
    : _name(name)
    , _desc(desc)
    , _unit(unit)
    , _type(type)
{
}

tagInfo::tagInfo(tagInfo const& right)
    : _name(right._name)
    , _desc(right._desc)
    , _unit(right._unit)
    , _type(right._type)
{
}

tagInfo::~tagInfo()
{
}

void tagInfo::jsonVal(Json::Value& val)
{
    val["name"] = _name;
    val["desc"] = _desc;
    val["unit"] = _unit;
    val["type"] = _type;
}

tagInfo& tagInfo::operator=(tagInfo const& right)
{
    if (this == &right){
        return *this;
    }

    this->_name = right._name;
    this->_desc = right._desc;
    this->_unit = right._unit;
    this->_type = right._type;

    return *this;
}
#include "tag.hpp"

tagInfo::tagInfo(string const &name, string const& desc, string const& unit, int type)
    : name(name)
    , desc(desc)
    , unit(unit)
    , type(type)
{
}

tagInfo::tagInfo(tagInfo const& right)
    : name(right.name)
    , desc(right.desc)
    , unit(right.unit)
    , type(right.type)
{
}

tagInfo::~tagInfo()
{
}

void tagInfo::jsonVal(Json::Value& val)
{
    val["name"] = name;
    val["desc"] = desc;
    val["unit"] = unit;
    val["type"] = type;
}

tagInfo& tagInfo::operator=(tagInfo const& right)
{
    if (this == &right){
        return *this;
    }

    this->name = right.name;
    this->desc = right.desc;
    this->unit = right.unit;
    this->type = right.type;

    return *this;
}
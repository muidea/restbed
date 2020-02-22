#include "common.hpp"


pageInfo::pageInfo(int totalPage, int currentPage, int pageSize)
    : totalPage(totalPage)
    , currentPage(currentPage)
    , pageSize(pageSize)
{
}

pageInfo::pageInfo(pageInfo const& right)
    : totalPage(right.totalPage)
    , currentPage(right.currentPage)
    , pageSize(right.pageSize)
{
}

pageInfo::~pageInfo()
{
}

void pageInfo::jsonVal(Json::Value& val)
{
    val["totalPage"] = totalPage;
    val["currentPage"] = currentPage;
    val["pageSize"] = pageSize;
}

pageInfo& pageInfo::operator=(pageInfo const& right)
{
    if (this == &right){
        return *this;
    }

    this->totalPage = right.totalPage;
    this->currentPage = right.currentPage;
    this->pageSize = right.pageSize;

    return *this;
}
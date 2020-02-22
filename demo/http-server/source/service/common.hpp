#ifndef __COMMON_HPP_1657__
#define __COMMON_HPP_1657__
#include <cstdlib>
#include "json/json.h"

using namespace std;

class pageInfo 
{
public:
    pageInfo(int totalPage, int currentPage, int pageSize);
    pageInfo(pageInfo const& right);
    ~pageInfo();

    void jsonVal(Json::Value& val);
    pageInfo& operator=(pageInfo const& right);

protected:
    int totalPage;
    int currentPage;
    int pageSize;

private:
    pageInfo();

};

#endif
#ifndef __COMMON_HPP_1657__
#define __COMMON_HPP_1657__
#include <cstdlib>
#include <set>
#include <string>
#include "json/json.h"
#include "tag.hpp"
#include "value.hpp"

using namespace std;

void getCurrentTimeStamp(string& curTimeStamp);

class pageInfo 
{
public:
    pageInfo(int totalPage, int currentPage, int pageSize);
    pageInfo(pageInfo const& right);
    ~pageInfo();

    void jsonVal(Json::Value& val);
    pageInfo& operator=(pageInfo const& right);

protected:
    int _totalPage;
    int _currentPage;
    int _pageSize;

private:
    pageInfo();

};


class unknownResult 
{
public:
    unknownResult();
    unknownResult(unknownResult const& right);
    ~unknownResult();

    void jsonVal(Json::Value& val);
    unknownResult& operator=(unknownResult const& right);

protected:
    int _errorCode;
    string _reason;
};

class enumResult 
{
public:
    enumResult(int errorCode, string const& reason, pageInfo const& pageInfo, tagInfoList const& tagInfos);
    enumResult(enumResult const& right);
    ~enumResult();

    void jsonVal(Json::Value& val);
    enumResult& operator=(enumResult const& right);

protected:
    int _errorCode;
    string _reason;
    pageInfo _pageInfo;
    tagInfoList _tagInfos;
private:
    enumResult();
};

class subscribeParam
{
public:
    subscribeParam();
    ~subscribeParam();

    int parse(Json::Value& val);

    set<string> const& tags();
    string const& callBack();

protected:
    set<string> _tags;
    string _callBack;
};

class subscribeResult 
{
public:
    subscribeResult(int errorCode, string const& reason);
    subscribeResult(subscribeResult const& right);
    ~subscribeResult();

    void jsonVal(Json::Value& val);
    subscribeResult& operator=(subscribeResult const& right);

protected:
    int _errorCode;
    string _reason;
private:
    subscribeResult();

};

typedef subscribeParam unsubscribeParam;
typedef subscribeResult unsubscribeResult;

class publishData
{
public:
    publishData(string const& timeStamp, tagValueList const& vals);
    publishData(publishData const& right);
    ~publishData();

    void jsonVal(Json::Value& val);
    publishData& operator=(publishData const& right);

protected:
    string _timeStamp;
    tagValueList _tagValueList;

private:
    publishData();
};

class queryParam
{
public:
    queryParam();
    ~queryParam();

    int parse(Json::Value& val);

    string const& beginTime();
    string const& endTime();
    uint valueCount();
    set<string> const& tags();

protected:
    string _beginTime;
    string _endTime;
    uint _count;
    set<string> _tags;
};

class queryResult 
{
public:
    queryResult(int errorCode, string const& reason, pageInfo const& pageInfo, tagValuesMap const& tagVals);
    queryResult(queryResult const& right);
    ~queryResult();

    void jsonVal(Json::Value& val);
    queryResult& operator=(queryResult const& right);

protected:
    int _errorCode;
    string _reason;
    pageInfo _pageInfo;
    tagValuesMap _tagVals;
private:
    queryResult();
};

class healthResult 
{
public:
    healthResult(int errorCode, string const& reason, int status);
    healthResult(healthResult const& right);
    ~healthResult();

    void jsonVal(Json::Value& val);
    healthResult& operator=(healthResult const& right);

protected:
    int _errorCode;
    string _reason;
    int _status;
private:
    healthResult();
};


#endif

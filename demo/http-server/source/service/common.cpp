#include "common.hpp"
#include <time.h>
#include <sstream>

// 2020年02月25日 
void getCurrentTimeStamp(string& curTimeStamp)
{
    const time_t t = time(NULL);
    struct tm* current_time = localtime(&t);
    stringstream ss;
    ss << current_time->tm_year + 1900 << "-"
     << current_time->tm_mon + 1 << "-"
     << current_time->tm_mday << " "
     << current_time->tm_hour << ":"
     << current_time->tm_min << ":"
     << current_time->tm_sec;

     curTimeStamp = ss.str();
}

pageInfo::pageInfo(int totalPage, int currentPage, int pageSize)
    : _totalPage(totalPage)
    , _currentPage(currentPage)
    , _pageSize(pageSize)
{
}

pageInfo::pageInfo(pageInfo const& right)
    : _totalPage(right._totalPage)
    , _currentPage(right._currentPage)
    , _pageSize(right._pageSize)
{
}

pageInfo::~pageInfo()
{
}

void pageInfo::jsonVal(Json::Value& val)
{
    val["totalPage"] = this->_totalPage;
    val["currentPage"] = this->_currentPage;
    val["pageSize"] = this->_pageSize;
}

pageInfo& pageInfo::operator=(pageInfo const& right)
{
    if (this == &right){
        return *this;
    }

    this->_totalPage = right._totalPage;
    this->_currentPage = right._currentPage;
    this->_pageSize = right._pageSize;

    return *this;
}

commonResult::commonResult(int errorCode, string const& reason)
    : _errorCode(errorCode)
    , _reason(reason)
{
}

commonResult::commonResult(commonResult const& right)
    : _errorCode(right._errorCode)
    , _reason(right._reason)
{
}

commonResult::~commonResult()
{
}

void commonResult::jsonVal(Json::Value& val)
{
    val["errorCode"] = this->_errorCode;
    val["reason"] = this->_reason;
}

commonResult& commonResult::operator=(commonResult const& right)
{
    if (this == &right){
        return *this;
    }

    this->_errorCode = right._errorCode;
    this->_reason = right._reason;

    return *this;
}

unknownResult::unknownResult()
    : _errorCode(-1)
    , _reason("unknown error")
{
}

unknownResult::unknownResult(unknownResult const& right)
    : _errorCode(right._errorCode)
    , _reason(right._reason)
{
}

unknownResult::~unknownResult()
{
}

void unknownResult::jsonVal(Json::Value& val)
{
    val["errorCode"] = this->_errorCode;
    val["reason"] = this->_reason;
}

unknownResult& unknownResult::operator=(unknownResult const& right)
{
    if (this == &right) {
        return *this;
    }

    this->_errorCode = right._errorCode;
    this->_reason = right._reason;
 
    return *this;
}

enumResult::enumResult(int errorCode, string const& reason, pageInfo const& pageInfo, tagInfoList const& tagInfos)
    : _errorCode(errorCode)
    , _reason(reason)
    , _pageInfo(pageInfo)
    , _tagInfos(tagInfos)
{
}

enumResult::enumResult(enumResult const& right)
    : _errorCode(right._errorCode)
    , _reason(right._reason)
    , _pageInfo(right._pageInfo)
    , _tagInfos(right._tagInfos)
{
}

enumResult::~enumResult()
{
}

void enumResult::jsonVal(Json::Value& val)
{
    Json::Value allContent, pageContent,tagsContent;
    this->_pageInfo.jsonVal(pageContent);
    allContent["pagination"] = pageContent;

    auto iter = this->_tagInfos.begin();
    for (; iter != this->_tagInfos.end(); ++iter ){
        Json::Value val;
        iter->jsonVal(val);

        tagsContent.append(val);
    }
    allContent["tags"] = tagsContent;

    val["errorCode"] = this->_errorCode;
    val["reason"] = this->_reason;
    val["data"] = allContent;
}

enumResult& enumResult::operator=(enumResult const& right)
{
    if (this == &right){
        return *this;
    }

    this->_errorCode = right._errorCode;
    this->_reason = right._reason;
    this->_pageInfo = right._pageInfo;
    this->_tagInfos = right._tagInfos;

    return *this;
}

subscribeParam::subscribeParam()
{

}

subscribeParam::~subscribeParam()
{

}

int subscribeParam::parse(Json::Value& val)
{
    string callback;
    if(val["callback"].isNull()){
        return -1;
    }

    if(val["tags"].isNull()){
        return -1;
    }
    callback = val["callback"].asString();
    if (callback.length() == 0){
        return -1;
    }

    Json::Value tagsVal = val["tags"];
    if(!tagsVal.isArray()){
        return -1;
    }
    
    set<string> tags;
    int tagsSize = tagsVal.size();
    for (int ii = 0; ii < tagsSize; ++ii ){
        if (!tagsVal[ii].isString()) {
            return -1;
        }

        tags.insert(tagsVal[ii].asString());
    }

    this->_tags.swap(tags);
    this->_callBack = callback;

    return  0;
}

set<string> const& subscribeParam::tags()
{
    return this->_tags;
}

string const& subscribeParam::callBack()
{
    return this->_callBack;
}

subscribeResult::subscribeResult(int errorCode, string const& reason)
    : _errorCode(errorCode)
    , _reason(reason)
{
}

subscribeResult::subscribeResult(subscribeResult const& right)
    : _errorCode(right._errorCode)
    , _reason(right._reason)
{
}

subscribeResult::~subscribeResult()
{
}

void subscribeResult::jsonVal(Json::Value& val)
{
    val["errorCode"] = this->_errorCode;
    val["reason"] = this->_reason;
}

subscribeResult& subscribeResult::operator=(subscribeResult const& right)
{
    if (this == &right){
        return *this;
    }

    this->_errorCode = right._errorCode;
    this->_reason = right._reason;

    return *this;
}

publishData::publishData(string const& timeStamp, tagValueList const& vals)
    : _timeStamp(timeStamp)
    , _tagValueList(vals)
{
}

publishData::publishData(publishData const& right)
    : _timeStamp(right._timeStamp)
    , _tagValueList(right._tagValueList)
{
}

publishData::~publishData()
{
}

void publishData::jsonVal(Json::Value& allContent)
{
    Json::Value valueContent;
    allContent["timestamp"] = this->_timeStamp;

    auto iter = this->_tagValueList.begin();
    for (; iter != this->_tagValueList.end(); ++iter ) {
        Json::Value val;
        iter->jsonVal(val);

        valueContent.append(val);
    }
    allContent["value"] = valueContent;
}

publishData& publishData::operator=(publishData const& right)
{
    if (this == &right){
        return *this;
    }

    this->_timeStamp = right._timeStamp;
    this->_tagValueList = right._tagValueList;

    return *this;
}

queryParam::queryParam()
{

}

queryParam::~queryParam()
{

}

int queryParam::parse(Json::Value& val)
{
    string beginTime;
    string endTime;
    uint valueCount;
    if(val["beginTime"].isNull()){
        return -1;
    }
    if(val["endTime"].isNull()){
        return -1;
    }
    if(val["count"].isNull()){
        return -1;
    }
    if(val["tags"].isNull()){
        return -1;
    }

    beginTime = val["beginTime"].asString();
    if (beginTime.length() == 0){
        return -1;
    }

    endTime = val["endTime"].asString();
    if (endTime.length() == 0){
        return -1;
    }

    valueCount = val["count"].asUInt();

    Json::Value tagsVal = val["tags"];
    if(!tagsVal.isArray()){
        return -1;
    }
    
    set<string> tags;
    int tagsSize = tagsVal.size();
    for (int ii = 0; ii < tagsSize; ++ii ){
        if (!tagsVal[ii].isString()) {
            return -1;
        }

        tags.insert(tagsVal[ii].asString());
    }

    this->_beginTime = beginTime;
    this->_endTime = endTime;
    this->_count = valueCount;
    this->_tags.swap(tags);

    return  0;
}

string const& queryParam::beginTime()
{
    return this->_beginTime;
}

string const& queryParam::endTime()
{
    return this->_endTime;
}

uint queryParam::valueCount()
{
    return this->_count;
}

set<string> const& queryParam::tags()
{
    return this->_tags;
}

queryResult::queryResult(int errorCode, string const& reason, pageInfo const& pageInfo, tagValuesMap const& tagVals)
    : _errorCode(errorCode)
    , _reason(reason)
    , _pageInfo(pageInfo)
    , _tagVals(tagVals)
{
}

queryResult::queryResult(queryResult const& right)
    : _errorCode(right._errorCode)
    , _reason(right._reason)
    , _pageInfo(right._pageInfo)
    , _tagVals(right._tagVals)
{
}

queryResult::~queryResult()
{
}

void queryResult::jsonVal(Json::Value& val)
{
    Json::Value allContent, pageContent,tagsContent;

    this->_pageInfo.jsonVal(pageContent);
    allContent["pagination"] = pageContent;

    auto iter = this->_tagVals.begin();
    for (; iter != this->_tagVals.end(); ++iter ){
        Json::Value valList;
        auto vals = iter->second;
        for ( auto i = vals.begin(); i != vals.end(); ++i) {
            Json::Value val;
            i->jsonVal(val);

            valList.append(val);
        }

        tagsContent[iter->first] = valList;
    }

    allContent["values"] = tagsContent;

    val["errorCode"] = this->_errorCode;
    val["reason"] = this->_reason;
    val["data"] = allContent;
}

queryResult& queryResult::operator=(queryResult const& right)
{
    if (this == &right){
        return *this;
    }

    this->_errorCode = right._errorCode;
    this->_reason = right._reason;
    this->_pageInfo = right._pageInfo;
    this->_tagVals = right._tagVals;

    return *this;
}

healthResult::healthResult(int errorCode, string const& reason, int status)
    : _errorCode(errorCode)
    , _reason(reason)
    , _status(status)
{
}

healthResult::healthResult(healthResult const& right)
    : _errorCode(right._errorCode)
    , _reason(right._reason)
    , _status(right._status)
{
}

healthResult::~healthResult()
{
}

void healthResult::jsonVal(Json::Value& val)
{
    Json::Value allContent;

    allContent["status"] = 0;

    val["errorCode"] = this->_errorCode;
    val["reason"] = this->_reason;
    val["data"] = allContent;
}

healthResult& healthResult::operator=(healthResult const& right)
{
    if (this == &right){
        return *this;
    }

    this->_errorCode = right._errorCode;
    this->_reason = right._reason;
    this->_status = right._status;

    return *this;
}

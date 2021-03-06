#include <json/json.h>
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <memory>
#include <exception>
#include "service.hpp"
#include "tag.hpp"
#include "value.hpp"
#include "common.hpp"

using namespace std;

APIService::APIService()
{
}

APIService::~APIService()
{
}

int APIService::Start()
{
    auto enumTagsResource = make_shared<Resource>();
    enumTagsResource->set_path("/tags/enum");
    auto enumTagsFunc = bind(&APIService::enumTags, this, placeholders::_1);
    enumTagsResource->set_method_handler("GET", enumTagsFunc);

    _httpService.publish(enumTagsResource);

    auto queryHisDataResource = make_shared<Resource>();
    queryHisDataResource->set_path("/history/query");
    auto queryHisDataFunc = bind(&APIService::queryHisData, this, placeholders::_1);
    queryHisDataResource->set_method_handler("POST", queryHisDataFunc);
    _httpService.publish(queryHisDataResource);

    auto subscribeRealDataResource = make_shared<Resource>();
    subscribeRealDataResource->set_path("/realtime/subscribe");
    auto subscribeRealDataFunc = bind(&APIService::subscribeRealData, this, placeholders::_1);
    subscribeRealDataResource->set_method_handler("POST", subscribeRealDataFunc);
    _httpService.publish(subscribeRealDataResource);

    auto unsubscribeRealDataResource = make_shared<Resource>();
    unsubscribeRealDataResource->set_path("/realtime/unsubscribe");
    auto unsubscribeRealDataFunc = bind(&APIService::unsubscribeRealData, this, placeholders::_1);
    unsubscribeRealDataResource->set_method_handler("POST", unsubscribeRealDataFunc);
    _httpService.publish(unsubscribeRealDataResource);

    auto isHealthResource = make_shared<Resource>();
    isHealthResource->set_path("/ishealth");
    auto isHealthFunc = bind(&APIService::isHealth, this, placeholders::_1);
    isHealthResource->set_method_handler("GET", isHealthFunc);
    _httpService.publish(isHealthResource);

    return _provider.start();
}

void APIService::Stop()
{

    _provider.stop();

    _httpService.stop();
}

void APIService::Run()
{
    auto settings = make_shared<Settings>();
    settings->set_port(8020);

    _httpService.start(settings);
}

void APIService::enumTags(const shared_ptr<Session> session)
{
    const auto request = session->get_request();
    
    string currentTimeStamp;
    getCurrentTimeStamp(currentTimeStamp);
    fprintf(stdout, "[%s] %s\n", currentTimeStamp.c_str(), "enumTags");

    list<tagInfo> tags;
    _provider.queryTags(tags);

    pageInfo page(1, 1, 50);

    Json::Value jsonResult;
    enumResult result(0, "", page, tags);
    result.jsonVal(jsonResult);

    string resultContent = jsonResult.toStyledString();

    session->close(OK, resultContent, {{"Content-Length", to_string(resultContent.length())}, {"Connection", "close"}, {"Content-Type", "application/json;charset=UTF-8"}});
}

void APIService::queryHisData(const shared_ptr<Session> session)
{
    const auto request = session->get_request();
    size_t content_length = request->get_header("Content-Length", 0);

    string currentTimeStamp;
    getCurrentTimeStamp(currentTimeStamp);
    fprintf(stdout, "[%s] %s\n", currentTimeStamp.c_str(), "queryHisData");

    try {
        if (content_length > 0) {
            auto handler = bind(&APIService::queryHisDataHandler, this, placeholders::_1, placeholders::_2);
            session->fetch(content_length, handler);
        } else {
            commonErrorHandler(session, 1, "invalid post param");
        }
    }catch(...) {
        unknownErrorHandler(session);
    }
}

void APIService::queryHisDataHandler(const shared_ptr<Session> session, Bytes const &payload)
{
    char *dataPtr = (char *)payload.data();

    Json::Value jsonParam;

    int errorCode = 0;
    string reason = "";

    Json::Value jsonResult;
    pageInfo page(1, 1, 50);

    tagValuesMap values;
    do
    {
        bool res;
        string errs;
        Json::CharReaderBuilder readerBuilder;
        std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
        res = jsonReader->parse(dataPtr, dataPtr + payload.size(), &jsonParam, &errs);
        if (!res || !errs.empty()) {
            errorCode = 1;
            reason = "invalid jsonParam";
            break;
        }

        queryParam param;
        if (0 != param.parse(jsonParam))
        {
            errorCode = 1;
            reason = "invalid jsonParam";
            break;
        }

        _provider.queryValues(param.beginTime(), param.endTime(), param.valueCount(), values);
    } while (false);

    queryResult result(errorCode, reason, page, values);
    result.jsonVal(jsonResult);
    string resultContent = jsonResult.toStyledString();

    session->close(OK, resultContent, {{"Content-Length", to_string(resultContent.length())}, {"Connection", "close"}, {"Content-Type", "application/json;charset=UTF-8"}});
}

void APIService::subscribeRealData(const shared_ptr<Session> session)
{
    const auto request = session->get_request();
    size_t content_length = request->get_header("Content-Length", 0);

    string currentTimeStamp;
    getCurrentTimeStamp(currentTimeStamp);
    fprintf(stdout, "[%s] %s\n", currentTimeStamp.c_str(), "subscribeRealData");

    try {
        if (content_length >0){
            auto handler = bind(&APIService::subscribeRealDataHandler, this, placeholders::_1, placeholders::_2);
            session->fetch(content_length, handler);
        } else {
            commonErrorHandler(session, 1, "invalid post param");
        }
    }catch(...){
        unknownErrorHandler(session);
    }
}

void APIService::subscribeRealDataHandler(const shared_ptr<Session> session, const Bytes &payload)
{
    char *dataPtr = (char *)payload.data();
    Json::Value jsonParam;

    int errorCode = 0;
    string reason = "";

    do
    {
        bool res;
        string errs;
        Json::CharReaderBuilder readerBuilder;
        std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
        res = jsonReader->parse(dataPtr, dataPtr + payload.size(), &jsonParam, &errs);
        if (!res || !errs.empty()) {
            errorCode = 1;
            reason = "invalid jsonParam";
            break;
        }

        subscribeParam param;
        if (0 != param.parse(jsonParam))
        {
            errorCode = 1;
            reason = "invalid jsonParam";
            break;
        }
        _provider.subscribe(param.callBack(), param.tags(), this);

    } while (false);

    Json::Value jsonResult;
    subscribeResult result(errorCode, reason);
    result.jsonVal(jsonResult);

    string resultContent = jsonResult.toStyledString();

    session->close(OK, resultContent, {{"Content-Length", to_string(resultContent.length())}, {"Connection", "close"}, {"Content-Type", "application/json;charset=UTF-8"}});
}

void APIService::unsubscribeRealData(const shared_ptr<Session> session)
{
    const auto request = session->get_request();
    size_t content_length = request->get_header("Content-Length", 0);

    string currentTimeStamp;
    getCurrentTimeStamp(currentTimeStamp);
    fprintf(stdout, "[%s] %s\n", currentTimeStamp.c_str(), "unsubscribeRealData");

    try {
        if (content_length>0) {
            auto handler = bind(&APIService::unsubscribeRealDataHandler, this, placeholders::_1, placeholders::_2);
            session->fetch(content_length, handler);
        } else {
            commonErrorHandler(session, 1, "invalid post param");
        }
    }catch(...){
        unknownErrorHandler(session);
    }
}

void APIService::unsubscribeRealDataHandler(const shared_ptr<Session> session, const Bytes &payload)
{
    char *dataPtr = (char *)payload.data();
    Json::Value jsonParam;

    int errorCode = 0;
    string reason = "";
    do
    {
        bool res;
        string errs;
        Json::CharReaderBuilder readerBuilder;
        std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
        res = jsonReader->parse(dataPtr, dataPtr + payload.size(), &jsonParam, &errs);
        if (!res || !errs.empty()) {
            errorCode = 1;
            reason = "invalid jsonParam";
            break;
        }

        unsubscribeParam param;
        if (0 != param.parse(jsonParam))
        {
            errorCode = 1;
            reason = "invalid jsonParam";
            break;
        }

        _provider.unsubscribe(param.callBack());
    } while (false);

    Json::Value jsonResult;
    subscribeResult result(errorCode, reason);
    result.jsonVal(jsonResult);

    string resultContent = jsonResult.toStyledString();

    session->close(OK, resultContent, {{"Content-Length", to_string(resultContent.length())}, {"Connection", "close"}, {"Content-Type", "application/json;charset=UTF-8"}});
}

void APIService::isHealth(const shared_ptr<Session> session)
{
    const auto request = session->get_request();

    string currentTimeStamp;
    getCurrentTimeStamp(currentTimeStamp);
    fprintf(stdout, "[%s] %s\n", currentTimeStamp.c_str(), "isHealth");

    Json::Value jsonResult;
    healthResult result(0, "", 0);
    result.jsonVal(jsonResult);

    string resultContent = jsonResult.toStyledString();
    session->close(OK, resultContent, {{"Content-Length", to_string(resultContent.length())}, {"Connection", "close"}, {"Content-Type", "application/json;charset=UTF-8"}});
}

void APIService::onHandle(string const &handler, tagValueList const &value)
{
    publishData publishData("", value);
    Json::Value jsonResult;
    publishData.jsonVal(jsonResult);
    const string& resultContent = jsonResult.toStyledString();

    auto request = make_shared<Request>(Uri(handler));
    request->set_header("Host", request->get_host());
    request->add_header("Content-Type", "application/json");
    request->add_header("Content-Length", to_string(resultContent.length()));
    request->set_method("POST");
    request->set_body(resultContent);

    bool isOK = false;
    auto response = Http::sync(request);
    if (response->get_status_code() == 200){
        isOK = true;
    }

    int currentCount = 0;
    {
        jthread::JMutexAutoLock lock(_handlerMutex);
        auto it = _handlerFailedCount.find(handler);
        if (!isOK){
            if(it == _handlerFailedCount.end()){
                _handlerFailedCount[handler] = 1;
                return;
            }

            currentCount = it->second++;
        } else {
            if (it!=_handlerFailedCount.end()) {
                _handlerFailedCount.erase(it);
            }
        }
    }

    if (currentCount > 10){
        _provider.unsubscribe(handler);
    }
}


void APIService::commonErrorHandler(const shared_ptr< Session > session, int errorCode, string const& reason)
{
    Json::Value jsonResult;
    commonResult result(errorCode, reason);
    result.jsonVal(jsonResult);

    string resultContent = jsonResult.toStyledString();

    session->close(OK, resultContent, {{"Content-Length", to_string(resultContent.length())}, {"Connection", "close"}, {"Content-Type", "application/json;charset=UTF-8"}});
}


void APIService::unknownErrorHandler(const shared_ptr< Session > session)
{
    Json::Value jsonResult;
    unknownResult result;
    result.jsonVal(jsonResult);

    string resultContent = jsonResult.toStyledString();

    session->close(OK, resultContent, {{"Content-Length", to_string(resultContent.length())}, {"Connection", "close"}, {"Content-Type", "application/json;charset=UTF-8"}});
}

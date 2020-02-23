#include <json/json.h>
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include "service.hpp"
#include "tag.hpp"
#include "value.hpp"
#include "common.hpp"

using namespace std;

void mockTags( list< tagInfo >& tags );
void mockValues(list<tagValue>& values);
void mockTagsValues(tagValuesMap& values);

APIService::APIService()
{

}

APIService::~APIService()
{

}

int APIService::Start()
{
    _runningFlag = true;

    auto enumTagsResource = make_shared< Resource >( );
    enumTagsResource->set_path( "/tags/enum" );
    auto enumTagsFunc = bind(&APIService::enumTags, this, placeholders::_1);
    enumTagsResource->set_method_handler( "GET", enumTagsFunc );

    _httpService.publish(enumTagsResource);

    auto queryHisDataResource = make_shared< Resource >( );
    queryHisDataResource->set_path( "/history/query" );
    auto queryHisDataFunc = bind(&APIService::queryHisData, this, placeholders::_1);
    queryHisDataResource->set_method_handler( "GET", queryHisDataFunc );
    _httpService.publish(queryHisDataResource);

    auto subscribeRealDataResource = make_shared< Resource >( );
    subscribeRealDataResource->set_path( "/realtime/subscribe" );
    auto subscribeRealDataFunc = bind(&APIService::subscribeRealData, this, placeholders::_1);
    subscribeRealDataResource->set_method_handler( "POST", subscribeRealDataFunc );
    _httpService.publish(subscribeRealDataResource);

    auto unsubscribeRealDataResource = make_shared< Resource >( );
    unsubscribeRealDataResource->set_path( "/realtime/unsubscribe" );
    auto unsubscribeRealDataFunc = bind(&APIService::unsubscribeRealData, this, placeholders::_1);
    unsubscribeRealDataResource->set_method_handler( "POST", unsubscribeRealDataFunc );
    _httpService.publish(unsubscribeRealDataResource);

    auto isHealthResource = make_shared< Resource >( );
    isHealthResource->set_path( "/ishealth" );
    auto isHealthFunc = bind(&APIService::isHealth, this, placeholders::_1);
    isHealthResource->set_method_handler( "GET", isHealthFunc );
    _httpService.publish(isHealthResource);
}

void APIService::Stop()
{
    _runningFlag = false;

    _httpService.stop();
}

void APIService::Run()
{
    _httpService.start();
}

void APIService::enumTags( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    size_t content_length = request->get_header( "Content-Length", 0 );

    fprintf( stdout, "%s\n", "enumTags" );

    list< tagInfo > tags;
    mockTags(tags);

    pageInfo page(1, 1, 50);

    Json::Value jsonResult;
    enumResult result(0,"", page, tags);
    result.jsonVal(jsonResult);

    string resultContent  = jsonResult.toStyledString();
    stringstream stream;
    stream << resultContent.length();
    string resultLen = stream.str();

    session->close( OK, resultContent, { { "Content-Length", resultLen }, { "Connection", "close" }, { "Content-Type", "application/json;charset=UTF-8" } } );
}

void APIService::queryHisData( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    size_t content_length = request->get_header( "Content-Length", 0 );
    int catalog = request->get_query_parameter("catalog", 0);

    fprintf( stdout, "%s, catalog:%d\n", "queryHisData", catalog );

    tagValuesMap values;
    mockTagsValues(values);

    pageInfo page(1, 1, 50);

    Json::Value jsonResult;
    queryResult result(0,"", page, values);
    result.jsonVal(jsonResult);

    string resultContent  = jsonResult.toStyledString();
    stringstream stream;
    stream << resultContent.length();
    string resultLen = stream.str();

    session->close( OK, resultContent, { { "Content-Length", resultLen }, { "Connection", "close" }, { "Content-Type", "application/json;charset=UTF-8" } } );
}

void APIService::subscribeRealData( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    size_t content_length = request->get_header( "Content-Length", 0 );

    auto handler = bind(&APIService::subscribeRealDataHandler, this, placeholders::_1, placeholders::_2);
    session->fetch( content_length, handler);
}

void APIService::subscribeRealDataHandler(const shared_ptr< Session > session, const Bytes& payload)
{
    char* dataPtr = (char*)payload.data();
    Json::Reader reader;
    Json::Value jsonParam;

    int errorCode = 0;
    string reason = "";

    do
    {
        if (!reader.parse(dataPtr, jsonParam)) {
            errorCode = 1;
            reason = "invalid jsonParam";
        }

        subscribeParam param;
        if (0 !=param.parse(jsonParam)) {
            errorCode = 1;
            reason = "invalid jsonParam";
            break;
        }

    } while (false);
        

    Json::Value jsonResult;
    subscribeResult result(errorCode, reason);
    result.jsonVal(jsonResult);

    string resultContent  = jsonResult.toStyledString();

    stringstream stream;
    stream << resultContent.length();
    string resultLen = stream.str();

    session->close( OK, resultContent, { { "Content-Length", resultLen }, { "Connection", "close" }, { "Content-Type", "application/json;charset=UTF-8" } } );
}

void APIService::unsubscribeRealData( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    size_t content_length = request->get_header( "Content-Length", 0 );

    auto handler = bind(&APIService::unsubscribeRealDataHandler, this, placeholders::_1, placeholders::_2);
    session->fetch( content_length, handler);
}

void APIService::unsubscribeRealDataHandler(const shared_ptr< Session > session, const Bytes& payload)
{
    char* dataPtr = (char*)payload.data();
    Json::Reader reader;
    Json::Value jsonParam;

    int errorCode = 0;
    string reason = "";
    do
    {
        if (!reader.parse(dataPtr, jsonParam)) {
            errorCode = 1;
            reason = "invalid jsonParam";
        }

        unsubscribeParam param;
        if (0 !=param.parse(jsonParam)) {
            errorCode = 1;
            reason = "invalid jsonParam";
            break;
        }

    } while (false);

    Json::Value jsonResult;
    subscribeResult result(errorCode, reason);
    result.jsonVal(jsonResult);

    string resultContent  = jsonResult.toStyledString();
    stringstream stream;
    stream << resultContent.length();
    string resultLen = stream.str();

    session->close( OK, resultContent, { { "Content-Length", resultLen }, { "Connection", "close" }, { "Content-Type", "application/json;charset=UTF-8" } } );
}

void APIService::isHealth( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    size_t content_length = request->get_header( "Content-Length", 0 );

    fprintf( stdout, "%s\n", "isHealth" );
    Json::Value jsonResult;
    healthResult result(0, "", 0);
    result.jsonVal(jsonResult);

    string resultContent  = jsonResult.toStyledString();
    stringstream stream;
    stream << resultContent.length();
    string resultLen = stream.str();

    session->close( OK, resultContent, { { "Content-Length", resultLen }, { "Connection", "close" }, { "Content-Type", "application/json;charset=UTF-8" } } );
}

void* APIService::Thread()
{
    while (_runningFlag)
    {
        //sleep(10000);
    }
    
}
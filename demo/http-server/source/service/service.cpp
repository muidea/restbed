#include <json/json.h>
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include "service.hpp"
#include "tag.hpp"
#include "value.hpp"

using namespace std;

void mockTags( list< tagInfo >& tags );
void mockValues(list<tagValue>& values);

APIService::APIService()
{

}

APIService::~APIService()
{

}

int APIService::Start()
{
    auto enumTagsResource = make_shared< Resource >( );
    enumTagsResource->set_path( "/tags/enum" );
    auto enumTagsFunc = bind(&APIService::enumTags, this, placeholders::_1);
    enumTagsResource->set_method_handler( "GET", enumTagsFunc );

    httpService.publish(enumTagsResource);

    auto queryHisDataResource = make_shared< Resource >( );
    queryHisDataResource->set_path( "/history/query" );
    auto queryHisDataFunc = bind(&APIService::queryHisData, this, placeholders::_1);
    queryHisDataResource->set_method_handler( "GET", queryHisDataFunc );
    httpService.publish(queryHisDataResource);

    auto subscribeRealDataResource = make_shared< Resource >( );
    subscribeRealDataResource->set_path( "/realtime/subscribe" );
    auto subscribeRealDataFunc = bind(&APIService::subscribeRealData, this, placeholders::_1);
    subscribeRealDataResource->set_method_handler( "GET", subscribeRealDataFunc );
    httpService.publish(subscribeRealDataResource);

    auto unsubscribeRealDataResource = make_shared< Resource >( );
    unsubscribeRealDataResource->set_path( "/realtime/unsubscribe" );
    auto unsubscribeRealDataFunc = bind(&APIService::unsubscribeRealData, this, placeholders::_1);
    unsubscribeRealDataResource->set_method_handler( "GET", unsubscribeRealDataFunc );
    httpService.publish(unsubscribeRealDataResource);

    auto isHealthResource = make_shared< Resource >( );
    isHealthResource->set_path( "/ishealth" );
    auto isHealthFunc = bind(&APIService::isHealth, this, placeholders::_1);
    isHealthResource->set_method_handler( "GET", isHealthFunc );
    httpService.publish(isHealthResource);
}

void APIService::Stop()
{
    httpService.stop();
}

void APIService::Run()
{
    httpService.start();
}

void APIService::enumTags( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    size_t content_length = request->get_header( "Content-Length", 0 );

    fprintf( stdout, "%s\n", "enumTags" );

    Json::Value root;
    list< tagInfo > tags;
    mockTags(tags);

    auto iter = tags.begin();
    for (; iter != tags.end(); ++iter ){
        Json::Value val;
        iter->jsonVal(val);

        root.append(val);
    }

    string content  = root.toStyledString();
    std::cout << content << std::endl;
    stringstream stream;
    stream << content.length();
    string contentLen = stream.str();

    session->close( OK, content, { { "Content-Length", contentLen }, { "Connection", "close" }, { "Content-Type", "application/json;charset=UTF-8" } } );
}

void APIService::queryHisData( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    size_t content_length = request->get_header( "Content-Length", 0 );

    session->fetch( content_length, [ request ]( const shared_ptr< Session > session, const Bytes & body )
    {
        fprintf( stdout, "%s\n", "queryHisData" );
        session->close( OK, "queryHisData!", { { "Content-Length", "13" }, { "Connection", "close" } } );
    });
}

void APIService::subscribeRealData( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    size_t content_length = request->get_header( "Content-Length", 0 );

    session->fetch( content_length, [ request ]( const shared_ptr< Session > session, const Bytes & body )
    {
        fprintf( stdout, "%s\n", "subscribeRealData" );
        session->close( OK, "subscribeRealData!", { { "Content-Length", "18" }, { "Connection", "close" } } );
    });
}

void APIService::unsubscribeRealData( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    size_t content_length = request->get_header( "Content-Length", 0 );

    session->fetch( content_length, [ request ]( const shared_ptr< Session > session, const Bytes & body )
    {
        fprintf( stdout, "%s\n", "{\"account\":\"administrator\",\"password\":\"administrator\"}" );
        session->close( OK, "{\"account\":\"administrator\",\"password\":\"administrator\"}", { { "Content-Length", "55" }, { "Connection", "close" },{ "Content-Type", "application/json;charset=UTF-8" } } );
    });
}

void APIService::isHealth( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    size_t content_length = request->get_header( "Content-Length", 0 );

    session->fetch( content_length, [ request ]( const shared_ptr< Session > session, const Bytes & body )
    {
        fprintf( stdout, "%s\n", "isHealth" );
        session->close( OK, "isHealth!", { { "Content-Length", "13" }, { "Connection", "close" } } );
    });
}

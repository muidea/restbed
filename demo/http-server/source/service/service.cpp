#include "server.hpp"


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
    enumTagsResource->set_method_handler( "GET", this.enumTags );
    this.httpService.publish(enumTagsResource);

    auto queryHisDataResource = make_shared< Resource >( );
    queryHisDataResource->set_path( "/history/query" );
    queryHisDataResource->set_method_handler( "GET", this.queryHisData );
    this.httpService.publish(queryHisDataResource);

    auto subscribeRealDataResource = make_shared< Resource >( );
    subscribeRealDataResource->set_path( "/realtime/subscribe" );
    subscribeRealDataResource->set_method_handler( "GET", this.subscribeRealData );
    this.httpService.publish(subscribeRealDataResource);

    auto unsubscribeRealDataResource = make_shared< Resource >( );
    unsubscribeRealDataResource->set_path( "/realtime/unsubscribe" );
    unsubscribeRealDataResource->set_method_handler( "GET", this.unsubscribeRealData );
    this.httpService.publish(unsubscribeRealDataResource);

    auto isHealthResource = make_shared< Resource >( );
    isHealthResource->set_path( "/ishealth" );
    isHealthResource->set_method_handler( "GET", this.isHealth );
    this.httpService.publish(isHealthResource);
}

void APIService::Stop()
{
    this.httpService.stop()
}

void APIService::Run()
{
    this.httpService.start();
}

void APIService::enumTags( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    size_t content_length = request->get_header( "Content-Length", 0 );

    session->fetch( content_length, [ request ]( const shared_ptr< Session > session, const Bytes & body )
    {
        fprintf( stdout, "%.*s\n", ( int ) body.size( ), body.data( ) );
        session->close( OK, "enumTags!", { { "Content-Length", "13" }, { "Connection", "close" } } );
    });
}

void APIService::queryHisData( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    size_t content_length = request->get_header( "Content-Length", 0 );

    session->fetch( content_length, [ request ]( const shared_ptr< Session > session, const Bytes & body )
    {
        fprintf( stdout, "%.*s\n", ( int ) body.size( ), body.data( ) );
        session->close( OK, "queryHisData!", { { "Content-Length", "13" }, { "Connection", "close" } } );
    });
}

void APIService::subscribeRealData( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    size_t content_length = request->get_header( "Content-Length", 0 );

    session->fetch( content_length, [ request ]( const shared_ptr< Session > session, const Bytes & body )
    {
        fprintf( stdout, "%.*s\n", ( int ) body.size( ), body.data( ) );
        session->close( OK, "subscribeRealData!", { { "Content-Length", "13" }, { "Connection", "close" } } );
    });
}

void APIService::unsubscribeRealData( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    size_t content_length = request->get_header( "Content-Length", 0 );

    session->fetch( content_length, [ request ]( const shared_ptr< Session > session, const Bytes & body )
    {
        fprintf( stdout, "%.*s\n", ( int ) body.size( ), body.data( ) );
        session->close( OK, "unsubscribeRealData!", { { "Content-Length", "13" }, { "Connection", "close" } } );
    });
}

void APIService::isHealth( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    size_t content_length = request->get_header( "Content-Length", 0 );

    session->fetch( content_length, [ request ]( const shared_ptr< Session > session, const Bytes & body )
    {
        fprintf( stdout, "%.*s\n", ( int ) body.size( ), body.data( ) );
        session->close( OK, "isHealth!", { { "Content-Length", "13" }, { "Connection", "close" } } );
    });
}

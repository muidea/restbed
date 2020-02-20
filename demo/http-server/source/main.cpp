#include <memory>
#include <cstdlib>
#include <restbed>
#include "service/service.hpp"

using namespace std;
using namespace restbed;

void post_method_handler(const shared_ptr<Session> session)
{
    const auto request = session->get_request();

    size_t content_length = request->get_header("Content-Length", 0);

    session->fetch(content_length, [request](const shared_ptr<Session> session, const Bytes &body) {
        fprintf(stdout, "%.*s\n", (int)body.size(), body.data());
        session->close(OK, "Hello, World!", {{"Content-Length", "13"}, {"Connection", "close"}});
    });
}

void get_method_handler(const shared_ptr<Session> session)
{
    const auto request = session->get_request();

    size_t content_length = request->get_header("Content-Length", 0);

    session->fetch(content_length, [request](const shared_ptr<Session> session, const Bytes &body) {
        fprintf(stdout, "%.*s\n", (int)body.size(), body.data());
        session->close(OK, "Hello, World!", {{"Content-Length", "13"}, {"Connection", "close"}});
    });
}

int main(const int, const char **)
{
    /*
    auto postResource = make_shared< Resource >( );
    postResource->set_path( "/resource" );
    postResource->set_method_handler( "POST", post_method_handler );

    auto getResource = make_shared< Resource >( );
    getResource->set_path( "/get" );
    getResource->set_method_handler( "GET", get_method_handler );


    Service service;
    service.publish( postResource );
    service.publish( getResource );
    service.start( );
    */

    APIService apiService;
    apiService.Start();
    apiService.Run();
    apiService.Stop();

    return EXIT_SUCCESS;
}

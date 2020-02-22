#pragma once

#include <memory>
#include <cstdlib>
#include <restbed>
#include <json/json.h>

using namespace std;
using namespace restbed;

class APIService {
public:
    APIService();
    ~APIService();
    int Start();
    void Stop();
    void Run();

protected:
    void enumTags( const shared_ptr< Session > session );
    void queryHisData( const shared_ptr< Session > session );
    void subscribeRealData( const shared_ptr< Session > session );
    void unsubscribeRealData( const shared_ptr< Session > session );
    void isHealth( const shared_ptr< Session > session );

    void constructResult(int errorCode, string const& reason, Json::Value& content, Json::Value& result);

private:
    Service httpService;

};

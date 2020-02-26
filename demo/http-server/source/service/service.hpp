#ifndef __SERVICE_HPP_1656__
#define __SERVICE_HPP_1656__

#include <map>
#include <memory>
#include <cstdlib>
#include <restbed>

#include <json/json.h>
#include <jthread/jmutexautolock.h>

#include "provider.hpp"

using namespace std;
using namespace restbed;

class APIService 
    : protected CallBacker {
public:
    APIService();
    virtual ~APIService();
    int Start();
    void Stop();
    void Run();

protected:
    void enumTags( const shared_ptr< Session > session );
    void queryHisData( const shared_ptr< Session > session );
    void subscribeRealData( const shared_ptr< Session > session );
    void unsubscribeRealData( const shared_ptr< Session > session );
    void isHealth( const shared_ptr< Session > session );

    void queryHisDataHandler(const shared_ptr< Session > session, Bytes const& payload);
    void subscribeRealDataHandler(const shared_ptr< Session > session, Bytes const& payload);
    void unsubscribeRealDataHandler(const shared_ptr< Session > session, Bytes const& payload);

    virtual void onHandle(string const& handler, tagValueList const& value);

    void commonErrorHandler(const shared_ptr< Session > session, int errorCode, string const& reason);
    void unknownErrorHandler(const shared_ptr< Session > session);
private:
    Service _httpService;

    Provider _provider;
    
    map<string,int> _handlerFailedCount;
    jthread::JMutex _handlerMutex;

};

#endif

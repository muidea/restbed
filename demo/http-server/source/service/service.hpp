#ifndef __SERVICE_HPP_1656__
#define __SERVICE_HPP_1656__

#include <memory>
#include <cstdlib>
#include <restbed>

#include <json/json.h>
#include <jthread/jthread.h>

using namespace std;
using namespace restbed;
using namespace jthread;

class APIService
    : protected JThread {
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

    void subscribeRealDataHandler(const shared_ptr< Session > session, Bytes const& payload);
    void unsubscribeRealDataHandler(const shared_ptr< Session > session, Bytes const& payload);

    virtual void *Thread();

private:
    bool _runningFlag;
    Service _httpService;
};

#endif

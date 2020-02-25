#ifndef __PROVIDER_HPP_1953__
#define __PROVIDER_HPP_1953__
#include <string>
#include <list>
#include <set>
#include <map>
#include <memory>
#include <jthread/jthread.h>
#include <jthread/jmutex.h>
#include "tag.hpp"
#include "value.hpp"

using namespace std;
using namespace jthread;

class CallBacker
{
public:
    virtual ~CallBacker(){};
    virtual void onHandle(string const& handler, tagValueList const& value) = 0;
};

typedef list<CallBacker> CallBackerList;

class tagCallBacker
{
public:
    tagCallBacker(set<string> const& tags, string const& handler, CallBacker* callBakcer)
        : _tagSet(tags)
        , _handler(handler)
        , _callBakcer(callBakcer)
    {

    }

    ~tagCallBacker()
    {

    }

    void dispatch()
    {
        tagValueList temp;
        _callBakcer->onHandle(_handler, _tagValueList);

        _tagValueList.swap(temp);
    }

    bool onNotify(tagValue const& val)
    {
        auto iter = _tagSet.find(val.name());
        if(iter == _tagSet.end()) {
            return false;
        }

        _tagValueList.push_back(val);
        return true;
    }

private:
    set<string> _tagSet;
    string _handler;
    tagValueList _tagValueList;

    CallBacker* _callBakcer;
};

typedef shared_ptr<tagCallBacker> tagCallBackerPtr;

// handler -> tagCallBacker
typedef map< string, tagCallBackerPtr > handlerCallBackerMap;

class Provider
    : protected JThread
{
public:
    Provider();
    ~Provider();
    
    int start();
    void stop();

    void queryTags(tagInfoList& tags);
    void queryValues(string const& beginTime, string const& endTime, int valueCount, tagValuesMap& values);
    void subscribe( string const& handler, set<string> const& tags, CallBacker* callBacker );
    void unsubscribe( string const& handler );

protected:
    virtual void *Thread();

protected:
    bool _runningFlag;

    handlerCallBackerMap _handlerCallBackerMap;

    jthread::JMutex _handlerCallBackerMutex;

};

#endif


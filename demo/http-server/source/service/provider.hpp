#ifndef __PROVIDER_HPP_1953__
#define __PROVIDER_HPP_1953__
#include <string>
#include <list>
#include <set>
#include <map>
#include <memory>
#include <jthread/jmutex.h>
#include "tag.hpp"
#include "value.hpp"

using namespace std;

class CallBacker
{
public:
    virtual ~CallBacker(){};
    virtual void onHandle(string const& handler, tagValueList const& value) = 0;
};

class Observer
{
public:
    virtual ~Observer(){};
    virtual void onNotify(tagValue const& val) = 0;
};

typedef list<CallBacker> CallBackerList;
typedef list<Observer> ObserverList;

class tagCallBacker
    : protected Observer
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

    string const& handler()
    {
        return _handler;
    }

    void dispatch()
    {
        tagValueList temp;
        _callBakcer->onHandle(_handler, _tagValueList);

        _tagValueList.swap(temp);
    }

protected:
    virtual void onNotify(tagValue const& val)
    {
        auto iter = _tagSet.find(val.name());
        if(iter == _tagSet.end()) {
            return;
        }

        _tagValueList.push_back(val);
    }

private:
    set<string> _tagSet;
    string _handler;
    tagValueList _tagValueList;

    CallBacker* _callBakcer;
};

// tag name -> tagCallBacker
typedef multimap< string, shared_ptr<tagCallBacker> > tagCallBackerMap;

class Provider
{
public:
    Provider();
    ~Provider();
    
    int start();
    void stop();

    void queryTags(tagInfoList& tags);
    void queryValues(string const& beginTime, string const& endTime, int valueCount, tagValuesMap& values);
    void subscribe( set<string> const& tags, string const& handler, CallBacker* callBacker );
    void unsubscribe( set<string> const& tags, string const& handler );

protected:
    tagCallBackerMap _tagCallBackerMap;
    jthread::JMutex _tagCallBackerMutex;

};

#endif


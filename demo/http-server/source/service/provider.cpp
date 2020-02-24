#include "provider.hpp"
#include <jthread/jmutexautolock.h>
#include <algorithm>

void mockTags( list< tagInfo >& tags );
void mockValues(list<tagValue>& values);
void mockTagsValues(tagValuesMap& values);

Provider::Provider()
{

}

Provider::~Provider()
{

}

int Provider::start()
{
    return 0;
}

void Provider::stop()
{

}

void Provider::queryTags(tagInfoList& tags)
{
    mockTags(tags);
}

void Provider::queryValues(string const& beginTime, string const& endTime, int valueCount, tagValuesMap& values)
{
    mockTagsValues(values);
}

void Provider::subscribe(set<string> const& tags, string const& handler, CallBacker* callBacker)
{
    jthread::JMutexAutoLock lock(_tagCallBackerMutex);
    auto iter = tags.begin();
    for (; iter != tags.end(); ++iter) {
        auto range = _tagCallBackerMap.equal_range(*iter);
        if (range.first == end(_tagCallBackerMap)) {
            shared_ptr<tagCallBacker> ptr(new tagCallBacker(tags, handler, callBacker));
            _tagCallBackerMap.insert(make_pair(*iter, ptr));

            continue;
        }

        bool find = false;
        for (auto it = range.first; it != range.second; ++it) {
            if( it->second->handler() == handler) {
                find = true;
                break;
            }
        }

        if(!find){
            shared_ptr<tagCallBacker> ptr(new tagCallBacker(tags, handler, callBacker));
            _tagCallBackerMap.insert(make_pair(*iter, ptr));
        }
    }
}

void Provider::unsubscribe(set<string> const& tags, string const& handler)
{
    jthread::JMutexAutoLock lock(_tagCallBackerMutex);
    auto iter = tags.begin();
    for (; iter != tags.end(); ++iter){
        auto range = _tagCallBackerMap.equal_range(*iter);
        if (range.first == end(_tagCallBackerMap)) {
            continue;
        }

        for (auto it = range.first; it != range.second; ++it)
        {
            if( it->second->handler() == handler) {
                _tagCallBackerMap.erase(it);
                break;
            }
        }
    }
}
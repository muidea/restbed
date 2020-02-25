#include "provider.hpp"
#include <unistd.h>
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
    _runningFlag = true;

    return JThread::Start();
}

void Provider::stop()
{
    _runningFlag = false;

    JThread::Kill();
}

void Provider::queryTags(tagInfoList& tags)
{
    mockTags(tags);
}

void Provider::queryValues(string const& beginTime, string const& endTime, int valueCount, tagValuesMap& values)
{
    mockTagsValues(values);
}

void Provider::subscribe(string const& handler, set<string> const& tags, CallBacker* callBacker)
{
    jthread::JMutexAutoLock lock(_handlerCallBackerMutex);
    
    tagCallBackerPtr curCallBacker(new tagCallBacker(tags, handler, callBacker));
    _handlerCallBackerMap[handler] = curCallBacker;
}

void Provider::unsubscribe(string const& handler)
{
    jthread::JMutexAutoLock lock(_handlerCallBackerMutex);
    _handlerCallBackerMap.erase(handler);
}

void* Provider::Thread()
{
    JThread::ThreadStarted();
    
    while (_runningFlag)
    {
        sleep(1);
        tagValueList values;
        mockValues(values);

        handlerCallBackerMap handlerCallBackerMap;
        {
            jthread::JMutexAutoLock lock(_handlerCallBackerMutex);
            auto iter = values.begin();
            for (; iter != values.end(); ++iter) {
                for (auto it = _handlerCallBackerMap.begin(); it != _handlerCallBackerMap.end(); ++it) {
                    if (it->second->onNotify(*iter)){
                        handlerCallBackerMap[it->first] = it->second;
                    }
                }
            }
        }

        auto it = handlerCallBackerMap.begin();
        for (; it != handlerCallBackerMap.end(); ++it ) {
            it->second->dispatch();
        }
    }

}


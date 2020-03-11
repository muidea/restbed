#include <list>
#include "tag.hpp"
#include "value.hpp"

using namespace std;

void mockTags( list< tagInfo >& tags )
{
    tagInfo t1("tag001", "tag001 desc", "w", 3);
    tags.push_back(t1);

    tagInfo t2("tag002", "tag002 desc", "w", 12);
    tags.push_back(t2);

    tagInfo t3("tag003", "tag003 desc", "w", 1);
    tags.push_back(t3);

     tagInfo t4("tag004", "tag004 desc", "w", 105);
    tags.push_back(t4);
}

void mockValues(list<tagValue>& values)
{
    tagValue v1("tag001", 12, 0, 1234);
    values.push_back(v1);

    tagValue v2("tag002", 23.456, 0, 2343);
    values.push_back(v2);

    tagValue v3("tag003", true, 0, 3454);
    values.push_back(v3);

    tagValue v4("tag004", "test string", 0, 1213);
    values.push_back(v4);
}

void mockTagsValues(tagValuesMap& values)
{
    tagValueList tag1List;
    tagValue v1("tag001", 12, 0, 1234);
    tag1List.push_back(v1);
    values["tag001"] = tag1List;

    tagValueList tag2List;
    tagValue v2("tag002", 23.456, 0, 2343);
    tag2List.push_back(v2);
    values["tag002"] = tag2List;

    tagValueList tag3List;
    tagValue v3("tag003", true, 0, 3454);
    tag3List.push_back(v3);
    values["tag003"] = tag3List;

    tagValueList tag4List;
    tagValue v4("tag004", "test string", 0, 1213);
    tag4List.push_back(v4);
    values["tag004"] = tag4List;
}

#include <list>
#include "tag.hpp"
#include "value.hpp"

using namespace std;

void mockTags( list< tagInfo >& tags )
{
    tagInfo t1("tag001", "tag001 desc", "w", 1);
    tags.push_back(t1);

    tagInfo t2("tag002", "tag002 desc", "w", 2);
    tags.push_back(t2);

    tagInfo t3("tag003", "tag003 desc", "w", 3);
    tags.push_back(t3);

     tagInfo t4("tag004", "tag004 desc", "w", 4);
    tags.push_back(t4);
}

void mockValues(list<tagValue>& values)
{
    tagValue v1("tag001", 12, 0, "2020年02月21日 11:51:33");
    values.push_back(v1);

    tagValue v2("tag002", 23.456, 0, "2020年02月21日 11:51:33");
    values.push_back(v2);

    tagValue v3("tag003", true, 0, "2020年02月21日 11:51:33");
    values.push_back(v3);

    tagValue v4("tag004", "test string", 0, "2020年02月21日 11:51:33");
    values.push_back(v4);
}

# include "stdafx.h"
# include <nnt/Foundation+NNT.h>

# include <nnt/TL/foundation/iterator.hpp>
# include <nnt/TL/foundation/rbtree.hpp>
# include <nnt/TL/foundation/list.hpp>
# include <nnt/TL/foundation/vector.hpp>
# include <nnt/TL/foundation/string.hpp>
# include <nnt/TL/foundation/map.hpp>

int _tmain(int argc, _TCHAR* argv[])
{
    NNT_USINGNAMESPACE;

    typedef foundation::map<int, float> map_t;

    map_t obj;

    for (int i = 0; i < 10; ++i)
    {
        obj.insert(foundation::make_pair<map_t::value_type>(i, i));
    }

    map_t::iterator found = obj.find(5);
    if (found != obj.end())
    {
        trace_msg("found!");
    }

    obj.erase(found);
    found = obj.find(5);
    if (found == obj.end())
    {
        trace_msg("removed");
    }

    //for (map_t::iterator iter = obj.begin(); iter != obj.end(); ++iter)
    {

    }

	return 0;
}



# include "stdafx.h"
# include <nnt/Foundation+NNT.h>

# include <nnt/TL/foundation/iterator.hpp>
# include <nnt/TL/foundation/stack.hpp>
# include <nnt/TL/foundation/rbtree.hpp>
# include <nnt/TL/foundation/list.hpp>
# include <nnt/TL/foundation/vector.hpp>
# include <nnt/TL/foundation/string.hpp>
# include <nnt/TL/foundation/map.hpp>

class CA
{
public:
    int v;
};

class CB
{
};

int _tmain(int argc, _TCHAR* argv[])
{
    NNT_USINGNAMESPACE;    

    {
        typedef foundation::vector<int> vec_t;
        vec_t vec;
        vec << 1 << 2 << 3 << 4;
        int val = vec[6];
        for (vec_t::iterator iter = vec.begin(); iter != vec.end(); ++iter)
        {
            val = *iter;
            if (val == 4)
                vec << 5;
        }
    }

    {
        typedef foundation::list<int> list_t;
        list_t lst;
        lst << 1 << 2 << 3;
        for (list_t::iterator iter = lst.begin(); iter != lst.end(); ++iter)
        {
            int val = *iter;
            if (val == 2)
            {
                lst.erase(iter++);
                break;
            }
        }
    }

    {
        typedef foundation::stack<int> stack_t;
        stack_t stk;
        stk << 1 << 2 << 3;
        while (!stk.is_empty())
        {
            int val;
            stk >> val;
        }
    }

    {
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

        core::vector<float> values = obj.all_values<core::vector<float> >();
        core::vector<int> keys = obj.all_values<core::vector<int> >();

    }

	return 0;
}


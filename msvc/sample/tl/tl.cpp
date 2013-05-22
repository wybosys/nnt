
# include "stdafx.h"
# include <nnt/Foundation+NNT.h>

# include <nnt/TL/foundation/rbtree.hpp>
# include <nnt/TL/foundation/list.hpp>
# include <nnt/TL/foundation/vector.hpp>
# include <nnt/TL/foundation/string.hpp>

int _tmain(int argc, _TCHAR* argv[])
{
    typedef nnt::foundation::rbtree<int, float> tree_t;

    tree_t obj;

    for (int i = 0; i < 100; ++i)
    {
        obj.insert(i, i);
    }

    float val = *obj.lookup(50);
    obj.remove(10);
    obj.lookup(10);

	return 0;
}


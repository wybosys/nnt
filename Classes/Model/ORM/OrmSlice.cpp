
# include "Core.h"
# include "OrmSlice.hpp"

NNT_BEGIN_ORM

RSlice::RSlice()
{
    fields["_id"] = type::integer(0, 0, true);
    fields.add_key("_id");
}

RSlice::~RSlice()
{
    
}

NNT_END_ORM


# ifndef __NNT_ORM_SLICE_24D971157ABC4273909DFBA8C7656AFE_H_INCLUDED
# define __NNT_ORM_SLICE_24D971157ABC4273909DFBA8C7656AFE_H_INCLUDED

# include "OrmObject.hpp"
# include "OrmBlock.hpp"

NNT_BEGIN_HEADER_ORM

class Slice
{
public:
    
    core::string name;
    
};

class RSlice
: public Slice
{
public:
    
    RSlice();
    ~RSlice();
    
    Fields fields;
    
};

NNT_END_HEADER_ORM

# endif

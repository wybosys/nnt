
# ifndef __WSI_ORM_SLICE_24D971157ABC4273909DFBA8C7656AFE_H_INCLUDED
# define __WSI_ORM_SLICE_24D971157ABC4273909DFBA8C7656AFE_H_INCLUDED

# include "OrmObject.hpp"
# include "OrmBlock.hpp"

WSI_BEGIN_HEADER_ORM

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

WSI_END_HEADER_ORM

# endif

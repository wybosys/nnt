
# ifndef __WSI_ORM_CUBE_7B828FFC5363420DB33972AFD82C1824_H_INCLUDED
# define __WSI_ORM_CUBE_7B828FFC5363420DB33972AFD82C1824_H_INCLUDED

# include "OrmObject.hpp"

WSI_BEGIN_HEADER_ORM

class ICube
: public RefObject
{
public:
    
    virtual bool is_expired() const = 0;
    
};

class Cube
{
    
public:
    
    Cube();
    virtual ~Cube();
    
    int version;
    
};

class SqlCube
: public Cube
{
    
};

WSI_END_HEADER_ORM

# endif

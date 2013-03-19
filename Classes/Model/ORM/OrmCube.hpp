
# ifndef __NNT_ORM_CUBE_7B828FFC5363420DB33972AFD82C1824_H_INCLUDED
# define __NNT_ORM_CUBE_7B828FFC5363420DB33972AFD82C1824_H_INCLUDED

# include "OrmObject.hpp"

NNT_BEGIN_HEADER_ORM

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

NNT_END_HEADER_ORM

# endif

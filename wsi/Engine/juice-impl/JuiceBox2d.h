
# ifndef __JUICE_BOX2D_319A0EE4E2764FECA8753884A5AA7EC6_H_INCLUDED
# define __JUICE_BOX2D_319A0EE4E2764FECA8753884A5AA7EC6_H_INCLUDED

# include "../Juice.hpp"

JUICEIMPL_BEGIN

WSIDECL_PRIVATE_HEAD_CXX(PhysicsBox2d);

class PhysicsBox2d
: public Physics<PhysicsBox2d, Types3d>
{
    WSIDECL_PRIVATE_CXX(PhysicsBox2d);
    
    typedef Physics<PhysicsBox2d, Types3d> super;
    
public:
    
    typedef super::bounding_type bounding_type;
    typedef super::position_type position_type;
    
    PhysicsBox2d();
    ~PhysicsBox2d();
    
public:
    
    void set_gravity(real y, real x = 0);
    
    void prepare();
    void update();
    
    phyobj_t* add_box(bounding_type const&, phyparam_t const&);
    
    position_type position(phyobj_t const*) const;
    real angle(phyobj_t const*) const;
    
};

JUICEIMPL_END

# endif
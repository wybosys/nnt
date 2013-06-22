
# ifndef __JUICE_PHYSICS_AA480BAF29B64715AE9816D0D8B3D21E_H_INCLUDED
# define __JUICE_PHYSICS_AA480BAF29B64715AE9816D0D8B3D21E_H_INCLUDED

JUICE_BEGIN

typedef enum {
    PHY_SHAPETYPE_POLYGON = 1,
} PHY_SHAPETYPE;

typedef struct {} phyobj_t;

class phyparam_t {
    
public:    
    phyparam_t()
    : density(1), friction(0), restitution(0)
    {
        PASS;
    }
    
    //! density. kg/m^2.
    real density;
    
    //! friction.
    real friction;
    
    //! restitution.
    real restitution;
    
};

template <typename classT, typename typesT>
class Physics
: public RefObject<classT>
{
    
public:
    
    typedef typename typesT::vertex_type position_type;
    typedef typename typesT::bounding_type bounding_type;
    
    Physics()
    : velocity(0), offset(0), time(0)
    {
        PASS;
    }
    
    ~Physics()
    {
        PASS;
    }
    
    //! set gravity.
    void set_gravity(real y, real x = 0)
    {
        PASS;
    }
    
public:
    
    //! prepare physics world.
    void prepare()
    {
        PASS;
    }
    
    //! update.
    void update()
    {
        PASS;
    }
    
    //! add a box.
    phyobj_t* add_box(bounding_type const& box, real density, real friction)
    {
        PASS;
    }
    
    //! get value.
    position_type position(phyobj_t const*) const
    {
        return position_type();
    }
    
    //! get angle.
    real angle(phyobj_t const*) const
    {
        return 0;
    }
    
public:
    
    //! ground box.
    bounding_type box;
    
    //! velocity.
    real velocity;
    
    //! offset.
    real offset;
    
    //! time.
    real time;
    
};

JUICE_END

# endif
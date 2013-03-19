
# ifndef __JUICE_LIGHT_D4F4E8C2C41A4329B46CBE40C17FD122_H_INCLUDED
# define __JUICE_LIGHT_D4F4E8C2C41A4329B46CBE40C17FD122_H_INCLUDED

JUICE_BEGIN

template <typename implT, typename typesT>
class Light
{
    typedef Light<implT, typesT> self_type;
    
public:
    
    typedef typename typesT::vertex_type vertex_type;
    typedef typename typesT::color_type color_type;
    
    Light()
    {
        PASS;
    }
    
    ~Light()
    {
        PASS;    
    }
    
    template <typename driverT>
    void pack(driverT* drv)
    {
        drv->set_light(jimpl);
    }
    
    //! index of this light assigned while rendering.
    uint index;
    
    //! position of this light.
    vertex_type position;
    
    //! color for ambient.
    color_type ambient;
    
    //! color for diffuse.
    color_type diffuse;
    
    //! color for specular.
    color_type specular;
    
};

JUICE_END

# endif
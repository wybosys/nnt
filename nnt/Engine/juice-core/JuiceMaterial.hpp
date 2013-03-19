
# ifndef __JUICE_MATERIAL_84BFDE9B1EA04C76B40160CBC2E21FBC_H_INCLUDED
# define __JUICE_MATERIAL_84BFDE9B1EA04C76B40160CBC2E21FBC_H_INCLUDED

JUICE_BEGIN

template <typename implT, typename typesT>
class Material
{
    typedef Material<implT, typesT> self_type;
    
public:
    
    typedef typename typesT::color_type color_type;
    
    Material()
    : lightable(true),
    deepness(true)
    {
        PASS;
    }
    
    ~Material()
    {
        PASS;
    }
    
    //! if can light on, default is true.
    bool lightable;
    
    //! color.
    color_type color;

    //! deepness, default is true.
    bool deepness;
};

JUICE_END

# endif
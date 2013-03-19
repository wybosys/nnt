
# ifndef __WSI_NSLOCALE_47DC1E57E30549BBB5676940356D5588_H_INCLUDED
# define __WSI_NSLOCALE_47DC1E57E30549BBB5676940356D5588_H_INCLUDED

WSI_BEGIN_HEADER_OBJC


WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ns)

class Calendar
: public ns::Object<NSCalendar>
{
    
};

class Locale
: public ns::Object<NSLocale>
{
    typedef ns::Object<NSLocale> super;
    
public:
    
    Locale();
    Locale(id);
    ~Locale();
    
    ns::String identifier() const;
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif

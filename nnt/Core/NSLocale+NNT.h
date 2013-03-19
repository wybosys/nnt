
# ifndef __NNT_NSLOCALE_47DC1E57E30549BBB5676940356D5588_H_INCLUDED
# define __NNT_NSLOCALE_47DC1E57E30549BBB5676940356D5588_H_INCLUDED

NNT_BEGIN_HEADER_OBJC


NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ns)

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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif

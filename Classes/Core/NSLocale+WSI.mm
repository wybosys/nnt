
# import "Core.h"
# import "NSLocale+NNT.h"

NNT_BEGIN_OBJC

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(ns)

Locale::Locale()
{
    
}

Locale::Locale(id obj)
: super(obj)
{
    
}

Locale::~Locale()
{
    
}

ns::String Locale::identifier() const
{
    return this->_self.localeIdentifier;
}

NNT_END_NS
NNT_END_CXX

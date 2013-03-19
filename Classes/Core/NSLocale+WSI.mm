
# import "Core.h"
# import "NSLocale+WSI.h"

WSI_BEGIN_OBJC

WSI_END_OBJC

WSI_BEGIN_CXX
WSI_BEGIN_NS(ns)

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

WSI_END_NS
WSI_END_CXX

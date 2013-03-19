
# include "Core.h"
# include "XmppObject.h"

WSI_BEGIN_CXX
WSI_BEGIN_NS(xmpp)

Object::Object()
{
    
}

Object::~Object()
{
    
}

bool Object::save(core::data & da) const
{
    return true;
}

bool Object::load(xmlnode_t const*)
{
    return false;
}

bool Object::append(xmlnode_t *node) const
{
    return false;
}

bool StringObject::save(core::data& da) const
{
    da = core::type_cast<core::data>(str);
    return true;
}

bool StringObject::load(xmlnode_t const* node)
{
    str = node->value;
    return true;
}

WSI_END_NS
WSI_END_CXX
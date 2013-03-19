
# include "Core.h"
# include "XmppCompression.h"

XMPPCORE_BEGIN

Compression::Compression()
: _compression(COMPRESSION_UNKNOWN)
{
    
}

bool Compression::couldload(const xmlnode_t * node)
{
    if (node->name == "compression" &&
        node->ns == "http://jabber.org/features/compress")
    {
        return true;
    }
    return false;
}

bool Compression::load(const xmlnode_t * node)
{
    for (xmlnode_t const* each = node->first;
         each;
         each = each->next)
    {
        if (each->value == "zlib")
            MASK_SET(COMPRESSION_ZLIB, _compression);
    }
    return true;
}

void Compression::process(Client&)
{
    
}

XMPPCORE_END
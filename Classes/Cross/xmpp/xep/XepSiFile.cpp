
# include "Core.h"
# include "XepSiFile.h"

XMPPXEP_BEGIN

SiFile::SiFile()
{
    
}

SiFile::~SiFile()
{
    
}

bool SiFile::couldload(xmlnode_t const* node)
{
    return false;
}

bool SiFile::save(core::data &da) const
{
    return false;
}

XMPPXEP_END

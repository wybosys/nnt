
# include "Core.h"
# include "XepSiPub.h"

XMPPXEP_BEGIN

SiPub::SiPub()
{
    
}

SiPub::~SiPub()
{
    
}

bool SiPub::append(xmlnode_t *node) const
{
    xmlnode_t* sipub = node->add_node("sipub");
    sipub->ns = "http://jabber.org/protocol/si-pub";
    sipub->add_attr("id", idr);

    if (mimetype.empty() == false)
        sipub->add_attr("mime-type", mimetype);
    
    if (profile.empty() == false)
        sipub->add_attr("profile", profile);
    
    if (file.is_used())
    {
        xmlnode_t* nf = sipub->add_node("file");
        nf->ns = "http://jabber.org/protocol/si/profile/file-transfer";
        nf->add_attr("name", file->name);
        if (file->size)
            nf->add_attr("size", core::tostr(file->size));
    }
    
    return true;
}

XMPPXEP_END

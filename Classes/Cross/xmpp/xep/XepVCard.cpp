
# include "Core.h"
# include "XepVCard.h"
# include "../XmppIMClient.h"
# include "../../../Security/BaseN+WSI.h"

XMPPXEP_BEGIN

VCard::VCard()
{
    type = cor::IQ_GET;
    vcard = new cross::VCard;
}

VCard::~VCard()
{
    safe_drop(vcard);
}

bool VCard::couldload(xmlnode_t const* node)
{
    return
    node->name == "vCard" &&
    node->ns == "vcard-temp";
}

bool VCard::load(xmlnode_t const* node)
{
    vcard->clear();
    
    xmlnode_t const* found = NULL, *temp = NULL;
    
    // find name.
    if ((found = node->node("N")))
    {
        if ((temp = found->node("FAMILY")))
        {
            vcard->name.family = temp->value;
        }
        
        if ((temp = found->node("GIVEN")))
        {
            vcard->name.name = temp->value;
        }
        
        if ((temp = found->node("MIDDLE")))
        {
            vcard->name.middle = temp->value;
        }
    }
    
    if ((found = node->node("NICKNAME")))
    {
        vcard->name.nick = found->value;
    }
    
    if ((found = node->node("TITLE")))
    {
        vcard->name.title = found->value;
    }
    
    // bd.
    if ((found = node->node("BDAY")))
    {
        vcard->birthday = found->value;
    }
    
    // orgs.
    xmlnode_t::const_nodes_result founds = node->nodes("ORG");
    if (founds.size())
    {
        for (xmlnode_t::const_nodes_result::const_iterator each = founds.begin();
             each != founds.end();
             ++each)
        {
            xmlnode_t const* node = *each;
            vcard->orangizations.push_back(cross::vcard::Organization());
            cross::vcard::Organization& ref = vcard->orangizations.back();
            
            if ((found = node->node("ORGNAME")))
            {
                ref.name = found->value;
            }
            
            if ((found = node->node("ORGUNIT")))
            {
                ref.unit = found->value;
            }
        }
    }
    
    // emails.
    founds = node->nodes("EMAIL");
    if (founds.size())
    {
        for (xmlnode_t::const_nodes_result::const_iterator each = founds.begin();
             each != founds.end();
             ++each)
        {
            xmlnode_t const* node = *each;
            vcard->emails.push_back(cross::vcard::Email());
            cross::vcard::Email& ref = vcard->emails.back();
            
            if ((found = node->node("USERID")))
            {
                ref.email = found->value;
            }
        }
    }
    
    // voices.
    founds = node->nodes("TEL");
    if (founds.size())
    {
        for (xmlnode_t::const_nodes_result::const_iterator each = founds.begin();
             each != founds.end();
             ++each)
        {
            xmlnode_t const* node = *each;
            if (node->children.size() < 3)
                continue;
            
            node = node->first;
            cross::vcard::Contact* ct = vcard->contact_bytype(node->name);
            if (ct == NULL)
            {
                cross::vcard::Contact obj(node->name);
                vcard->contacts.push_back(obj);
                ct = vcard->contact_bytype(node->name);
            }
            
            node = node->next;
            cross::vcard::Phone phone;
            phone.type = node->name;
            node = node->next;
            phone.number = node->value;
            ct->phones.push_back(phone);
        }
    }
    
    // mobiles.
    founds = node->nodes("MOBILE");
    if (founds.size())
    {
        for (xmlnode_t::const_nodes_result::const_iterator each = founds.begin();
             each != founds.end();
             ++each)
        {
            xmlnode_t const* node = *each;
            vcard->mobiles.push_back(cross::vcard::Mobile());
            cross::vcard::Mobile& ref = vcard->mobiles.back();
            
            ref.number = node->value;
        }
    }
    
    // desc.
    if (( found = node->node("DESC")))
    {
        vcard->desc = found->value;
    }
    
    // photo.
    if (( found = node->node("PHOTO")))
    {
        xmlnode_t const* ty = found->node("TYPE");
        xmlnode_t const* da = found->node("BINVAL");
        
        if (ty && da)
        {
            cross::vcard::Photo* photo = new cross::vcard::Photo;
            vcard->photo = photo;
            
            // read data.
            photo->type = cross::mime::MimeFromString(ty->value);
            base64::decode(da->value, photo->raw);
        }
    }
    
    return super::load(node);
}

void VCard::process(Client& cli)
{
    eventobj_t evt;
    evt.data = this;
    cli.emit(kSignalGotVCard, evt);
}

bool VCard::save(core::data &da) const
{
    cor::IQ iq;
    to_iq(iq);
    iq.to.resource.clear();
    
    iq.root.add_node("vcard")->ns = "vcard-temp";
    
    bool suc = iq.save(da);
    
    return suc;
}

VCardUpdate::VCardUpdate()
{
    type = cor::IQ_SET;
}

void VCardUpdate::set(cross::VCard *card)
{
    refobj_set(this->vcard, card);
}

bool VCardUpdate::save(core::data &da) const
{
    cor::IQ iq;
    to_iq(iq);
    iq.to.clear();
    iq.from.clear();
    
    xmlnode_t* node = NULL;
    
    // add node.
    xmlnode_t* root = iq.root.add_node("vCard");
    root->ns = "vcard-temp";
    
    node = root->add_node("N");
    node->add_node("FAMILY", vcard->name.family);
    node->add_node("GIVEN", vcard->name.name);
    node->add_node("MIDDLE", vcard->name.middle);
    
    root->add_node("NICKNAME", vcard->name.nick);
    root->add_node("TITLE", vcard->name.title);
    root->add_node("BDAY", vcard->birthday);
    root->add_node("DESC", vcard->desc);
    root->add_node("JABBERID", to.bare());
    
    for (cross::VCard::orangizations_type::const_iterator each = vcard->orangizations.begin();
         each != vcard->orangizations.end();
         ++each)
    {
        node = root->add_node("ORG");
        node->add_node("ORGNAME", each->name);
        node->add_node("ORGUNIT", each->unit);
    }
    
    for (cross::VCard::emails_type::const_iterator each = vcard->emails.begin();
         each != vcard->emails.end();
         ++each)
    {
        node = root->add_node("EMAIL");
        node->add_node("USERID", each->email);
    }
    
    for (cross::VCard::contacts_type::const_iterator each = vcard->contacts.begin();
         each != vcard->contacts.end();
         ++each)
    {
        for (cross::vcard::Contact::phones_type::const_iterator iter = each->phones.begin();
             iter != each->phones.end();
             ++iter)
        {
            node = root->add_node("TEL");
            node->add_node(each->type);
            node->add_node(iter->type);
            node->add_node("NUMBER", iter->number);
        }
    }
    
    for (cross::VCard::mobiles_type::const_iterator each = vcard->mobiles.begin();
         each != vcard->mobiles.end();
         ++each)
    {
        node = root->add_node("MOBILE", each->number);
    }
    
    return iq.save(da);
}

// --------------------------------------------------- V4

VCardV4::VCardV4()
{
    type = cor::IQ_GET;
}

bool VCardV4::couldload(xmlnode_t const*)
{
    return false;
}

bool VCardV4::load(xmlnode_t const*)
{
    return false;
}

void VCardV4::process(Client&)
{
    PASS;
}

bool VCardV4::save(core::data &da) const
{
    cor::IQ iq;
    to_iq(iq);
    
    iq.root.add_node("vcard")->ns = "urn:ietf:params:xml:ns:vcard-4.0";
    
    bool suc = iq.save(da);
    
    return suc;
}

XMPPXEP_END
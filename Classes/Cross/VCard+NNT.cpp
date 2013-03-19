
# include "Core.h"
# include "VCard+NNT.h"
# include "../Parser/XmlParser.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(cross)

using namespace ::nnt::parser;

VCard::VCard()
: photo(NULL)
{
    PASS;
}

VCard::~VCard()
{
    safe_drop(photo);
}

void VCard::clear()
{
    name.clear();
    birthday.clear();
    orangizations.clear();
    contacts.clear();
    emails.clear();
    desc.clear();
    mobiles.clear();
    zero_drop(photo);
}

bool tostr(VCard const& cd, core::string& str)
{
    XmlNode root("VCARD");
    
    // add name
    XmlNode* node = root.add_node("NAME");
    node->add_node("FAMILY", cd.name.family);
    node->add_node("NAME", cd.name.name);
    node->add_node("MIDDLE", cd.name.middle);
    
    if (!cd.name.nick.empty())
        node->add_node("NICK", cd.name.nick);
    if (!cd.name.title.empty())
        node->add_node("TITLE", cd.name.title);
    
    // birthday.
    if (!cd.birthday.empty())
        root.add_node("BIRTHDAY", cd.birthday);
    
    // orangizations.
    if (cd.orangizations.size())
    {
        node = root.add_node("ORANGIZATION");
        for (VCard::orangizations_type::const_iterator each = cd.orangizations.begin();
             each != cd.orangizations.end();
             ++each)
        {
            XmlNode* item = node->add_node("ITEM");
            item->add_node("NAME", each->name);
            item->add_node("UNIT", each->unit);
        }
    }
    
    // contacts.
    if (cd.contacts.size())
    {
        node = root.add_node("CONTACT");
        for (VCard::contacts_type::const_iterator each = cd.contacts.begin();
             each != cd.contacts.end();
             ++each)
        {
            node = node->add_node("ITEM");
            node->add_node("TYPE", each->type);
    
            for (cross::vcard::Contact::phones_type::const_iterator iter = each->phones.begin();
                 iter != each->phones.end();
                 ++iter)
            {
                XmlNode* item = node->add_node("PHONE");
                item->add_node("TYPE", iter->type);
                item->add_node("NUMBER", iter->number);
            }
        }
    }
    
    // mobile.
    if (cd.mobiles.size())
    {
        node = root.add_node("MOBILE");
        for (VCard::mobiles_type::const_iterator each = cd.mobiles.begin();
             each != cd.mobiles.end();
             ++each)
        {
            XmlNode* item = node->add_node("ITEM");
            item->add_node("NUMBER", each->number);
        }
    }
    
    // email.
    if (cd.emails.size())
    {
        node = root.add_node("EMAIL");
        for (VCard::emails_type::const_iterator each = cd.emails.begin();
             each != cd.emails.end();
             ++each)
        {
            XmlNode* item = node->add_node("ITEM");
            item->add_node("ADDRESS", each->email);
        }
    }
    
    // photo.
    if (cd.photo && !cd.photo->name.empty())
    {
        node = root.add_node("PHOTO");
        node->add_node("NAME", cd.photo->name);
        node->add_node("MIME", mime::MimeToString(cd.photo->type));
    }

    // save to string.
    str = root.to_string();
    return true;
}

bool tocard(core::string const& str, VCard& cd)
{
    // init.
    cd.clear();
    
    // load from xml.
    XmlDocument doc;
    if (!doc.parse_string(str) || !doc.root())
        return false;
    
    XmlNode const& root = *doc.root();
    if (root.name != "VCARD")
        return false;
    XmlNode const* node = NULL, *temp = NULL;
    
    // find name.
    if ((node = root.node("NAME")))
    {
        if ((temp = node->node("FAMILY")))
            cd.name.family = temp->value;
        if ((temp = node->node("NAME")))
            cd.name.name = temp->value;
        if ((temp = node->node("MIDDLE")))
            cd.name.middle = temp->value;
        if ((temp = node->node("NICK")))
            cd.name.nick = temp->value;
        if ((temp = node->node("TITLE")))
            cd.name.title = temp->value;
    }
    
    // find birday.
    if ((node = root.node("BIRTHDAY")))
        cd.birthday = node->value;
    
    // find orangizations.
    if ((node = root.node("ORANGIZATION")))
    {
        node = node->first;
        while (node)
        {
            if (node->name == "ITEM")
            {
                cross::vcard::Organization item;
                if ((temp = node->node("NAME")))
                    item.name = temp->value;
                if ((temp = node->node("UNIT")))
                    item.unit = temp->value;
                cd.orangizations << item;
            }
            node = node->next;
        }
    }
    
    // find contact.
    if ((node = root.node("CONTACT")))
    {
        node = node->first;
        while (node)
        {
            if (node->name == "ITEM")
            {
                cross::vcard::Contact ct;
                if ((temp = node->node("TYPE")))
                    ct.type = temp->value;
                
                XmlNode::const_nodes_result phones = node->nodes("PHONE");
                for (XmlNode::const_nodes_result::const_iterator each = phones.begin();
                     each != phones.end();
                     ++each)
                {
                    cross::vcard::Phone ph;
                    if ((temp = (*each)->node("TYPE")))
                        ph.type = temp->value;
                    if ((temp = (*each)->node("NUMBER")))
                        ph.number = temp->value;
                    ct.phones << ph;
                }
                
                cd.contacts << ct;
            }
            node = node->next;
        }
    }
    
    // find mobile.
    if ((node = root.node("MOBILE")))
    {
        node = node->first;
        while (node)
        {
            if (node->name == "ITEM")
            {
                cross::vcard::Mobile item;
                if ((temp = node->node("NUMBER")))
                    item.number = temp->value;
                cd.mobiles << item;
            }
            node = node->next;
        }
    }
    
    // find email.
    if ((node = root.node("EMAIL")))
    {
        node = node->first;
        while (node)
        {
            if (node->name == "ITEM")
            {
                cross::vcard::Email item;
                if ((temp = node->node("ADDRESS")))
                    item.email = temp->value;
                cd.emails << item;
            }
            node = node->next;
        }
    }
    
    // find photo.
    if ((node = root.node("PHOTO")))
    {
        if (cd.photo == NULL)
            cd.photo = new cross::vcard::Photo;
        
        if ((temp = node->node("NAME")))
            cd.photo->name = temp->value;
        if ((temp = node->node("MIME")))
            cd.photo->type = mime::MimeFromString(temp->value);
    }
    
    return true;
}

vcard::Contact* VCard::contact_bytype(core::string const& tp)
{
    for (contacts_type::iterator each = contacts.begin();
         each != contacts.end();
         ++each)
    {
        if (each->type == tp)
            return &*each;
    }
    return NULL;
}

NNT_END_NS
NNT_END_CXX

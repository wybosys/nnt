
# ifndef __WSI_CROSS_VCARD_C4D94BE517294DE79D0973654DC2A84C_H_INCLUDED
# define __WSI_CROSS_VCARD_C4D94BE517294DE79D0973654DC2A84C_H_INCLUDED

# include "Mime+WSI.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(cross)
WSI_BEGIN_NS(vcard)

class Name
{
public:
    
    void clear()
    {
        family.clear();
        name.clear();
        middle.clear();
        nick.clear();
        title.clear();
    }
    
    core::string family, name, middle, nick, title;
    
};

class Organization
{
public:
    
    Organization()
    {
        PASS;
    }
    
    Organization(core::string const& val0, core::string const& val1)
    : name(val0), unit(val1)
    {
        PASS;
    }
    
    core::string name, unit;
    
};

class Address
{
public:
    
    Address()
    {
        PASS;
    }
    
    core::string country;
    
};

class Phone
{
public:
    
    Phone()
    {
        PASS;
    }
    
    Phone(core::string const& str)
    : type(str)
    {
        PASS;
    }
  
    core::string type, number;
    
};

class Contact
{
public:
    
    Contact()
    {
        PASS;
    }
    
    Contact(core::string const& tp)
    : type(tp)
    {
        PASS;
    }
    
    //! type.
    core::string type;
    
    //! voice.
    typedef core::list<Phone> phones_type;
    phones_type phones;
    
    //! address.
    typedef core::list<Address> addresses_type;
    addresses_type addresses;
    
};

class Email
{
public:
    
    Email()
    {
        PASS;
    }
    
    Email(core::string const& val)
    : email(val)
    {
        PASS;
    }
    
    core::string email;
    
};

class Mobile
{
public:
    
    Mobile()
    {
        PASS;
    }
    
    Mobile(core::string const& val)
    : number(val)
    {
        PASS;
    }
    
    core::string number;
    
};

class Photo
: public RefObject
{
public:
    
    Photo()
    : type(mime::UNKNOWN)
    {
        PASS;
    }
    
    virtual ~Photo()
    {
        PASS;
    }
    
    //! mime type of data.
    mime::MimeType type;
    
    //! data of image.
    core::data raw;
    
    //! name of image.
    core::string name;
    
};

WSI_END_NS

WSICLASS(VCard);

class VCard
: public RefObject
{
public:
    
    VCard();
    virtual ~VCard();
    
    vcard::Name name;
    
    core::string birthday;
    
    typedef core::list<vcard::Organization> orangizations_type;
    orangizations_type orangizations;
    
    typedef core::list<vcard::Contact> contacts_type;
    contacts_type contacts;
    
    typedef core::list<vcard::Email> emails_type;
    emails_type emails;
    
    core::string desc;
    
    typedef core::list<vcard::Mobile> mobiles_type;
    mobiles_type mobiles;
    
    void clear();
    
    vcard::Photo* photo;
    
public:
    
    vcard::Contact* contact_bytype(core::string const&);
    
};

WSIAPI(bool) tostr(VCard const&, core::string&);
WSIAPI(bool) tocard(core::string const&, VCard&);

WSI_END_NS

WSI_BEGIN_NS(wtl)

template <>
inline_impl core::string type_cast<core::string, cross::VCard>(cross::VCard const& cd)
{
    core::string str;
    cross::tostr(cd, str);
    return str;
}

template <>
inline_impl cross::VCard type_cast<cross::VCard, core::string>(core::string const& str)
{
    cross::VCard cd;
    cross::tocard(str, cd);
    return cd;
}

WSI_END_NS

WSI_END_HEADER_CXX

# endif
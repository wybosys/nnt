
# include "Core.h"
# include "XmppJID.h"

XMPPCORE_BEGIN

Jid::Jid()
{
    PASS;
}

Jid::Jid(core::string const& str)
{
    set(str);
}

void Jid::set(core::string const& str)
{
    username = "";
    address = "";
    resource = "";
    
    core::regex_captured_t wh;
    static core::regex re("(\\S+)@(\\S+)/(\\S+)");
    re.capture(str, wh);
    if (wh.size())
    {
        username = wh[0][1];
        address = wh[0][2];
        resource = wh[0][3];
        return;
    }
    
    static core::regex re_nr("(\\S+)@(\\S+)");
    re_nr.capture(str, wh);
    if (wh.size())
    {
        username = wh[0][1];
        address = wh[0][2];
        resource = "";
        return;
    }
    
    /*
    uint npos = str.find_first_of('.');
    if (npos != core::string::npos)
    {
        username = core::string(str.begin(), str.begin() + npos);
        address = core::string(str.begin() + npos + 1, str.end());
        return;
    }
     */
    
    username = str;
}

void Jid::clear()
{
    username = "";
    address = "";
    resource = "";
}

core::string Jid::full() const
{
    if (username.empty())
        return "";
    core::string ret;
    if (address.empty())
        return username;
    ret = username + "@" + address;
    if (resource.empty())
        return ret;
    ret += "/" + resource;
    return ret;
}

core::string Jid::bare() const
{
    if (username.empty())
        return "";
    core::string ret;
    if (address.empty())
        return username;
    ret = username + "@" + address;
    return ret;
}

core::string Jid::domain() const
{
    core::string ret = address;
    if (resource.empty())
        return ret;
    ret += "/" + resource;
    return ret;
}

bool Jid::is_sameuser(Jid const& r) const
{
    return
    username == r.username &&
    address == r.address;
}

bool Jid::empty() const
{
    return
    username.empty() &&
    address.empty() &&
    resource.empty();
}

XMPPCORE_END
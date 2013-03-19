
# include "Core.h"
# include "XimIM.h"

XMPPIM_BEGIN

PresenceType PresenceTypeFromString(core::string const& str)
{
    PresenceType ret = PT_OFFLINE;
    if (str == "away")
        ret = PT_AWAY;
    else if (str == "chat")
        ret = PT_CHAT;
    else if (str == "dnd")
        ret = PT_DND;
    else if (str == "xa")
        ret = PT_XA;
    else if (str.empty())
        ret = PT_ONLINE;
    else if (str == "none")
        ret = PT_ONLINE;
    return ret;
}

core::string PresenceTypeToString(PresenceType pt)
{
    core::string ret;
    switch (pt)
    {
        case PT_AWAY: ret = "away"; break;
        case PT_CHAT: ret = "chat"; break;
        case PT_DND: ret = "dnd"; break;
        case PT_XA: ret = "xa"; break;
        case PT_NULL: ret = ""; break;
        default: break;
    }
    return ret;
}

MessageType MessageTypeFromString(core::string const& str)
{
    MessageType ret = MT_NULL;
    if (str == "chat")
        ret = MT_CHAT;
    else if (str == "error")
        ret = MT_ERROR;
    else if (str == "groupchat")
        ret = MT_GROUPCHAT;
    else if (str == "headline")
        ret = MT_HEADLINE;
    else if (str == "normal")
        ret = MT_NORMAL;
    return ret;
}

core::string MessageTypeToString(MessageType mt)
{
    core::string ret;
    switch (mt)
    {
        case MT_CHAT: ret = "chat"; break;
        case MT_ERROR: ret = "error"; break;
        case MT_GROUPCHAT: ret = "groupchat"; break;
        case MT_HEADLINE: ret = "headline"; break;
        case MT_NORMAL: ret = "normal"; break;
        default: break;
    }
    return ret;
}

XMPPIM_END
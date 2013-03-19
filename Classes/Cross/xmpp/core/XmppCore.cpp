
# include "Core.h"
# include "XmppCore.h"

XMPPCORE_BEGIN

IqType IqTypeFromString(core::string const& str)
{
    IqType ret = IQ_UNKNOWN;
    if (str == "get")
        ret = IQ_GET;
    else if (str == "set")
        ret = IQ_SET;
    else if (str == "result")
        ret = IQ_RESULT;
    else if (str == "error")
        ret = IQ_ERROR;
    return ret;
}

core::string IqTypeToString(IqType it)
{
    core::string ret;
    
    switch (it)
    {
        case IQ_GET: ret = "get"; break;
        case IQ_SET: ret = "set"; break;
        case IQ_RESULT: ret = "result"; break;
        case IQ_ERROR: ret = "error"; break;
        default: break;        
    }
    
    return ret;
}

ErrorCode ErrorCodeFromString(core::string const& str)
{
    ErrorCode ret = 0;
    
    if (str == "not-authorized")
        ret = ERR_NOT_AUTHORIZED;
    
    return ret;
}

XMPPCORE_END
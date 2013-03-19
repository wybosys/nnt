
# include "Core.h"
# include "MaeAccount.h"
# include "../../Security/MDN+WSI.h"

WAE_MODEL_BEGIN_NS(account)

ns::String User::Passwd(ns::String const& plain)
{
    ns::String str = @"wae/";
    str += plain;
    ns::String res = [[MD5 StringDigest:str] lowercaseString];
    res = [[MD5 StringDigest:res] lowercaseString];
    return res;
}

WAE_MODEL_END_NS


# ifndef __WSI_MAE_ACCOUNT_9F8AAE4EBEF64920BB0CD533B5371E1F_H_INCLUDED
# define __WSI_MAE_ACCOUNT_9F8AAE4EBEF64920BB0CD533B5371E1F_H_INCLUDED

# include "../AEModel.h"

WAE_MODEL_BEGIN_NS(account)

class User
: public RefObject
{
public:
    
    ns::String name;
    ns::String appid;
    ns::String prefix;
    uint gid;
    uint uid;
    
    static ns::String Passwd(ns::String const&);
    
};

class Group
: public RefObject
{
public:
    
    ns::String name;
    ns::String prefix;
    uint gid;
    
};

WAE_MODEL_END_NS

# endif

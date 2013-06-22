
# ifndef __NNT_MAE_AUTH_54E11071882948D88498AA56F855CCDA_H_INCLUDED
# define __NNT_MAE_AUTH_54E11071882948D88498AA56F855CCDA_H_INCLUDED

# include "../AEModel.h"
# include "MaeAccount.h"

WAE_MODEL_BEGIN_NS(auth)

class Login
: public AppEngine
{
public:
    
    Login();
    
    virtual void params(ns::MutableArray&) const;
    virtual void success(id);
    
    NEED ns::String name, passwd;
    OPTIONAL bool isplain;
    
    account::User user;
    
};

class AllUser
: public AppEngine
{
public:
    
    AllUser();
    
    virtual void success(id);
    
    core::refpointer_vector<account::User> users;
};

class AllGroup
: public AppEngine
{
public:
    
    AllGroup();
    
    virtual void success(id);
    
    core::refpointer_vector<account::Group> groups;
    
};

class FindGroup
: public AppEngine
{
public:
    
    FindGroup();
    
    virtual void params(ns::MutableArray&) const;
    virtual void success(id);
    
    OPTIONAL uint gid;
    OPTIONAL ns::String name;
    
    auto_ref<account::Group> group;
    
};

class AddGroup
: public AppEngine
{
public:
    
    AddGroup();
    
    virtual void params(ns::MutableArray&) const;
    
    NEED ns::String name;
    OPTIONAL uint gid;
    OPTIONAL ns::String prefix;
    
};

class AddUser
: public AppEngine
{
public:
    
    AddUser();
    
    virtual void params(ns::MutableArray&) const;
    
    NEED ns::String name;
    OPTIONAL uint uid, gid;
    OPTIONAL ns::String prefix;
    
};

WAE_MODEL_END_NS

# endif

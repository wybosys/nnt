
# import "Core.h"
# import "MaeAuth.h"

WAE_MODEL_BEGIN_NS(auth)

Login::Login()
: isplain(false)
{
    set_method(@"api.auth.user.login");
}

void Login::params(ns::MutableArray &arr) const
{
    arr.add(ns::Pair(@"user", name));
    
    if (isplain)
    {
        arr.add(ns::Pair(@"plain", @"1"));
        arr.add(ns::Pair(@"passwd", passwd));
    }
    else
    {
        ns::String enc_passwd = account::User::Passwd(passwd);
        arr.add(ns::Pair(@"passwd", enc_passwd));
    }
}

void Login::success(id obj)
{
    ns::Dictionary dict(obj);
    user.name = dict[@"name"];
    user.appid = dict[@"appid"];
}

AllUser::AllUser()
{
    set_method(@"api.auth.user.all");
}

void AllUser::success(id obj)
{
    users.clear();
    
    for (id each in obj)
    {
        ns::Dictionary da(each);
        
        instance_ref<account::User> usr;
        usr->name = da[@"name"];
        usr->gid = core::touint(da[@"gid"]);
        usr->uid = core::touint(da[@"uid"]);
        usr->prefix = da[@"prefix"];
        
        users.add(*usr);
    }
}

AllGroup::AllGroup()
{
    set_method(@"api.auth.group.all");
}

void AllGroup::success(id obj)
{
    groups.clear();
    for (id each in obj)
    {
        ns::Dictionary da(each);
        
        instance_ref<account::Group> grp;
        grp->name = da[@"name"];
        grp->gid = core::touint(da[@"gid"]);
        grp->prefix = da[@"prefix"];
        
        groups.add(*grp);
    }
}

FindGroup::FindGroup()
: gid(-1)
{
    set_method(@"api.auth.group.find");
}

void FindGroup::params(ns::MutableArray &arr) const
{
    if (gid != -1)
        arr.add(ns::Pair(@"id", tostr(gid)));
    if (name.not_empty())
        arr.add(ns::Pair(@"name", name));
}

void FindGroup::success(id obj)
{
    ns::Dictionary da(obj);
    group.reset(instance_ref<account::Group>());
    group->gid = core::touint(da[@"gid"]);
    group->name = da[@"name"];
    group->prefix = da[@"prefix"];
}

AddGroup::AddGroup()
: gid(-1)
{
    set_method(@"api.auth.group.add");
    set_update(true);
}

void AddGroup::params(ns::MutableArray &arr) const
{
    if (gid != -1)
        arr.add(ns::Pair(@"id", tostr(gid)));
    if (prefix.not_empty())
        arr.add(ns::Pair(@"prefix", prefix));
    arr.add(ns::Pair(@"name", name));
}

AddUser::AddUser()
: uid(-1), gid(-1)
{
    set_method(@"api.auth.user.add");
    set_update(true);
}

void AddUser::params(ns::MutableArray& arr) const
{
    if (gid != -1)
        arr.add(ns::Pair(@"gid", tostr(gid)));
    if (uid != -1)
        arr.add(ns::Pair(@"uid", tostr(uid)));
    if (prefix.not_empty())
        arr.add(ns::Pair(@"prefix", prefix));
    arr.add(ns::Pair(@"name", name));
}

WAE_MODEL_END_NS

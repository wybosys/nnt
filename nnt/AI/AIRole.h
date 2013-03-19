
# ifndef __NNTAI_ROLE_01f912d84eb0481a8ad950eeadd35cea_H_INCLUDED
# define __NNTAI_ROLE_01f912d84eb0481a8ad950eeadd35cea_H_INCLUDED

# include "AIAction.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ai)

class IRoles;

class IRole
    : public IObject
{
public:

    virtual IActions& actions() const = 0;
    virtual IRoles& roles() const = 0;
    virtual void react(void*) = 0;
    virtual bool pass(void*) const = 0;

};

class IRoles
    : public ntl::IArray<IRole*>
{

};

class Roles
    : public ntl::Arraylize<IRole*, core::refpointer_vector<IRole>, IRoles>
{

};

template <typename implT>
class Role
    : public ntl::uml::realization<implT, IRole>
{
public:

    Role()
    {
        PASS;
    }

    ~Role()
    {
        PASS;
    }

    virtual IActions& actions() const
    {
        return down_const(_acts);
    }

    virtual IRoles& roles() const
    {
        return down_const(_sub);
    }

    virtual bool pass(void*) const
    {
        return true;
    }

    virtual void react(void* obj)
    {
        if (pass(obj) == false)
            return;

        // run action.
        for (uint i = 0; i < _acts.size(); ++i)
        {
            _acts.at(i)->go(obj);
        }

        // run sub roles.
        for (uint i = 0; i < _sub.size(); ++i)
        {
            _sub.at(i)->react(obj);
        }
    }

protected:

    Actions _acts;
    Roles _sub;

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

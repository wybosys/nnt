
# ifndef __NNTAI_BEHAVE_7817be5c36d3449eadcb6a042c0c6491_H_INCLUDED
# define __NNTAI_BEHAVE_7817be5c36d3449eadcb6a042c0c6491_H_INCLUDED

# include "AIRole.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ai)

class IBehave
    : public IObject
{
public:

    virtual IRoles& roles() const = 0;
    virtual void react(void*) = 0;

};

template <typename implT>
class Behave
    : public ntl::uml::realization<implT, IBehave>
{
public:

    Behave()
    {
        PASS;
    }

    ~Behave()
    {        
        PASS;
    }

    virtual IRoles& roles() const
    {
        return down_const(_roles);
    }

    virtual void react(void* obj)
    {
        for (uint i = 0; i < _roles.size(); ++i)
        {
            _roles.at(i)->react(obj);
        }
    }

protected:

    Roles _roles;

};

class IBehaves
    : public ntl::IArray<IBehave*>
{

};

class Behaves
    : public ntl::Arraylize<IBehave*, core::refpointer_vector<IBehave>, IBehaves>
{

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif


# ifndef __NNTAI_ACTION_e062f2a3aa664315a23e742902bbb5ee_H_INCLUDED
# define __NNTAI_ACTION_e062f2a3aa664315a23e742902bbb5ee_H_INCLUDED

# include "../TL/Interface+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ai)

class IActions;

class IAction
    : public IObject
{
public:

    virtual void go(void*) = 0;
    virtual IActions& actions() const = 0;

};

class IActions
    : public ntl::IArray<IAction*>
{

};

class Actions
    : public ntl::Arraylize<IAction*, core::refpointer_vector<IAction>, IActions>
{

};

template <typename implT>
class Action
    : public ntl::uml::realization<implT, IAction>
{
public:

    virtual void go(void* obj)
    {
        for (uint i = 0; i < _acts.size(); ++i)
        {
            _acts.at(i)->go(obj);
        }
    }

    virtual IActions& actions() const
    {
        return down_const(_acts);
    }

protected:

    Actions _acts;

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif


# ifndef __WSIAI_ACTION_e062f2a3aa664315a23e742902bbb5ee_H_INCLUDED
# define __WSIAI_ACTION_e062f2a3aa664315a23e742902bbb5ee_H_INCLUDED

# include "../WTL/Interface+WSI.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ai)

class IActions;

class IAction
    : public IObject
{
public:

    virtual void go(void*) = 0;
    virtual IActions& actions() const = 0;

};

class IActions
    : public wtl::IArray<IAction*>
{

};

class Actions
    : public wtl::Arraylize<IAction*, core::refpointer_vector<IAction>, IActions>
{

};

template <typename implT>
class Action
    : public wtl::uml::realization<implT, IAction>
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

WSI_END_NS
WSI_END_HEADER_CXX

# endif

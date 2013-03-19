
# ifndef __NNT_AI_BODY_b316953be4214759bd7403ef89483579_H_INCLUDED
# define __NNT_AI_BODY_b316953be4214759bd7403ef89483579_H_INCLUDED

# include "AIBehave.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ai)

class IBody
    : public IObject
{
public:

    virtual IBehaves& behaves() const = 0;
    virtual void active() = 0;
    virtual void react(void*) = 0;

};

template <typename implT>
class Body
    : public ntl::uml::realization<implT, IBody>
{
public:

    Body()
    {
        PASS;
    }

    ~Body()
    {
        PASS;
    }

    virtual IBehaves& behaves() const
    {
        return down_const(_behaves);
    }

    virtual void active() = 0;

    virtual void react(void* obj)
    {
        for (uint i = 0; i < _behaves.size(); ++i)
        {
            _behaves.at(i)->react(obj);
        }
    }

protected:

    Behaves _behaves;

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

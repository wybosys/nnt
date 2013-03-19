
# ifndef __WSI_MODEL_OPE_2BB4058CF12A42DEAE0A58D5F94A1D26_H_INCLUDED
# define __WSI_MODEL_OPE_2BB4058CF12A42DEAE0A58D5F94A1D26_H_INCLUDED

# include "Model.h"

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

@interface OperationModel : Model

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ns)
WSI_BEGIN_NS(model)

class IOperation
{
public:
    
    virtual ~IOperation() {}
    virtual id run() = 0;
    
};

class Operation
: public ns::Model,
public IOperation
{
public:
    
    Operation();
    virtual ~Operation();
    
public:
    
    virtual bool process(id result);
    virtual id run();
    
};

WSI_END_NS
WSI_END_NS
WSI_END_HEADER_CXX

# endif
// end cxx

# endif
// end objc

# endif

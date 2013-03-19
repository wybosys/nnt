
# ifndef __WSI_MAE_SAPI_99AC97620FE64B8EBC12D493BA2CA885_H_INCLUDED
# define __WSI_MAE_SAPI_99AC97620FE64B8EBC12D493BA2CA885_H_INCLUDED

# include "../AEModel.h"

WAE_MODEL_BEGIN_NS(sapi)

class Method
{
public:
    
    ns::String name;
    core::vector<ns::String> requires, optionals;
    
};

class Class
: public RefObject
{
public:
    
    ns::String name;
    core::vector<Method> methods;
    
};

class List
: public AppEngine
{
public:
    
    List();
    
    virtual void success(id);
    
    core::refpointer_vector<Class> classes;
    
};

class FindDoc
: public AppEngine
{
public:
    
    FindDoc();
    
    virtual void params(ns::MutableArray&) const;
    virtual void success(id);
    
    NEED ns::String method;
    RESULT ns::String doc;
    
};

WAE_MODEL_END_NS

# endif

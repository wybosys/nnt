
# ifndef __WSI_MAE_TOOLKIT_AE9382FA38F845959FA30A8959B993E2_H_INCLUDED
# define __WSI_MAE_TOOLKIT_AE9382FA38F845959FA30A8959B993E2_H_INCLUDED

# include "../AEModel.h"

WAE_MODEL_BEGIN_NS(toolkit)

class Counter
: public RefObject
{
public:
    
    ns::String name, device, identity;
    uint sum;
    
};

class LaunchCounter
: public AppEngine
{
public:
    
    LaunchCounter();
    
    virtual void success(id);
    
    core::refpointer_vector<Counter> items;
    
};

class LaunchDeviceCounter
: public AppEngine
{
public:
    
    LaunchDeviceCounter();
    
    virtual void success(id);
  
    core::refpointer_vector<Counter> items;

};

WAE_MODEL_END_NS

# endif

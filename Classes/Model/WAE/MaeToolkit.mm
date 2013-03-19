
# import "Core.h"
# import "MaeToolkit.h"

WAE_MODEL_BEGIN_NS(toolkit)

LaunchCounter::LaunchCounter()
{
    set_method(@"toolkit.counter.launch.all");
}

void LaunchCounter::success(id res)
{
    items.clear();
    
    for (id each in res)
    {
        ns::Dictionary da(each);
        
        Counter& obj = items.add();
        obj.name = da[@"name"];
        obj.identity = da[@"id"];
        obj.sum = core::touint(da[@"sum"]);
    }
}

LaunchDeviceCounter::LaunchDeviceCounter()
{
    set_method(@"toolkit.counter.device.launch.all");
}

void LaunchDeviceCounter::success(id res)
{
    items.clear();
    
    for (id each in res)
    {
        ns::Dictionary da(each);
        
        Counter& obj = items.add();
        obj.name = da[@"name"];
        obj.device = da[@"dev"];
        obj.identity = da[@"id"];
        obj.sum = core::touint(da[@"sum"]);
    }
}

WAE_MODEL_END_NS

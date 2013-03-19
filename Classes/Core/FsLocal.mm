
# import "Core.h"
# import "FsLocal.h"
# import "Directory+WSI.h"

WSI_BEGIN_CXX
WSI_BEGIN_NS(ns)

bool Local::copy(ns::URL const& to, ns::URL const& from)
{
    if (!(to.is_file() && from.is_file()))
        return false;
    
    NSFileManager* fm = [NSFileManager defaultManager];
    bool suc = true;
    NSError* err = nil;
    ns::String str_from = from.std();
    ns::String str_to = to.std();
    suc = [fm copyItemAtPath:str_from toPath:str_to error:&err];
    if (!suc && err)
        trace_msg(err.debugDescription);
    return suc;
}

WSI_END_NS
WSI_END_CXX

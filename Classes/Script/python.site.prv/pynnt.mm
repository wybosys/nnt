
# import "Core.h"
# import "pynnt.h"

NNT_BEGIN_OBJC

NSString* PyNnt_ErrorMessage()
{
    ::nnt::core::string msg = ::nnt::PyNnt_ErrorMessage();
    return [NSString stringWithUTF8String:msg.c_str()];
}

NNT_END_OBJC

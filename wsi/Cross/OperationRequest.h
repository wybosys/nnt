
# ifndef __WSI_CROSS_OPERATIONREQUEST_B9131CE51D124E1B80E3C200F556435B_H_INCLUDED
# define __WSI_CROSS_OPERATIONREQUEST_B9131CE51D124E1B80E3C200F556435B_H_INCLUDED

# import "NullRpc.h"

WSI_BEGIN_HEADER_OBJC

@interface OperationRequest : NullRpc {
    
}

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(cross)

class OperationRequest
: public ns::Object< ::OperationRequest >
{
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif

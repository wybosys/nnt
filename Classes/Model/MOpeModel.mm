
# import "Core.h"
# import "MOpeModel.h"
# import "OperationRequest.h"

WSI_BEGIN_OBJC

@implementation OperationModel


@end

WSI_END_OBJC

WSI_BEGIN_CXX
WSI_BEGIN_NS(ns)
WSI_BEGIN_NS(model)

Operation::Operation()
{
    set_update(true);
    set_url(@"::wsi::model::operation::skipcache::url");
    set_rpc(cross::OperationRequest::getClass());
}

Operation::~Operation()
{
    
}

bool Operation::process(id result)
{
    return true;
}

id Operation::run()
{
    return nil;
}

WSI_END_NS
WSI_END_NS
WSI_END_CXX

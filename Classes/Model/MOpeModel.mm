
# import "Core.h"
# import "MOpeModel.h"
# import "OperationRequest.h"

NNT_BEGIN_OBJC

@implementation OperationModel


@end

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(ns)
NNT_BEGIN_NS(model)

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

NNT_END_NS
NNT_END_NS
NNT_END_CXX

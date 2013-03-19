
# import "Core.h"
# import "OperationRequest.h"
# import "MOpeModel.h"

NNT_BEGIN_OBJC

@implementation OperationRequest

- (NSObject*)call:(Model *)model withUrl:(NSURL *)url {
    [super call:model withUrl:url];
    
    __cxxmodel_wrapper* nsmdl = (__cxxmodel_wrapper*)model;
    ::wsi::ns::IModel* cxxmdl = nsmdl.model;
    ::wsi::ns::model::IOperation* opemdl = dynamic_cast< ::wsi::ns::model::IOperation*>(cxxmdl);
    return opemdl->run();
}

@end

NNT_END_OBJC
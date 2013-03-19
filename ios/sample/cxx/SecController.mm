
# import "Foundation+NNT.h"
# import "SecController.h"
# import "ThdController.h"

NNTAPP_BEGIN

void SecView::layout_subviews()
{
    
}

SecController::SecController()
{
    
}

SecController::~SecController()
{
    
}

void SecController::view_loaded()
{
    set_title(@"SECOND");
    
    WSI_AUTORELEASEPOOL_BEGIN
    
    ThdController* ctlr = ThdController::New();
    ctlr->Release();    
    //ThdController obj;
    
    WSI_AUTORELEASEPOOL_END

}

NNTAPP_END
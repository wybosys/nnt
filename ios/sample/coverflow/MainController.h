
# ifndef __MAIN_CONTROLLER_DBFB1F36C9464573ABB0031B3A4E94DE_H_INCLUDED
# define __MAIN_CONTROLLER_DBFB1F36C9464573ABB0031B3A4E94DE_H_INCLUDED

# import "UICoverFlow.h"
# import "UICoverFlowController.h"
# import "UICoverFlowItem.h"

WSI_BEGIN_HEADER_OBJC

@interface MainController : WSIUIViewController {
    UICoverFlowController* ctlr;
}

@property (nonatomic, readonly) UICoverFlow* coverflow;

@end

WSI_END_HEADER_OBJC

# endif
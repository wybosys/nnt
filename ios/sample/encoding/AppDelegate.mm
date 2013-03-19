
# include "WSIFoundation.h"
# import "AppDelegate.h"
# include "MainController.h"

@implementation AppDelegate

- (void)load {    
    
    ::wsiapp::MainController* ctlr = ::wsiapp::MainController::New();
    self.rootViewController = *ctlr;
    ctlr->Release();

    using namespace ::wsi;

    static ns::Regex re(@"\\[(?:([\\d+\\.]+),?)+\\]");
    ns::String str = @"var st=0;var arrOdds=[[3,[1,0.98,0.5,0.91,1.97,3.20,3.80,0.97,2,0.91],[2,1.00,0.5,0.91,1.99,3.25,4.55,0.85,1.75,1.05]],[8,[1,0.975,0.5,0.875,1.90,3.25,4.33,0.975,2,0.875],[2,1.00,0.5,0.925,2.00,3.20,4.20,0.825,1.75,1.075]],[4,[1,0.78,0.25,1.06,2.50,3.10,2.60,0.96,2,0.88],[2,1.00,0.5,0.88,2.00,3.20,4.33,1.14,2,0.74]],[1,[1,0.78,0.25,1.02,2.05,3.05,3.25,0.85,2,0.85],[2,1.00,0.5,0.86,2.00,3.10,3.33,1.08,2,0.72]]]";
    
    ns::Array arr = re.capture(str);
    ns::String strsub = arr[0];
    static ns::Regex rev(@"([\\d+\\.]+)");
    ns::Array res = rev.grep(strsub);
    
}

@end

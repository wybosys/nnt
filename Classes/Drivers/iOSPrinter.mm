
# import "Core.h"
# import "iOSPrinter.h"

# import <UIKit/UIPrintError.h>
# import <UIKit/UIPrintFormatter.h>
# import <UIKit/UIPrintInfo.h>
# import <UIKit/UIPrintInteractionController.h>
# import <UIKit/UIPrintPageRenderer.h>
# import <UIKit/UIPrintPaper.h>

NNT_BEGIN_OBJC

NNTDECL_PRIVATE_BEGIN(InteractionPrinter, NSObject)
<UIPrintInteractionControllerDelegate>

@property (nonatomic, retain) UIPrintInteractionController* ctlr_print;

NNTDECL_PRIVATE_IMPL(InteractionPrinter)

@synthesize ctlr_print;

- (id)init {
    self = [super init];
    
    if ([InteractionPrinter IsSupported] == NO) {
        [Msgbox warn:_W(@"printer: unsupported.")];
        return self;
    }
    
    ctlr_print = [[UIPrintInteractionController sharedPrintController] retain];
    ctlr_print.delegate = self;
    
    // set info.
    UIPrintInfo* info = [UIPrintInfo printInfo];
    info.orientation = UIPrintInfoOrientationPortrait;
    info.outputType = UIPrintInfoOutputGeneral;
    info.duplex = UIPrintInfoDuplexLongEdge;
    info.jobName = @"::nnt::print::job";
    
    ctlr_print.printInfo = info;
    ctlr_print.showsPageRange = YES;
    
    return self;
}

- (void)dealloc {
    safe_release(ctlr_print);
    [super dealloc];
}

NNTDECL_PRIVATE_END

@implementation InteractionPrinter

@dynamic printFormatter, printItem, printItems, printPageRenderer;

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(InteractionPrinter);
    return self;
}

- (void)dealloc {
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (UIPrintPageRenderer*)printPageRenderer {
    return d_ptr.ctlr_print.printPageRenderer;
}

- (void)setPrintPageRenderer:(UIPrintPageRenderer *)printPageRenderer {
    d_ptr.ctlr_print.printPageRenderer = printPageRenderer;
}

- (UIPrintFormatter*)printFormatter {
    return d_ptr.ctlr_print.printFormatter;
}

- (void)setPrintFormatter:(UIPrintFormatter *)printFormatter {
    d_ptr.ctlr_print.printFormatter = printFormatter;
}

- (id)printItem {
    return d_ptr.ctlr_print.printingItem;
}

- (void)setPrintItem:(id)printItem {
    d_ptr.ctlr_print.printingItem = printItem;
}

- (NSArray*)printItems {
    return d_ptr.ctlr_print.printingItems;
}

- (void)setPrintItems:(NSArray *)printItems {
    d_ptr.ctlr_print.printingItems = printItems;
}

+ (BOOL)IsSupported {
    return [UIPrintInteractionController isPrintingAvailable];
}

- (void)execute:(CGRect)rect inView:(UIView*)view animated:(BOOL)animated {
    UIPrintInteractionCompletionHandler completionHandler =
    ^(UIPrintInteractionController *printController, BOOL completed, NSError *error) {
        if(!completed && error){
            trace_fmt(@"FAILED! due to error in domain %@ with error code %u", error.domain, error.code);
        }
        
        [self release];
    };
    
    BOOL suc;
    
    if (NNT_ISPAD) {
        suc = [d_ptr.ctlr_print presentFromRect:rect inView:view animated:animated completionHandler:completionHandler];
    } else {
        suc = [d_ptr.ctlr_print presentAnimated:animated completionHandler:completionHandler];
    }
    
    if (suc == NO) {
        [Msgbox fatal:_W(@"failed to open printer.")];
        return;
    }
    
    // protect self.
    [self retain];
}

@end

@implementation UIPrintFormatter (NNT)

- (NSInteger)defaultPageCount {
    return [self pageCount];
}

@end

NNTIMPL_OBJCXX_WRAPPER(UIPrintPageRenderer);

NNTIMPL_OBJCXX_WRAPPER_BEGIN(UISimpleTextPrintFormatter)

- (NSInteger)defaultPageCount {
    return [super pageCount];
}

- (NSInteger)pageCount {
    ::nnt::driver::print::ns::formatter::IFormatter* format = (::nnt::driver::print::ns::formatter::IFormatter*)self._cxxobj;
    if (format) {
        return format->page_count();
    }
    return [self defaultPageCount];
}

NNTIMPL_OBJCXX_WRAPPER_END

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(ns)


NNT_END_NS
NNT_END_CXX

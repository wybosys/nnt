
# import "WSIFoundation.h"
# import "mustacheViewController.h"
# import "MustacheParser.h"
# import "WSIResource.h"

@implementation mustacheViewController

- (void)loadView {
    WSIUIWebView *view = [[WSIUIWebView alloc] initWithFrame:CGRectZero];
    self.view = view;
    [view release];
}

- (void)viewDidLoad {
    WSIUIWebView *web = (WSIUIWebView*)self.view;
        
    wsi::ns::MutableDictionary dict;
    wsi::ns::MutableDictionary a;
    wsi::ns::MutableDictionary b;
    wsi::ns::MutableDictionary b_inner;
    
    a[@"name"] = @"A";
    b[@"name"] = @"B";
    b_inner[@"name_inner"] = @"B INNER";
    b[@"array_inner"] = [NSArray arrayWithObjects:(id)b_inner, (id)b_inner, nil];
    
    dict[@"array"] = [NSArray arrayWithObjects:(id)a, (id)b, nil];
    
    NSString *tpl = [WSIResource ContentOf:@"table.htm"];
    MustacheParser *parser = [[MustacheParser alloc] init];
    [parser loadTemplate:tpl];
    NSString* html = [parser renderObject:dict];
    trace_msg(html);
    
    [web loadHTMLStringLocal:html];   
    [parser release];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

@end

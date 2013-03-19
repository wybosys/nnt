
# import "Core.h"
# import "App.h"
# include <stdio.h>
# import "WSIUIObject.h"
# import "FileCache.h"
# import "CoreGraphic+WSI.h"
# import "WSIConfiguration.h"
# import "CmdArguments.h"
# import "AppInformation.h"
# import "UUID+WSI.h"

# ifdef WSI_TARGET_IOS

#   import "UIDevice+WSI.h"
#   import "UICacheActivityIndicatorView.h"
#   import "AppStoreService.h"

# endif

# ifdef WSI_DEBUG
#   define USE_DTRACE
# endif

# import MAC_IOS_SELECT("./null.prv.h", "UIStatusBarControl.h")

# ifdef USE_DTRACE
#   import MAC_IOS_SELECT("./null.prv.h", "DTraceLogoSwitch.h")
# endif

WSI_BEGIN_CXX

static Application* __cxxgs_app = NULL;

WSI_END_CXX

WSI_BEGIN_OBJC

# define kCacheActivityIndicatorDuration .5f
# define kCacheActivityIndicatorHideWait 2.f
# define kCacheActivityIndicatorSize 30, 30
# define kCacheActivityIndicatorPos .75

signal_t kSignalAppOpenUrl = @"::wsi::app::openurl";
signal_t kSignalAppFinishLaunching = @"::wsi::app::finish_launching";
signal_t kSignalAppHiding = @"::wsi::app::hiding";
signal_t kSignalAppHiden = @"::wsi::app::hiden";
signal_t kSignalAppShowing = @"::wsi::app::showing";
signal_t kSignalAppShown = @"::wsi::app::shown";
signal_t kSignalAppActiving = @"::wsi::app::activing";
signal_t kSignalAppActived = @"::wsi::app::actived";
signal_t kSignalAppInactiving = @"::wsi::app::inactiving";
signal_t kSignalAppInactived = @"::wsi::app::inactived";
signal_t kSignalAppBackground = @"::wsi::app::background::in";
signal_t kSignalAppBackgroundExpired = @"::wsi::app::background::expired";
signal_t kSignalNotification = @"::wsi::notification";
signal_t kSignalDeviceToken = @"::wsi::devicetoken::got";
signal_t kSignalMemoryWarning = @"::wsi::memory::warning";

NSString* kConfigDeviceToken = @"::wsi::config::device::token";

extern void LoadTheme(NSString*);

static WSIApplication *__gs_app = nil;
bool __need_manual_appear = false;
bool WSI_DEVICE_ISIPHONE = false;
bool WSI_DEVICE_ISIPHONE_SIMULATOR = false;
bool WSI_DEVICE_ISIPAD = false;
bool WSI_DEVICE_ISIPAD_SIMULATOR = false;
bool WSI_DEVICE_ISIPOD = false;
bool WSI_DEVICE_ISSIMULATOR = false;
bool WSI_SUPPORT_BLOCKS = false;
bool WSI_SUPPORT_MULTITASKS = false;
double DEVICE_VERSION = 0;

# ifdef WSI_TARGET_IOS

@interface IOSDefaultWindow : WSIUIWindow {
# ifdef USE_DTRACE
    DTraceLogoSwitch* _logo;
# endif
}

@end

@implementation IOSDefaultWindow

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
# ifdef USE_DTRACE
    
    _logo = [DTraceLogoSwitch logoSwitch];
    [self addSubview:_logo];
    
# endif
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (void)layoutSubviews {
    [super layoutSubviews];
    
# ifdef USE_DTRACE
    
    ::wsi::cg::TransformRect rc_logo(::wsi::cg::Rect(64, 64, 32, 32),
                                     [[UIDevice currentDevice] transform]);
    _logo.logicFrame = rc_logo;
    [self bringSubviewToFront:_logo];
    
# endif
}

@end

# endif

WSIDECL_PRIVATE_BEGIN(WSIApplication, WSIObject)
MACEXPRESS(<NSWindowDelegate>)
{
    BSEAppInformation* _bse_appinfo;
}

@property (nonatomic, assign) int countNetworkActivityIndicator;
@property (nonatomic, assign) BOOL appIsActivity;

WSIDECL_PRIVATE_IMPL(WSIApplication)

@synthesize countNetworkActivityIndicator;
@synthesize appIsActivity;

- (id)init {
    self = [super init];
    countNetworkActivityIndicator = 0;
    
    // init bse.
    _bse_appinfo = [[BSEAppInformation alloc] init];
    _bse_appinfo.app = d_owner;
    
    return self;
}

- (void)dealloc {
    safe_release(_bse_appinfo);
    
    [super dealloc];
}

WSIDECL_PRIVATE_END

@implementation WSIApplication

@synthesize window = _window;
@synthesize applicationName = _applicationName, applicationURLScheme = _applicationURLScheme, applicationIdentity = _applicationIdentity, urlInAppStore = _urlInAppStore;
@dynamic networkActivityIndicatorVisible;
@synthesize rootViewController = _rootViewController;

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(WSIApplication);
    
    // init WSI environment.
    [WSI Init];
    
    // bin app to global.
    __gs_app = self;
    
    if (::wsi::__cxxgs_app)
        ::wsi::__cxxgs_app->replace(__gs_app);
    
# ifdef WSI_TARGET_IOS
    
    __need_manual_appear = need_manual_appear();
    
    WSI_DEVICE_ISIPHONE_SIMULATOR = [UIDevice isIPhoneSimulator];
    WSI_DEVICE_ISIPHONE = [UIDevice isIPhone] | WSI_DEVICE_ISIPHONE_SIMULATOR;
    WSI_DEVICE_ISIPAD_SIMULATOR = [UIDevice isIPadSimulator];
    WSI_DEVICE_ISIPAD = [UIDevice isIPad] | WSI_DEVICE_ISIPAD_SIMULATOR;
    WSI_DEVICE_ISIPOD = [UIDevice isIPod];
    WSI_DEVICE_ISSIMULATOR = WSI_DEVICE_ISIPHONE_SIMULATOR | WSI_DEVICE_ISIPAD_SIMULATOR;
    
    WSI_SUPPORT_BLOCKS = support_blocks();
    WSI_SUPPORT_MULTITASKS = support_multitasks();
    DEVICE_VERSION = device_version();
    
# endif
    
    // trace.
    trace_msg(@"debug: enable.");
        
    return self;
}

- (void)dealloc {
    
    safe_release(_applicationName);
    safe_release(_applicationIdentity);
    safe_release(_applicationURLScheme);
    safe_release(_urlInAppStore);
    
    // free root controller.
    safe_release(_rootViewController);
   
    // free window.
    safe_release(_window);
    
    // end wsi.
    [WSI Fin];
    
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

# ifdef WSI_TARGET_IOS

- (UIWindow*)window {
    if (_window)
        return _window;

    // alloc window.
    _window = [[IOSDefaultWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
    _window.backgroundColor = [UIColor clearColor];
    
    return _window;
}

- (void)setWindow:(UIWindow *)__window {
    // swap window.
    safe_release(_window);
    _window = [__window retain];
}

- (BOOL)networkActivityIndicatorVisible {
    BOOL ret;
    ret = d_ptr.countNetworkActivityIndicator > 0;
    return ret;
}

- (void)setNetworkActivityIndicatorVisible:(BOOL)val {
    WSI_SYNCHRONIZED(self)
    
    if (val) {
        ++d_ptr.countNetworkActivityIndicator;
    } else {
        --d_ptr.countNetworkActivityIndicator;
    }
        
    if (d_ptr.countNetworkActivityIndicator == 0) {
        [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
    } else if (d_ptr.countNetworkActivityIndicator == 1) {
        [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
    }
    
    WSI_SYNCHRONIZED_END
}

+ (NSString*)Identity {
    return [[[NSBundle mainBundle] infoDictionary] valueForKey:(NSString*)kCFBundleIdentifierKey];
}

+ (NSString*)Name {
    return [[[NSBundle mainBundle] infoDictionary] valueForKey:(NSString*)kCFBundleNameKey];
}

+ (NSString*)DeviceIdentity {
    NSString* idr = [[WSIConfiguration shared] get:@"::wsi::device::identity" null:nil];
    if (idr != nil)
        return idr;
    idr = uuid_string();
    [[WSIConfiguration shared] set:@"::wsi::device::identity" val:idr];
    return idr;
}

# endif // end ios.

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalAppOpenUrl)
WSIEVENT_SIGNAL(kSignalAppHiding)
WSIEVENT_SIGNAL(kSignalAppHiden)
WSIEVENT_SIGNAL(kSignalAppShowing)
WSIEVENT_SIGNAL(kSignalAppShown)
WSIEVENT_SIGNAL(kSignalAppActiving)
WSIEVENT_SIGNAL(kSignalAppActived)
WSIEVENT_SIGNAL(kSignalAppInactiving)
WSIEVENT_SIGNAL(kSignalAppInactived)
WSIEVENT_SIGNAL(kSignalAppFinishLaunching)
WSIEVENT_SIGNAL(kSignalAppBackground)
WSIEVENT_SIGNAL(kSignalAppBackgroundExpired)
WSIEVENT_SIGNAL(kSignalNotification)
WSIEVENT_SIGNAL(kSignalDeviceToken)
WSIEVENT_SIGNAL(kSignalMemoryWarning)
WSIEVENT_END

+ (WSIApplication*)shared {
    return __gs_app;
}

+ (WSIApplication*)current {
    return __gs_app;
}

- (void)load {
    PASS;
}

// for mac
# ifdef WSI_TARGET_MAC

void LoadTheme(NSString*) {
    PASS;
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    trace_msg(@"application: launching.");
    
    // boot wsi.
    [WSI Boot];
    
    // load theme.
    LoadTheme(nil);
    
    // init.
    [self load:aNotification];
    
    // sig.
    [self emit:kSignalAppFinishLaunching];        
    
    trace_msg(@"application: launched.");
}

- (void)load:(NSNotification*)aNotification {
    [self load];
}

- (void)applicationWillFinishLaunching:(NSNotification *)notification {
    trace_msg(@"application: launching.");
}

- (void)applicationWillHide:(NSNotification *)notification {
    trace_msg(@"application: hiding.");
    
    [self emit:kSignalAppHiding];    
}

- (void)applicationDidHide:(NSNotification *)notification {
    trace_msg(@"application: hiden.");
    
    [self emit:kSignalAppHiden];    
}

- (void)applicationWillUnhide:(NSNotification *)notification {
    trace_msg(@"application: showing.");
    
    [self emit:kSignalAppShowing];    
}

- (void)applicationDidUnhide:(NSNotification *)notification {
    trace_msg(@"application: shown.");
    
    [self emit:kSignalAppShown];    
}

- (void)applicationWillBecomeActive:(NSNotification *)notification {
    trace_msg(@"application: activing.");
    
    [self emit:kSignalAppActiving];    
}

- (void)applicationDidBecomeActive:(NSNotification *)notification {
    trace_msg(@"application: actived."); 
    
    d_ptr.appIsActivity = YES;
    
    // active hook.
    [WSI Active];
    
    // sig.
    [self emit:kSignalAppActived];               
}

- (void)applicationWillResignActive:(NSNotification *)notification {
    trace_msg(@"application: inactiving.");
    
    [self emit:kSignalAppInactiving];    
}

- (void)applicationDidResignActive:(NSNotification *)notification {
    trace_msg(@"application: inactived."); 
    
    d_ptr.appIsActivity = NO;
    
    // hook.
    [WSI Inactive];
    
    // sig.
    [self emit:kSignalAppInactived];              
}

- (void)applicationWillUpdate:(NSNotification *)notification {
    PASS;
}

- (void)applicationDidUpdate:(NSNotification *)notification {
    PASS;
}

- (void)applicationWillTerminate:(NSNotification *)notification {
    trace_msg(@"application: terminating.");
}

- (void)applicationDidChangeScreenParameters:(NSNotification *)notification {
    trace_msg(@"application: screen parameters changed.");
}

- (void)setRootViewController:(NSViewController *)ctlr {
    if (rootViewController == ctlr)
        return;
    
    NSView* view = ctlr.view;
    self.window.contentView = view;

    [NSObject refobjSet:&rootViewController ref:ctlr];
}

- (void)setWindow:(NSWindow *)win {
    if (_window == win)
        return;
    
    [NSObject refobjSet:&_window ref:win];
    
    _window.delegate = d_ptr;
}

# endif

// for IOS
# ifdef WSI_TARGET_IOS

- (void)applicationDidFinishLaunching:(UIApplication *)application {
    trace_msg(@"application: launched.");
    
    [self emit:kSignalAppFinishLaunching];
}

- (void)load:(UIApplication *)application options:(NSDictionary *)launchOptions {
    // short load.
    [self load];
}

@synthesize initialView;

- (void)setInitialView:(UIView *)view {
    if ([view isKindOfClass:[UIInitialView class]] == NO)
        return;
    initialView = view;
    
    // show.
    UIInitialView* ope = (UIInitialView*)view;
    [ope connect:kSignalInitialWillComplete sel:@selector(_initialview_completing) obj:self];
    [ope show];
}

- (void)_initialview_completing {
    // make current window as key.
    [self.window makeKeyAndVisible];
    
    // clear.
    initialView = nil;
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    trace_msg(@"application: launching.");
    
    // boot wsi.
    [WSI Boot];
    
    // init.
    [self load:application options:launchOptions];
    
    // load theme.
    LoadTheme(nil);
    
    // use window.
    if (initialView == nil) {
        // no initial view, direct show window.
        [self.window makeKeyAndVisible];
    }
    
    // appstore.
    if (_urlInAppStore) {
        [RateAppReminder shared].appurl = _urlInAppStore;
        [[RateAppReminder shared] remind];
    }
    
    // print debug info.
    trace_msg(@"application: launched.");
    
    // signal.
    [self emit:kSignalAppFinishLaunching];
            
    return YES;
}

- (UIWindow*)currentWindow {
    return self.window;
}

- (void)setRootViewController:(UIViewController*)ctlr {
    // remove old root view controller.
    [_rootViewController.view removeFromSuperview];
    
    // set.
    [NSObject refobjSet:&_rootViewController ref:ctlr];
    
# ifdef WSI_iOS_4
    
    self.window.rootViewController = _rootViewController;
    
# else
    
    // get frame.
    rootViewController.view.frame = self.window.bounds;
    [self.window addSubview:rootViewController.view];
    
# endif
}

- (void)background:(UIApplication*)app {
    trace_msg(@"run background operation.");
    
# ifdef WSI_DEBUG
    
    NSTimeInterval ti = app.backgroundTimeRemaining;
    trace_fmt(@"left %d seconds for background run.", (int)ti);
    
# endif
    
    if (::wsi::__cxxgs_app)
        ::wsi::__cxxgs_app->background();
    
    [self emit:kSignalAppBackground];
}

- (void)backgroundExpired:(UIApplication*)app {
    trace_msg(@"background is expired.");
    
    if (::wsi::__cxxgs_app)
        ::wsi::__cxxgs_app->background_expired();
    
    [self emit:kSignalAppBackgroundExpired];
}

# endif

- (NSString*)applicationURLScheme {
    if (_applicationURLScheme)
        return _applicationURLScheme;
    NSArray *arr = (NSArray*)[[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleURLTypes"];
    NSDictionary *dict = [arr objectAtIndex:0 null:nil];
    if (dict == nil)
        return nil;
    arr = [dict valueForKey:@"CFBundleURLSchemes" null:nil];
    if (arr == nil)
        return nil;
    NSString* str = [arr objectAtIndex:0 null:nil];
    if (str == nil) {
        [WSIObject refobjCopy:&_applicationURLScheme ref:@""];
        return nil;
    }
    
    [WSIObject refobjCopy:&_applicationURLScheme ref:str];
    
    return str;
}

- (NSString*)applicationName {
    if (_applicationName)
        return _applicationName;
    NSString *str = (NSString*)[[NSBundle mainBundle] objectForInfoDictionaryKey:(NSString*)kCFBundleNameKey];
    if (str == nil) {
        [WSIObject refobjCopy:&_applicationName ref:@""];
        return _applicationName;
    }
    
    [WSIObject refobjCopy:&_applicationName ref:str];

    return _applicationName;
}

- (NSString*)applicationIdentity {
    if (_applicationIdentity)
        return _applicationIdentity;
    NSString *str = (NSString*)[[NSBundle mainBundle] objectForInfoDictionaryKey:(NSString*)kCFBundleIdentifierKey];
    if (str == nil) {
        [WSIObject refobjCopy:&_applicationIdentity ref:@""];
        return _applicationIdentity;
    }
    
    [WSIObject refobjCopy:&_applicationIdentity ref:str];

    return _applicationIdentity;
}

# ifdef WSI_TARGET_IOS

- (void)applicationWillTerminate:(UIApplication *)application {
    trace_msg(@"application: terminating.");
    
# ifdef WSI_DEBUG
    [Msgbox warn:@"Application Terminating !"];
# endif
}

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    trace_msg(@"application: memory warning!");
    
# ifdef WSI_DEBUG
    [Msgbox warn:@"memory is not enough, please reboot your device or close unused apps !"];
# endif
    
    [self emit:kSignalMemoryWarning];
}

- (BOOL)isActivity {
    return d_ptr.appIsActivity;
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    trace_msg(@"application: actived.");
    
    d_ptr.appIsActivity = YES;
    
    // call active process.
    [WSI Active];
    
    // emit signal.
    [self emit:kSignalAppActived];
}

- (void)applicationWillResignActive:(UIApplication *)application {
    trace_msg(@"application: inactiving.");
    
    [self emit:kSignalAppInactiving];
}

static UIBackgroundTaskIdentifier __gs_background_identitier = UIBackgroundTaskInvalid;

- (void)applicationWillEnterForeground:(UIApplication *)application {
    trace_msg(@"application: activing.");
    
    // stop last background task.
    if (__gs_background_identitier != UIBackgroundTaskInvalid) {
        [application endBackgroundTask:__gs_background_identitier];
        __gs_background_identitier = UIBackgroundTaskInvalid;
    }
    
    // signal.
    [self emit:kSignalAppActiving];
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    trace_msg(@"application: inactived.");
    
    d_ptr.appIsActivity = NO;
    
    // call inactive process.
    [WSI Inactive];
    
    // emit signal.
    [self emit:kSignalAppInactived];
    
    // call cxx background function.
    if (::wsi::__cxxgs_app) {
        
        __gs_background_identitier = [application beginBackgroundTaskWithExpirationHandler:^{
            [self backgroundExpired:application];
        }];
        
        // start long-running.
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
            [self background:application];
        });
        
    }
}

- (void)application:(UIApplication *)application willChangeStatusBarOrientation:(UIInterfaceOrientation)newStatusBarOrientation duration:(NSTimeInterval)duration {
    trace_msg(@"application: rotating.");
}

- (void)application:(UIApplication *)application didChangeStatusBarOrientation:(UIInterfaceOrientation)oldStatusBarOrientation {
    trace_msg(@"application: rotated.");
        
    // send signal.
    [[WSIUIObject shared] emit:kSignalOrientationChanged];
}

NSString *kWSIApp_Url = @"url";
NSString *kWSIApp_Source = @"source";
NSString *kWSIApp_Anno = @"annotation";
NSString *kWSIApp_App = @"app";

- (BOOL)application:

# ifdef WSI_iOS_4
(UIApplication *)application 
            openURL:(NSURL *)url 
  sourceApplication:(NSString *)sourceApplication 
         annotation:(id)annotation
# else
(UIApplication *)application
handleOpenURL:(NSURL *)url
# endif
{
# ifdef WSI_iOS_4
# else
    id sourceApplication = @"";
    id annotation = @"";
    id application = nil;
# endif
    
    trace_fmt(@"URL: %@\nSOURCE: %@\n", [url absoluteString], sourceApplication);
    
    OpenURLObject* obj = [[OpenURLObject alloc] init];
    obj.app = application;
    obj.url = url;
    obj.source = sourceApplication;
    obj.annotation = annotation;
    [self emit:kSignalAppOpenUrl result:obj];
    safe_release(obj);
    
    return YES;
}

# endif

- (void)enableFileCache {
    FileCache *cache = [[FileCache alloc] initWithPath:@"cache" type:NSVariableDirectory | WSIDirectoryTypeSystem];
    cache.policyLimit = YES;
    [cache setDefault];
    [cache release];
}

- (void)enableICloud {
    // register to observe notifications from the store
    [[NSNotificationCenter defaultCenter]
     addObserver:self
     selector:@selector(_icloud_changed:)
     name:NSUbiquitousKeyValueStoreDidChangeExternallyNotification
     object:[NSUbiquitousKeyValueStore defaultStore]];
    
    // get changes that might have happened while this
    // instance of your app wasn't running
    [[NSUbiquitousKeyValueStore defaultStore] synchronize];
}

- (void)_icloud_changed:(NSNotification*)noti {
    trace_msg(@"recieve iCloud data changed.");
}

# ifdef WSI_iOS_3

- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification {
    
# ifdef WSI_DEBUG
    trace_fmt(@"receive a local notification: %@.", notification.alertBody);
# endif
    
    // reset badge number.
    if ([UIApplication sharedApplication].applicationIconBadgeNumber)
        [UIApplication sharedApplication].applicationIconBadgeNumber -= notification.applicationIconBadgeNumber;
    
    // show message.
    if (d_ptr.appIsActivity) {
        [Msgbox stop:notification.alertBody obj:self ok:@selector(notification_action:) cancel:nil ctx:notification];
    } else {
        [self emit:kSignalNotification result:notification.userInfo];
    }
}

- (void)notification_action:(UILocalNotification*)notification {
    [self emit:kSignalNotification result:notification.userInfo];
}

- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
    trace_obj(deviceToken);
    
    // get device token.
    [[WSIConfiguration shared] set:kConfigDeviceToken data:deviceToken];
    
    // signal.
    [self emit:kSignalDeviceToken result:deviceToken];
}

- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error {
    trace_msg(error.debugDescription);
}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo {
    trace_msg(@"receive a remote notification.");
    
    trace_obj(userInfo);
    
    [self emit:kSignalNotification result:userInfo];
}

# endif

@end

# ifdef WSI_TARGET_IOS

@implementation OpenURLObject

@synthesize url, source, annotation, app;

- (void)dealloc {
    safe_release(url);
    safe_release(source);
    safe_release(annotation);
    safe_release(app);
    [super dealloc];
}

@end

# endif

WSI_END_OBJC

WSI_BEGIN_CXX

class Arguments
: public IArguments
{
public:
    
    Arguments(int argc, char* argv[])
    : argu(argc, argv)
    {
        PASS;
    }
    
    virtual int count() const
    {
        return argu.size();
    }
    
    virtual core::string& at(int idx)
    {
        return argu[idx];
    }
    
    CmdArguments argu;
    
};

static NSAutoreleasePool* __rpool = nil;

Application::Application()
: _app(NULL), _argu(NULL)
{
    // rpool.
    __rpool = [[NSAutoreleasePool alloc] init];
    
    // set global.
    __cxxgs_app = this;
}

Application::Application(WSIApplication* app)
: _argu(NULL)
{
    _app = app;
 
    // set global.
    __cxxgs_app = this;
    
    // set objc app.
    _set(_app);
}

Application::~Application()
{
    [__rpool drain];
    
    safe_delete_type(_argu, Arguments*);
}
    
Application& Application::getInstance()
{
    return *__cxxgs_app;
}

ui::Window& Application::window()
{
    _win._set((ui::Window::objc_type*)__gs_app.window);
    return _win;
}

void Application::open(ns::URL const& url)
{
# ifdef WSI_TARGET_IOS
    [[UIApplication sharedApplication] openURL:url];
# endif
}

int Application::execute(int argc, char* argv[])
{
    if (_argu == NULL)
        _argu = new Arguments(argc, argv);
    return _do_execute(argc, argv);
}

int Application::_do_execute(int argc, char *argv[])
{
    int ret;
    WSI_AUTORELEASEPOOL_BEGIN
    
    try
    {
        WSI_AUTORELEASEPOOL_BEGIN
        
        // main routine.
        
# ifdef WSI_TARGET_IOS
        
        ret = UIApplicationMain(argc, argv, nil, NSStringFromClass([WSIAppImplementation class]));
        
# else
        
        ret = NSApplicationMain(argc, (const char **)argv);
        
# endif
        
        WSI_AUTORELEASEPOOL_END
    }
    catch (NSException* ex)
    {
        trace_fmt(@"Exception: %@: %@ %@.", ex.name, ex.reason, ex.userInfo);
    }
    catch (exception::message const& WSIDEBUG_EXPRESS(ex))
    {
        trace_fmt(@"Exception: %@.", core::type_cast<ns::String>(ex.get()).nsobject());
    }
    catch (::std::exception const& WSIDEBUG_EXPRESS(ex))
    {
        trace_fmt(@"Exception: %@.", core::type_cast<ns::String>(core::string(ex.what())).nsobject());
    }
    catch (...)
    {
        trace_msg(@"Exception: unknown exception.");
    }
    
    WSI_AUTORELEASEPOOL_END
    return ret;
}

void Application::load()
{
    PASS;
}

IArguments* Application::arguments()
{
    return (IArguments*)_argu;
}

void Application::set_appstore(ns::String const& str)
{
    __gs_app.urlInAppStore = str;
}

void Application::enable_filecache()
{
    [__gs_app enableFileCache];
}

void Application::enable_icloud()
{
    [__gs_app enableICloud];
}

void Application::_do_set_root(MAC_IOS_SELECT(NSViewController, UIViewController)* ctlr)
{
    __gs_app.rootViewController = ctlr;
}

# ifdef WSI_TARGET_IOS

bool Application::is_activity() const
{
    return __gs_app.isActivity;
}

void Application::_do_set_initial(UIView *view)
{
    __gs_app.initialView = view;
}

void Application::background()
{
    PASS;
}

void Application::background_expired()
{
    PASS;
}

# endif

class _ApplicationWrapper
{
public:
    
    static void set(Application& app, id _app)
    {
        app._app = _app;
        app._set(_app);
    }
    
};

WSI_END_CXX

WSI_BEGIN_OBJC

@implementation WSIApplicationDelegate

- (void)load {
    ::wsi::_ApplicationWrapper::set(::wsi::Application::getInstance(), __gs_app);
    ::wsi::Application::getInstance().load();
}

@end

@implementation WSIAppImplementation

@end

WSI_END_OBJC

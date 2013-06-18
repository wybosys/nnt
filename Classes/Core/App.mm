
# import "Core.h"
# import "App.h"
# include <stdio.h>
# import "UIObject+NNT.h"
# import "FileCache.h"
# import "Graphic+NNT.h"
# import "Configuration+NNT.h"
# import "CmdArguments.h"
# import "AppInformation.h"
# import "UUID+NNT.h"

# ifdef NNT_TARGET_IOS

#   import "UIDevice+NNT.h"
#   import "UICacheActivityIndicatorView.h"
#   import "AppStoreService.h"

# endif

# ifdef NNT_DEBUG
#   define USE_DTRACE
# endif

# import MAC_IOS_SELECT("./null.prv.h", "UIStatusBarControl.h")

# ifdef USE_DTRACE
#   import MAC_IOS_SELECT("./null.prv.h", "DTraceLogoSwitch.h")
# endif

# import "AppStatistics.h"

NNT_BEGIN_CXX

static Application* __cxxgs_app = NULL;

NNT_END_CXX

NNT_BEGIN_OBJC

# define kCacheActivityIndicatorDuration .5f
# define kCacheActivityIndicatorHideWait 2.f
# define kCacheActivityIndicatorSize 30, 30
# define kCacheActivityIndicatorPos .75

signal_t kSignalAppOpenUrl = @"::nnt::app::openurl";
signal_t kSignalAppFinishLaunching = @"::nnt::app::finish_launching";
signal_t kSignalAppHiding = @"::nnt::app::hiding";
signal_t kSignalAppHiden = @"::nnt::app::hiden";
signal_t kSignalAppShowing = @"::nnt::app::showing";
signal_t kSignalAppShown = @"::nnt::app::shown";
signal_t kSignalAppActiving = @"::nnt::app::activing";
signal_t kSignalAppActived = @"::nnt::app::actived";
signal_t kSignalAppInactiving = @"::nnt::app::inactiving";
signal_t kSignalAppInactived = @"::nnt::app::inactived";
signal_t kSignalAppBackground = @"::nnt::app::background::in";
signal_t kSignalAppBackgroundExpired = @"::nnt::app::background::expired";
signal_t kSignalNotification = @"::nnt::notification";
signal_t kSignalDeviceToken = @"::nnt::devicetoken::got";
signal_t kSignalMemoryWarning = @"::nnt::memory::warning";

NSString* kConfigDeviceToken = @"::nnt::config::device::token";

extern void LoadTheme(NSString*);

static NNTApplication *__gs_app = nil;
bool __need_manual_appear = false;
bool NNT_DEVICE_ISIPHONE = false;
bool NNT_DEVICE_ISIPHONE_SIMULATOR = false;
bool NNT_DEVICE_ISIPAD = false;
bool NNT_DEVICE_ISIPAD_SIMULATOR = false;
bool NNT_DEVICE_ISIPOD = false;
bool NNT_DEVICE_ISSIMULATOR = false;
bool NNT_SUPPORT_BLOCKS = false;
bool NNT_SUPPORT_MULTITASKS = false;
double DEVICE_VERSION = 0;

# ifdef NNT_TARGET_IOS

@interface IOSDefaultWindow : NNTUIWindow {
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
    
    ::nnt::cg::TransformRect rc_logo(::nnt::cg::Rect(64, 64, 32, 32),
                                     [[UIDevice currentDevice] transform]);
    _logo.logicFrame = rc_logo;
    [self bringSubviewToFront:_logo];
    
# endif
}

@end

# endif

NNTDECL_PRIVATE_BEGIN(NNTApplication, NNTObject)
MACEXPRESS(<NSWindowDelegate>)
{
    BSEAppInformation* _bse_appinfo;
    int _countNetworkActivityIndicator;
    BOOL _appIsActivity;
    AppStatistics* _appstat;
}

@property (nonatomic, assign) int countNetworkActivityIndicator;
@property (nonatomic, assign) BOOL appIsActivity;
@property (nonatomic, retain) AppStatistics* appStat;

NNTDECL_PRIVATE_IMPL(NNTApplication)

@synthesize countNetworkActivityIndicator = _countNetworkActivityIndicator;
@synthesize appIsActivity = _appIsActivity;
@synthesize appStat = _appstat;

- (id)init {
    self = [super init];
    
    _countNetworkActivityIndicator = 0;
    _appIsActivity = NO;
    
    // init bse.
    _bse_appinfo = [[BSEAppInformation alloc] init];
    _bse_appinfo.app = d_owner;
    
    return self;
}

- (void)dealloc {
    
    safe_release(_bse_appinfo);
    safe_release(_appstat);
    
    [super dealloc];
}

NNTDECL_PRIVATE_END

@implementation NNTApplication

@synthesize window = _window;
@synthesize applicationName = _applicationName, applicationURLScheme = _applicationURLScheme, applicationIdentity = _applicationIdentity, urlInAppStore = _urlInAppStore;
@dynamic networkActivityIndicatorVisible;
@synthesize rootViewController = _rootViewController;

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(NNTApplication);
    
    // init NNT environment.
    [NNT Init];
    
    // bin app to global.
    __gs_app = self;
    
    if (::nnt::__cxxgs_app)
        ::nnt::__cxxgs_app->replace(__gs_app);
    
# ifdef NNT_TARGET_IOS
    
    __need_manual_appear = need_manual_appear();
    
    NNT_DEVICE_ISIPHONE_SIMULATOR = [UIDevice isIPhoneSimulator];
    NNT_DEVICE_ISIPHONE = [UIDevice isIPhone] | NNT_DEVICE_ISIPHONE_SIMULATOR;
    NNT_DEVICE_ISIPAD_SIMULATOR = [UIDevice isIPadSimulator];
    NNT_DEVICE_ISIPAD = [UIDevice isIPad] | NNT_DEVICE_ISIPAD_SIMULATOR;
    NNT_DEVICE_ISIPOD = [UIDevice isIPod];
    NNT_DEVICE_ISSIMULATOR = NNT_DEVICE_ISIPHONE_SIMULATOR | NNT_DEVICE_ISIPAD_SIMULATOR;
    
    NNT_SUPPORT_BLOCKS = support_blocks();
    NNT_SUPPORT_MULTITASKS = support_multitasks();
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
    
    // end nnt.
    [NNT Fin];
    
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

# ifdef NNT_TARGET_IOS

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
    NNT_SYNCHRONIZED(self)
    
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
    
    NNT_SYNCHRONIZED_END
}

+ (NSString*)Identity {
    return [[[NSBundle mainBundle] infoDictionary] valueForKey:(NSString*)kCFBundleIdentifierKey];
}

+ (NSString*)Name {
    return [[[NSBundle mainBundle] infoDictionary] valueForKey:(NSString*)kCFBundleNameKey];
}

# endif // end ios.

+ (NSString*)DeviceIdentity {
    NSString* idr = [[NNTConfiguration shared] get:@"::nnt::device::identity" null:nil];
    if (idr != nil)
        return idr;
    idr = uuid_string();
    [[NNTConfiguration shared] set:@"::nnt::device::identity" val:idr];
    return idr;
}

# ifdef NNT_TARGET_MAC

+ (NSString*)Identity {
    return NULL;
}

+ (NSString*)Name {
    return @"";
}

# endif

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalAppOpenUrl)
NNTEVENT_SIGNAL(kSignalAppHiding)
NNTEVENT_SIGNAL(kSignalAppHiden)
NNTEVENT_SIGNAL(kSignalAppShowing)
NNTEVENT_SIGNAL(kSignalAppShown)
NNTEVENT_SIGNAL(kSignalAppActiving)
NNTEVENT_SIGNAL(kSignalAppActived)
NNTEVENT_SIGNAL(kSignalAppInactiving)
NNTEVENT_SIGNAL(kSignalAppInactived)
NNTEVENT_SIGNAL(kSignalAppFinishLaunching)
NNTEVENT_SIGNAL(kSignalAppBackground)
NNTEVENT_SIGNAL(kSignalAppBackgroundExpired)
NNTEVENT_SIGNAL(kSignalNotification)
NNTEVENT_SIGNAL(kSignalDeviceToken)
NNTEVENT_SIGNAL(kSignalMemoryWarning)
NNTEVENT_END

+ (NNTApplication*)shared {
    return __gs_app;
}

+ (NNTApplication*)current {
    return __gs_app;
}

- (void)load {
    PASS;
}

// for mac
# ifdef NNT_TARGET_MAC

void LoadTheme(NSString*) {
    PASS;
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    trace_msg(@"application: launching.");
    
    // boot nnt.
    [NNT Boot];
    
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
    [NNT Active];
    
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
    [NNT Inactive];
    
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
    if (_rootViewController == ctlr)
        return;
    
    NSView* view = ctlr.view;
    self.window.contentView = view;

    [NSObject refobjSet:&_rootViewController ref:ctlr];
}

- (void)setWindow:(NSWindow *)win {
    if (_window == win)
        return;
    
    [NSObject refobjSet:&_window ref:win];
    
    _window.delegate = d_ptr;
}

# endif

// for IOS
# ifdef NNT_TARGET_IOS

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
    
    // boot nnt.
    [NNT Boot];
    
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
    
# ifdef NNT_iOS_4
    
    self.window.rootViewController = _rootViewController;
    
# else
    
    // get frame.
    rootViewController.view.frame = self.window.bounds;
    [self.window addSubview:rootViewController.view];
    
# endif
}

- (void)background:(UIApplication*)app {
    trace_msg(@"run background operation.");
    
# ifdef NNT_DEBUG
    
    NSTimeInterval ti = app.backgroundTimeRemaining;
    trace_fmt(@"left %d seconds for background run.", (int)ti);
    
# endif
    
    if (::nnt::__cxxgs_app)
        ::nnt::__cxxgs_app->background();
    
    [self emit:kSignalAppBackground];
}

- (void)backgroundExpired:(UIApplication*)app {
    trace_msg(@"background is expired.");
    
    if (::nnt::__cxxgs_app)
        ::nnt::__cxxgs_app->background_expired();
    
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
        [NNTObject refobjCopy:&_applicationURLScheme ref:@""];
        return nil;
    }
    
    [NNTObject refobjCopy:&_applicationURLScheme ref:str];
    
    return str;
}

- (NSString*)applicationName {
    if (_applicationName)
        return _applicationName;
    
    NSString *str = (NSString*)[[NSBundle mainBundle] objectForInfoDictionaryKey:(NSString*)kCFBundleNameKey];
    if (str == nil) {
        [NNTObject refobjCopy:&_applicationName ref:@""];
        return _applicationName;
    }
    
    [NNTObject refobjCopy:&_applicationName ref:str];

    return _applicationName;
}

- (NSString*)applicationIdentity {
    if (_applicationIdentity)
        return _applicationIdentity;
    NSString *str = (NSString*)[[NSBundle mainBundle] objectForInfoDictionaryKey:(NSString*)kCFBundleIdentifierKey];
    if (str == nil) {
        [NNTObject refobjCopy:&_applicationIdentity ref:@""];
        return _applicationIdentity;
    }
    
    [NNTObject refobjCopy:&_applicationIdentity ref:str];

    return _applicationIdentity;
}

# ifdef NNT_TARGET_IOS

- (void)enableStatistics {
    //AppStatistics* as = [[AppStatistics alloc] init];
    //d_ptr.appStat = as;
    //safe_release(as);
}

- (void)applicationWillTerminate:(UIApplication *)application {
    trace_msg(@"application: terminating.");
    
# ifdef NNT_DEBUG
    
    [Msgbox warn:@"Application Terminating !"];
    
# endif
}

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    trace_msg(@"application: memory warning!");
    
# ifdef NNT_DEBUG
    
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
    [NNT Active];
    
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
    [NNT Inactive];
    
    // emit signal.
    [self emit:kSignalAppInactived];
    
    // call cxx background function.
    if (::nnt::__cxxgs_app) {
        
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
    [[NNTUIObject shared] emit:kSignalOrientationChanged];
}

NSString *kOpenUrlTarget = @"url";
NSString *kOpenUrlSource = @"source";
NSString *kOpenUrlAnno = @"annotation";
NSString *kOpenUrlApp = @"app";

- (BOOL)application:

# ifdef NNT_iOS_4

(UIApplication *)application 
            openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication
         annotation:(id)annotation

# else

(UIApplication *)application
handleOpenURL:(NSURL *)url

# endif

{
# ifdef NNT_iOS_4
    
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
    FileCache *cache = [[FileCache alloc] initWithPath:@"cache" type:NSVariableDirectory | NNTDirectoryTypeSystem];
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

# ifdef NNT_iOS_3

- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification {
    
# ifdef NNT_DEBUG
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
    [[NNTConfiguration shared] set:kConfigDeviceToken data:deviceToken];
    
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

# ifdef NNT_TARGET_IOS

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

NNT_END_OBJC

NNT_BEGIN_CXX

class Arguments
: public IArguments
{
public:
    
    Arguments(int argc, char* argv[])
    : argu(argc, argv)
    {
        PASS;
    }
    
    virtual usize count() const
    {
        return argu.size();
    }
    
    virtual core::string& at(int idx)
    {
        return argu[idx];
    }
    
    cmd::Arguments argu;
    
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

Application::Application(NNTApplication* app)
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
    
    safe_delete<Arguments>(_argu);
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
# ifdef NNT_TARGET_IOS
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
    NNT_AUTORELEASEPOOL_BEGIN
    
    try
    {
        NNT_AUTORELEASEPOOL_BEGIN
        
        // main routine.
        
# ifdef NNT_TARGET_IOS
        
        ret = UIApplicationMain(argc, argv, nil, NSStringFromClass([NNTAppImplementation class]));
        
# else
        
        ret = NSApplicationMain(argc, (const char **)argv);
        
# endif
        
        NNT_AUTORELEASEPOOL_END
    }
    catch (NSException* ex)
    {
        trace_fmt(@"Exception: %@: %@ %@.", ex.name, ex.reason, ex.userInfo);
    }
    catch (exception::message const& NNTDEBUG_EXPRESS(ex))
    {
        trace_fmt(@"Exception: %@.", core::type_cast<ns::String>(ex.get()).nsobject());
    }
    catch (::std::exception const& NNTDEBUG_EXPRESS(ex))
    {
        trace_fmt(@"Exception: %@.", core::type_cast<ns::String>(core::string(ex.what())).nsobject());
    }
    catch (...)
    {
        trace_msg(@"Exception: unknown exception.");
    }
    
    NNT_AUTORELEASEPOOL_END
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

void Application::enable_statistics()
{
    //[__gs_app enableStatistics];
}

void Application::_do_set_root(MAC_IOS_SELECT(NSViewController, UIViewController)* ctlr)
{
    __gs_app.rootViewController = ctlr;
}

# ifdef NNT_TARGET_IOS

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

NNT_END_CXX

NNT_BEGIN_OBJC

@implementation NNTApplicationDelegate

- (void)load {
    ::nnt::_ApplicationWrapper::set(::nnt::Application::getInstance(), __gs_app);
    ::nnt::Application::getInstance().load();
}

@end

@implementation NNTAppImplementation

@end

NNT_END_OBJC


# ifndef __NNT_CORE_APP_E360275B13394967BD08A1ACD9F2F9C4_H_INCLUDED
# define __NNT_CORE_APP_E360275B13394967BD08A1ACD9F2F9C4_H_INCLUDED

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX

class IArguments
{
public:

    virtual usize count() const = 0;
    virtual core::string& at(int) = 0;

};

class IApplication
{
public:
    
    IApplication() {}
    virtual ~IApplication() {}
    
    //! execute.
    virtual int execute(int argc, char *argv[]) = 0;

    //! get arguments.
    virtual IArguments* arguments() = 0;
    
    //! load.
    virtual void load() = 0;
    
};

NNT_END_HEADER_CXX

# endif

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

IOSEXPRESS(NNTDECL_EXTERN_CLASS(UIStatusBarControl));

NNTDECL_PRIVATE_HEAD(NNTApplication);

@interface NNTApplication : NNTObject <
IOSEXPRESS(UIApplicationDelegate)
MACEXPRESS(NSApplicationDelegate)
> {
    
    //! app info.
    NSString *_applicationName, *_applicationIdentity, *_applicationURLScheme, *_urlInAppStore;
    
    //! window.
    MAC_IOS_SELECT(NSWindow, UIWindow) *_window;
    
    //! root view controller.
    MAC_IOS_SELECT(NSViewController, UIViewController) *_rootViewController;
    
    NNTDECL_PRIVATE(NNTApplication);
}

@property (nonatomic, copy) NSString *applicationName, *applicationIdentity, *applicationURLScheme, *urlInAppStore;
@property (assign) BOOL networkActivityIndicatorVisible;
@property (nonatomic, retain) MAC_IOS_SELECT(NSWindow, UIWindow) *window;
@property (nonatomic, retain) MAC_IOS_SELECT(NSViewController, UIViewController) *rootViewController;

//!load for unity program.
- (void)load;

// for mac.
# ifdef NNT_TARGET_MAC

- (void)load:(NSNotification*)aNotification;

# endif

// for ios.
# ifdef NNT_TARGET_IOS

//! window.
- (UIWindow*)currentWindow;

//! load.
- (void)load:(UIApplication *)application options:(NSDictionary *)launchOptions;

//! overridable function.

- (void)background:(UIApplication*)app;
- (void)backgroundExpired:(UIApplication*)app;

@property (nonatomic, assign) UIView* initialView;

//! if app is activity.
- (BOOL)isActivity;

//! start app statistics.
- (void)enableStatistics;

# endif

//! shared.
+ (NNTApplication*)shared;
+ (NNTApplication*)current;

//! enable file cache.
- (void)enableFileCache;

//! enable icloud.
- (void)enableICloud;

//! get app's info.
+ (NSString*)Identity;
+ (NSString*)Name;

//! get device identity.
+ (NSString*)DeviceIdentity;

@end

# ifdef NNT_TARGET_IOS

@interface OpenURLObject : NSObject

@property (nonatomic, copy) NSURL* url;
@property (nonatomic, copy) NSString *source, *annotation;
@property (nonatomic, retain) UIApplication* app;

@end

NNT_EXTERN bool __need_manual_appear;

NNT_EXTERN bool NNT_DEVICE_ISIPHONE;
NNT_EXTERN bool NNT_DEVICE_ISIPHONE_SIMULATOR;
NNT_EXTERN bool NNT_DEVICE_ISIPAD;
NNT_EXTERN bool NNT_DEVICE_ISIPAD_SIMULATOR;
NNT_EXTERN bool NNT_DEVICE_ISIPOD;
NNT_EXTERN bool NNT_DEVICE_ISSIMULATOR;

NNT_EXTERN bool NNT_SUPPORT_BLOCKS;
NNT_EXTERN bool NNT_SUPPORT_MULTITASKS;

NNT_EXTERN double DEVICE_VERSION;

# endif

//! open a url.
NNT_EXTERN signal_t kSignalAppOpenUrl;
NNT_EXTERN NSString *kOpenUrlTarget;
NNT_EXTERN NSString *kOpenUrlSource;
NNT_EXTERN NSString *kOpenUrlAnno;
NNT_EXTERN NSString *kOpenUrlApp;

//! notification.
NNT_EXTERN signal_t kSignalNotification;
NNT_EXTERN signal_t kSignalDeviceToken;

//! app control.
NNT_EXTERN signal_t kSignalAppFinishLaunching;
NNT_EXTERN signal_t kSignalMemoryWarning;

//! hide.
NNT_EXTERN signal_t kSignalAppHiding;
NNT_EXTERN signal_t kSignalAppHiden;
NNT_EXTERN signal_t kSignalAppShowing;
NNT_EXTERN signal_t kSignalAppShown;

//! active.
NNT_EXTERN signal_t kSignalAppActiving;
NNT_EXTERN signal_t kSignalAppActived;
NNT_EXTERN signal_t kSignalAppInactiving;
NNT_EXTERN signal_t kSignalAppInactived;

//! background.
NNT_EXTERN signal_t kSignalAppBackground;
NNT_EXTERN signal_t kSignalAppBackgroundExpired;

//! key.
NNT_EXTERN NSString* kConfigDeviceToken;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# ifdef NNT_TARGET_IOS
# include "UIWindow+NNT.h"
# else
# include "../UIKit/NSWindow+NNT.h"
# endif

NNT_BEGIN_HEADER_OBJC

@interface NNTApplicationDelegate : NNTApplication
@end

@interface NNTAppImplementation : NNTApplicationDelegate
@end

NNT_END_HEADER_OBJC

NNT_BEGIN_HEADER_CXX

class _ApplicationWrapper;

class Application
: public ns::Object<>,
public IApplication
{
    NNTDECL_NOCOPY(Application);
    friend class _ApplicationWrapper;
    
public:
    
    Application();
    Application(NNTApplication*);
    ~Application();
    
    //! get instance of app.
    static Application& getInstance();
    
    //! get window.
    ui::Window& window();
    
    //! open url.
    void open(ns::URL const& url);
    
    // impl.
    virtual int execute(int argc, char *argv[]);
    virtual void load();
    virtual IArguments* arguments();
    
    //! enable file cache.
    void enable_filecache();
    
    //! enable icloud store.
    void enable_icloud();
    
    //! enable app statistics.
    void enable_statistics();
    
    //! set controller.
    template <typename ctlrT>
    void set_root(ctlrT& ctlr)
    {
        ntl::const_pointer<ctlrT> ptr(ctlr);
        this->_do_set_root(*ptr);
        _root = &ctlr;
    }
    
    //! get root.
    template <typename ctlrT>
    ctlrT& root()
    {
        return *(ctlrT*)_root;
    }
    
    //! overridable function.
    
# ifdef NNT_TARGET_IOS
    
    //! callback for background run.
    virtual void background_expired();
    virtual void background();
    
    //! set initial view.
    template <typename viewT>
    void set_initial(viewT& view)
    {
        ntl::const_pointer<viewT> ptr(view);
        this->_do_set_initial(*ptr);
    }
    
    bool is_activity() const;
    
# endif
    
    NNTApplication* nsobject()
    {
        return _app;
    }
    
    void set_appstore(ns::String const&);
    
protected:
    
    int _do_execute(int argc, char* argv[]);
    
    void _do_set_root(MAC_IOS_SELECT(NSViewController, UIViewController)* ctlr);
    
# ifdef NNT_TARGET_IOS
    
    void _do_set_initial(UIView*);
    
# endif
    
    //! object.
    NNTApplication* _app;
    
    //! window.
    ui::Window _win;
    
    //! root.
    void* _root;
    
    //! cmd.
    void* _argu;
    
};

NNT_END_HEADER_CXX

# endif

# endif

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX

NNTCLASS(Environment);

class Environment
{
public:
    
    Environment();
    ~Environment();
    
public:
    
    //! get instance.
    NNT_STATIC Environment* getInstance();
    
    //! get directory.
    NNT_STATIC core::string workingDirectory();
    
    //! replace working directory, not change to system's current directory.
    NNT_STATIC void replaceWorkingDirectory(core::string const&);
    
};

# ifdef NNT_CROSS_PLATFORM

NNT_BEGIN_NS(ui)
NNT_BEGIN_NS(uc)

class Window;

NNT_END_NS
NNT_END_NS

NNT_BEGIN_NS(cross)

NNTCLASS(Console);

class Console
    : public cxx::Object<>,
public IApplication
{
public:

    Console();
    ~Console();

    virtual void load();
    virtual int execute(int argc, char *argv[]);
    virtual IArguments* arguments();

protected:

    void _doload();

    void* _cmd;

};

NNTCLASS(Application);

class Application
: public cxx::Object<>,
public IApplication
{
public:
    
    Application();
    ~Application();
    
public:
    
    //! impl.
    virtual void load();
    virtual int execute(int argc, char *argv[]);
    virtual IArguments* arguments();
    
    // get.
    static Application& getInstance();
    
public:
    
    //! set root.
    template <typename rootT>
    void set_root(rootT const& obj)
    {
        core::const_pointer<rootT> ptr(obj);
        _root = (void*)&*ptr;
    }
    
    void* root() const
    {
        return (void*)_root;
    }
    
    ui::uc::Window* window() const
    {
        return (ui::uc::Window*)_window;
    }
    
protected:
    
    void* _root;
    ui::uc::Window* _window;
    
};

NNT_END_NS // cross

# endif

NNT_END_HEADER_CXX

# ifdef NNTAPP_GUI

extern int NNT_MAIN(int, char**);

# endif

# if defined(NNTAPP_GUI) && defined(NNT_MSVC)

# include "../UIKit/Cross/UcKernel.h"

extern "C" int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int windowStyle)
{
    NNT_USINGNAMESPACE;
    ui::uc::msvc::BackgroundWindow bw;
    bw.cmd = lpCmdLine;
    bw.hcurrent = hInstance;
    bw.hprevious = hPrevInstance;
    bw.ws = windowStyle;
    bw.entry = NNT_MAIN;
    return bw.main();
}

# endif

# endif

# endif
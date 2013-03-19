
# ifndef __WSI_CORE_APP_E360275B13394967BD08A1ACD9F2F9C4_H_INCLUDED
# define __WSI_CORE_APP_E360275B13394967BD08A1ACD9F2F9C4_H_INCLUDED

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX

class IArguments
{
public:

    virtual int count() const = 0;
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

WSI_END_HEADER_CXX

# endif

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

IOSEXPRESS(WSIDECL_EXTERN_CLASS(UIStatusBarControl));

WSIDECL_PRIVATE_HEAD(WSIApplication);

@interface WSIApplication : WSIObject <
IOSEXPRESS(UIApplicationDelegate)
MACEXPRESS(NSApplicationDelegate)
> {
    
    //! app info.
    NSString *_applicationName, *_applicationIdentity, *_applicationURLScheme, *_urlInAppStore;
    
    //! window.
    MAC_IOS_SELECT(NSWindow, UIWindow) *_window;
    
    //! root view controller.
    MAC_IOS_SELECT(NSViewController, UIViewController) *_rootViewController;
    
    WSIDECL_PRIVATE(WSIApplication);
}

@property (nonatomic, copy) NSString *applicationName, *applicationIdentity, *applicationURLScheme, *urlInAppStore;
@property (assign) BOOL networkActivityIndicatorVisible;
@property (nonatomic, retain) MAC_IOS_SELECT(NSWindow, UIWindow) *window;
@property (nonatomic, retain) MAC_IOS_SELECT(NSViewController, UIViewController) *rootViewController;

//!load for unity program.
- (void)load;

// for mac.
# ifdef WSI_TARGET_MAC

- (void)load:(NSNotification*)aNotification;

# endif

// for ios.
# ifdef WSI_TARGET_IOS

//! window.
- (UIWindow*)currentWindow;

//! load.
- (void)load:(UIApplication *)application options:(NSDictionary *)launchOptions;

//! overridable function.

- (void)background:(UIApplication*)app;
- (void)backgroundExpired:(UIApplication*)app;

@property (nonatomic, assign) UIView* initialView;

- (BOOL)isActivity;

# endif

//! shared.
+ (WSIApplication*)shared;
+ (WSIApplication*)current;

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

# ifdef WSI_TARGET_IOS

@interface OpenURLObject : NSObject

@property (nonatomic, copy) NSURL* url;
@property (nonatomic, copy) NSString *source, *annotation;
@property (nonatomic, retain) UIApplication* app;

@end

WSI_EXTERN bool __need_manual_appear;

WSI_EXTERN bool WSI_DEVICE_ISIPHONE;
WSI_EXTERN bool WSI_DEVICE_ISIPHONE_SIMULATOR;
WSI_EXTERN bool WSI_DEVICE_ISIPAD;
WSI_EXTERN bool WSI_DEVICE_ISIPAD_SIMULATOR;
WSI_EXTERN bool WSI_DEVICE_ISIPOD;
WSI_EXTERN bool WSI_DEVICE_ISSIMULATOR;

WSI_EXTERN bool WSI_SUPPORT_BLOCKS;
WSI_EXTERN bool WSI_SUPPORT_MULTITASKS;

WSI_EXTERN double DEVICE_VERSION;

# endif

//! open a url.
WSI_EXTERN signal_t kSignalAppOpenUrl;
WSI_EXTERN NSString *kWSIApp_Url;
WSI_EXTERN NSString *kWSIApp_Source;
WSI_EXTERN NSString *kWSIApp_Anno;
WSI_EXTERN NSString *kWSIApp_App;

//! notification.
WSI_EXTERN signal_t kSignalNotification;
WSI_EXTERN signal_t kSignalDeviceToken;

//! app control.
WSI_EXTERN signal_t kSignalAppFinishLaunching;
WSI_EXTERN signal_t kSignalMemoryWarning;

//! hide.
WSI_EXTERN signal_t kSignalAppHiding;
WSI_EXTERN signal_t kSignalAppHiden;
WSI_EXTERN signal_t kSignalAppShowing;
WSI_EXTERN signal_t kSignalAppShown;

//! active.
WSI_EXTERN signal_t kSignalAppActiving;
WSI_EXTERN signal_t kSignalAppActived;
WSI_EXTERN signal_t kSignalAppInactiving;
WSI_EXTERN signal_t kSignalAppInactived;

//! background.
WSI_EXTERN signal_t kSignalAppBackground;
WSI_EXTERN signal_t kSignalAppBackgroundExpired;

//! key.
WSI_EXTERN NSString* kConfigDeviceToken;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# ifdef WSI_TARGET_IOS
# include "UIWindow+WSI.h"
# else
# include "../UIKit/NSWindow+WSI.h"
# endif

WSI_BEGIN_HEADER_OBJC

@interface WSIApplicationDelegate : WSIApplication
@end

@interface WSIAppImplementation : WSIApplicationDelegate
@end

WSI_END_HEADER_OBJC

WSI_BEGIN_HEADER_CXX

class _ApplicationWrapper;

class Application
: public ns::Object<>,
public IApplication
{
    WSIDECL_NOCOPY(Application);
    friend class _ApplicationWrapper;
    
public:
    
    Application();
    Application(WSIApplication*);
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
    
    //! set controller.
    template <typename ctlrT>
    void set_root(ctlrT& ctlr)
    {
        wtl::const_pointer<ctlrT> ptr(ctlr);
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
    
# ifdef WSI_TARGET_IOS
    
    //! callback for background run.
    virtual void background_expired();
    virtual void background();
    
    //! set initial view.
    template <typename viewT>
    void set_initial(viewT& view)
    {
        wtl::const_pointer<viewT> ptr(view);
        this->_do_set_initial(*ptr);
    }
    
    bool is_activity() const;
    
# endif
    
    WSIApplication* nsobject()
    {
        return _app;
    }
    
    void set_appstore(ns::String const&);
    
protected:
    
    int _do_execute(int argc, char* argv[]);
    
    void _do_set_root(MAC_IOS_SELECT(NSViewController, UIViewController)* ctlr);
    
# ifdef WSI_TARGET_IOS
    
    void _do_set_initial(UIView*);
    
# endif
    
    //! object.
    WSIApplication* _app;
    
    //! window.
    ui::Window _win;
    
    //! root.
    void* _root;
    
    //! cmd.
    void* _argu;
    
};

WSI_END_HEADER_CXX

# endif

# endif

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX

WSICLASS(Environment);

class Environment
{
public:
    
    Environment();
    ~Environment();
    
public:
    
    //! get instance.
    WSI_STATIC Environment* getInstance();
    
    //! get directory.
    WSI_STATIC core::string workingDirectory();
    
    //! replace working directory, not change to system's current directory.
    WSI_STATIC void replaceWorkingDirectory(core::string const&);
    
};

# ifdef WSI_CROSS_PLATFORM

WSI_BEGIN_NS(ui)
WSI_BEGIN_NS(uc)

class Window;

WSI_END_NS
WSI_END_NS

WSI_BEGIN_NS(cross)

WSICLASS(Console);

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

WSICLASS(Application);

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

WSI_END_NS

# endif

WSI_END_HEADER_CXX

# endif

# endif

# ifndef __WSI_UIKIT_UICHMCONTROLLER_A383D5DFEA844E779D9265318138AC60_H_INCLUDED
# define __WSI_UIKIT_UICHMCONTROLLER_A383D5DFEA844E779D9265318138AC60_H_INCLUDED

# import "UIViewController+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(UICHMController);

@interface UICHMController : WSIUIViewController {
    
    UINavigationController *navi;
    
    WSIDECL_PRIVATE(UICHMController);
}

@property (nonatomic, retain) UINavigationController *navi;

//! init
- (id)initWithNamed:(NSString*)name;

//! process file.
- (BOOL)readFile:(NSString*)file;
- (BOOL)readNamed:(NSString*)file;

//! clear
- (void)clear;

# pragma mark act

- (void)fileDidLoaded;

@end

_CXXCONTROLLER_DECL(UICHMController);

//! signal for file loaded.
WSI_EXTERN signal_t kSignalFileLoaded;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class CHMController
: public SimpleController<CHMController, _CXXCONTROLLER(UICHMController), WSIUIView>
{
    typedef SimpleController<CHMController, _CXXCONTROLLER(UICHMController), WSIUIView> super;
    
public:
    
    CHMController()
    {
        PASS;
    }
    
    bool read(ns::String const& file)
    {
        return [this->_self readFile:file];
    }
    
    bool read_named(ns::String const& name)
    {
        return [this->_self readNamed:name];
    }
    
    void clear()
    {
        [this->_self clear];
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
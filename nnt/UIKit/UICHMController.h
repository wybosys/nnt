
# ifndef __NNT_UIKIT_UICHMCONTROLLER_A383D5DFEA844E779D9265318138AC60_H_INCLUDED
# define __NNT_UIKIT_UICHMCONTROLLER_A383D5DFEA844E779D9265318138AC60_H_INCLUDED

# import "UIViewController+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(UICHMController);

@interface UICHMController : NNTUIViewController {
    
    UINavigationController *navi;
    
    NNTDECL_PRIVATE(UICHMController);
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
NNT_EXTERN signal_t kSignalFileLoaded;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class CHMController
: public SimpleController<CHMController, _CXXCONTROLLER(UICHMController), NNTUIView>
{
    typedef SimpleController<CHMController, _CXXCONTROLLER(UICHMController), NNTUIView> super;
    
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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
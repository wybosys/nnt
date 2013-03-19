
# ifndef __WSI_NS_RUNLOOP_D03D196FC51D43E0A44A94ECD2A3D262_H_INCLUDED
# define __WSI_NS_RUNLOOP_D03D196FC51D43E0A44A94ECD2A3D262_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface NSRunSection : WSIObject {
    CFRunLoopRef _rl;
}

- (void)block;
- (void)unblock;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ns)

class Runloop
: public ns::Object<NSRunLoop>
{
    typedef ns::Object<NSRunLoop> super;
    
public:
    
    Runloop()
    {
        PASS;
    }
    
    Runloop(objc_type* rl)
    : super(rl)
    {
        PASS;
    }
    
    static Runloop Current()
    {
        return [NSRunLoop currentRunLoop];
    }
    
    static Runloop Main()
    {
        static Runloop st_main([NSRunLoop mainRunLoop]);
        return st_main;
    }
    
    String mode() const
    {
        return this->_self.currentMode;
    }
    
    void run()
    {
        [this->_self run];
    }
    
    void run(String const& mode, Date const& de)
    {
        [this->_self runMode:mode beforeDate:de];
    }
    
    void run(Date const& de)
    {
        [this->_self runUntilDate:de];
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif

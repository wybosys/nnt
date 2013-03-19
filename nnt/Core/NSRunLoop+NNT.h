
# ifndef __NNT_NS_RUNLOOP_D03D196FC51D43E0A44A94ECD2A3D262_H_INCLUDED
# define __NNT_NS_RUNLOOP_D03D196FC51D43E0A44A94ECD2A3D262_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface NSRunSection : NNTObject {
    CFRunLoopRef _rl;
}

- (void)block;
- (void)unblock;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ns)

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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif

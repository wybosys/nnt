
# ifndef __WSI_CORE_CONSOLE_E8C0848EFFA14ED394F3FEBE2A7B72FC_H_INCLUDED
# define __WSI_CORE_CONSOLE_E8C0848EFFA14ED394F3FEBE2A7B72FC_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface WSIConsole : WSIObject {
    void* h_console;
}

- (void)print:(NSString*)str;
- (void)println:(NSString*)str;

+ (WSIConsole*)shared;

@end

WSI_EXTERN signal_t kSignalPrint;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX

class Console
: public ns::Object<>
{
    
public:
    
    Console();
    ~Console();
    
    static char const* prefix;
    static char const* suffix;
    
public:
    
    void print(char const*) const;
    void println(char const*) const;
    
protected:
    
    FILE *_hout, *_hin, *_herr;
    int _hdup:3;
    
private:
    
    mutable bool _nln;
    
    static void* watcher_input(void*);
};

WSI_END_HEADER_CXX

# endif

# endif
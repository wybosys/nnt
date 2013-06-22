
# ifndef __NNT_CORE_CONSOLE_E8C0848EFFA14ED394F3FEBE2A7B72FC_H_INCLUDED
# define __NNT_CORE_CONSOLE_E8C0848EFFA14ED394F3FEBE2A7B72FC_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface NNTConsole : NNTObject {
    void* h_console;
}

- (void)print:(NSString*)str;
- (void)println:(NSString*)str;

+ (NNTConsole*)shared;

@end

NNT_EXTERN signal_t kSignalPrint;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX

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

NNT_END_HEADER_CXX

# endif

# endif
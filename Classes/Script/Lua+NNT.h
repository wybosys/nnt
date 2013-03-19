
# ifndef __NNT_LUA_811675FC155E4821BDC91B270362A462_H_INCLUDED
# define __NNT_LUA_811675FC155E4821BDC91B270362A462_H_INCLUDED

# include "NNTScript.h"

NNT_BEGIN_HEADER_C

struct _wlua_State
{
    struct lua_State* state;
    struct _wlua_Processor* processor;
};

struct _wlua_Processor
{
    struct _wlua_State state;
    int stack_count;
};

typedef _wlua_State wlua_State;
typedef _wlua_Processor wlua_Processor;

NNTAPI(wlua_Processor*) wlua_Open();
NNTAPI(void) wlua_Close(wlua_Processor*);
NNTAPI(void) wluaopen_kernel(struct lua_State*);

static struct lua_State* wluaL(wlua_Processor* proc)
{
    return proc->state.state;
}

NNT_END_HEADER_C

// for object-c

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(NNTLua);

@interface NNTLua : NNTObject <NNTScript> {
    
    NNTDECL_PRIVATE(NNTLua);
}

@property (nonatomic, readonly) wlua_Processor* processor;

//! execute string.
- (BOOL)executeUTF8String:(char const*)expr;

@end

NNT_END_HEADER_OBJC

# endif

// for c++

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(script)

class Lua
: public cxx::Object<>
{
public:
    
    Lua();
    ~Lua();
    
protected:
    
    wlua_Processor* _proc;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif

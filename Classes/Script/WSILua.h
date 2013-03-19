
# ifndef __WSI_LUA_811675FC155E4821BDC91B270362A462_H_INCLUDED
# define __WSI_LUA_811675FC155E4821BDC91B270362A462_H_INCLUDED

# include "WSIScript.h"

WSI_BEGIN_HEADER_C

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

WSIAPI(wlua_Processor*) wlua_Open();
WSIAPI(void) wlua_Close(wlua_Processor*);
WSIAPI(void) wluaopen_kernel(struct lua_State*);

static struct lua_State* wluaL(wlua_Processor* proc)
{
    return proc->state.state;
}

WSI_END_HEADER_C

// for object-c

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(WSILua);

@interface WSILua : WSIObject <WSIScript> {
    
    WSIDECL_PRIVATE(WSILua);
}

@property (nonatomic, readonly) wlua_Processor* processor;

//! execute string.
- (BOOL)executeUTF8String:(char const*)expr;

@end

WSI_END_HEADER_OBJC

# endif

// for c++

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(script)

class Lua
: public cxx::Object<>
{
public:
    
    Lua();
    ~Lua();
    
protected:
    
    wlua_Processor* _proc;
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif

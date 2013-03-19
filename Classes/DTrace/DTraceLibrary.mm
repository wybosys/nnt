
# import "Core.h"
# import "DTraceLibrary.h"
# import "Console+NNT.h"
# import "DTraceController.h"
# include <signal.h>
# import "AbstractCache.h"
# import "NNTConfiguration.h"

NNT_BEGIN_HEADER_C

# include "../../contrib/lua/lua.h"
# include "../../contrib/lua/lstate.h"
# include "../../contrib/lua/lualib.h"
# include "../../contrib/lua/lauxlib.h"

NNT_END_HEADER_C

NNT_BEGIN_C

int wluado_echo(lua_State* state)
{
    int cnt = lua_gettop(state);
    if (cnt != 1)
        return 0;
    
    if (lua_isstring(state, -1))
    {
        char const* str = lua_tostring(state, -1);
        NSString* sstr = [NSString stringWithUTF8String:str];
        [[NNTConsole shared] println:sstr];
    }
    else if (lua_isnumber(state, -1))
    {
        lua_Number nm = lua_tonumber(state, -1);
        NSString* sstr = [NSString stringWithFormat:@"%.14g", nm];
        [[NNTConsole shared] println:sstr];
    }
    else
    {
        [[NNTConsole shared] println:@"echo: Unknown Type."];
    }
    
    return 1;
}

int wluado_clear(lua_State* state)
{
    [[DTraceController shared] clear];
    return 1;
}

int wluado_hide(lua_State* state)
{
    [DTraceController shared].showLogo = NO;
    [[DTraceController shared] hide];
    return 1;
}

int wluado_debug(lua_State* state)
{
    raise(SIGINT);
    return 1;
}

int wluado_cache_clear(lua_State* state)
{
    [[AbstractCache defaultCache] clear];
    return 1;
}

int wluado_configuration_clear(lua_State* state)
{
    [[NNTConfiguration shared] clear];
    ::nnt::store::Configuration::shared().clear();
    return 1;
}

void wluaopen_dtrace_objc(wlua_Processor* proc)
{
    lua_register(wluaL(proc), "echo", wluado_echo);
    lua_register(wluaL(proc), "clear", wluado_clear);
    lua_register(wluaL(proc), "hide", wluado_hide);
    lua_register(wluaL(proc), "debug", wluado_debug);
    
    lua_register(wluaL(proc), "cache_clear", wluado_cache_clear);
    
    lua_register(wluaL(proc), "configuration_clear", wluado_configuration_clear);
}

NNT_END_C

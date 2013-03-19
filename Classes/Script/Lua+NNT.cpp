
# include "Core.h"
# include "NNTLua.h"

NNT_BEGIN_HEADER_C

# include "../../contrib/lua/lua.h"
# include "../../contrib/lua/lstate.h"
# include "../../contrib/lua/lualib.h"
# include "../../contrib/lua/lauxlib.h"

NNT_END_HEADER_C

NNT_BEGIN_C

int wluak_version(lua_State* state)
{
    char const* str = NNT_VERSION_STR;
    lua_pushstring(state, str);
    return 1;
}

int wluak_exit(lua_State* state)
{
    exit(0);
    return 1;
}

void wluaopen_kernel(lua_State* state)
{
    lua_register(state, "version", wluak_version);
    lua_register(state, "exit", wluak_exit);
}

static int wlua_panic(lua_State* state)
{
    trace_msg("lua is paniced.");
    return 1;
}

wlua_Processor* wlua_Open()
{
    wlua_Processor* obj = (wlua_Processor*)malloc(sizeof(wlua_Processor));
    
    obj->state.state = lua_open();
    if (obj->state.state == NULL)
    {
        wlua_Close(obj);
        return NULL;
    }
    
    obj->state.state->custom = obj;
    obj->state.processor = obj;
    obj->stack_count = 0;
    
    // pack.
    lua_atpanic(obj->state.state, wlua_panic);
    
    return obj;
}

void wlua_Close(wlua_Processor* obj)
{
    free(obj);
}

NNT_END_C

NNT_BEGIN_CXX
NNT_BEGIN_NS(script)

Lua::Lua()
{
    _proc = wlua_Open();
}

Lua::~Lua()
{
    wlua_Close(_proc);
}

NNT_END_NS
NNT_END_CXX

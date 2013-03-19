
# include "Core.h"
# include "DTraceLibrary.h"
# include <signal.h>

NNT_BEGIN_HEADER_C

# include "../../contrib/lua/lua.h"
# include "../../contrib/lua/lstate.h"
# include "../../contrib/lua/lualib.h"
# include "../../contrib/lua/lauxlib.h"

NNT_END_HEADER_C

NNT_BEGIN_C

int wluad_object_counter(lua_State* state)
{
    lua_pushinteger(state, ::wsi::Object::__global_object_counter);
    return 1;
}

int wluad_debug(lua_State* state)
{
    raise(SIGINT);
    return 1;
}

void wluaopen_dtrace(wlua_Processor* proc)
{
    lua_register(wluaL(proc), "object_counter", wluad_object_counter);
    lua_register(wluaL(proc), "debug", wluad_debug);
}

NNT_END_C

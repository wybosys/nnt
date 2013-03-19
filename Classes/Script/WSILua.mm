
# import "Core.h"
# import "NNTLua.h"

NNT_BEGIN_HEADER_C

# include "../../contrib/lua/lua.h"
# include "../../contrib/lua/lstate.h"
# include "../../contrib/lua/lualib.h"
# include "../../contrib/lua/lauxlib.h"

NNT_END_HEADER_C

NNT_BEGIN_OBJC

@interface NNTLuaPrivate : NSObject {

    wlua_Processor* lua;
    
}

@property (nonatomic, assign) NNTLua *d_owner;
@property (nonatomic, readonly) wlua_Processor *lua;

@end

@implementation NNTLuaPrivate

@synthesize d_owner;
@synthesize lua;

- (id)init {
    self = [super init];
    
    lua = wlua_Open();
    
    luaopen_base(wluaL(lua));
    luaopen_table(wluaL(lua));
    luaopen_string(wluaL(lua));
    luaopen_math(wluaL(lua));
    wluaopen_kernel(wluaL(lua));
    
    return self;
}

- (void)dealloc {
    wlua_Close(lua);

    [super dealloc];
}

@end

@implementation NNTLua

@dynamic processor;

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(NNTLua);
    return self;
}

- (void)dealloc {
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (BOOL)executeUTF8String:(const char *)expr {
    luaL_loadstring(wluaL(d_ptr.lua), expr);
    int sta = lua_pcall(wluaL(d_ptr.lua), 0, LUA_MULTRET, 0);
    return sta == 0;
}

- (wlua_Processor*)processor {
    return d_ptr.lua;
}

# pragma mark impl.

- (BOOL)executeString:(NSString *)str {
    return [self executeUTF8String:[str UTF8String]];
}

- (NSString*)errorMessage {
    return @"";
}

@end

NNT_END_OBJC
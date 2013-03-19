
# import "Core.h"
# import "WSILua.h"

WSI_BEGIN_HEADER_C

# include "../../contrib/lua/lua.h"
# include "../../contrib/lua/lstate.h"
# include "../../contrib/lua/lualib.h"
# include "../../contrib/lua/lauxlib.h"

WSI_END_HEADER_C

WSI_BEGIN_OBJC

@interface WSILuaPrivate : NSObject {

    wlua_Processor* lua;
    
}

@property (nonatomic, assign) WSILua *d_owner;
@property (nonatomic, readonly) wlua_Processor *lua;

@end

@implementation WSILuaPrivate

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

@implementation WSILua

@dynamic processor;

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(WSILua);
    return self;
}

- (void)dealloc {
    WSIDECL_PRIVATE_DEALLOC();
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

WSI_END_OBJC
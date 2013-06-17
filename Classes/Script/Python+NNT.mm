
# import "Core.h"
# import "Python+NNT.h"

NNT_BEGIN_HEADER_C

# import "../../3rd/python/Include/Python.h"

NNT_END_HEADER_C

// load module.
# import "python.site.prv/nnt.modules.h"
# import "python.site.prv/pynnt.h"

NNT_BEGIN_OBJC

NNTDECL_PRIVATE_BEGIN(NNTPython, NSObject)

NNTDECL_PRIVATE_IMPL(NNTPython)

- (id)init {
    self = [super init];
    
    Py_SetPythonHome((char*)"");
    Py_InitializeEx(0);
    Py_SetProgramName((char*)"PyNNT");
    
    // load modules.
    PyNnt_LoadModules();
    
    return self;
}

- (void)dealloc {
    
    if (Py_IsInitialized()) {
        Py_Finalize();
    }
    
    [super dealloc];
}

NNTDECL_PRIVATE_END

@implementation NNTPython

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(NNTPython);
    return self;
}

- (void)dealloc {
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (BOOL)executeUTF8String:(const char *)expr {
    int ret = PyRun_SimpleString(expr);
    return ret == 0;
}

# pragma mark impl.

- (BOOL)executeString:(NSString *)str {
    return [self executeUTF8String:[str UTF8String]];
}

- (NSString*)errorMessage {
    return PyNnt_ErrorMessage();
}

@end

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(script)

# ifdef NNT_TARGET_IOS

core::string GetPythonLibraryPath()
{
    ns::String str = ns::URL::Bundle("python.bundle");
    return core::type_cast<core::string>(str);
}

# endif

NNT_END_NS
NNT_END_CXX

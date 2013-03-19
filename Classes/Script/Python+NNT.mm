
# import "Core.h"
# import "NNTPython.h"

NNT_BEGIN_HEADER_C
# import "../../3rd/python/Include/Python.h"
NNT_END_HEADER_C

// load module.
# import "_python.site/nnt.modules.h"
# import "_python.site/pynnt.h"

NNT_BEGIN_OBJC

@interface NNTPythonPrivate : NSObject

@property (nonatomic, assign) NNTPython* d_owner;

@end

@implementation NNTPythonPrivate

@synthesize d_owner;

- (id)init {
    self = [super init];
    
    Py_SetPythonHome((char*)"");
    Py_InitializeEx(0);
    Py_SetProgramName((char*)"PyNNT");
    
    // load modules.
    PyNNT_LoadModules();
    
    return self;
}

- (void)dealloc {
    
    if (Py_IsInitialized()) {
        Py_Finalize();
    }
    
    [super dealloc];
}

@end

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
    return PyNNT_ErrorMessage();
}

@end

NNT_END_OBJC

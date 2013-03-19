
# import "Core.h"
# import "WSIPython.h"

WSI_BEGIN_HEADER_C
# import "../../3rd/python/Include/Python.h"
WSI_END_HEADER_C

// load module.
# import "_python.site/wsi.modules.h"
# import "_python.site/pywsi.h"

WSI_BEGIN_OBJC

@interface WSIPythonPrivate : NSObject

@property (nonatomic, assign) WSIPython* d_owner;

@end

@implementation WSIPythonPrivate

@synthesize d_owner;

- (id)init {
    self = [super init];
    
    Py_SetPythonHome((char*)"");
    Py_InitializeEx(0);
    Py_SetProgramName((char*)"PyWSI");
    
    // load modules.
    PyWSI_LoadModules();
    
    return self;
}

- (void)dealloc {
    
    if (Py_IsInitialized()) {
        Py_Finalize();
    }
    
    [super dealloc];
}

@end

@implementation WSIPython

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(WSIPython);
    return self;
}

- (void)dealloc {
    WSIDECL_PRIVATE_DEALLOC();
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
    return PyWSI_ErrorMessage();
}

@end

WSI_END_OBJC


# import "Core.h"
# import "Console+WSI.h"
# import "Directory+WSI.h"

WSI_BEGIN_OBJC

signal_t kSignalPrint = @"::wsi::console::print";

# define CON ((::wsi::Console*)h_console)

static WSIConsole* __gs_console = nil;

@implementation WSIConsole

- (id)init {
    self = [super init];
    
    h_console = new ::wsi::Console;
    
    return self;
}

- (void)dealloc {
    delete (::wsi::Console*) h_console;
    h_console = NULL;
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalPrint)
WSIEVENT_END

- (void)print:(NSString*)str {
    [self emit:kSignalPrint result:str];
    
    CON->print(str.UTF8String);
}

- (void)println:(NSString*)str {
    [self emit:kSignalPrint result:str];
    
    CON->println(str.UTF8String);
}

+ (WSIConsole*)shared {
    WSI_SYNCHRONIZED(self)
    
    if (__gs_console == nil) {
        __gs_console = [[self alloc] init];
    }
    
    WSI_SYNCHRONIZED_END
    
    return __gs_console;
}

@end

WSI_END_OBJC

WSI_BEGIN_CXX

Console::Console()
{
    _hout = stdout;
    _hin = stdin;
    _herr = stderr;
    
    _hdup = false;
    _nln = true;
}

Console::~Console()
{
    if (_hdup & b00000001)
    {
        fclose(_hout);
    }
    if (_hdup & b00000010)
    {
        fclose(_hin);
    }
    if (_hdup & b00000100)
    {
        fclose(_herr);
    }
}

char const* Console::prefix = "wsi";
char const* Console::suffix = "$ ";

void Console::print(const char * str) const
{
    if (str)
        fwrite(str, 1, strlen(str), _hout);
}

void Console::println(const char * str) const
{
    if (str)
        fwrite(str, 1, strlen(str), _hout);
    fwrite("\r\n", 1, 2, _hout);
    
    if (!_nln)
        _nln = true;
}

void* Console::watcher_input(void *arg)
{
    return NULL;
}

WSI_END_CXX
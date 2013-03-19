
# import <Foundation/Foundation.h>
# import <wsi/WSIFoundation.h>
# import <wsi/UITheme.h>

WSI_EXTERN void process_loop(void);
WSI_EXTERN void usage(void);
WSI_EXTERN void version(void);
WSI_EXTERN bool check_quit(::std::string const&);
WSI_EXTERN bool load_theme(::std::string const&);
WSI_EXTERN bool find_key(::std::string const&);
WSI_EXTERN bool list_all(::std::string const&);
WSI_EXTERN bool close_theme(::std::string const&);

WSI_STATIC UITheme* gs_theme = nil;

int main (int argc, const char * argv[])
{
    @autoreleasepool {        
        [WSI Init];
        process_loop();
        [WSI Fin];
    }
    return 0;
}

void process_loop() 
{
    version();
    
    ::std::string input;
    
    while (1) 
    {
        ::std::cout << "$";
        ::std::cin >> input;
        
        if (check_quit(input))
            break;
        
        if (0) { PASS; }
        
        elif (load_theme(input)) {}
        elif (find_key(input)) {}
        elif (list_all(input)) {}
        elif (close_theme(input)) {}
        
        else { usage(); }
    }
    
    // clear
    zero_release(gs_theme);
    
    ::std::cout << "Goodbye" << ::std::endl;
}

bool check_quit(::std::string const& str)
{
    return str == "q" || str == "quit";
}

void usage()
{
    ::std::cout << "usage:" << ::std::endl <<
    "[q|quit] exit this program." << ::std::endl <<
    "[load] <path of theme> load theme." << ::std::endl <<
    "[find] <key> find obj associated by key." << ::std::endl <<
    "[ls|list] list all object with key." << ::std::endl <<
    "[close] close theme." << ::std::endl
    ;
}

void version()
{
    ::std::cout << "The theme editor for wsi-uikit-theme file." << ::std::endl;
}

bool load_theme(::std::string const& input)
{
    if (input != "load") return false;
    ::std::string file;
    ::std::cin >> file;
    zero_release(gs_theme);
    // load
    gs_theme = [[UITheme alloc] init];
    if (![gs_theme loadTheme:[NSString stringWithCString:file.c_str() encoding:NSASCIIStringEncoding] type:WSIDirectoryTypeAbsolute])
    {
        zero_release(gs_theme);
    }
    return true;
}

bool find_key(::std::string const& input)
{
    if (input != "find") return false;
    ::std::string key;
    ::std::cin >> key;
    id obj = [gs_theme instanceObject:key.c_str()];
    if (obj)
    {
        ::std::cout << "found " << object_getClassName(obj) << " object" << ::std::endl;
    } 
    else 
    {
        ::std::cout << "no object" << ::std::endl;
    }
    return true;
}

WSI_EXTERN bool list_all_func(char const* key, uint klen, id obj);
bool list_all_func(char const* key, uint klen, id obj)
{
    ::std::cout << "key is: [" << key << "] object is: [" << object_getClassName(obj) << "]" << ::std::endl;
    return true;
}

bool list_all(::std::string const& input)
{
    if (input != "list" && input != "ls") return false;
    [gs_theme walk:list_all_func];
    return true;
}

bool close_theme(::std::string const& input)
{
    if (input != "close") return false;
    zero_release(gs_theme);
    return true;
}

# ifndef __WSI_BSE_APPINFO_40F3FDB0844B43B08730AA11F9FE0DD3_H_INCLUDED
# define __WSI_BSE_APPINFO_40F3FDB0844B43B08730AA11F9FE0DD3_H_INCLUDED

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WSIApplication);
WSIDECL_EXTERN_CLASS(Server);

@interface BSEAppInformation : WSIObject {
    WSIApplication* _app;
    Server* _serv;
}

@property (nonatomic, assign) WSIApplication* app;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(bse)

class Application
{
public:
    
    class Counter
    {
    public:
        
        static uint Launch();
        
    };
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif

# endif

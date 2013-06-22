
# ifndef __NNT_BSE_APPINFO_40F3FDB0844B43B08730AA11F9FE0DD3_H_INCLUDED
# define __NNT_BSE_APPINFO_40F3FDB0844B43B08730AA11F9FE0DD3_H_INCLUDED

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NNTApplication);
NNTDECL_EXTERN_CLASS(Server);

@interface BSEAppInformation : NNTObject {
    NNTApplication* _app;
    Server* _serv;
}

@property (nonatomic, assign) NNTApplication* app;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(bse)

class Application
{
public:
    
    class Counter
    {
    public:
        
        static uint Launch();
        
    };
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif

# endif

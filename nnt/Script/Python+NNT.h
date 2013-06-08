
# ifndef __NNT_SCRIPT_PYTHON_F355F4C98E2F47739353521115BA507D_H_INCLUDED
# define __NNT_SCRIPT_PYTHON_F355F4C98E2F47739353521115BA507D_H_INCLUDED

# include "Script+NNT.h"

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(NNTPython);

@interface NNTPython : NNTObject <NNTScript> {
    NNTDECL_PRIVATE(NNTPython);
}

- (BOOL)executeUTF8String:(char const*)expr;

@end

NNT_END_HEADER_OBJC

# endif

# ifdef NNT_CXX

# include "../TL/URI+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(script)

NNT_EXTERN core::string GetPythonLibraryPath();

NNTDECL_PRIVATE_HEAD_CXX(Python);

class Python
{
    NNTDECL_PRIVATE_CXX(Python);
    
public:
    
    Python();
    ~Python();

    bool run_file(core::uri const&);

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif

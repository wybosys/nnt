
# ifndef __NNT_DTRACE_LIBRARY_56F975C178A948AAB3CA8A49AB7F6CEE_H_INCLUDED
# define __NNT_DTRACE_LIBRARY_56F975C178A948AAB3CA8A49AB7F6CEE_H_INCLUDED

# include "../Script/NNTLua.h"

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_C

void wluaopen_dtrace_objc(wlua_Processor*);

NNT_END_HEADER_C

# endif

NNT_BEGIN_HEADER_C

void wluaopen_dtrace(wlua_Processor*);

NNT_END_HEADER_C

# endif

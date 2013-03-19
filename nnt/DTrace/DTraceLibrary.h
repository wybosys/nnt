
# ifndef __WSI_DTRACE_LIBRARY_56F975C178A948AAB3CA8A49AB7F6CEE_H_INCLUDED
# define __WSI_DTRACE_LIBRARY_56F975C178A948AAB3CA8A49AB7F6CEE_H_INCLUDED

# include "../Script/WSILua.h"

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_C

void wluaopen_dtrace_objc(wlua_Processor*);

WSI_END_HEADER_C

# endif

WSI_BEGIN_HEADER_C

void wluaopen_dtrace(wlua_Processor*);

WSI_END_HEADER_C

# endif

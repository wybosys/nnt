
# ifndef __WAE_A06D921FF8874C0EB110DCE621616146_H_INCLUDED
# define __WAE_A06D921FF8874C0EB110DCE621616146_H_INCLUDED

# include "WSIFoundation.h"

# define WAE_BEGIN \
WSIAPP_BEGIN \
WSI_BEGIN_NS(wae)

# define WAE_BEGIN_NS(ns) \
WAE_BEGIN \
WSI_BEGIN_NS(ns)

# define WAE_BEGIN_NS2(ns, ns2) \
WAE_BEGIN_NS(ns) \
WSI_BEGIN_NS(ns2)

# define WAE_END \
WSI_END_NS \
WSIAPP_END

# define WAE_END_NS \
WSI_END_NS \
WAE_END

# define WAE_END_NS2 \
WSI_END_NS \
WAE_END_NS

# include "Context.h"
# include "Server.h"
# include "User.h"
# include "Preferences.h"

# endif

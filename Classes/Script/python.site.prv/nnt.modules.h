
# ifndef __NNTPY_MODULES_7FE4C235069A4F8FBDA3268FD216155D_H_INCLUDED
# define __NNTPY_MODULES_7FE4C235069A4F8FBDA3268FD216155D_H_INCLUDED

NNT_BEGIN_HEADER_C

NNT_EXTERN void PyNnt_LoadModules_c(void);
NNT_EXTERN void PyNnt_LoadModules_objc(void);

# ifdef NNT_OBJC

# define PyNnt_LoadModules PyNnt_LoadModules_objc

# else

# define PyNnt_LoadModules PyNnt_LoadModules_c

# endif

NNT_END_HEADER_C

# endif

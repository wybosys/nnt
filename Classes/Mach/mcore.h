
# ifndef __NNT_MACH_CORE_3ba6734fd8bf4e0895cbd341cc2f240c_H_INCLUDED
# define __NNT_MACH_CORE_3ba6734fd8bf4e0895cbd341cc2f240c_H_INCLUDED

NNT_BEGIN_HEADER_C

// mr is Mach Register.
typedef uinteger mr_integer;

typedef struct {
    mr_integer ax, bx, cx, dx, di, si;
} mregister;

NNT_END_HEADER_C

# endif

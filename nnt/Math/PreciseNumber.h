
# ifndef __NNT_MATH_PRECISENUMBER_03CC56132D8E4D379C1AA5B7CFF88857_H_INCLUDED
# define __NNT_MATH_PRECISENUMBER_03CC56132D8E4D379C1AA5B7CFF88857_H_INCLUDED

# ifndef NNT_GMP_INNER

# import <gmp/gmp.h>

# ifdef NNT_CXX
# import <gmp/gmpxx.h>
# endif

# else

typedef struct mpf_t, mpz_t, mpq_t;

# endif

NNT_BEGIN_HEADER_OBJC

@interface NSString (Precise)

+ (NSString *)stringFromMPF:(mpf_t)num;
+ (NSString *)stringFromMPZ:(mpz_t)num;
+ (NSString *)stringFromMPQ:(mpq_t)num;

@end

NNTDECL_CATEGORY(NSString, Precise);

NNT_END_HEADER_OBJC

# endif

# ifndef __WSI_MATH_PRECISENUMBER_03CC56132D8E4D379C1AA5B7CFF88857_H_INCLUDED
# define __WSI_MATH_PRECISENUMBER_03CC56132D8E4D379C1AA5B7CFF88857_H_INCLUDED

# ifndef WSI_GMP_INNER

# import <gmp/gmp.h>

# ifdef WSI_CXX
# import <gmp/gmpxx.h>
# endif

# else

typedef struct mpf_t, mpz_t, mpq_t;

# endif

WSI_BEGIN_HEADER_OBJC

@interface NSString (Precise)

+ (NSString *)stringFromMPF:(mpf_t)num;
+ (NSString *)stringFromMPZ:(mpz_t)num;
+ (NSString *)stringFromMPQ:(mpq_t)num;

@end

WSIDECL_CATEGORY(NSString, Precise);

WSI_END_HEADER_OBJC

# endif
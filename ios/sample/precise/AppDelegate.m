
# import "Foundation+NNT.h"
# import "AppDelegate.h"
# import "PreciseNumber.h"

@implementation AppDelegate

- (void)load {
    mpz_t a;    
    mpz_init_set_str(a, "111111111111111111111111111111111111111111111111111111111111", 10);
    
    mpz_t b;
    mpz_init_set_str(b, "222222222222222222222222222222222222222222222222222222222222", 10);
    
    mpz_t c;
    mpz_mul(c, a, b);
    //mpz_add(c, a, b);
    
    //trace_msg([NSString stringFromMPZ:c]);
    [Msgbox info:[NSString stringFromMPZ:c]];
}

@end

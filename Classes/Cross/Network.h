
# ifndef __NNT_NETWORK_51608FBA71BB4E95B47DB8BAFF63D71A_H_INCLUDED
# define __NNT_NETWORK_51608FBA71BB4E95B47DB8BAFF63D71A_H_INCLUDED

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(NNTNetworkStatus);

@interface NNTNetworkStatus : NNTObject {
    
    //! available status.
    BOOL availableWWAN;
    BOOL availableEn;
    BOOL available;
    
    //! address.
    NSString *address;
    
    NNTDECL_PRIVATE(NNTNetworkStatus);
}

@property (nonatomic, readonly) BOOL availableWWAN, available, availableEn;
@property (nonatomic, readonly) NSString *address;

//! get instance.
+ (NNTNetworkStatus*)getInstance;

@end

NNT_END_HEADER_OBJC

# endif

# endif
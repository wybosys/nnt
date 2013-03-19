
# ifndef __WSI_NETWORK_51608FBA71BB4E95B47DB8BAFF63D71A_H_INCLUDED
# define __WSI_NETWORK_51608FBA71BB4E95B47DB8BAFF63D71A_H_INCLUDED

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(WSINetworkStatus);

@interface WSINetworkStatus : WSIObject {
    
    //! available status.
    BOOL availableWWAN;
    BOOL availableEn;
    BOOL available;
    
    //! address.
    NSString *address;
    
    WSIDECL_PRIVATE(WSINetworkStatus);
}

@property (nonatomic, readonly) BOOL availableWWAN, available, availableEn;
@property (nonatomic, readonly) NSString *address;

//! get instance.
+ (WSINetworkStatus*)getInstance;

@end

WSI_END_HEADER_OBJC

# endif

# endif
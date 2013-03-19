
# ifndef __WSI_OA_TOGGLE_2EEAD93743FE43EA8F9704D087C7A81C_H_INCLUDED
# define __WSI_OA_TOGGLE_2EEAD93743FE43EA8F9704D087C7A81C_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(OAManager);
WSIDECL_EXTERN_CLASS(OAToggle);

@protocol OAToggleDelegate <NSObject>

//! save data with uid.
- (void)save:(NSDictionary*)data uid:(NSString*)uid;

//! load data with uid.
- (NSDictionary*)load:(NSString*)uid;

@optional
//! delete data with uid.
- (void)del:(NSString*)uid;

//! show weibo
- (void)toggleShowWeibo:(OAToggle*)toggle;

@end

@interface OAToggle : WSIObject {
    id<OAToggleDelegate> delegate;
    
    @protected
    OAManager* _manager;
}

@property (nonatomic, assign) id<OAToggleDelegate> delegate;
@property (nonatomic, assign) BOOL showAllWeibo, showSina, showTencent, showTencentOS, showNetease, showKaixin, showRenren, showSohu, showDouban;

//! count.
- (usize)count;

//! name.
- (NSString*)name:(uindex)idx;

//! imageRes
- (UIImage*)logoImage:(uindex)idx;

//! get data.
- (NSDictionary*)load:(uindex)idx;
- (NSDictionary*)load_byclass:(Class)cls;

//! don't check delegate.
- (NSDictionary*)load_unsafe:(uindex)idx;
- (NSDictionary*)load_byclass_unsafe:(Class)cls;

//! save data.
- (void)save:(NSDictionary*)data idx:(uindex)idx;

//! delete data.
- (void)del:(uindex)idx;

//! authorize.
- (void)authorize:(uindex)idx;

//! is enable.
- (BOOL)is_enable:(uindex)idx;
- (BOOL)is_enable_byclass:(Class)cls;

@end

WSI_END_HEADER_OBJC

# endif
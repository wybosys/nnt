
# ifndef __WSI_PAY_UNIPAY_642BD99A319A459FAA967116FE8D91BC_H_INCLUDED
# define __WSI_PAY_UNIPAY_642BD99A319A459FAA967116FE8D91BC_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface ByPayApiView : WSIUIView

@property (nonatomic, assign) UIView* pay;

@end

@interface ByPayApiController : WSIUIViewController

@property (nonatomic, copy) NSString *application, *merchantId, *merchantOrderId, *merchantOrderTime, *signResult;
@property (nonatomic, retain) NSData *result;
@property (nonatomic, retain) id Owner;

- (NSString*)generateSign;
- (NSData*)generateResult;
- (void)processResult:(NSData*)data;

@end

WSI_EXTERN signal_t kSignalByPayClose;

WSI_END_HEADER_OBJC

# endif

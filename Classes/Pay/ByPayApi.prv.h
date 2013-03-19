
# ifndef __NNT_PAY_UNIPAY_642BD99A319A459FAA967116FE8D91BC_H_INCLUDED
# define __NNT_PAY_UNIPAY_642BD99A319A459FAA967116FE8D91BC_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface ByPayApiView : NNTUIView

@property (nonatomic, assign) UIView* pay;

@end

@interface ByPayApiController : NNTUIViewController

@property (nonatomic, copy) NSString *application, *merchantId, *merchantOrderId, *merchantOrderTime, *signResult;
@property (nonatomic, retain) NSData *result;
@property (nonatomic, retain) id Owner;

- (NSString*)generateSign;
- (NSData*)generateResult;
- (void)processResult:(NSData*)data;

@end

NNT_EXTERN signal_t kSignalByPayClose;

NNT_END_HEADER_OBJC

# endif

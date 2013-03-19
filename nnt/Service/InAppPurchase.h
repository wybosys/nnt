
# ifndef __NNT_SERVICE_INAPPPURCHASE_7FE2B536037546DAA010775549AC1392_H_INCLUDED
# define __NNT_SERVICE_INAPPPURCHASE_7FE2B536037546DAA010775549AC1392_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(SKProduct);
NNTDECL_EXTERN_CLASS(SKPayment);

@interface InAppPurchaseItem : NNTObject {
    
    SKProduct* _product;
    SKPayment* _payment;
    
}

@property (nonatomic, retain) SKProduct* product;
@property (nonatomic, retain) SKPayment* payment;

- (BOOL)downloadable;
- (NSArray*)downloadContentLengths;
- (NSString*)downloadContentVersion;

@end

NNT_EXTERN signal_t kSignalPaying;
NNT_EXTERN signal_t kSignalPayFailed;
NNT_EXTERN signal_t kSignalPaySuccess;
NNT_EXTERN signal_t kSignalPayRestore;

NNTDECL_PRIVATE_HEAD(InAppPurchaseItems);

@interface InAppPurchaseItems : NNTObject {
    
    NSSet* _identifiers;
    NSArray* _products;
    
    NNTDECL_PRIVATE(InAppPurchaseItems);
}

@property (nonatomic, retain) NSSet* identifiers;
@property (nonatomic, retain) NSArray* products;

- (void)update;
- (void)fetch;

@end

NNTDECL_EXTERN_CLASS(SKPaymentQueue);

NNTDECL_PRIVATE_HEAD(InAppPurchaseService);

@interface InAppPurchaseService : NNTObject {
    SKPaymentQueue* _queue;
    
    NNTDECL_PRIVATE(InAppPurchaseService);
}

+ (BOOL)Payable;
+ (InAppPurchaseService*)shared;

- (void)addItem:(InAppPurchaseItem*)item;

@end

NNT_EXTERN signal_t kSignalFailed;
NNT_EXTERN signal_t kSignalSuccess;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(purchase)
NNT_BEGIN_NS(inapp)

class Item
: public ns::Object<InAppPurchaseItem>
{
    typedef ns::Object<InAppPurchaseItem> super;
    
public:
    
    Item();
    Item(id);
    ~Item();
    
    ns::String description() const;
    ns::String title() const;
    ns::String identifier() const;
    bool is_downloadable() const;
    ns::Array content_lengths() const;
    ns::String content_version() const;
    ns::Locale locale() const;
    ns::Decimal price() const;
    
};

class Items
: public ns::Object<InAppPurchaseItems>
{
public:
    
    Items();
    Items(ns::Set const&);
    Items(ns::String const&);
    ~Items();
    
    void update();
    void fetch();
    
    void set_identifier(ns::Set const&);
    void set_identifier(ns::String const&);
    
    uint count() const;
    Item at(uint) const;

};

class Service
: public ns::Object<InAppPurchaseService>
{
    typedef ns::Object<InAppPurchaseService> super;
    
protected:
    
    Service(id);
    
public:
    
    Service();
    ~Service();
    
    static Service& getInstance();
    static bool Payable();
    
    void add(Item&);
    
};

NNT_END_NS
NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif

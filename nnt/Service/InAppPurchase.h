
# ifndef __WSI_SERVICE_INAPPPURCHASE_7FE2B536037546DAA010775549AC1392_H_INCLUDED
# define __WSI_SERVICE_INAPPPURCHASE_7FE2B536037546DAA010775549AC1392_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(SKProduct);
WSIDECL_EXTERN_CLASS(SKPayment);

@interface InAppPurchaseItem : WSIObject {
    
    SKProduct* _product;
    SKPayment* _payment;
    
}

@property (nonatomic, retain) SKProduct* product;
@property (nonatomic, retain) SKPayment* payment;

- (BOOL)downloadable;
- (NSArray*)downloadContentLengths;
- (NSString*)downloadContentVersion;

@end

WSI_EXTERN signal_t kSignalPaying;
WSI_EXTERN signal_t kSignalPayFailed;
WSI_EXTERN signal_t kSignalPaySuccess;
WSI_EXTERN signal_t kSignalPayRestore;

WSIDECL_PRIVATE_HEAD(InAppPurchaseItems);

@interface InAppPurchaseItems : WSIObject {
    
    NSSet* _identifiers;
    NSArray* _products;
    
    WSIDECL_PRIVATE(InAppPurchaseItems);
}

@property (nonatomic, retain) NSSet* identifiers;
@property (nonatomic, retain) NSArray* products;

- (void)update;
- (void)fetch;

@end

WSIDECL_EXTERN_CLASS(SKPaymentQueue);

WSIDECL_PRIVATE_HEAD(InAppPurchaseService);

@interface InAppPurchaseService : WSIObject {
    SKPaymentQueue* _queue;
    
    WSIDECL_PRIVATE(InAppPurchaseService);
}

+ (BOOL)Payable;
+ (InAppPurchaseService*)shared;

- (void)addItem:(InAppPurchaseItem*)item;

@end

WSI_EXTERN signal_t kSignalFailed;
WSI_EXTERN signal_t kSignalSuccess;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(purchase)
WSI_BEGIN_NS(inapp)

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

WSI_END_NS
WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif


# ifndef __WSI_UIKIT_selfECT_7A7189911D1847BD9A8BB8EA634B694C_H_INCLUDED
# define __WSI_UIKIT_selfECT_7A7189911D1847BD9A8BB8EA634B694C_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

typedef enum
{
    WordWrapping,
    CharWrapping,
    Clipping,
    TruncatingHead,
    TruncatingTail,
    TruncatingMiddle,
}
WSILineBreadMode;

typedef enum
{
    Left,
    Center,
    Right
}
WSIAlignment;

# if WSI_IOS_MIN >= __IPHONE_6_0

//#   define TextAlignment(op) NSTextAlignment##op

static UILineBreakMode LineBreak(WSILineBreadMode mode)
{
    UILineBreakMode ret;
    switch (mode)
    {
        default:
        case WordWrapping: ret = NSLineBreakByWordWrapping; break;
        case CharWrapping: ret = NSLineBreakByCharWrapping; break;
        case Clipping: ret = NSLineBreakByClipping; break;
        case TruncatingHead: ret = NSLineBreakByTruncatingHead; break;
        case TruncatingTail: ret = NSLineBreakByTruncatingTail; break;
        case TruncatingMiddle: ret = NSLineBreakByTruncatingTail; break;
    }
    return ret;
}

# else

//#   define TextAlignment(op) UITextAlignment##op

static UILineBreakMode LineBreak(WSILineBreadMode mode)
{
    uint ret;
    switch (mode)
    {
        default:
        case WordWrapping: ret = UILineBreakModeWordWrap; break;
        case CharWrapping: ret = UILineBreakModeCharacterWrap; break;
        case Clipping: ret = UILineBreakModeClip; break;
        case TruncatingHead: ret = UILineBreakModeHeadTruncation; break;
        case TruncatingTail: ret = UILineBreakModeTailTruncation; break;
        case TruncatingMiddle: ret = UILineBreakModeMiddleTruncation; break;
    }
    return (UILineBreakMode)ret;
}

# endif

@interface WSIUIObject : WSIObject {
    
    //! event of global is processing.
    BOOL isGlobalEventProcessing;
    
    @private
    int __is_global_event_processing;
}

@property (nonatomic, readonly) BOOL isGlobalEventProcessing;

+ (WSIUIObject*)shared;

@end

@interface WSIUIObject (event)

- (void)emit_begin;
- (void)emit_end;

@end

# ifdef WSI_CXX

WSI_EXTERN bool WSI_DEVICE_ISIPHONE;
WSI_EXTERN bool WSI_DEVICE_ISIPHONE_SIMULATOR;
WSI_EXTERN bool WSI_DEVICE_ISIPAD;
WSI_EXTERN bool WSI_DEVICE_ISIPAD_SIMULATOR;
WSI_EXTERN bool WSI_DEVICE_ISIPOD;

WSI_BEGIN_HEADER_CXX

template <typename valT>
class _device
{
public:
    
    _device(valT const& _phone, valT const& _pad)
    : val_phone(_phone), val_pad(_pad)
    {
        PASS;
    }
    
    _device(_device const& r)
    : val_phone(r.val_phone), val_pad(r.val_pad)
    {
        PASS;
    }
    
    operator valT const& () const
    {
        if (WSI_DEVICE_ISIPAD)
            return val_pad;
        return val_phone;
    }
    
    valT const& value() const
    {
        if (WSI_DEVICE_ISIPAD)
            return val_pad;
        return val_phone;
    }
    
    valT const* operator -> () const
    {
        if (WSI_DEVICE_ISIPAD)
            return &val_pad;
        return &val_phone;
    }
    
    valT const& val_pad, & val_phone;
};

template <typename valT>
static _device<valT> device(valT const& phone, valT const& pad)
{
    return _device<valT>(phone, pad);
}

WSI_BEGIN_NS(ui)

template <WSIAlignment Type>
class TextAlignment
{
public:
    
    TextAlignment()
    {
# if WSI_IOS_MIN >= __IPHONE_6_0
        switch (Type)
        {
            case Left: align = NSTextAlignmentLeft; break;
            case Center: align = NSTextAlignmentCenter; break;
            case Right: align = NSTextAlignmentRight; break;
        }
# else
        switch (Type)
        {
            case Left: align = UITextAlignmentLeft; break;
            case Center: align = UITextAlignmentCenter; break;
            case Right: align = UITextAlignmentRight; break;
        }
# endif        
    }
    
    template <typename valT>
    operator valT () const
    {
        return (valT)align;
    }
    
    uint align;
    
};

const TextAlignment<Left> TextAlignmentLeft;
const TextAlignment<Right> TextAlignmentRight;
const TextAlignment<Center> TextAlignmentCenter;

template <typename implT, typename objT>
class Object
: public ::wsi::ns::Object<objT, RefObject>
{
    typedef ::wsi::ns::Object<objT, RefObject> super, object_type;
    typedef Object<implT, objT> self_type;
    
protected:
    
    typedef implT _class;
    
public:
    
    typedef typename object_type::owner_function_type owner_function_type;
    
    Object()
    : super(nil)
    {
        PASS;
    }
    
    Object(objT* obj)
    : super(obj)
    {
        PASS;
    }
    
    Object(self_type const& r)
    : super(r)
    {
        PASS;
    }
    
    virtual ~Object()
    {
        PASS;
    }    
    
    static implT* New()
    {
        return new implT;
    }
    
    void drop()
    {
        super::_release();
    }
    
    void destroy()
    {
        delete (implT*)this;
    }
        
    implT* impl()
    {
        return (implT*)this;
    }
    
    implT const* impl() const
    {
        return (implT const*)this;
    }
    
    bool is_firstresponder() const
    {
        return [this->_self isFirstResponder];
    }
    
    bool set_firstresponder(bool val)
    {
        if (val)
            return [this->_self becomeFirstResponder];
        return [this->_self resignFirstResponder];
    }
    
    void focus()
    {
        [this->_self becomeFirstResponder];
    }
    
    void unfocus()
    {
        [this->_self resignFirstResponder];
    }
            
};

class IObject
{
public:
    
    virtual ~IObject() {}
    
    //! get cxx object.
    virtual void* cxxobject() const = 0;
    
    //! get objc object.
    virtual id nsobject() const = 0;
    
    //! destroy.
    virtual void destroy() = 0;
    virtual void drop() = 0;
    
};

typedef struct {} empty_view_type;
typedef struct {} empty_controller_type;
 
template <typename objT>
class auto_release
{
    typedef auto_release<objT> self_type;
    
protected:
    
    auto_release(objT* obj)
    : _obj(obj)
    {
        PASS;
    }
    
    auto_release(self_type const&);
    
public:
    
    auto_release()
    : _obj(NULL)
    {
        PASS;
    }
    
    ~auto_release()
    {
        if (_obj)
        {
            _obj->drop();
        }
    }
    
    typedef objT object_type;
    typedef empty_view_type view_type;
    typedef empty_controller_type controller_type;
    
    static self_type instance()
    {
        return self_type(new objT);
    }
    
    static self_type instance(objT* r)
    {
        return self_type(r);
    }
    
    operator objT* () const
    {
        return (objT*)_obj;
    }    
    
    operator objT& () const
    {
        return *(objT*)_obj;
    }
    
    objT* operator -> () const
    {
        return (objT*)_obj;
    }
    
    objT& operator () () const
    {
        return *(objT*)_obj;
    }
    
    objT& obj() const
    {
        return *(objT*)_obj;
    }
    
    objT& operator * () const
    {
        return *(objT*)_obj;   
    }
    
    template <typename valT>
    operator valT* () const
    {
        return (valT*)(*_obj);
    }
    
protected:
    
    objT* _obj;
    
};

template <typename uiT>
class Instance
: public auto_release<uiT>
{
    typedef auto_release<uiT> super;
    
public:
    
    Instance()
    {
        this->_obj = new uiT;
    }
    
};

# define interface_cast(obj, type) \
(dynamic_cast<type*>((::wsi::RefObject*)obj))

WSIDECL_BOOLOBJECT(animate, nonanimate);
WSIDECL_BOOLOBJECT(show, hide);
WSIDECL_BOOLOBJECT(on, off);
WSIDECL_BOOLOBJECT(active, inactive);
WSIDECL_BOOLOBJECT(left, hold);

WSI_END_NS
WSI_END_HEADER_CXX

@interface cxxnsobject : NSObject {
    id target;
}

@property (nonatomic, assign) id target;

@end

# endif

WSI_EXTERN signal_t kSignalTouchesBegin;
WSI_EXTERN signal_t kSignalTouchesEnd;
WSI_EXTERN signal_t kSignalTouchesMoved;
WSI_EXTERN signal_t kSignalTouchesOffset;
WSI_EXTERN signal_t kSignalTouchesCancel;
WSI_EXTERN signal_t kSignalOrientationChanged;
WSI_EXTERN signal_t kSignalThemeChanged;
WSI_EXTERN signal_t kSignalDeviceShaked;

WSI_END_HEADER_OBJC

# endif
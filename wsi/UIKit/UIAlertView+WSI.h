
# ifndef __WSI_UIKIT_UIALERTVIEW_97D8DBD2DA0642C998F5797CECA9B92D_H_INCLUDED
# define __WSI_UIKIT_UIALERTVIEW_97D8DBD2DA0642C998F5797CECA9B92D_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface WSIUIAlertView : UIAlertView <UIAlertViewDelegate> {
    WSIOBJECT_DECL;
    
    //! lock for sync mode.
    //NSLock* showlock;
    
    //! last signal.
    signal_t lastSignal;
    
@protected
    uint _index;
}

WSIOBJECT_PROP;

//@property (nonatomic, readonly) NSLock* showlock;
@property (nonatomic, readonly) signal_t lastSignal;

- (id)initWithTitle:(NSString*)title message:(NSString*)message;
- (id)initWithTitle:(NSString*)title lineCount:(NSUInteger)lineCount;

- (id)initWithTitle:(NSString*)title message:(NSString*)message cancelButtonTitle:(NSString*)cancelButtonTitle okButtonTitle:(NSString*)okButtonTitle;
- (id)initWithTitle:(NSString *)title lineCount:(NSUInteger)lineCount cancelButtonTitle:(NSString*)cancelButtonTitle okButtonTitle:(NSString*)okButtonTitle;

- (id)initWithTitle:(NSString*)title message:(NSString*)message okButtonTitle:(NSString*)okButtonTitle;
- (id)initWithTitle:(NSString*)title lineCount:(NSUInteger)lineCount okButtonTitle:(NSString*)okButtonTitle;

//! set self to delegate.
- (id)selfDelegate;

//! one line-rect into alert.
+ (CGRect)lineRect;
+ (CGRect)rectOfLine:(NSUInteger)idx;

//! append control.
- (void)appendSubview:(UIView*)view;

@end

WSI_EXTERN signal_t kSignalIndex0;
WSI_EXTERN signal_t kSignalIndex1;
WSI_EXTERN signal_t kSignalIndex2;
WSI_EXTERN signal_t kSignalIndex3;
WSI_EXTERN signal_t kSignalIndex4;
WSI_EXTERN signal_t kSignalIndex5;
WSI_EXTERN signal_t kSignalIndex6;
WSI_EXTERN signal_t kSignalIndex7;
WSI_EXTERN signal_t kSignalIndex8;
WSI_EXTERN signal_t kSignalIndex9;
WSI_EXTERN signal_t kSignalIndexYes;
WSI_EXTERN signal_t kSignalIndexNo;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class AlertView
: public Object< AlertView, WSIUIAlertView >
{
    typedef ns::Object< WSIUIAlertView > super;
    
public:
    
    AlertView(ns::String const& title, ns::String const& msg)
    {
        this->_self = [[objc_type alloc] initWithTitle:title message:msg];
    }
    
    AlertView(ns::String const& title, uint linecount)
    {
        this->_self = [[objc_type alloc] initWithTitle:title lineCount:linecount];
    }
    
    AlertView(ns::String const& title, ns::String const& msg, ns::String const& ok)
    {
        this->_self = [[objc_type alloc] initWithTitle:title message:msg okButtonTitle:ok];
    }
    
    AlertView(ns::String const& title, uint linecount, ns::String const& ok)
    {
        this->_self = [[objc_type alloc] initWithTitle:title lineCount:linecount okButtonTitle:ok];
    }
    
    AlertView(ns::String const& title, ns::String const& msg, ns::String const& ok, ns::String const& cancel)
    {
        this->_self = [[objc_type alloc] initWithTitle:title message:msg cancelButtonTitle:cancel okButtonTitle:ok];
    }
    
    AlertView(ns::String const& title, uint linecount, ns::String const& ok, ns::String const& cancel)
    {
        this->_self = [[objc_type alloc] initWithTitle:title lineCount:linecount cancelButtonTitle:cancel okButtonTitle:ok];
    }
    
    void show(bool background = false);
    
    static CGRect bounds_ofline(uint idx)
    {
        return [WSIUIAlertView rectOfLine:idx];
    }
    
    template <typename viewT>
    void add_sub(viewT const& view)
    {
        wtl::const_pointer<viewT> ptr(view);
        [this->_self appendSubview:*ptr];
    }
    
    /*
    void lock()
    {
        [this->_self.showlock lock];
    }
    
    void unlock()
    {
        [this->_self.showlock unlock];
    }
     */
    
    signal_t last_signal() const
    {
        return this->_self.lastSignal;
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
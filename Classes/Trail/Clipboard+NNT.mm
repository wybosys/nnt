
# import "Core.h"
# import "Clipboard+NNT.h"
# import <UIKit/UIKit.h>

NNT_BEGIN_OBJC

signal_t kSignalContentChanged = @"::nnt::content::changed";

NNTDECL_PRIVATE_BEGIN(Clipboard, NNTObject)
{
    UIPasteboard* _pb;
}

@property (nonatomic, retain) UIPasteboard* pb;

NNTDECL_PRIVATE_IMPL(Clipboard)

@synthesize pb = _pb;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    safe_release(_pb);
    [super dealloc];
}

- (void)setPb:(UIPasteboard *)pb {
    if (_pb) {
        [[NSNotificationCenter defaultCenter] removeObserver:self];
        safe_release(_pb);
    }
    
    _pb = [pb retain];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(noti_changed:)
                                                 name:UIPasteboardChangedNotification
                                               object:_pb];
}

- (void)noti_changed:(NSNotification*)noti {
    UIPasteboard* paste = (UIPasteboard*)noti.object;
    if (paste != _pb)
        return;
    
    [d_owner emit:kSignalContentChanged];
}

NNTDECL_PRIVATE_END

@implementation Clipboard

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(Clipboard);
    
    d_ptr.pb = [UIPasteboard generalPasteboard];
    
    return self;
}

- (id)initWithUnique {
    self = [super init];
    NNTDECL_PRIVATE_INIT(Clipboard);
    
    d_ptr.pb = [UIPasteboard pasteboardWithUniqueName];
    
    return self;
}

- (id)initWithName:(NSString *)name {
    self = [super init];
    NNTDECL_PRIVATE_INIT(Clipboard);

    d_ptr.pb = [UIPasteboard pasteboardWithName:name create:YES];
    
    return self;
}

- (void)dealloc {
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalContentChanged)
NNTEVENT_END

- (UIPasteboard*)pasteboard {
    return d_ptr.pb;
}

@end

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(sys)

Clipboard::Clipboard()
{
    
}

Clipboard::Clipboard(ns::String const& name)
: super(nil)
{
    if (name.is_empty())
        this->_self = [[objc_type alloc] initWithUnique];
    else
        this->_self = [[objc_type alloc] initWithName:name];
}

bool Clipboard::is_string() const
{
    return [this->_self.pasteboard containsPasteboardTypes:UIPasteboardTypeListString];
}

bool Clipboard::is_url() const
{
    return [this->_self.pasteboard containsPasteboardTypes:UIPasteboardTypeListURL];
}

bool Clipboard::is_image() const
{
    return [this->_self.pasteboard containsPasteboardTypes:UIPasteboardTypeListImage];
}

bool Clipboard::is_color() const
{
    return [this->_self.pasteboard containsPasteboardTypes:UIPasteboardTypeListColor];
}

Clipboard::operator ns::String() const
{
    return to_string();
}

ns::String Clipboard::to_string() const
{
    return this->_self.pasteboard.string;
}

Clipboard::operator ns::URL() const
{
    return to_url();
}

ns::URL Clipboard::to_url() const
{
    return this->_self.pasteboard.URL;
}

Clipboard::operator ui::Image() const
{
    return to_image();
}

ui::Image Clipboard::to_image() const
{
    return this->_self.pasteboard.image;
}

Clipboard::operator ui::Color() const
{
    return to_color();
}

ui::Color Clipboard::to_color() const
{
    return this->_self.pasteboard.color;
}

void Clipboard::clear()
{
    this->_self.pasteboard.items = nil;
}

uint Clipboard::count() const
{
    return this->_self.pasteboard.items.count;
}

NNT_END_NS
NNT_END_CXX

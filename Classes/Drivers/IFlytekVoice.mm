
# include "Core.h"
# include "IFlytekVoice.h"
# include <iflytek/IFlyRecognizeControl.h>
# include <iflytek/IFlySynthesizerControl.h>
# include <iflytek/SpeechUser.h>
# include <iflytek/UpLoadController.h>
# include "App.h"

WSI_USINGCXXNAMESPACE;

WSI_BEGIN_OBJC

# define DEFAULT_APPID @"51209fc4"
//# define DEFAULT_ENGINEURL @"http://dev.voicecloud.cn:1028/index.htm"
# define DEFAULT_ENGINEURL @"http://dev.voicecloud.cn/index.htm";

WSIDECL_PRIVATE_BEGIN(IFlytekVoiceRecognizer, WSIObject)
<IFlyRecognizeControlDelegate>
{
    IFlyRecognizeControl* _ifly;
    WSIUIDesktop* _desk;
}

@property (nonatomic, readonly) IFlyRecognizeControl* ifly;
@property (nonatomic, assign) WSIUIDesktop* desk;

WSIDECL_PRIVATE_IMPL(IFlytekVoiceRecognizer)

@synthesize ifly = _ifly;
@synthesize desk = _desk;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    safe_release(_ifly);
    [super dealloc];
}

- (IFlyRecognizeControl*)ifly {
    if (_ifly == nil) {
        ns::String param = ns::String::Format(@"server_url=%@,appid=%@", d_owner.engineurl, d_owner.appid);
        _ifly = [[IFlyRecognizeControl alloc] initWithOrigin:CGPointZero initParam:param];
        [self _setup];
    }
    
    return _ifly;
}

- (void)_setup {
    _ifly.delegate = self;
    [_ifly setEngine:@"sms" engineParam:nil grammarID:nil];
    [_ifly setSampleRate:16000];
    [_ifly setShowLog:NO];
}

# pragma mark delegate

- (void)onResult:(IFlyRecognizeControl *)iFlyRecognizeControl theResult:(NSArray *)resultArray {
    trace_obj(resultArray);
    
    // find max score.
    NSString* value;
    {
        int max = 0;
        for (NSDictionary* each in resultArray) {
            NSString* name = [each valueForKey:@"NAME"];
            NSNumber* score = [each valueForKey:@"SCORE"];
            if (score.intValue > max) {
                max = score.intValue;
                value = name;
            }
        }
    }
    
    // emit.
    [d_owner emit:kSignalVoiceRecognizeSuccess result:value];
}

- (void)onRecognizeEnd:(IFlyRecognizeControl *)iFlyRecognizeControl theError:(SpeechError) error {
    [_desk close];
    [d_owner release];
}

WSIDECL_PRIVATE_END

@interface IFlytekDesktop : WSIUIDesktop {
    UIView* _ifly;
}

@property (nonatomic, assign) UIView* ifly;

@end

@implementation IFlytekDesktop

@synthesize ifly = _ifly;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (void)setIfly:(UIView *)ifly {
    [_ifly removeFromSuperview];
    _ifly = ifly;
    [self addSubview:_ifly];
}

- (void)layoutSubviews {
    [_ifly moveToCenter:cg::Rect(self.bounds).center()];
}

@end

@implementation IFlytekVoiceRecognizer

@synthesize appid = _appid, engineurl = _engineurl;

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(IFlytekVoiceRecognizer);
    
    self.appid = DEFAULT_APPID;
    self.engineurl = DEFAULT_ENGINEURL;
    
    return self;
}

- (void)dealloc {
    safe_release(_appid);
    safe_release(_engineurl);
    
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalVoiceRecognizeSuccess)
WSIEVENT_END

- (void)execute {
    [self retain];
    
    IFlytekDesktop* desk = [[IFlytekDesktop alloc] init];
    desk.ifly = d_ptr.ifly;
    d_ptr.desk = desk;
    [desk connect:kSignalShown sel:@selector(act_shown) obj:self];
    [desk show];
    safe_release(desk);
}

- (void)act_shown {
    if (![d_ptr.ifly start]) {
        [d_ptr.desk close];
        [Msgbox fatal:_W(@"failed to start voice recognizer!")];
        [self release];
    }
}

@end

# pragma mark speech

WSIDECL_PRIVATE_BEGIN(IFlytekSpeech, WSIObject)
<IFlySynthesizerControlDelegate>
{
    IFlySynthesizerControl* _ifly;
}

@property (nonatomic, readonly) IFlySynthesizerControl* ifly;

WSIDECL_PRIVATE_IMPL(IFlytekSpeech)

@synthesize ifly = _ifly;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    [_ifly removeFromSuperview];
    safe_release(_ifly);
    [super dealloc];
}

- (IFlySynthesizerControl*)ifly {
    if (_ifly == NULL) {
        ns::String param = ns::String::Format(@"server_url=%@,appid=%@", d_owner.engineurl, d_owner.appid);
        _ifly = [[IFlySynthesizerControl alloc] initWithOrigin:CGPointZero initParam:param];
        [self _setup];
    }
    
    return _ifly;
}

- (void)_setup {
    _ifly.delegate = self;
    [_ifly setVoiceName:@"xiaoyan"];
    [_ifly setShowUI:NO];
    [_ifly setShowLog:NO];
    
    // add to root view.
    [[WSIApplication shared].currentWindow addSubview:_ifly];
}

# pragma mark delegate

- (void)onSynthesizerEnd:(IFlySynthesizerControl *)iFlySynthesizerControl theError:(SpeechError) error {
    [d_owner emit:kSignalSpeechCompletion];
    [d_owner release];
}

- (void)onSynthesizerBufferProgress:(float)bufferProgress {
    PASS;
}

- (void)onSynthesizerPlayProgress:(float)playProgress {
    PASS;
}

WSIDECL_PRIVATE_END

@implementation IFlytekSpeech

@synthesize appid = _appid, engineurl = _engineurl, text = _text;

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(IFlytekSpeech);
    
    self.appid = DEFAULT_APPID;
    self.engineurl = DEFAULT_ENGINEURL;
    
    return self;
}

- (void)dealloc {
    safe_release(_appid);
    safe_release(_engineurl);
    safe_release(_text);
    
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalSpeechCompletion)
WSIEVENT_END

- (void)speak {
    [self retain];
    
    [d_ptr.ifly setText:_text params:nil];
    if (![d_ptr.ifly start]) {
        [Msgbox fatal:_W(@"failed to start voice recognizer!")];
        [self release];
    }
}

@end

WSI_END_OBJC

WSI_BEGIN_CXX
WSI_BEGIN_NS(iflytek)

VoiceRecognizer::VoiceRecognizer()
{
    
}

VoiceRecognizer::~VoiceRecognizer()
{
    
}

void VoiceRecognizer::set_appid(ns::String const& str)
{
    this->_self.appid = str;
}

void VoiceRecognizer::set_engineurl(ns::String const& str)
{
    this->_self.engineurl = str;
}

void VoiceRecognizer::execute()
{
    [this->_self execute];
}

Speech::Speech()
{
    
}

Speech::~Speech()
{
    
}

void Speech::set_appid(ns::String const& str)
{
    this->_self.appid = str;
}

void Speech::set_engineurl(ns::String const& str)
{
    this->_self.engineurl = str;
}

void Speech::set_text(ns::String const& str)
{
    this->_self.text = str;
}

void Speech::speak()
{
    [this->_self speak];
}

WSI_END_NS
WSI_END_CXX

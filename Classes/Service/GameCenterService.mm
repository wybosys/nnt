
# import "Core.h"
# import "GameCenterService.h"

NNT_USINGCXXNAMESPACE;

NNT_BEGIN_OBJC

NNT_EXTERN double DEVICE_VERSION;

@interface GameCenterAchievement ()

@property (nonatomic, retain) GKAchievement* object;

@end

NNTDECL_PRIVATE_BEGIN(GameCenterService, NNTObject) {
    GKLocalPlayer* _player;
}

@property (nonatomic, readonly) GKLocalPlayer* player;

+ (BOOL)isAvaliable;

NNTDECL_PRIVATE_IMPL(GameCenterService)

@synthesize player = _player;

- (id)init {
    self = [super init];
    
    if ([GameCenterServicePrivate isAvaliable]) {
        _player = [[GKLocalPlayer localPlayer] retain];
    }
    
    return self;
}

- (void)dealloc {
    safe_release(_player);
    [super dealloc];
}

+ (BOOL)isAvaliable {
    // from xcode's sample project.
    
    // Check for presence of GKLocalPlayer API.
    Class gcClass = (NSClassFromString(@"GKLocalPlayer"));
    
    // The device must be running running iOS 4.1 or later.
    NSString *reqSysVer = @"4.1";
    NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
    BOOL osVersionSupported = ([currSysVer compare:reqSysVer options:NSNumericSearch] != NSOrderedAscending);
    
    return (gcClass && osVersionSupported);
}

NNTDECL_PRIVATE_END

@interface GameCenterService ()

@property (nonatomic, copy) NSString* playerId, /**playerName,*/ *playerNickname;

@end

@implementation GameCenterService

@synthesize playerId = _playerId, /*playerName = _playerName,*/ playerNickname = _playerNickname;

+ (id)shared {
    static GameCenterService* serv = nil;
    NNT_SYNCHRONIZED(self)
    if (serv == nil)
        serv = [[[self class] alloc] init];
    NNT_SYNCHRONIZED_END
    return serv;
}

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(GameCenterService);
    
    // auth.
    if (![self authenticated])
        [self authorize];
    
    return self;
}

- (void)dealloc {
    safe_release(_playerId);
    //safe_release(_playerName);
    safe_release(_playerNickname);
    
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalUserLogin)
NNTEVENT_END

- (BOOL)authenticated {
    return d_ptr.player.authenticated;
}

- (void)authorize {
    [d_ptr.player authenticateWithCompletionHandler:^(NSError *error) {
        if (d_ptr.player.authenticated) {
            if (!_playerId ||
                ![_playerId isEqualToString:d_ptr.player.playerID]) {
                
                // get player info.
                self.playerId = d_ptr.player.playerID;
                //self.playerName = d_ptr.player.displayName;
                self.playerNickname = d_ptr.player.alias;
                                
                [self emit:kSignalUserLogin];
            }
        }
    }];
}

@end

@implementation GameCenterAchievements

@synthesize records = _records;

- (id)init {
    self = [super init];
    
    // fetch records from server.
    [self update];
    
    return self;
}

- (void)dealloc {
    safe_release(_records);
    
    [super dealloc];
}

- (void)update {
    [GKAchievement loadAchievementsWithCompletionHandler:^(NSArray *achievements, NSError *error) {
        if (error) {
            trace_msg(@"failed load achievements from gamecenter.");
        } else {
            NSMutableDictionary* dict = [NSMutableDictionary dictionaryWithCapacity:achievements.count];
            for (GKAchievement* each in achievements) {
                GameCenterAchievement* obj = [[GameCenterAchievement alloc] init];
                obj.object = each;
                [dict setObject:obj forKey:each.identifier];
                safe_release(obj);
            }
            
            self.records = dict;
        }
        
        [self unblock];
    }];
    
    [self block];
}

+ (GameCenterAchievements*)shared {
    static GameCenterAchievements* ret = nil;
    NNT_SYNCHRONIZED(self)
    if (ret == nil) {
        ret = [[[self class] alloc] init];
    }
    NNT_SYNCHRONIZED_END
    return ret;
}

- (GameCenterAchievement*)find:(NSString*)identifier {
    return [_records objectForKey:identifier null:nil];
}

@end

@implementation GameCenterAchievement

@synthesize identifier = _identifier;
@dynamic percentComplete, showsCompletionBanner;
@synthesize object = _achievement;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    safe_release(_achievement);
    safe_release(_identifier);
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalSuccess)
NNTEVENT_END

- (GKAchievement*)achievement {
    if (_achievement == nil) {
        GameCenterAchievement* record = [[GameCenterAchievements shared] find:_identifier];
        if (record)
            _achievement = [record.object retain];
        if (_achievement == nil)
            _achievement = [[GKAchievement alloc] initWithIdentifier:_identifier];
        if (DEVICE_VERSION >= 5.0)
            _achievement.showsCompletionBanner = YES;
    }
    return _achievement;
}

- (double)percentComplete {
    return self.achievement.percentComplete;
}

- (void)setPercentComplete:(double)percentComplete {
    self.achievement.percentComplete = percentComplete;
}

- (BOOL)showsCompletionBanner {
    if (DEVICE_VERSION < 5.0)
        return NO;
    return self.achievement.showsCompletionBanner;
}

- (void)setShowsCompletionBanner:(BOOL)showsCompletionBanner {
    if (DEVICE_VERSION >= 5.0)
        self.achievement.showsCompletionBanner = showsCompletionBanner;
}

- (void)submit {
    [self.achievement reportAchievementWithCompletionHandler:^(NSError *error) {
        if (error) {
            trace_msg(@"failed submit achievement to gamecenter.");
        } else {
            [self emit:kSignalSuccess];
        }
    }];
}

- (BOOL)isCompleted {
    return self.achievement.isCompleted;
}

@end

@interface GameCenterScore ()

- (void)setLeaderboard:(GKLeaderboard*)lb;
- (void)setScore:(GKScore*)sc;

@end

@implementation GameCenterScore

@synthesize value = _value;

- (id)init {
    self = [super init];
    
    _context = 0;
    
    return self;
}

- (void)dealloc {
    safe_release(_score);
    [super dealloc];
}

- (void)setLeaderboard:(GKLeaderboard *)lb {
    safe_release(_score);
    
    _score = [[GKScore alloc] initWithCategory:lb.category];
    if (DEVICE_VERSION > 5.0) {
        [_score setShouldSetDefaultLeaderboard:YES];
        [_score setContext:_context++];
    }
    
    _score.value = _value;
}

- (void)setScore:(GKScore *)sc {
    safe_release(_score);
    
    _score = [sc retain];
    _value = _score.value;
}

- (void)setValue:(int64_t)value {
    _score.value = _value = value;
}

- (GKScore*)object {
    return (GKScore*)_score;
}

@end

@implementation GameCenterLeaderboard

@synthesize identifier = _identifier;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    safe_release(_lb);
    safe_release(_identifier);
    
    [super dealloc];
}

- (GKLeaderboard*)lb {
    if (_lb == nil) {
        _lb = [[GKLeaderboard alloc] init];
        _lb.category = _identifier;
    }
    
    return _lb;
}

- (GameCenterScore*)score {
    __block GameCenterScore* ret = nil;
    
    [self.lb loadScoresWithCompletionHandler:^(NSArray *scores, NSError *error) {
        if (error) {
            trace_msg(@"failed get scores from gamecenter.");
        } else {
            ret = [[GameCenterScore alloc] init];
            if (scores.count) {
                [ret setScore:scores.first];
            }
        }
        
        [self unblock];
    }];
    
    [self block];
    return [ret autorelease];
}

- (void)submit:(GameCenterScore *)score {
    [score setLeaderboard:self.lb];
    GKScore* sco = (GKScore*)score.object;
    [sco reportScoreWithCompletionHandler:^(NSError *error){
        if (error) {
            trace_msg(@"failed submit score to gamecenter.");
        } else {
            PASS;
        }
    }];
}

@end

@implementation GameCenterAchievementsController

NNTOBJECT_IMPL_NOSIGNALS;

- (id)init {
    self = [super init];
    
    [self setAchievementDelegate:self];
    
    return self;
}

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    
}

- (void)achievementViewControllerDidFinish:(GKAchievementViewController *)viewController {
    UIViewController* ctlr = [self attachFind:kViewControllerModalParentController];
    if (ctlr && ctlr.modalViewController == self) {
        [ctlr dismissModalViewControllerAnimated:YES];
    }
}

@end

_CXXCONTROLLER_IMPL(GameCenterAchievementsController);

@implementation GameCenterLeaderboardController

NNTOBJECT_IMPL_NOSIGNALS;

- (id)init {
    self = [super init];
    
    [self setLeaderboardDelegate:self];
    
    return self;
}

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    
}

- (void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController {
    UIViewController* ctlr = [self attachFind:kViewControllerModalParentController];
    if (ctlr && ctlr.modalViewController == self) {
        [ctlr dismissModalViewControllerAnimated:YES];
    }
}

@end

_CXXCONTROLLER_IMPL(GameCenterLeaderboardController);

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(game)

GameCenter::GameCenter()
{
    
}

GameCenter::GameCenter(id obj)
: super(obj)
{
    PASS;
}

bool GameCenter::authenticated() const
{
    return this->_self.authenticated;
}

GameCenter& GameCenter::getInstance()
{
    static GameCenter obj([objc_type shared]);
    return obj;
}

ns::String GameCenter::player_id() const
{
    return this->_self.playerId;
}

ns::String GameCenter::player_nickname() const
{
    return this->_self.playerNickname;
}

Achievement::Achievement()
{
    
}

Achievement::Achievement(ns::String const& idr)
{
    set_identifier(idr);
}

void Achievement::set_identifier(ns::String const& idr)
{
    this->_self.identifier = idr;
}

ns::String Achievement::identifier() const
{
    return this->_self.identifier;
}

void Achievement::set_percent(real val)
{
    this->_self.percentComplete = val;
}

real Achievement::percent() const
{
    return this->_self.percentComplete;
}

void Achievement::set_value(real val)
{
    set_percent(val * 100);
}

real Achievement::value() const
{
    return percent() / 100;
}

void Achievement::submit()
{
    [this->_self submit];
}

void Achievement::show_banner(bool val)
{
    this->_self.showsCompletionBanner = val;
}

bool Achievement::completed() const
{
    return this->_self.isCompleted;
}

Score::Score()
{

}

Score::Score(id obj)
: super(obj)
{
    
}

int64_t Score::value() const
{
    return this->_self.value;
}

void Score::set_value(int64_t val)
{
    this->_self.value = val;
}

Leaderboard::Leaderboard()
{
    
}

Leaderboard::Leaderboard(ns::String const& idr)
{
    this->_self.identifier = idr;
}

Score Leaderboard::score() const
{
    return this->_self.score;
}

void Leaderboard::submit(Score const& score) const
{
    [this->_self submit:score];
}

AchievementsController::AchievementsController()
{
    
}

AchievementsController::~AchievementsController()
{
    
}

LeaderboardController::LeaderboardController()
{
    
}

LeaderboardController::~LeaderboardController()
{
    
}

NNT_END_NS
NNT_END_CXX

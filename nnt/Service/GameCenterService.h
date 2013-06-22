
# ifndef __NNT_SERVICE_GAMECENTER_07EFB3B072F64724A840470E86B62DED_H_INCLUDED
# define __NNT_SERVICE_GAMECENTER_07EFB3B072F64724A840470E86B62DED_H_INCLUDED

# import <GameKit/GameKit.h>
# import "UIViewController+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(GameCenterService);

@interface GameCenterService : NNTObject {
    NNTDECL_PRIVATE(GameCenterService);
    
    NSString *_playerId, /**_playerName,*/ *_playerNickname;
    
}

@property (nonatomic, readonly, copy) NSString *playerId, /**playerName,*/ *playerNickname;

+ (id)shared;

- (BOOL)authenticated;
- (void)authorize;

@end

@interface GameCenterAchievement : NNTObject {
    GKAchievement* _achievement;
    NSString* _identifier;
}

@property (nonatomic, copy) NSString* identifier;
@property (nonatomic, assign) double percentComplete;
@property (nonatomic, assign) BOOL showsCompletionBanner;

- (void)submit;
- (BOOL)isCompleted;

@end

@interface GameCenterAchievements : NNTObject {
    NSDictionary* _records;
}

@property (nonatomic, retain) NSDictionary* records;

+ (GameCenterAchievements*)shared;
- (GameCenterAchievement*)find:(NSString*)identifier;

@end

@interface GameCenterScore : NNTObject {
    GKScore* _score;
    int64_t _value;
    int64_t _context;
}

@property (nonatomic, assign) int64_t value;

@end

@interface GameCenterLeaderboard : NNTObject {
    GKLeaderboard* _lb;
    NSString* _identifier;
}

@property (nonatomic, copy) NSString* identifier;

- (GameCenterScore*)score;
- (void)submit:(GameCenterScore*)score;

@end

NNT_EXTERN signal_t kSignalSuccess;

@interface GameCenterAchievementsController : GKAchievementViewController <GKAchievementViewControllerDelegate>
{
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

@end

_CXXCONTROLLER_DECL(GameCenterAchievementsController);

@interface GameCenterLeaderboardController : GKLeaderboardViewController <GKLeaderboardViewControllerDelegate>
{
    NNTOBJECT_DECL;
}

NNTOBJECT_PROP;

@end

_CXXCONTROLLER_DECL(GameCenterLeaderboardController);

NNT_EXTERN signal_t kSignalUserLogin;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(game)

class GameCenter
: public ns::Object<GameCenterService>
{
    typedef ns::Object<GameCenterService> super;
    
protected:
    
    GameCenter(id);
    
public:
    
    GameCenter();
    
    static GameCenter& getInstance();
    
    bool authenticated() const;
    ns::String player_id() const;
    ns::String player_nickname() const;
    
};

class Achievement
: public ns::Object<GameCenterAchievement>
{
public:
    
    Achievement();
    explicit Achievement(ns::String const&);
    
    void set_identifier(ns::String const&);
    ns::String identifier() const;
    
    void set_percent(real);
    real percent() const;
    
    // [0, 1]
    void set_value(real);
    real value() const;
    
    void submit();
    bool completed() const;
    
    //! show banner.
    void show_banner(bool=true);
    
};

class Score
: public ns::Object<GameCenterScore>
{
    typedef ns::Object<GameCenterScore> super;
    
public:
  
    Score();
    Score(id);
    
    int64_t value() const;
    void set_value(int64_t);
    
};

class Leaderboard
: public ns::Object<GameCenterLeaderboard>
{
public:
    
    Leaderboard();
    Leaderboard(ns::String const&);
    
    Score score() const;
    void submit(Score const&) const;
    
};

class AchievementsController
: public ui::SimpleController<AchievementsController, _CXXCONTROLLER(GameCenterAchievementsController), UIView>
{
public:
    
    AchievementsController();
    ~AchievementsController();
    
};

class LeaderboardController
: public ui::SimpleController<LeaderboardController, _CXXCONTROLLER(GameCenterLeaderboardController), UIView>
{
public:
    
    LeaderboardController();
    ~LeaderboardController();
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif

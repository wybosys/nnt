
# import "WSIFoundation.h"
# import "MainController.h"

# include "Juice.hpp"
# include "JuiceBox2d.h"

WSI_BEGIN_OBJC

class TestScreenManager;
class TestDriver;
class TestTree;
class TestBall;

@interface CABallLayer : CALayer

@property (nonatomic, assign) real radius;
@property (nonatomic, retain) UIColor* color;

@end

class TestBall
: public juice::PhyEntity<TestBall>
{
public:
    TestBall()
    {
        layer = [safe_alloc(CABallLayer) init];
        layer.masksToBounds = YES;
        
        this->params.friction = .1f;
        this->params.density = 1;
        this->params.restitution = .5f;
    }
    
    ~TestBall()
    {
        safe_release(layer);
    }
    
public:
    CABallLayer* layer;
};

class TestTree
: public juice::PhyTree<TestTree, juice::PhysicsBox2d>
{
public:
    TestTree()
    {
        this->physics.velocity = 6;
        this->physics.offset = 2;
        //this->physics.set_gravity(-98);
        
        TestBall* ball = NULL;
        
        ball = new TestBall;
        ball->layer.radius = 50;
        ball->layer.color = [UIColor orangeColor];
        ball->layer.frame = CGRectMake(0, 0, 100, 100);
        ball->bbx = juice::Box(juice::Position(0, 1000), juice::Size(100, 100));
        
        balls << ball;
        ball->drop();
    }
    
    ~TestTree()
    {
        juice::clear(balls);
    }
    
    juice::vector<TestBall*> balls;   
};

class TestDriver
: public juice::CococaDriver<TestDriver>
{
    
};

class TestScreenManager
: public juice::ScreenManager<TestScreenManager>
{
public:
    void prepare_scene()
    {    
        // prepare tree.
        tree->prepare();
        
        // add balls.
        juice::vector<TestBall*>::const_iterator iter_ball = tree->balls.begin();
        for (; iter_ball != tree->balls.end(); ++iter_ball)
        {
            // add ball.
            TestBall* ball = *iter_ball;
            //[driver->layer addSublayer:ball->layer];
            [driver->layer performSelectorOnMainThread:@selector(addSublayer:) withObject:ball->layer waitUntilDone:YES];
            [ball->layer performSelectorOnMainThread:@selector(setNeedsDisplay) withObject:nil waitUntilDone:YES];
            
            // add phy.
            ball->phyobj = tree->physics.add_box(ball->bbx, ball->params);
        }
    }
        
    void next_frame()
    {
        WSI_AUTORELEASEPOOL_BEGIN
        
        [CATransaction begin];
        [CATransaction setValue:(id)kCFBooleanTrue forKey:kCATransactionDisableActions];
        
        tree->physics.time = 1 / this->fps_limit;
        tree->update();
        
        juice::vector<TestBall*>::const_iterator iter_ball = tree->balls.begin();
        for (; iter_ball != tree->balls.end(); ++iter_ball)
        {
            TestBall* ball = *iter_ball;
            CGPoint pt = *(CGPoint*)(real*)tree->physics.position(ball->phyobj);
            pt.y = 1000 - pt.y;  
            CGRect rc = ball->layer.frame;
            //trace_fmt(@"%f %f", rc.origin.y, pt.y);
            rc.origin = pt;           
            ball->layer.frame = rc;
        }
        
        [CATransaction commit];
        
        WSI_AUTORELEASEPOOL_END
    }
    
    juice::Property<TestTree> tree;    
    juice::Property<TestDriver> driver;
};

@interface MainView : WSIUIView

@end

@implementation MainView

@end

@implementation MainController 

- (void)loadView {
    MainView* view = [[MainView alloc] initWithZero];
    self.view = view;
    [view release];
}

- (void)viewIsLoading {
    MainView* view = (MainView*)self.view;
    
    TestScreenManager* scrmgr = new TestScreenManager;
    TestDriver* drv = new TestDriver;
    TestTree* tree = new TestTree;   
    
    CGRect rc = CGRectMake(0, 0, 1000, 1000);
    // set layer.
    [view.layer addSublayer:drv->layer];
    drv->layer.frame = rc;
    
    // load data.
    scrmgr->driver = drv;
    scrmgr->tree = tree;
    tree->physics.box = juice::Box(juice::Position(0, -1000), juice::Size(1000, 1000));
    
    // render.
    scrmgr->fps_limit = 60;
    scrmgr->render();
    
    // clear.
    drv->drop();
    tree->drop();
    scrmgr->drop();
}

@end

@implementation CABallLayer

@synthesize radius;
@synthesize color;

- (id)init {
    self = [super init];
    self.backgroundColor = [UIColor clearColor].CGColor;
    return self;
}

- (void)dealloc {
    safe_release(color);
    [super dealloc];
}

- (void)drawInContext:(CGContextRef)ctx {
    //CGRect rc = CGContextGetClipBoundingBox(ctx);
    CGContextAddArc(ctx, radius, radius, radius, 0, M_PI + M_PI, 0);
    CGContextSetFillColorWithColor(ctx, color.CGColor);
    CGContextFillPath(ctx);
}

@end

WSI_END_OBJC
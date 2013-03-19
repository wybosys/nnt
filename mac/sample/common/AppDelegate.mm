
# import "wsi/WSIFoundation.h"
# import "AppDelegate.h"

# include "TestCommon.h"
# include "TestBoost.h"
# include "TestConfig.h"
# include "TestLogger.h"
# include "TestTask.h"

@implementation AppDelegate

- (void)load:(NSNotification *)aNotification {
    wsiapp::TestCommon com;
    com.main();
    
    wsiapp::TestBoost boost;
    boost.main();
    
    wsiapp::TestConfig config;
    config.main();
    
    wsiapp::TestLogger logger;
    logger.main();
    
    wsiapp::TestTask task;
    task.main();
}

@end

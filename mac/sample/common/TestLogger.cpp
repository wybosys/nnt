
# include "wsi/WSIFoundation.h"
# include "TestLogger.h"
# include "wsi/Store/WSILogger.h"
# include "wsi/Core/App.h"

WSIAPP_BEGIN

void TestLogger::main()
{
    ::wsi::store::DMYLogger logger;
    logger.open(::wsi::Application::getInstance()->working_directory() + "common_", ".log");
    logger.warn("WARNNING");
    logger.notice("NOTICE");
    logger.fatal("FATAL");
    logger.info("INFO");
}

WSIAPP_END